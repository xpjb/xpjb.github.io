use proc_macro2::{Delimiter, TokenStream, TokenTree};
use serde_json::{json, Value};
use std::{fs, str::FromStr};
use syn::visit::{self, Visit};
fn tokens(stream:TokenStream)->usize { stream.into_iter().map(|t|match t {
    TokenTree::Group(g)=>tokens(g.stream())+if g.delimiter()==Delimiter::None{0}else{2}, _=>1
}).sum() }
fn count_item(item:syn::Item)->usize {
    let file=syn::File{shebang:None,attrs:vec![],items:vec![item]};
    tokens(TokenStream::from_str(&prettyplease::unparse(&file)).unwrap())
}
#[derive(Default)]
struct Counts { uses:usize,use_tokens:usize,traits:usize,trait_tokens:usize,modules:usize,module_tokens:usize,empty_impls:usize,frames:usize,false_cfg:usize }
impl<'ast> Visit<'ast> for Counts {
    fn visit_item_use(&mut self,item:&'ast syn::ItemUse) {
        self.uses+=1;self.use_tokens+=count_item(syn::Item::Use(item.clone()));
        visit::visit_item_use(self,item);
    }
    fn visit_item_trait(&mut self,item:&'ast syn::ItemTrait) {
        let name=item.ident.to_string();
        let generated=name.rsplit_once("Behaviour").is_some_and(|(_,suffix)|suffix.chars().all(|c|c.is_ascii_digit()));
        if generated {self.traits+=1;self.trait_tokens+=count_item(syn::Item::Trait(item.clone()));}
        else {visit::visit_item_trait(self,item);}
    }
    fn visit_item_mod(&mut self,item:&'ast syn::ItemMod) {
        self.modules+=1;let mut wrapper=item.clone();
        if let Some((_,items))=&mut wrapper.content {items.clear();}
        self.module_tokens+=count_item(syn::Item::Mod(wrapper));
        visit::visit_item_mod(self,item);
    }
    fn visit_item_impl(&mut self,item:&'ast syn::ItemImpl){
        if item.items.is_empty(){self.empty_impls+=1;}
        visit::visit_item_impl(self,item);
    }
    fn visit_expr_closure(&mut self,item:&'ast syn::ExprClosure){
        if item.inputs.iter().any(|p|match p {
            syn::Pat::Type(p)=>matches!(p.pat.as_ref(),syn::Pat::Ident(i)if i.ident.to_string().starts_with("__inline_")),
            syn::Pat::Ident(p)=>p.ident.to_string().starts_with("__inline_"),_=>false
        }) {self.frames+=1;}
        visit::visit_expr_closure(self,item);
    }
    fn visit_attribute(&mut self,a:&'ast syn::Attribute){
        if a.path().is_ident("cfg") {
            if let Ok(syn::Meta::List(m))=a.parse_args::<syn::Meta>() {
                if m.path.is_ident("any")&&m.tokens.is_empty(){self.false_cfg+=1;}
            }
        }
        visit::visit_attribute(self,a);
    }
}
fn main(){
    let p=std::env::args().nth(1).expect("manifest");
    let mut rows:Vec<Value>=serde_json::from_slice(&fs::read(p).unwrap()).unwrap();
    for row in &mut rows {
        let text=fs::read_to_string(row["absolute"].as_str().unwrap()).unwrap();
        let file=syn::parse_file(&text).unwrap();let mut c=Counts::default();c.visit_file(&file);
        let total=tokens(TokenStream::from_str(&text).unwrap());
        let used=c.use_tokens+c.trait_tokens+c.module_tokens;assert!(used<=total);
        row["physical_lines"]=text.lines().count().into();
        row["formatted_lines"]=prettyplease::unparse(&file).lines().count().into();
        row["tokens"]=total.into();
        row["anatomy"]=json!({"import_statements":c.uses,"import_tokens":c.use_tokens,"behaviour_traits":c.traits,"behaviour_trait_tokens":c.trait_tokens,"module_declarations":c.modules,"module_wrapper_tokens":c.module_tokens,"other_tokens":total-used,"empty_impl_blocks":c.empty_impls,"parameterized_generated_closures":c.frames,"always_false_cfg_attributes":c.false_cfg});
        row.as_object_mut().unwrap().remove("absolute");
    }
    println!("{}",serde_json::to_string_pretty(&rows).unwrap());
}

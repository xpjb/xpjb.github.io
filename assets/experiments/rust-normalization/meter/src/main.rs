use proc_macro2::{Delimiter, TokenStream, TokenTree};
use serde_json::Value;
use quote::ToTokens;
use syn::visit_mut::VisitMut;
use std::{fs, str::FromStr};

// Group delimiters each count once; punctuation is proc_macro2 punctuation,
// and a whole literal counts as one token. Doc comments become attributes.
fn tokens(stream: TokenStream) -> usize {
    stream.into_iter().map(|t| match t {
        TokenTree::Group(g) => tokens(g.stream()) + if g.delimiter() == Delimiter::None { 0 } else { 2 },
        _ => 1,
    }).sum()
}
fn without_tests(meta: &syn::Meta) -> Option<bool> {
    match meta {
        syn::Meta::Path(p) if p.is_ident("test") => Some(false),
        syn::Meta::List(l) => {
            let values: Vec<_> = l.parse_args_with(syn::punctuated::Punctuated::<syn::Meta,syn::Token![,]>::parse_terminated).ok()?.iter().map(without_tests).collect();
            if l.path.is_ident("all") { if values.contains(&Some(false)) {Some(false)} else if values.iter().all(|v|*v==Some(true)){Some(true)}else{None} }
            else if l.path.is_ident("any") {if values.contains(&Some(true)){Some(true)}else if values.iter().all(|v|*v==Some(false)){Some(false)}else{None}}
            else if l.path.is_ident("not") && values.len()==1 {values[0].map(|v|!v)} else {None}
        }
        _ => None
    }
}
struct Production;
impl VisitMut for Production {
    fn visit_file_mut(&mut self, file: &mut syn::File) { self.items(&mut file.items); }
    fn visit_item_mod_mut(&mut self, module: &mut syn::ItemMod) { if let Some((_,items))=&mut module.content {self.items(items);} }
}
impl Production {
    fn items(&mut self, items: &mut Vec<syn::Item>) {
        items.retain(|item| {
            let attrs = match item {
                syn::Item::Fn(i)=>&i.attrs, syn::Item::Mod(i)=>&i.attrs, syn::Item::Use(i)=>&i.attrs,
                syn::Item::Struct(i)=>&i.attrs, syn::Item::Enum(i)=>&i.attrs, syn::Item::Impl(i)=>&i.attrs,
                syn::Item::Trait(i)=>&i.attrs, syn::Item::Type(i)=>&i.attrs, syn::Item::Const(i)=>&i.attrs,
                syn::Item::Static(i)=>&i.attrs, syn::Item::Macro(i)=>&i.attrs, _=>return true,
            };
            !attrs.iter().any(|a| a.path().segments.last().is_some_and(|s| s.ident=="test")
                || (a.path().is_ident("cfg") && a.parse_args::<syn::Meta>().ok().and_then(|m|without_tests(&m))==Some(false)))
        });
        for item in items {self.visit_item_mut(item);}
    }
}
fn main() {
    let manifest = std::env::args().nth(1).expect("file manifest");
    let mut rows: Vec<Value> = serde_json::from_slice(&fs::read(manifest).unwrap()).unwrap();
    for row in &mut rows {
        let path = row["absolute"].as_str().unwrap();
        let source = fs::read_to_string(path).unwrap();
        let file = syn::parse_file(&source).unwrap_or_else(|e| panic!("{path}: {e}"));
        let formatted = prettyplease::unparse(&file);
        let stream = TokenStream::from_str(&source).unwrap();
        row["physical_lines"] = source.lines().count().into();
        row["nonblank_lines"] = source.lines().filter(|l| !l.trim().is_empty()).count().into();
        row["bytes"] = source.len().into();
        row["formatted_lines"] = formatted.lines().count().into();
        row["formatted_nonblank_lines"] = formatted.lines().filter(|l| !l.trim().is_empty()).count().into();
        row["tokens"] = tokens(stream).into();
        // These project trees put standalone test sources under tests/ or tests.rs.
        // Inline test-only items are removed structurally, not by line matching.
        let test_file = std::path::Path::new(row["path"].as_str().unwrap()).components().any(|p| p.as_os_str()=="tests" || p.as_os_str()=="tests.rs");
        let mut production = file;
        if test_file { production.items.clear(); production.attrs.clear(); }
        else { Production.visit_file_mut(&mut production); }
        row["production_formatted_lines"] = prettyplease::unparse(&production).lines().count().into();
        row["production_tokens"] = tokens(production.into_token_stream()).into();
        row.as_object_mut().unwrap().remove("absolute");
    }
    println!("{}", serde_json::to_string_pretty(&rows).unwrap());
}

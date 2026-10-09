use proc_macro2::{Delimiter, TokenStream, TokenTree};
use serde_json::Value;
use std::{fs, str::FromStr};

// Group delimiters each count once; punctuation is proc_macro2 punctuation,
// and a whole literal counts as one token. Doc comments become attributes.
fn tokens(stream: TokenStream) -> usize {
    stream.into_iter().map(|t| match t {
        TokenTree::Group(g) => tokens(g.stream()) + if g.delimiter() == Delimiter::None { 0 } else { 2 },
        _ => 1,
    }).sum()
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
        row.as_object_mut().unwrap().remove("absolute");
    }
    println!("{}", serde_json::to_string_pretty(&rows).unwrap());
}

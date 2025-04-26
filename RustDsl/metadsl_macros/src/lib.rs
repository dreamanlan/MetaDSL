extern crate proc_macro;
use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, ItemStruct, Fields};

#[proc_macro_attribute]
pub fn add_abstract_syntax_component_fields(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemStruct);

    let name = input.ident;
    let fields = input.fields;

    let expanded = if let Fields::Named(fields_named) = fields {
        let existing_fields = fields_named.named;

        quote! {
            pub struct #name {
                #existing_fields
                m_separator: i32,
            }
        }
    } else {
        quote! {
            compile_error!("add_field can only be used with structs with named fields");
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro]
pub fn impl_abstract_syntax_component(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn impl_set_seperator(&mut self, sep: i32)
        {
            self.m_separator = sep;
        }
        fn impl_get_seperator(&self) -> i32
        {
            return self.m_separator;
        }
        fn impl_get_sep_char(&self) -> char
        {
            match (self.m_separator) {
                SEPARATOR_COMMA => {
                    return ',';
                }
                SEPARATOR_SEMICOLON => {
                    return ';';
                }
                _ => {
                    return ' ';
                }
            }
        }

        fn impl_set_empty_separator(&mut self)
        {
            self.m_separator = SEPARATOR_NOTHING;
        }
        fn impl_set_comma_separator(&mut self)
        {
            self.m_separator = SEPARATOR_COMMA;
        }
        fn impl_set_semi_colon_separator(&mut self)
        {
            self.m_separator = SEPARATOR_SEMICOLON;
        }
        fn impl_is_empty_separator(&self) -> bool
        {
            return self.m_separator == SEPARATOR_NOTHING;
        }
        fn impl_is_comma_separator(&self) -> bool
        {
            return self.m_separator == SEPARATOR_COMMA;
        }
        fn impl_is_semi_colon_separator(&self) -> bool
        {
            return self.m_separator == SEPARATOR_SEMICOLON;
        }
    };

    TokenStream::from(expanded)
}

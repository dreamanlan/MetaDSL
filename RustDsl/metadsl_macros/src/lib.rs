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

#[proc_macro_attribute]
pub fn add_abstract_expression_fields(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemStruct);

    let name = input.ident;
    let fields = input.fields;

    let expanded = if let Fields::Named(fields_named) = fields {
        let existing_fields = fields_named.named;

        quote! {
            pub struct #name<'a> {
                #existing_fields
                m_calculator: Option<Rc<DslCalculatorCell<'a>>>,
                m_dsl: Option<SyntaxComponent>,
            }
        }
    } else {
        quote! {
            compile_error!("add_field can only be used with structs with named fields");
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro_attribute]
pub fn add_abstract_and_simple_expression_fields(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemStruct);

    let name = input.ident;
    let fields = input.fields;

    let expanded = if let Fields::Named(fields_named) = fields {
        let existing_fields = fields_named.named;

        quote! {
            pub struct #name<'a> {
                #existing_fields
                m_calculator: Option<Rc<DslCalculatorCell<'a>>>,
                m_dsl: Option<SyntaxComponent>,
                m_exps: Option<Vec<ExpressionBox<'a>>>,
            }
        }
    } else {
        quote! {
            compile_error!("add_field can only be used with structs with named fields");
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro_attribute]
pub fn add_object_dispatch_fields(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemStruct);

    let name = input.ident;
    let fields = input.fields;

    let expanded = if let Fields::Named(fields_named) = fields {
        let existing_fields = fields_named.named;

        quote! {
            pub struct #name {
                #existing_fields
                m_obj_id: u32,
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
pub fn impl_abstract_expression(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn as_dyn(&mut self) -> &mut dyn AbstractExpression<'a>
        {
            self
        }
        fn impl_calculator(&self) -> &Rc<DslCalculatorCell<'a>>
        {
            if let Some(calculator) = &self.m_calculator {
                return calculator;
            }
            panic!("no calculator");
        }
        fn impl_syntax_component(&self) -> &SyntaxComponent
        {
            if let Some(dsl) = &self.m_dsl {
                return dsl;
            }
            panic!("no syntax component");
        }
        fn impl_set_calculator(&mut self, calculator: Rc<DslCalculatorCell<'a>>)
        {
            self.m_calculator = Some(calculator);
        }
        fn impl_set_syntax_component(&mut self, dsl: SyntaxComponent)
        {
            self.m_dsl = Some(dsl);
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro]
pub fn impl_simple_expression(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn impl_get_expressions(&self) -> &Option<Vec<ExpressionBox<'a>>>
        {
            return &self.m_exps;
        }
        fn impl_get_expressions_mut(&mut self) -> &mut Option<Vec<ExpressionBox<'a>>>
        {
            return &mut self.m_exps;
        }
        fn impl_set_expressions(&mut self, exps: Vec<ExpressionBox<'a>>)
        {
            self.m_exps = Some(exps);
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro]
pub fn impl_expression_with_abstract(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn calc(&mut self) -> DslCalculatorValue
        {
            return AbstractExpression::calc(self);
        }
        fn load_syntax_component(&mut self, dsl: &SyntaxComponent, calculator: Rc<DslCalculatorCell<'a>>) -> bool
        {
            return AbstractExpression::load_syntax_component(self, dsl, calculator);
        }
        fn load_value_or_function(&mut self, dsl: &ValueOrFunction, calculator: Rc<DslCalculatorCell<'a>>) -> bool
        {
            return AbstractExpression::load_value_or_function(self, dsl, calculator);
        }
        fn load_value_syntax(&mut self, dsl: ValueData, calculator: Rc<DslCalculatorCell<'a>>) -> bool
        {
            return AbstractExpression::load_value_syntax(self, dsl, calculator);
        }
        fn load_function_syntax(&mut self, dsl: FunctionData, calculator: Rc<DslCalculatorCell<'a>>) -> bool
        {
            return AbstractExpression::load_function_syntax(self, dsl, calculator);
        }
        fn load_statement_syntax(&mut self, dsl: StatementData, calculator: Rc<DslCalculatorCell<'a>>) -> bool
        {
            return AbstractExpression::load_statement_syntax(self, dsl, calculator);
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro]
pub fn impl_abstract_with_simple(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn do_calc(&mut self) -> DslCalculatorValue
        {
            return SimpleExpressionBase::do_calc(self);
        }
        fn load_expressions(&mut self, exps: &mut Vec<ExpressionBox<'a>>) -> bool
        {
            return SimpleExpressionBase::load_expressions(self, exps);
        }
    };

    TokenStream::from(expanded)
}

#[proc_macro]
pub fn impl_object_dispatch(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
        fn get_object_id(&self) -> u32
        {
            return self.m_obj_id;
        }
        fn set_object_id(&mut self, id: u32)
        {
            self.m_obj_id = id;
        }
    };

    TokenStream::from(expanded)
}

//---------------------------------------------------------------------------------------
#[proc_macro_attribute]
pub fn add_fields_template(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemStruct);

    let name = input.ident;
    let fields = input.fields;

    let expanded = if let Fields::Named(fields_named) = fields {
        let existing_fields = fields_named.named;

        quote! {
            pub struct #name<'a> {
                #existing_fields

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
pub fn impl_template(_input: TokenStream) -> TokenStream {
    let expanded = quote! {
    };

    TokenStream::from(expanded)
}
//---------------------------------------------------------------------------------------
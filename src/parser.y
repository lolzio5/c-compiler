// Adapted from: https://www.lysator.liu.se/c/ANSI-C-grammar-y.html

%code requires{
    #include "ast.hpp"
    #include <memory>

    extern Node *g_root;
    extern FILE *yyin;
    int yylex(void);
    void yyerror(const char *);
}

// Represents the value associated with any kind of AST node.
%union{
  Node         *node;
  NodeList     *nodes;
  int          number_int;
  double       number_float;
  std::string  *string;
  yytokentype  token;
}

%token IDENTIFIER INT_CONSTANT FLOAT_CONSTANT STRING_LITERAL
%token PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token TYPE_NAME TYPEDEF EXTERN STATIC AUTO REGISTER SIZEOF
%token CHAR SHORT INT LONG SIGNED UNSIGNED FLOAT DOUBLE CONST VOLATILE VOID
%token STRUCT UNION ENUM ELLIPSIS
%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%type <node> translation_unit function_definition primary_expression postfix_expression
%type <node> unary_expression cast_expression multiplicative_expression additive_expression shift_expression relational_expression
%type <node> equality_expression and_expression exclusive_or_expression inclusive_or_expression logical_and_expression logical_or_expression
%type <node> conditional_expression assignment_expression expression constant_expression declaration declaration_specifiers
%type <node> init_declarator type_specifier struct_specifier struct_declaration_list struct_declaration specifier_qualifier_list struct_declarator_list
%type <node> struct_declarator enum_specifier enumerator_list enumerator declarator direct_declarator pointer parameter_list parameter_declaration
%type <node> identifier_list type_name abstract_declarator direct_abstract_declarator initializer initializer_list statement labeled_statement
%type <node> compound_statement expression_statement selection_statement iteration_statement jump_statement

%type <nodes> statement_list external_declaration argument_expression_list init_declarator_list declaration_list

%type <string> unary_operator assignment_operator storage_class_specifier

%type <number_int> INT_CONSTANT STRING_LITERAL
%type <number_float> FLOAT_CONSTANT
%type <string> IDENTIFIER


%start ROOT
%%

ROOT
  : translation_unit { g_root = $1; }

translation_unit
	: external_declaration { $$ = $1; }
	| translation_unit external_declaration
	;

external_declaration
	: function_definition { $$ = new NodeList($1); }
	| external_declaration function_definition { $1->PushBack($2); $$=$1; }
	| declaration
	;

function_definition
	: declaration_specifiers declarator declaration_list compound_statement
	| declaration_specifiers declarator compound_statement {
		$$ = new FunctionDefinition($1, $2, $3);
	}
	| declarator declaration_list compound_statement
	| declarator compound_statement
	| declaration_specifiers declarator ';' { $$ = new EmptyFunctionDefinition($1, $2); }
	;


primary_expression
	: IDENTIFIER {
       	$$ = new VariableIdentifier(*$1);
		delete $1;
	}
	| INT_CONSTANT {
		$$ = new IntConstant($1);
	}
    | FLOAT_CONSTANT {
		$$ = new FloatConstant($1);
	}
	| STRING_LITERAL {
		$$ = new StringConstant($1);
	}
	| '(' expression ')' { $$ = $2; }
	;

postfix_expression
	: primary_expression { $$ = $1; }
	| postfix_expression '[' expression ']'
	| postfix_expression '(' ')' { $$ = new FunctionCall($1); }
	| postfix_expression '(' argument_expression_list ')' { $$ = new FunctionCallWithArguments($1, $3); }
	| postfix_expression '.' IDENTIFIER
	| postfix_expression PTR_OP IDENTIFIER
	| postfix_expression INC_OP
	| postfix_expression DEC_OP
	;

argument_expression_list
	: assignment_expression { $$ = new NodeList($1); }
	| argument_expression_list ',' assignment_expression { $1->PushBack($3); $$ = $1; }
	;

unary_expression
	: postfix_expression { $$ = $1; }
	| INC_OP unary_expression
	| DEC_OP unary_expression
	| unary_operator cast_expression
	| SIZEOF unary_expression { $$ = new SizeOfVariable($2); }
	| SIZEOF '(' type_name ')' { $$ = new SizeOfType($3); }
	;

unary_operator
	: '&'
	| '*'
	| '+'
	| '-'
	| '~'
	| '!'
	;

cast_expression
	: unary_expression { $$ = $1; }
	| '(' type_name ')' cast_expression
	;

multiplicative_expression
	: cast_expression { $$ = $1; }
	| multiplicative_expression '*' cast_expression { $$ = new MulOperation($1, $3); }
	| multiplicative_expression '/' cast_expression { $$ = new DivOperation($1, $3); }
	| multiplicative_expression '%' cast_expression { $$ = new ModuloOperation($1, $3); }
	;

additive_expression
	: multiplicative_expression { $$ = $1; }
	| additive_expression '+' multiplicative_expression { $$ = new AddOperation($1, $3); }
	| additive_expression '-' multiplicative_expression { $$ = new SubOperation($1, $3); }
	;

shift_expression
	: additive_expression { $$ = $1; }
	| shift_expression LEFT_OP additive_expression { $$ = new ShiftLeft($1, $3); }
	| shift_expression RIGHT_OP additive_expression { $$ = new ShiftRight($1, $3); }
	;

relational_expression
	: shift_expression { $$ = $1; }
	| relational_expression '<' shift_expression {$$ = new LessThan($1, $3);}
	| relational_expression '>' shift_expression {$$ = new GreaterThan($1, $3);}
	| relational_expression LE_OP shift_expression {$$ = new LessThanEqual($1, $3);}
	| relational_expression GE_OP shift_expression {$$ = new GreaterThanEqual($1, $3);}
	;

equality_expression
	: relational_expression { $$=$1; }
	| equality_expression EQ_OP relational_expression {$$= new Equal($1,$3);}
	| equality_expression NE_OP relational_expression {$$= new NotEqual($1,$3);}
	;

and_expression
	: equality_expression { $$ = $1; }
	| and_expression '&' equality_expression {$$ = new BitwiseAnd($1, $3);}


exclusive_or_expression
	: and_expression { $$ = $1; }
	| exclusive_or_expression '^' and_expression {$$ = new BitwiseXOR($1, $3);}
	;

inclusive_or_expression
	: exclusive_or_expression { $$ = $1; }
	| inclusive_or_expression '|' exclusive_or_expression {$$ = new BitwiseOr($1, $3);}
	;

logical_and_expression
	: inclusive_or_expression { $$ = $1; }
	| logical_and_expression AND_OP inclusive_or_expression { $$ = new LogicalAnd($1, $3); }
	;

logical_or_expression
	: logical_and_expression { $$ = $1; }
	| logical_or_expression OR_OP logical_and_expression { $$ = new LogicalOr($1, $3); }
	;


conditional_expression
	: logical_or_expression { $$ = $1; }
	| logical_or_expression '?' expression ':' conditional_expression
	;

assignment_expression
	: conditional_expression { $$ = $1; }
	| unary_expression '=' assignment_expression  { $$ = new VariableAssignExpression($1, $3); }
	| unary_expression ADD_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new AddOperation($1, $3)); }
	| unary_expression SUB_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new SubOperation($1, $3)); }
	| unary_expression MUL_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new MulOperation($1, $3)); }
	| unary_expression DIV_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new DivOperation($1, $3)); }
	| unary_expression MOD_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new ModuloOperation($1, $3)); }
	| unary_expression LEFT_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new ShiftLeft($1, $3)); }
	| unary_expression RIGHT_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new ShiftRight($1, $3)); }
	| unary_expression AND_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new BitwiseAnd($1, $3)); }
	| unary_expression OR_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new BitwiseOr($1, $3)); }
	| unary_expression XOR_ASSIGN assignment_expression { $$ = new VariableAssignExpression($1, new BitwiseXOR($1, $3)); }
	;

assignment_operator
	: '='
	| MUL_ASSIGN
	| DIV_ASSIGN
	| MOD_ASSIGN
	| ADD_ASSIGN
	| SUB_ASSIGN
	| LEFT_ASSIGN
	| RIGHT_ASSIGN
	| AND_ASSIGN
	| XOR_ASSIGN
	| OR_ASSIGN
	;

expression
	: assignment_expression { $$ = $1; }
	| expression ',' assignment_expression
	;

constant_expression
	: conditional_expression { $$ = $1; }
	;

declaration
	: declaration_specifiers ';'
	| declaration_specifiers init_declarator_list ';' { $$ = new MultiDeclarator($1, $2); }
	;

declaration_specifiers
	: storage_class_specifier
	| storage_class_specifier declaration_specifiers
	| type_specifier { $$ = $1; }
	| type_specifier declaration_specifiers
	;

init_declarator_list
	: init_declarator { $$ = new NodeList($1); }
	| init_declarator_list ',' init_declarator { $1->PushBack($3); $$=$1; }
	;

init_declarator
	: declarator { $$ = new VariableDeclarator($1,nullptr); }
	| declarator '=' initializer {
		$$ = new VariableDeclarator($1,$3);
	}
	;

storage_class_specifier
	: TYPEDEF
	| EXTERN
	| STATIC
	| AUTO
	| REGISTER
	;

type_specifier
	: VOID {
		$$ = new TypeSpecifier("void");
	}
	| CHAR {
		$$ = new TypeSpecifier("char");
	}
	| SHORT {
		$$ = new TypeSpecifier("short");
	}
	| INT {
		$$ = new TypeSpecifier("int");
	}
	| LONG {
		$$ = new TypeSpecifier("long");
	}
	| FLOAT {
		$$ = new TypeSpecifier("float");
	}
	| DOUBLE {
		$$ = new TypeSpecifier("double");
	}
	| SIGNED {
		$$ = new TypeSpecifier("signed");
	}
	| UNSIGNED {
		$$ = new TypeSpecifier("unsigned");
	}
  	| struct_specifier
	| enum_specifier
	| TYPE_NAME
	;

struct_specifier
	: STRUCT IDENTIFIER '{' struct_declaration_list '}'
	| STRUCT '{' struct_declaration_list '}'
	| STRUCT IDENTIFIER
	;

struct_declaration_list
	: struct_declaration
	| struct_declaration_list struct_declaration
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list
	| type_specifier { $$ = $1; }
	;

struct_declarator_list
	: struct_declarator
	| struct_declarator_list ',' struct_declarator
	;

struct_declarator
	: declarator
	| ':' constant_expression
	| declarator ':' constant_expression
	;

enum_specifier
	: ENUM '{' enumerator_list '}'
	| ENUM IDENTIFIER '{' enumerator_list '}'
	| ENUM IDENTIFIER
	;

enumerator_list
	: enumerator
	| enumerator_list ',' enumerator
	;

enumerator
	: IDENTIFIER
	| IDENTIFIER '=' constant_expression
	;

declarator
	: pointer direct_declarator
	| direct_declarator { $$ = $1; }
	;

direct_declarator
	: IDENTIFIER {
		$$ = new FunctionIdentifier(*$1); //function name, pointer to String is owned directly
        delete $1;
	}
	| '(' declarator ')'
	| direct_declarator '[' constant_expression ']' //array declarator
	| direct_declarator '[' ']'
	| direct_declarator '(' parameter_list ')' { $$ = new FunctionWithParamDefinition($1,$3); }
	| direct_declarator '(' identifier_list ')'
	| direct_declarator '(' ')' {
		$$ = new DirectDeclarator($1); //no parameters
	}
	;

pointer
	: '*'
	| '*' pointer
	;

parameter_list
	: parameter_declaration { $$ = $1; }
	| parameter_list ',' parameter_declaration { $$ = new ParameterList($1, $3); }
	;

parameter_declaration
	: declaration_specifiers declarator { $$ = new ParameterDeclarator($1, $2); }
	| declaration_specifiers abstract_declarator
	| declaration_specifiers
	;

identifier_list
	: IDENTIFIER
	| identifier_list ',' IDENTIFIER
	;

type_name
	: specifier_qualifier_list { $$ = $1; }
	| specifier_qualifier_list abstract_declarator
	;

abstract_declarator
	: pointer
	| direct_abstract_declarator
	| pointer direct_abstract_declarator
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'
	| '[' ']'
	| '[' constant_expression ']'
	| direct_abstract_declarator '[' ']'
	| direct_abstract_declarator '[' constant_expression ']'
	| '(' ')'
	| '(' parameter_list ')'
	| direct_abstract_declarator '(' ')'
	| direct_abstract_declarator '(' parameter_list ')'
	;

initializer
	: assignment_expression { $$ = $1; }
	| '{' initializer_list '}'
	| '{' initializer_list ',' '}'
	;

initializer_list
	: initializer
	| initializer_list ',' initializer
	;

statement
	: labeled_statement
	| compound_statement { $$ = $1; }
	| expression_statement { $$ = $1; }
	| selection_statement { $$ = $1; }
	| iteration_statement { $$ = $1; }
	| jump_statement { $$ = $1; }
	;

labeled_statement
	: IDENTIFIER ':' statement
	| CASE constant_expression ':' statement
	| DEFAULT ':' statement
	;

compound_statement
	: '{' '}' {
		$$ = nullptr;
	}
	| '{' statement_list '}' {
		$$ = $2;
	}
	| '{' declaration_list '}' {
		$$ = $2;
	}
	| '{' declaration_list statement_list '}'  {
		$$ = $3; // may need to implement multiline here
	}
	;

declaration_list
	: declaration { $$ = new NodeList($1); }
	| declaration_list declaration { $1->PushBack($2); $$=$1; }
	;

statement_list
	: statement { $$ = new NodeList($1); }  // creates a list of nodes
	| statement_list statement { $1->PushBack($2);
								 $$=$1;
	}
	;

expression_statement
	: ';'
	| expression ';' { $$ = $1; }
	;

selection_statement
	: IF '(' expression ')' statement { $$ = new IfStatement($3, $5); }
	| IF '(' expression ')' statement ELSE statement { $$ = new IfElseStatement($3, $5, $7);}
	| SWITCH '(' expression ')' statement {$$= new SwitchStatement($3, $5);}
	;

iteration_statement
	: WHILE '(' expression ')' statement { $$ = new WhileLoop($3, $5); }
	| DO statement WHILE '(' expression ')' ';'
	| FOR '(' expression_statement expression_statement ')' statement
	| FOR '(' expression_statement expression_statement expression ')' statement { $$ = new ForLoop($3, $4, $5, $7);}
	;

jump_statement
	: GOTO IDENTIFIER ';'
	| CONTINUE ';'
	| BREAK ';'
	| RETURN ';' {
		$$ = new ReturnStatement(nullptr);
	}
	| RETURN expression ';' {
		$$ = new ReturnStatement($2);
	}
	;

%%

Node *g_root;

Node *ParseAST(std::string file_name)
{
  yyin = fopen(file_name.c_str(), "r");
  if(yyin == NULL){
    std::cerr << "Couldn't open input file: " << file_name << std::endl;
    exit(1);
  }
  g_root = nullptr;
  yyparse();
  return g_root;
}

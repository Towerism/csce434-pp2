/* File: parser.y
 * --------------
 * Yacc input file to generate the parser for the compiler.
 *
 * pp2: your job is to write a parser that will construct the parse tree
 *      and if no parse errors were found, print it.  The parser should
 *      accept the language as described in specification, and as augmented
 *      in the pp2 handout.
 */

%{

/* Just like lex, the text within this first region delimited by %{ and %}
 * is assumed to be C/C++ code and will be copied verbatim to the y.tab.c
 * file ahead of the definitions of the yyparse() function. Add other header
 * file inclusions or C++ variable declarations/prototypes that are needed
 * by your code here.
 */
#include <string.h>

#include <util/errors.hh>
#include <util/utility.hh>
#include "scanner.hh" // for yylex
#include "parser.hh"

  void yyerror(const char *msg); // standard error-handling routine

  static Operator* makeOp(yyltype loc, const char* str);
%}

/* The section before the first %% is the Definitions section of the yacc
 * input file. Here is where you declare tokens and types, add precedence
 * and associativity options, and so on.
 */

/* yylval
 * ------
 * Here we define the type of the yylval global variable that is used by
 * the scanner to store attibute information about the token just scanned
 * and thus communicate that information to the parser.
 *
 * pp2: You will need to add new fields to this union as you add different
 *      attributes to your non-terminal symbols.
 */
%union {
  int integerConstant;
  bool boolConstant;
  char* stringConstant;
  double doubleConstant;
  char identifier[MaxIdentLen+1]; // +1 for terminating null
  char punctuation;
  Identifier* identifierNode;
  Decl* decl;
  VarDecl* varDecl;
  FnDecl* fnDecl;
  ClassDecl* classDecl;
  InterfaceDecl* interfaceDecl;
  Type* type;
  NamedType* namedType;
  Expr* expr;
  Stmt* stmt;
  CaseStmt* caseStmt;
  DefaultStmt* defaultStmt;
  List<Decl*>* declList;
  List<VarDecl*>* varDeclList;
  List<Stmt*>* stmtList;
  List<NamedType*>* namedTypeList;
  List<Expr*>* exprList;
  List<CaseStmt*>* caseStmtList;
}

/* Tokens * ------
 * Here we tell yacc about all the token types that we are using.
 * Yacc will assign unique numbers to these and export the #define
 * in the generated y.tab.h header file.
 */
%token   T_Void T_Bool T_Int T_Double T_String T_Class
%token   T_LessEqual T_GreaterEqual T_Equal T_NotEqual T_Dims
%token   T_And T_Or T_Null T_Extends T_This T_Interface T_Implements
%token   T_While T_For T_If T_Else T_Return T_Break
%token   T_New T_NewArray T_Print T_ReadInteger T_ReadLine
%token   T_Incr T_Decr T_Switch T_Case T_Default

%token <identifier> T_Identifier
%token <stringConstant> T_StringConstant
%token <integerConstant> T_IntConstant
%token <doubleConstant> T_DoubleConstant
%token <boolConstant> T_BoolConstant
%token <punctuation> '='

%nonassoc '='
%left T_Or
%left T_And
%nonassoc T_Equal T_NotEqual
%nonassoc '<' T_LessEqual '>' T_GreaterEqual
%left '+' '-'
%left '*' '/' '%'
%left '!' P_UnaryMinus T_Incr T_Decr
%nonassoc P_IncrHigher
%nonassoc '[' '.'

%nonassoc P_NoElse
%nonassoc T_Else
%nonassoc P_CaseMatchedStmt
%nonassoc P_DefaultMatchedStmt
%nonassoc P_CaseEmpty
%nonassoc P_DefaultEmpty

/* Non-terminal types
 * ------------------
 * In order for yacc to assign/access the correct field of $$, $1, we
 * must to declare which field is appropriate for the non-terminal.
 * As an example, this first type declaration establishes that the DeclList
 * non-terminal uses the field named "declList" in the yylval union. This
 * means that when we are setting $$ for a reduction for DeclList ore reading
 * $n which corresponds to a DeclList nonterminal we are accessing the field
 * of the union named "declList" which is of type List<Decl*>.
 * pp2: You'll need to add many of these of your own.
 */
%type <declList> DeclList Fields Prototypes
%type <decl> Decl Field Prototype
%type <varDecl> VariableDecl Variable
%type <classDecl> ClassDecl
%type <interfaceDecl> InterfaceDecl
%type <identifierNode> Identifier
%type <fnDecl> FunctionSignature FunctionDecl
%type <stmt> StmtBlock Stmt BreakStmt ReturnStmt WhileStmt
%type <stmt> ForStmt PrintStmt SemicolonTerminatedStmt IfStmt SwitchStmt
%type <caseStmtList> CaseStmts
%type <defaultStmt> DefaultStmt

%type <caseStmt> CaseStmt
%type <stmtList> Stmts
%type <type> Type
%type <expr> ExprOptional Expr LValue Constant Call
%type <namedType> Extends
%type <varDeclList> VarDecls Formals FormalsOptional
%type <namedTypeList> Implements ImplementsOptional
%type <exprList> ExprList ActualsOptional Actuals;

%%
/* Rules
 * -----
 * All productions and actions should be placed between the start and stop
 * %% markers which delimit the Rules section.

 */
Program : DeclList {
  Program *program = new Program($1);
  if (ReportError::NumErrors() == 0) {
    switch(getTestType()) {
    case SyntaxTest:
      program->Print(0);
      break;
    case ScopeTest:
    default:
      program->analyze();
      break;
    }
  }
 }
;

DeclList
: DeclList Decl { ($$=$1)->Append($2); }
| Decl { ($$ = new List<Decl*>)->Append($1); }
;

Decl
: VariableDecl { $$ = $1; }
| FunctionDecl { $$ = $1; }
| ClassDecl { $$ = $1; }
| InterfaceDecl { $$ = $1; }
;

VariableDecl
: Variable ';' { $$ = $1; }
;

Variable
: Type Identifier { $$ = new VarDecl($2, $1);  }
;

Identifier
: T_Identifier { $$ = new Identifier(@1, strdup($1)); }
;

ClassDecl
: T_Class Identifier Extends ImplementsOptional '{' Fields '}' {
  $$ = new ClassDecl($2, $3, $4, $6); }
| T_Class Identifier Extends ImplementsOptional '{' '}' {
  $$ = new ClassDecl($2, $3, $4, new List<Decl*>); }
;

Fields
: Fields Field { ($$=$1)->Append($2); }
| Field { ($$ = new List<Decl*>)->Append($1); }
;

Field
: VariableDecl { $$ = $1; }
| FunctionDecl { $$ = $1; }
;

Extends
: T_Extends Identifier { $$ = new NamedType($2); }
| {$$ = NULL; }
;

ImplementsOptional
: T_Implements Implements { $$ = $2; }
| { $$ = new List<NamedType*>; }
;

Implements
: Identifier { ($$=new List<NamedType*>)->Append(new NamedType($1)); }
| Implements ',' Identifier {($$=$1)->Append(new NamedType($3)); }
;

InterfaceDecl
: T_Interface Identifier '{' Prototypes '}' { $$ = new InterfaceDecl($2, $4); }
| T_Interface Identifier '{' '}' { $$ = new InterfaceDecl($2, new List<Decl*>); }
;

Prototypes
: Prototypes Prototype { ($$=$1)->Append($2); }
| Prototype { ($$ = new List<Decl*>)->Append($1); }
;

Prototype
: FunctionSignature ';' { $$ = $1; }
;

FunctionDecl
: FunctionSignature StmtBlock { ($$=$1)->SetFunctionBody($2); }
;

FunctionSignature
: Type Identifier '(' FormalsOptional ')' { $$ = new FnDecl($2, $1, $4); }
| T_Void Identifier '(' FormalsOptional ')' { $$ = new FnDecl($2, Type::voidType, $4); }
;

FormalsOptional
: Formals { $$ = $1; }
| { $$ = new List<VarDecl*>; }
;

Formals
: Variable { ($$=new List<VarDecl*>)->Append($1); }
| Formals ',' Variable { ($$=$1)->Append($3); }
;

StmtBlock
: '{' VarDecls Stmts '}' { $$ = new StmtBlock($2, $3); }
| '{' Stmts '}' { $$ = new StmtBlock(new List<VarDecl*>, $2); }
| '{' VarDecls '}' { $$ = new StmtBlock($2, new List<Stmt*>); }
| '{' '}' { $$ = new StmtBlock(new List<VarDecl*>, new List<Stmt*>); }
;

VarDecls
: VarDecls VariableDecl { ($$=$1)->Append($2); }
| VariableDecl { ($$ = new List<VarDecl*>)->Append($1); }
;

Stmts
: Stmts Stmt { ($$=$1)->Append($2); }
| Stmt { ($$ = new List<Stmt*>)->Append($1); }
;

Stmt
: SemicolonTerminatedStmt ';' { $$ = $1; }
| IfStmt { $$ = $1; }
| WhileStmt { $$ = $1; }
| ForStmt { $$ = $1; }
| SwitchStmt { $$ = $1; }
| StmtBlock { $$ = $1; }
;

SemicolonTerminatedStmt
: BreakStmt { $$ = $1; }
| ReturnStmt {$$ = $1;}
| PrintStmt { $$ = $1; }
| ExprOptional { $$ = $1; }
;

IfStmt
: T_If '(' Expr ')' Stmt %prec P_NoElse { $$ = new IfStmt($3, $5, NULL); }
| T_If '(' Expr ')' Stmt T_Else Stmt { $$ = new IfStmt($3, $5, $7); }
;

BreakStmt
: T_Break { $$ = new BreakStmt(@1); }
;

ReturnStmt
: T_Return ExprOptional { $$ = new ReturnStmt(@1, $2); }
;

WhileStmt
: T_While '(' Expr ')' Stmt { $$ = new WhileStmt($3, $5); }
;

ForStmt
: T_For '(' ExprOptional ';' Expr ';' ExprOptional ')' Stmt { $$ = new ForStmt($3, $5, $7, $9); }
;

SwitchStmt
: T_Switch '(' Expr ')' '{' CaseStmts DefaultStmt '}' { $$ = new SwitchStmt(@1, $3, $6, $7); }
;

CaseStmts
: CaseStmts CaseStmt { ($$=$1)->Append($2); }
| CaseStmt { ($$ = new List<CaseStmt*>)->Append($1); }
;

CaseStmt
: T_Case T_IntConstant ':' Stmts %prec P_CaseMatchedStmt { $$ = new CaseStmt(@1, new IntConstant(@2, $2), $4); }
| T_Case T_IntConstant ':' %prec P_CaseEmpty { $$ = new CaseStmt(@1, new IntConstant(@2, $2), new List<Stmt*>); }
;

DefaultStmt
: T_Default ':' Stmts %prec P_DefaultMatchedStmt { $$ = new DefaultStmt(@1, $3); }
| T_Default ':' %prec P_DefaultEmpty { $$ = new DefaultStmt(@1, new List<Stmt*>); }
| { $$ = NULL; }
;

PrintStmt
: T_Print '(' ExprList ')' { $$ = new PrintStmt($3); }
;

ExprList
: Expr { ($$=new List<Expr*>)->Append($1); }
| ExprList ',' Expr { ($$=$1)->Append($3); }
;

Type
: T_Int { $$ = Type::intType; }
| T_Double { $$ = Type::doubleType; }
| T_String { $$ = Type::stringType; }
| T_Bool { $$ = Type::boolType; }
| Identifier { $$ = new NamedType($1); }
| Type T_Dims { $$ = new ArrayType(Join(@1, @2), $1); }
;

ExprOptional
: Expr { $$ = $1; }
| { $$ = new EmptyExpr(); }
;

Expr
: LValue '=' Expr { $$ = new AssignExpr($1, makeOp(@2, "="), $3); }
| LValue { $$ = $1; }
| Expr '+' Expr { $$ = new ArithmeticExpr($1, makeOp(@2, "+"), $3); }
| Expr '-' Expr { $$ = new ArithmeticExpr($1, makeOp(@2, "-"), $3); }
| Expr '*' Expr { $$ = new ArithmeticExpr($1, makeOp(@2, "*"), $3); }
| Expr '/' Expr { $$ = new ArithmeticExpr($1, makeOp(@2, "/"), $3); }
| Expr '%' Expr { $$ = new ArithmeticExpr($1, makeOp(@2, "%"), $3); }
| Expr '<' Expr { $$ = new RelationalExpr($1, makeOp(@2, "<"), $3); }
| Expr '>' Expr { $$ = new RelationalExpr($1, makeOp(@2, ">"), $3); }
| Expr T_LessEqual Expr { $$ = new RelationalExpr($1, makeOp(@2, "<="), $3); }
| Expr T_GreaterEqual Expr { $$ = new RelationalExpr($1, makeOp(@2, ">="), $3); }
| Expr T_Equal Expr { $$ = new EqualityExpr($1, makeOp(@2, "=="), $3); }
| Expr T_NotEqual Expr { $$ = new EqualityExpr($1, makeOp(@2, "!="), $3); }
| Expr T_Or Expr { $$ = new LogicalExpr($1, makeOp(@2, "||"), $3); }
| Expr T_And Expr { $$ = new LogicalExpr($1, makeOp(@2, "&&"), $3); }
| '!' Expr { $$ = new LogicalExpr(makeOp(@1, "!"), $2); }
| '-' Expr %prec P_UnaryMinus { $$ = new ArithmeticExpr(makeOp(@1, "-"), $2); }
| Expr T_Incr { $$ = new PostfixExpr($1, makeOp(@2, "++")); }
| Expr T_Decr { $$ = new PostfixExpr($1, makeOp(@2, "--")); }
| Constant { $$ = $1; }
| T_This { $$ = new This(@1); }
| T_ReadInteger '(' ')' { $$ = new ReadIntegerExpr(Join(@1, @3)); }
| T_ReadLine '(' ')' { $$ = new ReadLineExpr(Join(@1, @3)); }
| T_New '(' Identifier ')' { $$ = new NewExpr(Join(@1, @4), new NamedType($3)); }
| Call { $$ = $1; }
| T_NewArray '(' Expr ',' Type ')' { $$ = new NewArrayExpr(Join(@1, @6), $3, $5); }
| '(' Expr ')' { $$ = $2; }
;

LValue
: Identifier { $$ = new FieldAccess(NULL, $1); }
| Expr '.' Identifier { $$ = new FieldAccess($1, $3); }
| Expr '[' Expr ']' { $$ = new ArrayAccess(Join(@1, @4), $1, $3); }
;

Call
: Identifier '(' ActualsOptional ')' { $$ = new Call(Join(@1, @4), NULL, $1, $3); }
| Expr '.' Identifier '(' ActualsOptional ')' { $$ = new Call(Join(@1, @6), $1, $3, $5); }
;

ActualsOptional
: Actuals { $$ = $1; }
| { $$ = new List<Expr*>; }
;

Actuals
: Expr { ($$=new List<Expr*>)->Append($1); }
| Actuals ',' Expr { ($$=$1)->Append($3); }
;

Constant
: T_IntConstant { $$ = new IntConstant(@1, $1); }
| T_DoubleConstant { $$ = new DoubleConstant(@1, $1); }
| T_StringConstant { $$ = new StringConstant(@1, $1); }
| T_BoolConstant { $$ = new BoolConstant(@1, $1); }
| T_Null { $$ = new NullConstant(@1); }
;

%%

/* The closing %% above marks the end of the Rules section and the beginning
 * of the User Subroutines section. All text from here to the end of the
 * file is copied verbatim to the end of the generated y.tab.c file.
 * This section is where you put definitions of helper functions.
 */

/* Function: InitParser
 * --------------------
 * This function will be called before any calls to yyparse().  It is designed
 * to give you an opportunity to do anything that must be done to initialize
 * the parser (set global variables, configure starting state, etc.). One
 * thing it already does for you is assign the value of the global variable
 * yydebug that controls whether yacc prints debugging information about
 * parser actions (shift/reduce) and contents of state stack during parser.
 * If set to false, no information is printed. Setting it to true will give
 * you a running trail that might be helpful when debugging your parser.
 * Please be sure the variable is set to false when submitting your final
 * version.
 */
void InitParser()
{
  PrintDebug("parser", "Initializing parser");
  yydebug = false;
}
Operator* makeOp(yyltype loc, const char* str) {
  return new Operator(loc, str);
}

parser grammar DLParser;

aryOp :
    PLUS_OPERATOR
    | MINUS_OPERATOR
    | MULT_OPERATOR
    | DIV_OPERATOR
    | MOD_OPERATOR
    | ASSIGN_OPERATOR
    | EQUAL_OPERATOR
    | LOGICAL_AND_OPERATOR
    | LOGICAL_OR_OPERATOR
;

expressionList :
    (expressionStatement (',' expressionStatement)*)?
;

expressionStatement :
    blockExpression
    | unblockExpression
;


blockExpression :
    OPEN_CURLY_SYMBOL statements CLOSE_CURLY_SYMBOL
    | OPEN_CURLY_SYMBOL CLOSE_CURLY_SYMBOL
;

unblockExpression :
    unblockExpression op=(MULT_OPERATOR | DIV_OPERATOR) unblockExpression
    | unblockExpression op=(PLUS_OPERATOR | MINUS_OPERATOR) unblockExpression
    | QUOTED_STRING
    | unblockExpression OPEN_PAR_SYMBOL expressionList CLOSE_PAR_SYMBOL
    | CONST
    | IDENTIFIER
;

tupleType :
    OPEN_PAR_SYMBOL CLOSE_PAR_SYMBOL
;

type :
    tupleType
    | IDENTIFIER
;

variableDecl :
    LET_SYMBOL IDENTIFIER COLON_SYMBOL type
    | LET_SYMBOL IDENTIFIER COLON_SYMBOL type EQUAL_OPERATOR expressionStatement
;

param :
    IDENTIFIER COLON_SYMBOL type
;

paramList :
    (param (',' param)*)?
;

functionDecl :
    FUN_SYMBOL IDENTIFIER OPEN_PAR_SYMBOL paramList CLOSE_PAR_SYMBOL JSON_SEPARATOR_SYMBOL type blockExpression
;

decl :
    functionDecl
    | variableDecl
;

comOP :
    ASSIGN_OPERATOR
    | EQUAL_OPERATOR
    | GREATER_OR_EQUAL_OPERATOR
    | GREATER_THAN_OPERATOR
    | LESS_OR_EQUAL_OPERATOR
    | LESS_THAN_OPERATOR
    | NOT_EQUAL_OPERATOR
    | NOT_EQUAL2_OPERATOR
;


condition :
    unblockExpression op=(EQUAL_OPERATOR | NOT_EQUAL_OPERATOR) unblockExpression
    | unblockExpression 
;


conditionElem :
    expressionStatement
    | expressionStatement ELSE_SYMBOL conditionElem
    | expressionStatement ELSE_IF_SYMBOL  OPEN_PAR_SYMBOL condition CLOSE_PAR_SYMBOL conditionElem
;

conditionStmt : 
    IF_SYMBOL OPEN_PAR_SYMBOL condition CLOSE_PAR_SYMBOL conditionElem
;

statement :
    decl
    | expressionStatement
    | conditionStmt
/*
    | whileStmt
    | doWhileStmt
    | forStmt
    | assisgnStmt
    | callReturnStmt
    | callNoReturnStmt
    | returnStmt
*/
    | SEMICOLON_SYMBOL
;

statements :
    statement SEMICOLON_SYMBOL
    | statement SEMICOLON_SYMBOL statements
;

module :
    statements EOF
;

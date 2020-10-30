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

whileStmt : 
    WHILE_SYMBOL '(' CONDITION ')'



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


statement :
    decl
    | expressionStatement
    | conditionStmt
    | whileStmt
    | doWhileStmt
    | forStmt
    | assisgnStmt
    | callReturnStmt
    | callNoReturnStmt
    | returnStmt
    | SEMICOLON_SYMBOL
;

statements :
    statement SEMICOLON_SYMBOL
    | statement SEMICOLON_SYMBOL statements
;

module :
    statements EOF
;

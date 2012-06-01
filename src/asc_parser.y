%token INTEGER PLUS MINUS NEWLINE

%%
program:
    program expression NEWLINE
    |
    ;

expression:
    INTEGER
    | expression PLUS expression
    | expression MINUS expression
    ;

%%

int main()
{
    yyparse();
}

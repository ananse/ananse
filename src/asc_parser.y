%token IDENTIFIER PLUS MINUS NUMBER NEWLINE TIMES DIVIDES EQUALS
%token OPEN_BRACKET CLOSE_BRACKET

%{
    #include <stdio.h>
%}

%%
program:    statement NEWLINE
    |       program statement NEWLINE

statement:  assignment 
    ;

assignment: IDENTIFIER EQUALS expression { printf("assignment %d", $3); }

expression: expression PLUS multiply_expression  {$$ = $1 + $3;}
    |       expression MINUS multiply_expression   {$$ = $1 - $3;}
    |       multiply_expression              {$$ = $1;}
    ;

multiply_expression:    multiply_expression TIMES primary { $$ = $1 * $3; }
    |                   multiply_expression DIVIDES primary { $$ = $1 / $3; }
    |                   primary {$$ = $1;}
    ;

primary :   OPEN_BRACKET expression CLOSE_BRACKET {$$ = $2;}
    |       NUMBER                                  {$$ = $1;}
    ;
    

%%

int main()
{
    yyparse();
}

%token IDENTIFIER PLUS NUMBER NEWLINE

%{
    #include <stdio.h>
%}

%%
program:    statement NEWLINE
    |       program statement NEWLINE

statement:  expression { printf("%d", $1); }
    ;

expression: NUMBER PLUS NUMBER  {$$ = $1 + $3;}
    |       NUMBER '-' NUMBER   {$$ = $1 - $3;}
    |       NUMBER              {$$ = $1;}
    ;
%%

int main()
{
    yyparse();
}

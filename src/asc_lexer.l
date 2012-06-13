digit       [0-9]
plus        \+
minus       -
multiply    *
period      .
newline     \n
%{
    #include "asc_parser.h"
    extern int yylval;
%}

%%
[ \t]       ; /* ignore white spaces */
{digit}+    {yylval = atoi(yytext); return NUMBER;}
{plus}      { return PLUS; }
{newline}   { return NEWLINE; }
%%

int yywrap()
{
    return 1;
}

int yyerror()
{

}

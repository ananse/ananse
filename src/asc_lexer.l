digit           [0-9]
plus            \+
minus           -
times           \*
divides         \/
period          \.
newline         \n
open_bracket    \(
close_bracket   \)
equal_sign      =
%{
    #include "asc_parser.h"
    extern int yylval;
%}

%%
[ \t]       ; /* ignore white spaces */
{digit}+        {yylval = atoi(yytext); return NUMBER;}
{plus}          { return PLUS; }
{minus}         { return MINUS; }
{newline}       { return NEWLINE; }
{times}         { return TIMES; }
{divides}       { return DIVIDES; }
{open_bracket}  { return OPEN_BRACKET; }
{close_bracket} { return CLOSE_BRACKET; }
{equal_sign}    { return EQUALS; }
[a-zA-Z_][a-zA-Z0-9_\.]*    { return IDENTIFIER; }
%%

int yywrap()
{
    return 1;
}

int yyerror()
{

}

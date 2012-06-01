digit       [0-9]
plus        +
minus       -
multiply    *

%%
{digit}     printf("digit");
%%

int yywrap()
{
    return 1;
}

int yyerror()
{

}

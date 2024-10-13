%{
#include <stdio.h>
#include <string.h>
%}

%%
abc             { printf("ABC"); }
[[:alpha:]]+    { printf("%s", yytext); }
[[:space:]]+    { printf("%s", yytext); }
.               { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

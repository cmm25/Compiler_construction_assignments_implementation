%{
#include <stdio.h>
int wordCount = 0;
int totalSize = 0;
%}

%%

[a-zA-Z]+              { wordCount++;  totalSize  += yyleng; }  
[a-zA-Z]+[-'][a-zA-Z]+ { wordCount++;  totalSize  += yyleng; }  
.|\n                   {  totalSize ++; }                       

%%

int main() {
    yylex();
    printf("Total word count: %d\n", wordCount);
    printf("Total character count: %d\n",  totalSize );
    return 0;
}

int yywrap() {
    return 1;
}

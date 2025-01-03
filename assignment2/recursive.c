#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

char *expr;  // Points to the input expression
int token;   // Current token

int getToken(void);
int term(void);
int factor(void);
int expression(void);

int getToken(void) {
    while (*expr == ' ') expr++;  
    token = *expr++;
    return token;
}

// Handle expressions: expression -> term | term + expression
int expression(void) {
    int temp = term();
    
    while (token == '+') {
        getToken();
        temp += term();
    }
    return temp;
}

// Handle terms: term -> factor | factor * term
int term(void) {
    int temp = factor();
    
    while (token == '*') {
        getToken();
        temp *= factor();
    }
    return temp;
}

// Handle factors: factor -> digit | (expression)
int factor(void) {
    int temp = 0;
    
    if (isdigit(token)) {
        do {
            temp = temp * 10 + (token - '0');
            getToken();
        } while (isdigit(token));
    }
    else if (token == '(') {
        getToken();
        temp = expression();
        if (token != ')') {
            printf("Error: Missing closing parenthesis\n");
            exit(1);
        }
        getToken();
    }
    else {
        printf("Error: Expected number or '('\n");
    }
    return temp;
}

int main() {
    char input_expr[100];
    int result;
    
    printf("Enter arithmetic expression (digits, +, *, and parentheses): ");
    fgets(input_expr, sizeof(input_expr), stdin);
    
    // Remove newline if present
    for (int i = 0; input_expr[i]; i++) {
        if (input_expr[i] == '\n') {
            input_expr[i] = '\0';
            break;
        }
    }
    
    expr = input_expr;
    getToken();
    result = expression();
    
    if (token != '\0' && token != '\n') {
        printf("Error: Unexpected characters after expression\n");
        return 1;
    }
    
    printf("Result = %d\n", result);
    return 0;
}
#include <stdio.h>
#include <string.h>

#define MAX 100

char stack[MAX];
int top = -1;


void push(char c) {
    stack[++top] = c;
}


char pop() {
    if (top == -1)
        return '\0';
    return stack[top--];
}


int isMatchingPair(char open, char close) {
    if (open == '(' && close == ')') return 1;
    if (open == '{' && close == '}') return 1;
    if (open == '[' && close == ']') return 1;
    return 0;
}


int isBalanced(char exp[]) {
    for (int i = 0; i < strlen(exp); i++) {
        char ch = exp[i];

        
        if (ch == '(' || ch == '{' || ch == '[') {
            push(ch);
        }
        
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (top == -1)    
                return 0;

            char popped = pop();
            if (!isMatchingPair(popped, ch))
                return 0;
        }
    }

    
    return (top == -1);
}

int main() {
    char expression[MAX];

    printf("Enter an expression: ");
    scanf("%s", expression);

    if (isBalanced(expression))
        printf("Parentheses are Balanced\n");
    else
        printf("Parentheses are NOT Balanced\n");

    return 0;
}

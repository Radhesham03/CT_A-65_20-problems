#include <stdio.h>
#define MAX 10

int arr[MAX];
int top1 = -1;
int top2 = MAX;


void push1(int x) {
    if (top1 + 1 == top2) {
        printf("Stack Overflow!\n");
        return;
    }
    arr[++top1] = x;
    printf("%d pushed to Stack1\n", x);
}


void push2(int x) {
    if (top1 + 1 == top2) {
        printf("Stack Overflow!\n");
        return;
    }
    arr[--top2] = x;
    printf("%d pushed to Stack2\n", x);
}

void pop1() {
    if (top1 == -1) {
        printf("Stack1 Underflow!\n");
        return;
    }
    printf("%d popped from Stack1\n", arr[top1--]);
}


void pop2() {
    if (top2 == MAX) {
        printf("Stack2 Underflow!\n");
        return;
    }
    printf("%d popped from Stack2\n", arr[top2++]);
}


void display() {
    printf("\nStack1: ");
    for (int i = top1; i >= 0; i--) {
        printf("%d ", arr[i]);
    }

    printf("\nStack2: ");
    for (int i = top2; i < MAX; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    push1(10);
    push1(20);
    push2(5);
    push2(15);
    display();

    pop1();
    pop2();
    display();

    return 0;
}

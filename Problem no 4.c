#include <stdio.h>
#define MAX 10

int arr[MAX];


int front1 = -1, rear1 = -1;


int front2 = MAX, rear2 = MAX;


void enqueue1(int x) {
    if (rear1 + 1 == rear2) {
        printf("Queue1 Overflow!\n");
        return;
    }

    if (front1 == -1) 
        front1 = 0;

    arr[++rear1] = x;
    printf("%d inserted in Queue1\n", x);
}


void enqueue2(int x) {
    if (rear1 + 1 == rear2) {
        printf("Queue2 Overflow!\n");
        return;
    }

    if (front2 == MAX)
        front2 = MAX - 1;

    arr[--rear2] = x;
    printf("%d inserted in Queue2\n", x);
}


void dequeue1() {
    if (front1 == -1 || front1 > rear1) {
        printf("Queue1 Underflow!\n");
        return;
    }

    printf("%d removed from Queue1\n", arr[front1++]);

    if (front1 > rear1)
        front1 = rear1 = -1;
}


void dequeue2() {
    if (front2 == MAX || front2 < rear2) {
        printf("Queue2 Underflow!\n");
        return;
    }

    printf("%d removed from Queue2\n", arr[front2--]);

    if (front2 < rear2)
        front2 = rear2 = MAX;
}


void display() {
    printf("\nQueue1: ");
    if (front1 == -1)
        printf("Empty");
    else {
        for (int i = front1; i <= rear1; i++)
            printf("%d ", arr[i]);
    }

    printf("\nQueue2: ");
    if (front2 == MAX)
        printf("Empty");
    else {
        for (int i = front2; i >= rear2; i--)
            printf("%d ", arr[i]);
    }

    printf("\n");
}

int main() {
    enqueue1(10);
    enqueue1(20);
    enqueue2(5);
    enqueue2(15);

    display();

    dequeue1();
    dequeue2();

    display();
    return 0;
}

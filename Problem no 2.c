#include <stdio.h>
#define MAX 5   

int queue[MAX];
int front = -1, rear = -1;


void enqueue(int x) {
    if (rear == MAX - 1) {
        printf("Queue Overflow! Cannot insert %d\n", x);
    } else {
        if (front == -1)  
            front = 0;
        rear++;
        queue[rear] = x;
        printf("%d inserted into queue\n", x);
    }
}


void dequeue() {
    if (front == -1 || front > rear) {
        printf("Queue Underflow! Nothing to delete\n");
    } else {
        printf("%d deleted from queue\n", queue[front]);
        front++;
    }
}


void display() {
    if (front == -1 || front > rear) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements are: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

int main() {
    int choice, value;

    while (1) {
        printf("\n--- Queue Menu ---\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to insert: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }
}

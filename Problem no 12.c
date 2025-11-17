#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

/************ INSERTION ************/

void insertAtBeg(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;
}

void insertAtPos(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insertAtBeg(head, data);
        return;
    }

    struct Node* newNode = createNode(data);
    struct Node* temp = *head;
    int i;

    for (i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

/************ DELETION ************/

void deleteBeg(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    *head = (*head)->next;
    free(temp);
}

void deleteEnd(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    struct Node* prev = NULL;

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == NULL)
        *head = NULL;  // only one node
    else
        prev->next = NULL;

    free(temp);
}

void deletePos(struct Node** head, int pos) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    if (pos == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    struct Node* prev = NULL;
    int i;
    for (i = 1; temp != NULL && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

/************ DISPLAY ************/

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/************ REVERSE ************/

void reverse(struct Node** head) {
    struct Node *prev = NULL, *next = NULL, *curr = *head;

    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *head = prev;
}

/************ FIND MIDDLE ************/

struct Node* findMiddle(struct Node* head) {
    if (!head) return NULL;

    struct Node *slow = head, *fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

/************ SORT (Ascending) ************/

void sortList(struct Node* head) {
    struct Node *i, *j;
    int temp;

    for (i = head; i != NULL; i = i->next)
        for (j = i->next; j != NULL; j = j->next)
            if (i->data > j->data) {
                temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
}

/************ DETECT LOOP ************/

int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast)
            return 1;  // loop exists
    }
    return 0;
}

/************ MERGE TWO SORTED LISTS ************/

struct Node* merge(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = merge(a->next, b);
        return a;
    } else {
        b->next = merge(a, b->next);
        return b;
    }
}

/************ SUM OF ALL DATA ************/

int sumList(struct Node* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

/************ PRINT ODD & EVEN DATA ************/

void printOddEven(struct Node* head) {
    struct Node* temp = head;

    printf("Even data: ");
    while (temp) {
        if (temp->data % 2 == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    temp = head;
    printf("\nOdd data: ");
    while (temp) {
        if (temp->data % 2 != 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\n");
}

/************ MAIN MENU ************/

int main() {
    struct Node* head = NULL;
    int choice, data, pos;

    while (1) {
        printf("\n----- LINKED LIST MENU -----\n");
        printf("1. Insert at Beginning\n");
        printf("2. Insert at End\n");
        printf("3. Insert at Position\n");
        printf("4. Delete at Beginning\n");
        printf("5. Delete at End\n");
        printf("6. Delete at Position\n");
        printf("7. Display\n");
        printf("8. Reverse\n");
        printf("9. Find Middle\n");
        printf("10. Sort List\n");
        printf("11. Detect Loop\n");
        printf("12. Sum of Data\n");
        printf("13. Print Odd & Even\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtBeg(&head, data);
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;

            case 3:
                printf("Enter data and position: ");
                scanf("%d %d", &data, &pos);
                insertAtPos(&head, data, pos);
                break;

            case 4:
                deleteBeg(&head);
                break;

            case 5:
                deleteEnd(&head);
                break;

            case 6:
                printf("Enter position: ");
                scanf("%d", &pos);
                deletePos(&head, pos);
                break;

            case 7:
                display(head);
                break;

            case 8:
                reverse(&head);
                break;

            case 9: {
                struct Node* mid = findMiddle(head);
                if (mid)
                    printf("Middle element: %d\n", mid->data);
                break;
            }

            case 10:
                sortList(head);
                break;

            case 11:
                if (detectLoop(head))
                    printf("Loop detected!\n");
                else
                    printf("No loop.\n");
                break;

            case 12:
                printf("Sum = %d\n", sumList(head));
                break;

            case 13:
                printOddEven(head);
                break;

            case 0:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}

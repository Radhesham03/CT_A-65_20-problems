#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Create new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

/*************** INSERTION *****************/

void insertAtBeg(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head != NULL) {
        newNode->next = *head;
        (*head)->prev = newNode;
    }

    *head = newNode;
}

void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    struct Node* temp = *head;
    while (temp->next != NULL) temp = temp->next;

    temp->next = newNode;
    newNode->prev = temp;
}

void insertAtPos(struct Node** head, int data, int pos) {
    if (pos == 1) {
        insertAtBeg(head, data);
        return;
    }

    struct Node* temp = *head;
    struct Node* newNode = createNode(data);
    int i;

    for (i = 1; temp != NULL && i < pos - 1; i++)
        temp = temp->next;

    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    newNode->prev = temp;

    if (temp->next != NULL)
        temp->next->prev = newNode;

    temp->next = newNode;
}

/**************** DELETION ****************/

void deleteBeg(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    *head = temp->next;

    if (*head != NULL)
        (*head)->prev = NULL;

    free(temp);
}

void deleteEnd(struct Node** head) {
    if (*head == NULL) return;

    struct Node* temp = *head;

    while (temp->next != NULL)
        temp = temp->next;

    if (temp->prev == NULL) {  
        *head = NULL;          
    } else {
        temp->prev->next = NULL;
    }

    free(temp);
}

void deletePos(struct Node** head, int pos) {
    if (*head == NULL) return;

    struct Node* temp = *head;
    int i;

    if (pos == 1) {
        deleteBeg(head);
        return;
    }

    for (i = 1; temp != NULL && i < pos; i++)
        temp = temp->next;

    if (temp == NULL) return;

    if (temp->prev) temp->prev->next = temp->next;
    if (temp->next) temp->next->prev = temp->prev;

    free(temp);
}

/*************** DISPLAY ***************/

void display(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

/*************** REVERSE ***************/

void reverse(struct Node** head) {
    struct Node *curr = *head, *temp = NULL;

    while (curr != NULL) {
        temp = curr->prev;
        curr->prev = curr->next;
        curr->next = temp;
        curr = curr->prev;
    }

    if (temp != NULL)
        *head = temp->prev;
}

/*************** FIND MIDDLE ***************/

struct Node* findMiddle(struct Node* head) {
    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

/*************** SORT LIST ***************/

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

/*************** DETECT LOOP ***************/

int detectLoop(struct Node* head) {
    struct Node *slow = head, *fast = head;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast)
            return 1;
    }
    return 0;
}

/*************** SUM OF DATA ***************/

int sumList(struct Node* head) {
    int sum = 0;
    while (head) {
        sum += head->data;
        head = head->next;
    }
    return sum;
}

/*************** PRINT ODD & EVEN ***************/

void printOddEven(struct Node* head) {
    printf("Even: ");
    struct Node* temp = head;
    while (temp) {
        if (temp->data % 2 == 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }

    printf("\nOdd: ");
    temp = head;
    while (temp) {
        if (temp->data % 2 != 0)
            printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

/*************** MERGE TWO SORTED DLL ***************/

struct Node* merge(struct Node* a, struct Node* b) {
    if (!a) return b;
    if (!b) return a;

    if (a->data <= b->data) {
        a->next = merge(a->next, b);
        if (a->next) a->next->prev = a;
        return a;
    } else {
        b->next = merge(a, b->next);
        if (b->next) b->next->prev = b;
        return b;
    }
}

/**************** MENU ****************/

int main() {
    struct Node* head = NULL;
    int choice, data, pos;

    while (1) {
        printf("\n---- DOUBLY LINKED LIST MENU ----\n");
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
                printf("Enter data & position: ");
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
                if (mid) printf("Middle Element: %d\n", mid->data);
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
                printf("Sum of nodes = %d\n", sumList(head));
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

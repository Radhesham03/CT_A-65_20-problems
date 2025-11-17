#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left, *right;
};

/**************** CREATE NODE *****************/

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

/**************** INSERT INTO BST *****************/

struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);

    return root;
}

/**************** TRAVERSALS *****************/

void inorder(struct Node* root) {
    if (!root) return;
    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void preorder(struct Node* root) {
    if (!root) return;
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void postorder(struct Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

/**************** BFS (LEVEL ORDER) *****************/

void BFS(struct Node* root) {
    if (!root) return;

    struct Node* queue[100];
    int front = 0, rear = 0;

    queue[rear++] = root;

    while (front < rear) {
        struct Node* temp = queue[front++];
        printf("%d ", temp->data);

        if (temp->left)
            queue[rear++] = temp->left;
        if (temp->right)
            queue[rear++] = temp->right;
    }
}

/**************** DFS *****************/

void DFS(struct Node* root) {
    preorder(root);   // preorder = DFS
}

/**************** MIRROR TREE *****************/

struct Node* mirror(struct Node* root) {
    if (root == NULL) return root;

    struct Node* temp = root->left;
    root->left = root->right;
    root->right = temp;

    mirror(root->left);
    mirror(root->right);

    return root;
}

/**************** FIND PARENT OF A NODE *****************/

struct Node* parent(struct Node* root, int key) {
    if (!root || root->data == key)
        return NULL;

    if ((root->left && root->left->data == key) ||
        (root->right && root->right->data == key))
        return root;

    if (key < root->data)
        return parent(root->left, key);
    else
        return parent(root->right, key);
}

/**************** FIND CHILDREN *****************/

void children(struct Node* root, int key) {
    struct Node* p = root;

    while (p != NULL) {
        if (p->data == key) {
            if (p->left) printf("Left child: %d\n", p->left->data);
            else printf("Left child: NULL\n");

            if (p->right) printf("Right child: %d\n", p->right->data);
            else printf("Right child: NULL\n");
            return;
        }
        else if (key < p->data)
            p = p->left;
        else
            p = p->right;
    }
    printf("Node not found.\n");
}

/**************** FIND SIBLING *****************/

void sibling(struct Node* root, int key) {
    struct Node* p = parent(root, key);

    if (!p) {
        printf("No sibling (root or node not found).\n");
        return;
    }

    if (p->left && p->left->data == key && p->right)
        printf("Sibling: %d\n", p->right->data);
    else if (p->right && p->right->data == key && p->left)
        printf("Sibling: %d\n", p->left->data);
    else
        printf("No sibling.\n");
}

/**************** GRANDPARENT *****************/

struct Node* grandParent(struct Node* root, int key) {
    struct Node* p = parent(root, key);
    if (!p) return NULL;
    return parent(root, p->data);
}

/**************** UNCLE *****************/

struct Node* uncle(struct Node* root, int key) {
    struct Node* gp = grandParent(root, key);
    if (!gp) return NULL;

    struct Node* p = parent(root, key);

    if (gp->left == p)
        return gp->right;
    else
        return gp->left;
}

/**************** MAIN *****************/

int main() {
    struct Node* root = NULL;
    int choice, data, key;

    while (1) {
        printf("\n----- BST MENU -----\n");
        printf("1. Insert\n");
        printf("2. Inorder\n");
        printf("3. Preorder\n");
        printf("4. Postorder\n");
        printf("5. BFS (Level Order)\n");
        printf("6. DFS\n");
        printf("7. Mirror Tree\n");
        printf("8. Children of Node\n");
        printf("9. Sibling of Node\n");
        printf("10. Parent of Node\n");
        printf("11. Grandparent of Node\n");
        printf("12. Uncle of Node\n");
        printf("0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter value: ");
            scanf("%d", &data);
            root = insert(root, data);
            break;

        case 2:
            inorder(root);
            printf("\n");
            break;

        case 3:
            preorder(root);
            printf("\n");
            break;

        case 4:
            postorder(root);
            printf("\n");
            break;

        case 5:
            BFS(root);
            printf("\n");
            break;

        case 6:
            DFS(root);
            printf("\n");
            break;

        case 7:
            mirror(root);
            printf("Tree mirrored.\n");
            break;

        case 8:
            printf("Enter node: ");
            scanf("%d", &key);
            children(root, key);
            break;

        case 9:
            printf("Enter node: ");
            scanf("%d", &key);
            sibling(root, key);
            break;

        case 10: {
            printf("Enter node: ");
            scanf("%d", &key);
            struct Node* p = parent(root, key);
            if (p) printf("Parent: %d\n", p->data);
            else printf("No parent (root or node not found).\n");
            break;
        }

        case 11: {
            printf("Enter node: ");
            scanf("%d", &key);
            struct Node* gp = grandParent(root, key);
            if (gp) printf("Grandparent: %d\n", gp->data);
            else printf("No grandparent.\n");
            break;
        }

        case 12: {
            printf("Enter node: ");
            scanf("%d", &key);
            struct Node* u = uncle(root, key);
            if (u) printf("Uncle: %d\n", u->data);
            else printf("No uncle found.\n");
            break;
        }

        case 0:
            exit(0);

        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}

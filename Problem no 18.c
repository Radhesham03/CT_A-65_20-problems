#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    int isEndOfWord;
};

struct TrieNode* createNode() {
    struct TrieNode *node = (struct TrieNode*)malloc(sizeof(struct TrieNode));

    node->isEndOfWord = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        node->children[i] = NULL;

    return node;
}

void insert(struct TrieNode *root, char *key) {
    struct TrieNode *crawl = root;

    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a'; 

        if (crawl->children[index] == NULL)
            crawl->children[index] = createNode();

        crawl = crawl->children[index];
    }
    crawl->isEndOfWord = 1;
}

int search(struct TrieNode *root, char *key) {
    struct TrieNode *crawl = root;

    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';

        if (crawl->children[index] == NULL)
            return 0;

        crawl = crawl->children[index];
    }
    return (crawl != NULL && crawl->isEndOfWord);
}

int main() {
    struct TrieNode *root = createNode();

    int n;
    char key[50];

    printf("Enter number of words to insert: ");
    scanf("%d", &n);

    printf("Enter words (lowercase):\n");
    for (int i = 0; i < n; i++) {
        scanf("%s", key);
        insert(root, key);
    }

    printf("\nEnter a word to search: ");
    scanf("%s", key);

    if (search(root, key))
        printf("'%s' found in Trie\n", key);
    else
        printf("'%s' NOT found in Trie\n", key);

    return 0;
}

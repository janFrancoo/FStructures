#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#define ALPHABET_LEN 26

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    bool isEndOfWord;
    struct Node *child[ALPHABET_LEN];
} Node;

Node *getNode() {
    Node *node = malloc(sizeof(Node));
    node->isEndOfWord = FALSE;

    for (int i=0; i<ALPHABET_LEN; i++)
        node->child[i] = NULL;

    return node;
}

int stringLength(char *word) {
    int count = 0;
    while (word[count] != '\0')
        count++;
    return count;
}

int indexOfChar(char c) {
    return (int) c - (int) 'a';
}

void insert(Node *root, char *word) {
    Node *t = root;

    for (int i=0; i<stringLength(word); i++) {
        int idx = indexOfChar(word[i]);
        if (t->child[idx] == NULL)
            t->child[idx] = getNode();
        t = t->child[idx];
    }

    t->isEndOfWord = TRUE;
}

bool search(Node *root, char *word) {
    Node *t = root;

    for (int i=0; i<stringLength(word); i++) {
        int idx = indexOfChar(word[i]);
        if (t->child[idx] == NULL)
            return FALSE;
        t = t->child[idx];
    }

    return t != NULL && t->isEndOfWord == TRUE;
}

void printTrie(Node *node, char word[], int idx) {
    if (node->isEndOfWord == TRUE) {
        word[idx] = '\0';
        printf("%s\n", word);
    }

    for (int i=0; i<ALPHABET_LEN; i++) {
        if (node->child[i] != NULL) {
            word[idx] = i + (int) 'a';
            printTrie(node->child[i], word, idx + 1);
        }
    }
}

void getSuggestions(Node *node, char *word) {
    Node *t = node;

    for (int i=0; i<stringLength(word); i++) {
        int idx = indexOfChar(word[i]);
        if (t->child[idx] == NULL)
            break;
        t = t->child[idx];
    }

    printTrie(t, word, stringLength(word));
}

#endif // TRIE_H_INCLUDED

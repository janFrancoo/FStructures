#ifndef HASH_CHAIN_H_INCLUDED
#define HASH_CHAIN_H_INCLUDED

#define     MAX         25
#define     MAX_DISP    10
#define     TRUE        1
#define     FALSE       0
typedef int bool;

typedef struct {
    int *table;
    int maxLen;
} HashTable;

typedef struct {
    int value;
    struct HNode *next;
} HNode;

void createHashTable_Chain(HashTable **table, int max) {
    if (max == NULL) {
        max = MAX;
    }

    (*table) = malloc(sizeof(HashTable));
    (*table)->maxLen = max;
    (*table)->table = malloc(sizeof(HNode*) * max);

    for (int i=0; i<max; i++) {
        ((*table)->table)[i] = NULL;
    }
}

void insertToTableToLinkedList(HNode **head, int value) {
    HNode *newHNode = malloc(sizeof(HNode));
    newHNode->next = NULL;
    newHNode->value = value;

    if ((*head) == NULL) {
        (*head) = newHNode;
        return;
    }

    HNode *t = (*head);
    while (t->next != NULL)
        t = t->next;

    t->next = newHNode;
}

int hash(int max, int key) {
    return key % max;
}

void insertToTable(HashTable **table, int key, int value) {
    if ((*table) == NULL)
        return;

    HNode *head = NULL;
    int idx = hash((*table)->maxLen, key);

    if ((*table)->table[idx] == NULL) {
        insertToTableToLinkedList(&head, value);
        (*table)->table[idx] = head;
    } else {
        insertToTableToLinkedList(&((*table)->table[idx]), value);
    }
}

void printKey(HashTable *table, int key, int maxDisp) {
    if (maxDisp == NULL)
        maxDisp = MAX_DISP;

    int idx = hash(table->maxLen, key);

    HNode *head = table->table[idx];
    if (head == NULL)
        return;

    displayList(head, maxDisp);
}

bool searchList(HNode *head, int value) {
    HNode *t = head;
    while (t != NULL) {
        if (t->value == value)
            return TRUE;
        t = t->next;
    }
    return FALSE;
}

int searchListIdx(HNode *head, int value) {
    int count = 0;
    HNode *t = head;
    while (t != NULL) {
        if (t->value == value)
            return count;
        t = t->next;
        count++;
    }
    return -1;
}

void displayList(HNode *head, int maxDisp) {
    int i = 0;
    HNode *t = head;
    while (t != NULL && i < maxDisp) {
        printf("%d -> ", t->value);
        t = t->next;
        i++;
    }
    printf("\n");
}

void printTable(HashTable *table, int maxDisp) {
    if (maxDisp == NULL)
        maxDisp = MAX_DISP;

    for (int i=0; i<table->maxLen; i++) {
        HNode *head = table->table[i];
        printf("[%d] --- ", i);
        if (head == NULL)
            printf("~~\n");
        else
            displayList(head, maxDisp);
    }
}

bool searchTable(HashTable *table, int key, int value) {
    int idx = hash(table->maxLen, key);

    if (table->table[idx] == NULL)
        return FALSE;

    return searchList(table->table[idx], value);
}

void removeKey(HashTable **table, int key) {
    int idx = hash((*table)->maxLen, key);
    (*table)->table[idx] = NULL;
}

HNode *removeHNode(HNode *head, int value) {
    HNode *t = head, *prev = head;

    // If list is empty
    if(t == NULL)
        return NULL;

    // If head will be removed
    if(t != NULL && t->value == value) {
        head = head->next;
        free(t);
        return head;
    }

    // Iterate t to the HNode that will be removed
    while(t->next != NULL && t->value != value) {
        prev = t;
        t = t->next;
    }

    // If HNode was found, remove
    if(t->value == value) {
        prev->next = t->next;
        free(t);
    }

    return head;
}

void removeValue(HashTable **table, int key, int value) {
    int idx = hash((*table)->maxLen, key);
    HNode *head = (*table)->table[idx];
    (*table)->table[idx] = removeHNode(head, value);
}

#endif // CHAIN_HASHING_H_INCLUDED

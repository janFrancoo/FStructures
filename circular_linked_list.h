#ifndef CIRCULAR_LINKED_LIST_H_INCLUDED
#define CIRCULAR_LINKED_LIST_H_INCLUDED

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    struct CNode *next;
} CNode;

void insertToCLL (CNode **head, int value) {
    CNode *n = malloc(sizeof(CNode));
    n->value = value;
    n->next = *head;

    if(*head == NULL) {
        n->next = n;
        *head = n;
    }
    else {
        CNode *t = *head;
        while (t->next != *head)
            t = t->next;
        t->next = n;
    }
}

void deleteFromCLL (CNode **head, int value) {
    if (*head == NULL)
        return;

    CNode *t = *head, *prev = *head;

    // If head will be removed
    if((*head)->value == value) {
        while(t->next != *head)
            t = t->next;
        t->next = (*head)->next;
        *head = (*head)->next;
        return;
    }

    // Search the value
    t = t->next;
    while(t != *head && t->value != value) {
        prev = t;
        t = t->next;
    }

    // If value was found, delete
    if(t->value == value) {
        prev->next = t->next;
        free(t);
    }
}

bool searchInCLL (CNode *head, int value) {
    CNode *t = head;
    if (t->value == value)
        return TRUE;

    t = t->next;
    while(t != head) {
        if(t->value == value)
            return TRUE;
        t = t->next;
    }
    return FALSE;
}

void printCLL (CNode *head) {
    CNode *t = head;
    if(t != NULL) {
        printf("%d -> ", t->value);
        t = t->next;
    }
    while(t != head) {
        if(t->next == head) printf("%d -----> *%d", t->value, head->value);
        else                printf("%d -> ", t->value);
        t = t->next;
    }
    printf("\n");
}

#endif // CIRCULAR_LINKED_LIST_H_INCLUDED

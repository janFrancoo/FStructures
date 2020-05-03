#ifndef DOUBLY_LINKED_LIST_H_INCLUDED
#define DOUBLY_LINKED_LIST_H_INCLUDED

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    struct DNode *next;
    struct DNode *prev;
} DNode;

void insertToDLL (DNode **head, int value) {
    DNode *n = malloc(sizeof(DNode));
    n->value = value;
    n->next = NULL;

    if(*head == NULL) {
        n->prev = NULL;
        *head = n;
        return;
    }

    DNode *t = *head;
    while(t->next != NULL)
        t = t->next;

    t->next = n;
    n->prev = t;
}

void deleteFromDLL (DNode **head, int value) {
    DNode *t = *head;

    // If head is null, return
    if(t == NULL)
        return;

    // If head will be removed
    if(t->value == value) {
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(t);
        return;
    }

    // Search DNode
    while(t != NULL && t->value != value)
        t = t->next;

    // If found and it is not the last, remove
    if(t->value == value && t->next != NULL) {
        ((DNode*)(t->prev))->next = t->next;
        ((DNode*)(t->next))->prev = t->prev;
        free(t);
    }
    // If found and it is the last DNode, remove
    else if(t->value == value && t->next == NULL) {
        ((DNode*)(t->prev))->next = NULL;
        free(t);
    }
}

bool searchInDLL (DNode *head, int value) {
    DNode *t = head;
    while(t != NULL) {
        if(t->value == value)
            return TRUE;
        t = t->next;
    }
    return FALSE;
}

void printDLL (DNode *head) {
    DNode *t = head;
    while(t != NULL) {
        if(t->next != NULL) printf("%d -> ", t->value);
        else                printf("%d", t->value);
        t = t->next;
    }
    printf("\n");
}

#endif // DOUBLY_LINKED_LIST_H_INCLUDED

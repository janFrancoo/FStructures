#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#define ADJ_LIST        0
#define ADJ_MATRIX      1
#define DEF_SIZE        10

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    bool isDirected;
    bool isWeighted;
    int representMode;
    int nNode;
    int *graphArr;
} Graph;

typedef struct {
    int data;
    int weight;
    struct Node *next;
} Node;

void createGraph(Graph **graph, bool isDirected, bool isWeighted, int representMode, int nNode) {
    if (isDirected == NULL || (isDirected != FALSE && isDirected != TRUE))
        isDirected = FALSE;

    if (isWeighted == NULL || (isWeighted != FALSE && isWeighted != TRUE))
        isWeighted = FALSE;

    if (representMode == NULL || (representMode != 0 && representMode != 1))
        representMode = ADJ_LIST;

    if (nNode == NULL || nNode < 0)
        nNode = DEF_SIZE;

    (*graph) = malloc(sizeof(Graph));
    (*graph)->isDirected = isDirected;
    (*graph)->isWeighted = isWeighted;
    (*graph)->representMode = representMode;
    (*graph)->nNode = nNode;
    (*graph)->graphArr = malloc(sizeof(int) * nNode);

    if (representMode == ADJ_MATRIX) {
        for (int i=0; i<nNode; i++) {
            (*graph)->graphArr[i] = calloc(nNode, sizeof(int));
            ((int*)(*graph)->graphArr[i])[i] = -1;
        }
    }
    else
        for (int i=0; i<nNode; i++)
            (*graph)->graphArr[i] = NULL;
}

void newConnection(Graph **graph, int node1, int node2, bool allowDuplicate, int weight) {
    if ((*graph) == NULL || node1 < 0 || node1 > (*graph)->nNode
                        || node2 < 0 || node2 > (*graph)->nNode)
        return;

    if ((*graph)->isWeighted == TRUE && weight == NULL)
        return;

    if ((*graph)->isWeighted == FALSE)
        weight = NULL;

    if (allowDuplicate == NULL || (allowDuplicate != FALSE && allowDuplicate != TRUE))
        allowDuplicate = FALSE;

    if ((*graph)->representMode == ADJ_LIST) {
        if ((*graph)->graphArr[node1] == NULL) {
            Node *head = malloc(sizeof(Node));
            head->weight = weight;
            head->data = node2;
            head->next = NULL;
            (*graph)->graphArr[node1] = head;
        }
        else if (allowDuplicate == TRUE)
            insertToLL(&((*graph)->graphArr[node1]), node2, weight);
        else if (checkLL((*graph)->graphArr[node1], node2) == FALSE)
            insertToLL(&((*graph)->graphArr[node1]), node2, weight);

        if ((*graph)->isDirected == FALSE) {
            if ((*graph)->graphArr[node2] == NULL) {
                Node *head = malloc(sizeof(Node));
                head->data = node1;
                if ((*graph)->isWeighted)
                    head->weight = weight;
                else
                    head->weight = NULL;
                head->next = NULL;
                (*graph)->graphArr[node2] = head;
            }
            else if (allowDuplicate == TRUE)
                insertToLL(&((*graph)->graphArr[node2]), node1, weight);
            else if (checkLL((*graph)->graphArr[node2], node1) == FALSE)
                insertToLL(&((*graph)->graphArr[node2]), node1, weight);
        }
    }
    else {
        if (!(*graph)->isWeighted)
            weight = 1;
        if ((*graph)->isDirected == FALSE) {
            ((int*)((*graph)->graphArr[node1]))[node2] = weight;
            ((int*)((*graph)->graphArr[node2]))[node1] = weight;
        } else {
            ((int*)((*graph)->graphArr[node1]))[node2] = weight;
        }
    }
}

void removeConnection(Graph **graph, int node1, int node2) {
    if ((*graph) == NULL || node1 < 0 || node1 > (*graph)->nNode
                        || node2 < 0 || node2 > (*graph)->nNode)
        return;

    if ((*graph)->representMode == ADJ_LIST) {
        deleteFromLL(&((*graph)->graphArr[node1]), node2);
        if ((*graph)->isDirected == FALSE)
            deleteFromLL(&((*graph)->graphArr[node2]), node1);
    }
    else {
        ((int*)((*graph)->graphArr[node1]))[node2] = 0;
        if ((*graph)->isDirected == FALSE)
            ((int*)((*graph)->graphArr[node2]))[node1] = 0;
    }
}

bool checkConnection(Graph *graph, int node1, int node2) {
    if (graph == NULL || node1 < 0 || node1 > graph->nNode
                        || node2 < 0 || node2 > graph->nNode)
        return FALSE;

    if (graph->representMode == ADJ_LIST) {
        if (graph->isDirected == FALSE)
            if (checkLL(graph->graphArr[node1], node2) &&
                checkLL(graph->graphArr[node2], node1))
                return TRUE;
        else
            if (checkLL(graph->graphArr[node1], node2))
                return TRUE;
    }
    else {
        if (graph->isDirected == FALSE)
            if (((int*)(graph->graphArr[node1]))[node2] != 0
                && ((int*)(graph->graphArr[node2]))[node1] != 0
                && ((int*)(graph->graphArr[node1]))[node2] != -1
                && ((int*)(graph->graphArr[node2]))[node1] != -1)
                return TRUE;
        else {
            if (((int*)(graph->graphArr[node1]))[node2] != 0
                && ((int*)(graph->graphArr[node1]))[node2] != -1)
                return TRUE;
        }
    }

    return FALSE;
}

void insertToLL(Node **head, int data, int weight) {
    Node *n = malloc(sizeof(Node));
    n->data = data;
    n->weight = weight;
    n->next = NULL;

    Node *t = *head;
    while(t->next != NULL)
        t = t->next;

    t->next = n;
}

bool checkLL(Node *head, int data) {
    Node *t = head;
    while (t != NULL) {
        if (t->data == data)
            return TRUE;
        t = t->next;
    }
    return FALSE;
}

void deleteFromLL(Node **head, int data) {
    Node *t = *head, *prev = *head;

    // If head will be removed
    if(t != NULL && t->data == data) {
        *head = (*head)->next;
        free(t);
        return;
    }

    // Iterate t to the node that will be removed
    while(t->next != NULL && t->data != data) {
        prev = t;
        t = t->next;
    }

    // If node was found, remove
    if(t->data == data) {
        prev->next = t->next;
        free(t);
    }
}

void printLL(Node *head) {
    Node *t = head;
    while (t != NULL) {
        if (t->next != NULL)
            if (t->weight != NULL)
                printf("%d (%d) -> ", t->data, t->weight);
            else
                printf("%d -> ", t->data, t->weight);
        else
            if (t->weight != NULL)
                printf("%d (%d)", t->data, t->weight);
            else
                printf("%d", t->data);
        t = t->next;
    }
}

void printGraph(Graph *graph) {
    if (graph == NULL)
        return;

    if (graph->representMode == ADJ_LIST) {
        for (int i=0; i<graph->nNode; i++) {
            printf("[%d] | ", i);
            if (graph->graphArr[i] == NULL)
                printf("~~~");
            else
                printLL(graph->graphArr[i]);
            printf("\n");
        }
    }
    else {
        for (int i=-1; i<graph->nNode; i++)
            if (i == -1)
                printf("     ");
            else
                printf("[%d] ", i);
        printf("\n");

        for (int i=-1; i<graph->nNode; i++)
            printf("____");
        printf("\n");

        for (int i=0; i<graph->nNode; i++) {
            for (int j=-1; j<graph->nNode; j++) {
                if (j == -1)
                    printf("[%d] | ", i);
                else if (((int*)(graph->graphArr[i]))[j] != -1)
                    printf("%d   ", ((int*)(graph->graphArr[i]))[j]);
                else if (((int*)(graph->graphArr[i]))[j] == -1)
                    printf("~   ");
            }
            printf("\n");
        }
    }
    printf("\n");
}

#endif // GRAPH_H_INCLUDED

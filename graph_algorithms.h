#ifndef GRAPH_ALGORITHMS_H_INCLUDED
#define GRAPH_ALGORITHMS_H_INCLUDED

#include <limits.h>

#include "graph.h"
#include "queue.h"
#include "stack.h"

#define INF INT_MAX

void breadFirstSearch(Graph *graph, int startNode) {
    if (startNode < 0 ||startNode > graph->nNode)
        return;

    Queue *queue;
    initWithSize(&queue, graph->nNode);
    bool *visited = calloc(graph->nNode, sizeof(bool));

    visited[startNode] = TRUE;
    enqueue(queue, startNode);

    printf("BFS\n");
    if (graph->representMode == ADJ_MATRIX) {
        while (!isEmptyQueue(queue)) {
            int node = dequeue(queue);
            printf("%d ", node);

            for (int i=0; i<graph->nNode; i++)
                if (checkConnection(graph, node, i) && visited[i] != TRUE) {
                    visited[i] = TRUE;
                    enqueue(queue, i);
                }
        }
    }
    else {
        while (!isEmptyQueue(queue)) {
            int node = dequeue(queue);
            printf("%d ", node);

            Node *head = graph->graphArr[node];
            Node *t = head;
            while (t != NULL) {
                if (!visited[t->data]) {
                    visited[t->data] = TRUE;
                    enqueue(queue, t->data);
                }
                t = t->next;
            }
        }
    }
    printf("\n");
}

void depthFirstSearch(Graph *graph, int startNode) {
    if (startNode < 0 ||startNode > graph->nNode)
        return;

    Stack *stack;
    initStack(&stack);
    bool *visited = calloc(graph->nNode, sizeof(bool));

    printf("DFS\n");
    visited[startNode] = TRUE;
    push(stack, startNode);
    printf("%d ", startNode);

    if (graph->representMode == ADJ_MATRIX) {
        while (!isEmptyStack(stack)) {
            int node = top(stack);
            int i;
            for (i=0; i<graph->nNode; i++)
                if (checkConnection(graph, node, i) && !visited[i]) {
                    visited[i] = TRUE;
                    push(stack, i);
                    printf("%d ", i);
                    break;
                }
            if (i == graph->nNode)
                pop(stack);
        }
    }
    else {
        while (!isEmptyStack(stack)) {
            int node = top(stack);
            bool pushed = FALSE;

            Node *head = graph->graphArr[node];
            Node *t = head;

            while (t != NULL) {
                if (!visited[t->data]) {
                    push(stack, t->data);
                    visited[t->data] = TRUE;
                    pushed = TRUE;
                    printf("%d ", t->data);
                    break;
                }
                t = t->next;
            }
            if (!pushed)
                pop(stack);
        }
    }
    printf("\n");
}

void dijkstraShortestPath(Graph *graph, int startNode) {
    int *distanceArr = malloc(graph->nNode * sizeof(int));
    for (int i=0; i<graph->nNode; i++)
        distanceArr[i] = INF;
    bool *visited = calloc(graph->nNode, sizeof(bool));
    distanceArr[startNode] = 0;

    int node = startNode;
    if (graph->representMode == ADJ_MATRIX) {
        int minNode;
        while (minNode != NULL) {
            visited[node] = TRUE;
            minNode = NULL;
            int minPath = 9999;

            for (int i=0; i<graph->nNode; i++) {
                if (checkConnection(graph, node, i)) {
                    if (((int*)(graph->graphArr[node]))[i] + distanceArr[node] < distanceArr[i])
                        distanceArr[i] = ((int*)(graph->graphArr[node]))[i] + distanceArr[node];
                    if (distanceArr[i] < minPath && !visited[i]) {
                        minPath = distanceArr[i];
                        minNode = i;
                    }
                }
            }

            node = minNode;
        }
    }
    else {
        int minNode;
        while (minNode != NULL) {
            visited[node] = TRUE;
            minNode = NULL;
            int minPath = INF;

            Node *head = graph->graphArr[node];
            Node *t = head;
            while (t != NULL) {
                if (distanceArr[node] + t->weight < distanceArr[t->data])
                    distanceArr[t->data] = distanceArr[node] + t->weight;
                if (distanceArr[t->data] < minPath && !visited[t->data]) {
                    minPath = distanceArr[t->data];
                    minNode = t->data;
                }
                t = t->next;
            }

            node = minNode;
        }
    }

    printf("\n");
    printf("DIJKSTRA SHORTEST PATH\n");
    for (int i=0; i<graph->nNode; i++)
        if (distanceArr[i] == INF)
            printf("INF ");
        else
            printf("%d ", distanceArr[i]);
    printf("\n");
}

void primsMinimumSpanningTree(Graph *graph) {
    int startNode = rand() % graph->nNode;

    Stack *stack;
    initStack(&stack);
    push(stack, startNode);

    bool *visited = calloc(graph->nNode, sizeof(bool));
    visited[startNode] = TRUE;

    printf("PRIM'S MINIMUM SPANNING TREE\n");
    if (graph->representMode == ADJ_MATRIX) {
        while (stack->top != graph->nNode) {
            int minPath = INF, minNode, fromNode;

            for(int i=0; i<=stack->top; i++) {
                for (int j=0; j<graph->nNode; j++) {
                    if (!visited[j] && checkConnection(graph, stack->arr[i], j)) {
                        if (((int*)(graph->graphArr[stack->arr[i]]))[j] < minPath) {
                            minPath = ((int*)(graph->graphArr[stack->arr[i]]))[j];
                            minNode = j;
                            fromNode = stack->arr[i];
                        }
                    }
                }
            }

            push(stack, minNode);
            visited[minNode] = TRUE;
            printf("%d -> %d\n", fromNode, minNode);
        }
    }
    else {
        while (stack->top != graph->nNode) {
            int minPath = INF, minNode, fromNode;

            for(int i=0; i<=stack->top; i++) {
                Node *head = graph->graphArr[stack->arr[i]];
                Node *t = head;
                while (t != NULL) {
                    if (!visited[t->data] && checkConnection(graph, stack->arr[i], t->data)) {
                        if (t->weight < minPath) {
                            minPath = t->weight;
                            minNode = t->data;
                            fromNode = stack->arr[i];
                        }
                    }
                    t = t->next;
                }
            }

            push(stack, minNode);
            visited[minNode] = TRUE;
            printf("%d -> %d\n", fromNode, minNode);
        }
    }
    printf("\n");
}

#endif // GRAPH_ALGORITHMS_H_INCLUDED

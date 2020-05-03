#ifndef PRIORITY_QUEUE_H_INCLUDED
#define PRIORITY_QUEUE_H_INCLUDED

#include <math.h>

#define N       16
#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    int priority;
} Element;

typedef struct {
    int front;
    int rear;
    int size;
    Element *data;
} pQueue;

void createPQueue (pQueue **queue) {
    (*queue) = malloc(sizeof(pQueue));
    (*queue)->front = 0;
    (*queue)->rear = 0;
    (*queue)->size = N;
    (*queue)->data = malloc(sizeof(Element) * N);
}

void increaseSizeOfPQueue(pQueue *queue) {
    queue->data = realloc(queue->data, sizeof(Element) * queue->size * 2);
    queue->size *= 2;
}

void decreaseSizeOfPQueue(pQueue *queue) {
    int count = 0;
    int activeSize = getActiveSize(queue);

    while(activeSize != 0) {
        activeSize /= 2;
        count++;
    }

    int newSize = pow(2, count);
    count = 0;
    Element *elements = malloc(sizeof(Element) * newSize);

    for(int i=queue->front; i<queue->rear; i++) {
        elements[count] = queue->data[i];
        count++;
    }

    queue->data = elements;
    queue->rear = count;
    queue->front = 0;
    queue->size = newSize;
}

bool isPQueueFull(pQueue *queue) {
    if(queue->rear == queue->size - 1)
        return TRUE;
    return FALSE;
}

bool isPQueueEmpty(pQueue *queue) {
    if(queue->front == queue->rear)
        return TRUE;
    return FALSE;
}

int getActiveSize(pQueue *queue) {
    return queue->rear - queue->front;
}

void enqueueP (pQueue *queue, int value, int priority) {
    Element e;
    e.priority = priority;
    e.value = value;
    if(isPQueueFull(queue))
        increaseSizeOfPQueue(queue);
    queue->data[queue->rear] = e;
    queue->rear = queue->rear + 1;
}

int getHighestPriority(pQueue *queue) {
    int max = queue->data[0].priority;
    int index = 0;
    for(int i=queue->front; i<queue->rear; i++) {
        if(queue->data[i].priority > max) {
            max = queue->data[i].priority;
            index = i;
        }
    }
    return index;
}

int dequeueP (pQueue *queue) {
    if(!isPQueueEmpty(queue)) {
        int iPriority = getHighestPriority(queue);
        int willBeReturned = queue->data[iPriority].value;
        for(int i=iPriority; i<queue->rear; i++)
            queue->data[i] = queue->data[i+1];
        queue->rear = queue->rear - 1;
        if(queue->size > getActiveSize(queue) * 2)
            decreaseSizeOfPQueue(queue);
        return willBeReturned;
    }
    return -1;
}

void updatePriority(pQueue *queue, int value) {
    for(int i=queue->front; i<queue->rear; i++)
        queue->data[i].priority += value;
}

bool searchInPQueue(pQueue *queue, int element) {
    for(int i=queue->front; i<queue->rear; i++) {
        if(queue->data[i].value == element)
            return TRUE;
    }
    return FALSE;
}

void printPQueue(pQueue *queue, bool debug) {
    for(int i=queue->front; i<queue->rear; i++)
        printf("%d ", queue->data[i].value);
    if(debug)   printf("\nSize = %d, Active Size = %d\n", queue->size, getActiveSize(queue));
    else        printf("\n");
}

#endif // PQUEUE_H_INCLUDED

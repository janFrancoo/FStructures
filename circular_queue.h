#ifndef CIRCULAR_QUEUE_H_INCLUDED
#define CIRCULAR_QUEUE_H_INCLUDED

#define N       8
#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct{
    int rear;
    int front;
    int size;
    bool r_tour;
    int *data;
} CQueue;


void createCQueue (CQueue **queue) {
    (*queue) = malloc(sizeof(CQueue));
    (*queue)->front = 0;
    (*queue)->rear = 0;
    (*queue)->size = N;
    (*queue)->r_tour = FALSE;
    (*queue)->data = malloc(sizeof(int) * N);
}

bool isSatisfied(bool r_tour, int rear, int front) {
    if(r_tour == FALSE) {
        if(rear >= front)
            return TRUE;
        return FALSE;
    }
    else {
        if(rear <= front)
            return TRUE;
        return FALSE;
    }
}

void enqueueC (CQueue *queue, int element) {
    if(isSatisfied(queue->r_tour, queue->rear + 1, queue->front)) {
        queue->data[queue->rear] = element;
        queue->rear += 1;
        if(queue->rear == queue->size) {
            queue->rear = 0;
            queue->r_tour = TRUE;
        }
    }
}

int dequeueC (CQueue *queue) {
    if(isSatisfied(queue->r_tour, queue->rear, queue->front + 1)) {
        int element = queue->data[queue->front];
        queue->front += 1;
        if(queue->front == queue->size) {
            queue->front = 0;
            queue->r_tour = FALSE;
        }
        return element;
    }
    return -1;
}

void printCQueue(CQueue *queue) {
    printf("front = %d, rear = %d\n", queue->front, queue->rear);
    if(queue->front > queue->rear || (queue->rear == queue->front && queue->r_tour == TRUE)) {
        for(int i=queue->front; i<queue->size; i++)
            printf("%d ", queue->data[i]);
        for(int i=0; i<queue->rear; i++)
            printf("%d ", queue->data[i]);
    }
    else {
        for(int i=queue->front; i<queue->rear; i++)
            printf("%d ", queue->data[i]);
    }

    printf("\n");
}

#endif // CQUEUE_H_INCLUDED

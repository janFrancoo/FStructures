#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define TRUE    1
#define FALSE   0
#define N       16
typedef int bool;

typedef struct {
    int front;
    int rear;
    int size;
    int *data;
} Queue;

void createQueue(Queue **queue) {
    (*queue) = malloc(sizeof(Queue));
    (*queue)->front = 0;
    (*queue)->rear = 0;
    (*queue)->size = N;
    (*queue)->data = malloc(sizeof(int) * N);
}

void createQueueWithSize (Queue **queue, int n){
    (*queue) = malloc(sizeof(Queue));
    (*queue)->front = 0;
    (*queue)->rear = 0;
    (*queue)->size = n;
    (*queue)->data = malloc(sizeof(int) * n);
}

void increaseQueueSize(Queue *queue) {
    int count = 0;
    int *newQueueArr = malloc(sizeof(int) * queue->size * 2);
    for(int i=queue->front; i<queue->rear; i++){
        newQueueArr[count] = queue->data[i];
        count++;
    }

    queue->size = queue->size * 2;
    queue->front = 0;
    queue->rear = count;
    queue->data = newQueueArr;
}

void decreaseQueueSize(Queue *queue) {
    int activeSize = getActiveCount(queue);
    int count = 0;

    while(activeSize != 0) {
        activeSize /= 2;
        count++;
    }

    int newSize = pow(2, count);
    int *newQueueArr = malloc(sizeof(int) * newSize);
    count = 0;

    while(!isQueueEmpty(queue)) {
        newQueueArr[count] = dequeue(queue);
        count++;
    }

    queue->data = newQueueArr;
    queue->front = 0;
    queue->rear = count;
    queue->size = newSize;
}

int getActiveCount(Queue *queue) {
    return queue->rear - queue->front;
}

bool isQueueEmpty(Queue *queue) {
    if(queue->front == queue->rear)
        return TRUE;
    return FALSE;
}

bool isQueueFull(Queue *queue){
    if(queue->rear == queue->size - 1)
        return TRUE;
    return FALSE;
}

int getFront(Queue *queue){
    return queue->data[queue->front];
}

int getRear(Queue *queue){
    return queue->data[queue->rear];
}

void enqueue(Queue *queue, int value){
    if(isQueueFull(queue))
        increaseQueueSize(queue);
    queue->data[queue->rear] = value;
    queue->rear = queue->rear + 1;
}

int dequeue(Queue *queue){
    if(!isQueueEmpty(queue)){
        int willBeReturned = queue->data[queue->front];
        queue->front = queue->front + 1;
        if(queue->size > getActiveCount(queue) * 2){
            decreaseQueueSize(queue);
        }
        return willBeReturned;
    }
    return -1;
}

void printQueue(Queue *queue) {
    for(int i=queue->front; i<queue->rear; i++)
        printf("%d ", queue->data[i]);
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// ALGORITHMS ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void reverseQueue (Queue *queue) {
    if(isQueueEmpty(queue))
        return;
    else {
        int data = dequeue(queue);
        reverseQueue (queue);
        enqueue(queue, data);
    }
}

int _getMinIndex(Queue *queue, int sortIndex) {
    int minIndex = -1, min = 9999, n = getActiveCount(queue);
    for(int i=0; i<n; i++) {
        int element = dequeue(queue);
        if(element < min && i <= sortIndex) {
            minIndex = i;
            min = element;
        }
        enqueue(queue, element);
    }
    return minIndex;
}

void _insertMinToRear(Queue *queue, int minIndex) {
    int min, n = getActiveCount(queue);
    for(int i=0; i<n; i++) {
        int element = dequeue(queue);
        if(i != minIndex)
            enqueue(queue, element);
        else
            min = element;
    }
    enqueue(queue, min);
}

void sortQueue(Queue *queue) {
    int n = getActiveCount(queue);
    for(int i=1; i<=n; i++)
        _insertMinToRear(queue, _getMinIndex(queue, n - i));
}

#endif // QUEUE_H_INCLUDED

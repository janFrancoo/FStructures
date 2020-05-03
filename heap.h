#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

#include "helper.h"
#include <math.h>

#define SIZE    25

enum {
    MAX_HEAP,
    MIN_HEAP
};

typedef struct {
    int size;
    int currIdx;
    int mode;
    int *data;
} Heap;

void createHeap(Heap **heap, int mode, int size) {
    if (size == NULL)
        size = SIZE;
    if (mode == NULL)
        mode = MAX_HEAP;
    else if (mode != 0 && mode != 1)
        mode = MAX_HEAP;

    (*heap) = malloc(sizeof(Heap));
    (*heap)->size = size;
    (*heap)->currIdx = 0;
    (*heap)->mode = mode;
    (*heap)->data = malloc(sizeof(int) * size);
}

void heapify(Heap **heap, int i) {
    if ((*heap)->currIdx <= 1)
        return;

    int left = 2*i + 1;
    int right = 2*i + 2;

    if ((*heap)->mode == MAX_HEAP) {
        int largest = i;

        if (left < (*heap)->currIdx && (*heap)->data[left] > (*heap)->data[largest])
            largest = left;
        if (right < (*heap)->currIdx && (*heap)->data[right] > (*heap)->data[largest])
            largest = right;

        if (largest != i) {
            swap(&(*heap)->data[i], &(*heap)->data[largest]);
            heapify(heap, largest);
        }
    } else {
        int minimum = i;

        if (left < (*heap)->currIdx && (*heap)->data[left] < (*heap)->data[minimum])
            minimum = left;
        if (right < (*heap)->currIdx && (*heap)->data[right] < (*heap)->data[minimum])
            minimum = right;

        if (minimum != i) {
            swap(&(*heap)->data[i], &(*heap)->data[minimum]);
            heapify(heap, minimum);
        }
    }
}

void insert(Heap **heap, int data) {
    if ((*heap)->currIdx == (*heap)->size)
        return;

    (*heap)->data[(*heap)->currIdx++] = data;
    for (int i=(*heap)->currIdx/2-1; i>=0; i--)
        heapify(heap, i);
}

int getData(Heap *heap, int data) {
    if (heap->mode == MAX_HEAP) {
        for (int i=0; i<heap->currIdx; i++) {
            if (heap->data[i] == data)
                return i;
            if  (data > heap->data[i])
                break;
        }
        return -1;
    } else {
        for (int i=0; i<heap->currIdx; i++) {
            if (heap->data[i] == data)
                return i;
            if  (data < heap->data[i])
                break;
        }
        return -1;
    }
}

void removeData(Heap **heap, int data) {
    int idxToRemove = getData((*heap), data);
    if (idxToRemove == -1)
        return;
    else {
        swap(&(*heap)->data[(*heap)->currIdx--], &(*heap)->data[idxToRemove]);
        for (int i=(*heap)->currIdx/2-1; i>=0; i--)
            heapify(heap, i);
    }
}

int getDepth(Heap *heap) {
    return (log(heap->currIdx) / log(2));
}

int getMin(Heap *heap) {
    if (heap->mode == MIN_HEAP)
        return heap->data[0];
    else {
        int depth = getDepth(heap);
        int first = pow(2, depth) - 1;
        int last = heap->currIdx - 1;

        int n = last - first + 1, j = 0;
        int *arr = malloc(sizeof(int) * n);
        for (int i=first; i<(first + n); i++)
            arr[j++] = heap->data[i];
        return minimum(arr, n);
    }
}

int getMax(Heap *heap) {
    if (heap->mode == MAX_HEAP)
        return heap->data[0];
    else {
        int depth = getDepth(heap);
        int first = pow(2, depth) - 1;
        int last = heap->currIdx - 1;

        int n = last - first + 1, j = 0;
        int *arr = malloc(sizeof(int) * n);
        for (int i=first; i<(first + n); i++)
            arr[j++] = heap->data[i];
        return maximum(arr, n);
    }
}

void printHeap(Heap *heap) {
    for (int i=0; i<heap->currIdx; i++)
        printf("%d ", heap->data[i]);
    printf("\n");
}

#endif // HEAP_H_INCLUDED

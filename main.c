#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

#include "queue.h"
#include "circular_queue.h"
#include "priority_queue.h"

#include "linked_list.h"
#include "doubly_linked_list.h"
#include "circular_linked_list.h"

#include "binary_tree.h"
#include "avl_tree.h"
// #include "red_black_tree.h"

#include "hash_chain.h"
// #include "hash_open_address.h" Can not be used with hash_chain.h (duplicate structure names, function names etc.)

#include "heap.h"

// #include "graph.h"
// #include "graph_algorithms.h"

#include "matrix.h"

int main()
{
    /*
    // STACK //
    // Create stack
    Stack *stack;
    createStack(&stack);

    // Push 10 values randomly
    for (int i=0; i<10; i++)
        push(stack, rand() % 10);
    printStack(stack);

    // Reverse values recursively
    reverseStack(stack);
    printStack(stack);

    // Delete middle value from stack (give arguments start index & top index)
    deleteMiddleValueFromStack(stack, 0, stack->top);
    printStack(stack);

    // Sort stack
    sortStack(&stack);
    printStack(stack);

    // Clear stack and push 10 values randomly
    while (!isStackEmpty(stack))
        pop(stack);

    for (int i=0; i<10; i++)
        push(stack, rand() % 10);
    printStack(stack);

    // Sort stack recursively
    sortStackRecursively(stack);
    printStack(stack);

    // QUEUE //
    // Create queue
    Queue *queue;
    createQueue(&queue);
    // createQueueWithSize(&queue, 15);

    // Enqueue random values and print to console
    for (int i=0; i<10; i++)
        enqueue(queue, rand() % 10);
    printQueue(queue);

    // Reverse queue
    reverseQueue(queue);
    printQueue(queue);

    // Sort queue
    sortQueue(queue);
    printQueue(queue);

    // Clear
    while (!isQueueEmpty(queue))
        dequeue(queue);

    // CIRCULAR QUEUE
    CQueue *queue;
    createCQueue(&queue);
    enqueueC(queue, 10);
    enqueueC(queue, 20);
    enqueueC(queue, 30);
    dequeueC(queue);
    dequeueC(queue);
    printCQueue(queue);

    // PRIORITY QUEUE
    pQueue *queue;
    createPQueue(&queue);

    enqueueP(queue, 10, 2);
    enqueueP(queue, 20, 1);
    enqueueP(queue, 30, 5);
    enqueueP(queue, 40, 3);
    printPQueue(queue, TRUE); // TRUE -> print active size & size
    dequeueP(queue);
    printPQueue(queue, FALSE);

    // LINKED LIST
    // Create list, insert values and print list to console with size value
    Node *head = NULL;
    for (int i=0; i<10; i++)
        insertToLL(&head, rand() % 100);
    printLL(head, TRUE);

    // Search - remove - search
    printf("58 is in list?: %d\n", searchInLL(head, 58));
    deleteFromLL(&head, 58);
    // deleteFromLLWithIdx(&head, 7);
    printf("58 is in list?: %d\n", searchInLL(head, 58));

    // Get middle
    printf("Middle: %d\n", getMiddleOfLL(head));

    // Swap nods
    swapNodes(&head, 34, 78);
    // swapNodesWithIndex(&head, 5, 10);
    printLL(head, FALSE);

    // Reverse list
    reverseLL(&head);
    printLL(head, FALSE);

    // Sort list
    mergeSortLL(&head);
    printLL(head, FALSE);

    // Delete list
    deleteLL(&head);
    printLL(head, TRUE);

    // DOUBLY LINKED LIST
    DNode *head = NULL;
    insertToDLL(&head, 10);
    insertToDLL(&head, 20);
    insertToDLL(&head, 30);
    searchInDLL(head, 20);
    deleteFromDLL(&head, 20);
    printDLL(head);

    // CIRCULAR LINKED LIST
    CNode *head = NULL;
    insertToCLL(&head, 10);
    insertToCLL(&head, 20);
    insertToCLL(&head, 30);
    deleteFromCLL(&head, 20);
    searchInCLL(head, 20);
    printCLL(head);

    // BINARY TREE
    // Create tree and insert values
    TNode *root = NULL;
    for (int i=0; i<10; i++)
        insertToTree(&root, rand() % 100);
    printTree(root);    // print console to tree (does not work properly)

    // Search - remove - search
    printf("58?: %d\n", findInTree(root, 58));
    deleteFromTree(&root, 58);
    printf("58?: %d\n", findInTree(root, 58));

    // Node count , height
    printf("Node count: %d - Height: %d\n", getTNodeCount(root), getHeight(root));

    // Traverse tree
    traversePreorder(root);
    printf("\n");
    traverseInorder(root);
    printf("\n");
    traversePostorder(root);
    printf("\n");

    // Sequence detect
    int seq[3] = {41, 34, 0};
    printf("is seq 41 - 34 - 0 exists?: %d\n", isSequenceExists(root, seq, 3));

    // Distances
    printf("root - 64: %d\n", distanceFromRoot(root, 64));
    printf("34 - 64: %d\n", distanceBetweenTNodes(root, 34, 64));

    // Clear
    cutTree(&root);
    printTree(root);

    // AVL TREE
    AVL *root = NULL;
    for (int i=0; i<10; i++)
        insertToAVL(&root, rand() % 100);
    printAVL(root);

    // HASH TABLE CHAIN MODE
    HashTable *hashTable;
    createHashTable_Chain(&hashTable, NULL); // NULL -> default size
    insertToTable(&hashTable, 10, 100);
    insertToTable(&hashTable, 10, 101);
    insertToTable(&hashTable, 10, 102);
    printTable(hashTable, NULL);    // NULL -> default display value
    removeKey(&hashTable, 10);
    insertToTable(&hashTable, 20, 50);
    insertToTable(&hashTable, 25, 92);
    removeValue(&hashTable, 25, 92);
    printTable(hashTable, NULL);

    // GRAPH
    Graph *graph;
    createGraph(&graph, FALSE, TRUE, ADJ_LIST, 9);

    newConnection(&graph, 0, 1, FALSE, 4);
    newConnection(&graph, 0, 7, FALSE, 8);
    newConnection(&graph, 1, 2, FALSE, 8);
    newConnection(&graph, 1, 7, FALSE, 11);
    newConnection(&graph, 2, 3, FALSE, 7);
    newConnection(&graph, 2, 5, FALSE, 4);
    newConnection(&graph, 2, 8, FALSE, 2);
    newConnection(&graph, 3, 4, FALSE, 9);
    newConnection(&graph, 3, 5, FALSE, 14);
    newConnection(&graph, 4, 5, FALSE, 10);
    newConnection(&graph, 5, 6, FALSE, 2);
    newConnection(&graph, 6, 7, FALSE, 1);
    newConnection(&graph, 6, 8, FALSE, 6);
    newConnection(&graph, 7, 8, FALSE, 7);

    printGraph(graph);

    dijkstraShortestPath(graph, 0);

    // MATRIX
    Matrix *m1;
    createMatrixFromFile(&m1, "matrix1.txt");
    printMatrix(m1);

    Matrix *m2;
    createMatrixFromFile(&m2, "matrix2.txt");
    printMatrix(m2);

    Matrix *mZero;
    zeroMatrix(&mZero, 2, 5);
    printMatrix(mZero);

    Matrix *mOne;
    oneMatrix(&mOne, 2, 5);
    printMatrix(mOne);

    Matrix *mMult;
    matrixMultiplication(m1, m2, &mMult);
    printMatrix(mMult);

    Matrix *mAdd;
    matrixAddition(m1, m2, &mAdd);
    printMatrix(mAdd);

    Matrix *mSub;
    matrixSub(m1, m2, &mSub);
    printMatrix(mSub);

    Matrix *transpose;
    matrixTranspose(m1, &transpose);
    printMatrix(transpose);

    Matrix *mCopy;
    copyMatrix(m1, &mCopy, 0, 1, 2, 2);
    printMatrix(mCopy);

    Matrix *sqDetMatrix;
    createMatrixFromFile(&sqDetMatrix, "sqDetMatrix.txt");
    printMatrix(sqDetMatrix);

    Matrix *randSqMatrix;
    randomSquareMatrix(&randSqMatrix, 7, 20);
    printMatrix(randSqMatrix);
    printf("%d\n", getDeterminant(randSqMatrix));

    Matrix *m;
    zeroMatrix(&m, 3, 3);
    ((int*)m->data[0])[0] = 1;
    ((int*)m->data[0])[1] = 0;
    ((int*)m->data[0])[2] = 5;
    ((int*)m->data[1])[0] = 2;
    ((int*)m->data[1])[1] = 1;
    ((int*)m->data[1])[2] = 6;
    ((int*)m->data[2])[0] = 3;
    ((int*)m->data[2])[1] = 4;
    ((int*)m->data[2])[2] = 0;
    printMatrix(m);

    Matrix *inverse;
    getInverse(m, &inverse);
    printMatrix(inverse);
    */

    return 0;
}

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#define true        1
#define false       0
#define initSize    4
typedef int bool;

typedef struct{
    int *arr;
    int top;
    int size;
}Stack;

void createStack(Stack **stack){
    (*stack) = malloc(sizeof(Stack));
    (*stack)->size = initSize;
    (*stack)->top = -1;
    (*stack)->arr = malloc((*stack)->size * sizeof(int));
}

void increaseStackSize(Stack *stack){
    stack->size = stack->size * 2;
    stack->arr = realloc(stack->arr, sizeof(int) * stack->size);
}

void decreaseStackSize(Stack *stack){
    stack->size = stack->size / 2;
    stack->arr = realloc(stack->arr, sizeof(int) * stack->size);
}

void push(Stack *stack, int element){
    if(isStackFull(stack))
        increaseStackSize(stack);
    stack->top = stack->top + 1;
    stack->arr[stack->top] = element;
}

int pop(Stack *stack){
    if(!isStackEmpty(stack)){
        if(stack->size / 2 > stack->top)
            decreaseStackSize(stack);
        int toBeReturned = stack->arr[stack->top];
        stack->top = stack->top - 1;
        return toBeReturned;
    }
    return NULL;
}

int peek(Stack *stack){
    if(!isStackEmpty(stack)){
        return stack->arr[stack->top];
    }
    return NULL;
}

bool isStackFull(Stack *stack){
    return stack->top == stack->size - 1 ? true : false;
}

bool isStackEmpty(Stack *stack){
    return stack->top == -1 ? true : false;
}

void printStack(Stack *stack){
    for(int i=0; i<=stack->top; i++){
        printf("%d ", stack->arr[i]);
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// ALGORITHMS ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void _insertAtBottom(Stack *stack, int element){
    if(isStackEmpty(stack))
        push(stack, element);
    else{
        int temp = pop(stack);
        _insertAtBottom(stack, element);
        push(stack, temp);
    }
}

void reverseStack(Stack *stack){
    if(!isStackEmpty(stack)){
        int temp = pop(stack);
        reverseStack(stack);
        _insertAtBottom(stack, temp);
    }
}

void _sortedInsert(Stack *stack, int element){
    if(isStackEmpty(stack) || element > peek(stack)){
        push(stack, element);
        return;
    }

    int temp = pop(stack);
    _sortedInsert(stack, element);
    push(stack, temp);
}

void sortStackRecursively(Stack *stack){
    if(!isStackEmpty(stack)){
        int temp = pop(stack);
        sortStackRecursively(stack);
        _sortedInsert(stack, temp);
    }
}

void sortStack(Stack **stack){
    Stack *tmpStack;
    createStack(&tmpStack);
    while(!isStackEmpty(*stack)){
        int temp = pop(*stack);
        while(!isStackEmpty(tmpStack) && peek(tmpStack) > temp)
            push(*stack, pop(tmpStack));
        push(tmpStack, temp);
    }
    *stack = tmpStack;
}

void deleteMiddleValueFromStack(Stack *stack, int curr, int n){
    if(isStackEmpty(stack) || curr == n)
        return;

    int temp = pop(stack);
    deleteMiddleValueFromStack(stack, curr+1, n);
    if(curr != n/2)
        push(stack, temp);
}

#endif // STACK_H_INCLUDED

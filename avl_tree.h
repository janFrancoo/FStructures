#ifndef AVL_TREE_H_INCLUDED
#define AVL_TREE_H_INCLUDED

#include "helper.h"

typedef struct {
    int value;
    int height;
    struct AVL *left;
    struct AVL *right;
} AVL;

void insertToAVL(AVL **root, int value) {
    if ((*root) == NULL) {
        AVL *n = malloc(sizeof(AVL));
        n->height = 1;
        n->value = value;
        n->left = NULL;
        n->right = NULL;
        (*root) = n;
        return;
    }

    if (value < (*root)->value)
        insertToAVL(&((*root)->left), value);
    else if (value > (*root)->value)
        insertToAVL(&((*root)->right), value);
    else
        return;

    (*root)->height = 1 + max(getHeightOfAVL((*root)->left), getHeightOfAVL((*root)->right));
    int balance = getBalance(*root);

    // LL Case
    if (balance > 1 && value < ((AVL *)(*root)->left)->value)
        rotateRight(&(*root));

    // RR Case
    if (balance < -1 && value > ((AVL *)(*root)->right)->value)
        rotateLeft(&(*root));

    // LR Case
    if (balance > 1 && value > ((AVL *)(*root)->left)->value) {
        rotateLeft(&((*root)->left));
        rotateRight(&(*root));
    }

    // RL Case
    if (balance < -1 && value < ((AVL *)(*root)->right)->value) {
        rotateRight(&((*root)->right));
        rotateLeft(&(*root));
    }
}

AVL *minValueAVL(AVL *root) {
    AVL *t = root;
    while(t->left != NULL)
        t = t->left;
    return t;
}

void deleteAVL(AVL **root, int value) {
    if (*root == NULL)
        return;

    if (value < (*root)->value)
        deleteAVL(&((*root)->left), value);
    else if (value > (*root)->value)
        deleteAVL(&((*root)->right), value);
    else {
        // ONE OR NO CHILD CASE
        if ((*root)->left == NULL || (*root)->right == NULL) {
            AVL *temp = (*root)->left ? (*root)->left : (*root)->right;

            // NO CHILD CASE
            if (temp == NULL)
                (*root) = NULL;
            else // ONE CHILD CASE
                (*root) = temp;
        }
        // TWO CHILD CASE
        else {
            AVL *temp = minValueAVL((*root)->right);
            (*root)->value = temp->value;
            deleteAVL(&((*root)->right), temp->value);
        }
    }

    if ((*root) == NULL)
        return;

    (*root)->height = 1 + max(getHeightOfAVL((*root)->left), getHeightOfAVL((*root)->right));
    int balance = getBalance(*root);

    // LL Case
    if (balance > 1 && getBalance((*root)->left) >= 0)
        rotateRight(&(*root));

    // RR Case
    if (balance < -1 && getBalance((*root)->right) <= 0)
        rotateLeft(&(*root));

    // LR Case
    if (balance > 1 && getBalance((*root)->left) < 0) {
        rotateLeft(&((*root)->left));
        rotateRight(&(*root));
    }

    // RL Case
    if (balance < -1 && getBalance((*root)->right) > 0) {
        rotateRight(&((*root)->right));
        rotateLeft(&(*root));
    }
}

void rotateLeft(AVL **root) {
    AVL *rightAVL = (*root)->right;
    AVL *transferAVL = rightAVL->left;

    rightAVL->left = (*root);
    (*root)->right = transferAVL;

    (*root)->height = 1 + max(getHeightOfAVL((*root)->left), getHeightOfAVL((*root)->right));
    rightAVL->height = 1 + max(getHeightOfAVL(rightAVL->left), getHeightOfAVL(rightAVL->right));
    (*root) = rightAVL;
}

void rotateRight(AVL **root) {
    AVL *leftAVL = (*root)->left;
    AVL *transferAVL = leftAVL->right;

    leftAVL->right = (*root);
    (*root)->left = transferAVL;

    (*root)->height = 1 + max(getHeightOfAVL((*root)->left), getHeightOfAVL((*root)->right));
    leftAVL->height = 1 + max(getHeightOfAVL(leftAVL->left), getHeightOfAVL(leftAVL->right));
    (*root) = leftAVL;
}

int getBalance(AVL *root) {
    if (root == NULL)
        return 0;
    return getHeightOfAVL(root->left) - getHeightOfAVL(root->right);
}

int getHeightOfAVL(AVL *root) {
    if (root == NULL)
        return 0;
    return root->height;
}

void printAVL(AVL *root) {
    int height = getHeightOfAVL(root);
    for(int i=1; i<=height + 1; i++) {
        printLevel(root, i);
        printf("\n");
    }
}

void printLevel(AVL *root, int level) {
    if (root == NULL) {
        printf("~ ");
        return;
    }

    if (level == 1)
        printf("%d ", root->value);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

#endif // AVL_TREE_H_INCLUDED

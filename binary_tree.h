#ifndef BINARY_TREE_H_INCLUDED
#define BINARY_TREE_H_INCLUDED

#include "helper.h"

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    struct TNode *left;
    struct TNode *right;
} TNode;

void insertToTree (TNode **root, int value) {
    if (*root == NULL) {
        TNode *n = malloc(sizeof(TNode));

        n->value = value;
        n->right = NULL;
        n->left = NULL;

        *root = n;

        return;
    }
    else if (value <= (*root)->value) {
        insertToTree(&((*root)->left), value);
    }
    else {
        insertToTree(&((*root)->right), value);
    }
}

TNode *minValueTNode(TNode *root) {
    TNode *current = root;
    while(current && current->left != NULL)
        current = current->left;
    return current;
}

void deleteFromTree (TNode **root, int value) {
    if((*root) == NULL)
        return;

    if(value < (*root)->value)
        deleteFromTree(&((*root)->left), value);
    else if(value > (*root)->value)
        deleteFromTree(&((*root)->right), value);
    else {
        if((*root)->left == NULL && (*root)->right == NULL) {
            (*root) = NULL;
            free((*root));
            return;
        }
        else if((*root)->left == NULL && (*root)->right != NULL) {
            TNode *temp = (*root)->right;
            (*root)->right = NULL;
            free((*root)->right);
            (*root) = temp;
        }
        else if((*root)->left != NULL && (*root)->right == NULL) {
            TNode *temp = (*root)->left;
            (*root)->left = NULL;
            free((*root)->left);
            (*root) = temp;
        }
        else {
            TNode *temp = minValueTNode((*root)->right);
            (*root)->value = temp->value;
            deleteFromTree(&((*root)->right), temp->value);
        }
    }
}

bool findInTree (TNode *root, int value) {
    if (root == NULL)
        return FALSE;
    if (value == root->value)
        return TRUE;

    bool res1 = findInTree(root->left, value);
    if(res1)    return TRUE;

    bool res2 = findInTree(root->right, value);
    return res2;
}

int getHeight(TNode *root) {
    if (root == NULL)
        return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

int getTNodeCount(TNode *root) {
    if (root == NULL)
        return 0;
    return getTNodeCount(root->left) + getTNodeCount(root->right) + 1;
}

void printTree(TNode *TNode) {
    int h = getHeight(TNode);
    for(int i=1; i<=h; i++) {
        printBlank((h - i) * 2);
        printGivenLevel(TNode, i);
        printf("\n\n");
    }
}

void printGivenLevel (TNode *root, int level) {
    if (root == NULL) {
        printf("  ");
        return;
    }
    if (level == 1) {
        printf("  %d  ", root->value);
    }
    else if (level > 1) {
        printGivenLevel(root->left, level - 1);
        printGivenLevel(root->right, level - 1);
    }
}

void traversePreorder (TNode *TNode) {
    if (TNode == NULL)
        return;

    printf("%d -> ", TNode->value);
    traverseInorder(TNode->left);
    traverseInorder(TNode->right);
}

void traverseInorder (TNode *TNode) {
    if (TNode == NULL)
        return;

    traverseInorder(TNode->left);
    printf("%d -> ", TNode->value);
    traverseInorder(TNode->right);
}

void traversePostorder (TNode *TNode) {
    if (TNode == NULL)
        return;

    traverseInorder(TNode->left);
    traverseInorder(TNode->right);
    printf("%d -> ", TNode->value);
}

int getValueOfRoot (TNode *root) {
    return root->value;
}

bool isSequenceExists (TNode *root, int seq[], int n) {
    selectionSort(seq, n);
    int index = 0;
    isSequenceExistsUtil(root, seq, &index);
    return (index == n);
}

void isSequenceExistsUtil(TNode *TNode, int seq[], int *index) {
    if (TNode == NULL)
        return;

    isSequenceExistsUtil(TNode->left, seq, index);

    if (TNode->value == seq[*index]) {
        *index = *index + 1;
    }

    isSequenceExistsUtil(TNode->right, seq, index);
}

int distanceBetweenTNodes(TNode *root, int a, int b) {
    if (a > b)
        swap(&a, &b);
    if (root == NULL)
        return 0;

    if (a < root->value && b < root->value)
        return distanceBetweenTNodes(root->left, a, b);
    else if (a > root->value && b > root->value)
        return distanceBetweenTNodes(root->right, a, b);
    else if (a <= root->value && b >= root->value)
        return distanceFromRoot(root, a) + distanceFromRoot(root, b);
}

int distanceFromRoot(TNode *root, int value) {
    if (value == root->value)
        return 0;

    if(value < root->value)
        return distanceFromRoot(root->left, value) + 1;

    if(value > root->value)
        return distanceFromRoot(root->right, value) + 1;
}

void cutTree (TNode **root) {
    while((*root) != NULL)
        deleteFromTree(&(*root), getValueOfRoot(*root));
}

#endif // BINARY_TREE_H_INCLUDED

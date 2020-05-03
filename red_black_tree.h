#ifndef RED_BLACK_TREE_H_INCLUDED
#define RED_BLACK_TREE_H_INCLUDED

#include "helper.h"

#define BLACK   0
#define RED     1
#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    int color : 2;
    struct Node *parent;
    struct Node *right;
    struct Node *left;
} Node;

Node *createNode(int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value;
    n->right = NULL;
    n->left = NULL;
    n->parent = NULL;
    n->color = RED;
    return n;
}

Node *bstInsert(Node *root, Node *node) {
    if (root == NULL) {
        return node;
    }

    if (node->value < root->value) {
        root->left = bstInsert(root->left, node);
        ((Node *)root->left)->parent = root;
    }
    else if (node->value > root->value) {
        root->right = bstInsert(root->right, node);
        ((Node *)root->right)->parent = root;
    }

    return root;
}

void insert(Node **root, int value) {
    if(search(*root, value) == FALSE) {
        Node *n = createNode(value);
        (*root) = bstInsert(*root, n);
        fixViolation(root, &n);
    }
}

void rotateLeft(Node **root, Node **node) {
    Node *right = (*node)->right;
    (*node)->right = right->left;

    if ((*node)->right != NULL)
        ((Node*)((*node)->right))->parent = (*node);

    right->parent = (*node)->parent;

    if ((*node)->parent == NULL)
        (*root) = right;
    else if ((*node) == ((Node*)((*node)->parent))->left)
        ((Node*)((*node)->parent))->left = right;
    else
        ((Node*)((*node)->parent))->right = right;

    right->left = (*node);
    (*node)->parent = right;
}

void rotateRight(Node **root, Node **node) {
    Node *left = (*node)->left;
    (*node)->left = left->right;

    if ((*node)->left != NULL)
        ((Node*)((*node)->left))->parent = (*node);

    left->parent = (*node)->parent;

    if ((*node)->parent == NULL)
        (*root) = left;
    else if ((*node) == ((Node*)((*node)->parent))->left)
        ((Node*)((*node)->parent))->left = left;
    else
        ((Node*)((*node)->parent))->right = left;

    left->right = (*node);
    (*node)->parent = left;
}

void fixViolation(Node **root, Node **node) {
    Node *parent = NULL, *grandParent = NULL;
    while (((*node) != (*root)) && ((*node)->color != BLACK) && (((Node*)(*node)->parent)->color == RED)) {
        parent = (*node)->parent;
        grandParent = ((Node *)((*node)->parent))->parent;
        if (parent == grandParent->left) {
            Node *uncle = grandParent->right;
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                (*node) = grandParent;
            }
            else {
                if ((*node) == parent->right) {
                    rotateLeft(root, &parent);
                    (*node) = parent;
                    parent = (*node)->parent;
                }
                rotateRight(root, &grandParent);
                int temp = parent->color;
                parent->color = grandParent->color;
                grandParent->color = temp;
                (*node) = parent;
            }
        }
        else {
            Node *uncle = grandParent->left;
            if (uncle != NULL && uncle->color == RED) {
                grandParent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                (*node) = grandParent;
            }
            else {
                if (*node == parent->left) {
                    rotateRight(root, &parent);
                    (*node) = parent;
                    parent = (*node)->parent;
                }
                rotateLeft(root, &grandParent);
                int temp = parent->color;
                parent->color = grandParent->color;
                grandParent->color = temp;
                (*node) = parent;
            }
        }
    }
    (*root)->color = BLACK;
}

bool search(Node *root, int value) {
    Node *t = root;
    while (t != NULL) {
        if (value < t->value)
            t = t->left;
        else if (value > t->value)
            t = t->right;
        else
            return TRUE;
    }
    return FALSE;
}

int getHeight(Node *root) {
    if (root == NULL)
        return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

void print(Node *root) {
    int height = getHeight(root);
    for (int level=1; level<=height; level++) {
        printLevel(root, level);
        printf("\n");
    }
}

void printLevel(Node *node, int level) {
    if (node == NULL)
        return;
    if (level == 1)
        printf("%d(%d) ", node->value, node->color);
    else if (level > 1) {
        printLevel(node->left, level - 1);
        printLevel(node->right, level - 1);
    }
}

#endif // RED_BLACK_TREE_H_INCLUDED

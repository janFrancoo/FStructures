#ifndef LINKED_LIST_H_INCLUDED
#define LINKED_LIST_H_INCLUDED

#define TRUE    1
#define FALSE   0
typedef int bool;

typedef struct {
    int value;
    struct Node *next;
} Node;

void insertToLL (Node **head, int value) {
    Node *n = malloc(sizeof(Node));
    n->value = value;
    n->next = NULL;

    if(*head == NULL) {
        *head = n;
        return;
    }

    Node *t = *head;
    while(t->next != NULL)
        t = t->next;

    t->next = n;
}

bool searchInLL (Node *head, int value) {
    Node *t = head;
    while(t != NULL) {
        if (t->value == value)
            return TRUE;
        t = t->next;
    }
    return FALSE;
}

void deleteFromLL (Node **head, int value) {
    Node *t = *head, *prev = *head;

    // If list is empty
    if(t == NULL)
        return;

    // If head will be removed
    if(t != NULL && t->value == value) {
        *head = (*head)->next;
        free(t);
        return;
    }

    // Iterate t to the node that will be removed
    while(t->next != NULL && t->value != value) {
        prev = t;
        t = t->next;
    }

    // If node was found, remove
    if(t->value == value) {
        prev->next = t->next;
        free(t);
    }
}

void deleteFromLLWithIdx (Node **head, int index) {
    Node *t = *head, *prev = *head;

    // If head will be removed
    if(index == 0) {
        t = *head;
        *head = (*head)->next;
        free(t);
        return;
    }

    // Go to that index
    for(int i=0; t != NULL && i<index-1; i++)
        t = t->next;

    // If the node that will be deleted is not null, delete
    if(t->next != NULL) {
        Node *next = ((Node*)(t->next))->next;
        free(t->next);
        t->next = next;
    }
}

void deleteLL (Node **head) {
    Node *t = *head, *next;

    while(t != NULL) {
        next = t->next;
        free(t);
        t = next;
    }

    *head = NULL;
}

int getValueFromLL (Node *head, int index) {
    Node *t = head;

    for(int i=0; i<index && t != NULL; i++)
        t = t->next;

    if(t != NULL)
        return t->value;

    return -1;
}

int getLengthOfLL (Node *head) {
    if(head == NULL)
        return 0;
    return getLengthOfLL (head->next) + 1;
}

int getMiddleOfLL (Node *head) {
    Node *t = head, *prev = head;

    while(t != NULL && t->next != NULL) {
        t = ((Node*)(t->next))->next;
        prev = prev->next;
    }

    return prev->value;
}

void printLL (Node *head, bool len) {
    Node *t = head;
    if(t == NULL)
        printf(" ~~ ");
    while(t != NULL) {
        if(t ->next == NULL)    printf("%d", t->value);
        else                    printf("%d -> ", t->value);
        t = t->next;
    }
    if(len)
        printf("\nLength = %d\n", getLengthOfLL (head));
    else
        printf("\n");
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////// ALGORITHMS ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////

void swapNodes (Node **head, int valueX, int valueY) {
    if (valueX == valueY)
        return;

    bool isXFound = FALSE, isYFound = FALSE;
    Node *t = *head, *prevX = NULL, *x = *head, *prevY = NULL, *y = *head;
    while(t != NULL) {
        if(t->value != valueX && !isXFound) {
            prevX = x;
            x = x->next;
        }
        if(t->value != valueY && !isYFound) {
            prevY = y;
            y = y->next;
        }
        if(t->value == valueX)  isXFound = TRUE;
        if(t->value == valueY)  isYFound = TRUE;
        t = t->next;
    }

    if(x == NULL || y == NULL)
        return;

    if(prevX == NULL)
        *head = y;
    else
        prevX->next = y;

    if(prevY == NULL)
        *head = x;
    else
        prevY->next = x;

    Node *temp = y->next;
    y->next = x->next;
    x->next = temp;
}

void swapNodesWithIndex (Node **head, int indexX, int indexY) {
    if(indexX == indexY)
        return;

    Node *t = *head, *prevX = NULL, *x = *head, *prevY = NULL, *y = head;

    for(int i=0; (i<indexX || i <indexY) && t != NULL; i++) {
        if(i + 1 == indexX) {
            prevX = t;
            x = t->next;
        }
        if(i + 1 == indexY) {
            prevY = t;
            y = t->next;
        }
        t = t->next;
    }

    if(x == NULL || y == NULL)
        return;

    if(prevX == NULL)   *head = y;
    else                prevX->next = y;

    if(prevY == NULL)   *head = x;
    else                prevY->next = x;

    t = y->next;
    y->next = x->next;
    x->next = t;
}

void reverseLL (Node **head) {
    Node *prev = NULL, *next = NULL;
    Node *current = *head;

    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    *head = prev;
}

Node *_sortedMerge(Node *a, Node *b) {
	if (a == NULL)
		return b;

	else if (b == NULL)
		return a;

	Node *result = NULL;

	if (a->value <= b->value) {
		result = a;
		result->next = _sortedMerge(a->next, b);
	} else {
		result = b;
		result->next = _sortedMerge(a, b->next);
	}

	return result;
}

void _frontBackSplit(Node *source, Node **frontRef, Node **backRef) {
	if (source == NULL || source->next == NULL) {
		*frontRef = source;
		*backRef = NULL;
		return;
    }

	Node *slow = source;
	Node *fast = source->next;

	while (fast != NULL) {
        fast = fast->next;
		if (fast != NULL) {
            slow = slow->next;
			fast = fast->next;
		}
	}

	*frontRef = source;
	*backRef = slow->next;
	slow->next = NULL;
}

void mergeSortLL (Node **head) {
    if (*head == NULL || (*head)->next == NULL)
        return;

    Node *a, *b;
    _frontBackSplit(*head, &a, &b);
    mergeSortLL(&a);
    mergeSortLL(&b);
    *head = _sortedMerge(a, b);
}

#endif // LINKED_LIST_H_INCLUDED

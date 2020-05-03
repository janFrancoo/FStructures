#ifndef HASH_OPEN_ADDRESS_H_INCLUDED
#define HASH_OPEN_ADDRESS_H_INCLUDED

#define MAX_LEN 25
#define TRUE    1
#define FALSE   0
typedef int bool;

enum {
    LINEAR,
    QUADRATIC,
    DOUBLE_HASH
};

typedef struct {
    int key;
    int value;
} TableElement;

typedef struct {
    int maxLen;
    int addressMode;
    int *table;
} HashTable;

void createHashTable(HashTable **hashTable, int max, int mode) {
    if (max == NULL)
        max = MAX_LEN;

    if (mode == NULL)
        mode = LINEAR;
    else if (mode < 0 || mode > 2)
        return;

    (*hashTable) = malloc(sizeof(HashTable));
    (*hashTable)->maxLen = max;
    (*hashTable)->addressMode = mode;
    (*hashTable)->table = malloc(sizeof(int) * max);

    for (int i=0; i<max; i++)
        (*hashTable)->table[i] = NULL;
}

int hashModulo(int max, int key) {
    return key % max;
}

// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
// CAN BE APPLIED A BETTER SOLUTION USING SIEVE METHOD!!!
int generatePrimes(int n) {
    int j, prime;
    for (int i=2; i<n; i++) {
        for (j=2; j<i-1; j++)
            if (i % j == 0) {
                break;
            }
        if (i == (j + 1))
            prime = i;
    }
    return prime;
}

int hashFunc2(int max, int key) {
    int prime = generatePrimes(max);
    return prime - (key % prime);
}

void insert(HashTable **hashTable, int key, int value) {
    if ((*hashTable) == NULL)
        return;

    int idx = hashModulo((*hashTable)->maxLen, key);
    int add = TRUE, newIdx, base;

    TableElement *element = malloc(sizeof(TableElement));
    element->key = key;
    element->value = value;

    if ((*hashTable)->table[idx] == NULL) {
        (*hashTable)->table[idx] = element;
        return;
    }

    switch((*hashTable)->addressMode) {
        case LINEAR: ;
            newIdx = (idx + 1) % (*hashTable)->maxLen;
            while ((*hashTable)->table[newIdx] != NULL) {
                newIdx = (newIdx + 1) % (*hashTable)->maxLen;
                if (newIdx == idx) {
                    add = FALSE;
                    break;
                }
            }
            if (add)
                (*hashTable)->table[newIdx] = element;
            break;
        case QUADRATIC: ;
            base = 1;
            newIdx = (idx + (base * base)) % (*hashTable)->maxLen;
            while ((*hashTable)->table[newIdx] != NULL) {
                base++;
                newIdx = (newIdx + (base * base)) % (*hashTable)->maxLen;
                if (base == (*hashTable)->maxLen) {
                    add = FALSE;
                    break;
                }
            }
            if (add)
                (*hashTable)->table[newIdx] = element;
            break;
        case DOUBLE_HASH: ;
            base = 1;
            newIdx = (idx + (base * hashFunc2((*hashTable)->maxLen, idx))) % (*hashTable)->maxLen;
            while ((*hashTable)->table[newIdx] != NULL) {
                base++;
                newIdx = (newIdx + (base * hashFunc2((*hashTable)->maxLen, idx))) % (*hashTable)->maxLen;
                if (base == (*hashTable)->maxLen) {
                    add = FALSE;
                    break;
                }
            }
            if (add)
                (*hashTable)->table[newIdx] = element;
            break;
    }
}

void printKey (HashTable *hashTable, int key) {
    int idx = hashModulo(hashTable->maxLen, key);
    if (hashTable->table[idx] == NULL)
        printf("[%d] -- ~~\n", idx);
    else
        printf("[%d] -- <%d, %d>\n", idx, ((TableElement*)(hashTable->table[idx]))->key,
               ((TableElement*)(hashTable->table[idx]))->value);
}

void printTable(HashTable *hashTable) {
    for (int i=0; i<hashTable->maxLen; i++) {
        if (hashTable->table[i] == NULL)
            printf("[%d] -- ~~\n", i);
        else {
            TableElement *element = hashTable->table[i];
            printf("[%d] -- <%d, %d>\n", i, element->key, element->value);
        }
    }
    printf("\n");
}

int getValue(HashTable *hashTable, int key) {
    int idx = hashModulo(hashTable->maxLen, key), base;
    TableElement *element = hashTable->table[idx];
    if (TableElement != NULL && element->key == key)
        return element->value;

    int newIdx;
    switch (hashTable->addressMode) {
        case LINEAR: ;
            newIdx = idx + 1;
            while (hashTable->table[newIdx] != NULL) {
                element = hashTable->table[newIdx];
                if (element->key == key)
                    return element->value;
                newIdx = (newIdx + 1) % hashTable->maxLen;
                if (newIdx == idx)
                    break;
            }
            return -1;
            break;
        case QUADRATIC: ;
            base = 1;
            newIdx = idx + (base * base);
            while (hashTable->table[newIdx] != NULL) {
                element = hashTable->table[newIdx];
                if (element->key == key)
                    return element->value;
                base++;
                newIdx = (newIdx + (base * base)) % hashTable->maxLen;
                if (base == hashTable->maxLen)
                    break;
            }
            return -1;
            break;
        case DOUBLE_HASH:
            base = 1;
            newIdx = (idx + (base * hashFunc2(hashTable->table, idx))) % hashTable->maxLen;
            while (hashTable->table[newIdx] != NULL) {
                element = hashTable->table[newIdx];
                if (element->key == key)
                    return element->value;
                base++;
                newIdx = (newIdx + (base * hashFunc2(hashTable->maxLen, newIdx))) % hashTable->maxLen;
                if (base == hashTable->maxLen)
                    break;
            }
            return -1;
            break;
    }
}

void removeKey(HashTable **hashTable, int key, bool removeAll) {
    if (removeAll == NULL || (*hashTable)->addressMode == DOUBLE_HASH)
        removeAll = FALSE;
    int idx = hashModulo((*hashTable)->maxLen, key), base;
    TableElement *element = (*hashTable)->table[idx];
    if (element != NULL && element->key == key)
        (*hashTable)->table[idx] = NULL;
    else {
        int newIdx;
        switch ((*hashTable)->addressMode) {
            case LINEAR: ;
                newIdx = idx + 1;
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key) {
                        (*hashTable)->table[newIdx] = NULL;
                        if (!removeAll)
                            break;
                    }
                    newIdx = (newIdx + 1) % (*hashTable)->maxLen;
                    if (newIdx == idx)
                        break;
                }
                break;
            case QUADRATIC: ;
                base = 1;
                newIdx = idx + (base * base);
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key) {
                        (*hashTable)->table[newIdx] = NULL;
                        if (!removeAll)
                            break;
                    }
                    base++;
                    newIdx = (newIdx + (base * base)) % (*hashTable)->maxLen;
                    if (base == (*hashTable)->maxLen)
                        break;
                }
                break;
            case DOUBLE_HASH:
                base = 1;
                newIdx = (idx + (base * hashFunc2((*hashTable)->maxLen, idx))) % (*hashTable)->maxLen;
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key) {
                        (*hashTable)->table[newIdx] = NULL;
                        if (!removeAll)
                            break;
                    }
                    base++;
                    newIdx = (newIdx + (base * hashFunc2((*hashTable)->maxLen, newIdx))) % (*hashTable)->maxLen;
                    if (base == (*hashTable)->maxLen)
                        break;
                }
                break;
        }
    }
}

void removeValue(HashTable **hashTable, int key, int value) {
    int idx = hashModulo((*hashTable)->maxLen, key), base;
    TableElement *element = (*hashTable)->table[idx];
    if (element != NULL && element->key == key && element->value == value)
        (*hashTable)->table[idx] = NULL;
    else {
        int newIdx;
        switch ((*hashTable)->addressMode) {
            case LINEAR: ;
                newIdx = idx + 1;
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key && element->value == value)
                        (*hashTable)->table[newIdx] = NULL;
                    newIdx = (newIdx + 1) % (*hashTable)->maxLen;
                    if (newIdx == idx)
                        break;
                }
                break;
            case QUADRATIC: ;
                base = 1;
                newIdx = idx + (base * base);
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key && element->value == value)
                        (*hashTable)->table[newIdx] = NULL;
                    base++;
                    newIdx = (newIdx + (base * base)) % (*hashTable)->maxLen;
                    if (base == (*hashTable)->maxLen)
                        break;
                }
                break;
            case DOUBLE_HASH:
                base = 1;
                newIdx = (idx + (base * hashFunc2((*hashTable)->maxLen, idx))) % (*hashTable)->maxLen;
                while ((*hashTable)->table[newIdx] != NULL) {
                    element = (*hashTable)->table[newIdx];
                    if (element->key == key && element->value == value)
                        (*hashTable)->table[newIdx] = NULL;
                    base++;
                    newIdx = (newIdx + (base * hashFunc2((*hashTable)->maxLen, newIdx))) % (*hashTable)->maxLen;
                    if (base == (*hashTable)->maxLen)
                        break;
                }
                break;
        }
    }
}

void clearTable (HashTable **hashTable) {
    for (int i=0; i<(*hashTable)->maxLen; i++)
        (*hashTable)->table[i] = NULL;
}

#endif // HASHING_OPEN_ADDRESSING_H_INCLUDED

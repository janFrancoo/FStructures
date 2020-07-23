#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

int main()
{
    Node *root = getNode();

    char words[][15] = {"jan", "jane", "janfranco", "janefranco", "janfrancocom"};
    for (int i=0; i<5; i++)
        insert(root, words[i]);

    char printWord[15];
    printTrie(root, printWord, 0);

    printf("--------\n");

    getSuggestions(root, words[0]);

    return 0;
}

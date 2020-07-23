#include <stdio.h>
#include <stdlib.h>

#include "trie.h"

int main()
{
    Node *root = getNode();

    char words[][15] = {"jan", "jane", "janfranco", "janefranco", "janfrancocom"};
    for (int i=0; i<5; i++)
        insert(root, words[i]);

    /*char printWord[15];
    printTrie(root, printWord, 0);

    printf("--------\n");*/

    int idx = 0;
    char c;
    char *word = malloc(sizeof(char) * 1);
    while ((int) c != 13) {
        c = getch();
        word[idx] = c;
        idx++;
        word[idx] = '\0';
        printf("%s\n", word);
        word = realloc(word, sizeof(char) * (idx + 1));
        printf("-------\n");
        getSuggestions(root, word);
    }

    return 0;
}

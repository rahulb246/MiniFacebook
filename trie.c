#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "trie.h"

Trie *createTrieNode()
{
    Trie *node = malloc(sizeof(Trie));
    assert(node!=NULL);
    node->isEOW = false;
    node->index = -1;
    int i;
    for(i=0; i<ALPHABET_SIZE; i++)
        node->next[i] = NULL;
    return node;
}

Trie *createTrie()
{
    return createTrieNode();
}

int addPersonToTrie(Trie *trie, char personName[], int index)
{
    int i = 0 ;
    while(personName[i]!='\0')
    {
        assert(isalpha(personName[i]));
        int idx = tolower(personName[i]) - 'a';
        if(trie->next[idx]==NULL)
            trie->next[idx] = createTrieNode();
        trie = trie->next[idx];
        i++;
    }
    trie->isEOW = true;
    if(trie->index == -1)
        trie->index = index;

    return trie->index;
}

int getPersonIndexFromTrie(Trie *trie, char *personName)
{
    int i;
    for(i=0; personName[i]!='\0'; i++)
    {
        if(!isalpha(personName[i]))
            return -1;
        int idx = tolower(personName[i])-'a';
        if(trie->next[idx]== NULL)
            return -1;
        trie = trie->next[idx];
    }

    if(trie->isEOW==false)
        return -1;

    return trie->index;
}

bool hasPersonInTrie(Trie *trie, char *personName)
{
    return getPersonIndexFromTrie(trie, personName)!=-1;
}

/*

    TRIE IMPLEMENTATION
    COPYRIGHT - BEING ZERO PVT LTD
	info@beingzero.in
*/

#ifndef TRIE_H_INCLUDED
#define TRIE_H_INCLUDED

#define     ALPHABET_SIZE   26

#include <stdbool.h>

typedef struct trie Trie;
struct trie
{
    bool isEOW;
    int index;
    Trie *next[ALPHABET_SIZE];
};

// CREATE TRIE
Trie *createTrie();

// INSERT PERSON NAME INTO TRIE
int addPersonToTrie(Trie *trie, char personName[], int index);

// GET INDEX OF PERSON NAME
int getPersonIndexFromTrie(Trie *trie, char *personName);

// CHECK PRESENCE OF PERSON
bool hasPersonInTrie(Trie *trie, char *personName);

#endif // TRIE_H_INCLUDED

#include "socialnetwork.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int capacity = 2;
int personCount = 0;

void allocateArrays()
{
    int i,j;
    personNames = malloc(capacity*sizeof(char*));
    assert(personNames!=NULL);
    relationship = malloc(capacity*sizeof(char*));
    assert(relationship!=NULL);
    for(i=0; i<capacity; i++)
    {
        relationship[i] = malloc((i+1)*sizeof(char));
        assert(relationship[i]!=NULL);
        for(j=0; j<=i; j++)
            relationship[i][j] = 0;
    }
}

void reallocateArrays()
{
    int i,j, oldCapacity;
    oldCapacity = capacity;
    capacity = 2*capacity;

    personNames = realloc(personNames, capacity*sizeof(char*));
    assert(personNames!=NULL);

    relationship = realloc(relationship, capacity*sizeof(char*));
    assert(relationship!=NULL);

    for(i=oldCapacity; i<capacity; i++)
    {
        relationship[i] = malloc((i+1)*sizeof(char));
        assert(relationship[i]!=NULL);
        for(j=0; j<=i; j++)
            relationship[i][j] = 0;
    }
}

#include <stdio.h>
#include <stdlib.h>
#include "socialnetwork.h"
#include "trie.h"
#include <string.h>
#include <assert.h>
#include <limits.h>
extern int personCount;
extern int capacity;
Trie *trie= NULL;
int showMenu()
{
    int choice;
    printf("\nMENU");
    printf("\n====");
    printf("\n1. Add Friendship");
    printf("\n2. List friends");
    printf("\n3. Mutual Friends");
    printf("\n4. Print Stats");
    printf("\n5. Friendship path");
    printf("\n6. Exit");
    printf("\nEnter choice : ");
    scanf("%d",&choice);
    return choice;
}
void addPerson(char name[])
{
    int idx = getPersonIndexFromTrie(trie, name);
    if(idx!=-1)
        return;
    addPersonToTrie(trie, name, personCount);
    if(personCount==capacity-1)
        reallocateArrays();
    personNames[personCount] = malloc(strlen(name)+1);
    strcpy(personNames[personCount],name);
    personCount++;
    printf("\nAdded '%s'",name);
}

void addFriendship(char name1[],char name2[])
{
    addPerson(name1);
    addPerson(name2);

    int x = getPersonIndexFromTrie(trie, name1);
    int y = getPersonIndexFromTrie(trie, name2);

    if(x>y)
        relationship[x][y] = 1;
    else
        relationship[y][x] = 1;

    printf("\n '%s' & '%s' are friends now...",name1,name2);
}

char getRelationship(int i, int j)
{
    if ( i > j )
        return relationship[i][j];
    else
        return relationship[j][i];
}

void listFriends(char name[])
{
    printf("\nFriends of %s are : ",name);
    int idx = getPersonIndexFromTrie(trie, name);

    int i;
    for(i=0;i<personCount;i++)
        if(getRelationship(idx, i)==1)
            printf("%s ", personNames[i]);
}

void mutualFriends( char name1[],char name2[])
{
    printf("\nMutual friends of %s and %s are : ",name1,name2);
    int idx1 = getPersonIndexFromTrie(trie,name1);
    int idx2 = getPersonIndexFromTrie(trie,name2);
    int i=0;
    for(i=0;i<personCount;i++)
        if(getRelationship(idx1,i)==1 && getRelationship(idx2,i)==1)
            printf("'%s' ",personNames[i]);
}

void printStats()
{
    int maxIdx=0,maxCount=0,i,j,micount=INT_MAX,macount=0;
    int minIdx=0, minCount=0;
    for(i=0;i<personCount;i++)
    {
        for(j=0;j<personCount;j++)
        {
            if(getRelationship(i,j)==1)
            {
                maxCount++;
                minCount++;
            }
        }
        if(micount > minCount)
        {
            micount=minCount;
            minIdx=i;
        }
        if(macount < maxCount)
        {
            macount = maxCount;
            maxIdx=i;
        }
    }
    printf("\nMost connected person %s, Friends %d",personNames[maxIdx],maxCount);
    printf("\nLeast connected person %s, Friends %d",personNames[minIdx],minCount);


}

void printPathRecursive(char s[],char d[],char visited[],char path[])
{
    int idx=getPersonIndexFromTrie(trie,s);
    int len=strlen(path);
    if(visited[idx])
        return;
    char *np=malloc(len+2+strlen(s));
    if(len==0)
        sprintf(np,"%s",s);
    else
        sprintf(np,"%s>%s",path,s);
    if(strcmp(s,d)==0)
    {
        printf("\n%s",np);
        return;
    }

    visited[idx]=true;
    int i;
    for(i=0; i<personCount; i++)
    {
        if(getRelationship(idx,i))
                printPathRecursive(personNames[i],d,visited,path);
    }
    visited[idx]=false;
}

void printPath(char s[], char d[])
{
    printf("\nPath between %s and %s: ", s, d);
     bool visited[personCount];
     int i;
    for(i=0; i<personCount; i++)
        visited[i] = false;
    printPathRecursive(s,d,visited,"");
}

int main()
{

    int choice;
    char name1[50],name2[50];
    trie=createTrie();
    allocateArrays();


    FILE *fp=fopen("friendship.txt","r");

    while (!feof(fp))
    {
        fscanf(fp,"%s %s",name1,name2);
        addFriendship(name1,name2);
    }
    fclose(fp);



    while (1)
    {
        choice=showMenu();
        switch(choice)
        {
        case 1:
            printf("\nEnter First Name : ");
            scanf("%s",name1);
            printf("\nEnter Second Name : ");
            scanf("%s",name2);
            addFriendship(name1,name2);
            break;
        case 2:
            printf("\nEnter Name : ");
            scanf("%s",name1);
            listFriends(name1);
            break;
        case 3:
            printf("\nEnter First Name : ");
            scanf("%s",name1);
            printf("\nEnter Second Name : ");
            scanf("%s",name2);
            mutualFriends(name1,name2);
            break;
        case 4:
            printStats();
            break;
        case 5:
            printf("\nEnter First Name : ");
            scanf("%s",name1);
            printf("\nEnter Second Name : ");
            scanf("%s",name2);
            printPath(name1,name2);
            break;
        case 6:
            return 0;
        default :
            printf("\nBAD choice, try again...");
        }
    }
    return 0;
}

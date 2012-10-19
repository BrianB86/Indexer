#ifndef SORTED_LIST_H
#define SORTED_LIST_H
/*
 * sorted-list.h
 */

#include <stdlib.h>

typedef int (*CompareFuncT)(void *, void *);

struct Node
{
	struct Node* next;
	void * object;
};
typedef struct Node* NodePtr;

struct SortedList
{
	NodePtr head;
	CompareFuncT funct;
};
typedef struct SortedList* SortedListPtr;

struct SortedListIterator
{
	NodePtr curr;
	NodePtr prev;
};
typedef struct SortedListIterator* SortedListIteratorPtr;


SortedListPtr SLCreate(CompareFuncT cf);

void SLDestroy(SortedListPtr list);

int SLInsert(SortedListPtr list, void *newObj);

int SLRemove(SortedListPtr list, void *newObj);

SortedListIteratorPtr SLCreateIterator(SortedListPtr list);

void SLDestroyIterator(SortedListIteratorPtr iter);

void *SLNextItem(SortedListIteratorPtr iter);

#endif

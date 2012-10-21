#ifndef INDEXER_H
#define INDEXER_H
/*
 * indexer.h
 */

#include <stdlib.h>
#include "sorted-list.h"

int compareWords(void* word1, void * word2);
int compareFiles(void* word1, void * word2);

struct fileNode
{
	char *fileName;
	int wordCount;
};
typedef struct fileNode* fileNPtr;

struct wordNode
{
	char * wordName;
	SortedListPtr fileList;
};
typedef struct wordNode* wordNPtr;

int compareWords(void * word1, void * word2);

#endif

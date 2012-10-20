#ifndef INDEXER_H
#define INDEXER_H
/*
 * indexer.h
 */

#include <stdlib.h>

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

int compareWords(wordNPtr word1, wordNPtr word2);



#endif

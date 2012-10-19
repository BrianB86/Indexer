#ifndef INDEXER_H
#define INDEXER_H
/*
 * indexer.h
 */

#include <stdlib.h>

struct file
{
	char *fileName;
	int wordCount;
};
typedef struct file* filePtr;

struct word
{
	char * word;
	filePtr file;
};
typedef struct word* wordPtr;

int compareWords(wordPtr word1, wordPtr word2);

#endif

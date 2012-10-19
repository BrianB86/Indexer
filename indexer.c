/* Coded by Brian Battell, Lara Martin, and Elana Braff*/

/* indexer.c*/
#include	<string.h>
#include	<stdio.h>
#include	"indexer.h"
#include	"tokenizer.h"
#include	"sorted-list.h"



int compareWords(wordPtr word1, wordPtr word2)
{
	return strcmp(word1->word, word2->word);
}

int main(int argc, char ** argv)
{
	TokenizerT * tk;
	char* token = NULL;
	if (argc != 3)
	{
		printf("Invalid number of arguments.\n");
		return -1;
	}
	/*dest is arg[1]*/
	/*source files are arg[2]*/
	
	walkDir(argv[2]);
	/*tk = run(argv[2]);*/
	/*token = TKGetNextToken(tk);
	while(token!= NULL) {
		printf("%s\n", token);
		free(token);
		token = TKGetNextToken(tk);
	}*/
	TKDestroy(tk);
	
	return 0;
}

SortedListPtr setSortedList(TokenizerT * tk, SortedListPtr sl)
{
	int i;
	if (sl == NULL)
	{
			for (i = 0; i < 
	}
}


int walkDir(char* name){ //take in SL also
	DIR* dr =opendir(name);
	struct dirent *fname;
	char* newPath;
	if(!dr){
		return 0;
		}
	while ((fname=readdir(dr))!=NULL){
		if(fname->d_name[0]=='.'){
			continue;
		}
		else if(fname->d_type==DT_DIR){
			printf("DirName: %s\n", fname->d_name);
			newPath=(char*)malloc(strlen(name)+strlen(fname->d_name)+1);
			sprintf(newPath, "%s/%s", name, fname->d_name);
			walkDir(newPath); //Pass SL
			free(newPath);
		}else if(fname->d_type==DT_REG){
			printf("FileName: %s\n", fname->d_name);
			newPath=(char*)malloc(strlen(name)+strlen(fname->d_name)+1);
			sprintf(newPath, "%s/%s", name, fname->d_name); // add full path to file name and pass to tokenizer
			// Tokenize and add words to list
			free(newPath);
		}
		
	}
	closedir(dr);
	return 1;
}


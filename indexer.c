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
	DIR* dr;
	struct stat statbuf;
	struct dirent *fname;
	char* newPath;
	
	if(stat(name,&statbuf)==-1){
		printf("Error accessing file or Directory %s\n",name);
		return -1;
	}

	if(S_ISDIR(statbuf.st_mode)){
		dr =opendir(name);
		if(!dr){
			printf("Cannot open Directory %s\n",name);
			return -1;
		}
		printf("DirName: %s\n", name);
		while ((fname=readdir(dr))!=NULL){
			if(fname->d_name[0]=='.'){ 			/*---------- Skips hidden fies and '.' '..' Directorys */
				continue;
			}
			else{
				newPath=(char*)malloc(strlen(name)
				+strlen(fname->d_name)+1);   
				sprintf(newPath, "%s/%s", name, fname->d_name);
				walkDir(newPath); //Pass SL also
				free(newPath);
			}
		}
	}
	else if(S_ISREG(statbuf.st_mode)){
			printf("FileName: %s\n", name);
			// Tokenize and add words to list	
	}
	
	return 1;
}


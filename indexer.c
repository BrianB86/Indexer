/* Coded by Brian Battell, Lara Martin, and Elana Braff*/

/* indexer.c*/

#include	<string.h>
#include	<stdio.h>
#include	<dirent.h>
#include	<sys/stat.h>
#include	"indexer.h"
#include	"sorted-list.h"
#include	"tokenizer.h"

SortedListPtr globalList;

int compareWords(void* word1, void * word2)
{
	/*comparing to itself???*/
	wordNPtr w1, w2;
	char *s1, *s2;
	w1 = (wordNPtr)word1;
	w2 = (wordNPtr)word2;	
	s1 = w1->wordName;
	s2 = w2->wordName;
	
	return strcmp(s1, s2);
}

int compareStrings(void *p1, void *p2)
{
	char *s1 = p1;
	char *s2 = p2;

	return strcmp(s1, s2);
}

/*SortedListPtr setSortedList(TokenizerT * tk, SortedListPtr sl)
{
	int i;
	if (sl == NULL)
	{
			for (i = 0; i < 
	}
}*/

int walkDir(char* name){ /*---------------------------------take in SL also*/
	DIR* dr;
	struct stat statbuf;
	struct dirent *fname;
	char* newPath;
	char* token;
	TokenizerT * tk;
	
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
			if(fname->d_name[0]=='.'){ 	/*-------------------Skips hidden fies and '.' '..' Directorys */
				continue;
			}
			else{
				newPath=(char*)malloc(strlen(name)
				+strlen(fname->d_name)+1);   
				sprintf(newPath, "%s/%s", name, fname->d_name);
				walkDir(newPath); /*-------------------------Pass SL also*/
				free(newPath);
			}
		}
	}
	else if(S_ISREG(statbuf.st_mode)){
			printf("FileName: %s\n", name);
			/*Tokenize and add words to list*/
			tk = run(name);
			token = TKGetNextToken(tk);
			while(token!= NULL) {
				free(token);
				token = TKGetNextToken(tk);
				SLInsert(globalList, token);
			}
	}
	
	return 1;
}

int main(int argc, char** argv)
{
	NodePtr curr;
	
	if (argc != 3)
	{
		printf("Invalid number of arguments.\n");
		return -1;
	}
	/*dest is arg[1]*/
	/*source files are arg[2]*/
	
	globalList = SLCreate(compareWords);
	
	walkDir(argv[2]);
	curr = globalList->head;
	while(curr != NULL) /*prints the list*/
		{
			printf("LIST %d\n",*((int *)curr->object));
			curr = curr->next;
		}
	/*TKDestroy(tk);*/
	
	return 0;
}

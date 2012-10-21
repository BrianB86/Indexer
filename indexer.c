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
	int i;
	wordNPtr w1, w2;
	char *s1, *s2;
	w1 = (wordNPtr)word1;
	w2 = (wordNPtr)word2;
	s1 = w1->wordName;
	/*printf("word1: %s\n",s1);*/
	s2 = w2->wordName;
	/*printf("word2: %s\n",s2);*/

	i =strcmp(s1, s2);
	return i;

}

int compareFiles(void* word1, void * word2)
{
	int i;
	fileNPtr w1, w2;
	char *s1, *s2;
	w1 = (fileNPtr)word1;
	w2 = (fileNPtr)word2;
	s1 = w1->fileName;
	/*printf("word1: %s\n",s1);*/
	s2 = w2->fileName;	
	/*printf("word2: %s\n",s2);*/
	i =strcmp(s1, s2);
	return i;

}

int walkDir(char* name){ /*---------------------------------take in SL also*/
	DIR* dr;
	struct stat statbuf;
	struct dirent *fname;
	char* newPath;
	char* token;
	char* temp;
	wordNPtr wNode;
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
			if(fname->d_name[0]=='.' || fname->d_name[strlen(fname->d_name)-1]=='~'){ 	/*-------------------Skips hidden fies and '.' '..' Directories */
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
				temp = (char*)malloc(strlen(token));
				strcpy(temp,token);
				wNode = (wordNPtr)malloc(sizeof(struct wordNode));
				wNode->wordName = temp;
				temp = (char*)malloc(strlen(name));
				strcpy(temp,name);
				SLInsert(globalList, wNode, temp);
				free(token);
				token = TKGetNextToken(tk);
			}
	}

	return 1;
}

int main(int argc, char** argv)
{
	NodePtr curr;
	wordNPtr word;

	NodePtr flist;
	fileNPtr file;


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
			word=(wordNPtr)curr->object;
			printf("LIST %s\n",(char*)word->wordName);
			
			flist = word->fileList->head;
			while(flist!=NULL){
				file= (fileNPtr)flist->object;
				printf("FILE: %s NUM %i\n",file->fileName,file->wordCount);
				flist = flist->next;
				
				}
			curr = curr->next;
		}
	/*TKDestroy(tk);*/
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"

int main(int argc, char *argv[]) 
{	
	/*Deklarasi Variable*/
	String text = "";
	char word[40];
	char arr[1][40];
	addr stopword = NULL;
	addrStat treeOfWord = NULL;
	int i;
	
	/* Start Program*/
	getStopwords(&stopword);
	
	for(i = 0; i < 1; i++){
		printf("Nama File %d : ", i+1);	scanf("%s", arr[i]);
	}
	
	for(i = 0; i < 1; i++){
		printf("%s\n", arr[i]);
		text = "";
		text = caseFolding(text, arr[i]);
		//printf("%s\n", text);
		//text = StemString(text);
		Tokenizing(text, i+1, stopword, &treeOfWord);
	}
	
	printf("Akhir : \n");
	InorderStat(treeOfWord); printf("\n");
	
	system("pause");	
	return 0;
}

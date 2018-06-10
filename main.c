#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"

int main(int argc, char *argv[]) 
{	
	/* Uji Case Folding */
	char location[50] = "test.txt";
	String text = "";
	String arr[4];
	addr stopword = NULL;
	addrStat treeOfWord = NULL;
	text = caseFolding(text, location);
	
	printf("%s\n\n", text);
	
	getStopwords(&stopword);
	
	//PrintInorder(stopword);	printf("\n");
	
	treeOfWord = Tokenizing(text, 1);
	printf("\n");
	InorderStat(treeOfWord); printf("\n");
	
	system("pause");	
	return 0;
}

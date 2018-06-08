#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"
#include "lib/AVL/Tree.h"
#include "lib/Statistik/Statistik.h"

int main(int argc, char *argv[]) 
{	
	/* Uji Cast Folding
	char location[50] = "test.txt";
	String text = "";
	text = caseFolding(text, location);
	
	printf("%s\n", text);
	*/
	
	/* Uji AVL Khusus Stopword
	addr root = NULL;
	infotype info;
	char text[40];
	int i = 0;
	
	for(i = 0; i < 4; i++){
		printf("Nama %d :", i);	scanf("%s", &text);
		strcpy(info,text);
		AVLTree(&root, info);
	}
	
	PrintInorder(root); printf("\n");
	*/
	
	addrStat root = NULL;
	StatData info;
	char text[40];
	int i = 0;
	
	for(i = 0; i < 4; i++){
		printf("Nama %d :", i);	scanf("%s", &text);
		strcpy(info.kata,text);
		AddStat(&root, info.kata, 1);
	}
	
	InorderStat(root); printf("\n");
	
	system("pause");	
	return 0;
}

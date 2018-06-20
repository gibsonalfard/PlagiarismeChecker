#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"

int main(int argc, char *argv[]) 
{	
	/*Deklarasi Variable*/
	String text = "";
	char word[40];
	char arr[1][40];
	addrStat treeOfWord = NULL;
	int i, choice, n; 
	addr stopword = NULL;
	addr kataDasar = NULL;
	char ENG[] = "File/stopwordEN.txt";
	char IND[] = "File/stopwordID.txt";
	char ENGWords[] = "File/KataDasarEN.txt";
//	char INDWords[] = "File/KataDasarID.txt";
	
	/* Start Program*/	
	printf("1. Bahasa Indonesia\n");
	printf("2. Bahasa Inggris\n");
	printf("\nPilih bahasa: "); scanf("%d", &choice);
	
	switch(choice){
		case 1: 
				getStopwords(&stopword, IND);
//				getKataDasar(&kataDasar, INDWords);
				printf("Masukan jumlah file yang akan dibandingkan: "); scanf("%d", &n);
		break;
		case 2:
				getStopwords(&stopword, ENG);
				getKataDasar(&kataDasar, ENGWords);
				printf("Enter amount of file that will be compared: "); scanf("%d", &n);
		break;
	}
	
	for(i = 0; i < n; i++){
		printf("Nama File %d : ", i+1);	scanf("%s", arr[i]);
	}
	
	for(i = 0; i < n; i++){
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

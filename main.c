#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"

void banner(){
	printf("         ================================================================\n");
	printf("\n                         PROGRAM PEMERIKSA PLAGIARISME\n");
	printf("\n         ================================================================\n");
}

int main(int argc, char *argv[]) 
{	
	/*Deklarasi Variable*/
	String text = "";
	char word[40];
	addrStat treeOfWord = NULL;
	int i, choice, n; 
	addr stopword = NULL;
	addr kataDasar = NULL;
	Queue similar;
	char arr[n][40];
	char ENG[] = "File/stopwordEN.txt";
	char IND[] = "File/stopwordID.txt";
	char ENGWords[] = "File/KataDasarEN.txt";
//	char INDWords[] = "File/KataDasarID.txt";
	
	CreateQueue(&similar);
	
	/* Start Program*/
	banner();
	printf("\n         1. Bahasa Indonesia\n");
	printf("\n         2. Bahasa Inggris\n");
	printf("\n         Pilih bahasa: "); scanf("%d", &choice);
	
	switch(choice){
		case 1: 
				system("cls");
				banner();
				getStopwords(&stopword, IND);
//				getBasicWords(&kataDasar, INDWords);
				printf("\n         Masukan jumlah file yang akan dibandingkan: "); scanf("%d", &n);
				for(i = 0; i < n; i++){
					printf("Nama File %d : ", i+1);	scanf("%s", arr[i]);
				}
		break;
		case 2:
				system("cls");
				banner();
				getStopwords(&stopword, ENG);
				getBasicWords(&kataDasar, ENGWords);
				printf("\n         Enter amount of file that will be compared: "); scanf("%d", &n);
				system("cls");
				banner();
				for(i = 0; i < n; i++){
					printf("\n         File Name %d : ", i+1);	scanf("%s", arr[i]);
				}
		break;
	}
	
	for(i = 0; i < n; i++){
		//printf("%s\n", arr[i]);
		text = "";
		text = caseFolding(text, arr[i]);
		Tokenizing(text, i+1, stopword, kataDasar, &treeOfWord);
	}
	
	//printf("Akhir : \n");
	//InorderStat(treeOfWord, n); printf("\n");
	system("cls");
	banner();
	similar = getSimilarityList(treeOfWord, n);
	printf("\n         Akhir : \n");
	printResult(similar, arr);
	
	system("pause");	
	return 0;
}

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
	char* teks = "";
	char ENG[] = "File/stopwordEN.txt";
	char IND[] = "File/stopwordID.txt";
	char ENGWords[] = "File/KataDasarEN.txt";
//	char INDWords[] = "File/KataDasarID.txt";
	
	//CreateQueue(&similar);
	
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
				system("cls");
				banner();
				teks = "\n         Nama File";
		break;
		case 2:
				system("cls");
				banner();
				getStopwords(&stopword, ENG);
				getBasicWords(&kataDasar, ENGWords);
				printf("\n         Enter amount of file that will be compared: "); scanf("%d", &n);
				system("cls");
				banner();
				teks = "\n         File Name";
		break;
	}
	char arr[n][40];
	for(i = 0; i < n; i++){
		printf("%s %d : ", teks,i+1);	scanf("%s", arr[i]);
	}
	
	for(i = 0; i < n; i++){
		//printf("%s\n", arr[i]);
		text = "";
		text = caseFolding(text, arr[i]);
		Tokenizing(text, i+1, stopword, kataDasar, &treeOfWord);
	}
	
	//printf("Akhir : \n");
	//InorderStat(treeOfWord, n); printf("\n");
	//system("pause");
	system("cls");
	banner();
	similar = getSimilarityList(treeOfWord, n);
	printResult(similar, arr);
		
	system("pause");	
	return 0;
}

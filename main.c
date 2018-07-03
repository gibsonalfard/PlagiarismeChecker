#include <stdio.h>
#include <stdlib.h>

#include "lib/Function/Function.h"
/*
void goAnotherFile(){
	FILE *F;
	FILE *T;
	F = fopen("File/daftarKataDasar.txt", "r");
	T = fopen("File/KataDasarID.txt", "a");
	
	int c;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		if(c == 32){
			word = concatLetter(word,(char)10);
			fprintf(T,word);
			word="";
		}else{
			word = concatLetter(word,(char)c);
		}
	}
	fclose(F);
	fclose(T);
}*/

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
	int i, n;
	addr stopword = NULL;
	addr kataDasar = NULL;
	Queue similar;
	String teks = "";
	String errorMsg = "";
	char ENG[] = "File/stopwordEN.txt";
	char IND[] = "File/stopwordID.txt";
	char ENGWords[] = "File/KataDasarEN.txt";
	char INDWords[] = "File/KataDasarID.txt";
	
	CreateQueue(&similar);
	CreateStemDictionary();
	
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
				getBasicWords(&kataDasar, INDWords);
				printf("\n         Masukan jumlah file yang akan dibandingkan: "); scanf("%d", &n);
<<<<<<< HEAD
				system("cls");
				banner();
				teks = "\n         Nama File";
=======
				teks = "\tNama File";
				errorMsg = "Maaf, Dokumen tidak dapat ditemukan";
>>>>>>> 55149dd9096b88a61677ec5e0b69e4a1bc174495
		break;
		case 2:
				system("cls");
				banner();
				getStopwords(&stopword, ENG);
				getBasicWords(&kataDasar, ENGWords);
				printf("\n         Enter amount of file that will be compared: "); scanf("%d", &n);
				system("cls");
				banner();
<<<<<<< HEAD
				teks = "\n         File Name";
=======
				teks = "\tFile Name";
				errorMsg = "Sorry, Document cannot be found";
>>>>>>> 55149dd9096b88a61677ec5e0b69e4a1bc174495
		break;
	}
	char arr[n][40];
	i = 0;
	while(i < n){
		printf("%s %d : ", teks,i+1);	scanf("%s", arr[i]);
		
		if(!isDocumentExist(arr[i])){
			printf("\t%s\n\t", errorMsg);
			system("pause");
		}else{
			i++;
		}
	}
	
	for(i = 0; i < n; i++){
		//printf("%s\n", arr[i]);
		text = "";
		text = caseFolding(text, arr[i]);
		Tokenizing(text, i+1, stopword, kataDasar, &treeOfWord);
	}
	
	printf("Akhir : \n");
	InorderStat(treeOfWord, n); printf("\n");
	system("pause");
	system("cls");
	banner();
	similar = getSimilarityList(treeOfWord, n);
	printResult(similar, arr);
		
	system("pause");	
	return 0;
}

#include "Function.h"

String caseFolding(String text, char *location){	
	FILE *F;
	location = concatWord("Storage/",location);
	F = fopen(location, "r");
	int c, i;
	char letter;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		//Pengecekan tanda baca menggunakan kode ASCII
		if((c > 64 && c < 91) || (c > 96 && c < 123) || c == 32 || c == 10){
			letter = tolower((char)c);
			word = concatLetter(word, letter);
		}
	}
	//Penanda akhir pada string
	word = concatLetter(word, ' ');
	if(strlen(word) > 0){
		text = concatWord(text, word);
	}
	
	fclose(F);
	return text;
}

void getStopwords(addr *T, char *namaFile){
	FILE *F;
	F = fopen(namaFile, "r");
	
	int c;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		if(c == 10){
			AVLTree(&(*T), word);
			word="";
		}else{
			word = concatLetter(word,(char)c);
		}
	}
	
	fclose(F);
}

void getKataDasar(addr *T, char *namaFile){
	FILE *F;
	F = fopen(namaFile, "r");
	
	int c;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		if(c == 10){
			AVLTree(&(*T), word);
			word="";
		}else{
			word = concatLetter(word,(char)c);
		}
	}
	
	fclose(F);
}

void Tokenizing(String text, int doc, addr stop, addrStat *root){
	int n = strlen(text), i;
	String word = "";
	StatData info;
	
	for(i = 0; i < n; i++){
		if(text[i] == 32 || text[i] == 10 && strlen(word) != 0){
			if(!isStopword(word, stop)){
				word[stem(word, 0, strlen(word)-1) + 1] = 0;
				AddStat(&(*root), word, doc);
			}
			word = "";
			//printf("Tokening\n");
			//InorderStat(root); printf("\n");
			//PreorderStat(root); printf("\n\n");
			//system("pause");
		}else {
			word = concatLetter(word, text[i]);
		}
	}
}


bool isStopword(String word, addr stopword){
	return searchNode(stopword, word) != NULL;
}

String StemString(String text){
	int n = strlen(text), i;
	String word = "";
	String finalWord = "";
	
	for(i = 0; i < n; i++){
		if(text[i] == 32 || text[i] == 10){
			//printf("Word : %s %d\t", word, strlen(word));
			word[stem(word, 0, strlen(word)-1) + 1] = 0;
			//printf("Word : %s %d\n", word, strlen(word));
			finalWord = concatWord(finalWord, word);
			finalWord = concatLetter(finalWord, ' ');
			word = "";
		}else {
			word = concatLetter(word, text[i]);
		}
	}
	//printf("Kotak Masih ada : %s", finalWord);
	return finalWord;
}

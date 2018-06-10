#include "Function.h"

String caseFolding(String text, char *location){	
	FILE *F;
	location = concatWord("File/",location);
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

void getStopwords(addr *T){
	FILE *F;
	F = fopen("File/stopwordEN.txt", "r");
	
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

addrStat Tokenizing(String text, int doc){
	int n = strlen(text), i;
	String word = "";
	StatData info;
	addrStat root = NULL;
	
	for(i = 0; i < n; i++){
		if(text[i] == 32 || text[i] == 10){
			AddStat(&root, word, doc);
			word = "";
		}else {
			word = concatLetter(word, text[i]);
		}
		
	}
	return root;
}

//bool isStopword(String word){
//		
//}

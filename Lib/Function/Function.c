#include "Function.h"

String caseFolding(String text, char *location){	
	FILE *F;
	location = concatWord("lib/File/",location);
	F = fopen(location, "r");
	int c, i;
	char letter;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		//Pengecekan tanda baca menggunakan kode ASCII
		if((c > 64 && c < 91) || (c > 96 && c < 123) || c == 32){
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
	F = fopen("lib/File/stopword.txt", "r");
	
	int c;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		if(c == 10){
			AVLTree(&(*T), word);
			//printf("%s\n", word);
			word="";
		}else{
			word = concatLetter(word,(char)c);
		}
	}
	
	fclose(F);
}

addrStat Tokenizing(String text, int doc, addrStat root){
	int n = strlen(text), i;
	String word = "";
	StatData info;
	for(i = 0; i < n; i++){
		if(text[i] == 32){
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

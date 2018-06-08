#include "Function.h"

String caseFolding(String text, char *location){	
	FILE *F;
	F = fopen(location, "r");
	int c, i;
	char letter;
	String word = "";
	
	while((c = fgetc(F)) != EOF){
		//Pengecekan tanda baca menggunakan kode ASCII
		if((c > 64 && c < 91 || c > 96 && c < 123) || c == 32){
			letter = tolower((char)c);
			//Pengecekan spasi
			/* Ini kayanya gak terlalu perlu tay
			if(c == 32){
				word = concatLetter(word, ' ');
				text = concatWord(text, word);
			}*/
			word = concatLetter(word, letter);
		}
	}
	
	if(strlen(word) > 0){
		text = concatWord(text, word);
	}
	
	fclose(F);
	return text;
}

#include "Function.h"

String caseFolding(String text, char *location){	
	FILE *F;
	F = fopen(location, "r");
	int c, i;
	char letter;
	String word;
	
	while((c = fgetc(F)) != EOF){
		//Pengecekan tanda baca menggunakan kode ASCII
		if((c > 64 && c < 91 && c > 96 && c < 123) || c == 32){
			letter = tolower((char)c);
			//Pengecekan spasi
			if(c == 32){
				concatLetter(word, ' ');
				concatWord(text, word);
			}
			concatLetter(word, letter);	
		}
	}
	
	fclose(F);
	return text;
}

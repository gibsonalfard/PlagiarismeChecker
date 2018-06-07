#include "String.h"

String concatWord(String first, String last){
	String new_str;
	
	if((new_str = malloc(strlen(first) + strlen(last) + 1)) != NULL){
		new_str[0] = '\0';
		strcat(new_str, first);
		strcat(new_str, last);
	}
	
	return new_str;
}

String concatLetter(String base, char add){
	String str = base;
	
	size_t len = strlen(str);
	String str2 = malloc(len + 1 + 1);
	strcpy(str2, str);
	str2[len] = add;
	str2[len + 1] = '\0';
	
	return str2;
}

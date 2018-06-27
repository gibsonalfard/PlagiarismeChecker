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

void getBasicWords(addr *T, char *namaFile){
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

void Tokenizing(String text, int doc, addr stop, addr dasar, addrStat *root){
	int n = strlen(text), i;
	String word = "";
	StatData info;
	
	for(i = 0; i < n; i++){
		if(text[i] == 32 || text[i] == 10 && strlen(word) != 0){
			if(!isStopword(word, stop)){
				if(!isBasicWord(word, dasar) && strlen(word) > 1){
					word[stem(word, 0, strlen(word)-1) + 1] = 0;	
				}
				AddStat(&(*root), word, doc);
			}
			word = "";
		}else {
			word = concatLetter(word, text[i]);
		}
	}
}


bool isStopword(String word, addr stopword){
	return searchNode(stopword, word) != NULL;
}

bool isBasicWord(String word, addr basic){
	return searchNode(basic, word) != NULL;
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

Queue getSimilarityList(addrStat statistik, int numOfDocs){
	records info;
	Queue Q;
	int rows,cols;
	char* label = "";
	
	CreateQueue(&Q);
	
	for(rows = 0; rows < numOfDocs-1; rows++){
		for(cols = rows+1; cols < numOfDocs; cols++){
			int index[2] = {rows, cols};
			int total[2] = {0,0};

			//getTotal(statistik, index, total);
			
			label = concatLetter(label, (char)(rows+48));
			label = concatLetter(label, '-');
			label = concatLetter(label, (char)(cols+48));
			
			strcpy(info.label, label);
			info.same = 0;
			info.total = 0;
			
			countSimilarity(statistik, &info, total);
			info.total = sqrt((float)total[0]) * sqrt((float)total[1]);
			
			EnQueue(&Q, info);
			label = "";
		}
	}
	
	return Q;
}

void getTotal(addrStat root, int index[], int total[]){
	if (root) {
		/*Count Total*/
		total[0] += root->info.amount[index[0]];
		total[1] += root->info.amount[index[1]];
		
		if(root->left != NULL){
			getTotal(root->left, index, total);
		}
		if(root->right != NULL){
			getTotal(root->right, index, total);	
		}
	}
}
/*
void countSimilarity(addrStat root, records *info, int total[]){
	float stat1, stat2;
	int index[2] = {0,0};
	if (root) {
		getIndex((*info).label, index);
		if(root->info.amount[index[0]] != 0 || root->info.amount[index[1]] != 0){
			(*info).total += 1;
			
			stat1 = (float)(root->info.amount[index[0]])/total[0];
			stat2 = (float)(root->info.amount[index[1]])/total[1];
			
			if(absolute(stat1-stat2) < 10 && (stat1 != 0 && stat2 != 0)){
				(*info).same += 1;
			}
		}
		if(root->left != NULL){
			countSimilarity(root->left, &(*info), total);
		}
		if(root->right != NULL){
			countSimilarity(root->right, &(*info), total);	
		}
	}
}*/

void countSimilarity(addrStat root, records *info, int rerata[]){
	int index[2] = {0,0};
	if (root) {
		getIndex((*info).label, index);
		
		(*info).same += (root->info).amount[index[0]] * (root->info).amount[index[1]];
		rerata[0] += (root->info).amount[index[0]] * (root->info).amount[index[0]];
		rerata[1] +=  (root->info).amount[index[1]] * (root->info).amount[index[1]];
		
		if(root->left != NULL){
			countSimilarity(root->left, &(*info), rerata);
		}
		if(root->right != NULL){
			countSimilarity(root->right, &(*info), rerata);	
		}
	}
}

void getIndex(char* teks, int index[]){
	index[0] = (int)(teks[0]) - 48;
	index[1] = (int)(teks[2]) - 48;
}

float absolute(float number){
	return number > 0 ? number : (number*-1);
}

void printResult(Queue Q, char docs[][40]){
	/*Melakukan Print terhadap Queue*/
	int index[2] = {0,0};
	float similarity = 0;
	if(isEmptyQueue(Q)){
		printf("Queue Kosong\n");
	}else{
		addrList P = First(Q);
		while(P != Nil){
			getIndex(Info(P).label, index);
			similarity = ((float)(Info(P).same)/(float)(Info(P).total))*100;
			printf("\n         Perbandingan Kemiripan \n\n         Dokumen %s \n\n         Dokumen %s \n", docs[index[0]], docs[index[1]]);
			printf("\n         Kemiripan Dokumen %.2f%c \n\n", similarity, '%');
			//printf("%s / %d / %d\n",Info(P).label, Info(P).same, Info(P).total);
			P = Next(P);
		}
		
		printf("\n");
	}
}

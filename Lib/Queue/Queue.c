#include "Queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30;

void CreateQueue(Queue *Q){
	/*Membuat sebuah Queue*/
	
	First(*Q) = Nil;
}

boolean isEmptyQueue(Queue Q){
	/*Memerikasa apakah Queue Kosong*/
	
	return (First(Q) == Nil);	
}

boolean isFullQueue(Queue Q){
	/*Memeriksa apakah Queue Penuh*/
	
	return countQueue(Q) == MAX;
}

void EnQueue(Queue *Q, records X){
	/*Melakukan Proses EnQueue List*/
	if(isFullQueue(*Q)){
		printf("Antrian Penuh");
	}else{
		InsVLast(&(*Q), X);
	}
}

void DeQueue(Queue *Q, records *X){
	/*Melakukan Proses DeQueue List*/
	if(isEmptyQueue(*Q)){
		printf("Tidak ada antrian\n");
		strcpy((*X).label,"None");
	}else{
		DelVFirst(&(*Q), &(*X));	
	}
}

int countQueue(Queue Q){
	/*Mengitung jumlah elemen dari Queue*/
	
	return NbElmt(Q);
}

void printQueue(Queue Q){
	/*Melakukan Print terhadap Queue*/

	if(isEmptyQueue(Q)){
		printf("Queue Kosong\n");
	}else{
		addrList P = First(Q);
		while(P != Nil){
			printf("%s / %d / %d\n",Info(P).label, Info(P).same, Info(P).total);
			P = Next(P);
		}
		
		printf("\n");
	}
}

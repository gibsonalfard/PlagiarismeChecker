#ifndef queue_H
#define queue_H

#include "boolean.h"
#include "list1.h"
#include <stdlib.h>

typedef List Queue;

void CreateQueue(Queue *Q);
/*Membuat sebuah Queue*/

boolean isEmptyQueue(Queue Q);
/*Memerikasa apakah Queue Kosong*/

boolean isFullQueue(Queue Q);
/*Memeriksa apakah Queue Penuh*/

void EnQueue(Queue *Q, records X);
/*Melakukan Proses EnQueue List*/

void DeQueue(Queue *Q, records *X);
/*Melakukan Proses DeQueue List*/

int countQueue(Queue Q);
/*Mengitung jumlah elemen dari Queue*/

void printQueue(Queue Q);
/*Melakukan Print terhadap Queue*/

#endif

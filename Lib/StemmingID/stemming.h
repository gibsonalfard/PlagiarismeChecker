#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifndef STEMMING_H
#define STEMMING_H

/*
 * Library ini digunakan untuk melakukan stemming terhadap suatu kata
 * algoritma ini merupakan implementasi dari algoritma Nazief dan Adriani (1996) yang
 * dilengkapi oleh penilitian Jelita Asian (2004) dengan beberapa modifikasi
 * 
 */
 
typedef struct {
	char kata[50];
}daftarKata;

daftarKata listRootWord[30174];

/**** Program Utama ****/
char* stemming (char* kataUntukDiStem);

/**** Kelompok Pemeriksa ****/
bool isUjungSama (char* kataDiperiksa, char suffixPembanding[]);
bool isAwalSama (char* kataDiperiksa, char prefixPembanding[]);
int jumlahSukuKata (char* kataDiperiksa);
bool sudahRootWord (char* kataDiperiksa);
bool SearchtoTree (char kataDiperiksa[], daftarKata* list);

/**** Kelompok Pengedit ****/
char* hapusSuffix (char* kataDiedit, int ukuranSuffix);
char* hapusPrefix (char* kataDiedit, int ukuranPrefix);

/**** Kelompok Lain ****/


#endif

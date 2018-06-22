/* File :  list1.h   					*/
/* Desk :  deklarasi list  berkait dgn representasi     */
/* 	   fisik pointer;				*/
/* 	   Representasi address dgn pointer 		*/
/* Oleh :  ANI RAHMANI / 23501007 	  		*/
/* Tgl  :  25/10/01					*/	 

/* List :  */
#include "list1.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

/* ** Prototype   **  */
/* ** Test List Kosong **  */
boolean ListEmpty(List  L){
	/*  Mengirim true jika List kosong  */
	
	return (First(L) == Nil);
}                       

/* Pembuatan  List Kosong  */
void CreateList(List *L){
	/* I.S  :  Sembarang    			*/
	/* F.S  :  Terbentuk  List kosong  	*/
	
	First(*L) = Nil;	
}

/* Manajeman  memory  			*/
addrList Alokasi(records X){
	 /* Mengirimkan  address  hasil alokasi    sebuah elemen */
	 /* Jika alokasi  berhasil, maka  address tidak nil, dan misalnya  */
	 /* menghasilkan   P,  maka info(P)=X,  Next(P)=Nil;               */
	 /* Jika alokasi  gagal,  mengirimkan  Nil 			   */
	 
	 addrList P = (addrList) malloc(sizeof(ElmtList));
	 
	 if(P != Nil){
		Info(P) = X;
		Next(P) = Nil;
	 }
	 
	 return P;
}

void Dealokasi(addrList *P){
	/* I.S  :   P  terdefinisi         	*/
	/* F.S  :   P dikembalikan ke  sistem 	*/
	/*   	    Melakukan  dealokasi, pengembalian address  P */
	
	//Nil (Putuskan dari LL) dulu baru bebaskan
	Next(*P) = Nil;
	free(*P);
}


/*   ** PENCARIAN SEBUAH ELEMEN LIST **   */

addrList Search1(List L, char*  X){
	/* Mencari apakah  ada elemen list dengan info(P)=X      */
	/* Jika ada, mengirimkan  address elemen tersebut	 */
	/* Jika  tidak ada, mengirimkan Nil 			 */
	
	addrList P = First(L);
	boolean ketemu = false;
	
	while(P != Nil && !ketemu){
		if (strcmp(Info(P).label,X) == 0){
			ketemu = true;
		}else{
			P = Next(P);
		}
	}
	
	return P;
}

boolean FSearch(List L, addrList P){
	/* Mencari apakah  ada elemen List yang  beralamat   P   */
	/* Mengirimkan true jika ada, false jika tidak ada  	 */
	
	addrList Q = First(L);
	boolean ketemu = false;
	
	while(Q != Nil && !ketemu){
		if(Q == P){
			ketemu = true;
		}else{
			Q = Next(Q);
		}
	}
	
	return ketemu;
}

addrList SearchPrec(List L, char* X){
	/* mencari apakah ada elemen List  yang beralamat P 	     */
	/* Mnegirimkan address elemen sebelum elemen yang nilainya X */
	/* Mencari apakah ada elemen List dengan info(P)=X	     	*/
	/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P   */	
	
	addrList P = First(L);
	addrList Q = Nil;
	boolean ketemu = false;
	
	if (Next(P) != Nil){
		while(P != Nil && !ketemu){
			if(strcmp(Info(P).label,X) == 0){
				ketemu = true;
			}else{
				Q = P;
				P = Next(P);
			}
		}
	}
	
	return Q;
}

/* ** PRIMITIF BERDASARKAN NILAI ** */

/* ** Penambahan Elemen ** */
void InsVFirst(List *L, records X){
	/* I.S  : L mungkin kosong          */
	/* F.S  : Melakukan alokasi sebuah elemen dan                */
	/*        menambahkan elemen pertama dengan nilai X jika     */
	/*        Alokasi berhasil 				     				*/
	
	//Fadly
	addrList P = Alokasi(X);
	if (P != Nil){
		InsertFirst(&(*L),P);
	}	
	
	//
}

void InsVLast(List *L, records X){
	/* I.S  : L mungkin kosong          */
	/* F.S  : Melakukan alokasi sebuah elemen dan                */
	/*        menambahkan elemen list di akhir; elemen terakhir  */
	/*        yang baru bernilai X jika alokasi berhasil, 	     */	
	/*	  Jika alokasi gagal: I.S = F.S			     */
	
	addrList P = Alokasi(X);
	if (P != Nil){
		InsertLast(&(*L),P);
	}
}	

/* *** Penghapusan Elemen  ***  */
	  

void DelVFirst(List *L, records *X){
	/* I.S    : List tidak kosong  		                 */
  	/* F.S    : Elemen pertama List dihapus, nilai info disimpan   */
  	/*	      pada X dan alamat elemen pertama  di-dealokasi 	 */	
  	addrList P;
  	
  	DelFirst(&(*L),&P);
  	*X = Info(P);
  	Dealokasi(&P);
}

void DelVLast(List *L, records *X){
	/* I.S    : List tidak kosong  		                 */
  	/* F.S    : Elemen terakhir list dihapus, nilai info disimpan  */
  	/*	      pada X dan alamat elemen terakhir di-dealokasi 	 */	
  	
  	addrList P;
  	
  	DelLast(&(*L),&P);
  	*X = Info(P);
  	Dealokasi(&P);
}

/* *******  PRIMITIF BERDASARKAN ALAMAT ********	*/
/* Penambahan Elemen Berdasarkan Alamat 		*/

void InsertFirst(List *L, addrList P){
	/* I.S   : Sembarang, P sudah dialokasi			*/
	/* F.S   : Menambahkan elemen ber-address P, sebagai    */
	/*         elemen pertama				*/	
	
	/* Citay & Fadly
	Next(P) = Info(*L);
	First(*L) = Info(P);
	
	// Randi
	Next(P) = Info(*L);
	Info(*L) = Info(P);
	*/
	
	//Ilham
	Next(P) = First(*L);
	First(*L) = P;
}

void InsertAfter(List *L, addrList P, addrList Prec){
	/* I.S   : Prec pastilah elemen list dan bukan elemen terakhir  */
	/*         P sudah dialokasi 					*/
	/* F.S   : Insert P sebagai elemen sesudah elemen beralamat Prec*/
	
	
}

void InsertLast(List *L, addrList P){
	/* I.S   : Sembarang, P sudah dialokasi				*/
	/* F.S   : P ditambahkan  sebagai elemen terakhir yang baru	*/
	
	addrList Head;
	
	if(ListEmpty(*L)){
		InsertFirst((&(*L)), P);
	} else{
		Head = First(*L);
		
		while(Next(Head) != Nil){
			Head = Next(Head);
		}
		
		Next(Head) = P;
	}
}

/* ****** PENGHAPUSAN SEBUAH ELEMEN	*********   */
void DelFirst (List *L, addrList *P){
	/* I.S   : List tidak kosong 	*/
	/* F.S   : P adalah alamat elemen pertama list sebelum penghapusan */
	/*         Elemen List berkurang satu (mungkin menjadi kosong)     */
	/* First elemen yang baru adalah suksesor elemen pertama yang lama */
	
	*P = First(*L);
	First(*L) = Next(*P);
	Next(*P) = Nil;	
}

void DelLast(List *L, addrList *P){
	/* I.S   : List tidak kosong  */
	/* F.S   : P adalah alamat elemen terakhir list sebelum penghapusan */
	/*	   Elemen list berkurang 1 (mungkin menjadi kosong)	    */
	/*         Last elemen baru adalah predessesor elemen pertama yang  */
	/*         jika tidak ada					    */
	
	addrList Trav,Prep;
	Trav = First(*L);
	
	while(Next(Trav) != Nil){
		Prep = Trav;
		Trav = Next(Trav);
	}
	
	*P = Trav;
	Next(Prep) = Nil;
}

/* *************PROSES SEMUA ELEMEN ****************   */
void PrintInfo(List L){
	/* I.S   : List mungkin kosong 	*/
	/* F.S   : Jika list tidak kosong, semua info yang disimpan pada */
	/*         elemen list di-print					 */
	/*         Jika list kosong, hanya menuliskan "List Kosong"	 */
	
	if(ListEmpty(L)){
		printf("List Kosong\n");
	}else{
		addrList P = First(L);
		while(P != Nil){
			printf("%s \n",Info(P).label);
			P = Next(P);
		}
		
		printf("\n");
	}
}

int NbElmt(List L){
	/* Mengirimkan banyaknya elemen list, mengirimkan Nol jika kosong */
	
	addrList Trav;
	int i = 0;
	
	Trav = First(L);
	
	while(Trav != Nil){
		i++;
		Trav = Next(Trav);
	}
	
	return i;
}

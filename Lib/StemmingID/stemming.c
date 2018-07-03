#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stemming.h"

#ifndef STEMMING_C
#define STEMMING_C

/*
 * Deskripsi :	Library ini digunakan untuk melakukan stemming terhadap suatu kata
 * 				algoritma ini merupakan implementasi dari algoritma Nazief dan Adriani (1996) yang
 * 				dilengkapi oleh penilitian Jelita Asian (2004) dengan beberapa modifikasi
 * Author	 :	prolog32
 * 
 */


char* stemming (char* kataUntukDiStem){
	// Deskripsi  : modul utama untuk melakukan stemming
	// I.S.		  : sembarang, parameter tidak kosong
	// F.S.		  : mengembalikan address dari kata yang sudah distemming
	// author	  : prolog32
	
	//error handling
	if(kataUntukDiStem==NULL){
		return kataUntukDiStem;
	}
	
	bool skip4a = false;
	char word[50];
	strcpy(word, kataUntukDiStem);
	
	// step 1.
	// periksa apakah sudah rootword?
	// jika sudah rootword, langsung kembalikan
	{
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// periksa anomali berdasar Asian, Jelita (2004)
	{
		if((isAwalSama(kataUntukDiStem, "me") ||
			isAwalSama(kataUntukDiStem, "di") ||
			isAwalSama(kataUntukDiStem, "pe")) && (
			isUjungSama(kataUntukDiStem, "i")) &&
			(*(kataUntukDiStem+2) == 'n') || 
			(*(kataUntukDiStem+3) == 'g') ||
			(*(kataUntukDiStem+3) == 'y')){
				// periksa apakah sudah rootword
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
				// periksa apakah sudah rootword
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
				kataUntukDiStem = hapusSuffix(kataUntukDiStem, 1);
		} else if (isAwalSama(kataUntukDiStem, "ter") && isUjungSama(kataUntukDiStem, "i")){
				// periksa apakah sudah rootword
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
				// periksa apakah sudah rootword
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
				kataUntukDiStem = hapusSuffix(kataUntukDiStem, 1);
		} else if (isAwalSama(kataUntukDiStem, "be") && (
					isUjungSama(kataUntukDiStem, "an") || 
					isUjungSama(kataUntukDiStem, "lah"))){
						// periksa apakah sudah rootword
						if(sudahRootWord(kataUntukDiStem)){	
							return kataUntukDiStem;
						}
						kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
						// periksa apakah sudah rootword
						if(sudahRootWord(kataUntukDiStem)){	
							return kataUntukDiStem;
						}
						if(isUjungSama(kataUntukDiStem, "an")){
							kataUntukDiStem = hapusSuffix(kataUntukDiStem, 2);
						} else if (isUjungSama(kataUntukDiStem, "lah")){
							kataUntukDiStem = hapusSuffix(kataUntukDiStem, 3);
						}
		}
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// step 2a.
	// periksa akhiran lah, kah, tah, pun
	{
		if(isUjungSama(kataUntukDiStem, "lah") || 
		   isUjungSama(kataUntukDiStem, "kah") || 
	   	   isUjungSama(kataUntukDiStem, "tah") ||
	   	   isUjungSama(kataUntukDiStem, "pun") ){
				kataUntukDiStem=hapusSuffix(kataUntukDiStem, 3);
				//periksa apakah rootword
				//jika rootword, maka keluarkan
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
		}
	}
	
	// step 2b.
	// periksa akhiran kepunyaan ku, mu, nya
	{
		if((isUjungSama(kataUntukDiStem, "ku") && !isAwalSama(kataUntukDiStem, "me"))|| 
	   		isUjungSama(kataUntukDiStem, "mu")){
				kataUntukDiStem=hapusSuffix(kataUntukDiStem, 2);
		} else if (isUjungSama(kataUntukDiStem, "nya")){
			kataUntukDiStem=hapusSuffix(kataUntukDiStem, 3);
		}
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// step 3a.
	// periksa akhiran i*, an, kan
	// akhiran i tidak dihapus, disimpan 
	{	
		if (isUjungSama(kataUntukDiStem, "an") && !isUjungSama(kataUntukDiStem, "kan") && !isUjungSama(kataUntukDiStem, "man") && !isUjungSama(kataUntukDiStem, "wan")){
			kataUntukDiStem=hapusSuffix(kataUntukDiStem, 2);
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
			if(isAwalSama(kataUntukDiStem, "di") || isAwalSama(kataUntukDiStem, "me"))
				skip4a = true;
			if (isUjungSama(kataUntukDiStem, "k")){
				kataUntukDiStem = hapusSuffix(kataUntukDiStem,1);
				if(isAwalSama(kataUntukDiStem, "ke") || isAwalSama(kataUntukDiStem, "se"))
					skip4a = true;
			}
				
		} else if (isUjungSama(kataUntukDiStem, "i") &&
		          !isUjungSama(kataUntukDiStem, "isasi") &&
				  !isUjungSama(kataUntukDiStem, "wati") && 
				  !isAwalSama(kataUntukDiStem, "me")){
			kataUntukDiStem=hapusSuffix(kataUntukDiStem, 1);
			if(isAwalSama(kataUntukDiStem, "be") || isAwalSama(kataUntukDiStem, "ke") || isAwalSama(kataUntukDiStem, "se"))
				skip4a = true;
		}
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// step 3b.
	// periksa akhiran serapan (man, wan, wati, iah, isme, is, isasi)
	{
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
		if((isUjungSama(kataUntukDiStem, "man") || 
		   isUjungSama(kataUntukDiStem, "wan")  || 
		   isUjungSama(kataUntukDiStem, "iah")) &&
		   !isAwalSama(kataUntukDiStem, "pe"))
			kataUntukDiStem = hapusSuffix(kataUntukDiStem, 3);
		  else if (isUjungSama(kataUntukDiStem, "wati") || isUjungSama(kataUntukDiStem, "isme") )
			kataUntukDiStem = hapusSuffix(kataUntukDiStem, 4);
		  else if (isUjungSama(kataUntukDiStem, "isasi") && (
		  		   *(kataUntukDiStem+strlen(kataUntukDiStem)-6) != 'a' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-6) != 'i' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-6) != 'u' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-6) != 'e' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-6) != 'o'))
			kataUntukDiStem = hapusSuffix(kataUntukDiStem, 5);
		  else if (isUjungSama(kataUntukDiStem, "is") && (
		  		   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'a' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'i' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'u' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'e' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'o' ||
				   *(kataUntukDiStem+strlen(kataUntukDiStem)-3) == 'l'))
			kataUntukDiStem = hapusSuffix(kataUntukDiStem, 2);
		  else if (isUjungSama(kataUntukDiStem, "an") && isAwalSama(kataUntukDiStem, "pe"))
		  	kataUntukDiStem = hapusSuffix(kataUntukDiStem, 2);
		  else if (isUjungSama(kataUntukDiStem, "ism"))
		  	kataUntukDiStem = hapusSuffix(kataUntukDiStem, 3);
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// step 4.0
	// tambahan periksa awalan kepunyaan
	{
		if(isAwalSama(kataUntukDiStem, "ku"))
			kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
		//periksa apakah rootword
		//jika rootword, maka keluarkan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}
	}
	
	// step 4a.
	// periksa awalan biasa (di, ke, se)
	{
		if (!skip4a &&
			(isAwalSama(kataUntukDiStem, "di") ||
			 isAwalSama(kataUntukDiStem, "ke") ||
			 isAwalSama(kataUntukDiStem, "se"))){
			 	kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
		}
		//periksa apakah rootword
		//jika iya maka kembalikan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}	
	}
		
	// step 4b.
	// periksa awalan istimewa (me, te, pe, be)
	{
		
		//periksa prefiks ter-
		if (isAwalSama(kataUntukDiStem, "te")){
			if(*(kataUntukDiStem+2) == 'r'){
				//periksa apakah rootword
				//jika rootword, maka kembalikan
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
				if(*(kataUntukDiStem+3) != 'r'){
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
				}
			} else if ((*(kataUntukDiStem+2) != 'r' ||
				   		*(kataUntukDiStem+2) != 'a' ||
				   		*(kataUntukDiStem+2) != 'i' ||
				   		*(kataUntukDiStem+2) != 'u' ||
				   		*(kataUntukDiStem+2) != 'e' ||
				   		*(kataUntukDiStem+2) != 'o') && 
				   		(*(kataUntukDiStem+5) != 'a' ||
				   		*(kataUntukDiStem+5) != 'i' ||
				   		*(kataUntukDiStem+5) != 'u' ||
				   		*(kataUntukDiStem+5) != 'e' ||
				   		*(kataUntukDiStem+5) != 'o')){
						   kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
			} else if (strcmp (kataUntukDiStem, "telanjur") == 0){
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
			}
			//periksa apakah rootword
			//jika rootword, maka kembalikan 
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
		}	
		
		
		//periksa prefiks ber-
		if(isAwalSama(kataUntukDiStem, "be")){
//			if(isAwalSama(kataUntukDiStem, "ber")){
//				//periksa apakah roootword
//				//jika rootword, maka kembalikan
//				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
//			} else if (*(kataUntukDiStem+3) == 'e'  &&  *(kataUntukDiStem+4) == 'r'){
//				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
//			}

			if (*(kataUntukDiStem+3) == 'e'  &&  *(kataUntukDiStem+4) == 'r'){
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
				//periksa apakah rootword
				//jika rootword, maka kembalikan
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
			} else if(isAwalSama(kataUntukDiStem, "ber")){
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
				//periksa apakah roootword
				//jika rootword, maka kembalikan
				if(sudahRootWord(kataUntukDiStem)){	
					return kataUntukDiStem;
				}
			}
		}
		
		
		//perisksa prefiks me-
		{
			//leburan s/t/p - konsonan
			if((*(kataUntukDiStem+4) != 'a' ||
				*(kataUntukDiStem+4) != 'i' ||
				*(kataUntukDiStem+4) != 'u' ||
				*(kataUntukDiStem+4) != 'e' ||
				*(kataUntukDiStem+4) != 'o' ) &&
				(isAwalSama(kataUntukDiStem, "men") && (*(kataUntukDiStem+3) == 's' || *(kataUntukDiStem+3) =='t')) ||
				(isAwalSama(kataUntukDiStem, "mem") && *(kataUntukDiStem+3)=='p') )
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			//leburan k-konsonan
			else if((*(kataUntukDiStem+5) != 'a' ||
				*(kataUntukDiStem+5) != 'i' ||
				*(kataUntukDiStem+5) != 'u' ||
				*(kataUntukDiStem+5) != 'e' ||
				*(kataUntukDiStem+5) != 'o' ) &&
				(isAwalSama(kataUntukDiStem, "meng") && *(kataUntukDiStem+4)=='k') )
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 4);
			//leburan menge - 1suku kata
			else if(isAwalSama(kataUntukDiStem, "menge") && jumlahSukuKata(kataUntukDiStem)==3)
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 5);
			//me- bukan leburan (konsonan selain pskt)
			else if(isAwalSama(kataUntukDiStem, "meng") && (
				*(kataUntukDiStem+4) == 'a' ||
				*(kataUntukDiStem+4) == 'i' ||
				*(kataUntukDiStem+4) == 'u' ||
//				*(kataUntukDiStem+4) == 'e' ||
				*(kataUntukDiStem+4) == 'o' ||
//				*(kataUntukDiStem+4) == 'g' ||
				*(kataUntukDiStem+4) == 'h' ||
				*(kataUntukDiStem+4) == 'q' ||
				*(kataUntukDiStem+4) == 'x') && jumlahSukuKata(kataUntukDiStem)>3)
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 4);
			else if(isAwalSama(kataUntukDiStem, "mem") && (
				*(kataUntukDiStem+3) == 'b' ||
				*(kataUntukDiStem+3) == 'f' ||
				*(kataUntukDiStem+3) == 'v'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			else if(isAwalSama(kataUntukDiStem, "men") && (
				*(kataUntukDiStem+3) == 'c' ||
				*(kataUntukDiStem+3) == 'd' ||
				*(kataUntukDiStem+3) == 'j' ||
				*(kataUntukDiStem+3) == 'z'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			else if(isAwalSama(kataUntukDiStem, "me") && (
				*(kataUntukDiStem+2) == 'l' ||
				*(kataUntukDiStem+2) == 'm' ||
				*(kataUntukDiStem+2) == 'n' ||
				*(kataUntukDiStem+2) == 'r' ||
				*(kataUntukDiStem+2) == 'w' ||
				*(kataUntukDiStem+2) == 'y'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
		
			if(isAwalSama(kataUntukDiStem, "ny")){
				*(kataUntukDiStem+1)='s';
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
			} else if(isAwalSama(kataUntukDiStem, "ng")){
				*(kataUntukDiStem+1)='k';
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
			} else if(isAwalSama(kataUntukDiStem, "n")){
				*(kataUntukDiStem+0)='t';
			} else if(isAwalSama(kataUntukDiStem, "m")){
				*(kataUntukDiStem+0)='p';
			}
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
			if(isUjungSama(kataUntukDiStem, "i"))	
					kataUntukDiStem = hapusSuffix(kataUntukDiStem, 1);
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}	
		}
		
		//periksa awalan pe-
		{
			if((*(kataUntukDiStem+4) != 'a' ||
				*(kataUntukDiStem+4) != 'i' ||
				*(kataUntukDiStem+4) != 'u' ||
				*(kataUntukDiStem+4) != 'e' ||
				*(kataUntukDiStem+4) != 'o' ) &&
				(isAwalSama(kataUntukDiStem, "pen") && (*(kataUntukDiStem+3) == 's' || *(kataUntukDiStem+3) =='t')) ||
				(isAwalSama(kataUntukDiStem, "pem") && *(kataUntukDiStem+3)=='p') )
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			//leburan k-konsonan
			else if((*(kataUntukDiStem+5) != 'a' ||
				*(kataUntukDiStem+5) != 'i' ||
				*(kataUntukDiStem+5) != 'u' ||
				*(kataUntukDiStem+5) != 'e' ||
				*(kataUntukDiStem+5) != 'o' ) &&
				(isAwalSama(kataUntukDiStem, "peng") && *(kataUntukDiStem+4)=='k') )
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 4);
			//leburan menge - 1suku kata
			else if(isAwalSama(kataUntukDiStem, "penge") && jumlahSukuKata(kataUntukDiStem)==3)
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 5);
			//pe- bukan leburan (konsonan selain pskt)
			else if(isAwalSama(kataUntukDiStem, "peng") && (
				*(kataUntukDiStem+4) == 'a' ||
				*(kataUntukDiStem+4) == 'i' ||
				*(kataUntukDiStem+4) == 'u' ||
//				*(kataUntukDiStem+4) == 'e' ||
				*(kataUntukDiStem+4) == 'o' ||
//				*(kataUntukDiStem+4) == 'g' ||
				*(kataUntukDiStem+4) == 'h' ||
				*(kataUntukDiStem+4) == 'q' ||
				*(kataUntukDiStem+4) == 'x') && jumlahSukuKata(kataUntukDiStem)>3)
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 4);
			else if(isAwalSama(kataUntukDiStem, "pem") && (
				*(kataUntukDiStem+3) == 'b' ||
				*(kataUntukDiStem+3) == 'f' ||
				*(kataUntukDiStem+3) == 'v'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			else if(isAwalSama(kataUntukDiStem, "pen") && (
				*(kataUntukDiStem+3) == 'c' ||
				*(kataUntukDiStem+3) == 'd' ||
				*(kataUntukDiStem+3) == 'j' ||
				*(kataUntukDiStem+3) == 'z'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 3);
			else if(isAwalSama(kataUntukDiStem, "pe")){
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
					//periksa apakah rootword
					//jika rootword, maka kembalikan
					if(isAwalSama(kataUntukDiStem, "r"))
							kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
					else if (strcmp(kataUntukDiStem, "lajar") == 0 ||
						 strcmp(kataUntukDiStem, "lunjur") == 0)
						 	kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
			}
			else if(isAwalSama(kataUntukDiStem, "pe") && (
				*(kataUntukDiStem+2) == 'l' ||
				*(kataUntukDiStem+2) == 'm' ||
				*(kataUntukDiStem+2) == 'n' ||
//				*(kataUntukDiStem+2) == 'r' ||
				*(kataUntukDiStem+2) == 'w' ||
				*(kataUntukDiStem+2) == 'y'))
					kataUntukDiStem = hapusPrefix(kataUntukDiStem, 2);
			
			
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
			if(isAwalSama(kataUntukDiStem, "ny")){
				*(kataUntukDiStem+1)='s';
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
			} else if(isAwalSama(kataUntukDiStem, "ng")){
				*(kataUntukDiStem+1)='k';
				kataUntukDiStem = hapusPrefix(kataUntukDiStem, 1);
			} else if(isAwalSama(kataUntukDiStem, "n")){
				*(kataUntukDiStem+0)='t';
			} else if(isAwalSama(kataUntukDiStem, "m")){
				*(kataUntukDiStem+0)='p';
			}
			
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}
			if(isUjungSama(kataUntukDiStem, "i"))	
					kataUntukDiStem = hapusSuffix(kataUntukDiStem, 1);
			//periksa apakah rootword
			//jika rootword, maka kembalikan
			if(sudahRootWord(kataUntukDiStem)){	
				return kataUntukDiStem;
			}	
		}
		
		//periksa apakah rootword
		//jika rootword, maka kembalikan
		if(sudahRootWord(kataUntukDiStem)){	
			return kataUntukDiStem;
		}	
	}
	
	//periksa terakhir
	{
		if(isUjungSama(kataUntukDiStem, "kan"))
			kataUntukDiStem = hapusSuffix(kataUntukDiStem, 3);
		
	}
	
//	puts(kataUntukDiStem);	
//	if(!sudahRootWord(kataUntukDiStem))
//		printf("tidak ketemu - :");
//		strcpy(kataUntukDiStem, word);
	
	return kataUntukDiStem;
}

bool sudahRootWord (char* kataDiperiksa){
	// Deskripsi  : memeriksa apakah kata yang diperiksa merupakan rootword
	// I.S.		  : sembarang, parameter tidak kosong
	// F.S.		  : mengembalikan nilai true atau false
	// author	  : prolog32
	
	char chkdWrd[50];
	strcpy(chkdWrd, kataDiperiksa);
	daftarKata* rw = listRootWord;
	return SearchtoTree(chkdWrd, rw);
}

bool SearchtoTree (char kataDiperiksa[], daftarKata* list){
	// Deskripsi  : memeriksa apakah kata yang diperiksa mengandung suffix (suffixPembanding)
	// I.S.		  : kedua parameter tidak kosong
	// F.S.		  : mengembalikan nilai true atau false
	// sumber	  :	https://stackoverflow.com/questions/249392/binary-search-in-array
	// pengedit	  : prolog32
	
	int bAtas = 30173;
	int bBawah = 0;
	int temp = 0;
	while (bAtas>bBawah){
		int mid = bBawah + (bAtas - bBawah)/2;
//		printf("%d - ", mid);
		if(temp==mid)
			return false;
		
		if(strcmp((list+mid)->kata, kataDiperiksa) > 0)
			bAtas = mid+1;
		else if(strcmp((list+mid)->kata, kataDiperiksa) < 0)
			bBawah = mid-1;
		else if(strcmp((list+mid)->kata, kataDiperiksa) == 0)
			return true;
		temp = mid;
//		printf("%d\n", mid);
	}
	return false;
}

bool isUjungSama (char* kataDiperiksa, char suffixPembanding[]){
	// Deskripsi  : memeriksa apakah kata yang diperiksa mengandung suffix (suffixPembanding)
	// I.S.		  : kedua parameter tidak kosong
	// F.S.		  : mengembalikan nilai true atau false
	// author	  : prolog32
	
	//error handling
	if(kataDiperiksa==NULL || suffixPembanding=="")
		return false;
	
	bool hasil = true;
	int i = strlen(suffixPembanding);
	
	while(i>0 && hasil){
		if(*(kataDiperiksa+(strlen(kataDiperiksa)-i)) != suffixPembanding[strlen(suffixPembanding)-i])
			hasil = false;
		else
			i--;
	}
	
	return hasil;
}

bool isAwalSama (char* kataDiperiksa, char prefixPembanding[]){
	// Deskripsi  : memeriksa apakah kata yang diperiksa mengandung prefix (prefixPembanding)
	// I.S.		  : kedua parameter tidak kosong
	// F.S.		  : mengembalikan nilai true atau false
	// author	  : prolog32
	
	//error handling
	if(kataDiperiksa==NULL || prefixPembanding=="")
		return false;
	
	bool hasil = true;
	int i = strlen(prefixPembanding);
	
	while(i>0 && hasil){
		if(*(kataDiperiksa+(i-1)) != prefixPembanding[i-1])
			hasil = false;
		else
			i--;
	}
	
	return hasil;
}

int jumlahSukuKata (char* kataDiperiksa){
	// Deskripsi  : menghitung jumlah suku kata pada suatu kata
	// I.S.		  : kataDiperiksa tidak null
	// F.S.		  : mengembalikan jumlah kemunculan huruf vokal pada suatu kata
	// author	  : prolog32
	
	//error handling
	if(kataDiperiksa==NULL)
		return 0;
		
	int jumlah = 0, i=0;
	while (i<strlen(kataDiperiksa)){
		if( *(kataDiperiksa+i) == 'a' || *(kataDiperiksa+i) == 'i' ||
		    *(kataDiperiksa+i) == 'u' || *(kataDiperiksa+i) == 'e' || 
			*(kataDiperiksa+i) == 'o' )
			jumlah++;
		i++;
	}
	return jumlah;
}

char* hapusSuffix (char* kataDiedit, int ukuranSuffix){
	// Deskripsi  : menghapus suffix dari suatu kata, mengembalikan address dari kata yang baru
	// I.S.		  : kedua parameter tidak kosong
	// F.S.		  : mengembalikan address dari string yang sudah dihapus suffixnya
	// author	  : prolog32
	
	//error handling
	if(kataDiedit==NULL || ukuranSuffix==0)
		return kataDiedit;
	
	char* penunjuk;
	char input[strlen(kataDiedit)];
	char output[strlen(kataDiedit)-ukuranSuffix];
	
	strcpy(input, kataDiedit);
	input[strlen(input)-ukuranSuffix]='\0';
	strcpy(output, input);
	penunjuk = output;
	
	return penunjuk;
}

char* hapusPrefix (char* kataDiedit, int ukuranPrefix){
	// Deskripsi  : menghapus prefix dari suatu kata, mengembalikan address dari kata yang baru
	// I.S.		  : kedua parameter tidak kosong
	// F.S.		  : mengembalikan address dari string yang sudah dihapus prefixnya
	// author	  : prolog32
	
	//error handling
	if(kataDiedit==NULL || ukuranPrefix==0)
		return kataDiedit;
	
	char* penunjuk;
	char input[strlen(kataDiedit)];
	char output[strlen(kataDiedit)-ukuranPrefix];
	
	strcpy(input, kataDiedit);
//	puts(input);
	strcpy(output, input+ukuranPrefix);
	penunjuk = output;
//	puts(penunjuk);
//	printf("%x\n",penunjuk);
	
	return penunjuk;
}


#endif

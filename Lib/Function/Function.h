#include "../String/String.h"
#include "../AVL/Tree.h"
#include "../Statistik/Statistik.h"
#include "../StemmingENG/stemming.h"

/* Memasukan teks ke dalam string dinamik dengan mengabaikan tanda baca dan angka */
String caseFolding(String text, char *location);
void getStopwords(addr *T);
//addrStat Tokenizing(String text, int doc,addr stop);
void Tokenizing(String text, int doc, addr stop, addrStat *root);
bool isStopword(String word, addr stopword);
String StemString(String text);

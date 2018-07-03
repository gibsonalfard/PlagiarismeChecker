#include "../String/String.h"
#include "../AVL/Tree.h"
#include "../Statistik/Statistik.h"
#include "../StemmingENG/stemming.h"
#include "../StemmingID/stemming.h"
#include "../Queue/Queue.h"
#include <math.h>

int choice;

/* Memasukan teks ke dalam string dinamik dengan mengabaikan tanda baca dan angka */
String caseFolding(String text, char *location);
void getStopwords(addr *T, char *namaFile);
void getKataDasar(addr *T, char *namaFile);
//addrStat Tokenizing(String text, int doc,addr stop);
void Tokenizing(String text, int doc, addr stop, addr dasar, addrStat *root);
bool isStopword(String word, addr stopword);
bool isBasicWord(String word, addr basic);
String StemString(String text);
Queue getSimilarityList(addrStat statistik, int numOfDocs);
//void countSimilarity(addrStat root, records *info, int total[]);
void countSimilarity(addrStat root, records *info, int rerata[]);
void getIndex(char* teks, int index[]);
void getTotal(addrStat root, int index[], int total[]);
float absolute(float number);
String getPlagiarismLevel(float number);
void printResult(Queue Q, char docs[][40]);
String StemmingWord(String word);
bool isDocumentExist(String location);
void CreateStemDictionary();

#include "../String/String.h"
#include "../AVL/Tree.h"
#include "../Statistik/Statistik.h"

/* Memasukan teks ke dalam string dinamik dengan mengabaikan tanda baca dan angka */
String caseFolding(String text, char *location);

addrStat Tokenizing(String text, int doc, addrStat root);

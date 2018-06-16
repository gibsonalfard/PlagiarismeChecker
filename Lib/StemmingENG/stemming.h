#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0
#define INC 50           /* size units in which s is increased */
#define LETTER(ch) (isupper(ch) || islower(ch))

int stem(char * p, int i, int j);

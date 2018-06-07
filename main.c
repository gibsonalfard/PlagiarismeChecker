#include <stdio.h>
#include <stdlib.h>
#include "lib/Function/Function.h"

int main(int argc, char *argv[]) 
{	
	char location[50] = "test.txt";
	String text = caseFolding(text, location);

	system("pause");	
	return 0;
}

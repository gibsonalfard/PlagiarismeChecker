#include <stdio.h>
#include <stdlib.h>

#include "lib/String/String.h"
#include "lib/AVL/Tree.h"

int main(int argc, char *argv[]) 
{
	address pohon = NULL;
	
	AVLTree(&pohon, "Ilham");
	PrintInorder(pohon);
	
	system("pause");	
	return 0;
}

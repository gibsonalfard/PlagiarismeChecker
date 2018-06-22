#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

int main(int argc, char *argv[]) 
{
	Queue Q;
	records info;
	char label[30];
	int i, same, total;
	
	CreateQueue(&Q);
	
	for(i=0;i<2;i++){
		printf("Label %d: ", i+1);	scanf("%s", label);
		printf("Same %d: ", i+1); scanf("%d",&same);
		printf("Total %d: ", i+1); scanf("%d", &total);
		
		strcpy(info.label,label);
		info.same = same;
		info.total = total;
		
		EnQueue(&Q, info);
	}
	
	printQueue(Q);
	
	system("pause");	
	return 0;
}

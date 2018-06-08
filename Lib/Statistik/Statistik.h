#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_DOC 3

typedef struct info{
	char kata[40];
	int amount[MAX_DOC];
} StatData;

typedef struct nodes* addrStat;

typedef struct nodes {
	addrStat parent;
	addrStat left;
	addrStat right;
	int height;
	StatData info;
} StatBlock;

//penambahan teks ke tree dan langsung dibuat avl
void AddStat (addrStat *root, char teks[], int numTeks);

//seimbang gak left right node
bool isBalance (addrStat node);

//proses penyeimbangan atau AVL
void BalancingTree (addrStat node, int pat1, int pat2);

void OrderDecrement (addrStat node);

int OrderHigher (addrStat left, addrStat right);

//menambah height parent dari node  baru
void OrderIncrement (addrStat node);

//penambahan node ke tree ssecara bst atau sorted
void AddTree (addrStat *root, StatData info, addrStat *newnode, int numOfTeks);

void NewOrder (addrStat node);

//bikin node baru
addrStat Alloc (StatData info);

void InorderStat (addrStat root);

void PreorderStat (addrStat root);

void toParent (addrStat *root);

void RefreshOrder (addrStat node);

//node diputar berlawanan arah jarum jam
void LeftRotation (addrStat node1, addrStat node2);

//node diputar searah jarum jam
void RightRotation (addrStat node1, addrStat node2);

void newNumberOfAmount(StatData *info, int numTeks);

void AmountPrint(StatData info);

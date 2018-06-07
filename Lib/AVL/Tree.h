#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct info{
	char kata[40];
	int amount;	
} infotype;

typedef struct node* address;

typedef struct node {
	address parent;
	address left;
	address right;
	int height;
	infotype info;
} Node;

//penambahan teks ke tree dan langsung dibuat avl
void AVLTree (address *root, char teks[]);

//seimbang gak left right node
bool BalanceNode (address node);

//proses penyeimbangan atau AVL
void Balancing (address node, int pat1, int pat2);

void DecreaseHeight (address node);

int Higher (address left, address right);

//menambah height parent dari node  baru
void IncreaseHeight (address node);

//penambahan node ke tree ssecara bst atau sorted
void InsertTree (address *root, infotype info, address *newnode);

void NewHeight (address node);

//bikin node baru
address NewNode (infotype info);

void PrintInorder (address root);

void PrintPreorder (address root);

void Rooter (address *root);

void RefreshHeight (address node);

//node diputar berlawanan arah jarum jam
void RotateLeft (address node1, address node2);

//node diputar searah jarum jam
void RotateRight (address node1, address node2);

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char infotype[40];

typedef struct node* addr;

typedef struct node {
	addr parent;
	addr left;
	addr right;
	int height;
	infotype info;
} Node;

//penambahan teks ke tree dan langsung dibuat avl
void AVLTree (addr *root, char teks[]);

//seimbang gak left right node
bool BalanceNode (addr node);

//proses penyeimbangan atau AVL
void Balancing (addr node, int pat1, int pat2);

void DecreaseHeight (addr node);

int Higher (addr left, addr right);

//menambah height parent dari node  baru
void IncreaseHeight (addr node);

//penambahan node ke tree ssecara bst atau sorted
void InsertTree (addr *root, infotype info, addr *newnode);

void NewHeight (addr node);

//bikin node baru
addr NewNode (infotype info);

void PrintInorder (addr root);

void PrintPreorder (addr root);

void Rooter (addr *root);

void RefreshHeight (addr node);

//node diputar berlawanan arah jarum jam
void RotateLeft (addr node1, addr node2);

//node diputar searah jarum jam
void RotateRight (addr node1, addr node2);

addr searchNode(addr root, char* word);

#include "Statistik.h"

//penambahan teks ke tree dan langsung dibuat avl
void AddStat (addrStat *root, String teks, int numTeks){
	StatData info;
	addrStat nodes = NULL;
	
	info.kata = teks;
	newNumberOfAmount(&info, numTeks);
	
	AddTree(&(*root), info, &nodes, numTeks);
	
	int pat1 = 0, pat2 = 0;
	while ( nodes->parent )
	{
		pat1 = pat2;
		
		if ( nodes == nodes->parent->right ) {
			pat2 = 1;
		} else {
			pat2 = 0;
		}
		
		nodes = nodes->parent;
		if ( !isBalance(nodes) ){
			BalancingTree( nodes, pat1, pat2);//printf("node %s %d\n",node->parent->info.kata, node->parent->height);
			nodes = nodes->parent;
//			
			toParent(&(*root));
		}
	}
}

//seimbang gak left right node
bool isBalance (addrStat node){
	int l = 0, r = 0;
	
	l = (node->left)? node->left->height+1: 0;
	r = (node->right)? node->right->height+1: 0;
	
	if (r-1 > l) {
		return false;
	} else if (l-1 > r) {
		return false;
	} else {
		return true;
	}
}

//proses penyeimbangan atau AVL
void BalancingTree (addrStat node, int pat1, int pat2){
	addrStat temp1, temp2, temp3;
	
	if ( pat2 == 1 ) {			
		temp2 = node->right;
		
		if ( pat1 == 1 ) {
			temp3 = node->right->right;
		} else {
			temp3 = node->right->left;
		}
	} 
	else {			
		temp2 = node->left;
		
		if ( pat1 == 1 ) {
			temp3 = node->left->right;
		} else {
			temp3 = node->left->left;
		}
	}
	
	temp1 = node;
	
	if ( pat1 == pat2 ) {
		if ( pat2 == 1 ) {
			LeftRotation(temp1, temp2);
		}
		else {
			RightRotation(temp1, temp2);
		}
	} 
	else {
		if ( pat2 == 1 ) {
			RightRotation(temp2, temp3);
			LeftRotation(temp1, temp3);
		}
		else {
			LeftRotation(temp2, temp3);
			RightRotation(temp1, temp3);
		}
	}	
}

void OrderDecrement(addrStat node);

int OrderHigher(addrStat left, addrStat right);

//menambah height parent dari node  baru
void OrderIncrement(addrStat node);

void newNumberOfAmount(StatData *info, int numTeks){
	int i;
	
	for(i = 1; i <= MAX_DOC; i++){
		(*info).amount[i-1] = (i == numTeks) ? 1 : 0;
	}
}

//penambahan node ke tree ssecara bst atau sorted
void AddTree(addrStat *root, StatData info, addrStat *newnode, int numOfTeks){
	if ( !(*root) ) {
		(*root) = Alloc(info);
		(*newnode) = (*root);
	}
	else {
		if ( strcmp((*root)->info.kata, info.kata) == 0 ) {
			(*root)->info.amount[numOfTeks-1]++;
			(*newnode) = (*root);
		}
		else if ( strcmp((*root)->info.kata, info.kata) == -1 ) {
			if ( (*root)->right ) {
				AddTree (&(*root)->right, info, &(*newnode), numOfTeks);
			} else {
				(*root)->right = Alloc(info);
				(*root)->right->parent = (*root);
				(*newnode) = (*root)->right;
				RefreshOrder((*newnode));
			}
		}
		else {
			if ( (*root)->left ) {
				AddTree (&(*root)->left, info, &(*newnode), numOfTeks);
			} else {
				(*root)->left = Alloc(info);
				(*root)->left->parent = (*root);
				(*newnode) = (*root)->left;
				RefreshOrder((*newnode));
			}
		}
	}
}

void NewOrder(addrStat node){
	if ( node->left && node->right ) {
		node->height = (node->left->height >= node->right->height) ? node->left->height+1 : node->right->height+1;
	}
	else if ( node->left ) {
		node->height = node->left->height+1;
	}
	else if ( node->right ) {
		node->height = node->right->height+1;
	}
	else {
		node->height = 0;
	}
}

//bikin node baru
addrStat Alloc (StatData info){
	
	addrStat node = (addrStat)malloc(sizeof(StatBlock));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	node->info = info;
	
	return node;
}

void InorderStat(addrStat root){
	if (root) {
		InorderStat(root->left);
		printf("%s",root->info.kata);
		AmountPrint(root->info);
		printf("\n");
		InorderStat(root->right);
	}
}

void AmountPrint(StatData info){
	int i;
	
	for(i=0;i<MAX_DOC;i++){
		printf(" %d", info.amount[i]);
	}
}

void PreorderStat (addrStat root);

void toParent(addrStat *root){
	while ( (*root)->parent )
	{
		(*root) = (*root)->parent;
	}
}

void RefreshOrder(addrStat node){
	if (node) {
		NewOrder(node);
		if (node->parent) {
			RefreshOrder(node->parent);
		}
	}
}

//node diputar berlawanan arah jarum jam
void LeftRotation(addrStat node1, addrStat node2){
	addrStat node = node1->right;
	node1->right = node2->left;
	node2->left = node2->parent;
	node2->parent = node1->parent;
	if (node1->parent) {
		if (node1->parent->right == node1) {
			node1->parent->right = node2;
		}
		else {
			node1->parent->left = node2;
		}
	}
	node1->parent = node;
	RefreshOrder(node2->left);
}

//node diputar searah jarum jam
void RightRotation (addrStat node1, addrStat node2){
	addrStat node = node1->left;
	node1->left = node2->right;
	node2->right = node2->parent;
	node2->parent = node1->parent;
	if (node1->parent) {
		if (node1->parent->right == node1) {
			node1->parent->right = node2;
		}
		else {
			node1->parent->left = node2;
		}
	}
	node1->parent = node;
	RefreshOrder(node2->right);
}

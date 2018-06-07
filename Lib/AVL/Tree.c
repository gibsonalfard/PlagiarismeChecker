#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "Tree.h"

void AVLTree (addr *root, char teks[])
{
	infotype info;
	addr node = NULL;
	
	strcpy( info.kata, teks);
	info.amount = 1;
	
	InsertTree( &(*root), info, &node); if (node->parent) printf("node : %s parent : %s\n",node->info.kata,node->parent->info.kata);
	
	int pat1 = 0, pat2 = 0;
	while ( node->parent )
	{
		pat1 = pat2;
		
		if ( node == node->parent->right ) {
			pat2 = 1;
		} else {
			pat2 = 0;
		}
		
		node = node->parent;
		if ( !BalanceNode(node) ){
			Balancing( node, pat1, pat2);//printf("node %s %d\n",node->parent->info.kata, node->parent->height);
			node = node->parent;
//			
			Rooter(&(*root));
		}
	}
}

void Rooter (addr *root)
{
	while ( (*root)->parent )
	{
		(*root) = (*root)->parent;
	}
}

bool BalanceNode (addr node)
{
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

void Balancing (addr node, int pat1, int pat2)
{printf("balancing, in\n");
	addr temp1, temp2, temp3;
	
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
			RotateLeft(temp1, temp2);
		}
		else {
			RotateRight(temp1, temp2);
		}
	} 
	else {
		if ( pat2 == 1 ) {
			RotateRight(temp2, temp3);
			RotateLeft(temp1, temp3);
		}
		else {
			RotateLeft(temp2, temp3);
			RotateRight(temp1, temp3);
		}
	}		
}

void DecreaseHeight (addr node)
{
	if ( node ) {
		node->height -= 1;
		DecreaseHeight( node->parent );
	} 
}

int Higher (addr left, addr right)
{
	if (left && right) {
		if (left->height >= right->height) {
			return left->height + 1;
		} else {
			return right->height + 1;
		}
	}
	else if (left) {
		return left->height + 1;
	}
	else {
		return right->height + 1;
	}
}

void IncreaseHeight (addr node)
{
	if ( node ) {
		node->height += 1;
		IncreaseHeight( node->parent );
	}
}

void InsertTree (addr *root, infotype info, addr *newnode)
{
	if ( !(*root) ) {
		(*root) = NewNode(info);
		(*newnode) = (*root);
	}
	else {
		if ( strcmp((*root)->info.kata, info.kata) == 0 ) {
			(*root)->info.amount++;
			(*newnode) = (*root);
		}
		else if ( strcmp((*root)->info.kata, info.kata) == -1 ) {
			if ( (*root)->right ) {
				InsertTree (&(*root)->right, info, &(*newnode));
			} else {
				(*root)->right = NewNode(info);
				(*root)->right->parent = (*root);
				(*newnode) = (*root)->right;
				RefreshHeight((*newnode));
			}
		}
		else {
			if ( (*root)->left ) {
				InsertTree (&(*root)->left, info, &(*newnode));
			} else {
				(*root)->left = NewNode(info);
				(*root)->left->parent = (*root);
				(*newnode) = (*root)->left;
				RefreshHeight((*newnode));
			}
		}
	}
}

void NewHeight (addr node)
{
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

addr NewNode (infotype info)
{
	addr node = (addr)malloc(sizeof(Node));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->height = 0;
	node->info = info;
	
	return node;
}

void PrintInorder (addr root)
{
	if (root) {
		PrintInorder(root->left);
		printf("%s",root->info.kata);
		PrintInorder(root->right);
	}
}

void PrintPreorder (addr root)
{
	if (root) {
		printf("%s %d %d",root->info.kata, root->info.amount, root->height);
		PrintPreorder(root->left);
		PrintPreorder(root->right);
	}
}

void RefreshHeight (addr node)
{
	if (node) {
		printf("\nrefresh, %s from %d to ",node->info.kata,node->height);
		NewHeight(node);
		printf("%d\n",node->height);
		if (node->parent) {
			RefreshHeight(node->parent);
		}
	}
}

void RotateLeft (addr node1, addr node2)
{
	addr node = node1->right;
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
	RefreshHeight(node2->left);
}

void RotateRight (addr node1, addr node2)
{
	addr node = node1->left;
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
	RefreshHeight(node2->right);
}

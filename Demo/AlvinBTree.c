#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "BTree.h"


void insertNoFullNode( BTree * tree, KeyType key) 
{

}

void splitFullNode( BTree tree) 
{
	BTree parent = tree->parent;
	int i = tree->keynum/2; // 分割后将要被提上去的索引位置

	
	BTreeNode *newNode = (BTreeNode *)calloc(BTREE_SIZE, 1);



}

void CreateBTree(BTree *tree, int length, KeyType array[])
{
	int i;
	BTree root = *tree;
	if(root==NULL)
	{
		root = (BTree)calloc(BTREE_SIZE, 1);
		root->is_leaf = 1;// 设置根结点为叶子结点
		root->keynum = 0;
		root->parent = NULL;//根结点的父结点设为NULL
		*tree = root;
	}


	for (i=0; i<length; i++)
	{
		//根结点没有满时
		if(root->keynum < MAXDEGREE-1)
		{
			// 从keynum到0找到要插入的位置，后边的数据后移
			insertNoFullNode(tree, array[i]);
		}else{
			splitFullNode(*tree);
		}
	}
}
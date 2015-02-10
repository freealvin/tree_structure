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
	int i = tree->keynum/2; // �ָ��Ҫ������ȥ������λ��

	
	BTreeNode *newNode = (BTreeNode *)calloc(BTREE_SIZE, 1);



}

void CreateBTree(BTree *tree, int length, KeyType array[])
{
	int i;
	BTree root = *tree;
	if(root==NULL)
	{
		root = (BTree)calloc(BTREE_SIZE, 1);
		root->is_leaf = 1;// ���ø����ΪҶ�ӽ��
		root->keynum = 0;
		root->parent = NULL;//�����ĸ������ΪNULL
		*tree = root;
	}


	for (i=0; i<length; i++)
	{
		//�����û����ʱ
		if(root->keynum < MAXDEGREE-1)
		{
			// ��keynum��0�ҵ�Ҫ�����λ�ã���ߵ����ݺ���
			insertNoFullNode(tree, array[i]);
		}else{
			splitFullNode(*tree);
		}
	}
}
//#include "BTree.h"
//#include <stdio.h>
//#include <stdlib.h>
//#include <memory.h>
//#include <assert.h>
//
//void alloc_tree(BTree *tree)
//{
//	if(0 == ((*tree) = (BTree) malloc (BTREE_SIZE)))
//	{
//		exit(-1);
//	}
//	memset((*tree), 0, BTREE_SIZE);
//	(*tree)->is_leaf = 1;
//}
//
//void insert_keys_to_tree(BTree *tree, int keys[], int n)
//{
//	int i;
//	for(i = 0; i < n; i++)
//	{
//		insert_key_to_tree(tree, keys[i]);
//	}
//}
//
//void insert_key_to_tree(BTree *tree, int key)
//{
//	if(tree == NULL)
//	{
//		alloc_tree(tree);
//	}
//	// ������ؼ�������������з���
//	if((*tree)->count == (MAXDEGREE-1))
//	{
//		BTree new_root = NULL;
//		alloc_tree(&new_root);
//		new_root->is_leaf = 0;
//		new_root->cs[0] = (*tree);
//		break_tree_child(&new_root, (*tree), 0); // ����
//		(*tree) = new_root;
//		insert_key_to_unfull_tree((*tree), key);
//	}
//	else
//	{
//		insert_key_to_unfull_tree((*tree), key);
//	}
//}
//
//void break_tree_child(BTree *tree, BTree *child, int i)
//{
//	int j = 0;
//	BTree rchild = NULL;
//
//	alloc_tree(rchild);
//	rchild->is_leaf = child->is_leaf; // ��ԭchildһ��
//	// ��ԭchild�ֳ���������
//	// ��ԭchild���Ҳ�r-1���ؼ�������rchild��keys��
//	for(j = 0; j < (MINDEGREE-1); j++)
//	{
//		rchild->keys[j] = child->keys[MINDEGREE+j];
//	}
//	rchild->count = MINDEGREE - 1;
//	// ��ԭchild���Ҳ��r+1����������rchild��cs��
//	for(j = 0; j < MINDEGREE; j++)
//	{
//		rchild->cs[j] = child->cs[MINDEGREE+j];
//	}
//	child->count = MINDEGREE - 1;
//
//	//��child�ĵ�r�����ؼ��ֲ���tree�ĵ�i��λ��
//	// ��tree�ӵ�i+1����(tree->count)λ�õ�cs����һλ
//	for(j=tree->count;j > i; j--)
//	{
//		tree->cs[j+1] = tree->cs[j];
//	}
//	tree->cs[i+1] = rchild;
//	// ���ӵ�i��(tree->count-1)λ�õĹؼ���ȫ�����Ų1
//	for(j=tree->count-1; j > i; j--)
//	{
//		tree->keys[j+1] = tree->keys[j];
//	}
//	tree->keys[i] = child->keys[MINDEGREE-1];
//	tree->count++;	
//	disk_write(tree);
//	disk_write(child);
//	disk_write(rchild);
//}
//
//void insert_key_to_unfull_tree(BTree *tree, int key)
//{
//	int i = 0;
//
//	// �����Ҷ�ӽ�㣬��ֱ�Ӳ��뼴�ɣ�����treeδȫ���������BTree����
//	if(tree->is_leaf == 1)
//	{
//		// �ҵ���Ҫ���²����λ��
//		i=tree->count-1;
//		while(i>=0 && key < tree->keys[i])
//		{
//			tree->keys[i+1] = tree->keys[i];
//			i--;
//		}
//		tree->keys[i+1] = key;
//		tree->count++;
//		disk_write(tree);
//	}
//	else
//	{ // ������ڽ�㣬�����ҵ�����Ѱ��λ�ú��ж����ӽ���Ƿ��Ѿ�ȫ������ȫ������ѣ�����������Ѱ��
//		i=tree->count-1;
//		while(i>=0 && key < tree->keys[i])
//		{
//			i--;
//		}
//		i++; // �ҵ�����Ѱ��λ��
//
//		disk_read(tree->cs[i]);
//		// ��������������������
//		if(tree->cs[i]->count == (MAXDEGREE-1))
//		{
//			break_tree_child(tree, tree->cs[i], i);
//			if(key > tree->keys[i])
//				i++;
//		}
//		insert_key_to_unfull_tree(tree->cs[i], key);
//	}
//}
//
//void disk_read(const BTree tree)
//{
//
//}
//
//void disk_write(const BTree tree)
//{
//
//}
//
//void display_tree(const BTree tree)
//{
//	if(tree==NULL || tree->count == 0)
//	{
//		return;
//	}
//
//	printf("(%d", tree->keys[0]);
//	int i = 0;
//	for(i = 1; i < tree->count; i++)
//	{
//		printf(",%d", tree->keys[i]);
//	}
//	printf(")");
//	if(0 == tree->is_leaf)
//	{
//		printf("(");
//		for(i = 0; i < tree->count+1; i++)
//		{
//			display_tree(tree->cs[i]);
//		}
//		printf(")");
//	}
//}
//
//int search_tree(const BTree tree, int key)
//{
//	if(tree==NULL)
//		return 0;
//	for(int i = tree->count-1; (i >= 0) && (key < tree->keys[i]); i--);
//	// �ڱ�������֮ǰ�ҵ�ƥ��ؼ���
//	if((i != -1) && (key == tree->keys[i]))
//	{
//		return 1;
//	}
//	i++;
//
//	if(1 == tree->is_leaf)
//	{
//		return 0;
//	}
//	else
//	{
//		return search_tree(tree->cs[i], key);
//	}
//}
//
//void delete_tree(BTree *tree, int key)
//{
//	if(0 == search_tree(tree, key))
//	{
//		return;
//	}
//
//	// ���ҹؼ���λ�ã�������
//	if( (tree->count==1) && (1 == tree->is_leaf))
//	{
//		free(tree);
//		tree = NULL;
//		return;
//	}
//	else if((tree->count==1) && (tree->keys[0] == key) && (tree->cs[0]->count == MINDEGREE-1) && (tree->cs[1]->count == MINDEGREE-1))
//	{
//		int j = 0;
//		BTree l_child = tree->cs[0], r_child = tree->cs[1];
//
//		l_child->keys[MINDEGREE-1] = tree->keys[0];
//		for(j = 0; j < r_child->count; j++)
//		{
//			l_child->keys[j+MINDEGREE] = r_child->keys[j];
//		}
//		for(j = 0; j < MINDEGREE; j++)
//		{
//			l_child->cs[MINDEGREE+j] = r_child->cs[j];
//		}
//		l_child->count = MAXDEGREE - 1;
//		free(r_child);
//
//		free(tree);
//		tree = l_child;
//		delete_unless_tree(tree, key);
//	}
//	else
//	{
//		delete_unless_tree(tree, key);
//	}
//}
//
//void delete_unless_tree(BTree *tree, int key)
//{	
//	// ���ҹؼ���λ�ã�������
//	int i = 0, j = 0;
//	for(i = tree->count-1; (i>=0) && (key < tree->keys[i]); i--);
//
//	// �����Ѿ�ȷ���ؼ����ڴ����У�������������ֱ��ɾ��
//	if(1 == tree->is_leaf)
//	{
//		// �����ӵ�i+1λ����(tree->count-1)λ�ùؼ��ֶ���ǰŲ1λ����tree->count--
//		for(j = i + 1; j < (tree->count); j++)
//		{
//			tree->keys[j-1] = tree->keys[j];
//		}
//		tree->count--;	
//	}
//	else if((i != -1) && (tree->keys[i] == key))
//	{// ����ؼ����ڴ������У���Ϊ�ڽ�㣬~
//		// case2a ���������д��ڵ���r����㣬����ǰ�̴���tree->key[i]�����������ӣ�����ݹ�ɾ��~
//		if(tree->cs[i]->count >= MINDEGREE)
//		{
//			int new_key = pre_succor_tree(tree, i);
//			tree->keys[i] = new_key;
//			delete_unless_tree(tree->cs[i], new_key);
//		}
//		else if(tree->cs[i+1]->count >= MINDEGREE)
//		{//case2b ���Һ��Ӵ��ڵ���r����㣬�����̴���tree->key[i], �������Һ��ӣ��ݹ�ɾ��~
//			int new_key = after_succor_tree(tree, i+1);
//			delete_unless_tree(tree->cs[i+1], new_key);
//		}
//		else
//		{//case2c �����Һ��Ӿ�Ϊr-1���ؼ��֣����轫ɾ������³������Һ��Ӻϲ�����ɾ��~
//			BTree l_child = tree->cs[i], r_child = tree->cs[i+1];
//
//			l_child->keys[MINDEGREE-1] = tree->keys[i];
//			for(j = 0; j < r_child->count; j++)
//			{
//				l_child->keys[j+MINDEGREE] = r_child->keys[j];
//			}
//			for(j = 0; j < MINDEGREE; j++)
//			{
//				l_child->cs[MINDEGREE+j] = r_child->cs[j];
//			}
//			l_child->count = MAXDEGREE - 1;
//			free(r_child);
//
//			// ��keys����(i+1)λ��(tree->count-1)λ��ǰ��1λ
//			for(j = i+1; j < (tree->count -1); j++)
//			{
//				tree->keys[j-1] = tree->keys[j];
//			}
//			// ��cs���д�(i+2)λ��(tree->count��λ��ǰ��1λ
//			for(j = i+2; j < tree->count; j++)
//			{
//				tree->cs[j-1] = tree->cs[j];
//			}
//			tree->count--;
//
//			delete_unless_tree(tree->cs[i], key);
//		}
//	}
//	else
//	{ // �������tree��keys�У���Ϊ�ڽ��~
//		i++; // �����Ӻ��ӵ���ȷλ��
//		if(tree->cs[i]->count >= MINDEGREE)
//		{// ����ؼ��ָ���>=��С��
//			delete_unless_tree(tree->cs[i], key);
//		}
//		else
//		{// ���������ֻ��MINDEGREE-1���ؼ��֣�����Ҫ���Ǵ��ֵܽ裬�����ֵܺϲ����
//			// case 3a ������Դ������ӽ�һ�ؼ���
//			if((i != 0) &&(tree->cs[i-1]->count >= MINDEGREE))
//			{
//				BTree ichild = tree->cs[i], lchild = tree->cs[i-1];
//				// ��i���ӵ������Ӻ�������1���Ա�Ϊlchild�����һ���Ӻ���������0λ��
//				for(j = tree->count; j >= 0; j--)
//				{
//					ichild->cs[j+1] = ichild->cs[j]; 
//				}
//				ichild->cs[0] = lchild->cs[lchild->count];
//				// ��i���ӵ����йؼ�������1���Ա�Ϊtree�е�(i-1)λ�õ�key������1��λ��
//				for(j = tree->count-1; j >= 0; j--)
//				{
//					ichild->keys[j+1] = ichild->keys[j];
//				}
//				ichild->keys[0] = tree->keys[i-1];
//				ichild->count++;
//
//				// ��tree�е�(i-1)λ�ؼ����滻��lchild�����ҹؼ���
//				tree->keys[i-1] = lchild->keys[lchild->count-1];
//
//				// ��lchild����������1
//				for(j = 0; j < lchild->count; j++)
//				{
//					lchild->cs[j] = lchild->cs[j+1];
//				}
//				// ��lchild�����ӹؼ�������1
//				for(j = 0; j < (lchild->count-1); j++)
//				{
//					lchild->keys[j] = lchild->keys[j+1];
//				}
//				lchild->count--;
//				delete_unless_tree(ichild, key);
//			}// if case 3a
//			else if((i != tree->count) && tree->cs[i+1]->count >= MINDEGREE)
//			{// case3a' ���child i�����ֵܹؼ��ֹ����衱(��>=MINDEGREE)
//				BTree ichild = tree->cs[i], rchild = tree->cs[i+1];
//				// ��rchild�ĵ�0���Ӻ�������ichild���Ӻ�����δλ����
//				ichild->cs[ichild->count+1] = rchild->cs[0];
//				// ��tree�ĵ�i���ؼ��ּ���ichild�Ĺؼ�����
//				ichild->keys[ichild->count] = tree->keys[i];
//				ichild->count++;				
//
//				// ��rchild�ĵ�0���ؼ��ָ�����tree��
//				tree->keys[i] = rchild->keys[0];
//
//				// ��rchild�������Ӻ�������1
//				for(j = 0; j < rchild->count; j++)
//				{
//					rchild->cs[j] = rchild->cs[j+1];
//				}
//				for(j = 0; j < (rchild->count-1); j++)
//				{
//					rchild->keys[j] = rchild->keys[j+1];
//				}
//				rchild->count--;
//				delete_unless_tree(ichild, key);
//			}// else if
//			else
//			{// case3b �����ֵܶ�ΪMINDEGREE-1�����
//				// ��û�����ֵܣ���i+1,ת�������ֵܵ�������д���
//				if(i == 0)
//				{
//					i++; 
//				}
//
//				BTree ichild = tree->cs[i];
//				BTree lchild = tree->cs[i-1];
//				// ��i���Ӻ����������ֵ�
//				for(j = 0; j < MINDEGREE; j++)
//				{
//					lchild->cs[j+MINDEGREE] = ichild->cs[j];
//				}
//				// ��tree�Ĺؼ���i-1�������ֵ���
//				lchild->keys[MINDEGREE-1] = tree->keys[i-1];
//				// ��i�Ĺؼ��ֶ��������ֵ���
//				for(j = 0; j < MINDEGREE-1; j++)
//				{
//					lchild->keys[MINDEGREE+j] = ichild->keys[j];
//				}
//				lchild->count = MAXDEGREE-1;
//				free(ichild);
//
//				// ����tree�е��Ӻ���λ��
//				for(j=i; j < tree->count; j++)
//				{
//					tree->cs[j] = tree->cs[j+1];
//				}
//				// ����tree�йؼ���λ��
//				for(j=i-1; j < (tree->count-1); j++)
//				{
//					tree->keys[j] = tree->keys[j+1];
//				}
//				tree->count--;
//				delete_unless_tree(lchild, key);
//			}
//		}// else
//	}// else
//}
//
//int pre_succor_tree(const BTree tree, int i)
//{
//	BTree p = tree->cs[i];
//	//ǰ��Ϊtree����������������Ҷ�ӽ��������һ���ؼ���
//	while((p->is_leaf == 0))
//	{
//		p = p->cs[p->count];
//	}
//	return p->keys[p->count-1];
//}
//
//int after_succor_tree(const BTree tree, int i)
//{
//	BTree p = tree->cs[i+1];	
//	//���Ϊtree������������Ҷ�ӽ��ĵ�һ���ؼ���
//	while(p->is_leaf == 0)
//	{
//		p = p->cs[0];
//	}
//	return p->keys[0];
//}
//////////////////////////////////////
//// �����������
//#define TEST_NUM 11
//int test_keys[TEST_NUM] = {10, 2, 1, 5, 4, 7, 8, 6, 13, 11, 14};
//
//int main_to_test()
//{
//	BTree tree = NULL;
//
//	insert_keys_to_tree(tree, test_keys, TEST_NUM);
//	display_tree(tree);
//
//	delete_tree(tree, 1);
//	printf("\n\nafter delete 1:\n");
//	display_tree(tree);
//
//	delete_tree(tree, 7);
//	printf("\n\nafter delete 7:\n");
//	display_tree(tree);
//
//	delete_tree(tree, 4);
//	printf("\n\nafter delete 4:\n");
//	display_tree(tree);
//
//	delete_tree(tree, 2);
//	printf("\n\nafter delete 2:\n");
//	display_tree(tree);
//
//	printf("\n");
//	return 0;
//}
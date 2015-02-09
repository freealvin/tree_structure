#ifndef _BTREE_H 
#define _BTREE_H

#define MINDEGREE 3 // ����BTree����С��
#define MAXDEGREE (MINDEGREE*2)

// ����BTree�����ݽṹ
typedef void* NodeData;

typedef struct _targBTreeNode
{
	NodeData	data; // 
	struct _targBTreeNode*	cs[MAXDEGREE]; //����ָ������
	int	keys[MAXDEGREE-1]; //�ؼ�������
	int count; // �ؼ��ָ���
	int is_leaf; // �Ƿ�ΪҶ�ӽ��
} BTreeNode, *BTree;

#define BTREE_SIZE sizeof(BTreeNode)

void alloc_tree(BTree *tree); //�����ڴ� 
void insert_keys_to_tree(BTree *tree, int keys[], int n); //��keys������tree��
void insert_key_to_tree(BTree *tree, int key); // ��key����������tree��
void insert_key_to_unfull_tree(BTree *tree, int key); // ��key�ؼ��ֲ�����δ������tree�� 
void break_tree_child(BTree *tree, BTree *child, int i); // ��tree�ĵ�i���Ӻ��ӷ���
void disk_read(const BTree tree); // ��������̣�δʵ��
void disk_write(const BTree tree); // ����д���̣�δʵ��
void display_tree(const BTree tree); // ��ʾBTree
int search_tree(const BTree tree, int key); // ����BTree���Ƿ���ڹؼ���
void delete_tree(BTree *tree, int key); // ɾ��BTree�е�ĳһ�ؼ��֣���Ҫ����BTreeΪ�յ��������~
void delete_unless_tree(BTree *tree, int key); // ɾ��BTree�е�ĳһ����~
int pre_succor_tree(const BTree tree, int i); // ��tree�е�iλ�ؼ��ֵ�ǰ��~
int after_succor_tree(const BTree tree, int i); // ��Btree�е�iλ�ؼ��ֵĺ��~

#endif
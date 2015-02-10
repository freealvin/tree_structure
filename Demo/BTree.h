#ifndef _BTREE_H 
#define _BTREE_H

#define MINDEGREE 3 // ����BTree����С��
#define MAXDEGREE (MINDEGREE*2)

// ����BTree�����ݽṹ
typedef int KeyType;

typedef struct BTNode
{
	KeyType	data; // 
	struct BTNode*	child[MAXDEGREE]; //����ָ������
	struct BTNode *parent;
	int	keys[MAXDEGREE-1]; //�ؼ�������
	int keynum; // �ؼ��ָ���
	int is_leaf; // �Ƿ�ΪҶ�ӽ��
} BTreeNode, *BTree;

#define BTREE_SIZE sizeof(BTreeNode)


#endif
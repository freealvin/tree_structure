#ifndef _BTREE_H 
#define _BTREE_H

#define MINDEGREE 3 // 定义BTree的最小度
#define MAXDEGREE (MINDEGREE*2)

// 定义BTree的数据结构
typedef int KeyType;

typedef struct BTNode
{
	KeyType	data; // 
	struct BTNode*	child[MAXDEGREE]; //孩子指针数组
	struct BTNode *parent;
	int	keys[MAXDEGREE-1]; //关键字数组
	int keynum; // 关键字个数
	int is_leaf; // 是否为叶子结点
} BTreeNode, *BTree;

#define BTREE_SIZE sizeof(BTreeNode)


#endif
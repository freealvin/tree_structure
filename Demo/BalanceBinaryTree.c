#include <stdlib.h>
#include <stdio.h>
/**********************************************http://c.biancheng.net/cpp/u/shuju/************/

/*
* @brief : 二叉树结构体声明
* @author : alvin
* @date : 2015/1/30 10:17
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
struct bin_tree{
	int data;
	struct bin_tree *right, *left;
	int height;
};

typedef struct bin_tree node;

/*
* @brief : 获得两个整数中较大的一个
* @author : alvin
* @date : 2015/1/30 15:53
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
int max_value(int a, int b)
{
	if(a-b>0)
		return a;
	else
		return b;
}

/*
* @brief : 获得结点的高度
* @author : alvin
* @date : 2015/1/30 16:03
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
int getHeight(node *tree){
	if(tree==NULL)
		return 0;
	return max_value(getHeight(tree->left), getHeight(tree->right))+1;

}

// 左左
/*                     8                         6
*                     / \                       / \
*                    6   9       =>            4   8
*                   / \                       /   / \
*                  4   7                     2   7   9
*                 /
*                2
*                      8                        6
*                     /                        / \
*                    6       =>               4   8
*                   /
*                  4
* 
*/
node *DealLL(node *tree)
{
	node *temp = tree->left;
	tree->left = temp->right;
	temp->right = tree;

	//tree->height -= 1;
	
	return temp;
}

//右右

node *DealRR(node *tree)
{
	node *temp = tree->right;
	tree->right = temp->left;
	temp->left = tree;
	return temp;
}

//左右
/*                     4                         6
*                     / \                       / \
*                    2   6       =>            4   8
*                       / \                   / \   \
*                      5   8                 2   5   9
*                           \
*                            9
*                
*                  4                            6
*                   \                          / \
*                    6       =>               4   8
*                     \
*                      8
* 
*/
node *DealLR(node *tree)
{
	//to LL
	node *temp = tree->left->right;
	tree->left->right = temp->left;
	temp->left = tree->left;
	tree->left = temp;

	//DealLR
	return DealLL(tree);
}

//右左
node *DealRL(node *tree)
{
	//to RR
	node *temp = tree->right->left;
	tree->right->left = temp->right;
	temp->right = tree->right;
	tree->right = temp;

	//DealRR
	return DealRR(tree);
}

/*
* @brief : 检测树是否平衡
* @author : alvin
* @date : 2015/1/30 16:24
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
int checkValid(node *tree)
{
	if(tree==NULL)
		return 1;
	else
	{

		int left = getHeight(tree->left);
		int right = getHeight(tree->right);
		if(left-right>1||right-left>1)
			return 0;
		else
			return 1;

	}

}



/*
* @brief : 向平衡二叉树里插入一个值
* @author : alvin
* @date : 2015/1/30 10:17
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/

node *insert(node **tree, int val)
{
	node *temp = NULL;
	if(!(*tree))
	{
		temp = (node*) malloc (sizeof(node));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;
		return *tree;

	}

	if(val < (*tree)->data)
	{
		node *newNode = insert(&((*tree)->left), val);
		if(!checkValid(*tree))
		{
			if ((*tree)->left->data> val)
			{
				*tree = DealLL(*tree);
			}else{
				*tree = DealLR(*tree);
			}
		}

		return newNode;
	}

	else if(val > (*tree)->data)
	{
		node *newNode = insert(&((*tree)->right), val);
		if(!checkValid(*tree))
		{
			if ((*tree)->right->data < val)
			{
				*tree = DealRR(*tree);
			}else{
				*tree = DealRL(*tree);
			}
		}

		return newNode;
	}else //不处理值已经存在的数据
	{
		return NULL;
	}

}



//插入后
//左侧比右侧高度大2
//		1）插入结点在左侧的左子树上
//		2) 新结点在左侧的右子树上
//右侧比左侧高度大2
//		1）新结点在右侧的左子树上
//		2）新结点在右侧的子树上
//


/*
* @brief : 在二叉树中查找节点值为val的结点并反回结点的地址
* @author : alvin
* @date : 2015/1/30 10:29
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
node * find(node *tree, int val)
{
	if(tree==NULL)
	{
		return NULL;
	}

	if(tree->data == val)
	{
		return tree;
	}

	if(tree->data > val){
		return find(tree->left, val);
	}

	if(tree->data < val)
	{
		return find(tree->right, val);
	}

	return NULL;
}

/*
 * 调整btNode子树
 */
node* adjust(node * btNode)
{
	node *temp ;
	if(btNode->right!=NULL)
	{
		if(btNode->right->left!=NULL)
		{
			temp =  btNode->right->left;
			btNode->right->left = adjust(btNode->right->left);
			btNode->right->left->left = btNode->left;
			btNode->right->left->right = btNode->right;
			return temp;
		}else
		{
			btNode->right->left = btNode->left;
			return btNode->right;
		}
	}else
	{
		return btNode->left;
	}

}

/*
* @brief : 删除二叉树的结点
* @author : alvin
* @date : 2015/1/30 10:20
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
node * deleteNode(node *tree, int val)
{
	/*
	 * 1. 找到要删除的结点的地址
	 */
	node *destNode = find(tree, val);
	node *temp;
	node *p;
	if(destNode==NULL)
	{
		printf("没有找到值为%d的结点，删除失败\n",val);
		return tree;
	}

	// 2. 调整目标结点的子树，找到一个可以替代要删除的目标结点的节点，并把要删除的目标结点删除
	/*
	 * 要删除的目标结点是根节点
	  */
	if(destNode == tree)
	{
		printf("根节点为要找的结点\n");
		temp = adjust(destNode);
		free(destNode);
		return temp;
	}else{
		p = tree;
		while(p){
			if(p->left == destNode){
				temp = adjust(p->left);
				free(destNode);
				p->left = temp;
				break;
			}else if(p->right == destNode)
			{
				temp = adjust(p->right);
				free(destNode);
				p->right = temp;
				break;
			}else{
				if(destNode->data < p->data){
					p = p->left;
				}else{
					p = p->right;
				}
			}
		}

		return tree;
	}

}
/*
* @brief : 删除释放二叉树
* @author : alvin
* @date : 2015/1/30 10:17
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}

/*
* @brief : 前序遍历
* @author : alvin
* @date : 2015/1/30 10:18
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void pre_print(node *tree)
{
	if(tree)
	{
		printf("%d\n", tree->data);
		pre_print(tree->left);
		pre_print(tree->right);
	}
}

/*
* @brief : 中序遍历二叉树
* @author : alvin
* @date : 2015/1/30 10:18
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void in_print(node *tree)
{
	if(tree)
	{
		in_print(tree->left);
		printf("address:%p, data: %d, height:%d\n", tree, tree->data, getHeight(tree));
		/*if(tree->left!=NULL)
		{
			printf("left address:%p\n", tree->left);
		}

		if(tree->right!=NULL)
		{
			printf("right address:%p\n", tree->right);
		}*/
		in_print(tree->right);
	}
}


/*
* @brief : 后续遍历二叉树
* @author : alvin
* @date : 2015/1/30 10:18
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void post_print(node *tree)
{
	if(tree)
	{
		post_print(tree->left);
		post_print(tree->right);
		printf("%d\n", tree->data);
	}
}


/*
* @brief : 查找大于min并且小于max的值
* @author : alvin
* @date : 2015/1/30 10:18
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void searchRange(node *tree, int min, int max)
{
	if(tree)
	{
		if(min < tree->data)
		{
			searchRange(tree->left, min,  max);
		}

		if(min<=tree->data && max>=tree->data)
		{
			printf("%d\n", tree->data);
		}

		if(min>tree->data || max>tree->data)
		{
			searchRange(tree->right, min, max);
		}
	}else
	{
		return;
	}
}



int main6()
{
	node *tree = NULL, *temp;
	int n = 10;
	int arr[10] = {9,8,4,5,6,7,2, 3,1, 13};
	int i;
	for(i=0; i<n; i++)
	{
		temp = insert(&tree, arr[i]);
		printf("new node address:%p\n", temp);
		pre_print(tree);
	}

	in_print(tree);

	deltree(tree);

	system("pause");
	return 0;
}
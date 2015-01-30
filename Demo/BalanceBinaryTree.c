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
	int left = getHeight(tree->left);
	int right = getHeight(tree->right);
	if(left-right>1||right-left>1)
		return 0;
	else
		return 1;

}

void balance(node *true)
{
	/*http://www.cppblog.com/cxiaojia/archive/2012/08/20/187776.html**/
	printf("need to do something here\n");
}

/*
* @brief : 向二叉树里插入一个值
* @author : alvin
* @date : 2015/1/30 10:17
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void insert(node **tree, int val)
{
	node *temp = NULL;
	if(!(*tree))
	{
		temp = (node*) malloc (sizeof(node));
		temp->left = temp->right = NULL;
		temp->data = val;
		*tree = temp;

	}

	if(val < (*tree)->data)
	{
		insert(&((*tree)->left), val);

	}

	else if(val > (*tree)->data)
	{
		insert(&((*tree)->right), val);
	}

}

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
		printf("data: %d, height:%d\n", tree->data, getHeight(tree));
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



int main()
{
	node *tree = NULL;
	int n = 10;
	int arr[10] = {8,6, 4,5,7,2, 3,   9, 1, 13};
	int i;
	for(i=0; i<n; i++)
	{
		insert(&tree, arr[i]);
		if(checkValid(tree))
		{
			printf("插入值%d后，树仍旧平衡\n", arr[i]);
		}else
		{
			printf("插入值%d后，树已经不平衡\n", arr[i]);
			balance(tree);
		}
	}

	in_print(tree);

	deltree(tree);

	system("pause");
	return 0;
}
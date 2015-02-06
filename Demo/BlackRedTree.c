#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


typedef struct Node{
	int data;
	struct Node *left;
	struct Node *right;
	struct Node *parent;
	int color;//0:red, 1:black
};

typedef struct Node RBNode;

static void pre_print(RBNode *tree)
{
	if(tree)
	{
		printf("%d\n", tree->data);
		pre_print(tree->left);
		pre_print(tree->right);
	}
}

RBNode* grandP(RBNode *node){
	return node->parent!=NULL ? node->parent->parent : NULL; 

}

RBNode* uncle(RBNode *node)
{
	if(node->parent != NULL){
		if(node->parent->parent != NULL)
		{
			if(node->parent == node->parent->parent->left)
			{
				return node->parent->parent->right;
			}else{
				return node->parent->parent->left;
			}
		}else
		{
			return NULL;
		}

	}

	return NULL;
}

RBNode *RightRoate(RBNode *tree)
{
	RBNode *temp = tree->left;
	if(temp->right!=NULL)
		temp->right->parent = tree;
	tree->left = temp->right;

	temp->parent = tree->parent;
	tree->parent = temp;
	temp->right = tree;

	return temp;
}


RBNode *LeftRoate(RBNode *tree)
{
	RBNode *temp = tree->right;
	if(temp->left!=NULL)
		temp->left->parent = tree;
	tree->right = temp->left;

	temp->parent = tree->parent;
	tree->parent = temp;
	temp->left = tree;
	return temp;
}
/*
* @brief : 红黑树插入节点后调整
* @author : alvin
* @date : 2015/2/6 11:54
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
void RB_INSERT_FIXUP(RBNode **T, RBNode *z){

	if(z!=NULL&&z->color == 0 && z->parent&& z->parent->color==0){

		RBNode *parent  = z->parent;
		RBNode *u = uncle(z);
		RBNode *g = grandP(z);

		//父节点和叔叔结点皆为红色
		if(u!=NULL&&u->color==0)
		{
			parent->color = 1;
			u->color = 1;
			g->color = 0;
			RB_INSERT_FIXUP(T, g);//设祖父结点为当前结点，继续调整
		}else{//叔叔结点为空或者为黑色
			if(parent->right == z){//当前结点是父结点的右子结点
				RBNode *temp = NULL;
				temp 	 = LeftRoate(parent);
				//左旋
				if(g->left == parent){
					temp->parent = g;
					g->left = temp;
					RB_INSERT_FIXUP(T, temp->left);
				}else{
					temp->parent = g;
					g->right = temp;
					RB_INSERT_FIXUP(T, temp->left);
				}
			}else{
				parent->color = 1;
				g->color = 0;
				RBNode *temp = NULL;
				temp = RightRoate(parent);//保存子树旋转后的根结点

				if(g->parent!=NULL){//判断是不是到根节点了
					RBNode *gg = g->parent;
					if(gg->left == g){
						gg->left = temp;
						temp->parent = gg;
					}else{
						gg->right = temp;
						temp->parent = gg;
					}

				}else{
					*T = temp;
				}
			}
		}

	}


	*T->color = 1;//根节点涂成黑色
}



void RB_INSERT(RBNode **tree, int val)
{
	RBNode *temp;
	RBNode *x = *tree;
	RBNode *y = NULL;
	while (x!=NULL){
		y = x;
		if(val < x->data)
			x = x->left;
		else
			x = x->right;
	}

	if(y == NULL){
		*tree = (RBNode *)malloc(sizeof(RBNode));
		(*tree)->color = 1;
		(*tree)->left = NULL;
		(*tree)->right = NULL;
		(*tree)->parent = NULL;
		(*tree)->data = val;
	}else{
		temp = (RBNode *)malloc(sizeof(RBNode));
		temp->left = NULL;
		temp->right = NULL;
		temp->parent = y;
		temp->color = 0;
		temp->data  = val;

		if(val < y->data){
			y->left = temp;
			
		}else
		{
			y->right = temp;
		}

		//只有父节点为红时才调整
		if(temp->parent->color==0){
			RB_INSERT_FIXUP(tree, temp);
		}
	}
}
int main()
{
	RBNode *root = NULL;
	int arr[20] = {12,1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
	int i=0;
	for(;i<20; i++){
		RB_INSERT(&root, arr[i]);
		pre_print(root);
		printf("********************************************************************");
	}
	return 0;
}
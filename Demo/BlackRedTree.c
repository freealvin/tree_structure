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
		printf("value: \t%d, \tcolor:\t%s\n", tree->data, tree->color==0?"red":"black");
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

/*
* @brief : �����������
* @author : alvin
* @date : 2015/2/9 13:29
* @version : ver 1.0
* @inparam : 
* @outparam :����������������ĸ���� 
*/
RBNode *RightRoate(RBNode *tree)
{
	RBNode *temp = tree->left;
	printf("��%dΪ���������\n",tree->data);
	if(temp->right!=NULL)
		temp->right->parent = tree;
	tree->left = temp->right;

	temp->parent = tree->parent;
	tree->parent = temp;
	temp->right = tree;

	return temp;
}


/*
* @brief : �����������
* @author : alvin
* @date : 2015/2/9 13:28
* @version : ver 1.0
* @inparam : 
* @outparam : 
*/
RBNode *LeftRoate(RBNode *tree)
{
	
	RBNode *temp = tree->right;
	printf("��%dΪ���������\n",tree->data);
	if(temp->left!=NULL)
		temp->left->parent = tree;
	tree->right = temp->left;

	temp->parent = tree->parent;
	tree->parent = temp;
	temp->left = tree;
	return temp;
}
/*
* @brief : ���������ڵ�����
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
		RBNode *temp;
		RBNode *gParent ;//�游���ĸ��ڵ�

		// ���ڵ���������Ϊ��ɫ��������ڣ��������ڣ��游����죬
		// �游����������ƻ�������ĺ�����ʣ����游���Ϊ��ǰ������
		if(u!=NULL&&u->color==0)
		{
			parent->color = 1;
			u->color = 1;
			g->color = 0;
			RB_INSERT_FIXUP(T, g);// ���游���Ϊ��ǰ��㣬��������
		}else{// ������Ϊ�ջ���Ϊ��ɫ



			if(parent == g->left){// 1. ��������游��������ʱ
					if(parent->right == z){// a.��ǰ����Ǹ��������ӽ�㣺����������b״̬
						temp = NULL;
						temp 	 = LeftRoate(parent);
						//����
						if(g->left == parent){
							temp->parent = g;
							g->left = temp;
							RB_INSERT_FIXUP(T, temp->left);
						}else{
							temp->parent = g;
							g->right = temp;
							RB_INSERT_FIXUP(T, temp->left);
						}
					}else{// b.��ǰ����Ǹ��������ӽ�㣺����ڣ��游��죬��������
						parent->color = 1;
						g->color = 0;
						temp = NULL;
						gParent = g->parent;// �����游���ĸ����
						temp = RightRoate(g);// ����������ת��ĸ����
				

						if(gParent!=NULL){// �ж��ǲ��ǵ����ڵ���
							if(gParent->left == g){
								gParent->left = temp;
								temp->parent = gParent;
							}else{
								gParent->right = temp;
								temp->parent = gParent;
							}

						}else{
							*T = temp;
						}
					}
			}else// 2.��������游�����Һ���ʱ���븸������游�������ӶԳƵ���
				{
					if(z==parent->left){//c).��ǰ����Ǹ��������ӣ�����������������d״̬
						// �Ը����Ϊ���������
						temp = NULL;
						temp 	 = RightRoate(parent);
						// ��������ĵ�ǰ���Ϊ��ǰ����������
						if(g->left == parent){
							temp->parent = g;
							g->left = temp;
							RB_INSERT_FIXUP(T, temp->right);
						}else{
							temp->parent = g;
							g->right = temp;
							RB_INSERT_FIXUP(T, temp->right);
						}

					}else// d).��ǰ����Ǹ������Һ��ӣ�����ڣ��游��죬����
					{
						parent->color = 1;
						g->color = 0;
						temp = NULL;
						gParent = g->parent;

						temp = LeftRoate(g);


						if(gParent!=NULL){// �ж��ǲ��ǵ����ڵ���
							if(gParent->left == g){
								gParent->left = temp;
								temp->parent = gParent;
							}else{
								gParent->right = temp;
								temp->parent = gParent;
							}

						}else{
							*T = temp;
						}

					}

			}

		}

	}


	(*T)->color = 1;//���ڵ�Ϳ�ɺ�ɫ
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

		//ֻ�и��ڵ�Ϊ��ʱ�ŵ���
		if(temp->parent->color==0){
			RB_INSERT_FIXUP(tree, temp);
		}
	}
}
int main10()
{
	RBNode *root = NULL;
	int arr[20] = {12,1, 9, 2, 0, 11, 7, 19, 4, 15, 18, 5, 14, 13, 10, 16, 6, 3, 8, 17};
	int i=0;
	for(;i<20; i++){
		RB_INSERT(&root, arr[i]);
		pre_print(root);
		printf("********************************************************************\n");
	}
	return 0;
}
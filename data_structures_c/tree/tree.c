#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "tree.h"	 /*current header */
#define MAGIC_NUM 23005363
#define TREE_IS_EMPTY(tree)\
		 (tree -> m_root == NULL)
#define IS_LEAF(m_root)\
		(m_root -> m_left == NULL && m_root -> m_right == NULL)
#define HAS_ONE_SUN_RIGTH(m_root)\
		(m_root -> m_left == NULL && m_root -> m_right != NULL)
#define HAS_ONE_SUN_LEFT(m_root)\
		(m_root -> m_left != NULL && m_root -> m_right == NULL)
#define HAS_TWO_SUNS(m_root)\
		(m_root -> m_left != NULL && m_root -> m_right != NULL)
#define MAX(num1,num2)\
		(num1 > num2 ? num1 : num2)		/*sets the variable max to the larger of the two variables num1 and num2*/


void printPreOrderTree(Node* _root);
void PrintPostOrder(Node* _node);
void PrintInOrder(Node* _node);
void DestroyNode(Node *_root);
Node* FindData(Node *_root, int _data);
Node* NodeCreate(int _data, Node *_father);

int isFullTree(Tree* _tree);
static int isFullTreeRec(Node* _node);
int AreSimilarTree(Tree* _tree1, Tree* _tree2);
static int AreSimilarTreeRec(Node* _node1, Node* _node2);
int CalcTreeLevel(Tree* _tree);
static int CalcTreeLevelRec(Node* _node);
int MirrorTree(Tree* _tree);
void MirrorTreeRec(Node* _node);

struct Node
{
	int m_data;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};
/***************************/
struct Tree
{
	Node* m_root;
	int m_magicNum;
};
/****************************/

Tree* TreeCreate()
{
	Tree* PTree;
	if((PTree = (Tree*)malloc(sizeof(Tree))) == NULL)
	{
		return NULL;
	}
	PTree -> m_root = NULL;
	PTree -> m_magicNum = MAGIC_NUM;
	return PTree;
}
/**********************************************/
void TreeDestroy(Tree* _tree)
{
	if ( NULL == _tree || _tree ->m_magicNum != MAGIC_NUM) 
     {
		return;
     }
  	
	DestroyNode(_tree -> m_root);
  
	_tree ->m_magicNum = 0;
	free(_tree);	
	return;	

}
/**********************************************/
ADTErr TreeInsert(Tree* _tree, int _data)
{
	Node *newNode = NULL;
	Node *pFather = NULL;
	
	if ( NULL == _tree)
	{
		return ERR_NOT_INITIALIZED;
     }
	if ( NULL == _tree -> m_root)
	{
		if(NULL == (newNode = NodeCreate(_data, NULL)))
		{
			return ERR_ALLOCATION_FAILED;
		}
		_tree -> m_root = newNode;
     }
     if (NULL == (pFather = FindData( _tree -> m_root, _data)))
     {
     	return ERR_DOUBLE_DATA;	
     }
     else
     {
    	if ((newNode = NodeCreate (_data ,pFather)) == NULL)
    	{
    		return ERR_ALLOCATION_FAILED;
    	}
    	if(pFather -> m_data < _data)
    	{
    		pFather -> m_right = newNode;
    	}
    	else if(pFather -> m_data > _data)
    	{
    		pFather -> m_left = newNode;
    	}
    	
    	return ERR_OK;
     }

}   
/***********************************************/
void TreePrint(Tree* _tree, TreeTraverse _traverseMode)
{
    if (_tree == NULL)
    {
    	 return;
    }
    
    if (_traverseMode == PRE_ORDER)
    {
    	printPreOrderTree( _tree ->m_root);
    }
	else if (_traverseMode == IN_ORDER)
	{
		PrintInOrder( _tree ->m_root);
	}
	else if (_traverseMode == POST_ORDER) 
	{
		PrintPostOrder(_tree ->m_root);
	}   

}
/*************************************************/
int TreeIsDataFound(Tree* _tree, int _data)
{
	if (_tree == NULL)
	{
		return FALSE;
	}	
	if(NULL != FindData(_tree -> m_root, _data))
	{
		return FALSE;
	}
	return TRUE;
}

/********************************************************/
/********************************************************/
/*****************HELP FUNCTION**************************/
/********************************************************/

void PrintInOrder(Node* _node)
{
	if(NULL == _node)
	{
		return;
	}
	PrintInOrder(_node -> m_left); /*first recur on m_left subtree */
	printf("%d ", _node -> m_data); /* print data of node*/
	PrintInOrder(_node -> m_right); /*recur on m_right subtree
 */
}
/**********************************************/
void PrintPostOrder(Node* _node)
{
	if(NULL == _node)
	{
		return;
	}
	PrintPostOrder(_node -> m_left); /*first recur on m_left subtree */
	PrintPostOrder(_node -> m_right); /*recur on m_right subtree */
	printf("%d ", _node -> m_data); /* print data of node*/
}
/************************************************/
void printPreOrderTree(Node* _root)
{
	if (_root == NULL)
    {
    	return;
    }
        
	printf("%d ", _root->m_data);
    printPreOrderTree(_root-> m_left);
    printPreOrderTree(_root-> m_right);
}
/***********************************************/

void DestroyNode(Node *_root)
{
	if(NULL == _root)
	{
		return;
	}
	DestroyNode(_root -> m_left);
	DestroyNode(_root -> m_right);
	free(_root);
}
/**********************************************/
Node* FindData(Node *m_root, int _data)
{
	Node* iNode =m_root;
	Node* last;
	while(iNode != NULL)
	{
		last = iNode;
		if(iNode-> m_data > _data)
		{
			iNode = iNode -> m_left;
		}
		 else if(iNode -> m_data < _data)
		{
			iNode = iNode -> m_right;
		}
		else
		{
			return NULL;
		}
	}
	return last;
}
/*****************************************************/
Node* NodeCreate(int _data, Node *_father)
{
	Node *pNode = NULL;

	if ((pNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return NULL;
 	}
	
	 pNode -> m_data = _data;
 	 pNode -> m_left = NULL;
 	 pNode -> m_right = NULL;
 	 pNode -> m_father = _father; /**/
 	
 	return pNode;
}
/*********************************************/
Node* GetRoot(Tree*  _ptrTree)
{
	return  _ptrTree -> m_root;
}


int GetRootData(Tree*  _ptrTree)
{
	return  _ptrTree -> m_root -> m_data;
}


int GetMagicNum(Tree* _ptrTree)
{
	return _ptrTree -> m_magicNum;
}


int GetRootLeftData(Tree* _ptrTree)
{
	return  _ptrTree -> m_root -> m_left -> m_data;
}


int GetRootRightData(Tree* _ptrTree)
{
	return  _ptrTree -> m_root -> m_right -> m_data;
}
/****************************************************/
/****************************************************/
/*******************targil *************************/

int isFullTree(Tree* _tree)
{
	if(_tree == NULL)
	{
		return FALSE;
	}
	if(isFullTreeRec(_tree -> m_root) == TRUE)
	{
		return TRUE;
	}
	return FALSE;

}

static int isFullTreeRec(Node* _node)
{
	if(NULL == _node)	
	{
		return FALSE;	
	}
	if(HAS_ONE_SUN_RIGTH(_node) || HAS_ONE_SUN_LEFT(_node))
	{
		return FALSE;
	}
	if(HAS_TWO_SUNS(_node) || IS_LEAF(_node))
	{
		return TRUE;
	}
	return (isFullTreeRec(_node -> m_left) && isFullTreeRec(_node -> m_right));
}

/*******************************************************/

int AreSimilarTree(Tree* _tree1, Tree* _tree2)
{
	if(_tree1 == NULL || _tree2 == NULL)
	{
		return FALSE;
	}
	return AreSimilarTreeRec(_tree1 -> m_root, _tree2 -> m_root);		
}

static int AreSimilarTreeRec(Node* _node1, Node* _node2)
{
	if(NULL == _node1 && NULL ==_node2)
	{
		return TRUE;
	}
	if(NULL == _node1 || NULL ==_node2)
	{
		return FALSE;
	}
	return (AreSimilarTreeRec(_node1 -> m_right, _node2 -> m_right) && AreSimilarTreeRec(_node1 -> m_left, _node2 -> m_left));
	
}

/****************************************************/

int CalcTreeLevel(Tree* _tree)
{
	if(NULL == _tree)	
	{
		return -1;	
	}
	return CalcTreeLevelRec(_tree -> m_root );;
}

static int CalcTreeLevelRec(Node* _node)
{
	if(NULL == _node)
	{
		
		return 0;
	}

	return (MAX(CalcTreeLevelRec(_node -> m_left), CalcTreeLevelRec(_node -> m_right))+1);
}
	
/*****************************************************/

int MirrorTree(Tree* _tree)
{
	Tree* mirrorTree = TreeCreate();

	if(NULL == _tree)	
	{
		return ERR_NOT_INITIALIZED;	
	}
	mirrorTree -> m_root = _tree -> m_root;
	MirrorTreeRec(_tree -> m_root);
	return ERR_OK;
}


void MirrorTreeRec(Node* _node)
{	
	Node* temp;
	if(NULL == _node)
	{
		return;
	}
	MirrorTreeRec(_node->m_right);
	MirrorTreeRec(_node->m_left);   	
	temp = _node->m_right;
	_node->m_right = _node->m_left;
	_node->m_left = temp;    
     return;
}



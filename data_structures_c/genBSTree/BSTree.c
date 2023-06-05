#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "BSTree.h"	 /*current header */
#define TREE_IS_EMPTY(tree) (tree -> m_root.m_left == NULL)
#define HAS_LEFT_SON(_node) ((Node*)_node) -> m_left != NULL
#define HAS_RIGHT_SON(_node) ((Node*)_node) -> m_right != NULL
#define IS_RIGHT_SON(_node) ((Node*)_node) -> m_father -> m_right == ((Node*)_node)
#define IS_LEFT_SON(_node) ((Node*)_node) -> m_father -> m_left == ((Node*)_node)
#define IS_LEAF(node)((node) -> m_left == NULL && (node) -> m_right == NULL)
#define HAS_ONE_CHILD(node)(((node) -> m_left == NULL && (node) -> m_right != NULL) ||\
                             ((node) -> m_left != NULL && (node) -> m_right == NULL))
typedef struct Node Node;

struct Node
{
	void* m_data;
	Node* m_left;
	Node* m_right;
	Node* m_father;
};

struct BSTree
{
	Node m_root;
	LessComparator m_func;
};

static void DestroyNode(Node *_node, void (*_destroyer)(void*));
static Node* NodeCreate(void* _data, Node *_father);
static Node* FindData(BSTree* _tree, void* _data);
static Node* RecBSTreeItrBegin(Node* _node);
static void RemoveSingleChild(Node* _node);
static void RemoveLeaf(Node* _node);
static void SwapData(Node* _node1, Node* _node2);
int IsTree(BSTree* _tree);


/*...................API.......................*/

BSTree* BSTreeCreate(LessComparator _less)
{
	BSTree* PTree;
	if(NULL == _less)
	{
		return NULL;
	}
	if((PTree = (BSTree*)malloc(sizeof(BSTree))) == NULL)
	{
		return NULL;
	}
	PTree -> m_root.m_data = NULL;
	PTree -> m_root.m_left = NULL;
	PTree -> m_root.m_right = NULL;
	PTree -> m_root.m_father = &(PTree -> m_root);
	PTree -> m_func = _less;
	return PTree;	
}

/*............................................*/

void  BSTreeDestroy(BSTree** _tree, void (*_destroyer)(void*))
{
	if(NULL == _tree || NULL == *_tree)
	{
		return;
	}
	
	if(NULL != _destroyer) 
	{
        _destroyer(((Node*)*_tree) -> m_data);
	}
	DestroyNode((*_tree) -> m_root.m_left, _destroyer);
	free(*_tree);    
    *_tree = NULL;	
}

/*............................................*/

BSTreeItr BSTreeInsert(BSTree* _tree, void* _item)
{
	Node *newNode = NULL;
	Node *pFather = NULL;
	if(NULL == _tree || NULL == _item)
	{
		return NULL;
	}
	if(NULL == _tree -> m_root.m_left )       /* check if is empty*/
	{
		if(NULL == (newNode = NodeCreate(_item, NULL)))
		{
			return (&(_tree -> m_root));
		}
		_tree -> m_root.m_left = newNode;
		newNode -> m_father = &(_tree -> m_root);
		return newNode;
     }
     if (NULL == (pFather = FindData( _tree, _item)))   /*duplication*/
     {
     	return (&(_tree -> m_root));	
     }
     else
     {
    	if ((newNode = NodeCreate (_item ,pFather)) == NULL) /*alocation error*/
    	{
    		return (&(_tree -> m_root));
    	}
    	if(-1 ==  _tree-> m_func(pFather -> m_data , _item))
    	{
    		pFather -> m_right = newNode;
    	}
    	else if(1 == _tree-> m_func(pFather -> m_data , _item))
    	{
    		pFather -> m_left = newNode;
    	}
    	
    	return newNode; /*!!!!!!!!!!!*/
	 }
}

/*............................................*/

BSTreeItr BSTreeItrBegin(const BSTree* _tree)
{
	if(NULL == _tree)
	{
		return NULL;
	}
	if(NULL == _tree -> m_root.m_left)
	{
		return ((void*)(&(_tree -> m_root)));
	}
	return RecBSTreeItrBegin(_tree -> m_root.m_left);
}

/*............................................*/

BSTreeItr BSTreeItrEnd(const BSTree* _tree)
{
	if(NULL == _tree)
	{
		return NULL;
	}	
	return ((void*)(&(_tree -> m_root)));
}

/*............................................*/

int BSTreeItrEquals(BSTreeItr _a, BSTreeItr _b)
{
	return (_a == _b);
}

/*............................................*/

BSTreeItr BSTreeItrNext(BSTreeItr _it)
{
    Node* runner;
    Node* temp;
    if (_it == NULL)
    {
        return NULL;
    }
    runner = (Node*)_it;
    if (runner -> m_right == NULL)    /*if has not right son*/
    {
        temp = runner;
        runner = runner -> m_father;
        while(runner -> m_left != temp)  /* as long i am right son*/
        {
            temp = runner;       
            runner = runner -> m_father;     /*go to the father*/
            if (runner == temp)
            {
                return _it;
            }
        }
    }
    else {
        runner = runner -> m_right;
        while (runner -> m_left != NULL)
        {
            runner = runner -> m_left;
        }
    }
    return runner;
}

/*............................................*/

BSTreeItr BSTreeItrPrev(BSTreeItr _it)
{
    Node* runner;
    Node* temp;
    if (_it == NULL)
    {
        return NULL;
    }
    runner = (Node*)_it;
    if (runner -> m_left == NULL)    /*if has not left son*/
    {
        temp = runner;
        runner = runner -> m_father;
        while(runner -> m_right != temp)   /*go to the father*/
        {
            temp = runner;
            runner = runner -> m_father;
            if (runner == temp)
            {
                return _it;
            }
        }
    }
    else {
        runner = runner -> m_left;                 /*go to left son*/
        while (runner -> m_right != NULL)         /* go to the right son as long until it NULL*/
        {
            runner = runner -> m_right;
        }
    }
    return runner;
}
/*............................................*/

void* BSTreeItrRemove(BSTreeItr _it)
{
    Node* runner;
    Node* next;
    void* data;
    if (_it == NULL || (((Node*)_it) -> m_father == (Node*)_it))
    {
        return NULL;
    }
    runner = (Node*)_it;
    data = runner -> m_data;
    if (IS_LEAF(runner))
    {
        RemoveLeaf(runner);
    }
    else if (HAS_ONE_CHILD(runner))
    {
        RemoveSingleChild(runner);
    }
    else{
        next = (Node*)BSTreeItrNext(_it);
        SwapData(runner, next);
        if (HAS_ONE_CHILD(next))       
        {
            RemoveSingleChild(next);
        }
        else {
            RemoveLeaf(next);
        }
    }
    return data;
}

/*............................................*/

void* BSTreeItrGet(BSTreeItr _it)
{
    if (_it == NULL)
    {
        return NULL;
    }
    return (((Node*)_it) -> m_data);
}

/*...................HELP FUNC.........................*/

static Node* RecBSTreeItrBegin(Node* _node)
{
	if(NULL == _node -> m_left)
	{
		return _node;
	}
	RecBSTreeItrBegin(_node -> m_left); /*first recur on m_left subtree */
}

/*...................................................*/

static void RemoveLeaf(Node* _node)
{
    if (IS_LEFT_SON(_node))
    {
        _node -> m_father -> m_left = NULL;
    }
    else {
        _node -> m_father -> m_right = NULL;
    }
    free(_node);
    return;
}
/*.................................*/
static void RemoveSingleChild(Node* _node)
{
    if (HAS_LEFT_SON(_node))
    {
        if (IS_LEFT_SON(_node))
        {
            _node -> m_father -> m_left = _node -> m_left;
        }
        else {
            _node -> m_father -> m_right = _node -> m_left;
        }
        _node -> m_left -> m_father = _node -> m_father;
    }
    else {
        if (IS_LEFT_SON(_node))
        {
            _node -> m_father -> m_left = _node -> m_right;
        }
        else {
            _node -> m_father -> m_right = _node -> m_right;
        }
        _node -> m_right -> m_father = _node -> m_father;
    }
    free(_node);
    return;
}
/*...............................................*/
static Node* FindData(BSTree* _tree, void* _data)
{
	Node* iNode = _tree -> m_root.m_left;
	Node* last;
	while(iNode != NULL)
	{
		last = iNode;
		if(1 == (_tree -> m_func(iNode -> m_data, _data)))
		{
			iNode = iNode -> m_left;
		}
		 else if(-1 == (_tree -> m_func(iNode -> m_data, _data)))
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

/*............................................*/

static Node* NodeCreate(void* _data, Node *_father)
{
	Node *pNode = NULL;

	if ((pNode = (Node*)malloc(sizeof(Node))) == NULL)
	{
		return NULL;
 	}
	
	 pNode -> m_data = _data;
 	 pNode -> m_left = NULL;
 	 pNode -> m_right = NULL;
 	 pNode -> m_father = _father; 
 	
 	return pNode;
}

/*............................................*/
static void DestroyNode(Node *_node, void (*_destroyer)(void*))
{
	if(NULL == _node)
	{
		return;
	}
	if(NULL != _destroyer)
	{
		_destroyer(_node -> m_data);
	}
	DestroyNode(_node -> m_left, _destroyer );
	DestroyNode(_node -> m_right, _destroyer);
	free(_node);
}
/*............................................*/
static void SwapData(Node* _node1, Node* _node2)
{
    void* temp;
    temp = _node1 -> m_data;
    _node1 -> m_data = _node2 -> m_data;
    _node2 -> m_data = temp;
}
/*............................................*/
int IsTree(BSTree* _tree)
{
    BSTreeItr begin, end;
    void* data;
    begin = BSTreeItrBegin(_tree);
    data = BSTreeItrGet(begin);
    end = BSTreeItrEnd(_tree);
    begin = BSTreeItrNext(begin);
    while (begin != end)
    {
        if (LessComparatorInt(BSTreeItrGet(begin), data) != 1)
        {
            return FALSE;
        }
        data = BSTreeItrGet(begin);
        begin = BSTreeItrNext(begin);
    }
    return TRUE;
}
/*..................................................*/
void* GetLeft(BSTree* _tree)
{
	return _tree -> m_root.m_left;
}
void* GetRight(BSTree* _tree)
{
	return _tree -> m_root.m_right;
}
void* GetFather(BSTree* _tree)
{
	return _tree -> m_root.m_father;
}
void* GetRoot(BSTree* _tree)
{
	return &(_tree -> m_root);
}
void* GetLeftData(BSTree* _tree)
{
	return _tree -> m_root.m_left -> m_data;
}
void* GetRightData(BSTree* _tree)
{
	return _tree -> m_root.m_right -> m_data;
}
void* TreeGetData(BSTreeItr* _node)
{
	return (((Node*)_node)-> m_data);
}


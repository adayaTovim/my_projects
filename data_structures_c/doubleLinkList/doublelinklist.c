#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "doublelinklist.h"	 /*current header */

#define MAGIC_NUM 230053645


void InsertNode(Node* p , Node* t);
void RemoveNode(Node* _t);
Node* CreateNode(int _data);

struct Node
{
	int m_data;
	Node* m_next;
	Node* m_prev;
};
/*****************************/
struct List
{
	Node m_head;
	Node m_tail;
	int m_magicNum;
};
/*******************************/
List* ListCreate(void)
{
	List *pList;

	if ((pList = (List*)malloc(sizeof(List))) == NULL)
	{
		return NULL;
 	}
 	
 	pList -> m_head.m_next = &pList -> m_tail;
 	pList -> m_head.m_prev = NULL;
 	
 	pList -> m_tail.m_next = NULL;
 	pList -> m_tail.m_prev = &pList -> m_head;
 	
 	pList -> m_magicNum = MAGIC_NUM;                   
 	
 	return pList;		
}
/*******************************************************/
void ListDestroy(List* _list)
{
	Node* pNode;
	if(NULL == _list || _list->m_magicNumber != MAGIC_NUMBER)
	{
		return;
	}
	pNode = (_list->m_head).m_next;
	while (pNode != &_list->m_tail)
	{	
		pNode = pNode->m_next;
		free(pNode->m_prev);
	}
	_list->m_magicNumber = 0;
	free(_list);
}
/*****************************************************/
ADTErr ListPushHead(List* _list, int _data)
{
	Node *pNode;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	pNode = CreateNode(_data);
	if (NULL== pNode)
	{
		return ERR_ALLOCATION_FAILED;
 	}
	pNode -> m_data = _data;
	InsertNode(pNode, _list -> m_head.m_next);
	return ERR_OK;
	
}
/**************************************************/
ADTErr ListPushTail(List* _list, int _data)
{
	Node *pNode = NULL;
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	pNode = CreateNode(_data);
	if (NULL== pNode)
	{
		return ERR_ALLOCATION_FAILED;
 	}
	InsertNode(pNode, _list -> m_tail.m_prev->m_next);	
	return ERR_OK;
}
/****************************************************/
ADTErr ListPopHead(List* _list, int* _data)
{
	if(NULL == _list || NULL == _data )
	{
		return ERR_NOT_INITIALIZED;
	}
	if(ListIsEmpty(_list) == TRUE)
	{
		return ERR_STACK_IS_EMPTY;
	}
	RemoveNode(_list -> m_head.m_next, _data);
	return ERR_OK;
			
}
/******************************************************/
ADTErr ListPopTail(List* _list, int* _data)
{
	if(NULL == _list || NULL == _data )
	{
		return ERR_NOT_INITIALIZED;
	}
	if(ListIsEmpty(_list) == TRUE)
	{
		return ERR_STACK_IS_EMPTY;
	}
	RemoveNode( _list -> m_tail.m_prev->m_next, _data);
	return ERR_OK;	
}
/**************************************************************/
size_t ListCountItems(List* _list)
{
	size_t nItems;
	Node* pNode;
	if (NULL == _list)
	{
		return 0;
	}
	nItems = 0;
	pNode = &_list->m_head;
	while (pNode->m_next != &_list->m_tail)
	{
		nItems++;
		pNode = pNode->m_next;
	}
	return nItems;
}
/*********************************************************/
int ListIsEmpty(List* _list)
{
	if(NULL == _list)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_list -> m_head.m_next == &_list ->  m_tail)
	{
		return TRUE;
	}
	return FALSE;
}
/***************************************************************/
void ListPrint(List* _list)
{
	Node* i = NULL;
	int num = 1;
	if(NULL == _list)
	{
		return;
	}
	for(i = _list -> m_head.m_next; i != &_list ->  m_tail; i = i -> m_next)
	{
		printf("Node num %d data is %d", num, _list -> m_head.m_next -> m_data);
		++num;	
	}	
	
}



/******************************************************************/
/********************help functions********************************/
/*****************************************************************/
Node* CreateNode(int _data)
{
	Node* node = (Node*)malloc(sizeof(Node));
	if (NULL == node)
	{
		return NULL;
	}
	node->m_data = _data;
	return node;
}
/******************************************************************/
void InsertNode(Node* p , Node* t)
{
	if(p == NULL || t == NULL)
	{
		return;
	}
	p-> m_prev = t->m_prev;

	p-> m_next = t ;

	t-> m_prev->m_next = p;

	t->m_prev = p;
}
/******************************************************************/
void RemoveNode(Node* _t, int* _data)
{
	if(_t == NULL)
	{
		return;
	}
	*_data = _t->m_data;
	_t-> m_prev->m_next = _t->m_next;
	_t->m_next->m_prev = _t->m_next;
	free(_t);
}
/*************************************************************/




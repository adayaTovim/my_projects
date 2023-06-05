#include <stdlib.h>  /*malloc*/
#include <stddef.h>  /* size_t */
#include "genList.h" /*API*/
#include "listInternal.h"

 Node* CreateNode(void* _data);
 void InsertNode(Node* p , Node* t);
 static int ListIsEmpty(List* _list);
 void RemoveNode(Node* _t);
/*
struct Node
{
    void* m_data;
    Node* m_next;
    Node* m_prev;
};
struct List
{
    Node m_head;
    Node m_tail;
};
*/

/*........................................*/
/*..................API..................*/
/*......................................*/
List* ListCreate(void)
{
    List *pList;
	if ((pList = (List*)malloc(sizeof(List))) == NULL)
	{
		return NULL;
 	}
 	pList -> m_head.m_next = &pList -> m_tail;
 	pList -> m_head.m_prev = &pList -> m_head; 	

 	pList -> m_tail.m_next = &pList -> m_tail;
 	pList -> m_tail.m_prev = &pList -> m_head;

 	return pList;	    
}
/*........................................*/
void ListDestroy(List** _pList, void (*_elementDestroy)(void* _item))
{
	Node* pNode;
    Node* i;
	if(NULL == _pList || NULL == *_pList)
	{
		return;
	}
    pNode = ((*_pList) -> m_head).m_next;
    while (pNode != &(*_pList)->m_tail)
    {	
        if (NULL != _elementDestroy)
        {
            _elementDestroy (pNode-> m_data);
        }
        pNode = pNode->m_next;
        free(pNode->m_prev);
    }
    free(*_pList);    
    *_pList = NULL;
}
/*........................................*/
ListResult ListPushHead(List* _list, void* _item)
{
	Node *pNode;
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(NULL == _item )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	pNode = CreateNode(_item);
	if (NULL== pNode)
	{
		return LIST_ALLOCATION_ERROR;
 	}
	InsertNode(pNode, _list -> m_head.m_next);
	return LIST_SUCCESS;
}
/*........................................*/
ListResult ListPushTail(List* _list, void* _item)
{
	Node *pNode = NULL;
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(NULL == _item )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	pNode = CreateNode(_item);
	if (NULL== pNode)
	{
		return LIST_ALLOCATION_ERROR;
 	}
	InsertNode(pNode, &(_list -> m_tail));	
	return LIST_SUCCESS;   
}
/*........................................*/
ListResult ListPopHead(List* _list, void** _pItem)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(NULL == _pItem )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(ListIsEmpty(_list) == TRUE)
	{
		return LIST_IS_EMPTY_ERROR;
	}
	*_pItem = _list->m_head.m_next -> m_data;
	RemoveNode(_list -> m_head.m_next);
	return LIST_SUCCESS;    
}
/*........................................*/
ListResult ListPopTail(List* _list, void** _pItem)
{
	if(NULL == _list)
	{
		return LIST_UNINITIALIZED_ERROR;
	}
    if(NULL == _pItem )
	{
		return LIST_NULL_ELEMENT_ERROR;
	}
	if(ListIsEmpty(_list) == TRUE)
	{
		return LIST_IS_EMPTY_ERROR;
	}
	*_pItem = _list->m_tail.m_prev -> m_data;
	RemoveNode(_list -> m_tail.m_prev);
	return LIST_SUCCESS;	
}
/*........................................*/
size_t ListSize(const List* _list)
{
	size_t nItems;
	Node* pNode;
	if (NULL == _list)
	{
		return 0;
	}
	nItems = 0;
	pNode = _list->m_head.m_next;
	while (pNode != &_list->m_tail)
	{
		nItems++;
		pNode = pNode->m_next;
	}
	return nItems;
}
/*........................................*/
/*............HELP FUNCTIONS..............*/
/*........................................*/
Node* CreateNode(void* _data)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	if (NULL == newNode)
	{
		return NULL;
	}
	newNode->m_data = _data;
	return newNode;
}
/*........................................*/
void RemoveNode(Node* _t)
{
	_t-> m_prev->m_next = _t->m_next;
	_t->m_next->m_prev = _t->m_prev;
	free(_t);
}
/*........................................*/
void InsertNode(Node* _p , Node* _t)
{
	_p-> m_prev = _t->m_prev;
	_p-> m_next = _t ;
	_t-> m_prev->m_next = _p;
	_t->m_prev = _p;
}
/*........................................*/
static int ListIsEmpty(List* _list)
{
	if(_list -> m_head.m_next == &_list ->  m_tail)
	{
		return TRUE;
	}
	return FALSE;
}
/*........................................*/
Node* GetHeadNext(List *_list)
{
	return _list -> m_head.m_next;
}
Node* GetTailPrev(List *_list)
{
	return _list -> m_tail.m_prev;
}
Node* GetHeadPrev(List *_list)
{
	return _list -> m_head.m_prev;
}
Node* GetTailNext(List *_list)
{
	return _list -> m_tail.m_next;
}
void* GetTail(List* _list)
{
	return &_list -> m_tail;
}
void* GetHead(List* _list)
{
	return &_list -> m_head;
}


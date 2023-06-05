#include <stdlib.h>  /*malloc*/
#include <stddef.h>  /* size_t */
#include "genList.h" /*API*/
#include "listItr.h" /*ITERATOR*/
#include "listInternal.h"


ListItr ListItrBegin(const List* _list)
{
    if(NULL == _list)
    {
        return NULL;
    }  
    return ((void*)_list -> m_head.m_next);
}
/*.............................*/
ListItr ListItrEnd(const List* _list)
{
    if(NULL == _list)
    {
        return NULL;
    }  
    return ((ListItr) &(_list -> m_tail));   
}
/*.............................*/
int ListItrEquals(const ListItr _a, const ListItr _b)
{
    return (_a == _b);
}
/*.............................*/
ListItr ListItrNext(ListItr _itr)
{
    if(NULL == _itr)
    {
        return NULL;
    }
    return (((Node*)_itr) -> m_next);
}
/*.............................*/
ListItr ListItrPrev(ListItr _itr)
{
    if(NULL == _itr)
    {
        return NULL;
    }
    /*mean we are at the begin itr*/
    if(((Node*)_itr) -> m_prev -> m_prev == ((Node*)_itr) -> m_prev)
    {
        return _itr;
    }
    return ((Node*)_itr) -> m_prev;
}
/*.............................*/
void* ListItrGet(ListItr _itr)
{ 
    if(NULL == _itr || ((Node*)_itr) -> m_next == (Node*)_itr)
    {
        return NULL;
    }
    return ((Node*)_itr) -> m_data;    
}
/*.............................*/
void* ListItrSet(ListItr _itr, void* _element)
{
    void* item;
    if(NULL == _itr || NULL == _element || ((Node*)_itr) -> m_next == (Node*)_itr)
    {
        return NULL;
    }
    item = ((Node*)_itr) -> m_data;
    ((Node*)_itr) -> m_data = _element;
    return item;
}
/*.............................*/
ListItr ListItrInsertBefore(ListItr _itr, void* _element)
{
    Node *pNode = NULL;
    if(NULL == _itr || NULL == _element)
    {
        return NULL;
    }
    pNode = CreateNode(_element);
    if(NULL == pNode)
    {
        return NULL;
    }
    InsertNode(pNode, (Node*)_itr);
    return pNode;
}
/*.............................*/
void* ListItrRemove(ListItr _itr)
{
    Node *pNode = NULL;
    if(NULL == _itr || ((Node*)_itr)->m_next == _itr)
    {
        return NULL;
    }
    pNode = ((Node*)_itr) -> m_data;
    RemoveNode((Node*)_itr);
    return pNode;
}

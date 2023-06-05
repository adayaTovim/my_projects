#ifndef __LISTINTERNAL_H__
#define __LISTINTERNAL_H__

#include "genList.h" /*API*/
#include "listItr.h" /*ITERATOR*/
#include "list_functions.h"

Node* CreateNode(void* _data);
void RemoveNode(Node* _t);
void InsertNode(Node* _p , Node* _t);

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


#endif /* __LISTINTERNAL_H__ */

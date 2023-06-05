#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>       /* size_t */
#include "linklist.h"	 /*current header */

Person* ListInsertHead(Person* _head ,Person* _p)
{
	if (NULL == _p)
	{
		return _head;
	}
	
	_p -> m_next = _head;
	return _p;
}
 /***********************************************/
 Person* ListRemoveHead(Person* _head, Person** _item)
 {
 	Person* newHead = NULL;
 	if (NULL == _head || NULL == _item)
	{
		if(NULL != _item)
		{
			*_item = NULL;
		}
		return _head;
	}
	*_item = _head; 
	
	return _head -> m_next;	
 }
/*****************************************************/
Person* ListInsertByKey(Person* _head, int _key, Person* _p)
{
	Person* current = _head;
	Person* temp = NULL;
	if(NULL == _p)
	{
		return _head;
	} 	
	if(NULL == _head || _key < _head -> m_id )
	{
		_p -> m_next = _head;
		return _p;
	} 
	while(current != NULL && _key >= current -> m_id)
	{	
		
		if(current -> m_id == _key)
		{
			return _head;	
		}
		temp = current;
		current = current -> m_next;
	}
	temp -> m_next = _p;
	_p -> m_next = current;	
	
	return _head;
}
/************************************************************/
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p)
{
	if(_p == NULL)
	{
		return _head;
	}
	if(_head == NULL || _key < _head -> m_id )
	{
		_p -> m_next = _head;
		return _p;
	}
	if(_key == _head -> m_id)
	{
		return _head;
	}
	
	_head -> m_next = ListInsertByKeyRec(_head -> m_next, _key, _p);
	
	return _head;	
}
/**************************************************************/
Person* ListRemoveByKey(Person* _head, int _key, Person* *_p)
{
	Person* temp = NULL;
	Person* current = _head;
	if(_p == NULL)  
	{
		return _head;
	} 	
	if(_head == NULL)  
	{
		return _head;
	} 
	if( _head -> m_id == _key)
	{
		*_p = _head;
		return _head -> m_next;
	}
	while(current == NULL || _key >= current -> m_id)
	{	
		if(current -> m_id == _key)
		{
			*_p = current;
			temp -> m_next = current -> m_next;
			return _head;
		}
		temp = current;
		current = current -> m_next;
	}
	return _head;
}
/*****************************************************/
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p)
{
	if(_p == NULL || _head == NULL || _head -> m_id > _key)
	{
		return _head;
	}
	if(_key == _head -> m_id)
	{
		*_p = _head;
		return _head -> m_next;
	}

	_head -> m_next = ListRemoveByKeyRec(_head -> m_next, _key, _p);
	
	return _head;	
}
/******************************************************/
void PrintList(Person* _head)
{
	int i = 1;
	if(_head == NULL)
	{
		printf("list is empty\n");
		return;
	}
	while(_head != NULL)
	{
		printf("Person: %d name is: %s ID is: %d and age: %d \n",i,_head -> m_name,_head ->m_id, _head -> m_age);
		_head = _head -> m_next;
		++i;
	}
}
/******************************************************/
Person* GetTheLastNodeRec(Person* _head)
{
	if(NULL == _head || NULL ==_head -> m_next)  
	{
		return _head;
	} 
	
	return GetTheLastNodeRec(_head -> m_next);
	
}
/******************************************************/
Person* GetTheOlder(Person* _head)
{
	Person* older;
	if(NULL == _head || NULL ==_head -> m_next)  
	{
		return _head;
	} 	

	older = GetTheOlder( _head -> m_next);
	
	if(older -> m_age < _head -> m_age)
	{
		older = _head ;
	}
	return older;
}

	


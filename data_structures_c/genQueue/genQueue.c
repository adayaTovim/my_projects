#include <stdio.h> /*for the print*/
#include "genQueue.h"
#include <stdlib.h> /*for malloc*/
#define TRUE 1
#define FALSE 0
struct Queue
{
    void**    m_que;        /*The Array of inegers*/
    size_t  m_size;		   /*The size of queue*/
    size_t  m_head;       /* Index of head in m_que */
    size_t  m_tail;       /* Index of tail in m_que */
    size_t  m_nItems;	  /* Index of number of items  */
};

Queue* QueueCreate(size_t _size)
{
	void** pQue = NULL;
	Queue *ptrQueue = NULL;
	if(0 == _size)
	{
		return NULL;
	}
	if(NULL == (ptrQueue = (Queue*)malloc(sizeof(Queue))))
	{
		return NULL;
	} 
	if(NULL == (pQue = (void**)malloc(_size*sizeof(void*))))
	{
		free(ptrQueue);
		return NULL;
	}
	ptrQueue -> m_que = pQue ;
	ptrQueue -> m_size = _size ;
	ptrQueue -> m_tail = 0;
	ptrQueue -> m_head = 0;
	ptrQueue -> m_nItems = 0;
	return ptrQueue;
}

void QueueDestroy(Queue** _queue, DestroyItem _itemDestroy)
{
	size_t size;
	size_t i = 0;
	size_t tail = 0;
	void **runner = NULL;
	if (NULL == _queue || NULL == *_queue)
	{
		return;
	}
	if(NULL != _itemDestroy && 0 != (*_queue) -> m_nItems)
	{
		runner = (*_queue) -> m_que;
		i = (*_queue) -> m_head;
		tail = (*_queue) -> m_tail;
		size = (*_queue) -> m_size;
		
		do 
		{
			_itemDestroy(runner[i]);
			i = (i+1) % size;
		}
		while(i != tail);
	}
	free((*_queue) -> m_que);
	free(*_queue);
	*_queue = NULL;
}

QueueResult QueueInsert(Queue* _queue,void* _item)
{
	
	if ( NULL == _item) 
	{
		return QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if (NULL == _queue) 
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	if (_queue -> m_size == _queue -> m_nItems)
	{
		return QUEUE_OVERFLOW_ERROR;
	}
	_queue -> m_que [_queue -> m_tail] = _item;
	(_queue -> m_tail) = (_queue -> m_tail+1) % (_queue -> m_size);
	(_queue -> m_nItems) ++;
	
	return QUEUE_SUCCESS;
}


QueueResult QueueRemove(Queue* _queue,void** _item)
{
	if(NULL == _item)
	{
		QUEUE_DATA_UNINITIALIZED_ERROR;
	}
	if (NULL == _queue) 
	{
		return QUEUE_UNINITIALIZED_ERROR;
	}
	
	if( 0 == _queue -> m_nItems)
	{
		return QUEUE_DATA_NOT_FOUND_ERROR; 
	}
	*_item = _queue -> m_que [_queue -> m_head];
	(_queue -> m_head) = (_queue -> m_head+1) % (_queue -> m_size) ;
	(_queue -> m_nItems) -- ;
		
	return QUEUE_SUCCESS;
}

size_t QueueIsEmpty(Queue* _queue)
{
	if (NULL == _queue) 
	{
		return TRUE;
	}
	return (_queue -> m_nItems == 0) ? TRUE : FALSE;
}

size_t QueueForEach(Queue* _queue, ActionFunction _action, void* _context)
{
	size_t size, i, counter;
	void* data = NULL;
	if(NULL == _queue || NULL == _action)
	{
		return 0;
	}
	for(i = 0; i < _queue -> m_nItems ; ++i)
	{
		if(0 == _action(_queue -> m_que[i], _context))
		{
			break;
		}
	}
 	return i;
}
/******************************************************/
size_t GetSizeQ(Queue* _queue)
{
	return _queue -> m_size;
}
/*****************************************************/
size_t GetNumOfItemsQ(Queue* _queue)
{
	return _queue -> m_nItems;
}
/*****************************************************/
size_t GetTailQ(Queue* _queue)
{
	return _queue -> m_tail;
}
/*****************************************************/
size_t GetHeadQ(Queue* _queue)
{
	return _queue -> m_head;
}
/*****************************************************/

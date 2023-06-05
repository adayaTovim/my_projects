#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h"  
#include "queue.h"	 /*current header */

#define MAGIC_NUM 230053647


struct Queue
{
int* m_que;   
size_t m_size;  
size_t m_head; /* Index of head in m_que. */
size_t m_tail; /* Index of tail in m_que. */
size_t m_nItems;
int m_magicNum;
};

/******************************************/

struct Queue* QueueCreate (size_t _size)
{
	int *pQueue = NULL;
	Queue *ptrQueue = NULL;

	if ( _size == 0)
	{
		return NULL;
	}
	if ((ptrQueue = (Queue*)malloc(sizeof(Queue))) == NULL)
	{
		return NULL;
 	}
	if ((pQueue = (int*)malloc(_size*sizeof(int))) == NULL)
	{
		free(ptrQueue);
		return NULL;
 	}
 	ptrQueue -> m_que = pQueue;
 	ptrQueue -> m_size = _size;
 	ptrQueue -> m_head = 0;
 	ptrQueue -> m_tail = 0;
 	ptrQueue -> m_nItems = 0;
 	ptrQueue -> m_magicNum = MAGIC_NUM;
 	return ptrQueue;
}

/*********************************************************/

void QueueDestroy(Queue *_queue)
{
	if(NULL == _queue || (_queue -> m_magicNum) != MAGIC_NUM)
	{
		return;
	}
	
	free(_queue -> m_que);
	_queue -> m_magicNum = 0;
	free(_queue);
}

/******************************************************/

ADTErr QueueInsert (Queue *_queue, int _item)
{
	if (_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
		
	if(_queue -> m_size == _queue -> m_nItems)
	{	
		return ERR_OVERFLOW;
	}
	_item = _queue -> m_que [_queue -> m_tail];
	_queue -> m_tail = (_queue -> m_tail + 1) % (_queue -> m_size);
	++(_queue -> m_nItems);
	
	return ERR_OK;
}

/*******************************************************/
ADTErr QueueRemove (Queue *_queue, int *_item)
{
	if(_queue == NULL || _item == NULL) 
	{
		return  ERR_NOT_INITIALIZED;
	}
	if( _queue -> m_nItems == 0)
	{
		return ERR_UNDERFLOW;
	}
	_queue -> m_que [_queue -> m_head] = *_item;
	(_queue -> m_head) = (_queue -> m_head + 1) % (_queue -> m_size);
	--(_queue -> m_nItems);
	
	return ERR_OK;		
}

/*******************************************************/
int QueueIsEmpty(Queue *_queue)
{
	if (_queue == NULL || _queue -> m_nItems == 0)
	{
		return TRUE;
	}	
	return FALSE;
}

/********************************************************/
void QueuePrint(Queue *_queue)
{	
	int i,j;
	if(_queue != NULL)
	{
		if(_queue -> m_nItems == 0)
		{
			printf("Queue is empty\n");
		}
		for(i = _queue -> m_head,j = 0 ; j <= _queue -> m_nItems; i = (i+1)%_queue -> m_size, ++j)
		{
		printf("Items %d = %d\n",i,_queue -> m_que[i]); 
		}
		printf("\n");
		
	}
}
/*******************************************************/
ADTErr PQueueInsert (Queue *_queue, int _item)
{
	if (_queue == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
		
	if(_queue -> m_size == _queue -> m_nItems)
	{	
		return ERR_OVERFLOW;
	}
	_item = _queue -> m_que [_queue -> m_head];
	_queue -> m_head = (_queue -> m_head -1) % (_queue -> m_size);
	++(_queue -> m_nItems);
	
	return ERR_OK;
}
/**************************************************************/

size_t GetSizeQueue(Queue *_queue)
{
	return _queue -> m_size;
}
size_t GetHeadQueue(Queue *_queue)
{
	return _queue -> m_head;
}
size_t GetTailQueue(Queue *_queue)
{
	return _queue -> m_tail;
}
size_t GetNumItemsQueue(Queue *_queue)
{
	return _queue -> m_nItems;
}
int GetMagicNumQueue(Queue *_queue)
{
	return _queue -> m_magicNum;
}
int GetReallMagicNumQueue()
{
	return MAGIC_NUM;
}


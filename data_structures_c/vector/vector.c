
#include <stdio.h>
#include <string.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h"  /*current header */
#define DECREASE_FACTOR 2
#define MAGIC_NUM 203676697

ADTErr CheckRealloc(Vector *_vector);

/***************************************************/

struct Vector
{
	int* m_items;

	size_t m_originalSize; 
	/* original allocated space for items */

	size_t m_size;
	/* actual allocated space for items*/

	size_t m_nItems;
	/* actual number of items */

	size_t m_blockSize;
	/* the chunk size to be allocated when no space*/
	
	int m_magicNum;
};

/*****************************************************/

size_t GetGetOriginalSize(Vector *_vector)
{
	return _vector -> m_originalSize;
}
size_t GetSize(Vector *_vector)
{
	return _vector -> m_size;
}
size_t GetNItem(Vector *_vector)
{
	return _vector -> m_nItems;
}
size_t GetBlockSize(Vector *_vector)
{
	return _vector -> m_blockSize;
}
int GetMagicNum(Vector *_vector)
{
	return _vector -> m_magicNum;
}

/***************************************************/

Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize)
{
	int* parr = NULL;
	Vector* pvector = NULL;

	if (_extensionBlockSize == 0 && _initialSize == 0)
	{
		return NULL;
	}
	if ((parr = (int*)malloc(_initialSize*sizeof(int))) == NULL)
	{
		return NULL;
 	}
	if ((pvector = (Vector*)malloc(sizeof(Vector))) == NULL)
	{
		return NULL;
 	}
 	
 	pvector -> m_items = parr;
 	pvector -> m_originalSize = _initialSize;
 	pvector -> m_size =_initialSize;
 	pvector -> m_nItems = 0;
 	pvector -> m_blockSize = _extensionBlockSize;
 	pvector -> m_magicNum = MAGIC_NUM;
 	
 	return pvector;
}

/*********************************************************/

void VectorDestroy(Vector* _vector)
{
	if(NULL == _vector || _vector -> m_magicNum != MAGIC_NUM)
	{
		return;
	}
	free(_vector -> m_items);
	_vector -> m_magicNum = 0;
	free(_vector);
}

/******************************************************/

ADTErr VectorAdd(Vector *_vector, int _item)
 {	

 	if (_vector == NULL)
    	{
    		return  ERR_NOT_INITIALIZED;
   	}
   	if (CheckRealloc(_vector) != ERR_OK)
	{
		return ERR_OVERFLOW;
	}
	
	else if (CheckRealloc(_vector) == ERR_OK)
	{
		_vector -> m_items [_vector -> m_nItems] = _item;
		(_vector -> m_nItems) ++;
	}
	
	return ERR_OK;
}

/******************************************************************/

ADTErr VectorDelete(Vector *_vector, int* _item)
{
	if(_vector == NULL || _item == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	
	if(_vector -> m_nItems == 0)
	{
		return ERR_UNDERFLOW; 
	}
	*_item = _vector -> m_items [_vector -> m_nItems-1];
	(_vector -> m_nItems) -- ;
	
	if(CheckRealloc(_vector) != ERR_OK)
	{
		return ERR_REALLOCATION_FAILED;
	}
	return ERR_OK;
}

/***********************************************************/

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item)
{
	if(_vector == NULL || _item == NULL) 
	{
		return  ERR_NOT_INITIALIZED;
	}
	if (_index > (_vector -> m_nItems))
	{
		return ERR_WRONG_INDEX;
	}
	
	*_item = _vector -> m_items [_index];
	
	return ERR_OK;	
}

/******************************************************************/

ADTErr VectorSet(Vector *_vector, size_t _index, int _item)
{
	if(_vector == NULL ) 
	{
		return  ERR_NOT_INITIALIZED;
	}
	if(_index > ( _vector -> m_nItems -1))
	{
		return ERR_WRONG_INDEX;
	}
	
	_vector -> m_items [_index] = _item;

return ERR_OK;
}

/***************************************************************/

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems)
{
	if(_vector == NULL || _numOfItems == NULL)
	{
		return  ERR_NOT_INITIALIZED;
	}
	*_numOfItems = _vector -> m_nItems;
	
return ERR_OK;
}

/***************************************************************/

void VectorPrint(Vector *_vector)
{
	int i;
	if(_vector == NULL)
	{
		printf("Vector is NULL\n");
          return;
	}
	for(i = 0 ; i < (_vector -> m_nItems); i++)
	{
		printf("m_nItems[%d] = %d\n" ,i, (_vector -> m_items[i]));
	}	

}

/*************************************************************/

ADTErr CheckRealloc(Vector *_vector)
{
	int *ptemp=NULL;
	if((_vector -> m_size) == (_vector -> m_nItems))
	{
		if(_vector -> m_blockSize == 0)
		{
			return ERR_OVERFLOW;
		}
		ptemp = (int*)realloc(_vector -> m_items, (_vector -> m_blockSize + _vector -> m_size)*sizeof(int));
    
		if( ptemp == NULL)
		{
			return ERR_REALLOCATION_FAILED;
		}
		else
		{
			_vector -> m_items = ptemp; 
			_vector -> m_size += (_vector -> m_blockSize);
		}
	}
	if ( (_vector -> m_size > _vector -> m_originalSize) && ((_vector -> m_blockSize)*DECREASE_FACTOR) <= (_vector -> m_size - _vector -> m_nItems)) 
	{
		ptemp = (int*)realloc(_vector -> m_items, (_vector -> m_blockSize + _vector -> m_size)*sizeof(int));
		if( ptemp == NULL)
		{
			return ERR_REALLOCATION_FAILED;
		}
		else
		{
			_vector -> m_items = ptemp; 
			_vector -> m_size -= (_vector -> m_blockSize);
		}
	}
	return ERR_OK;
}
	


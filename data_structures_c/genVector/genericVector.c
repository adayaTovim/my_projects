#include <stdio.h>
#include <stdlib.h>  /*malloc*/
#include "genericVector.h"  /*API*/
#define DECREASE_FACTOR 2


static VectorResult ReallocAddVecForAppend(Vector *_vector);
static VectorResult ReallocDelateVecForRemove(Vector *_vector);
static size_t GetOriginalSize(Vector *_vector);
static size_t GetSize(Vector *_vector);
static size_t GetnItems(Vector *_vector);
static size_t GetBlockSize(Vector *_vector);


struct Vector
{
	void** m_items;
	size_t m_originalSize; /* original allocated space for items */
	size_t m_size;/* actual allocated space for items*/
	size_t m_nItems;/* actual number of items */
	size_t m_blockSize;/* the chunk size to be allocated when no space*/
};


/**************API*************/
Vector* VectorCreate(size_t _initialCapacity, size_t _blockSize)
{	
	void** pItems=NULL;
	Vector* pVec=NULL;
	if(0 == _initialCapacity && 0 == _blockSize)
	{
		return NULL;
	}
	if(NULL == (pVec = (Vector*)malloc(sizeof(Vector))))
	{
		return NULL;
	}
	if(NULL == (pItems = (void**)malloc(_initialCapacity*sizeof(void*))))
	{
		free(pVec);
		return NULL;
	}
	pVec -> m_items = pItems ;
	pVec -> m_originalSize = _initialCapacity ; /*we do not want to go ender this size so we declare it in the original size and size*/
	pVec -> m_size = _initialCapacity ;
	pVec -> m_nItems = 0;
	pVec -> m_blockSize = _blockSize;
	
	return pVec; 
}
/*******************************/
void VectorDestroy(Vector** _vector, void (*_elementDestroy)(void*_item))
{
    size_t i, size;
    if (NULL == _vector || NULL == (*_vector)) 
    {
        return;
    }
    if (_elementDestroy != NULL)
    {
        size = (*_vector) -> m_size;
        for(i = 0; i < size; ++i)
        {
            _elementDestroy ((*_vector)-> m_items[i]);
        }
    }
    free((*_vector)-> m_items);
    free(*_vector);
    *_vector = NULL;
}
/*******************************/
VectorResult VectorAppend(Vector* _vector, void* _item)
 {	
 	if (NULL == _vector || NULL == _item)
    {
    		return  VECTOR_UNITIALIZED_ERROR;
   	}
   	if (ReallocAddVecForAppend(_vector) != VECTOR_SUCCESS)
	{
	    return VECTOR_ERR_OVERFLOW;
	}
	_vector -> m_items [_vector -> m_nItems] = _item;
	(_vector -> m_nItems) ++;
	return VECTOR_SUCCESS;
}
/*******************************/
VectorResult VectorRemove(Vector* _vector, void** _pValue)
{
	if(NULL ==_vector || NULL ==_pValue)
	{
		return VECTOR_UNITIALIZED_ERROR;
	}
	if(_vector -> m_nItems == 0)
	{
		return VECTOR_ERR_UNDERFLOW; 
	}
	*_pValue = _vector -> m_items [_vector -> m_nItems-1];
	--(_vector -> m_nItems);
	
	ReallocDelateVecForRemove(_vector);
	
	return VECTOR_SUCCESS;
}
/*******************************/
VectorResult VectorGet(const Vector* _vector, size_t _index, void** _pValue)
{
	if(_vector == NULL || _pValue == NULL) 
	{
		return  VECTOR_UNITIALIZED_ERROR;
	}
	if (_index > (_vector -> m_nItems))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	
	*_pValue = _vector -> m_items [_index];
	
	return VECTOR_SUCCESS;	
}
/*******************************/
VectorResult VectorSet(Vector* _vector, size_t _index, void*  _value)
{
	if(_vector == NULL || _value == NULL) 
	{
		return  VECTOR_UNITIALIZED_ERROR;
	}
	if(_index > ( _vector -> m_nItems -1))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}
	_vector -> m_items [_index] = _value;
    return VECTOR_SUCCESS;
}
/*******************************/
size_t VectorSize(const Vector* _vector)
{
	if(_vector == NULL)
	{
		return  0;
	}
    return _vector -> m_nItems;
}
/*******************************/
size_t VectorCapacity(const Vector* _vector)
{
	if(_vector == NULL)
	{
		return  0;
	}	
    return _vector -> m_size;    
}
/*******************************/
size_t VectorForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
    size_t size,i;
    void *item = NULL;
    if(NULL == _vector || NULL ==_action)
	{
		return  0;
	}
    size = _vector -> m_nItems;
    for(i = 0; i < size; ++i)
    {
        if(_action(_vector -> m_items[i], i, _context) == 0)
        {
            break;
        }
    }
    return i; 
}
/*******************************/
/********HELP*FUNCTIONS*********/
/*******************************/
static VectorResult ReallocAddVecForAppend(Vector *_vector)
{
	void **ptemp = NULL;
	if((_vector -> m_size) == (_vector -> m_nItems))
	{
		if(_vector -> m_blockSize == 0)
		{
			return VECTOR_ERR_OVERFLOW;
		}
		ptemp = (void**)realloc(_vector -> m_items, (_vector -> m_blockSize + _vector -> m_size)*sizeof(void*));
    
		if( NULL == *ptemp )
		{
			return VECTOR_REALLOCATION_FAILED_ERROR;
		}
		_vector -> m_items = ptemp; 
		_vector -> m_size += (_vector -> m_blockSize);	
	}
    return VECTOR_SUCCESS;
}
/*******************************/
static VectorResult ReallocDelateVecForRemove(Vector *_vector)
{
    void **ptemp=NULL;
    if ( (_vector -> m_size > _vector -> m_originalSize) && ((_vector -> m_blockSize)*DECREASE_FACTOR) <= (_vector -> m_size - _vector -> m_nItems)) 
	{
		ptemp = (void**)realloc(_vector -> m_items, (_vector -> m_blockSize + _vector -> m_size)*sizeof(void*));
		if(NULL == *ptemp)
		{
			return VECTOR_REALLOCATION_FAILED_ERROR;
		}
		_vector -> m_items = ptemp; 
		_vector -> m_size -= (_vector -> m_blockSize);
		
	}
	return VECTOR_SUCCESS;
}
/*******************************/
static size_t GetOriginalSize(Vector *_vector)
{
	return _vector -> m_originalSize;
}

static size_t GetSize(Vector *_vector)
{
	return _vector -> m_size;
}
static size_t GetnItems(Vector *_vector)
{
	return _vector -> m_nItems;
}

static size_t GetBlockSize(Vector *_vector)
{
	return _vector -> m_blockSize;
}

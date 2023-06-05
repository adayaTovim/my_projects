#include <stdio.h>
#include <stdlib.h>  /* for malloc */
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h" 
#include "stack.h"   /*current header */
#define MAGIC_NUM 30569777

int StackGetMagicNum(Stack *_stack);

 struct Stack 
{
Vector *m_vector;
int m_magicNum;
int m_min;

};

/*********************************************************/
stack* StackMin (Stack* _stack, int _item)
{
	if (_stack == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(_stack -> m_min > _item)
	{
		_stack -> m_min = _item;
	}
	return ERR_OK;	
	
}

/*******************************************************/
Stack* StackCreate (size_t _size, size_t _blockSize)
{	
	Vector* newvector = NULL;
	Stack *pstack = NULL;
	
	if (_size == 0 && _blockSize == 0)
	{
		return NULL;
	}
	
	if ((pstack = (Stack*)malloc(sizeof(Stack))) == NULL)
	{
		return NULL;
 	}
 	
 	if((newvector = VectorCreate(_size,_blockSize)) == NULL)
 	{
 		free(pstack);
 		return NULL;
 	}
 	
	pstack -> m_vector = newvector;
 	pstack -> m_magicNum = MAGIC_NUM;
 	
 	return pstack;		
}
/************************************************************/
void StackDestroy(Stack* _stack)
{
	if(NULL == _stack || _stack -> m_magicNum != MAGIC_NUM)
	{
		return;
	}
	VectorDestroy(_stack -> m_vector);
	_stack -> m_magicNum = 0;	
	free(_stack);

}
/************************************************************/
ADTErr StackPush (Stack* _stack, int _item)
{
	if (_stack == NULL)
	{
		return ERR_NOT_INITIALIZED;
	}
	if(StackIsEmpty == FALSE)
	{
		StackMin (Stack* _stack, int _item);
	}
	else
	{
		_stack -> m_min = _item;	
	}

	return VectorAdd(_stack -> m_vector, _item);
}

/************************************************************/
ADTErr StackPop (Stack* _stack, int* _item)
{
	if(_stack == NULL || _item == NULL) 
	{
		return  ERR_NOT_INITIALIZED;
	}
	return VectorAdd(_stack -> m_vector, *_item);
	

}
/************************************************************/
ADTErr StackTop (Stack* _stack, int* _item)
{
	size_t _numOfItems;
	if(_stack == NULL || _item == NULL) 
	{
		return  ERR_NOT_INITIALIZED;
	}
	VectorItemsNum(_stack -> m_vector, &_numOfItems);
	
	if(_numOfItems == 0) 
	{
		return ERR_STACK_IS_EMPTY;
	}
	
	VectorGet(_stack -> m_vector, _numOfItems - 1 ,_item);
	return ERR_OK;
}
/************************************************************/
int StackIsEmpty(Stack* _stack)
{
	size_t _numOfItems;
	if(_stack == NULL)
	{
		return  TRUE;	
	}
	VectorItemsNum(_stack -> m_vector, &_numOfItems);
	return (_numOfItems == 0) ? TRUE : FALSE;

}
/************************************************************/
void StackPrint (Stack *_stack)
{
	if(_stack == NULL)
	{
		return;	
	}
	VectorPrint(_stack -> m_vector);
}

/************************************************************/
int StackGetMagicNum(Stack *_stack)
{
	return _stack -> m_magicNum;
}

/******************************************************/
int StackGetReallMagicNum(void)
{
return MAGIC_NUM;
}




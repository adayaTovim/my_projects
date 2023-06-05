#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "heap.h"	 /*current header */
#include "vector.h"
#define MAGIC_NUM 203676691 
#define IS_LEAF(_index) ((_index*2)+ 1)
#define LEFT_SON(_index) ((_index*2)+ 1)
#define RIGHT_SON(_index)  ((_index*2)+ 2)


static void Heapify(Heap* _heap, size_t _index);
 /*help function,reset the elements in a heap - father must be biggest/equal to his sons*/
static Swap(Heap* _heap, size_t item1, size_t item2, int index1,int index2);
static void BobbleUpRec(Heap* _heap, size_t _index);
/* help function, compare son with his father in a heap */
static int FindBiggest(Heap* _heap, size_t _index);
int HeapGetMagicNum(Heap* _heap);



struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
	int m_magicNum;
};



Heap* HeapBuild(Vector* _vec) 
{
	Heap* pHeap = NULL;
	size_t numOfItem = 0;
	size_t index_smallestFather;
	int i;
	
	if((pHeap = (Heap*)malloc(sizeof(Heap))) == NULL)
	{
		return NULL;
	}
	VectorItemsNum(_vec, &numOfItem);
	pHeap -> m_vec = _vec;
	pHeap -> m_heapSize = numOfItem;
	pHeap -> m_magicNum = MAGIC_NUM;
	
	index_smallestFather = (pHeap -> m_heapSize -1)/2; /*  the smallest father  = (smallest son - 1)/2  */
	
	for(i = index_smallestFather + 1; i > 0; ++i)
	{
		Heapify(pHeap,index_smallestFather);
	}	
	return pHeap;
}
/*********************************************************************/
void HeapDestroy(Heap* _heap)
{
	if ( NULL == _heap || _heap ->m_magicNum != MAGIC_NUM) 
     {
		return;
     }
  
	_heap ->m_magicNum = 0;
	free(_heap);		
}
/**********************************************************************/
ADTErr HeapInsert(Heap* _heap, int _data) /* O(log n) */
{
	size_t index;
	if ( NULL == _heap) 
     {
		return ERR_NOT_INITIALIZED;
     }
     VectorItemsNum(_heap -> m_vec, &index);
     VectorAdd(_heap -> m_vec, _data);         /*add new element to the end */
     
	BobbleUpRec (_heap, index);               /* to compare the new element with its father*/
 	++(_heap -> m_heapSize);
     return ERR_OK;
}
/*******************************************************************/
ADTErr HeapMax(Heap* _heap, int* _data)
{
	if ( NULL == _heap || NULL == _data) 
     {
		return ERR_NOT_INITIALIZED;
     }	
     VectorGet(_heap -> m_vec, 0 , _data);
     return ERR_OK;
}
/******************************************************************/
ADTErr HeapExtractMax(Heap* _heap, int* _data) /* O(log n) */
{
	int Delete;
	if ( NULL == _heap || NULL == _data) 
     {
		return ERR_NOT_INITIALIZED;
     }	
     VectorGet(_heap -> m_vec, 0 , _data);	
     VectorDelete(_heap -> m_vec, &Delete);
     VectorSet(_heap -> m_vec, 0, Delete);
    	--(_heap -> m_heapSize);
    	Heapify(_heap, 0);
    	
    	return ERR_OK;
}
    	
/*********************************************************************/
size_t HeapItemsNum(Heap* _heap)
{
	size_t nOItems = 0;
	if ( NULL == _heap) 
     {
		return nOItems;
     }
     VectorItemsNum(_heap -> m_vec, &nOItems);  
     return nOItems;
}
/********************************************************************/
void HeapPrint(Heap* _heap)
{
	if ( NULL == _heap) 
     {
		return;
     }
	VectorPrint(_heap -> m_vec);
}

/**********************************************************************/
/*******************************HELP FUNCTION**************************/
/**********************************************************************/

static void Heapify(Heap* _heap, size_t _index)
{

	int leftson, rightson,father;
	
	if(IS_LEAF(_index))
	{
		return;
	}
	
	
	VectorGet(_heap -> m_vec, LEFT_SON(_index), &leftson);
	VectorGet(_heap -> m_vec, _index,& father);

	if(LEFT_SON(_index) + 1 == _heap -> m_heapSize)
	{
		rightson = leftson;  /*??????*/
	}
	else 
	{
		VectorGet(_heap -> m_vec, RIGHT_SON(_index), &rightson);
	}
	if(leftson > father && leftson >= rightson)         /*check if the left son is bigger*/
	{
		Swap(_heap, father, leftson, _index, LEFT_SON(_index));
		Heapify(_heap, LEFT_SON(_index));
	}
	else if(rightson > father && rightson >= leftson)           /*check if the right son is bigger*/
	{
		Swap(_heap, father, rightson, _index, RIGHT_SON(_index));
		Heapify(_heap, RIGHT_SON(_index));
	} 
}
/**********************************************************************/

static Swap(Heap* _heap, size_t item1, size_t item2, int index1,int index2)
{		
	VectorSet(_heap -> m_vec, index2, item1);
	VectorSet(_heap -> m_vec, index1, item2);
}	

/*********************************************************************/

static void BobbleUpRec(Heap* _heap, size_t _index)            
{
	int father = 0;
	int son = 0;	
	int ifather = (_index -1)/2;
	
	if(ifather < 0)
	{
		return;
	}
	VectorGet(_heap -> m_vec, ifather, &father);
	VectorGet(_heap -> m_vec, _index, &son);
	
	if(son > father)
	{
		Swap(_heap,father,son,ifather, _index );
		BobbleUpRec(_heap,ifather);
	}
}	

/*****************************************************************/
int HeapGetMagicNum(Heap* _heap)
{
	return _heap -> m_magicNum;
}
/***************************************************************/

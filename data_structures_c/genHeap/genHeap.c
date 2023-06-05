#include <stdio.h>
#include <stdlib.h>  /*malloc*/
#include "genHeap.h"  /*API*/
#include "genericVector.h"
#define DECREASE_FACTOR 2
#define LEFT_SON(_index) ((_index*2)+ 1)
#define IS_LEAF(_heap,_index) ((LEFT_SON(_index)) >= (_heap -> m_heapSize))
#define RIGHT_SON(_index)  ((_index*2)+ 2)
#define HAS_RIGHT(heap, i) ((2 * (i) + 2) < heap->m_heapSize)
#define TRUE 1
#define FALSE 0


struct Heap
{
	Vector* m_vec;
	size_t m_heapSize;
     LessThanComparator m_cFunc;
};

static void HeapifyRec(Heap *_heap, size_t _index);
static Swap(Heap* _heap, void* item1, void* item2, size_t index1,size_t index2);
static size_t FindNewHead(Heap* _heap, size_t _index);
static void BubbleUpRec(Heap* _heap, size_t _index);  

/*..............................................................*/
/*..............................API.............................*/
/*..............................................................*/
Heap* HeapBuild(Vector* _vector, LessThanComparator _pfLess)
{
    Heap* pHeap = NULL;
	size_t i,index_smallerFather;
	
    if(NULL == _vector || NULL == _pfLess)
    {
        return NULL;
    }
	if((pHeap = (Heap*)malloc(sizeof(Heap))) == NULL)
	{
		return NULL;
	}

    pHeap -> m_heapSize = VectorSize(_vector);
	pHeap -> m_vec = _vector;
	pHeap -> m_cFunc = _pfLess;
	

	if(pHeap -> m_heapSize > 1)
    {
        index_smallerFather = (pHeap -> m_heapSize -1)/2; /*  the smallest father  = (smallest son - 1)/2  */

	    for(i = index_smallerFather; i > 0; --i)
	    {
	    	HeapifyRec(pHeap,index_smallerFather);
	    }	
    	HeapifyRec(pHeap,0);
    }
	return pHeap;
}
/*..............................................................*/
Vector* HeapDestroy(Heap** _heap)
{
    Vector* pVector;
    if ( NULL == _heap || NULL == *_heap) 
    {
		return NULL;
	}
  
    pVector = (*_heap) -> m_vec;
	free(*_heap);	
    return pVector;
}
/*..............................................................*/
HeapResultCode HeapInsert(Heap* _heap, void* _element)
{
    size_t index;
    VectorResult ERR = VECTOR_SUCCESS;
	if ( NULL == _heap || NULL == _element) 
    {
		return HEAP_NOT_INITIALIZED;
    }
    ERR = VectorAppend(_heap -> m_vec, _element);
    if(VECTOR_ERR_OVERFLOW == ERR)
    {
        return HEAP_VECTOR_OVERFLOW;
    }
    if(VECTOR_ALLOCATION_ERROR == ERR)
    {
        return 	HEAP_ALLOCATION_ERROR;
    }

	BubbleUpRec (_heap, _heap -> m_heapSize);     /* to compare the new element with its father*/
 	++(_heap -> m_heapSize);
     return HEAP_SUCCESS;   
}
/*..............................................................*/
const void* HeapPeek(const Heap* _heap)
{
    void* data;
    if ( NULL == _heap || _heap -> m_heapSize == 0) 
     {
		return NULL;
     }	
     VectorGet(_heap -> m_vec, 0 , &data);
     return data;
}
/*..............................................................*/
void* HeapExtract(Heap* _heap)
{
    void* topElement;
    void* lastElement;
	if (NULL == _heap || _heap -> m_heapSize == 0) 
    {
		return NULL;
    }	
    VectorGet(_heap -> m_vec, 0 , &topElement);	
    VectorRemove(_heap -> m_vec, &lastElement);
	--(_heap -> m_heapSize);
	if(_heap -> m_heapSize > 0)
	{
    	VectorSet(_heap -> m_vec, 0, lastElement);
    	HeapifyRec(_heap, 0);   
	}
    return topElement; 	
}
/*..............................................................*/
size_t HeapSize(const Heap* _heap)
{
	if ( NULL == _heap) 
     {
		return 0;
     }
     return _heap -> m_heapSize;   
}
/*..............................................................*/
size_t HeapForEach(const Heap* _heap, ActionFunction _act, void* _context)
{
    size_t i,size;
    void *item=NULL ;
    if(_heap == NULL || _act == NULL)
	{
		return 0;
	}
	size = HeapSize(_heap);
    for(i = 0; i < size -1; ++i)
    {
        VectorGet(_heap -> m_vec, i, &item);
        if(_act(item, _context) == 0)
        {
            break;
        }
    }
    return i; 
}


/*..............................................................*/
/*.....................HELP FUNCTION............................*/
/*..............................................................*/
static void HeapifyRec(Heap *_heap, size_t _index)
{
    void* fatherValue = 0;
	void* sonValue = 0;
	size_t newHead = 0;
	
	if(IS_LEAF(_heap, _index))
	{
		return;
	}
	
	newHead = FindNewHead(_heap, _index);
	if(newHead == _index)
	{
		return;
	}
	VectorGet(_heap -> m_vec, newHead, &sonValue);
    VectorGet(_heap -> m_vec, _index, &fatherValue);
	Swap(_heap, sonValue, fatherValue, newHead, _index);
	HeapifyRec(_heap, newHead);
}
/*..............................................................*/
static Swap(Heap* _heap, void* item1, void* item2, size_t index1,size_t index2)
{		
	VectorSet(_heap -> m_vec, index2, &item1);
	VectorSet(_heap -> m_vec, index1, &item2);
}	
/*..............................................................*/
static size_t FindNewHead(Heap* _heap, size_t _index)
{
    void *leftValue;
	void *rightValue; 
	void *fatherValue; 
	void *newHeadValue;
    size_t newHead = _index;

    VectorGet(_heap->m_vec, _index, &fatherValue);
	VectorGet(_heap->m_vec, LEFT_SON(_index), &leftValue);
	newHeadValue = fatherValue;
    if((_heap -> m_cFunc(fatherValue,leftValue)) == TRUE)
    {
		newHead = LEFT_SON(_index);
    }
	if(HAS_RIGHT(_heap, _index))
	{
        VectorGet(_heap->m_vec, newHead, &newHeadValue);
		VectorGet(_heap->m_vec, RIGHT_SON(_index), &rightValue);

		if((_heap -> m_cFunc(newHeadValue, rightValue)) == TRUE)
		{
			newHead = RIGHT_SON(_index);
		}
	}
	return newHead;	    
}
/*..............................................................*/
static void BubbleUpRec(Heap* _heap, size_t _index)            
{
	void *father, *son;
	size_t iFather;
	
	if(_index == 0)
	{
		return;
	}
	iFather = (_index -1)/2;
	VectorGet(_heap -> m_vec, iFather, &father);
	VectorGet(_heap -> m_vec, _index, &son);
	
	if(_heap -> m_cFunc(father, son))
	{
		Swap(_heap,father,son,iFather, _index );
		BubbleUpRec(_heap,iFather);
	}
}

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "genericVector.h"
#define TRUE 1
#define FALSE 0


static void Test1CreateWorking();
static void Test2CreateBlockSizeZero();
static void Test3CreateInitialCapacityZero();
static void Test4CreateInputZero();
static void Test5CreateMalloc();
static void Test1DestroyVectorVectorNull();
static void Test2DestroyVectorDoubleFree();
static void Test1VectorAppendItemNULL();
static void Test2VectorAppendVectorNULL();
static void Test3VectorAppendWorking();
static void Test4RemoveReallocDecrease();
static void Test1VectorSetValueNULL();
static void Test2VectorSetVectorNULL();
static void Test3VectorSetOutOfBounds();
static void Test4VectorSetWorking();
static void Test1VectorGetValueNULL();
static void Test2VectorGetVectorNULL();
static void Test3VectorGetOutOfBounds();
static void Test4VectorGetWorking();
static void Test1VectorSizeVectorNULL();
static void Test2VectorSizeWorking();
static void Test5RemoveWorking();


static int VectorPrintInt(void* _element, size_t _index, void* _context)
{
	printf("%d\n", *(int*)_element);
	return 1;
}

static int VectorFindInt(void* _element, size_t __index, void* _context)
{
	return *(int*)_element != *(int*)_context;;
}

int main()
{
	Test1CreateWorking();
	Test2CreateBlockSizeZero();
	Test3CreateInitialCapacityZero();
	Test4CreateInputZero();
	Test5CreateMalloc();
	Test1DestroyVectorVectorNull();
	Test2DestroyVectorDoubleFree();
	Test1VectorAppendItemNULL();
	Test2VectorAppendVectorNULL();
	Test3VectorAppendWorking();
	Test4RemoveReallocDecrease();
	Test5RemoveWorking();
	Test1VectorSetValueNULL();
	Test2VectorSetVectorNULL();
	Test3VectorSetOutOfBounds();
	Test4VectorSetWorking();
	Test1VectorGetValueNULL();
	Test2VectorGetVectorNULL();
	Test3VectorGetOutOfBounds();
	Test4VectorGetWorking();
	Test1VectorSizeVectorNULL();
	Test2VectorSizeWorking();
	

	/*ActionFunction funcPtr;
	funPtr = VectorPrintInt;*/
}

/*******************TESTS***********************/
/***********************************************/
static void Test1CreateWorking()
{
	Vector *pVector = VectorCreate(6,2);
	if(pVector != NULL)
	{
		printf("Test1 Create positive num- pass\n");
	}
	else 
	{
		printf("Test1 Create positive num - fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test2CreateBlockSizeZero()
{
	Vector *pVector = VectorCreate(6,0);
	if(pVector != NULL)
	{
		printf("Test2 Create blockSize=0- pass\n");
	}
	else 
	{
		printf("Test2 Create blockSize=0- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test3CreateInitialCapacityZero()
{
	Vector *pVector = VectorCreate(0,3);
	if(pVector != NULL)
	{
		printf("Test3 Create initialCapacity Zero pass\n");
	}
	else 
	{
		printf("Test3 Create initialCapacity Zero- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test4CreateInputZero()
{
	Vector *pVector = VectorCreate(0,0);
	if(pVector == NULL)
	{
		printf("Test4 Create Input Zero- pass\n");
	}
	else 
	{
		printf("Test4 Create Input Zero- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test5CreateMalloc()
{
	Vector *pVector = VectorCreate(-2,2);
	if(pVector == NULL)
	{
		printf("Test5 Create Check Malloc- pass\n");
	}
	else 
	{
		printf("Test5 Create Check Malloc- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test1DestroyVectorVectorNull()
{
	Vector *pVector = NULL;
	VectorDestroy(&pVector,NULL);
	printf("Test1 destroy vector - pass\n");
	
}
/***********************************************/
static void Test2DestroyVectorDoubleFree()
{
	Vector *pVector = VectorCreate(2,2);
	VectorDestroy(&pVector,NULL);
	VectorDestroy(&pVector,NULL);
	printf("Test2 destroy vector DoubleFree- pass\n");
}
/***********************************************/
static void Test1VectorAppendItemNULL()
{
	Vector *pVector = VectorCreate(2,2);
	if(VectorAppend(pVector,NULL)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test1 Vector Append item NULL- pass\n");
	}
	else 
	{
		printf("Test1 Vector Append item NULL- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test2VectorAppendVectorNULL()
{
	void* item;
	if(VectorAppend(NULL,item)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test2 Vector Append vector NULL- pass\n");
	}
	else 
	{
		printf("Test2 Vector Append vector NULL- fail\n");
	}
}
/***********************************************/
static void Test3VectorAppendWorking()
{
	void* item;
	Vector *pVector = VectorCreate(2,2);
	if(VectorAppend(pVector,&item)== VECTOR_SUCCESS)
	{
		printf("Test3 Vector Append Working- pass\n");
	}
	else 
	{
		printf("Test2 Vector Append Working- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test1RemoveUnderFlow()
{
	void* item;
	Vector *pVector = VectorCreate(2,2);
	if(VectorRemove(pVector,&item)== VECTOR_ERR_UNDERFLOW)
	{
		printf("Test1 Vector Remove UnderFlow- pass\n");
	}
	else 
	{
		printf("Test1 Vector Remove UnderFlow- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test2RemoveVectorNULL()
{
	void* item;
	if(VectorRemove(NULL,&item)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test2 Vector Remove Vector NULL- pass\n");
	}
	else 
	{
		printf("Test2 Vector Remove  Vector NULL- fail\n");
	}
}
/***********************************************/
static void Test3RemoveValueNULL()
{
	Vector *pVector = VectorCreate(2,2);
	if(VectorRemove(pVector,NULL)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test3 Vector Remove _pValue NULL- pass\n");
	}
	else 
	{
		printf("Test3 Vector Remove  _pValue NULL- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test4RemoveReallocDecrease()
{
	Vector *pVector = VectorCreate(1,1);
	void *itemGet;
	int item1 = 2;
	int item2 = 4;
	int item3 = 6;
	size_t size1, size2;
	VectorAppend(pVector,&item1);
	VectorAppend(pVector,&item2);
	VectorAppend(pVector,&item3);
	size1 = VectorCapacity(pVector);
	VectorRemove(pVector,&itemGet);
	VectorRemove(pVector,&itemGet);
	size2 = VectorCapacity(pVector);

	if(size2 < size1)
	{
		printf("Test4 Vector Remove realloc decrease- pass\n");
	}
	else 
	{
		printf("Test4 Vector Remove realloc decrease- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test5RemoveWorking()
{
	Vector *pVector = VectorCreate(2,4);
	void *itemGet;
	int item1 = 2;
	int item2 = 4;

	VectorAppend(pVector,&item1);
	VectorAppend(pVector,&item2);
	VectorRemove(pVector,&itemGet);
	VectorRemove(pVector,&itemGet);

	if(VectorSize(pVector) == 0)
	{
		printf("Test4 Vector Remove working- pass\n");
	}
	else 
	{
		printf("Test4 Vector Remove working- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test1VectorSetValueNULL()
{
	Vector *pVector = VectorCreate(2,2);
	size_t index = 1;
	if(VectorSet(pVector, index, NULL)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test1 Vector set value NULL- pass\n");
	}
	else 
	{
		printf("Test1 Vector set value NULL- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test2VectorSetVectorNULL()
{
	size_t index = 1;
	void* value;
	if(VectorSet(NULL, index, value)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test2 Vector set vector NULL- pass\n");
	}
	else 
	{
		printf("Test2 Vector set vector NULL- fail\n");
	}
}
/***********************************************/
static void Test3VectorSetOutOfBounds()
{
	Vector *pVector = VectorCreate(2,2);
	size_t index = 6;
	int item = 2;
	void* value;
	VectorAppend(pVector,&item);
	VectorAppend(pVector,&item);
	if(VectorSet(pVector, index, &value) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("Test3 Vector set INDEX_OUT_OF_BOUNDS_ERROR- pass\n");
	}
	else 
	{
		printf("Test3 Vector set INDEX_OUT_OF_BOUNDS_ERROR- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test4VectorSetWorking()
{
	Vector *pVector = VectorCreate(4,4);
	size_t index = 1;
	void* value;
	if(VectorSet(pVector, index, value)== VECTOR_SUCCESS)
	{
		printf("Test4 Vector set working- pass\n");
	}
	else 
	{
		printf("Test4 Vector set working- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test1VectorGetValueNULL()
{
	Vector *pVector = VectorCreate(2,2);
	size_t index = 1;
	if(VectorGet(pVector, index, NULL)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test1 Vector get value NULL- pass\n");
	}
	else 
	{
		printf("Test1 Vector get value NULL- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test2VectorGetVectorNULL()
{
	size_t index = 1;
	void** value;
	if(VectorGet(NULL, index, value)== VECTOR_UNITIALIZED_ERROR)
	{
		printf("Test2 Vector get vector NULL- pass\n");
	}
	else 
	{
		printf("Test2 Vector get vector NULL- fail\n");
	}
}
/***********************************************/
static void Test3VectorGetOutOfBounds()
{
	Vector *pVector = VectorCreate(2,2);
	size_t index = 6;
	void** value;
	int item = 2;
	VectorAppend(pVector,&item);
	VectorAppend(pVector,&item);
	if(VectorGet(pVector, index, value) == VECTOR_INDEX_OUT_OF_BOUNDS_ERROR)
	{
		printf("Test3 Vector get INDEX_OUT_OF_BOUNDS_ERROR- pass\n");
	}
	else 
	{
		printf("Test3 Vector get INDEX_OUT_OF_BOUNDS_ERROR- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test4VectorGetWorking()
{
	Vector *pVector = VectorCreate(1,1);
	size_t index = 1;
	void* value;
	int item1 = 2;
	int item2 = 4;

	VectorAppend(pVector,&item1);
	VectorAppend(pVector,&item2);

	if(VectorGet(pVector, index, &value)== VECTOR_SUCCESS)
	{
		printf("Test4 Vector get working- pass\n");
	}
	else 
	{
		printf("Test4 Vector get working- fail\n");
	}
	VectorDestroy(&pVector,NULL);
}
/***********************************************/
static void Test1VectorSizeVectorNULL()
{
	if(VectorSize(NULL)== 0)
	{
		printf("Test1 Vector size vector NULL- pass\n");
	}
	else 
	{
		printf("Test1 Vector size vector NULL- fail\n");
	}
}
/***********************************************/
static void Test2VectorSizeWorking()
{
	Vector *pVector = VectorCreate(4,4);
	if(VectorSize(pVector)== VectorSize(pVector))
	{
		printf("Test2 Vector size working- pass\n");
	}
	else 
	{
		printf("Test2 Vector size working- fail\n");
	}
	VectorDestroy(&pVector,NULL);

}
/***********************************************/


/*
size_t VectorSize(const Vector* _vector)
{
	if(_vector == NULL)
	{
		return  0;
	}
    return _vector -> m_nItems;
}
*/
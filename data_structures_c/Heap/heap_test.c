#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "heap.h"	 /*current header */
#include "vector.h"
#define MAGIC_NUM 203676691 


void Test1_HeapBuild_OK(void);
void Test2_HeapDestroy_OK(void);
void Test3_HeapInsert_NULL(void);
void Test4_HeapInsert_OK(void);
void Test5_HeapMax_HeapNULL(void);
void Test6_HeapMax_dataNULL(void);
void Test7_HeapMax_OK(void);
void Test8_HeapExtractMax_heapNULL(void);
void Test9_HeapExtractMax_dataNULL(void);
void Test10_HeapExtractMax_OK(void);
void Test11_HeapItemsNum_heapNULL(void);
void Test12_HeapItemsNum_OK(void);

int main()
{

	int data;
	Vector* pVec = VectorCreate(7,15);
	Heap* pHeap = HeapBuild(pVec);
	
	HeapInsert(pHeap,5); 
	HeapInsert(pHeap,8); 
	HeapInsert(pHeap,9); 
	HeapInsert(pHeap,6); 
	HeapInsert(pHeap,4); 
	
	HeapMax(pHeap, &data);
	printf("the max element- %d\n",data);
	
	HeapPrint(pHeap);
	HeapDestroy(pHeap);
	
	/*tests*/
	Test1_HeapBuild_OK();
	Test2_HeapDestroy_OK();
	Test3_HeapInsert_NULL();
	Test4_HeapInsert_OK();
	Test5_HeapMax_HeapNULL();
	Test6_HeapMax_dataNULL();
	Test7_HeapMax_OK();
	Test8_HeapExtractMax_heapNULL();
	Test9_HeapExtractMax_dataNULL();
	Test10_HeapExtractMax_OK();
	Test11_HeapItemsNum_heapNULL();
	Test12_HeapItemsNum_OK();
	
	VectorDestroy(pVec);
	
}


/**************************************************/
/***********************TESTS**********************/
/**************************************************/

void Test1_HeapBuild_OK(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	if(pHeap != NULL)
	{
		printf("Test1_HeapBuild_OK **PASS**\n");
	}
	else
	{
		printf("Test1_HeapBuild_OK **FAIL**\n");
	}
	HeapDestroy(pHeap);
}

/************************************************/

void Test2_HeapDestroy_OK(void)
{
	int *magicNum;
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,2);
	HeapDestroy(pHeap);
	if(HeapGetMagicNum(pHeap) != MAGIC_NUM)
	{
		printf("Test2_HeapDestroy_OK **PASS**\n");
	}
	else
	{
		printf("Test2_HeapDestroy_OK **FAIL**\n");
	}
}

/*************************************************/

void Test3_HeapInsert_NULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,2);
	HeapDestroy(pHeap);

	if(HeapInsert(NULL, 3) == ERR_NOT_INITIALIZED)
	{
		printf("Test3_HeapInsert_OK **PASS**\n");
	}
	else
	{
		printf("Test3_HeapInsert_OK **FAIL**\n");
	}
}
/***************************************************/

void Test4_HeapInsert_OK(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,2);
	HeapDestroy(pHeap);

	if(HeapInsert(pHeap, 3) == ERR_OK)
	{
		printf("Test3_HeapInsert_OK **PASS**\n");
	}
	else
	{
		printf("Test3_HeapInsert_OK **FAIL**\n");
	}
}

/******************************************************/

void Test5_HeapMax_HeapNULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	int _data = 3;
	HeapInsert(pHeap,2);

	if(HeapMax(NULL, &_data) == ERR_NOT_INITIALIZED)
	{
		printf("Test5_HeapMax_HeapNULL **PASS**\n");
	}
	else
	{
		printf("Test5_HeapMax_HeapNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}

/*******************************************************/

void Test6_HeapMax_dataNULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,2);

	if(HeapMax(pHeap, NULL) == ERR_NOT_INITIALIZED)
	{
		printf("Test6_HeapMax_dataNULL **PASS**\n");
	}
	else
	{
		printf("Test6_HeapMax_dataNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}

/*******************************************************/

void Test7_HeapMax_OK(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	int _data = 3;
	HeapInsert(pHeap,2);

	if(HeapMax(pHeap, &_data) == ERR_OK)
	{
		printf("Test6_HeapMax_dataNULL **PASS**\n");
	}
	else
	{
		printf("Test6_HeapMax_dataNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}

/*******************************************************/

void Test8_HeapExtractMax_heapNULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	int _data;
	HeapInsert(pHeap,3);
	HeapInsert(pHeap,2);


	if(HeapExtractMax(NULL, &_data) == ERR_NOT_INITIALIZED)
	{
		printf("Test8_HeapExtractMax_heapNULL **PASS**\n");
	}
	else
	{
		printf("Test8_HeapExtractMax_heapNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}
/*******************************************************/

void Test9_HeapExtractMax_dataNULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);

	HeapInsert(pHeap,3);
	HeapInsert(pHeap,2);

	if(HeapExtractMax(pHeap, NULL) == ERR_NOT_INITIALIZED)
	{
		printf("Test9_HeapExtractMax_dataNULL **PASS**\n");
	}
	else
	{
		printf("Test9_HeapExtractMax_dataNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}
/*******************************************************/

void Test10_HeapExtractMax_OK(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	int _data;
	HeapInsert(pHeap,3);
	HeapInsert(pHeap,2);

	if(HeapExtractMax(pHeap, &_data) == ERR_OK)
	{
		printf("Test10_HeapExtractMax_OK **PASS**\n");
	}
	else
	{
		printf("Test10_HeapExtractMax_OK **FAIL**\n");
	}
	HeapDestroy(pHeap);
}
/*************************************************/
void Test11_HeapItemsNum_heapNULL(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,3);
	HeapInsert(pHeap,2);


	if(HeapItemsNum(NULL) == 0)
	{
		printf("Test11_HeapItemsNum_heapNULL **PASS**\n");
	}
	else
	{
		printf("Test11_HeapItemsNum_heapNULL **FAIL**\n");
	}
	HeapDestroy(pHeap);
}
/***************************************************/
void Test12_HeapItemsNum_OK(void)
{
	Vector* pVec = VectorCreate(2,3);
	Heap* pHeap = HeapBuild(pVec);
	HeapInsert(pHeap,3);
	HeapInsert(pHeap,2);


	if(HeapItemsNum(pHeap) == 2)
	{
		printf("Test12_HeapItemsNum_OK **PASS**\n");
	}
	else
	{
		printf("Test12_HeapItemsNum_OK **FAIL**\n");
	}
	HeapDestroy(pHeap);
}
/******************************************************/

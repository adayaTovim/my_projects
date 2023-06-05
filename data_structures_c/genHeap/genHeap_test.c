#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "genericVector.h"
#include "genHeap.h"  /*API*/

static int CompareInt(const void *_left, const void *_right);

static int HeapPrintInt(const void* _element, void* _context)
{
	printf("%d\n", *(int*)_element);
	return 1;
}

static int HeapFindInt(const void* _element, void* _context)
{
    return (*(int*)_element != *(int*)_context);
}
static int CompareInt(const void *_left, const void *_right)
{
    return (*(int*)_left < *(int*)_right) ?TRUE:FALSE; 

}

/*............TESTS.............*/
static void Test1HeapBuildVectorNull();
static void Test2HeapBuildPfLessNULL();
static void Test3HeapBuildWorking();
static void Test1HeapDestroyHeapNULL();
static void Test2HeapDestroyPointerIsNull(); 
static void Test3DestroyHeapIfWorkingOK();
static void Test1HeapInsertHeapNULL();
static void Test2HeapInsertElementNULL();
static void Test3HeapInsertSizeIncrease();
static void Test4HeapInsertBubbleUpWorking();
static void Test5HeapInsertWorking();
static void Test1HeapPeekHeapNULL();
static void Test2HeapPeekWorking();
static void Test1HeapExtractHepNull();
static void Test2HeapExtractValueOk();
static void Test1HeapSizeIfHeapNull();
static void Test2HeapSizeIfSizeOK();
static void Test1HeapForEachHeapIsNull();
static void Test2HeapForEachActionIsNull();
static void Test3HeapForEachPrintInt();
static void Test4HeapForEachFindIndex();


int main()
{
    Test1HeapBuildVectorNull();
    Test2HeapBuildPfLessNULL();
    Test3HeapBuildWorking();
    Test1HeapDestroyHeapNULL();
    Test2HeapDestroyPointerIsNull();
    Test3DestroyHeapIfWorkingOK();
    Test1HeapInsertHeapNULL();
    Test2HeapInsertElementNULL();
    Test3HeapInsertSizeIncrease();
    /*Test4HeapInsertBubbleUpWorking();*/
    Test5HeapInsertWorking();
    Test1HeapPeekHeapNULL();
    Test2HeapPeekWorking();
    Test1HeapExtractHepNull();
    Test2HeapExtractValueOk();
    Test1HeapSizeIfHeapNull();
    Test2HeapSizeIfSizeOK();
    Test1HeapForEachHeapIsNull();
    Test2HeapForEachActionIsNull();
    Test3HeapForEachPrintInt();
    Test4HeapForEachFindIndex();

}

static void Test1HeapBuildVectorNull()
{
    Heap* pHeap = HeapBuild(NULL,CompareInt);
	if(pHeap == NULL)
	{
		printf("Test1 HeapBuild Vector Null  **PASS**\n");
	}
	else
	{
		printf("Test1 HeapBuild Vector Null**FAIL**\n");
        HeapDestroy(&pHeap);
    }
}
/*...........................................*/
static void Test2HeapBuildPfLessNULL()
{
	Vector* pVec = VectorCreate(5,5);
    Heap* pHeap = HeapBuild(pVec,NULL);
	if(pHeap == NULL)
	{
		printf("Test2 HeapBuild PfLess NULL  **PASS**\n");
	}
	else
	{
		printf("Test2 HeapBuild PfLess NULL **FAIL**\n");
        HeapDestroy(&pHeap);
    }
    VectorDestroy(&pVec,NULL);
}
/*...........................................*/
static void Test3HeapBuildWorking()
{
	Vector* pVec = VectorCreate(2,3);
    Heap* pHeap = HeapBuild(pVec,CompareInt);
	if(pHeap != NULL)
	{
		printf("Test4 HeapBuild Working  **PASS**\n");
	}
	else
	{
		printf("Test4 HeapBuild Working **FAIL**\n");
    }
    HeapDestroy(&pHeap);
    VectorDestroy(&pVec,NULL);
}
/*...........................................*/
static void Test1HeapDestroyHeapNULL()
{
	if(HeapDestroy(NULL) == NULL )
	{
		printf("Test1 Heap Destroy Heap NULL  **PASS**\n");
	}
	else
	{
		printf("Test1 Heap Destroy Heap NULL **FAIL**\n");
    }
}
/*...........................................*/
static void Test2HeapDestroyPointerIsNull()  
{
	int item1 = 1;
	Heap *ptrHeap;
	Vector *addVector = VectorCreate(5,2);
	if(HeapDestroy(NULL) == NULL)
	{
		printf("Test2 Destroy Heap Pointer Is Null **PASS**\n");
	}
	else
	{
		printf("Test2 Destroy Heap Pointer Is Null**FAIL**\n");
	};
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test3DestroyHeapIfWorkingOK()
{
	int item1 = 1;
	Heap *ptrHeap;
	Vector *addVector = VectorCreate(5,2);
	ptrHeap = HeapBuild(addVector, CompareInt);
	if(HeapDestroy(&ptrHeap) != NULL)
	{
		printf("Test3 Destroy Heap If Working OK **PASS**\n");
	}
	else
	{
		printf("Test3 Destroy Heap If Working OK**FAIL**\n");
	}
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test1HeapInsertHeapNULL()
{
    int element;
	if(HeapInsert(NULL, &element) == HEAP_NOT_INITIALIZED)
	{
		printf("Test1 Heap Insert Heap NULL **PASS**\n");
	}
	else
	{
		printf("Test1 Heap Insert Heap NULL **FAIL**\n");
    }
}
/*...........................................*/
static void Test2HeapInsertElementNULL()
{
    Vector* pVec = VectorCreate(5,3);
    Heap* pHeap = HeapBuild(pVec,CompareInt);
	if(HeapInsert(pHeap, NULL) == HEAP_NOT_INITIALIZED)
	{
		printf("Test2 Heap Insert Element NULL **PASS**\n");
	}
	else
	{
		printf("Test2 Heap Insert Element NULL **FAIL**\n");
    }
    HeapDestroy(&pHeap);
    VectorDestroy(&pVec,NULL);
}
/*...........................................*/
static void Test3HeapInsertSizeIncrease()
{
    Vector* pVec = VectorCreate(1,2);
    Heap* pHeap = HeapBuild(pVec,CompareInt);
    size_t size1,size2;
    int item1 = 3;
    int item2 = 4;
    size1 = HeapSize(pHeap);
    HeapInsert(pHeap,&item1);
    HeapInsert(pHeap,&item2);
    size2 = HeapSize(pHeap);
	if(size1 == 0 && size2 == 2) 
	{
		printf("Test3 Heap Insert Increase **PASS**\n");
	}
	else
	{
		printf("Test2 Heap Insert Increase **FAIL**\n");
    }
    HeapDestroy(&pHeap);
    VectorDestroy(&pVec,NULL);
}
/*...........................................*/
static void Test4HeapInsertBubbleUpWorking()
{
    Vector *pVec = VectorCreate(1, 2); 
    Heap* pHeap = HeapBuild(pVec, CompareInt);
    int item1 = 3;
    int item2 = 4;
    int item3 = 1;
    void* value1;
    void* value2;
    void* value3; 
    HeapInsert (pHeap, &item1);
    HeapInsert (pHeap, &item2);
    HeapInsert (pHeap, &item3);
    value1 = HeapExtract(pHeap); 
    value2 = HeapExtract(pHeap);
    value3 = HeapExtract(pHeap);
    if ((*(int*)value1) == 4 && (*(int*)value2) == 3 && (*(int*)value3) == 1)
	{
		printf("Test4 HeapInsert BubbleUpOk **PASS**\n");
	}
	else
	{	
		printf("Test4 HeapInsert BubbleUpOk **FAIL**\n");
	}
    HeapDestroy(&pHeap);
    VectorDestroy(&pVec, NULL); 
}
/*...........................................*/
static void Test5HeapInsertWorking()  
{
	int item1 = 19;
	int item2 = 11;
	int item3 = 20;
	Heap *ptrHeap;
	Vector *addVector =  VectorCreate(5,2);
	ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	HeapInsert(ptrHeap, &item2);
	if( HeapInsert(ptrHeap,  &item3) == HEAP_SUCCESS)
	{
		printf("Test5 Heap Insert Working **PASS**\n");
	}
	else
	{
		printf("Test5 Heap Insert Working **FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test1HeapPeekHeapNULL()
{
    Heap* pHeap = NULL;
    if(HeapPeek(pHeap) == NULL )
	{
		printf("Test1 Heap Peek Heap NULL  **PASS**\n");
	}
	else
	{
		printf("Test1 Heap Peek Heap NULL **FAIL**\n");
    }
}
/*...........................................*/
static void Test2HeapPeekWorking()
{
    Heap* newHeap = NULL;
    const void* value;
    int item1 = 3;
    size_t size1, size2;
	Vector *newVector = VectorCreate(1, 2);
    newHeap = HeapBuild(newVector, CompareInt);
    HeapInsert (newHeap, &item1);
    value = HeapPeek(newHeap);
    if (*(int*) value == 3)
	{
		printf("Test2 HeapPeek Working  **PASS**\n");
	}
	else
	{
		printf("Test2 HeapPeek Working  **FAIL**\n");
    }
    HeapDestroy(&newHeap);
    VectorDestroy(&newVector, NULL);
}
/*...........................................*/
static void Test1HeapExtractHepNull()
{
	int item1 = 19;
	int item2 = 11;
	int item3 = 20;
	int* item= &item3;
	const void* topItem;
	Heap *ptrHeap;
	Vector *addVector =  VectorCreate(5,2);
	ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	HeapInsert(ptrHeap, &item2);
	HeapInsert(ptrHeap, &item3);
	topItem = HeapPeek(ptrHeap);
	if(HeapExtract(NULL) == NULL )
	{
		printf("Test1 Heap Extract Heap Is Null **PASS**\n");
	}
	else
	{
		printf("Test1 Heap Extract Heap Is Null**FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test2HeapExtractValueOk()
{
    Vector *pVec = VectorCreate(1, 2);
    Heap* pHeap = HeapBuild(pVec, CompareInt);
    void* value;
    int item1 = 3;
    HeapInsert (pHeap, &item1);
    value = HeapExtract(pHeap);
    if ((*(int*)value)==3)
	{
		printf("Test2 HeapExtract ValueOk **PASS**\n");
	}
	else
	{	
		printf("Test2 HeapExtract ValueOk **FAIL**\n");
	}
    HeapDestroy(&pHeap);
    VectorDestroy(&pVec, NULL);
}
/*...........................................*/
static void Test1HeapSizeIfHeapNull()
{
	int item1 = 19;
	void* topItem;
	Heap *ptrHeap;
	Vector *addVector =  VectorCreate(5,2);
	ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	if(HeapSize(NULL) == 0)
	{
		printf("Test1 Heap Size If Heap Null **PASS**\n");
	}
	else
	{
		printf("Test1 Heap Size If Heap Null**FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test2HeapSizeIfSizeOK()
{
	int item1 = 19;
	int item2 = 11;
	int item3 = 20;
	int* item = &item3;
	Vector *addVector =  VectorCreate(5,2);
	Heap* ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	HeapInsert(ptrHeap, &item2);
	HeapInsert(ptrHeap, &item3);
	if(HeapSize(ptrHeap) == 3)
	{
		printf("Test2 Heap Size If Size OK **PASS**\n");
	}
	else
	{
		printf("Test2 Heap Size If Size OK**FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test1HeapForEachHeapIsNull()
{
	int item1=3;
	int item2=2;
	int item3=1;
	int num = 5;
	Vector *addVector = VectorCreate(2,2);
	Heap* ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	HeapInsert(ptrHeap, &item2);
	HeapInsert(ptrHeap, &item3);
	if(HeapForEach(NULL, HeapPrintInt, &num) == 0)
	{
		printf("Test1 Heap For Each Heap Is Null **PASS**\n");
	}
	else
	{
		printf("Test1 Heap For Each Heap Is Null **FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test2HeapForEachActionIsNull()
{
	int item1=3;
	int item2=2;
	int item3=1;
	int num = 5;
	Vector *addVector = VectorCreate(2,2);
	Heap* ptrHeap = HeapBuild(addVector, CompareInt);
	HeapInsert(ptrHeap, &item1);
	HeapInsert(ptrHeap, &item2);
	HeapInsert(ptrHeap, &item3);
	if(HeapForEach(ptrHeap, NULL, &num) == 0)
	{
		printf("Test2 Heap For Each Action Is Null **PASS**\n");
	}
	else
	{
		printf("Test2 Heap For Each Action Is Null **FAIL**\n");
	}
	HeapDestroy(&ptrHeap);
	VectorDestroy(&addVector, NULL);
}
/*...........................................*/
static void Test3HeapForEachPrintInt()
{
    Heap* newHeap = NULL;
    int item1 = 3;
    int item2 = 4;
    int item3 = 1;
    int item4 = 2;
	Vector *newVector = VectorCreate(1, 2);
    VectorAppend (newVector, &item1);
    VectorAppend (newVector, &item2);
    VectorAppend (newVector, &item3);
    VectorAppend (newVector, &item4);
    newHeap = HeapBuild(newVector, CompareInt);
    printf("Test 3 Heap For Each Act Print:\n");
    HeapForEach(newHeap, HeapPrintInt ,NULL);
    HeapDestroy(&newHeap);
    VectorDestroy(&newVector, NULL);
}
/*...........................................*/
static void Test4HeapForEachFindIndex()
{ 
    Heap* newHeap = NULL;
    size_t index;
    int item1 = 3;
    int item2 = 5;
    int item3 = 4;
    int item4 = 8;
    void* value = &item4;
    Vector *newVector = VectorCreate(1,1);
    newHeap = HeapBuild(newVector, CompareInt);
    HeapInsert (newHeap, &item1);
    HeapInsert (newHeap, &item2);
    HeapInsert (newHeap, &item3);
    HeapInsert (newHeap, &item4);
    index = HeapForEach(newHeap, HeapFindInt, value);
    if(3 == index)
    {
        printf("Test4 Heap For Each Find Index  **PASS**\n");
	}
	else
	{
		printf("Test4 Heap For Each Find Index  **FAIL**\n");
	}	
    HeapDestroy(&newHeap);
    VectorDestroy(&newVector, NULL);
}
/*
static int HeapFindInt(const void* _element, const void* _context)
{
	return *(int*)_element != *(int*)_context;;
}

*/

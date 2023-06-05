#include <stdio.h> 
#include <stdlib.h>
#include <stddef.h>
#include "genQueue.h"
#define TRUE 1
#define FALSE 0

static void TestQueueCreatCheckSizeZero(void);
static void TestQueueCreatCheckSizeOK(void);
static void TestQueueCreatCheckNegativSize(void);

static void TestQueueDestroyIfWork(void);
static void TestQueueDestroyDubleFree(void);
static void TestQueueDestroyNULL(void);

static void TestQueueInsertQueueIsNull(void);
static void TestQueueInsertIfWorkOK(void);
static void TestQueueInsertOverFlow(void);
static void TestQueueInsertItemNull(void);
static void TestQueueInsertSize(void);

static void TestQueueRemoveQueueIsNull(void);
static void TestQueueRemoveItemIsNull(void);
static void TestQueueRemoveItemIfWorkOK(void);
static void TestQueueRemoveNumOfItems(void);

static void TestQueueIsEmptyQueueIsNull(void);
static void TestQueueIsEmptyFALSE(void);
static void TestQueueIsEmptyTRUE(void);

static void TestQueueGetTail(void);
static void TestQueueGetHead(void);

static void TestQueueForEachActionNull(void);
static void TestQueueForEachQueueNull(void);
static void TestQueueForEachPrintInt(void);
static void TestQueueForEachFindInt(void);

/************************************************************/



int main(void)
{
	printf("\n");
	TestQueueCreatCheckSizeZero();
	TestQueueCreatCheckSizeOK();
	TestQueueCreatCheckNegativSize();
	
	TestQueueDestroyIfWork();
	TestQueueDestroyDubleFree();
	TestQueueDestroyNULL();
	TestQueueInsertQueueIsNull();
	TestQueueInsertIfWorkOK();
	TestQueueInsertOverFlow();
	TestQueueInsertItemNull();
	TestQueueInsertSize();

	TestQueueRemoveQueueIsNull();
	TestQueueRemoveItemIsNull();
	TestQueueRemoveItemIfWorkOK();
	TestQueueRemoveNumOfItems();

	TestQueueIsEmptyQueueIsNull();
	TestQueueIsEmptyFALSE();
	TestQueueIsEmptyTRUE();
	
	TestQueueGetTail();
	TestQueueGetHead();

	TestQueueForEachActionNull();
	TestQueueForEachQueueNull();
	TestQueueForEachPrintInt();
	TestQueueForEachFindInt();


	return 0;
}

/************************************************************/
static void ItemDestroy(void* _element)
{
	if(NULL == _element)
	{
		return;
	}
	free(_element);
}
/*****************************************************************/
static int	QuePrintInt(void* _element, void* _context)
{
	if(NULL == _element )
	{
		return FALSE;
	}
	printf("%d  ", *(int*)_element);
	return TRUE;
}

static int QueFindInt(void* _element, void* _context)
{
	if(*(int*)_element == *(int*)_context)
	{
		return TRUE;
	}
	return TRUE;
}

/*************************************************************/
static void TestQueueCreatCheckSizeZero(void)
{
	Queue *addQueue = QueueCreate(0);
	if(addQueue == NULL)
	{
		printf("TestQueueCreatCheckSizeZero **PASS**\n");
	}
	else
	{
		printf("TestQueueCreatCheckSizeZero **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}
	
static void TestQueueCreatCheckSizeOK(void)
{
	Queue *addQueue = QueueCreate(5);
	if(addQueue != NULL)
	{
		printf("TestQueueCreatCheckSizeOK **PASS**\n");
	}
	else
	{
		printf("TestQueueCreatCheckSizeOK **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}
	
static void TestQueueCreatCheckNegativSize(void)
{
	Queue *addQueue = QueueCreate(-2);
	if(addQueue == NULL)
	{
		printf("TestQueueCreatCheckNegativSize **PASS**\n");
	}
	else
	{
		printf("TestQueueCreatCheckNegativSize **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}
		
static void TestQueueDestroyIfWork(void)
{
	int item = 4;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item);
	QueueDestroy(&addQueue, NULL);
	if(addQueue == NULL)
	{
		printf("TestQueueDestroyIfWork **PASS**\n");
	}
	else
	{
		printf("TestQueueDestroyIfWork **FAIL**\n");
	}
	printf("\n");
}

static void TestQueueDestroyDubleFree(void)
{
	Queue *addQueue = QueueCreate(5);
	QueueDestroy(&addQueue, NULL);
	QueueDestroy(&addQueue, NULL);
	printf("TestQueueDestroyDubleFree**PASS**\n");
	printf("\n");
}

static void TestQueueDestroyNULL(void)
{
	QueueDestroy(NULL, NULL);
	printf("TestQueueDestroyNULL **PASS**\n");
	printf("\n");
}

static void TestQueueInsertQueueIsNull(void)
{
	int item = 4;
	Queue *addQueue = QueueCreate(5);
	if(QueueInsert(NULL,&item) == QUEUE_UNINITIALIZED_ERROR)
	{
		printf("TestQueueInsertQueueIsNull **PASS**\n");
	}
	else
	{
		printf("TestQueueInsertQueueIsNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueInsertIfWorkOK(void)
{
	int item1 = 4;
	int item2 = 5;
	int item3 = 7;
	int item4 = 1;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(QueueInsert(addQueue,&item4) == QUEUE_SUCCESS)
	{
		printf("TestQueueInsertIfWorkOK **PASS**\n");
	}
	else
	{
		printf("TestQueueInsertIfWorkOK **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueInsertOverFlow(void)
{
	int item1 = 4;
	int item2 = 5;
	int item3 = 7;
	int item4 = 1;
	int item5 = 1;
	int item6 = 9;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	QueueInsert(addQueue,&item4);
	QueueInsert(addQueue,&item5);
	if(QueueInsert(addQueue,&item6) == QUEUE_OVERFLOW_ERROR)
	{
		printf("TestQueueInsertOverFlow **PASS**\n");
	}
	else
	{
		printf("TestQueueInsertOverFlow **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueInsertItemNull(void)
{
	int item1 = 4;
	int item2 = 5;
	int item3 = 7;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(QueueInsert(addQueue,NULL) == QUEUE_DATA_UNINITIALIZED_ERROR)
	{
		printf("TestQueueInsertItemNull **PASS**\n");
	}
	else
	{
		printf("TestQueueInsertItemNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueInsertSize(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	void* item4 = &item3;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(GetSizeQ(addQueue) == 5 && GetNumOfItemsQ(addQueue) == 3)
	{
		printf("TestQueueInsertSize **PASS**\n");
	}
	else
	{
		printf("TestQueueInsertSize **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueRemoveQueueIsNull(void)
{
	int item1 = 4;
	int item2 = 5;
	void* item3 = &item2;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(QueueRemove(NULL,&item3) == QUEUE_UNINITIALIZED_ERROR)
	{
		printf("TestQueueRemoveQueueIsNull **PASS**\n");
	}
	else
	{
		printf("TestQueueRemoveQueueIsNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueRemoveItemIsNull(void)
{
	int item1 = 4;
	int* item2 = NULL;
	void* item3 = NULL;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(QueueRemove(addQueue,&item3) == QUEUE_SUCCESS)
	{
		printf("TestQueueRemoveItemIsNull **PASS**\n");
	}
	else
	{
		printf("TestQueueRemoveItemIsNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueRemoveItemIfWorkOK(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	int result;
	void* item4;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	result = QueueRemove(addQueue,&item4);
	if( result == QUEUE_SUCCESS && item4 == &item1 )
	{
		printf("TestQueueRemoveItemIfWorkOK **PASS**\n");
	}
	else
	{
		printf("TestQueueRemoveItemIfWorkOK **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueRemoveNumOfItems(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	void* item4 = &item3;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	QueueRemove(addQueue,&item4);
	if(GetNumOfItemsQ(addQueue) == 2)
	{
		printf("TestQueueRemoveNumOfItems **PASS**\n");
	}
	else
	{
		printf("TestQueueRemoveNumOfItems **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}


static void TestQueueIsEmptyQueueIsNull(void)
{
	Queue *addQueue = QueueCreate(5);
	if(QueueIsEmpty(NULL) == TRUE)
	{
		printf("TestQueueIsEmptyQueueIsNull **PASS**\n");
	}
	else
	{
		printf("TestQueueIsEmptyQueueIsNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueIsEmptyFALSE(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);	
	if(QueueIsEmpty(addQueue) == FALSE)
	{
		printf("TestQueueIsEmptyFALSE **PASS**\n");
	}
	else
	{
		printf("TestQueueIsEmptyFALSE **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueIsEmptyTRUE(void)
{
	Queue *addQueue = QueueCreate(5);	
	if(QueueIsEmpty(addQueue) == TRUE)
	{
		printf("TestQueueIsEmptyTRUE **PASS**\n");
	}
	else
	{
		printf("TestQueueIsEmptyTRUE **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}
static void TestQueueGetTail(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	if(GetTailQ(addQueue) == 3)
	{
		printf("TestQueueGetTail **PASS**\n");
	}
	else
	{
		printf("TestQueueGetTail **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueGetHead(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	int item4 = 7;
	int item5 = 9;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	QueueInsert(addQueue,&item4);
	QueueInsert(addQueue,&item5);	
	if(GetHeadQ(addQueue) == 0)
	{
		printf("TestQueueGetHead **PASS**\n");
	}
	else
	{
		printf("TestQueueGetHead **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueForEachActionNull(void)
{
	int item1 = 4;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	if(QueueForEach(addQueue, NULL, &item1) == 0)
	{
		printf("TestQueueForEachActionNull **PASS**\n");
	}
	else
	{
		printf("TestQueueForEachActionNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueForEachQueueNull(void)
{
	int item1 = 4;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	if(QueueForEach(NULL, QuePrintInt, &item1) == 0)
	{
		printf("TestQueueForEachQueueNull **PASS**\n");
	}
	else
	{
		printf("TestQueueForEachQueueNull **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueForEachPrintInt(void)
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	int item4 = 7;
	int item5 = 9;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	QueueInsert(addQueue,&item4);
	QueueInsert(addQueue,&item5);
	if(QueueForEach(addQueue, QuePrintInt, NULL) == 5)
	{
		printf("\n");
		printf("TestQueueForEachPrintInt **PASS**\n");
	}
	else
	{
		printf("\n");
		printf("TestQueueForEachPrintInt **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}

static void TestQueueForEachFindInt(void)/***/
{
	int item1 = 4;
	int item2 = 1;
	int item3 = 3;
	int item4 = 7;
	int item5 = 9;
	size_t counter;
	Queue *addQueue = QueueCreate(5);
	QueueInsert(addQueue,&item1);
	QueueInsert(addQueue,&item2);
	QueueInsert(addQueue,&item3);
	QueueInsert(addQueue,&item4);
	QueueInsert(addQueue,&item5);
	counter = QueueForEach(addQueue, QueFindInt, &item5);
	printf("%ld", counter);
	if(QueueForEach(addQueue, QueFindInt, &item5) == 5)
	{
		printf("\n");
		printf("TestQueueForEachFindInt **PASS**\n");
	}
	else
	{
		printf("\n");
		printf("TestQueueForEachFindInt **FAIL**\n");
	}

	QueueDestroy(&addQueue, NULL);
	printf("\n");
}



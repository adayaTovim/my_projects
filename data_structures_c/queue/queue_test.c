#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h" 
#include "queue.h"    /*current header */
#define DECREASE_FACTOR 2
#define MAGIC_NUM 230053647

size_t GetSizeQueue(Queue *_queue);
size_t GetHeadQueue(Queue *_queue);
size_t GetTailQueue(Queue *_queue);
size_t GetNumItemsQueue(Queue *_queue);
int GetMagicNumQueue(Queue *_queue);
int GetReallMagicNumQueue();

void Test1CreatePositive(void);
void Test2CreateSizeZero(void);
void Test3CreateNegative(void);
void Test1DestroyOK(void);
void Test2DestroyDoubleFree(void);
void Test3DestroyMagicNum(void);
void Test1InsertNullQueue(void);
void Test2InsertOverFlow(void);
void Test1RemoveNullVector(void);
void Test2RemoveNullItem(void);
void Test3RemoveNumOfItem(void);
void Test4RemoveItemOk(void);
void Test1QueuerIsEmptyNULL(void);
void Test2QueuerIsEmptyReturnFALSE(void);

int main ()
{	
	int i;
	Queue *pQueue;
	pQueue = QueueCreate(10);
	for(i = 1; i < 5; ++i)
	{
		QueueInsert (pQueue, i);
	}
	QueuePrint(pQueue);
	QueueInsert(pQueue,8);
		QueuePrint(pQueue);
	PQueueInsert(pQueue, 7);
	QueuePrint(pQueue);
	QueueDestroy(pQueue);
	
	
	   /******test*******/
	printf("test Queue: /n");
	Test1CreatePositive();
	Test2CreateSizeZero();
	Test3CreateNegative();
	Test1DestroyOK();
	Test2DestroyDoubleFree();
	Test3DestroyMagicNum();
	Test1InsertNullQueue();
	Test2InsertOverFlow();
	Test1RemoveNullVector();
	Test2RemoveNullItem();
	Test3RemoveNumOfItem();
	Test4RemoveItemOk();
	Test1QueuerIsEmptyNULL();
	Test2QueuerIsEmptyReturnFALSE();
	
return 0;
}

void Test1CreatePositive(void)
{
	Queue *pQueue = QueueCreate(2);
	if(pQueue != NULL)
	{
		printf("Test1 Create positive num - pass\n");
		QueueDestroy(pQueue);
	}
	else 
	{
		printf("Test1 Create positive num  - fail\n");
	}
}
/*************************************************/
void Test2CreateSizeZero(void)
{
	Queue *pQueue ;
	pQueue = QueueCreate(0); 
	if(pQueue == NULL)
	{
		printf("Test2 create size zero - pass\n");
	}
	else 
	{
		printf("Test2 create size zero  - fail\n");
		QueueDestroy(pQueue);
	}

}
/**************************************************/
void Test3CreateNegative(void)
{
	Queue *pQueue ;
	pQueue = QueueCreate(-2); 
	if(pQueue == NULL)
	{
		printf("Test1 Create negative num - pass\n");
	}
	else 
	{
		printf("Test1 Create negative num  - fail\n");
		QueueDestroy(pQueue);
	}
}
/***********************************************/
void Test1DestroyOK(void)
{
	int *m_magicNum;
	Queue *pQueue ;
	pQueue = QueueCreate(2); 
	QueueDestroy(pQueue);
	GetMagicNumQueue(pQueue);
	if(m_magicNum == 0)
	{
		printf("Test1 destroy OK- pass\n");	
	}
	else
	{
		printf("Test1 destroy OK- fail\n");	
	}

}
/*****************************************************/
void Test2DestroyDoubleFree(void)
{
	int *m_magicNum;
	Queue *pQueue ;
	pQueue = QueueCreate(5);                       
	QueueDestroy(pQueue);
	QueueDestroy(pQueue);
	GetMagicNumQueue(pQueue);
	printf("Test2 destroy double free- pass\n");	
}
/*******************************************************/
void Test3DestroyMagicNum(void)
{
	int *m_magicNum;
	Queue *pQueue ;                                  
	pQueue = QueueCreate(4);                       
	QueueDestroy(pQueue);
	if(GetMagicNumQueue(pQueue) != MAGIC_NUM ) 
	{
		printf("Test3 destroy magic num - pass\n");
	}
	else 
	{
		printf("Test3 destroy magic num  - fail\n");
	}

}
/******************************************************/
void Test1InsertNullQueue(void)
{
	int _item = 3;
	Queue *pQueue = NULL;
	
	if(QueueInsert(pQueue,3) == ERR_NOT_INITIALIZED)
	{
		printf("Test1 insert NULL ERR_NOT_INITIALIZED - pass\n");	
	}
	else
	{
		printf("Test1 insert NULL ERR_NOT_INITIALIZED - fail\n");	
	}
	QueueDestroy(pQueue);
}
/********************************************************/
void Test2InsertOverFlow(void)
{
	int _item = 3;
	Queue *pQueue ;                                  
	pQueue = QueueCreate(2); 
	QueueInsert(pQueue,_item);
	QueueInsert(pQueue,_item);
	
	if(QueueInsert(pQueue,_item) == ERR_OVERFLOW)
	{
		printf("Test2 insert ERR_OVERFLOW - pass\n");	
	}
	else
	{
		printf("Test2 insert ERR_OVERFLOW - fail\n");	
	}
	QueueDestroy(pQueue);
}
/*******************************************************/
void Test1RemoveNullVector(void)
{
	int _item = 3;
	Queue *pQueue = NULL;

	if(QueueRemove(pQueue,&_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test1 remove vector NULL - pass\n");	
	}
	else
	{
			printf("Test1 remove vector NULL - fail\n");	
	}
	QueueDestroy(pQueue);
}
/******************************************************/
void Test2RemoveNullItem(void)
{
	Queue *pQueue;
	pQueue = QueueCreate(2); 

	if(QueueRemove(pQueue,NULL) == ERR_NOT_INITIALIZED)
	{
			printf("Test1 remove item NULL - pass\n");	
	}
	else
	{
			printf("Test1 remove item NULL - fail\n");	
	}
	QueueDestroy(pQueue);
}
/**********************************************************/
void Test3RemoveNumOfItem(void)
{
	int item = 2;
	Queue *pQueue;
	pQueue = QueueCreate(1); 

	if(QueueRemove(pQueue,&item) == ERR_UNDERFLOW)
	{
		printf("Test3 remove under flow - pass\n");	
	}
	else
	{
		printf("Test3 remove under flow  - fail\n");	
	}
	QueueDestroy(pQueue);
}
/************************************************************/
void Test4RemoveItemOk(void)
{
	int item = 2;
	Queue *pQueue;
	pQueue = QueueCreate(1);
	QueueInsert(pQueue, item);
	QueueRemove(pQueue, &item);
	

	if(GetNumItemsQueue(pQueue) == 0)
	{
		printf("Test4 remove OK -pass\n");
	}
	else
	{
		printf("Test4 remove OK -fail\n");
	}
	QueueDestroy(pQueue);
}
/*************************************************************/
void Test1QueuerIsEmptyNULL(void)
{
	Queue *pQueue = NULL;
	if(QueueIsEmpty(NULL) == TRUE)
	{
		printf("Test1 Queuer is empty NULL -pass\n");
	}
	else
	{
		printf("Test1 Queuer is empty NULL -fail\n");
	}
}
/**********************************************************/
void Test2QueuerIsEmptyReturnFALSE(void)
{
	int item = 3;
	Queue *pQueue = QueueCreate(1);
	QueueInsert(pQueue, item);
	if(QueueIsEmpty(pQueue) == FALSE)
	{
		printf("Test1 Queuer is empty return false -pass\n");
	}
	else
	{
		printf("Test1 Queuer is empty return false -pass\n");
	}	
}

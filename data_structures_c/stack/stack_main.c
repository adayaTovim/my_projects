#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h" 
#include "stack.h"   /*current header */
#define DECREASE_FACTOR 2
#define MAGIC_NUM 30569777



int StackGetMagicNum(Stack *_stack);
int StackGetReallMagicNum(void); 

void Test1CreatePositive(void);
void Test2CreateBlockSizeZero(void);
void Test3CreateSizeZero(void);
void Test4Create2Zero(void);
void Test5CreateMalloc(void);
void Test1DestroyStack(void);
void Test2DestroyDoubleStack(void);
void Test1PushNullStack(void);
void Test1PopNullVector(void);
void Test2tPopNullItem(void);
void Test1StackIsEmptyNULL(void);

int main (void)
{
	
	Test1CreatePositive();
	Test2CreateBlockSizeZero();
	Test3CreateSizeZero();
	Test4Create2Zero();
	Test5CreateMalloc();
	Test1DestroyStack();
	Test2DestroyDoubleStack();
	Test1PushNullStack();
	Test1PopNullVector();
	Test2tPopNullItem();
	Test1StackIsEmptyNULL();
	
	return 0;	 
}




	/*****tests*********/	
	
void Test1CreatePositive(void)
{
	Stack *_stack = StackCreate(2,2);
	if(_stack != NULL)
	{
		printf("Test1 Create positive num - pass\n");
	}
	else 
	{
		printf("Test1 Create positive num  - fail\n");
	}
	StackDestroy(_stack);
}
/****************************************/
void Test2CreateBlockSizeZero(void)
{
	Stack *_stack;
	_stack = StackCreate(2,0);
	if(_stack != NULL)
	{
		printf("Test2 create block size zero - pass\n");
	}
	else 
	{
		printf("Test2 create block size zero  - fail\n");
	}
	StackDestroy(_stack);
}
/****************************************************/
void Test3CreateSizeZero(void)
{
	Stack *_stack = StackCreate(0,4);
	if(_stack != NULL)
	{
		printf("Test3 create size zero - pass\n");
	}
	else 
	{
		printf("Test3 create size zero  - fail\n");
	}
	StackDestroy(_stack);
}
/*****************************************************************/
void Test4Create2Zero(void)
{
	Stack *_stack = StackCreate(0,0);
	if(_stack == NULL)
	{
		printf("Test4 create size & block size zero - pass\n");
	}
	else 
	{
		printf("Test4 create size & block size zero   - fail\n");
	}
	StackDestroy(_stack);
}

/********************************************************************/
void Test5CreateMalloc(void)
{
	Stack *_stack = StackCreate(-2,2);
	if(_stack == NULL)
	{
		printf("Test5 create malloc check - pass\n");
	}
	else 
	{
		printf("Test5 create malloc check  - fail\n");
	}
	StackDestroy(_stack);
}
/*****************************************************************/
void Test1DestroyStack(void)
{
	int m_magicNum;
	Stack *_stack = StackCreate(2,2);
	StackDestroy(_stack); 
	m_magicNum = GetMagicNum(_stack);
	
	if(m_magicNum != StackGetReallMagicNum() ) 
	{
		printf("Test1 destroy vectory - pass\n");
	}
	else 
	{
		printf("Test1 destroy vectory - fail\n");
	}

}
/*****************************************************************/
void Test2DestroyDoubleStack(void)
{
	int m_magicNum;
	Stack *_stack = StackCreate(2,2);
	StackDestroy(_stack);
	StackDestroy(_stack);
	StackGetMagicNum(_stack);
	printf("Test2 destroy double- pass\n");	
}
/*****************************************************************/
void Test1PushNullStack(void)
{
	int _item = 3;
	Stack *_stack = NULL;
	if(StackPush(_stack,_item) == ERR_NOT_INITIALIZED)
	{
		printf("Test1 add NULL ERR_NOT_INITIALIZED - pass\n");	
	}
	else
	{
		printf("Test1 add NULL ERR_NOT_INITIALIZED - fail\n");	
	}
	StackDestroy(_stack);
}
/*****************************************************************/

void Test1PopNullVector(void)
{
	int _item = 3;
	Stack *_stack = NULL;

	if(StackPop(_stack,&_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test2 delete vector NULL - pass\n");	
	}
	else
	{
			printf("Test2 delete vector NULL - fail\n");	
	}
	StackDestroy(_stack);
}
/****************************************************************/
void Test2tPopNullItem(void)
{
	int *_item = NULL;
	Stack *_stack = StackCreate(2,2);

	if(StackPop(_stack,_item) == ERR_NOT_INITIALIZED)
	{
		printf("Test3 delete item NULL - pass\n");	
	}
	else
	{
		printf("Test3 delete item NULL- fail\n");	
	}
	StackDestroy(_stack);
}
/************************************************************/
void Test1StackIsEmptyNULL(void)
{
	Stack *_stack = NULL;
	if(StackIsEmpty(NULL) == TRUE)
	{
		printf("Test1 stack is empty NULL -pass\n");
	}
	else
	{
		printf("Test1 stack is empty NULL -fail\n");
	}
}
/******************************************************
void Test2QueuerIsEmptyFALSE(void)
{
	Stack *_stack = StackCreate(2,2);
		if(StackIsEmpty(_stack) == TRUE)
		{
			printf("Test1 stack is empty NULL -pass\n");
		}
		else
		{
			printf("Test1 stack is empty NULL -fail\n");
		}	
}
****/


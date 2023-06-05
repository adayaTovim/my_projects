#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h> /*make sure the num are positiv */
#include "ADTDef.h"
#include "vector.h"
#define pass -1
#define fail -2
#define MAGIC_NUM 203676697
#define DECRIS_FACTOR 2;

size_t GetGetOriginalSize(Vector *_vector);
size_t GetSize(Vector *_vector);
size_t GetNItem(Vector *_vector);
size_t GetBlockSize(Vector *_vector);
int GetMagicNum(Vector *_vector);


void Test1CreatePositive(void);
void Test2CreateBlockSizeZero(void);
void Test3CreateSizeZero(void);
void Test4Create2Zero(void);
void Test5CreateMalloc(void);

void Test1DestroyVector(void);
void Test2DestroyDoubleFree(void);

void Test1AddNullVector(void);
void Test2AddOverFlow(void);
void Test3AddVectorInsertItem(void);

void Test1DeleteItem(void);
void Test2DeleteNullVector(void);
void Test3tDeleteNullItem(void);
void Test4DeleteNumOfElemantZero(void);
void Test5DeleteCheckRealloc(void);

void Test1GetNullVector(void);
void Test2GetNullItem(void);
void Test3GetIndexBigThenItems(void);
void Test4GetOk(void);

void Test1SetOk(void);
void Test2SetNullVector(void);
void Test3SetIndexBigThenItems(void);
void Test4SetSetAndGetSame(void);

void Test1ItemsNumVectorNull(void);
void Test2VectorItemsNumItemNull(void);
void Test3VectorItemsNumIncreas(void);
 
int main ()
{
	int i,temp;
	size_t size;		
	Vector *vec_ = VectorCreate(5,15);
	
	for(i = 0; i < 10; ++i)
	{
		VectorAdd(vec_, i);
	}
	
	VectorPrint(vec_);
	
	VectorSet(vec_, 3 ,1234);
	VectorGet(vec_, 3, &temp);
	
	if( temp != 1234)
	{
		printf("yeshhhh");
	}
	
	i=45;
	while (ERR_OK == VectorItemsNum(vec_, &size) && size  > 0)
	{
		int data;
		VectorDelete(vec_, &data);
		printf("%d, ", data);
	}
	
	printf("\n");
		
	
	VectorDestroy(vec_);
	
		/*****tests*********/
	Test1CreatePositive();
	Test2CreateBlockSizeZero();
	Test3tDeleteNullItem();
	Test4Create2Zero();
	Test5CreateMalloc();
	Test1DestroyVector();
	Test2DestroyDoubleFree();
	Test1AddNullVector();
	Test2AddOverFlow();
	Test3AddVectorInsertItem();
	Test1DeleteItem();
	Test2DeleteNullVector();
	Test3tDeleteNullItem();
	Test4DeleteNumOfElemantZero();
	Test5DeleteCheckRealloc();
	Test1GetNullVector();
	Test2GetNullItem();
	Test3GetIndexBigThenItems();
	Test4GetOk();
	Test1SetOk();
	Test2SetNullVector();
	Test3SetIndexBigThenItems();
	Test4SetSetAndGetSame();
	Test1ItemsNumVectorNull();
	Test2VectorItemsNumItemNull();
	Test3VectorItemsNumIncreas();
	


	return ERR_OK;
}

/*********************************************************/
void Test1CreatePositive(void)
{
	Vector *_vector = VectorCreate(6,2);
	if(_vector != NULL)
	{
		printf("Test1 Create positive num - pass\n");
	}
	else 
	{
		printf("Test1 Create positive num  - fail\n");
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test2CreateBlockSizeZero(void)
{
	Vector *_vector = VectorCreate(6,0);
	if(_vector != NULL)
	{
		printf("Test2 create block size zero - pass\n");
	}
	else 
	{
		printf("Test2 create block size zero  - fail\n");
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test3CreateSizeZero(void)
{
	Vector *_vector = VectorCreate(0,4);
	if(_vector != NULL)
	{
		printf("Test3 create size zero - pass\n");
	}
	else 
	{
		printf("Test3 create size zero  - fail\n");
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test4Create2Zero(void)
{
	Vector *_vector = VectorCreate(0,0);
	if(_vector == NULL)
	{
		printf("Test4 create size & block size zero - pass\n");
	}
	else 
	{
		printf("Test4 create size & block size zero   - fail\n");
	}
	VectorDestroy(_vector);
}
/********************************************************************/
void Test5CreateMalloc(void)
{
	Vector *_vector = VectorCreate(-2,2);
	if(_vector == NULL)
	{
		printf("Test5 create malloc check - pass\n\n");
	}
	else 
	{
		printf("Test5 create malloc check  - fail\n\n");
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test1DestroyVector(void)
{
	Vector *_vector = VectorCreate(2,2);
	VectorDestroy(_vector); 
	if(GetMagicNum(_vector) != MAGIC_NUM ) 
	{
		printf("Test1 destroy vectory - pass\n");
	}
	else 
	{
		printf("Test1 destroy vectory - fail\n");
	}

}
/*****************************************************************/
void Test2DestroyDoubleFree(void)
{
	Vector *_vector = VectorCreate(2,2);
	VectorDestroy(_vector);
	VectorDestroy(_vector);
	printf("Test2 destroy double- pass\n\n");	
}
/****************************************************************/
void Test1AddNullVector(void)
{
	int _item = 3;
	Vector *_vector = NULL;
	if(VectorAdd(_vector,_item) == ERR_NOT_INITIALIZED)
	{
		printf("Test1 add NULL ERR_NOT_INITIALIZED - pass\n");	
	}
	else
	{
		printf("Test1 add NULL ERR_NOT_INITIALIZED - fail\n");	
	}
	VectorDestroy(_vector);	
}
/********************************************************/
void Test2AddOverFlow(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,0);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	
	if(VectorAdd(_vector,_item) == ERR_OVERFLOW)
	{
		printf("Test2 add ERR_OVERFLOW - pass\n");	
	}
	else
	{
		printf("Test2 add ERR_OVERFLOW - fail\n");	
	}
	VectorDestroy(_vector);	
}
/*************************************************/
void Test3AddVectorInsertItem(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector, _item);
	VectorAdd(_vector, _item);
	VectorAdd(_vector, _item);
	if(GetNItem(_vector) == 3)
	{
		printf("Test3 add insert item - pass\n\n");	
	}
	else
	{
		printf("Test3 add insert item - fail\n\n");	
	}
	VectorDestroy(_vector);	
}
/*****************************************************************/
void Test1DeleteItem(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector, _item);
	VectorDelete(_vector,&_item);
	if(GetNItem(_vector) == 0)
	{
			printf("Test1 delete item - pass\n");	
	}
	else
	{
			printf("Test1 delete item - fail\n");	
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test2DeleteNullVector(void)
{
	int _item = 3;
	Vector *_vector = NULL;

	if(VectorDelete(_vector,&_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test2 delete vector NULL - pass\n");	
	}
	else
	{
			printf("Test2 delete vector NULL - fail\n");	
	}
	VectorDestroy(_vector);
}
/****************************************************************/
void Test3tDeleteNullItem(void)
{
	int *_item = NULL;
	Vector *_vector = VectorCreate(2,2);

	if(VectorDelete(_vector,_item) == ERR_NOT_INITIALIZED)
	{
		printf("Test3 delete item NULL - pass\n");	
	}
	else
	{
		printf("Test3 delete item NULL- fail\n");	
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test4DeleteNumOfElemantZero(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);

	if(VectorDelete(_vector,&_item) == ERR_UNDERFLOW)
	{
		printf("Test4 delete num of element zero - pass\n");	
	}
	else
	{
		printf("Test4 delete num of element zero - fail\n");	
	}
	VectorDestroy(_vector);
}
/**********************************************************/
void Test5DeleteCheckRealloc(void)
{
	int _item = 3;
	int size1, size2;
	Vector *_vector = VectorCreate(1,1);
	
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	
	VectorDelete(_vector,&_item);
	
	size1 = GetSize(_vector);
	
	VectorDelete(_vector,&_item);
	
	size2 = GetSize(_vector);
	
	if(size1 > size2)
	{
		printf("Test5 delete realloc decreas- pass\n\n");	
	}
	else
	{
		printf("Test5 delete realloc decreas- fail\n\n");	
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test1GetNullVector(void)
{
	int _item = 3;
	Vector *_vector = NULL;
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector, 1, &_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test1 get vector NULL- pass\n");	
	}
	else
	{
			printf("Test1 get vector NULL - fail\n");	
	}
	VectorDestroy(_vector);
}
/*****************************************************************/
void Test2GetNullItem(void)
{
	int *_item = NULL;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector,1,_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test2 get item NULL - pass\n");	
	}
	else
	{
			printf("Test2 get item NULL - fail\n");	
	}
	VectorDestroy(_vector);
}
/****************************************************************/
void Test3GetIndexBigThenItems(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector,8,&_item) == ERR_WRONG_INDEX)
	{
			printf("Test3 get index big then items - pass\n");	
	}
	else
	{
			printf("Test3 get index big then items - fail\n");	
	}
	VectorDestroy(_vector);
}
/******************************************************************/
void Test4GetOk(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	if(VectorGet(_vector,1,&_item) == ERR_OK)
	{
			printf("Test4 get OK - pass\n\n");	
	}
	else
	{
			printf("Test4 get OK- fail\n\n");	
	}
	VectorDestroy(_vector);	
}
/********************************************************************/
void Test1SetOk(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	if(VectorSet(_vector,1,_item) == ERR_OK)
	{
			printf("Test1 set OK - pass\n");	
	}
	else
	{
			printf("Test1 set OK- fail\n");	
	}
	VectorDestroy(_vector);	
}
/********************************************************************/
void Test2SetNullVector(void)
{
	int _item = 3;
	Vector *_vector = NULL;
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector,1,&_item) == ERR_NOT_INITIALIZED)
	{
			printf("Test2 set vector NULL- pass\n");	
	}
	else
	{
			printf("Test2 set vector NULL - fail\n");	
	}
	VectorDestroy(_vector);
}
/******************************************************************/
void Test3SetIndexBigThenItems(void)
{
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector,8, &_item) == ERR_WRONG_INDEX)
	{
			printf("Test3 set index big then items - pass\n");	
	}
	else
	{
			printf("Test3 set index big then items - fail\n");	
	}
	VectorDestroy(_vector);
}
/******************************************************************/
void Test4SetSetAndGetSame(void)
{ 
	int _item = 3;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorGet(_vector,1, &_item) == VectorSet(_vector,1,3))
	{
			printf("Test4 set and get same - pass\n\n");	
	}
	else
	{
			printf("Test4 set and get same - fail\n\n");	
	}
	VectorDestroy(_vector);
}
/******************************************************************/
void Test1ItemsNumVectorNull(void)
{
	size_t _numOfItems = 3;
	Vector *_vector = NULL;
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorItemsNum(_vector,&_numOfItems) == ERR_NOT_INITIALIZED)
	{
			printf("Test1 VectorItemsNum vectorNULL - pass\n");	
	}
	else
	{
			printf("Test1 VectorItemsNum vectorNULL - fail\n");	
	}
	VectorDestroy(_vector);
}
/********************************************************************/
void Test2VectorItemsNumItemNull(void)
{
	size_t *_numOfItems = NULL;
	Vector *_vector = VectorCreate(2,2);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	VectorAdd(_vector,3);
	if(VectorItemsNum(_vector,_numOfItems) == ERR_NOT_INITIALIZED)
	{
			printf("Test2 VectorItemsNum itemsNULL- pass\n");	
	}
	else
	{
			printf("Test2 VectorItemsNum itemsNULL - fail\n");	
	}
	VectorDestroy(_vector);
}

/********************************************************************/
void Test3VectorItemsNumIncreas(void)
{
	int _item;
	size_t _numOfItems = 3;
	Vector *_vector = VectorCreate(2,2);
	int numOfElement1 = GetNItem(_vector);
	
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	VectorAdd(_vector,_item);
	VectorItemsNum (_vector, &_numOfItems);
	
	if(GetNItem(_vector) > numOfElement1)
	{
			printf("Test3 VectorItemsNum increas - pass\n");	
	}
	else
	{
			printf("Test3 VectorItemsNum increas- fail\n");	
	}
	VectorDestroy(_vector);
}
/********************************************************************/
void Test4VectorItemsNumdecreas(void)
{ 	int _item;
	int numOfElement1; 
	size_t numOfItems = 3;
	Vector *_vector = VectorCreate(2, 2);

	VectorAdd (_vector, _item);/*add one item*/
	VectorAdd (_vector, _item);/*add one item*/
	VectorAdd (_vector, _item);
	numOfElement1 = GetNItem(_vector);
	VectorDelete(_vector, &_item);
	VectorDelete(_vector, &_item);
	VectorItemsNum (_vector, &numOfItems);
    if (GetNItem(_vector) < numOfElement1)
	{

		printf("test4 VectorItems Num dencreas.....PASS\n\n\n");
	}
	else
	{
		printf("test4 VectorItems Num decreas......Fail\n\n\n");
	}	
	VectorDestroy(_vector); 
}


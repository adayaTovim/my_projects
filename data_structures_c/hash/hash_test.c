#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "hash.h"	 /*current header */

size_t GetNewSize(Hash *_hash);
size_t GetnRealSize(Hash *_hash);
size_t GetNumOfItems(Hash *_hash);
size_t GetInsertionsCount(Hash *_hash);
size_t GetMaxOfRehash(Hash *_hash);
size_t GetAllRehash(Hash *_hash);
size_t FindLargestPrime (size_t _size);

/*................*/
size_t HashFunc(void* _data)
{
    return ((size_t)(*(int*)_data)* 2);
}
/*.................*/
int EqualityFuncForInt(void* _firstData, void* _secondData)
{
    return (*(int*) _firstData == *(int*) _secondData);
}
/*.................*/
void PrintKeyForInt(void* _data)
{
    printf("%d ", *(int*)_data); 
}

/*..................*/
static void Test1_HashCreateSizeIsZero();
static void Test2_HashCreateHushFuncIsNull();
static void Test3_HashCreateEqualityFunIsNull();
static void Test4_HashCreateIfOK();
static void Test5_HashCreateIfSizeAndRealSizeIsOK();
static void Test6_HashCreateIfItemNumIsOK();
static void Test7_HashCreateIfCountAndMaxOfRehashAndAllRehashIsOK();

static void Test1HashDestroyNULL();
static void Test2HashDestroyOK();

static void Test1HashInsertHashNULL();
static void Test2HashInsertDataNULL();
static void Test3HashInsertDuplicat();
static void Test4HashInsertOverFlow();
static void Test5HashInsertInsertedOK();
static void Test6_HashInsertRehash();

static void Test1_HashRemoveIfHashIsNull();
static void Test2_HashRemoveIfKeyIsNull();
static void Test3_HashRemoveIfHashIsEmpty();
static void Test4_HashRemoveIfHashSucces();
static void Test5_HashRemoveIfHashKeyNotFound();
static void Test6_HashRemoveNumOfItems();
static void Test7_HashRemoveDataOK();


static void Test1_HashNumOfItems_hashNull();
static void Test2_HashNumOfItems_working();
static void Test3HashDestroyDubleFree();
static void Test4HashDestroyOK();

static void Test1_HashCapacity_hashNull();
static void Test2_HashCapacity_working();

static void Test1_HashAverageRehashes_hashNull();
static void Test2_HashAverageRehashes_working();

static void Test1_HashMaxReHash_hashNull();
static void Test2_HashMaxReHash_working();

static void Test1_HashPrint_working();



int main()
{
    Test1_HashCreateSizeIsZero();
    Test2_HashCreateHushFuncIsNull();
    Test3_HashCreateEqualityFunIsNull();
    Test4_HashCreateIfOK();
    Test5_HashCreateIfSizeAndRealSizeIsOK();
    Test6_HashCreateIfItemNumIsOK();
    Test7_HashCreateIfCountAndMaxOfRehashAndAllRehashIsOK();

    Test1HashDestroyNULL();
    Test2HashDestroyOK();
    Test3HashDestroyDubleFree();
    Test4HashDestroyOK();

    Test1HashInsertHashNULL();
    Test2HashInsertDataNULL();
    Test3HashInsertDuplicat();
    Test4HashInsertOverFlow();
    Test5HashInsertInsertedOK();
    Test6_HashInsertRehash();
    

    Test1_HashRemoveIfHashIsNull();
    Test2_HashRemoveIfKeyIsNull();
    Test3_HashRemoveIfHashIsEmpty();
    Test4_HashRemoveIfHashSucces();
    Test5_HashRemoveIfHashKeyNotFound();
    Test6_HashRemoveNumOfItems();
    Test7_HashRemoveDataOK();

    Test1_HashNumOfItems_hashNull();
    Test2_HashNumOfItems_working();

    Test1_HashCapacity_hashNull();
    Test2_HashCapacity_working();

    Test1_HashAverageRehashes_hashNull();
    Test2_HashAverageRehashes_working();

    Test1_HashMaxReHash_hashNull();
    Test2_HashMaxReHash_working();

    Test1_HashPrint_working();

    return 0;
}



/*.................TESTS..................*/
static void Test1_HashCreateSizeIsZero()
{
	Hash *ptrHash;
	ptrHash = HashCreate(0 , HashFunc, EqualityFuncForInt);
	if(NULL == ptrHash)
	{
		printf("%-40s %s" ,"Test1_HashCreateSizeIsZero", "**Pass**\n");
	}
	else
	{
		printf("Test1_HashCreateSizeIsZero **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*......................................*/
static void Test2_HashCreateHushFuncIsNull()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , NULL, EqualityFuncForInt);
	if(NULL == ptrHash)
	{
		printf("%-40s %s" ,"Test2_HashCreateHushFuncIsNull", "**Pass**\n");
	}
	else
	{
		printf("Test2_HashCreateHushFuncIsNull **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*......................................*/
static void Test3_HashCreateEqualityFunIsNull()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , HashFunc, NULL);
	if(NULL == ptrHash)
	{
		printf("%-40s %s" ,"Test3_HashCreateEqualityFunIsNull", "**Pass**\n");
	}
	else
	{
		printf("Test3_HashCreateEqualityFunIsNull **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*.....................................*/
static void Test4_HashCreateIfOK()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(NULL != ptrHash)
	{
		printf("%-40s %s" ,"Test4_HashCreateIfOK", "**Pass**\n");
	}
	else
	{
		printf("Test4_HashCreateIfOK **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*.......................................*/

static void Test5_HashCreateIfSizeAndRealSizeIsOK()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(GetNewSize(ptrHash) == FindLargestPrime(5*1.3) && GetnRealSize(ptrHash) == 5)
	{
		printf("%-40s %s" ,"Test5_HashCreateIfSizeAndRealSizeIsOK", "**Pass**\n");
	}
	else
	{
		printf("Test5_HashCreateIfSizeAndRealSizeIsOK **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*.......................................*/
static void Test6_HashCreateIfItemNumIsOK()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(GetNumOfItems(ptrHash) == 0)
	{
		printf("%-40s %s" ,"Test6_HashCreateIfItemNumIsOK", "**Pass**\n");
	}
	else
	{
		printf("Test6_HashCreateIfItemNumIsOK **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*......................................*/
static void Test7_HashCreateIfCountAndMaxOfRehashAndAllRehashIsOK()
{
	Hash *ptrHash;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(GetInsertionsCount(ptrHash) == 0 && GetMaxOfRehash(ptrHash) == 0 && GetAllRehash(ptrHash) == 0 )
	{
	    printf("%-40s %s" ,"Test7_HashCreateRehashOK", "**Pass**\n");
	}
	else
	{
		printf("Test7_HashCreateIfCountAndMaxOfRehashAndAllRehashIsOK **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
	printf("\n");
}
/*.........................................*/
static void Test1HashDestroyNULL()
{
    HashDestroy(NULL, NULL);
	    printf("%-40s %s" ,"Test1_HashDestroyNULL", "**Pass**\n");
}
/*.....................................*/
static void Test2HashDestroyOK()
{
	Hash *ptrHash = HashCreate(5,HashFunc,EqualityFuncForInt );
    HashDestroy(&ptrHash, NULL);
   	if (ptrHash == NULL)
	{
	    printf("%-40s %s" ,"Test2_HashDestroyOK", "**Pass**\n");
	}
	else
	{	
		printf("Test2 HashDestroy OK    **Fail**\n");
	}
}
/*....................................*/
static void Test3HashDestroyDubleFree()
{
    Hash *ptrHash = HashCreate(5,HashFunc,EqualityFuncForInt );
    HashDestroy(&ptrHash, NULL);
    HashDestroy(&ptrHash, NULL);
	printf("%-40s %s" ,"Test3_HashDestroyDubleFree", "**Pass**\n");
}
/*....................................*/
static void Test4HashDestroyOK()
{
	Hash *ptrHash = HashCreate(5,HashFunc,EqualityFuncForInt );
    HashDestroy(&ptrHash, NULL);
   	if (ptrHash == NULL)
	{
		printf("%-40s %s" ,"Test4_HashDestroyOK", "**Pass**\n");
	}
	else
	{	
		printf("Test4 HashDestroy OK  **Fail**\n");
	}
    printf("\n");
}
/*....................................*/
static void Test1HashInsertHashNULL()
{
    int num1 = 3;
    if (SET_UNINITIALIZED == HashInsert(NULL, &num1))
	{
		printf("%-40s %s" ,"Test1_HashInsert_HashNULL", "**Pass**\n");
	}
	else
	{	
		printf("Test1 HashInsert HashNULL  **Fail**\n");
	}
}
/*.................................*/
static void Test2HashInsertDataNULL()
{
    Hash *ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
    if (SET_UNINITIALIZED == HashInsert(ptrHash, NULL))
	{
		printf("%-40s %s" ,"Test2_HashInsertDataNULL", "**Pass**\n");
	}
	else
	{	
		printf("Test2 HashInsert DataNULL....... Fail\n");
	}
    HashDestroy(&ptrHash, NULL);
}
/*...............................*/
static void Test3HashInsertDuplicat()
{
    Hash *ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
    int num1 = 3;
    HashInsert(ptrHash, &num1);
    if (SET_KEY_DUPLICATE == HashInsert(ptrHash, &num1))
	{
		printf("%-40s %s" ,"Test3_HashInsertDuplicat", "**Pass**\n");
	}
	else
	{	
		printf("Test3 HashInsert DUPLICATE   **Fail**\n");
	}
    HashDestroy(&ptrHash, NULL);
}
/*................................*/
static void Test4HashInsertOverFlow()
{
    
    Hash *ptrHash = HashCreate( 3 , HashFunc, EqualityFuncForInt);
    int num1 = 3;
    int num2 = 5;
    int num3 = 8;
    int num4 = 10;
    HashInsert(ptrHash, &num1);
    HashInsert(ptrHash, &num2);
    HashInsert(ptrHash, &num3);
    if (SET_OVERFLOW == HashInsert(ptrHash, &num4))
	{
		printf("%-40s %s" ,"Test4_HashInsertOverFlow", "**Pass**\n");
	}
	else
	{	
		printf("Test4 HashInsertOverFlow....... Fail\n");
	}
    HashDestroy(&ptrHash, NULL);
}
/*......................................*/
static void Test5HashInsertInsertedOK()
{
    Hash *ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
    int num1 = 3;
    int num2 = 2;
    HashInsert(ptrHash, &num1);
    HashInsert(ptrHash, &num2);
    if (HashIsFound(ptrHash, &num2) == TRUE )
	{
		printf("%-40s %s" ,"Test5_HashInsertInsertedOK", "**Pass**\n");
	}
	else
	{	
		printf("Test5 HashInsert Inserted....... Fail\n");
	}
    HashDestroy(&ptrHash, NULL);
}
/*.....................................*/
static void Test6_HashInsertRehash()
{
    Hash *ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
    int num1 = 3;
    int num2 = 5;
    int num3 = 28;
    int num4 = 14;
    HashInsert(ptrHash, &num1);
    HashInsert(ptrHash, &num2);
    HashInsert(ptrHash, &num3);
    if (HashInsert(ptrHash, &num4) == SET_SUCCESS)
	{
		printf("%-40s %s" ,"Test6_HashInsertRehash", "**Pass**\n");
	}
	else
	{	
		printf("Test5_HashInsertRehash !!*FAIL*!!\n");
	}
    HashDestroy(&ptrHash, NULL);
	printf("\n");
}
/*....................................*/
static void Test1_HashRemoveIfHashIsNull()
{
	Hash *ptrHash;
	void* data;
	int num = 5;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(HashRemove(NULL, &num, &data) == SET_UNINITIALIZED)
	{
		printf("%-40s %s" ,"Test1_HashRemoveIfHashIsNull", "**Pass**\n");
	}
	else
	{
		printf("Test1_HashRemoveIfHashIsNull **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*...........................................*/
static void Test2_HashRemoveIfKeyIsNull()
{
	Hash *ptrHash;
	void* data;
	int num = 5;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(HashRemove(ptrHash, NULL, &data) == SET_UNINITIALIZED)
	{
		printf("%-40s %s" ,"Test2_HashRemoveIfKeyIsNull", "**Pass**\n");
	}
	else
	{
		printf("Test2_HashRemoveIfKeyIsNull **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*...........................................*/
static void Test3_HashRemoveIfHashIsEmpty()
{
	Hash *ptrHash;
	void* data;
	int num = 5;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	if(HashRemove(ptrHash, &num, &data) == SET_UNDERFLOW)
	{
		printf("%-40s %s" ,"Test3_HashRemoveIfHashIsEmpty", "**Pass**\n");
	}
	else
	{
		printf("Test3_HashRemoveIfHashIsEmpty **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*...........................................*/
static void Test4_HashRemoveIfHashSucces()
{
	Hash *ptrHash;
	void* data;
	int num1 = 5, num2 = 4, num3 = 8, num4 = 6, num5 = 9 ;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	HashInsert(ptrHash, &num1);
	HashInsert(ptrHash, &num2);
	HashInsert(ptrHash, &num3);
    HashRemove(ptrHash, &num1, &data);
	if(HashIsFound(ptrHash, &num1) == FALSE)
	{
		printf("%-40s %s" ,"Test4_HashRemoveIfHashSucces", "**Pass**\n");
	}
	else
	{
		printf("Test4_HashRemoveIfHashSucces **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}
/*...........................................*/
static void Test5_HashRemoveIfHashKeyNotFound()
{
	Hash *ptrHash;
	void* data;
	int num1 = 5, num2 = 4, num3 = 8, num4 = 6, num5 = 9 ;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	HashInsert(ptrHash, &num1);
	HashInsert(ptrHash, &num2);
	HashInsert(ptrHash, &num3);
	if(HashRemove(ptrHash, &num4, &data) == SET_KEY_NOT_FOUND)
	{
		printf("%-40s %s" ,"Test5_HashRemoveIfHashKeyNotFound", "**Pass**\n");
	}
	else
	{
		printf("Test5_HashRemoveIfHashKeyNotFound **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}

static void Test6_HashRemoveNumOfItems()
{
	Hash *ptrHash;
	void* data;
	int num1 = 5, num2 = 4, num3 = 8, num4 = 6, num5 = 9 ;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	HashInsert(ptrHash, &num1);
	HashInsert(ptrHash, &num2);
	HashInsert(ptrHash, &num3);
	HashRemove(ptrHash, &num1, &data);
	if(GetNumOfItems(ptrHash) == 2)
	{
		printf("%-40s %s" ,"Test6_HashRemoveNumOfItems", "**Pass**\n");
	}
	else
	{
		printf("Test6_HashRemoveNumOfItems **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
}

static void Test7_HashRemoveDataOK()
{
	Hash *ptrHash;
	void* data;
	int num1 = 5, num2 = 4, num3 = 8, num4 = 6, num5 = 9 ;
	ptrHash = HashCreate( 5 , HashFunc, EqualityFuncForInt);
	HashInsert(ptrHash, &num1);
	HashInsert(ptrHash, &num2);
	HashInsert(ptrHash, &num3);
	HashRemove(ptrHash, &num1, &data);
	if(data == &num1)
	{
		printf("%-40s %s" ,"Test7_HashRemoveDataOK", "**Pass**\n");
	}
	else
	{
		printf("Test7_HashRemoveDataOK **FAIL**\n");
	}
	HashDestroy(&ptrHash, NULL);
	printf("\n");
}


static void Test1_HashNumOfItems_hashNull()
{
	if(HashNumOfItems(NULL) == 0)
	{
		printf("%-40s %s" ,"Test1_HashNumOfItems_hashNull", "**Pass**\n");
	}
	else 
	{
		printf("Test1_HashNumOfItems_hashNull **fail**\n");
	}
}
/*.....................................*/
static void Test2_HashNumOfItems_working()
{
	Hash* ptrHash = HashCreate(10, HashFunc, EqualityFuncForInt);
    int data1 = 3;
    int data2 = 8;
    int data3 = 14;
    HashInsert(ptrHash, &data1);
    HashInsert(ptrHash, &data2);
    HashInsert(ptrHash, &data3);
    if(HashNumOfItems(ptrHash) == GetNumOfItems(ptrHash))
	{
		printf("%-40s %s" ,"Test2_HashNumOfItems_working", "**Pass**\n");
	}
	else 
	{
		printf("Test2_HashNumOfItems_working **fail**\n");
	}
    HashDestroy(&ptrHash, NULL);
    printf("\n");

}
/*.....................................*/
static void Test1_HashCapacity_hashNull()
{
    if(HashCapacity(NULL) == 0)
	{
		printf("%-40s %s" ,"Test1_HashCapacity_hashNull", "**Pass**\n");
	}
	else 
	{
		printf("Test1_HashCapacity_hashNull **fail**\n");
	}
}
/*.......................................*/
static void Test2_HashCapacity_working()
{
	Hash* ptrHash = HashCreate(10, HashFunc, EqualityFuncForInt);
    if(HashCapacity(ptrHash) == 10)
	{
		printf("%-40s %s" ,"Test2_HashCapacity_working", "**Pass**\n");
	}
	else 
	{
		printf("Test2_HashCapacity_working **fail**\n");
	}
    HashDestroy(&ptrHash, NULL);
    printf("\n");

}
/*.......................................*/
static void Test1_HashAverageRehashes_hashNull()
{
    if(HashAverageRehashes(NULL) == 0)
	{
		printf("%-40s %s" ,"Test1_HashAverageRehashes_hashNull", "**Pass**\n");
	}
	else 
	{
		printf("Test1_HashAverageRehashes_hashNull **fail**\n");
	}
}
/*......................................*/

static void Test2_HashAverageRehashes_working()
{
    Hash* ptrHash = HashCreate(10, HashFunc, EqualityFuncForInt);
    int data1 = 3;
    int data2 = 8;
    int data3 = 14;
    size_t allRehash, counterInseration;

    HashInsert(ptrHash, &data1);
    HashInsert(ptrHash, &data2);
    HashInsert(ptrHash, &data2);
    HashInsert(ptrHash, &data2);
    allRehash = GetAllRehash(ptrHash);
    counterInseration = GetInsertionsCount(ptrHash);

    if(HashAverageRehashes(ptrHash) == allRehash/counterInseration)
	{
		printf("%-40s %s" ,"Test2_HashAverageRehashes_working", "**Pass**\n");
	}
	else 
	{
		printf("Test2_HashAverageRehashes_working **fail**\n");
	}
    HashDestroy(&ptrHash, NULL);
    printf("\n");

}

/*.......................................*/
static void Test1_HashMaxReHash_hashNull()
{
    if(HashAverageRehashes(NULL) == 0)
	{
		printf("%-40s %s" ,"Test1_HashMaxReHash_hashNull", "**Pass**\n");
	}
	else 
	{
		printf("Test1_HashMaxReHash_hashNull **fail**\n");
	}
}
/*.......................................*/

static void Test2_HashMaxReHash_working()
{
    Hash* ptrHash = HashCreate(10, HashFunc, EqualityFuncForInt);
    int data1 = 3;
    int data2 = 8;
    int data3 = 14;
    HashInsert(ptrHash, &data1);
    HashInsert(ptrHash, &data2);
    HashInsert(ptrHash, &data3);
    if(HashMaxReHash(ptrHash) == GetMaxOfRehash(ptrHash))
	{
		printf("%-40s %s" ,"Test2_HashMaxReHash_working", "**Pass**\n");
	}
	else 
	{
		printf("Test2_HashMaxReHash_working **fail**\n");
	}
    HashDestroy(&ptrHash, NULL);
    printf("\n");
}   

/*.......................................*/
static void Test1_HashPrint_working()
{
    Hash* ptrHash = HashCreate(10, HashFunc, EqualityFuncForInt);
    int data1 = 3;
    int data2 = 8;
    int data3 = 14;
    HashInsert(ptrHash, &data1);
    HashInsert(ptrHash, &data2);
    HashInsert(ptrHash, &data3);
	printf("%-40s %s" ,"Test1_HashPrint_working", "**Pass**\n");
    HashPrint(ptrHash, PrintKeyForInt);
    printf("\n");

}
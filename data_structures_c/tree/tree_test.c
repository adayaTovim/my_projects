#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "tree.h"	 /*current header */
#define MAGIC_NUM 23005363


void TreeCreateIfMallocOK(void);
void TestTreeDestroyIfWorking(void);
void TestTreeInsert_ERR_NOT_INITIALIZED(void);
void TestTreeInsert_ERR_DUBLE_DATA(void);
void TestTreeInsert_ERR_OK(void);
void TestTreeIsDataFound_TRUE(void);
void TestTreeIsDataFound_FALSE(void);
void TestTreeIsDataFound_NULL(void);
void TestTreePrint_(void);
void TestIsFullTree_TRUE(void);
void TestIsFullTree_FALSE(void);
void TestAreSimilarTree_TRUE(void);
void TestAreSimilarTree_FALSE(void);
void TestCalcTreeLevel_NULL(void);
void TestCalcTreeLevel_OK(void);
void TestCalcTreeLevel_ZERO(void);
void TestMirrorTree_NULL(void);
void TestMirrorTree_OK(void);

int main()
{
	int result;
	Tree *ptree1 = TreeCreate();
	Tree *ptree2 = TreeCreate();
	TreeInsert(ptree1,8);
	TreeInsert(ptree1,10);
	TreeInsert(ptree1,3);
	TreeInsert(ptree2,8);
	TreeInsert(ptree2,10);
	TreeInsert(ptree2,9);
	
	TreeCreateIfMallocOK();
	TestTreeDestroyIfWorking();
	TestTreeInsert_ERR_NOT_INITIALIZED();
	TestTreeInsert_ERR_DUBLE_DATA();
	TestTreeInsert_ERR_OK();
	TestTreeIsDataFound_TRUE();
	TestTreeIsDataFound_FALSE();
	TestTreeIsDataFound_NULL();
	TestIsFullTree_TRUE();
	TestIsFullTree_FALSE();
	TestAreSimilarTree_TRUE();
	TestAreSimilarTree_FALSE();
	TestCalcTreeLevel_NULL();
	TestCalcTreeLevel_OK();
	/*TestCalcTreeLevel_ZERO();*/
	TestMirrorTree_NULL();
	TestMirrorTree_OK();
	
	
	
	TestTreePrint_();

	
	printf("\n\n");
	
/*	result = isFullTree(ptree1);
	printf("IsFullTree :%d \n",result);
	
	result = AreSimilarTree(ptree1,ptree2);
	printf("Similar tree :%d \n",result);
	return 0;
*/

return;
}


void TreeCreateIfMallocOK(void)
{
	Tree *ptrTree = TreeCreate();
	if(ptrTree != NULL)
	{
		printf("TreeCreateIfMallocOK **PASS**\n");
	}
	else
	{
		printf("TreeCreateIfMallocOK**FAIL**\n");
	}
	TreeDestroy(ptrTree);
}

 void TestTreeDestroyIfWorking(void)
{

	int *magicNum;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 30);
	TreeInsert(ptrTree, 10);
	TreeDestroy(ptrTree);
	
	if(GetMagicNum(ptrTree) != MAGIC_NUM)
	{
		printf("TestTreeDestroyIfWorking **PASS**\n");
	}
	else
	{
		printf("TestTreeDestroyIfWorking **FAIL**\n");
	}
}

void TestTreeInsert_ERR_NOT_INITIALIZED(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	if(TreeInsert(NULL, 30) == ERR_NOT_INITIALIZED)
	{
		printf("TestTreeInsert_ERR_NOT_INITIALIZED **PASS**\n");
	}
	else
	{
		printf("TestTreeInsert_ERR_NOT_INITIALIZED **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}

void TestTreeInsert_ERR_DUBLE_DATA(void) /***/
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 40);
	TreeInsert(ptrTree, 5);
	if(TreeInsert(ptrTree, 10) == ERR_DOUBLE_DATA)
	{
		printf("TestTreeInsert_ERR_DUBLE_DATA **PASS**\n");
	}
	else
	{
		printf("TestTreeInsert_ERR_DUBLE_DATA **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}


void TestTreeInsert_ERR_OK(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 40);
	TreeInsert(ptrTree, 5);
	if(TreeInsert(ptrTree, 1) == ERR_OK)
	{
		printf("TestTreeInsert_ERR_OK **PASS**\n");
	}
	else
	{
		printf("TestTreeInsert_ERR_OK **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}

void TestTreeIsDataFound_NULL(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 5);
	if(TreeIsDataFound(NULL, 1) == FALSE)
	{
		printf("TestTreeIsDataFound_NULL **PASS**\n");
	}
	else
	{
		printf("TestTreeIsDataFound_NULL **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}
void TestTreeIsDataFound_TRUE(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 5);
	if(TreeIsDataFound(ptrTree, 5) == TRUE)
	{
		printf("TestTreeIsDataFound_TRUE **PASS**\n");
	}
	else
	{
		printf("TestTreeIsDataFound_TRUE **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}

void TestTreeIsDataFound_FALSE(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 5);
	if(TreeIsDataFound(ptrTree, 1) == FALSE)
	{
		printf("TestTreeIsDataFound_TRUE **PASS**\n");
	}
	else
	{
		printf("TestTreeIsDataFound_TRUE **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}


void TestTreePrint_(void) /***/
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 30);
	TreeInsert(ptrTree, 44);
	TreeInsert(ptrTree, 21);
	TreeInsert(ptrTree, 12);
	TreeInsert(ptrTree, 11);
	TreeInsert(ptrTree, 5);
	printf("TestTreePrint_ IN_ORDER\n");
	TreePrint(ptrTree, IN_ORDER); 
	printf("\nTestTreePrint_ PRE_ORDER\n");
	TreePrint(ptrTree, PRE_ORDER);
	printf("\nTestTreePrint_ POST_ORDER\n");
	TreePrint(ptrTree, POST_ORDER);
	TreeDestroy(ptrTree);
}

void TestIsFullTree_TRUE(void)
{
	int result;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 8);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 5);

	result = isFullTree(ptrTree);
	if(result == TRUE)
	{
		printf("TestIsFullTree_TRUE **PASS**\n");
	}
	else
	{
		printf("TestIsFullTree_TRUE **FAIL**\n");	
	}
	TreeDestroy(ptrTree);
}

void TestIsFullTree_FALSE(void)
{
	int result;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 20);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 5);

	result = isFullTree(ptrTree);
	if(result == FALSE)
	{
		printf("TestIsFullTree_FALSE **PASS**\n");
	}
	else
	{
		printf("TestIsFullTree_FALSE **FAIL**\n");	
	}
	TreeDestroy(ptrTree);
}

void TestAreSimilarTree_TRUE(void)
{
	int result;
	Tree *ptrTree1;
	Tree *ptrTree2;
	ptrTree1 = TreeCreate();
	ptrTree2 = TreeCreate();
	TreeInsert(ptrTree1, 20);
	TreeInsert(ptrTree1, 10);
	TreeInsert(ptrTree2, 20);
	TreeInsert(ptrTree2, 10);

	result = AreSimilarTree(ptrTree1,ptrTree2);
	if(result == TRUE)
	{
		printf("TestAreSimilarTree_TRUE **PASS**\n");
	}
	else
	{
		printf("TestAreSimilarTree_TRUE **FAIL**\n");	
	}	
	TreeDestroy(ptrTree1);
	TreeDestroy(ptrTree2);
}

void TestAreSimilarTree_FALSE(void)
{
	int result;
	Tree *ptrTree1;
	Tree *ptrTree2;
	ptrTree1 = TreeCreate();
	ptrTree2 = TreeCreate();
	TreeInsert(ptrTree1, 20);
	TreeInsert(ptrTree2, 20);
	TreeInsert(ptrTree2, 10);

	result = AreSimilarTree(ptrTree1,ptrTree2);
	if(result == FALSE)
	{
		printf("TestAreSimilarTree_FALSE **PASS**\n");
	}
	else
	{
		printf("TestAreSimilarTree_FALSE **FAIL**\n");	
	}
	TreeDestroy(ptrTree1);
	TreeDestroy(ptrTree2);
}

void TestCalcTreeLevel_NULL(void)
{
	if(CalcTreeLevel(NULL) == -1)
	{
		printf("TestCalcTreeLevel_NULL **PASS**\n");
	}
	else
	{
		printf("TestCalcTreeLevel_NULL **FAIL**\n");
	}
}

void TestCalcTreeLevel_OK(void)
{
	int result;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 9);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 5);
	TreeInsert(ptrTree, 2);
	TreeInsert(ptrTree, 13);	

	result = CalcTreeLevel(ptrTree);
	if(result == 3)
	{
		printf("TestCalcTreeLevel_OK **PASS**\n");
	}
	else
	{
		printf("TestCalcTreeLevel_OK **FAIL**\n");	
	}
	TreeDestroy(ptrTree);
}

void TestCalcTreeLevel_ZERO(void)
{
	int result;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree,8);

	result = CalcTreeLevel(ptrTree);
	if(result == 0)
	{
		printf("TestCalcTreeLevel_ZERO **PASS**\n");
	}
	else
	{
		printf("TestCalcTreeLevel_ZERO **FAIL**\n");	
	}
	TreeDestroy(ptrTree);
}

void TestMirrorTree_NULL(void)
{
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 8);
	if(MirrorTree(NULL) == ERR_NOT_INITIALIZED)
	{
		printf("TestMirrorTree_NULL **PASS**\n");
	}
	else
	{
		printf("TestMirrorTree_NULL **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}

void TestMirrorTree_OK(void)
{
	int result;
	Tree *ptrTree ;
	ptrTree = TreeCreate();
	TreeInsert(ptrTree, 9);
	TreeInsert(ptrTree, 10);
	TreeInsert(ptrTree, 5);
	TreeInsert(ptrTree, 2);
	TreeInsert(ptrTree, 13);	
	
	if(MirrorTree(ptrTree) == ERR_OK)
	{
		printf("TestMirrorTree_OK **PASS**\n");
	}
	else
	{
		printf("TestMirrorTree_OK **FAIL**\n");
	}
	TreeDestroy(ptrTree);
}


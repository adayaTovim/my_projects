#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "BSTree.h"	 /*current header */

void* GetLeft(BSTree* _tree);
void* GetRight(BSTree* _tree);
void* GetFather(BSTree* _tree);
void* GetRoot(BSTree* _tree);
void* GetLeftData(BSTree* _tree);
void* GetRightData(BSTree* _tree);
void* TreeGetData(BSTreeItr* _node);
int IsTree(BSTree* _tree);

static void Test1_BSTreeCreate_NULL();
static void Test2_BSTreeCreate_leftNULL();
static void Test3_BSTreeCreate_RightNULL();
static void Test4_BSTreeCreate_Father();
static void Test5_BSTreeCreate_Working();

static void Test1_BSTreeDestroy_treeNULL();
static void Test2_BSTreeDestroy_Working();
static void Test3_BSTreeDestroy_DoubleFree();

static void Test1_BSTreeInsert_treeNULL();
static void Test2_BSTreeInsert_itemNULL();
static void Test3_BSTreeInsert_working();
static void Test4_BSTreeInsert_duplicate();

static void Test1_BSTreeItrBegin_treeNULL();
static void Test2_BSTreeItrBegin_treeEmpty();
static void Test3_BSTreeItrBegin_Working();

static void Test1_BSTreeItrEnd_treeNULL();
static void Test2_BSTreeItrEnd_treeEmpty();
static void Test3_BSTreeItrEnd_Working();

static void Test1_BSTreeItrEquals_WorkingEqual();
static void Test2_BSTreeItrEquals_WorkingNotEqual();

static void Test1_BSTreeItrNext_itNULL();
static void Test2_BSTreeItrNext_working();

static void Test1_BSTreeItrPrev_itNULL();
static void Test2_BSTreeItrPrev_working();

static void Test1_BSTreeItrRemove_itNULL();
static void Test2_BSTreeItrRemove_removeEnd();
static void Test3_BSTreeItrRemove_removeLeaf();
static void Test4_BSTreeItrRemove_removeOneSon();

LessComparatorInt(void* _left, void* _right)
{
    if(*(int*)_left == *(int*)_right)
    {
        return 0;
    }
    if(*(int*)_left > *(int*)_right)
    {
        return 1;
    }
    if(*(int*)_left < *(int*)_right)
    {
        return -1;
    }
}

int main()
{
    Test1_BSTreeCreate_NULL();
    Test2_BSTreeCreate_leftNULL();
    Test3_BSTreeCreate_RightNULL();
    Test4_BSTreeCreate_Father();
    Test5_BSTreeCreate_Working();

    Test1_BSTreeDestroy_treeNULL();
    Test2_BSTreeDestroy_Working();
    Test3_BSTreeDestroy_DoubleFree();

    Test1_BSTreeInsert_treeNULL();
    Test2_BSTreeInsert_itemNULL();
    Test3_BSTreeInsert_working();
	Test4_BSTreeInsert_duplicate();

    Test1_BSTreeItrBegin_treeNULL();
    Test2_BSTreeItrBegin_treeEmpty();
    Test3_BSTreeItrBegin_Working();

    Test1_BSTreeItrEnd_treeNULL();
    Test2_BSTreeItrEnd_treeEmpty();
    Test3_BSTreeItrEnd_Working();

    Test1_BSTreeItrEquals_WorkingEqual();
    Test2_BSTreeItrEquals_WorkingNotEqual();

	Test1_BSTreeItrNext_itNULL();
	Test2_BSTreeItrNext_working();

	Test1_BSTreeItrPrev_itNULL();
	Test2_BSTreeItrPrev_working();

	Test1_BSTreeItrRemove_itNULL();
	Test2_BSTreeItrRemove_removeEnd();
	Test3_BSTreeItrRemove_removeLeaf();
	Test4_BSTreeItrRemove_removeOneSon();

    return 0;
}

/*...............................*/
static void Test1_BSTreeCreate_NULL()
{
	if(BSTreeCreate(NULL) == NULL)
	{
		printf("Test1_BSTreeCreate_NULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeCreate_NULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeCreate_leftNULL()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(GetLeft(PTree) == NULL)
	{
		printf("Test2_BSTreeCreate_leftNULL  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeCreate_leftNULL **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test3_BSTreeCreate_RightNULL()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(GetRight(PTree) == NULL)
	{
		printf("Test3_BSTreeCreate_RightNULL  **PASS**\n");
	}
	else
	{
		printf("Test3_BSTreeCreate_RightNULL **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test4_BSTreeCreate_Father()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(GetFather(PTree) == GetRoot(PTree))
	{
		printf("Test4_BSTreeCreate_Father  **PASS**\n");
	}
	else
	{
		printf("Test4_BSTreeCreate_Father **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test5_BSTreeCreate_Working()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(PTree != NULL)
	{
		printf("Test5_BSTreeCreate_Working  **PASS**\n");
	}
	else
	{
		printf("Test5_BSTreeCreate_Working **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
    printf("\n");
}
/*...............................*/
static void Test1_BSTreeDestroy_treeNULL()
{
    BSTreeDestroy(NULL,NULL);
    printf("Test1_BSTreeDestroy_treeNULL  **PASS**\n");
}
/*...............................*/
static void Test2_BSTreeDestroy_Working()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    BSTreeDestroy(&PTree,NULL);
    if(PTree == NULL)
	{
		printf("Test2_BSTreeDestroy_Working  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeDestroy_Working **FAIL**\n");
    }
}
/*...............................*/
static void Test3_BSTreeDestroy_DoubleFree()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    BSTreeDestroy(&PTree,NULL);
    BSTreeDestroy(&PTree,NULL);
    printf("Test3_BSTreeDestroy_DoubleFree  **PASS**\n");
    printf("\n");

}
/*...............................*/
static void Test1_BSTreeInsert_treeNULL()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    int item = 3;
    if(BSTreeInsert(NULL, &item) == NULL)
	{
		printf("Test1_BSTreeInsert_treeNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeInsert_treeNULL **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test2_BSTreeInsert_itemNULL()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(BSTreeInsert(PTree, NULL) == NULL)
	{
		printf("Test2_BSTreeInsert_itemNULL  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeInsert_itemNULL **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test3_BSTreeInsert_working()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    int item = 3;
    void* itr = BSTreeInsert(PTree, &item);
    if(item == (*(int*)GetLeftData(PTree)))
	{
		printf("Test3_BSTreeInsert_working  **PASS**\n");
	}
	else
	{
		printf("Test3_BSTreeInsert_working **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test4_BSTreeInsert_duplicate()
{
	BSTree* PTree = BSTreeCreate(LessComparatorInt);
    int item = 3;
    void* itr1 = BSTreeInsert(PTree, &item);
	void* itr2 = BSTreeInsert(PTree, &item);
    if(itr2 == GetRoot(PTree))
	{
		printf("Test4_BSTreeInsert_duplicate  **PASS**\n");
	}
	else
	{
		printf("Test4_BSTreeInsert_duplicate **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
	printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrBegin_treeNULL()
{
    if(BSTreeItrBegin(NULL) == NULL)
	{
		printf("Test1_BSTreeItrBegin_treeNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrBegin_treeNULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrBegin_treeEmpty()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(BSTreeItrBegin(PTree) == GetRoot(PTree))
	{
		printf("Test2_BSTreeItrBegin_treeEmpty  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeItrBegin_treeEmpty **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test3_BSTreeItrBegin_Working()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    int item1 = 3;
    int item2 = 4;
    void* itr;
    BSTreeInsert(PTree, &item1);
    BSTreeInsert(PTree, &item2);
    itr = BSTreeItrBegin(PTree);
    if(TreeGetData(itr) == &item1)
	{
		printf("Test3_BSTreeItrBegin_Working  **PASS**\n");
	}
	else
	{
		printf("Test3_BSTreeItrBegin_Working **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
    printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrEnd_treeNULL()
{
    if(BSTreeItrEnd(NULL) == NULL)
	{
		printf("Test1_BSTreeItrEnd_treeNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrEnd_treeNULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrEnd_treeEmpty()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    if(BSTreeItrEnd(PTree) == GetRoot(PTree))
	{
		printf("Test2_BSTreeItrEnd_treeEmpty  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeItrEnd_treeEmpty **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test3_BSTreeItrEnd_Working()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
    int item1 = 3;
    int item2 = 4;
    BSTreeInsert(PTree, &item1);
    BSTreeInsert(PTree, &item2);
    if(BSTreeItrEnd(PTree) == GetRoot(PTree))
	{
		printf("Test3_BSTreeItrEnd_Working  **PASS**\n");
	}
	else
	{
		printf("Test3_BSTreeItrEnd_Working **FAIL**\n");
    }
    BSTreeDestroy(&PTree,NULL);
    printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrEquals_WorkingEqual()
{
    void* a;
    if(BSTreeItrEquals(a, a) == 1)
	{
		printf("Test1_BSTreeItrEquals_WorkingEqual  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrEquals_WorkingEqual **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrEquals_WorkingNotEqual()
{
    void* a;
    void* b;
    if(BSTreeItrEquals(a, b) == 0)
	{
		printf("Test2_BSTreeItrEquals_WorkingNotEqual  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeItrEquals_WorkingNotEqual **FAIL**\n");
    }
    printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrNext_itNULL()
{
    if(BSTreeItrNext(NULL) == NULL)
	{
		printf("Test1_BSTreeItrNext_itNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrNext_itNULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrNext_working()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
	BSTreeItr itr1, itr2, itr3;
    itr1 = BSTreeItrBegin(PTree);
    itr2 = BSTreeItrEnd(PTree);
    itr3 = BSTreeItrNext(itr2);
	if(itr3 == itr2)
	{
		printf("Test2_BSTreeItrNext_working  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeItrNext_working **FAIL**\n");
    }
	BSTreeDestroy(&PTree,NULL);
	printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrPrev_itNULL()
{
    if(BSTreeItrPrev(NULL) == NULL)
	{
		printf("Test1_BSTreeItrPrev_itNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrPrev_itNULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrPrev_working()
{
    BSTree* PTree = BSTreeCreate(LessComparatorInt);
	BSTreeItr itr1, itr2, itr3;
    itr1 = BSTreeItrBegin(PTree);
    itr2 = BSTreeItrEnd(PTree);
    itr3 = BSTreeItrPrev(itr1);
	if(itr3 == itr1)
	{
		printf("Test2__BSTreeItrPrev_working  **PASS**\n");
	}
	else
	{
		printf("Test2__BSTreeItrPrev_working **FAIL**\n");
    }
	BSTreeDestroy(&PTree,NULL);
	printf("\n");
}
/*...............................*/
static void Test1_BSTreeItrRemove_itNULL()
{
    if(BSTreeItrRemove(NULL) == NULL)
	{
		printf("Test1_BSTreeItrRemove_itNULL  **PASS**\n");
	}
	else
	{
		printf("Test1_BSTreeItrRemove_itNULL **FAIL**\n");
    }
}
/*...............................*/
static void Test2_BSTreeItrRemove_removeEnd()
{
    int i = 0;
    int arr[11] = {80, 90, 95, 110, 107, 75, 50, 79, 65, 60, 40};
    BSTreeItr itr;
    void* item;
    BSTree *PTree = BSTreeCreate(LessComparatorInt);
    for (i = 0; i < 11; ++i)
    {
        itr = BSTreeInsert(PTree, &arr[i]);
    }
	itr = BSTreeItrEnd(PTree);
	item = BSTreeItrRemove(itr);
	if(item == NULL)
	{
		printf("Test2_BSTreeItrRemove_removeEnd  **PASS**\n");
	}
	else
	{
		printf("Test2_BSTreeItrRemove_removeEnd **FAIL**\n");
    }
	BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test3_BSTreeItrRemove_removeLeaf()
{
    int i = 0;
    int arr[11] = {80, 90, 95, 110, 107, 75, 50, 79, 65, 60, 40};
    BSTreeItr itr;
    void* item;
    BSTree *PTree = BSTreeCreate(LessComparatorInt);
    for (i = 0; i < 11; ++i)
    {
        itr = BSTreeInsert(PTree, &arr[i]);
    }
    itr = BSTreeItrBegin(PTree);
    item = BSTreeItrRemove(itr);
	if(*(int*)item == 40 && IsTree(PTree) )
	{
		printf("Test3_BSTreeItrRemove_removeLeaf  **PASS**\n");
	}
	else
	{
		printf("Test3_BSTreeItrRemove_removeLeaf **FAIL**\n");
    }
	BSTreeDestroy(&PTree,NULL);
}
/*...............................*/
static void Test4_BSTreeItrRemove_removeOneSon()
{
    int i = 0;
    int arr[11] = {80, 90, 95, 110, 107, 75, 50, 79, 65, 60, 40};
    BSTreeItr itr;
    void* item;
    BSTree *PTree = BSTreeCreate(LessComparatorInt);
    for (i = 0; i < 11; ++i)
    {
        itr = BSTreeInsert(PTree, &arr[i]);
    }
    itr = BSTreeItrBegin(PTree);
    item = BSTreeItrRemove(itr);
	if(*(int*)item == 50 && IsTree(PTree) )
	{
		printf("Test4_BSTreeItrRemove_removeOneSon  **PASS**\n");
	}
	else
	{
		printf("Test4_BSTreeItrRemove_removeOneSon **FAIL**\n");
    }
	BSTreeDestroy(&PTree,NULL);
}



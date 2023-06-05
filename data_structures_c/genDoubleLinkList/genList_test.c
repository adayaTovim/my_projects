#include <stdio.h>
#include <stdlib.h>  /*malloc*/
#include <stddef.h>  /* size_t */
#include "genList.h" /*API*/
#include "listItr.h" /*ITERATOR*/


static void Test1ListCreateHeadPrev();
static void Test2ListCreateTailNext();
static void Test3ListCreateHeadNext();
static void Test4ListCreateTailPrev();

static void Test1ListDestroyWorking();
static void Test2ListDestroyDoubleFree();

static void Test1ListPushHeadListNULL();
static void Test2ListPushHeadItemNULL();
static void Test3ListPushHeadSizeIncrease();
static void Test4ListPushHeadWorking();

static void Test1ListPushTailListNULL();
static void Test2ListPushTailItemNULL();
static void Test3ListPushTailSizeIncrease();
static void Test4ListPushTailWorking();

static void Test1ListPopHeadListNULL();
static void Test2ListPopHeadItemNULL();
static void Test3ListPopHeadWorking();
static void Test4ListPopHeadSizeDecrease();

static void Test1ListPopTailListNULL();
static void Test2ListPopTailItemNULL();
static void Test3ListPopTailWorking();
static void Test4ListPopTailSizeDecrease();


static void Test1ListSizeOK();

/*.............................*/

static void Test1ListItrBeginListNULL();
static void Test2ListItrBeginWorking();
static void Test1ListItrEndListNULL();
static void Test2ListItrEndWorking();
static void Test1ListItrEqualsTrue();
static void Test2ListItrEqualsFalse();
static void Test1ListItrNextItrNULL();
static void Test2ListItrNextWorking();
static void Test1ListItrPrevItrNULL();
static void Test2ListItrPrevWorking();
static void Test1ListItrGetItrNULL();
static void Test1ListItrSetItrNULL();
static void Test2ListItrSetElementNULL();
static void Test1ListItrInsertBeforeItrNULL();
static void Test2ListItrInsertBeforeElementNULL();
static void Test1ListItrRemoveItrNULL();



/*.............................*/

Node* GetHeadNext(List *_list);
Node* GetTailPrev(List *_list);
Node* GetHeadPrev(List *_list);
Node* GetTailNext(List *_list);
void* GetTail(List* list);
void* GetHead(List* list);

int main()
{
    printf("\n.......API TEST.......\n");
    Test1ListCreateHeadPrev();
    Test2ListCreateTailNext();
    Test3ListCreateHeadNext();
    Test4ListCreateTailPrev();
    Test1ListDestroyWorking();
    Test2ListDestroyDoubleFree();
 
    Test1ListPushHeadListNULL();
    Test2ListPushHeadItemNULL();
    Test3ListPushHeadSizeIncrease();
    Test4ListPushHeadWorking();
    
    Test1ListPushTailListNULL();
    Test2ListPushTailItemNULL();
    Test3ListPushTailSizeIncrease();
    Test4ListPushTailWorking();

    Test1ListPopHeadListNULL();
    Test2ListPopHeadItemNULL();
    Test3ListPopHeadWorking();
    Test4ListPopHeadSizeDecrease();

    Test1ListPopTailListNULL();
    Test2ListPopTailItemNULL();
    Test3ListPopTailWorking();
    Test4ListPopTailSizeDecrease();

    Test1ListSizeOK();

     /*..........................*/

    printf(".......ITR TEST.......\n");
    Test1ListItrBeginListNULL();
    Test2ListItrBeginWorking();
    Test1ListItrEndListNULL();
    Test2ListItrEndWorking();
    Test1ListItrEqualsTrue();
    Test2ListItrEqualsFalse();
    Test1ListItrNextItrNULL();
    Test2ListItrNextWorking();
    Test1ListItrPrevItrNULL();
    Test2ListItrPrevWorking();
    Test1ListItrGetItrNULL();
    Test1ListItrSetItrNULL();
    Test2ListItrSetElementNULL();
    Test1ListItrInsertBeforeItrNULL();
    Test2ListItrInsertBeforeElementNULL();
    Test1ListItrRemoveItrNULL();


    return 0;  
}
/*.........................................*/
static void Test1ListCreateHeadPrev()
{
    List *pList = ListCreate();
    void* head = GetHead(pList);
	if(GetHeadPrev(pList) == head)
	{
		printf("Test1ListCreate  **PASS**\n");
	}
	else
	{
		printf("Test1ListCreate **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test2ListCreateTailNext()
{
    List *pList = ListCreate();
    void* tail = GetTail(pList);
	if(GetTailNext(pList) == tail)
	{
		printf("Test2ListCreateTailNext  **PASS**\n");
	}
	else
	{
		printf("Test2ListCreateTailNext **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test3ListCreateHeadNext()
{
    List *ptrList = ListCreate();
	void* head = GetHeadNext(ptrList);
	if(GetTail(ptrList) == head)
	{
		printf("List3CreateHeadNext *PASS*\n");
	}
	else
	{
		printf("List3CreateHeadNext *FAIL*\n");
	}
	ListDestroy(&ptrList, NULL);
}
/*.........................................*/
static void Test4ListCreateTailPrev()
{
	List *ptrList = ListCreate();
	void* tail = GetTailPrev(ptrList);
	if(GetHead(ptrList) == tail)
	{
		printf("List4CreateTailPrev *PASS*\n");
	}
	else
	{
		printf("List4CreateTailPrev *FAIL*\n");
	}
	ListDestroy(&ptrList, NULL);
	printf("\n");
}
/*.........................................*/
static void Test1ListDestroyWorking()
{
    List *pList = ListCreate();
    ListDestroy(&pList,NULL);
    if(NULL == pList)
    {
        printf("Test1ListDestroyWorking  **PASS**\n");
    }
    else
    {
		printf("Test1ListDestroyWorking **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListDestroyDoubleFree()
{
    List *pList = ListCreate();
    ListDestroy(&pList,NULL);
    ListDestroy(&pList,NULL);
    printf("Test2ListDestroyDoubleFree  **PASS**\n");
}
/*.........................................*/
static void Test1ListPushHeadListNULL()
{
    void* item;
	if(ListPushHead(NULL, item) == LIST_UNINITIALIZED_ERROR)
	{
		printf("Test1ListPushHeadListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListPushHeadListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListPushHeadItemNULL()
{
    List *pList = ListCreate();
	if(ListPushHead(pList, NULL) == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test2ListPushHeadItemNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListPushHeadItemNULL **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test3ListPushHeadSizeIncrease()
{
    List *pList = ListCreate();
    size_t size1,size2;
    int item1 = 3;
    int item2 = 4;
    size1 = ListSize(pList);
    ListPushHead(pList,&item1);
    ListPushHead(pList,&item2);
    size2 = ListSize(pList);

    if (size2 == 2 && size1 == 0)
	{
		printf("Test3ListPushHeadSizeIncrease  **PASS**\n");
	}
	else
	{
		printf("Test3ListPushHeadSizeIncrease **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test4ListPushHeadWorking()
{
    List *pList = ListCreate();
    int item = 3;
    if (ListPushHead(pList,&item) == LIST_SUCCESS)
	{
		printf("Test4ListPushHeadWorking  **PASS**\n");
	}
	else
	{
		printf("Test4ListPushHeadWorking **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListPushTailListNULL()
{
    void* item;
	if(ListPushTail(NULL, item) == LIST_UNINITIALIZED_ERROR)
	{
		printf("Test1ListPushTailListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListPushTailListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListPushTailItemNULL()
{
    List *pList = ListCreate();
	if(ListPushTail(pList, NULL) == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test2ListPushTailItemNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListPushTailItemNULL **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test3ListPushTailSizeIncrease()
{
    List *pList = ListCreate();
    size_t size1,size2;
    int item1 = 3;
    int item2 = 4;
    size1 = ListSize(pList);
    ListPushTail(pList,&item1);
    ListPushTail(pList,&item2);
    size2 = ListSize(pList);
    if (size2 == 2 && size1 ==0)
	{
		printf("Test3ListPushTailSizeIncrease  **PASS**\n");
	}
	else
	{
		printf("Test3ListPushTailSizeIncrease **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test4ListPushTailWorking()
{
    List *pList = ListCreate();
    int item = 3;
    if (ListPushTail(pList,&item) == LIST_SUCCESS)
	{
		printf("Test4ListPushTailWorking  **PASS**\n");
	}
	else
	{
		printf("Test4ListPushTailWorking **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListPopHeadListNULL()
{
    void** item;
	if(ListPopHead(NULL, item) == LIST_UNINITIALIZED_ERROR)
	{
		printf("Test1ListPopHeadListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListPopHeadListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListPopHeadItemNULL()
{
    List *pList = ListCreate();
	if(ListPopHead(pList, NULL) == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test2ListPopHeadItemNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListPopHeadItemNULL **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test3ListPopHeadWorking()
{
    List *pList = ListCreate();
    int item1 = 3;
    int item2 = 8;
    void* value;
    ListPushTail(pList, &item1);
    ListPushTail(pList, &item2);
    if (ListPopHead(pList,&value) == LIST_SUCCESS)
	{
		printf("Test3ListPopHeadWorking  **PASS**\n");
	}
	else
	{
		printf("Test3ListPopHeadWorking **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test4ListPopHeadSizeDecrease()
{
    List *pList = ListCreate();
    size_t size1,size2;
    int item1 = 3;
    int item2 = 4;
    int item3 = 5;
    void* value;
    ListPushHead(pList,&item1);
    ListPushHead(pList,&item2);
    ListPushHead(pList,&item3);
    size1 = ListSize(pList);
    ListPopHead(pList,&value);
    size2 = ListSize(pList);

    if (size1 == 3 && size2 == 2)
	{
		printf("Test4ListPopHeadSizeDecrease  **PASS**\n");
	}
	else
	{
		printf("Test4ListPopHeadSizeIncrease **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListPopTailListNULL()
{
    void** item;
	if(ListPopTail(NULL, item) == LIST_UNINITIALIZED_ERROR)
	{
		printf("Test1ListPopTailListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListPopTailListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListPopTailItemNULL()
{
    List *pList = ListCreate();
	if(ListPopTail(pList, NULL) == LIST_NULL_ELEMENT_ERROR)
	{
		printf("Test2ListPopTailItemNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListPopTailItemNULL **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test3ListPopTailWorking()
{
    List *pList = ListCreate();
    int item1 = 3;
    int item2 = 8;
    void* value;
    ListPushTail(pList, &item1);
    ListPushTail(pList, &item2);
    if (ListPopTail(pList,&value) == LIST_SUCCESS)
	{
		printf("Test3ListPopTailWorking  **PASS**\n");
	}
	else
	{
		printf("Test3ListPopTailWorking **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
}
/*.........................................*/
static void Test4ListPopTailSizeDecrease()
{
    List *pList = ListCreate();
    size_t size1,size2;
    int item1 = 3;
    int item2 = 4;
    int item3 = 5;
    void* value;
    ListPushHead(pList,&item1);
    ListPushHead(pList,&item2);
    ListPushHead(pList,&item3);
    size1 = ListSize(pList);
    ListPopTail(pList,&value);
    size2 = ListSize(pList);

    if (size1 == 3 && size2 == 2)
	{
		printf("Test4ListPopTailSizeDecrease  **PASS**\n");
	}
	else
	{
		printf("Test4ListPopTailSizeDecrease **FAIL**\n");
    }
    ListDestroy(&pList,NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListSizeOK()
{
    size_t size1, size2;
    int item1 = 3;
    int item2 = 8;
    int item3 = 9;
    void* value;
    List *ptrList = ListCreate();
    size1 = ListSize(ptrList);
    ListPushTail(ptrList, &item1);
    ListPushTail(ptrList, &item2);
    ListPushTail(ptrList, &item3);
    size2 = ListSize(ptrList);
	if(size1 == 0 && size2 == 3)
	{
		printf("Test3ListPushTail OK  **PASS**\n");
	}
	else
	{
		printf("Test3ListPushTail OK **FAIL**\n");
	}
	ListDestroy(&ptrList, NULL);
    printf("\n");
}
/*.........................................*/
/*..................ITR....................*/
/*.........................................*/
static void Test1ListItrBeginListNULL()
{
	if(NULL == ListItrBegin(NULL))
	{
		printf("Test1ListItrBeginListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrBeginListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrBeginWorking()
{
	List *pList = ListCreate();
    Node* headNext = GetHeadNext(pList);
    if(ListItrBegin(pList) == headNext)
	{
		printf("Test2ListItrBeginWorking  **PASS**\n");
	}
	else
	{
		printf("Test2ListItrBeginWorking **FAIL**\n");
    }
    ListDestroy(&pList, NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListItrEndListNULL()
{
	if(ListItrEnd(NULL) == NULL)
	{
		printf("Test1ListItrEndListNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrEndListNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrEndWorking()
{
	List *pList = ListCreate();
    Node* tailPrev = GetTailPrev(pList);
    if(ListItrEnd(pList) == tailPrev)
	{
		printf("Test2ListItrEndWorking  **PASS**\n");
	}
	else
	{
		printf("Test2ListItrEndWorking **FAIL**\n");
    }
    ListDestroy(&pList, NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListItrEqualsTrue()
{
    List *pList = ListCreate();
    int a = 3;
    void *value1 = &a;
    void *value2 = &a;

    if(ListItrEquals(value1, value2) == TRUE)
	{
		printf("Test1ListItrEqualsTrue  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrEqualsTrue **FAIL**\n");
    }
    ListDestroy(&pList, NULL);
}
/*.........................................*/
static void Test2ListItrEqualsFalse()
{
    List *pList = ListCreate();
    int a = 3, b = 5;
    void *value1 = &a;
    void *value2 = &b;;
    
    if(ListItrEquals(value1, value2) == FALSE)
	{
		printf("Test2ListItrEqualsFalse  **PASS**\n");
	}
	else
	{
		printf("Test2ListItrEqualsFalse **FAIL**\n");
    }
    ListDestroy(&pList, NULL);
    printf("\n");    
}
/*.........................................*/
static void Test1ListItrNextItrNULL()
{
    if(ListItrNext(NULL) == NULL)
	{
		printf("Test1ListItrNextItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrNextItrNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrNextWorking()
{
    /*??????????????????*/
    List *pList = ListCreate();
    int item1 = 3, item2 = 8, item3 = 9;
    void* dataPulled = NULL;
    ListPushHead(pList, &item1); 
    ListPushHead(pList, &item2); 
    ListPushHead(pList, &item3);    
    dataPulled = ListItrEnd(pList); 
    if(GetTailNext(pList) == ListItrNext(dataPulled))
    {
		printf("Test2ListItrNextWorking **PASS**\n");
	}
	else
	{
		printf("Test2ListItrNextWorking  **FAIL**\n");
	}
	ListDestroy(&pList, NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListItrPrevItrNULL()
{
    if(ListItrPrev(NULL) == NULL)
	{
		printf("Test1ListItrPrevItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrPrevItrNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrPrevWorking()
{
    /*??????????????????*/
    List *pList = ListCreate();
    int item1 = 3, item2 = 8, item3 = 9;
    void* dataPulled = NULL;
    ListPushHead(pList, &item1); 
    ListPushHead(pList, &item2); 
    ListPushHead(pList, &item3);    
    dataPulled = ListItrBegin(pList); 

    if(GetTailNext(pList) == ListItrPrev(dataPulled))
    {
		printf("Test2ListItrPrevWorking **PASS**\n");
	}
	else
	{
		printf("Test2ListItrPrevWorking  **FAIL**\n");
	}
	ListDestroy(&pList, NULL);
    printf("\n");
}
/*.........................................*/
static void Test1ListItrGetItrNULL()
{
    if(ListItrGet(NULL) == NULL)
	{
		printf("Test1ListItrGetItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrGetItrNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test1ListItrSetItrNULL()
{
    void* _element;
    if(ListItrSet(NULL,_element) == NULL)
	{
		printf("Test1ListItrSetItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrSetItrNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrSetElementNULL()
{
    ListItr itr;
    if(ListItrSet(itr,NULL) == NULL)
	{
		printf("Test2ListItrSetElementNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListItrSetElementNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test1ListItrInsertBeforeItrNULL()
{
    void* _element;
    if(ListItrInsertBefore(NULL,_element) == NULL)
	{
		printf("Test1ListItrInsertBeforeItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrInsertBeforeItrNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test2ListItrInsertBeforeElementNULL()
{
    ListItr itr;
    if(ListItrInsertBefore(itr,NULL) == NULL)
	{
		printf("Test2ListItrInsertBeforeElementNULL  **PASS**\n");
	}
	else
	{
		printf("Test2ListItrInsertBeforeElementNULL **FAIL**\n");
    }
}
/*.........................................*/
static void Test1ListItrRemoveItrNULL()
{
    if(ListItrRemove(NULL) == NULL)
	{
		printf("Test1ListItrRemoveItrNULL  **PASS**\n");
	}
	else
	{
		printf("Test1ListItrRemoveItrNULL **FAIL**\n");
    }
}
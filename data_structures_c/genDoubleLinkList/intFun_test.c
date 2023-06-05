#include <stdio.h>
#include <stdlib.h>
#include "list_functions.h"
#include "listInternal.h"


int PredicateForInt(void * _element, void* _context)
{
    if(*(int *)_element == *(int *)_context)
    {
        return 1;
    }
    return 0;
}
/*..............................*/
int ActionFuncForInt(void* _element, void* _context)
{
    if(_element == 0)
    {
        return 0;
    }
    printf("%d ", *(int*)_element);
    return 1;
}
/*...............................*/
void DelateNode(void* _element)
{
    free(_element);
}
/*..............................*/

static void Test1_ListItrFindFirst_beginNULL();
static void Test2_ListItrFindFirst_endNULL();
static void Test3_ListItrFindFirst_PredFunNULL();
static void Test4_ListItrFindFirst_Working();

static void Test1_ListItrCountIf_beginNULL();
static void Test2_ListItrCountIf_endNULL();
static void Test3_ListItrCountIf_predFuncNULL();
static void Test4_ListItrCountIf_Working();

static void Test1_ListItrForEach_beginNULL();
static void Test2_ListItrForEach_endNULL();
static void Test3_ListItrForEach_actFuncNULL();
static void Test4_ListItrForEach_Working();

int main()
{
    Test1_ListItrFindFirst_beginNULL();
    Test2_ListItrFindFirst_endNULL();
    Test3_ListItrFindFirst_PredFunNULL();
    Test4_ListItrFindFirst_Working();

    Test1_ListItrCountIf_beginNULL();
    Test2_ListItrCountIf_endNULL();
    Test3_ListItrCountIf_predFuncNULL();
    Test4_ListItrCountIf_Working();

    Test1_ListItrForEach_beginNULL();
    Test2_ListItrForEach_endNULL();
    Test3_ListItrForEach_actFuncNULL();
    Test4_ListItrForEach_Working();


    return 0;
}

/*........................................*/
/*.................TESTS..................*/
/*........................................*/

static void Test1_ListItrFindFirst_beginNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrFindFirst(NULL, ListItrEnd(pList), PredicateForInt, NULL))
    {
        printf("Test1_ListItrFindFirst_beginNULL   **PASS**\n");
    }
    else
    {
        printf("Test1_ListItrFindFirst_beginNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test2_ListItrFindFirst_endNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrFindFirst(ListItrBegin(pList), NULL, PredicateForInt, NULL))
    {
        printf("Test2_ListItrFindFirst_endNULL   **PASS**\n");
    }
    else
    {
        printf("Test2_ListItrFindFirst_endNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test3_ListItrFindFirst_PredFunNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrFindFirst(ListItrBegin(pList), ListItrEnd(pList), NULL, NULL))
    {
        printf("Test3_ListItrFindFirst_PredFunNULL   **PASS**\n");
    }
    else
    {
        printf("Test3_ListItrFindFirst_PredFunNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
/*...................................................*/
static void Test4_ListItrFindFirst_Working()
{
    List* pList = ListCreate();
    int *a, *b;
    void* result;
    int item = 10;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    result = ListItrFindFirst(ListItrBegin(pList), ListItrEnd(pList), PredicateForInt, &item);
    if(*(int*)ListItrGet(result) == item)
    {
        printf("Test4_ListItrFindFirst_Working   **PASS**\n");
    }
    else
    {
        printf("Test4_ListItrFindFirst_Working   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
    printf("\n");
}
/*...................................................*/
static void Test1_ListItrCountIf_beginNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(0 == ListItrCountIf(NULL, ListItrEnd(pList), PredicateForInt, NULL))
    {
        printf("Test1_ListItrCountIf_beginNULL   **PASS**\n");
    }
    else
    {
        printf("Test1_ListItrCountIf_beginNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test2_ListItrCountIf_endNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(0 == ListItrCountIf(ListItrBegin(pList), NULL, PredicateForInt, NULL))
    {
        printf("Test2_ListItrCountIf_endNULL   **PASS**\n");
    }
    else
    {
        printf("Test2_ListItrCountIf_endNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test3_ListItrCountIf_predFuncNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(0 == ListItrCountIf(ListItrBegin(pList), ListItrEnd(pList), NULL, NULL))
    {
        printf("Test3_ListItrCountIf_predFuncNULL   **PASS**\n");
    }
    else
    {
        printf("Test3_ListItrCountIf_predFuncNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test4_ListItrCountIf_Working()
{
    List* pList = ListCreate();
    int *a, *b, *c, *d;
    size_t result;
    int item = 5;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    c = (int*)malloc(sizeof(int) * 1);
    *c = 5;
    d = (int*)malloc(sizeof(int) * 1);
    *d = 3; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    ListPushTail(pList, c);
    ListPushTail(pList, d);

    result = ListItrCountIf(ListItrBegin(pList), ListItrEnd(pList), PredicateForInt, &item);
    if(result == 2)
    {
        printf("Test4_ListItrCountIf_Working   **PASS**\n");
    }
    else
    {
        printf("Test4_ListItrCountIf_Working   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
    printf("\n");
}
/*...................................................*/
static void Test1_ListItrForEach_beginNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrForEach(NULL, ListItrEnd(pList), ActionFuncForInt, NULL))
    {
        printf("Test1_ListItrForEach_beginNULL   **PASS**\n");
    }
    else
    {
        printf("Test1_ListItrForEach_beginNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test2_ListItrForEach_endNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrForEach(ListItrBegin(pList), NULL, ActionFuncForInt, NULL))
    {
        printf("Test2_ListItrForEach_endNULL   **PASS**\n");
    }
    else
    {
        printf("Test2_ListItrForEach_endNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test3_ListItrForEach_actFuncNULL()
{
    List* pList = ListCreate();
    int *a, *b;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    if(NULL == ListItrForEach(ListItrBegin(pList), ListItrEnd(pList), NULL, NULL))
    {
        printf("Test3_ListItrForEach_actFuncNULL   **PASS**\n");
    }
    else
    {
        printf("Test3_ListItrForEach_actFuncNULL   **FAIL**\n");
    }
    ListDestroy(&pList,DelateNode);
}
/*...................................................*/
static void Test4_ListItrForEach_Working()
{
    List* pList = ListCreate();
    int *a, *b, *c;
    a = (int*)malloc(sizeof(int) * 1);
    *a = 5;
    b = (int*)malloc(sizeof(int) * 1);
    *b = 10; 
    c = (int*)malloc(sizeof(int) * 1);
    *c = 7; 
    ListPushTail(pList, a);
    ListPushTail(pList, b);
    ListPushTail(pList, c);
    ListItrForEach(ListItrBegin(pList), ListItrEnd(pList), ActionFuncForInt, NULL);
    printf("\n");
    printf("Test4_ListItrForEach_Working   **PASS**\n");
    ListDestroy(&pList,DelateNode);
}

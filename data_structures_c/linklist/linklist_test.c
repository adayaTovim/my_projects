#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>  /* size_t */
#include "linklist.h" 
#define SIZE 5

Person PersonArr[4] = {{100,"Adaya",30, NULL},{150,"Ben",31, NULL},{200,"Ariel",2,NULL},{250,"Yahel",1,NULL}};

void RestartArray();

void Test_1_ListInsertHead_IfPNULL();
void Test_2_ListInsertHead_OK();
void Test_1_ListRemoveHead_ItemNULL();
void Test_2_ListRemoveHead_HeadNULL();
void Test_3_ListRemoveHead_OK();
void Test_1_ListInsertByKey_PNULL();
void Test_2_ListInsertByKey_headNULL();
void Test_3_ListInsertByKey_KeySmallThenid();
void Test_4_ListInsertByKey_duplicate();
void Test_5_ListInsertByKeyOK_();
void Test_1_ListRemoveByKey_pNULL();
void Test_2_ListRemoveByKey_headNULL();
void Test_1_GetTheLastNodeRec_OK();
void Test_1_GetTheOlder_OK();

int main()
{
	/*printf("%d\n", PersonArr[0].m_id);
	printf("%s\n", PersonArr[0].m_name);
	printf("%d\n", PersonArr[0].m_age);
	printf("%d\n", PersonArr[1].m_id);
	printf("%s\n", PersonArr[1].m_name);
	printf("%d\n", PersonArr[1].m_age);
	printf("%d\n", PersonArr[2].m_id);
	printf("%s\n", PersonArr[2].m_name);
	printf("%d\n", PersonArr[2].m_age);
	printf("%d\n", PersonArr[3].m_id);
	printf("%s\n", PersonArr[3].m_name);   */
	


	/******************TESTS*********************/
	printf("Tests:/n");
	Test_1_ListInsertHead_IfPNULL();
	Test_2_ListInsertHead_OK();
	Test_1_ListRemoveHead_ItemNULL();
	Test_2_ListRemoveHead_HeadNULL();
	Test_3_ListRemoveHead_OK();
	Test_1_ListInsertByKey_PNULL();
	Test_2_ListInsertByKey_headNULL();
	Test_3_ListInsertByKey_KeySmallThenid();         
	Test_4_ListInsertByKey_duplicate();
	/*Test_5_ListInsertByKeyOK_();*/
	Test_1_ListRemoveByKey_pNULL();
	Test_2_ListRemoveByKey_headNULL();
	Test_1_GetTheLastNodeRec_OK();
	Test_1_GetTheOlder_OK();
	
return;
}

void RestartArray()
{
	int i;
	for(i = 0; i < SIZE; ++i)
	{
		PersonArr[i].m_next = NULL;
	}
}
/**************************************************/
void Test_1_ListInsertHead_IfPNULL()
{
	if(ListInsertHead(&PersonArr[0], NULL) == &PersonArr[0])
	{
		printf("Test_1_ListInsertHead -p NULL- pass\n");
	}
	else 
	{
		printf("Test_1_ListInsertHead -p NULL- fail\n");
	}
	RestartArray();
}
/*************************************************/
void Test_2_ListInsertHead_OK()
{
	
	if(ListInsertHead(&PersonArr[0], &PersonArr[2]) == &PersonArr[2])
	{
		printf("Test_2_List Insert Head - Ok- pass\n");
	}
	else 
	{
		printf("Test_1_List Insert Head - OK- fail\n");
	}
	RestartArray();
}
/*************************************************/
void Test_1_ListRemoveHead_ItemNULL()
{
	if(ListRemoveHead(&PersonArr[0], NULL) == &PersonArr[0])
	{
		printf("Test_1_List Remove Head - NULL- pass\n");
	}
	else 
	{
		printf("Test_1_List Remove Head - NULL- fail\n");
	}
	RestartArray();
}
/****************************************************/
void Test_2_ListRemoveHead_HeadNULL()
{
	Person* item;
	ListRemoveHead(NULL,&item);
	if(item == NULL)
	{
		printf("Test_2_List Remove Head - head NULL- pass\n");
	}
	else 
	{
		printf("Test_1_List Remove Head - head NULL- fail\n");
	}
	RestartArray();
}
/*************************************************/
void Test_3_ListRemoveHead_OK()
{
	Person* _item;
	Person* temp = &PersonArr[1] ;
	ListRemoveHead(&PersonArr[1],&_item);
	if(_item == temp)
	{
		printf("Test_3_List Remove Head - OK- pass\n");
	}
	else 
	{
		printf("Test_1_List Remove Head - OK- fail\n");
	}
	RestartArray();
}
/***************************************************/
void Test_1_ListInsertByKey_PNULL()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	if(ListInsertByKey(&PersonArr[0], 150, NULL ) == &PersonArr[0])
	{
		printf("Test_1_List Insert By Key_P NULL- pass\n");
	}
	else 
	{
		printf("Test_1_List Insert By Key_P NULL- fail\n");
	}
	RestartArray();
}
/******************************************************/
void Test_2_ListInsertByKey_headNULL()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	if(ListInsertByKey(NULL, 150, &PersonArr[2] ) == &PersonArr[2])
	{
		printf("Test_2_List Insert By Key_head NULL- pass\n");
	}
	else 
	{
		printf("Test_2_List Insert By Key_head NULL- fail\n");
	}
	RestartArray();
}
/***********************************************************/
void Test_3_ListInsertByKey_KeySmallThenid()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	if(ListInsertByKey(&PersonArr[0], 10, &PersonArr[2] ) == &PersonArr[2])
	{
		printf("Test_3_List Insert By Key_key<id- pass\n");
	}
	else 
	{
		printf("Test_2_List Insert By Key_key<id- fail\n");
	}
	RestartArray();
}
/************************************************************/
void Test_4_ListInsertByKey_duplicate()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	/*PrintList(&PersonArr[0]);*/
	
	if(ListInsertByKey(&PersonArr[0], 200, &PersonArr[2]) == &PersonArr[0])
	{
		printf("Test_4_List Insert By Key_OK- pass\n");
	}
	else 
	{
		printf("Test_4_List Insert By Key_OK- fail\n");
	}
	RestartArray();
} 
/************************************************************/
/*
void Test_5_ListInsertByKeyOK_()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	PrintList(&PersonArr[0]);
	
	ListInsertByKey(&PersonArr[0], 120 , &PersonArr[1]);
	if(PersonArr[1] == 120)
	{
		printf("Test_5_List Insert By Key OK- pass\n");
	}
	else 
	{
		printf("Test_5_List Insert By Key OK- fail\n");
	}
	RestartArray();
}
*/
/*************************************************************/
void Test_1_ListRemoveByKey_pNULL()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	if(ListRemoveByKey(&PersonArr[0], 150, NULL ) == &PersonArr[0])
	{
		printf("Test_1_List Remove By Key_P NULL- pass\n");
	}
	else 
	{
		printf("Test_1_List Remove By Key_P NULL- fail\n");
	}
	RestartArray();
}
/****************************************************/
void Test_2_ListRemoveByKey_headNULL()
{
	Person* item;
	
	if(ListRemoveByKey(NULL, 140, &item ) == NULL)
	{
		printf("Test_2_List Remove By Key_head NULL- pass\n");
	}
	else 
	{
		printf("Test_2_List Remove By Key_head NULL- fail\n");
	}
	RestartArray();
}

/****************************************************/
/****************************************************/
void Test_1_GetTheLastNodeRec_OK()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	
	if(GetTheLastNodeRec(&PersonArr[0]) == &PersonArr[3])
	{
		printf("Test_1_GetTheLastNodeRec ok- pass\n");
	}
	else 
	{
		printf("Test_1_GetTheLastNodeRec ok- fail\n");
	}
	RestartArray();
}
/**************************************************/
void Test_1_GetTheOlder_OK()
{
	PersonArr[0].m_next = &PersonArr[1];
	PersonArr[1].m_next = &PersonArr[2];
	PersonArr[2].m_next = &PersonArr[3];
	
	if(GetTheOlder(&PersonArr[0]) == &PersonArr[1])
	{
		printf("Test_1_GetTheOlder ok- pass\n");
	}
	else 
	{
		printf("Test_1_GetTheOlder ok- fail\n");
	}
	RestartArray();
}

#include <stdio.h>
#define __STACK_H__
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */


typedef struct Person Person;

struct Person
{

	int m_id; /* Primary Key */

	char m_name[128];

	int m_age;

	Person* m_next;

};
/****************************************************/

Person* ListInsertHead(Person* _head ,Person* _p);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* ListRemoveHead(Person* _head, Person** _item);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* ListInsertByKey(Person* _head, int _key, Person* _p);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* ListInsertByKeyRec(Person* _head, int _key, Person* _p);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* ListRemoveByKey(Person* _head, int _key, Person* *_p);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* ListRemoveByKeyRec(Person* _head, int _key, Person**_p);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
void PrintList(Person* _head);
/*
Description: 
Arguments: 
Return: 
Error: 
*/
Person* GetTheLastNodeRec(Person* _head);
Person* GetTheOlder(Person* _head);

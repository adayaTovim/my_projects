#ifndef __DOUBLELINKLIST_H__
#define __DOUBLELINKLIST_H__
#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */

typedef struct Node Node;
typedef struct List List;


List* ListCreate(void);

void ListDestroy(List* _list);

ADTErr ListPushHead(List* _list, int _data);

ADTErr ListPushTail(List* _list, int _data);

ADTErr ListPopHead(List* _list, int* _data);

ADTErr ListPopTail(List* _list, int* _data);

size_t ListCountItems(List* _list);

int ListIsEmpty(List* _list);

/* ListPrint is only for debug */

void ListPrint(List* _list);

#endif

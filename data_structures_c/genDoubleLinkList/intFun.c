#include "list_functions.h"
#include "listInternal.h"
#include <stdio.h> /*printf*/
#include <stddef.h> /*size_t*/
#include <stdlib.h> /*malloc*/

typedef int (*GenFunction)(void* _element, void* _context);
typedef int (*InnerFunction)(int _data, void* _context);

static ListItr InternalForEach(ListItr _begin, ListItr _end, GenFunction _genericFunc, void* _context, InnerFunction _InnerFunc, void* _innerCounter);
static int InnerFindFirst(int result, void* _innerCounter);
static int InnerCountIf(int result, void* _innerCounter);
static int InnerForEach(int result, void* _innerCounter);


/*........................API......................*/
ListItr ListItrFindFirst(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    if(NULL == _begin || NULL == _end || NULL == _predicate)
    {
        return NULL;
    }
    return InternalForEach(_begin, _end, _predicate, _context, InnerFindFirst , NULL);
}
/*......................................*/
size_t ListItrCountIf(ListItr _begin, ListItr _end, PredicateFunction _predicate, void* _context)
{
    size_t counter = 0;
    if(NULL == _begin || NULL == _end || NULL == _predicate)
    {
        return 0;
    }
    InternalForEach(_begin, _end, _predicate, _context, InnerCountIf, &counter);
    return counter;
}
/*.....................................*/
ListItr ListItrForEach(ListItr _begin, ListItr _end, ListActionFunction _action, void* _context)
{
    if(NULL == _begin || NULL == _end || NULL == _action)
    {
        return NULL;
    }
    return InternalForEach(_begin, _end, _action, _context, InnerForEach, NULL);
}
/*.....................................*/




/*..............HELP FUNC...............*/
static ListItr InternalForEach(ListItr _begin, ListItr _end, GenFunction _genericFunc, void* _context,
                               InnerFunction _innerFunc, void* _innerCounter)
{
	int result;
    void* data;
    while(_begin != _end)
	{
		data = ListItrGet(_begin);
		result = _genericFunc(data,_context);
        /*we can write also like this : 
          result *(_genericFunc)(data,_context); 
          in this way we can see that is a pointer to function*/
		result = _innerFunc(result, _innerCounter);
		if (result == 0)
		{
			break;
		}
		_begin = ListItrNext(_begin);
	}
	return _begin;
}
/*..................................*/
static int InnerFindFirst(int result, void* _innerCounter)
{
    if(result == 1)
    {
      return 0;  
    }
    return 1;
}
/*...................................*/
static int InnerCountIf(int result, void* _innerCounter)
{
    if(result == 1)
    {
        ++(*(size_t *)_innerCounter);
    }
    return 1;
}
/*...................................*/
static int InnerForEach(int result, void* _innerCounter)
{
    if(result == 0)
    {
        return 0;
    }
    return 1;
}
/*...................................*/



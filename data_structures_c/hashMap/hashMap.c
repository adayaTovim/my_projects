#include <stdlib.h>
#include <math.h>
#include "hashMap.h"
#include "listItr.h" 
#include "list_functions.h" 
#include "genList.h" 

#define TRUE 1
#define FALSE 0

struct HashMap
{
    List** m_data;                              
    HashFunction m_hashFunction;
    EqualityFunction m_equalityFunction;
    size_t m_capacity;                      /*size of the array m_data*/                   
    size_t m_numOfItems;                 
};

typedef struct Member{

    void* m_key;
    void* m_value;
}Member;

typedef struct KeyAndFunc{

    void* m_key;
    EqualityFunction m_equalityFunction;
}KeyAndFunc;

typedef struct CounterAndAct{

    size_t m_counter;
    KeyValueActionFunction m_action;
    void* m_context;
}CounterAndAct;

typedef struct DestroyFuncs{

    KeyDestroy m_keyDestroy;
    ValDestroy m_valueDestroy;
}DestroyFuncs;

static int IsPrime(size_t _num);
static int IsFound(List* _list, void* _key, EqualityFunction _equalityFunc, ListItr* _itrToRemove);
static Member* CreateMember(const void* _key, const void* _value);
static int IsFoundFunc (void* _element, void* _keyAndFunc);
static int ActionForEach(void* _element, void* _context);
static void ElementDestroy(void* _item);
static Map_Result InsertFirstMember(List** _list, Member* _member);
static int DestroyMemberKey(void* _element, void* _context);
static int DestroyMemberValue(void* _element, void* _context);
static int DestroyMemberFull(void* _element, void* _context);


HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
    HashMap* hash;
    if (NULL == _hashFunc || NULL == _keysEqualFunc || _capacity < MIN_SIZE)
    {
        return NULL;
    }
    hash = (HashMap*)malloc(sizeof(HashMap) * 1);
    if (NULL == hash)
    {
        return NULL;
    }
    while (!IsPrime(_capacity))
    {
        _capacity++;
    }
    hash->m_data = (List**)calloc(_capacity, sizeof(List*));
    if(NULL == hash->m_data)
    {
        free(hash);
        return NULL;
    }
    hash->m_capacity = _capacity;
    hash->m_numOfItems = 0;
    hash->m_hashFunction = _hashFunc;
    hash->m_equalityFunction = _keysEqualFunc; 
    return hash;
}

void HashMap_Destroy(HashMap** _map, KeyDestroy _keyDestroy, ValDestroy _valDestroy)
{
    size_t  i = 0;
    size_t size;
    DestroyFuncs destroyFuncs;
    PredicateFunction destroy;
    if(NULL == _map || NULL == *_map)
    {
        return;
    }
    size = (*_map)->m_capacity;
    if ((NULL != _keyDestroy || NULL != _valDestroy) && (*_map)->m_numOfItems != 0)
    {
        destroyFuncs.m_keyDestroy = _keyDestroy;
        destroyFuncs.m_valueDestroy = _valDestroy;
        if (_keyDestroy != NULL)
        {
            if (_valDestroy == NULL)
            {
                destroy = DestroyMemberKey;
            }
            else {
                destroy = DestroyMemberFull;
            }
        }
        else {
            destroy = DestroyMemberValue;
        }
        if (NULL == _keyDestroy && NULL == _valDestroy)
        {
            for (i = 0; i < size; ++i)
            {
                ListItrForEach(ListItrBegin((*_map)->m_data[i]), ListItrEnd((*_map)->m_data[i]), destroy, &destroyFuncs);
            }
        }
    }
    for (i = 0; i < size; ++i)
    {
        ListDestroy(&(*_map)->m_data[i], ElementDestroy);
    }
    free((*_map)->m_data);
    free(*_map);
    *_map = NULL;
}

Map_Result HashMap_Insert(HashMap* _map, const void* _key, const void* _value)
{
    size_t i;
    Member* member;
    ListResult listResult;
    if (NULL == _map || NULL == _key)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    i = _map->m_hashFunction((void*)_key) % _map->m_capacity;
    member = CreateMember(_key, _value); /*could be inserted into creation auxilairy funcs*/
    if (NULL == member)
    {
        return MAP_ALLOCATION_ERROR;
    }
    if (_map->m_data[i] == NULL)
    {
        listResult = InsertFirstMember(&_map->m_data[i], member);
        if (listResult == MAP_ALLOCATION_ERROR)
        {
            free(member);
            return MAP_ALLOCATION_ERROR;
        }
    }
    else if (IsFound(_map->m_data[i], (void*)_key, _map->m_equalityFunction, NULL) == TRUE)
    {
        free(member);
        return MAP_KEY_DUPLICATE_ERROR;
    }
    else
    {
        listResult = ListPushHead(_map->m_data[i], member);
        if (listResult != LIST_SUCCESS)
        {
            free(member);
            return MAP_ALLOCATION_ERROR;
        }
    }
    _map->m_numOfItems += 1;
    return MAP_SUCCESS;
}

Map_Result HashMap_Remove(HashMap* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
    size_t i;
    ListItr itrToRemove;
    Member* memberRemoved;
    if (NULL == _map || NULL == _searchKey || _pKey == NULL || _pValue == NULL)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    i = _map->m_hashFunction((void*)_searchKey) % _map->m_capacity;
    if (_map->m_numOfItems == 0 || !IsFound(_map->m_data[i], (void*)_searchKey, _map->m_equalityFunction, &itrToRemove))
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    memberRemoved = (Member*)ListItrRemove(itrToRemove);
    *_pKey = memberRemoved->m_key;
    *_pValue = memberRemoved->m_value;
    free(memberRemoved);
    _map->m_numOfItems -= 1;
    return MAP_SUCCESS;
}

Map_Result HashMap_Find(const HashMap* _map, const void* _key, void** _pValue)
{
    size_t i;
    ListItr itrToFind;
    Member* memberFound;
    if (NULL == _map || NULL == _key || NULL == _pValue)
    {
        return MAP_UNINITIALIZED_ERROR;
    }
    i = _map->m_hashFunction((void*)_key) % _map->m_capacity;
    if (!IsFound(_map->m_data[i], (void*)_key, _map->m_equalityFunction, &itrToFind))
    {
        return MAP_KEY_NOT_FOUND_ERROR;
    }
    memberFound = (Member*)ListItrGet(itrToFind);
    *_pValue = memberFound->m_value;
    return MAP_SUCCESS;
}
size_t HashMap_Size(const HashMap* _map)
{
	if (NULL == _map)
	{
		return 0;
	}
	return _map -> m_numOfItems;
}
size_t HashMap_ForEach(const HashMap* _map, KeyValueActionFunction _action, void* _context)
{
    size_t size;
    int i;
    CounterAndAct counterAndAct; /*and context*/ 
    ListItr itr;
    counterAndAct.m_action = _action;
    counterAndAct.m_counter = 0;
    counterAndAct.m_context = _context;
    if (_map == NULL || _action == NULL || _map->m_numOfItems == 0)
    {
        return 0;
    }
    size = _map->m_capacity;
    for (i = 0; i < size; ++i)
    {
        if (NULL != _map->m_data[i])
        {
            itr = ListItrForEach(ListItrBegin(_map->m_data[i]), ListItrEnd(_map->m_data[i]), ActionForEach, &counterAndAct);
            if (itr != ListItrEnd(_map->m_data[i]))
            {
                break;
            }
        }
        if (counterAndAct.m_counter == _map->m_numOfItems)
        {
            break;
        }
    }
    return counterAndAct.m_counter;
}

static void ElementDestroy(void* _item)
{
    free((Member*)_item);
}

static int DestroyMemberFull(void* _element, void* _context)
{
    ((DestroyFuncs*)_context)->m_keyDestroy(((Member*)_element)->m_key);
    ((DestroyFuncs*)_context)->m_valueDestroy(((Member*)_element)->m_value);
    return TRUE;
}

static int DestroyMemberKey(void* _element, void* _context)
{
    ((DestroyFuncs*)_context)->m_keyDestroy(((Member*)_element)->m_key);
    return TRUE;
}

static int DestroyMemberValue(void* _element, void* _context)
{
    ((DestroyFuncs*)_context)->m_valueDestroy(((Member*)_element)->m_value);
    return TRUE;
}

static int ActionForEach(void* _element, void* _context)
{
    if (((CounterAndAct*)_context)->m_action(((Member*)_element)->m_key, ((Member*)_element)->m_value, ((CounterAndAct*)_context)->m_context))
    {
        ((CounterAndAct*)_context)->m_counter += 1;
    }
    return 1;
}

static int IsPrime(size_t _num)
{
    size_t i;
    if (_num <= 1)
        return FALSE;
    if (_num == 2)
        return TRUE;
    if (_num % 2 == 0)
        return FALSE;
    for (i = 3; i <= _num/2; i += 2)
    {
        if (_num % i == 0)
            return FALSE;
    }
    return TRUE;
}

static Map_Result InsertFirstMember(List** _list, Member* _member)
{
    if (NULL == (*_list = ListCreate()))
    {
        return MAP_ALLOCATION_ERROR;
    }
    if ((ListPushHead(*_list, _member)) != LIST_SUCCESS)
    {
        return MAP_ALLOCATION_ERROR;
    }
    return MAP_SUCCESS;
}

static Member* CreateMember(const void* _key, const void* _value)
{
    Member* member;
    member = (Member*)malloc(sizeof(Member) * 1);
    if (NULL == member)
    {
        return NULL;
    }
    member->m_key = (void*)_key;
    member->m_value = (void*)_value;
    return member;
}

static int IsFound(List* _list, void* _key, EqualityFunction _equalityFunc, ListItr* _itrToRemove)
{
    size_t i;
    ListItr itrFound;
    KeyAndFunc keyAndFunc; 
    keyAndFunc.m_key = _key;
    keyAndFunc.m_equalityFunction = _equalityFunc;
    itrFound = ListItrFindFirst(ListItrBegin(_list), ListItrEnd(_list), IsFoundFunc, &keyAndFunc);
    if (itrFound == ListItrEnd(_list))
    {
        return FALSE;
    }
    if (NULL != _itrToRemove)
    {
        *_itrToRemove = itrFound;
    }
    return TRUE;    
}

static int IsFoundFunc (void* _element, void* _keyAndFunc)
{
    if (((KeyAndFunc*)_keyAndFunc)->m_equalityFunction(((Member*)_element)->m_key, ((KeyAndFunc*)_keyAndFunc)->m_key)) 
    {
        return TRUE;
    }
    return FALSE;
}













































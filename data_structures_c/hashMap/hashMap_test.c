#include <stdio.h>
#include <stdlib.h> /*for freeing*/
#include <stdio.h> /*for printf*/
#include <string.h> /*for str compare*/
#include "hashMap.h"
#define SIZE 10
#define TRUE 1
#define FALSE 0


typedef struct Names{
    
    char** m_name1;
    char** m_name2;
    char** m_name3;
    char** m_name4;
    char** m_name5;
    char** m_name6;
    char** m_name7;
    char** m_name8;
}Names;

typedef struct Keys{
    
    int* m_1;
    int* m_2;
    int* m_3;
    int* m_4;
    int* m_5;
    int* m_6;
    int* m_7;
    int* m_8;
}Keys;

static size_t HashFunc(void* _data);
static int EqualityFunc(void* _firstData, void* _secondData);
static void KeyDestroyFunc(void* _data);
static void ValueDestroyFunc(void* _name);
static int Print(const void* _key, void* _element, void* _context);
static Keys* CreateKeys();
static Names* CreateNames();


void TestCreateHash1();
void TestCreateHash2();
void TestCreateHash3();
void TestCreateHash4();
void TestDeleteHash();
void TestInsert1();
void TestRemove1();
void TestFind1();
void TestForEach1();



int main()
{
   
    TestCreateHash1();
    TestCreateHash2();
    TestCreateHash3();
    TestCreateHash4();
    TestDeleteHash();
    TestInsert1();
    TestRemove1();
    TestFind1();
    TestForEach1();

    return 0;
}


static size_t HashFunc(void* _data)
{
    return (size_t)(*(int*)_data * 2);
}
static int EqualityFunc(void* _firstKey, void* _secondKey)
{
    if (*(int*)_firstKey == *(int*)_secondKey)
    {
        return TRUE;
    }
    return FALSE;
}
static void KeyDestroyFunc(void* _key)
{
    free((int*)_key);
}
static void ValueDestroyFunc(void* _name)
{
    free((char**)_name);
}
static int Print(const void* _key, void* _element, void* _context)
{
    if (*(int*)_key % 2 == 0)
    {
        printf("%s\n", *(char**)_element);
    }
    return 1;
}

void TestCreateHash1()
{
    HashMap* hashMap;
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    if (hashMap != NULL)
    {
        printf("%-40s pass\n", "creating hash");
    }
    else
    {
        printf("%-40s fail\n", "creating hash");
    }
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
}
/*add capacity*/
void TestCreateHash2()
{
    HashMap* hashMap;
    hashMap = HashMap_Create(1, HashFunc, EqualityFunc);
    if (hashMap == NULL)
    {
        printf("%-40s pass\n", "creating hash with less than 2 size");
    }
    else
    {
        printf("%-40s fail\n", "creating hash with less than 2 size");
    }
}

void TestCreateHash3()
{
    HashMap* hashMap;
    hashMap = HashMap_Create(SIZE, NULL, EqualityFunc);
    if (hashMap == NULL)
    {
        printf("%-40s pass\n", "creating hash with NULL for Hashfunc");
    }
    else
    {
        printf("%-40s fail\n", "creating hash with NULL for Hashfunc");
    }
}

void TestCreateHash4()
{
    HashMap* hashMap;
    hashMap = HashMap_Create(SIZE, HashFunc, NULL);
    if (hashMap == NULL)
    {
        printf("%-40s pass\n", "creating hash with NULL for equalityFunc");
    }
    else
    {
        printf("%-40s fail\n", "creating hash with NULL for equalityFunc");
    }
}
/*add tests*/
void TestDeleteHash()
{
    HashMap* hashMap;
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    if (hashMap == NULL)
    {
        printf("%-40s pass\n", "Deleting hash");
    }
    else
    {
        printf("%-40s fail\n", "Deleting hash");
    }
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    printf("%-40s pass\n", "Deleting hash twice");
}

void TestInsert1()
{
    HashMap* hashMap;
    Names* names;
    Keys* keys;
    Map_Result result;
    names = CreateNames();
    if (names == NULL)
    {
        printf("Allocation failed\n");
    }
    keys = CreateKeys();
    if (keys == NULL)
    {
        printf("Allocation failed\n");
    }
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    result = HashMap_Insert(hashMap, keys->m_1, names->m_name1);
    if (result == MAP_SUCCESS)
    {
        printf("%-40s pass\n", "inserting hash");
    }
    else
    {
        printf("%-40s fail\n", "inseting hash");
    }
    result = HashMap_Insert(hashMap, keys->m_2, names->m_name2);
    result = HashMap_Insert(hashMap, keys->m_3, names->m_name3);
    result = HashMap_Insert(hashMap, keys->m_4, names->m_name4);
    if (result == MAP_KEY_DUPLICATE_ERROR)
    {
        printf("%-40s pass\n", "inserting Duplicte hash");
    }
    else
    {
        printf("%-40s fail\n", "inseting Duplicate hash");
    }
    result = HashMap_Insert(hashMap, keys->m_5, names->m_name5);
    result = HashMap_Insert(hashMap, keys->m_6, names->m_name6);
    result = HashMap_Insert(hashMap, keys->m_7, names->m_name7);
    result = HashMap_Insert(hashMap, keys->m_8, names->m_name8);
    if (result == MAP_SUCCESS)
    {
        printf("%-40s pass\n", "inserting collision hash");
    }
    else
    {
        printf("%-40s fail\n", "inseting collision hash");
    }
    result = HashMap_Insert(NULL, keys->m_5, names->m_name5);
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "inserting NULL hash");
    }
    else
    {
        printf("%-40s fail\n", "inseting NULL hash");
    }    
    result = HashMap_Insert(hashMap, NULL, names->m_name5);
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "inserting NULL key");
    }
    else
    {
        printf("%-40s fail\n", "inseting NULL key");
    }  
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    free(keys->m_4);
    free(names->m_name4);
    free(keys);
    free(names);
}

void TestRemove1()
{
    HashMap* hashMap;
    Names* names;
    Keys* keys;
    Map_Result result;
    void* keyRemoved;
    void* valueRemoved;
    names = CreateNames();
    if (names == NULL)
    {
        printf("Allocation failed\n");
    }
    keys = CreateKeys();
    if (keys == NULL)
    {
        printf("Allocation failed\n");
    }
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    result = HashMap_Insert(hashMap, keys->m_1, names->m_name1);
    result = HashMap_Insert(hashMap, keys->m_2, names->m_name2);
    result = HashMap_Insert(hashMap, keys->m_3, names->m_name3);
    result = HashMap_Insert(hashMap, keys->m_4, names->m_name4);
    result = HashMap_Insert(hashMap, keys->m_5, names->m_name5);
    result = HashMap_Insert(hashMap, keys->m_6, names->m_name6);
    result = HashMap_Insert(hashMap, keys->m_7, names->m_name7);
    result = HashMap_Insert(hashMap, keys->m_8, names->m_name8);
    result = HashMap_Remove(hashMap, keys->m_1, &keyRemoved, &valueRemoved);   
    if (result == MAP_SUCCESS && *(int*)keyRemoved == 2 && strcmp(*(char**)valueRemoved, "Jayden") == 0)
    {
        printf("%-40s pass\n", "removing key");
    }
    else
    {
        printf("%-40s fail\n", "removing key");
    }    
    result = HashMap_Remove(hashMap, keys->m_1, &keyRemoved, &valueRemoved);   
    if (result == MAP_KEY_NOT_FOUND_ERROR)
    {
        printf("%-40s pass\n", "removing nonexistent key");
    }
    else
    {
        printf("%-40s fail\n", "nonexistent key");
    }        
    result = HashMap_Remove(hashMap, NULL, &keyRemoved, &valueRemoved);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "removing NULL key");
    }
    else
    {
        printf("%-40s fail\n", "NULL key");
    }
    result = HashMap_Remove(NULL, keys->m_1, &keyRemoved, &valueRemoved);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "removing NULL map");
    }
    else
    {
        printf("%-40s fail\n", "NULL map");
    }
    result = HashMap_Remove(hashMap, keys->m_1, NULL, &valueRemoved);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "removing NULL keyHolder");
    }
    else
    {
        printf("%-40s fail\n", "NULL map");
    }    
    result = HashMap_Remove(hashMap, keys->m_1, &keyRemoved, NULL);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "removing NULL value");
    }
    else
    {
        printf("%-40s fail\n", "removing NULL value");
    }
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    free(keys->m_4);
    free(names->m_name4);
    free((int*)keyRemoved);
    free((char**) valueRemoved);
    free(keys);
    free(names);
}

void TestFind1()
{
    HashMap* hashMap;
    Names* names;
    Keys* keys;
    Map_Result result;
    void* valueRemoved;
    names = CreateNames();
    if (names == NULL)
    {
        printf("Allocation failed\n");
    }
    keys = CreateKeys();
    if (keys == NULL)
    {
        printf("Allocation failed\n");
    }
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    result = HashMap_Insert(hashMap, keys->m_1, names->m_name1);
    result = HashMap_Insert(hashMap, keys->m_2, names->m_name2);
    result = HashMap_Insert(hashMap, keys->m_3, names->m_name3);
    result = HashMap_Insert(hashMap, keys->m_4, names->m_name4);
    result = HashMap_Insert(hashMap, keys->m_5, names->m_name5);
    result = HashMap_Insert(hashMap, keys->m_6, names->m_name6);
    result = HashMap_Insert(hashMap, keys->m_7, names->m_name7);
    result = HashMap_Insert(hashMap, keys->m_8, names->m_name8);
    result = HashMap_Find(hashMap, keys->m_1, &valueRemoved);   
    if (result == MAP_SUCCESS && strcmp(*(char**)valueRemoved, "Jayden") == 0) /*add test to change the value within the hash map*/
    {
        printf("%-40s pass\n", "Finding key");
    }
    else
    {
        printf("%-40s fail\n", "Finding key");
    }          
    result = HashMap_Find(hashMap, NULL, &valueRemoved);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "finding NULL key");
    }
    else
    {
        printf("%-40s fail\n", "NULL key");
    }
    result = HashMap_Find(NULL, keys->m_1, &valueRemoved);   
    if (result == MAP_UNINITIALIZED_ERROR)
    {
        printf("%-40s pass\n", "finding NULL map");
    }
    else
    {
        printf("%-40s fail\n", "NULL map");
    }
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    free(keys->m_4);
    free(names->m_name4);
    free(keys);
    free(names);
}

void TestForEach1()
{
    HashMap* hashMap;
    Names* names;
    Keys* keys;
    names = CreateNames();
    if (names == NULL)
    {
        printf("Allocation failed\n");
    }
    keys = CreateKeys();
    if (keys == NULL)
    {
        printf("Allocation failed\n");
    }
    hashMap = HashMap_Create(SIZE, HashFunc, EqualityFunc);
    HashMap_Insert(hashMap, keys->m_1, names->m_name1);
    HashMap_Insert(hashMap, keys->m_2, names->m_name2);
    HashMap_Insert(hashMap, keys->m_3, names->m_name3);
    HashMap_Insert(hashMap, keys->m_4, names->m_name4);
    HashMap_Insert(hashMap, keys->m_5, names->m_name5);
    HashMap_Insert(hashMap, keys->m_6, names->m_name6);
    HashMap_Insert(hashMap, keys->m_7, names->m_name7);
    HashMap_Insert(hashMap, keys->m_8, names->m_name8);
    if (7 == HashMap_ForEach(hashMap, Print, NULL)) /*test a different function as well*/
    {
        printf("%-40s pass\n", "for each key");
    }
    else
    {
        printf("%-40s fail\n", "for each key");
    }          
    HashMap_Destroy(&hashMap, KeyDestroyFunc, ValueDestroyFunc);
    free(keys->m_4);
    free(names->m_name4);    
    free(keys);
    free(names);
}

static Names* CreateNames()
{
    Names* names;
    names = (Names*)malloc(sizeof(Names));
    if (names == NULL)
    {
        return NULL;
    }
    names->m_name1 = (char**)malloc(sizeof(char*));
    if (names->m_name1 == NULL)
    {
        return NULL;
    }
    *(names->m_name1) = "Jayden";
    names->m_name2 = (char**)malloc(sizeof(char*));
    if (names->m_name2 == NULL)
    {
        return NULL;
    }
    *(names->m_name2) = "Brayden";
    names->m_name3 = (char**)malloc(sizeof(char*));
    if (names->m_name3 == NULL)
    {
        return NULL;
    }
    *(names->m_name3) = "Aiden";
    names->m_name4 = (char**)malloc(sizeof(char*));
    if (names->m_name4 == NULL)
    {
        return NULL;
    }
    *(names->m_name4) = "Kaden";
    names->m_name5 = (char**)malloc(sizeof(char*));
    if (names->m_name5 == NULL)
    {
        return NULL;
    }
    *(names->m_name5) = "Hunter";
    names->m_name6 = (char**)malloc(sizeof(char*));
    if (names->m_name6 == NULL)
    {
        return NULL;
    }
    *(names->m_name6) = "Hayden";    
    names->m_name7 = (char**)malloc(sizeof(char*));
    if (names->m_name7 == NULL)
    {
        return NULL;
    }
    *(names->m_name7) = "Bentley";
    names->m_name8 = (char**)malloc(sizeof(char*));
    if (names->m_name8 == NULL)
    {
        return NULL;
    }
    *(names->m_name8) = "Tristen";
    return names;
}

static Keys* CreateKeys()
{
    Keys* keys;
    keys = (Keys*)malloc(sizeof(Keys));
    if (keys == NULL)
    {
        return NULL;
    }
    keys->m_1 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_1 == NULL)
    {
        return NULL;
    }
    *keys->m_1 = 2;
    keys->m_2 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_2 == NULL)
    {
        return NULL;
    }
    *keys->m_2 = 5;    
    keys->m_3 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_3 == NULL)
    {
        return NULL;
    }
    *keys->m_3 = 12;    
    keys->m_4 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_4 == NULL)
    {
        return NULL;
    }
    *keys->m_4 = 12;    
    keys->m_5 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_5 == NULL)
    {
        return NULL;
    }
    *keys->m_5 = 3;    
    keys->m_6 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_6 == NULL)
    {
        return NULL;
    }
    *keys->m_6 = 8;    
    keys->m_7 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_7 == NULL)
    {
        return NULL;
    }
    *keys->m_7 = 21;    
    keys->m_8 = (int*)malloc(sizeof(int) * 1);
    if (keys->m_8 == NULL)
    {
        return NULL;
    }
    *keys->m_8 = 1;    
    return keys;
}








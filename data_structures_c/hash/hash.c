#include <stdio.h>
#include <stdlib.h>  /*for malloc*/
#include <stddef.h>  /* size_t */
#include "hash.h"	 /*current header */

#define SIZE_FACTOR 1.3


static size_t FindData(const Hash* _hash, void* _data);
static size_t InsertHere(Hash* _hash, size_t _hashIndex);
size_t FindLargestPrime (size_t _size);

struct Hash

{
    void** m_data;
    char* m_state;
    size_t (*m_hashFunction)(void* _data);
    int (*m_equalityFunction)(void* _firstData, void* _secondData);
    size_t m_hashSize; /*real hash size */
    size_t m_originalSize; /*original size given by the client*/
    size_t m_numOfItems; /*number of occupied places in the table*/
    size_t m_maxOfRehashOperations; /*maximum amount of rehash operations which have been done over one insertion*/
    size_t m_counterOfInsertions; /*total amount of insertions into the table*/
    size_t m_allRehashOperations; /*all rehash operations mutual counter*/
};


/*..................API..................*/

Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int (*_equalityFunction)(void*, void*))
{
    Hash* newHash=NULL;
    char* statusArr = NULL;
    void** dataArr =NULL;
    size_t newSize;

    if (NULL == _hashFunction || NULL == _equalityFunction || _size < 2)
    {
        return NULL;
    }
    newSize =FindLargestPrime(_size * SIZE_FACTOR);
    if(NULL == (newHash = (Hash*)calloc(1, sizeof(Hash))))
    {
        return NULL;
    }
    if(NULL == (statusArr = (char*)calloc(newSize, sizeof(char))))
    {
        free (newHash);
        return NULL;
    }
    if(NULL == (dataArr = (void**)calloc(newSize, sizeof(void*))))
    {
        free (statusArr);
        free (newHash);
        return NULL;
    }

    newHash->m_data = dataArr;
    newHash->m_state = statusArr;
    newHash-> m_hashFunction = _hashFunction;
    newHash->m_equalityFunction = _equalityFunction;
    newHash->m_hashSize = newSize;
    newHash->m_originalSize = _size;
    return newHash;
}

/*...........................................*/

void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data))
{
	size_t size = 0, i = 0;
	if (NULL == _hash || NULL == *_hash)
	{
		return;
	}
	if(NULL != _keyDestroy)
	{
		size = (*_hash) -> m_numOfItems;
		for(i = 0; i < size ; ++i)
		{
            _keyDestroy((*_hash) -> m_data[i]);
		}
	}
	free((*_hash) -> m_data);
	free((*_hash) -> m_state);
	free(*_hash);
	*_hash = NULL;
}

/*...........................................*/

HashSet_Result HashInsert(Hash* _hash, void* _data)
{
    size_t hashIndex, indexToInsert;
    if(NULL == _hash || NULL == _data)
    {
        return SET_UNINITIALIZED;
    }
    if(_hash ->  m_numOfItems == _hash -> m_originalSize)
    {
        return SET_OVERFLOW;
    }
    hashIndex = _hash -> m_hashFunction(_data) % (_hash -> m_hashSize);  
    if(FindData(_hash, _data) !=  (_hash -> m_hashSize))
    {
        return SET_KEY_DUPLICATE;
    }

    if(0 == _hash -> m_numOfItems || FULL != _hash -> m_state[hashIndex])    /*if empty - we insert there*/
    {
        _hash -> m_data[hashIndex] = _data;
        _hash -> m_state[hashIndex] = FULL;
        ++_hash -> m_counterOfInsertions;
        ++(_hash -> m_numOfItems);
        return SET_SUCCESS;
    }

    indexToInsert = InsertHere(_hash, hashIndex);
    _hash -> m_data[indexToInsert] = _data;
    _hash -> m_state[indexToInsert] = FULL;
    ++(_hash -> m_numOfItems);
    if(_hash -> m_maxOfRehashOperations < _hash -> m_counterOfInsertions)
    {
        _hash -> m_maxOfRehashOperations = _hash -> m_counterOfInsertions;
    }
    _hash -> m_allRehashOperations += _hash -> m_counterOfInsertions;

    return SET_SUCCESS;
}

/*..............................................*/

HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data)
{
    size_t indexToRemove;
    if(NULL == _hash || NULL == _key)
    {
        return SET_UNINITIALIZED;
    }
    if(0 == _hash -> m_numOfItems)
    {
        return SET_UNDERFLOW;
    }
    indexToRemove = FindData(_hash, _key);
    if(indexToRemove == _hash -> m_hashSize) /*not found*/
    {
        return SET_KEY_NOT_FOUND;
    }
    *_data = _hash -> m_data[indexToRemove];
    _hash -> m_data[indexToRemove] = 0;
    _hash -> m_state[indexToRemove] = EMPTY_BUT_WAS_FULL;
    --(_hash -> m_numOfItems);

    return SET_SUCCESS;
}

/*...........................................*/

int HashIsFound(const Hash* _hash, void* _key)
{
    size_t index;
    
    if(NULL == _hash || NULL == _key)
    {
        return FALSE;
    }
    if(0 == _hash -> m_numOfItems)
    {
        return FALSE;
    }
    if(_hash -> m_hashSize != FindData(_hash, _key))
    {
        return TRUE;
    }
    return FALSE;
}

/*..................................*/

size_t HashNumOfItems(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }   
    return (_hash -> m_numOfItems);
}

/*................................*/

size_t HashCapacity(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }  
    return (_hash -> m_originalSize);
}

/*..................................*/

double HashAverageRehashes(const Hash* _hash)
{
    if(NULL == _hash || 0 == (_hash -> m_counterOfInsertions))
    {
        return 0;
    }
      
    return ((_hash -> m_allRehashOperations) / (_hash -> m_counterOfInsertions));   
}
/*...................................*/
size_t HashMaxReHash(const Hash* _hash)
{
    if(NULL == _hash)
    {
        return 0;
    }  
    return (_hash -> m_maxOfRehashOperations);     
}
/*..................................*/

void HashPrint(const Hash* _hash, void (*PrintKey)(void*))
{
    size_t i;
    if(NULL == _hash || NULL == PrintKey)
    {
        return;
    }  
    for(i = 0; i < (_hash -> m_hashSize); ++i)
    {
        if(_hash -> m_state[i] == FULL)
        {
            PrintKey(_hash -> m_data[i]);
        }
    }
}



/*...................................*/
/*................HELP..FUC...............*/
static size_t InsertHere(Hash* _hash, size_t _hashIndex)
{
    size_t i = 0, index = _hashIndex + 1;
    while(i < _hash -> m_hashSize)
    {
        if(FULL != _hash -> m_state[index])
        {
            _hash -> m_counterOfInsertions += i;
            return index;
        }
        index = (index + 1) % (_hash -> m_hashSize);
        ++i;
    }    
}

/*........................................*/

static size_t FindData(const Hash* _hash, void* _data)  /*return index if data found else return (_hash -> m_hashSize) */
{
    size_t hashIndex,i = 0;
    hashIndex = (_hash -> m_hashFunction(_data) % (_hash -> m_hashSize));  
    while(i < _hash -> m_hashSize)
    {
        if(ALWAYS_EMPTY == _hash -> m_state[hashIndex] || _hash -> m_maxOfRehashOperations < i)
        {
            return (_hash -> m_hashSize);
        }
        if(_hash -> m_state[hashIndex] == FULL)
        {
            if(_hash -> m_equalityFunction(_data, _hash -> m_data[hashIndex]))
            {
                return hashIndex;
            }
        }
        hashIndex = (hashIndex + 1) % (_hash -> m_hashSize);
        ++i;
    }
    return (_hash -> m_hashSize);
}

/*...............................................*/

size_t FindLargestPrime (size_t _size)
{
    size_t i;
    size_t temp = _size + 1;

    while (1)
    {
        for (i = 2; i < temp; i++)
        {
            if (temp % i == 0)
            {
                break;
            }
        }
        if (i == temp)
        {
            return temp;
        }
        temp++;
    }
}

/*...........................*/
size_t GetNewSize(Hash *_hash)
{
	return _hash -> m_hashSize;
}
size_t GetnRealSize(Hash *_hash)
{
	return _hash -> m_originalSize;
}
size_t GetNumOfItems(Hash *_hash)
{
	return _hash -> m_numOfItems;
}
size_t GetInsertionsCount(Hash *_hash)
{
	return _hash -> m_counterOfInsertions;
}
size_t GetMaxOfRehash(Hash *_hash)
{
	return _hash -> m_maxOfRehashOperations;
}
size_t GetAllRehash(Hash *_hash)
{
	return _hash -> m_allRehashOperations;
}
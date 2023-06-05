#ifndef __HASH_H__
#define __HASH_H__
#define ALWAYS_EMPTY 0
#define FULL 1
#define EMPTY_BUT_WAS_FULL -1
#define TRUE 1
#define FALSE 0


typedef struct Hash Hash;

typedef enum HashSet_Result {
    SET_SUCCESS = 0,
    SET_UNINITIALIZED,   /* Uninitialized HasSeterror*/
    SET_KEY_DUPLICATE,   /* Duplicate key error */
    SET_KEY_NOT_FOUND,   /* Key not found */
    SET_OVERFLOW,         /*No more space in HashSe */ 
    SET_UNDERFLOW       

}HashSet_Result;

typedef size_t (*HashFunction)(void* _data);

typedef int (*EqualityFunction)(void* _firstData, void* _secondData);

/** 
 * @brief create hash table
 * @param _size size of the hash table
 * @param _hashFunction a pointer to a function 
 * @param _equalityFunction a pointer to a function 
 * @return pointer to the created hash table
 * @return NULL if _size 0 or 1
 * @return NULL if _hashFunction or _equalityFunction NULL
 * @return NULL if if aloocation faild
 */
Hash* HashCreate(size_t _size, size_t (*_hashFunction)(void*), int (*_equalityFunction)(void*, void*));

/** 
 * @brief  destroy hash table
 * @param  _hash double pointer the hash table to be destroyed.
 * @param  _keyDestroy pointer to a function that takes in a void pointer and destroys the data element
 * @return NONE
 */
void HashDestroy(Hash** _hash, void (*_keyDestroy)(void* _data));

/** 
 * @brief   inserts an element into a hash table
 * @param  _hash pointer to a hash table
 * @param  _data pointer to the data to be inserted
 * @return SET_UNINITIALIZED  _hash and _data uninitialized
 * @return SET_OVERFLOW  if hash table is full
 * @return SET_KEY_DUPLICATE  if the data to be inserted is already present in the hash table.
 * @return SET_SUCCESS: in success.
 */
HashSet_Result HashInsert(Hash* _hash, void* _data);

/** 
 * @brief   removes an element from a hash table
 * @param  _hash pointer to a hash table
 * @param  _key pointer to the key of the element to be removed
 * @param  _data A double pointer to void 
 * @return SET_UNINITIALIZED  _hash and _data uninitialized
 * @return SET_UNDERFLOW  if hash table is empty
 * @return SET_KEY_NOT_FOUND  if the element to be removed is not present in the hash table
 * @return SET_SUCCESS: in success.
 */
HashSet_Result HashRemove(Hash* _hash, void* _key, void** _data);

/** 
 * @brief   checks if an element with a given key is present in a hash table
 * @param  _hash pointer to a hash table
 * @param  _key pointer to the key of the element to be removed
 * @return TRUE  if the element found
 * @return FALSE if the element is not found
 */
int HashIsFound(const Hash* _hash, void* _key);

/** 
 * @brief   function that return the number of items stored in a hash table
 * @param  _hash pointer to a hash table
 * @return num of items
 * @return 0 if _hash NULL
 */
size_t HashNumOfItems(const Hash* _hash);

/** 
 * @brief   function that returns the capacity of a hash table
 * @param  _hash pointer to a hash table
 * @return capacity of a hash table
 * @return 0 if _hash NULL
 */
size_t HashCapacity(const Hash* _hash);

/** 
 * @brief   function that returns the average number of rehash operations per insertion in a hash table
 * @param  _hash pointer to a hash table
 * @return average number of rehash operations per insertion in a hash table
 * @return 0 if _hash NULL
 */
double HashAverageRehashes(const Hash* _hash);

/** 
 * @brief  returns the maximum number of rehash operations required for a single insertion in a hash table.
 * @param  _hash pointer to a hash table
 * @return maximum number of rehash operations
 * @return 0 if _hash NULL
 */
size_t HashMaxReHash(const Hash* _hash);

/** 
 * @brief  print all the elements stored in a hash table
 * @param  _hash pointer to a hash table
 * @param   PrintKey pointer to a function that prints all elements
 * @return NONE
 */
void HashPrint(const Hash* _hash, void (*PrintKey)(void*));


#endif

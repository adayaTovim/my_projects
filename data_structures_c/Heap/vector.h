
#ifndef __VECTOR_H__
#define __VECTOR_H__
#include "ADTDef.h"  /*  error header  */
#include <stddef.h>  /* size_t  */


typedef struct Vector Vector;

Vector* VectorCreate(size_t _initialSize, size_t _extensionBlockSize);
 /*
Description: create new Vector.
Arguments: initialSize: size of initial items to insert the Vector.
		 extensionBlockSize: size of extantion if Vector is full.
Return: pointer to the new Vector
Error: NULL: 	if dynamic allocation failed
			if size = 0 and block size = 0
*/

void VectorDestroy(Vector* _vector);
/*
Description: Destroy the Vector
Arguments: _vector: Vector
Return: None
Error: None
*/

ADTErr VectorAdd(Vector *_vector, int _item);
/*
Description: Insert new element to the end of thr array
Arguments: _vector: Vector
	      Item: data of element to be inserted
Return: ERR_OK
Error: ERR_REALLOCATION_FAILED: when size < num of item and realloc failed
	  ERR_OVERFLOW: block size is defined as 0 when performing reallocation
	  ERR_NOT_INITIALIZED : vector address invailid
	  
*/

ADTErr VectorDelete(Vector *_vector, int* _item);
/*
Description: Delete element to the end of thr array
Arguments: _vector: Vector
	      Item: data of element to be delete
Return: ERR_OK
Error: ERR_NOT_INITIALIZED
	  ERR_REALLOCATION_FAILED
*/

ADTErr VectorGet(Vector *_vector, size_t _index, int *_item);
/*
Description: 
Arguments: 
Return: ERR_OK
Error: ERR_WRONG_INDEX
	  ERR_NOT_INITIALIZED
*/

ADTErr VectorSet(Vector *_vector, size_t _index, int _item);
/*
Description: 
Arguments: _
Return: ERR_OK
Error: ERR_WRONG_INDEX
	  ERR_NOT_INITIALIZED
*/

ADTErr VectorItemsNum(Vector *_vector, size_t* _numOfItems);
/*
Description: 
Arguments: _
Return: ERR_OK
Error: ERR_NOT_INITIALIZED
*/

void VectorPrint(Vector *_vector);
/*
Description: 
Arguments: _
Return: None
Error: None
*/

#endif /*__VECTOR_H__ */

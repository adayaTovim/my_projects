#ifndef __HEAP_H__
#define __HEAP_H__
#include "ADTDef.h" 
#include "vector.h"
#define MAGIC_NUM 203676691 

typedef struct Heap Heap;


Heap* HeapBuild(Vector* _vec); /* O(n) */
/*descraption: Build new heap from given vector.
  input: ptr to vector
  return: ptr to the heap; 
  errores: if aloocation faild return NULL.
*/


void HeapDestroy(Heap* _heap);
/*descraption: destroys a heap.
  input: ptr to heap.
  output: nothing.
  errores: nothing.
*/

ADTErr HeapInsert(Heap* _heap, int _data); /* O(log n) */
/*descraption: insert new element into a heap
  input: ptr to heap.
  return: return ERR_NOT_INITIALIZE -if the heap is NULL 
  		return ERR_OK - when the insert successful
*/

ADTErr HeapMax(Heap* _heap, int* _data);
/*descraption: retrieves the maximum element from a heap.
  input: ptr to heap,  ptr to data- where the max element will be stored.
  return: return ERR_NOT_INITIALIZED - if the heap/data is NULL.
  		 return ERR_OK - when the operation successful.
*/


ADTErr HeapExtractMax(Heap* _heap, int* _data); /* O(log n) */
/*descraption: replace the maximum element from a heap with the last element.
  input: ptr to heap,  ptr to data.
  return: if the heap/data is NULL return ERR_NOT_INITIALIZED .
  		 return ERR_OK- when the operation successful.
*/

size_t HeapItemsNum(Heap* _heap);
/*descraption: return number of element in a heap.
  input: ptr to heap. _
  output: heap Size
  return: if the heapa is NULL return 0 .
*/

void HeapPrint(Heap* _heap);
/*descraption: print elements in a heap.
  input: ptr to heap. 
  output: print the elements 	 
*/

#endif


#include <stddef.h>  /* size_t */
#include "ADTDef.h"  /* error header */
#include "vector.h"  /*current header */

#define MAGIC_NUM 230053647
#define TRUE 0
#define FALSE 1

typedef struct Queue Queue;

struct Queue* QueueCreate (size_t _size);  
/*
Description: create new struct Queue.
Arguments: size of initial items to insert 
Return: pointer to the new struct Queue
Error: NULL: if dynamic allocation failed or if size = 0 
*/

ADTErr PQueueInsert (Queue *_queue, int _item);
void QueueDestroy(Queue *_queue);
/*
Description: Destroy the struct Queue.
Arguments:  *Queue
Return: None
Error: None
*/

ADTErr QueueInsert (Queue *_queue, int _item);
/*
Description: Insert new element to the tail
Arguments: *Queue , Item: data of element to be inserted
Return: ERR_OK
Error: ERR_OVERFLOW if nitem and size equals 
	  ERR_NOT_INITIALIZED : queue address invailid  
*/

ADTErr QueueRemove (Queue *_queue, int *_item);
/*
Description: Delete element from the head 
Arguments: *Queue
	      Item: data of element to be delete
Return: ERR_OK
Error: ERR_NOT_INITIALIZED: queue address invailid or item
	  ERR_UNDERFLOW when nItems 0 
*/

int QueueIsEmpty(Queue *_queue);
/*
Description: check if queue empty
Arguments: *Queue
Return: TRUE: if nitem 0 or queue address invailid  , FALSE other
Error: None
*/

void QueuePrint(Queue *_queue);
/*
Description: print from the head to tail
Arguments: *Queue
Return: None
Error: None
*/



#ifndef __LISTITR_H__
#define __LISTITR_H__

#include "genList.h"

typedef void* ListItr;

/** 
 * @brief Get iterator to the list's beginning
 * @params _list : list to return begin iterator, pointing at first element
 *                 or at the end if list is empty
 * @return iterator pointing at the list's beginning
 *         NULL if _list is NULL
 */
ListItr ListItrBegin(const List* _list);

/** 
 * @brief Get iterator to the list end
 *
 * @params _list : list to return end iterator
 * @return an iterator pointing at the list's end
 *         NULL if _list is NULL
 */
ListItr ListItrEnd(const List* _list);

/** 
 * @brief returns none zero if _a and _b iterators refer to same node
 * @warning might be implemented as a macro
 * @return TRUE if a and b equals
 *         FALSE if a and b not equals
 */
int ListItrEquals(const ListItr _a, const ListItr _b);

/** 
 * @brief Get iterator to the next element from a given iterator
 * @warning if _itr is end iterator it will be returned
 * @return an iterator pointer to the next element 
 *         NULL if _itr is null
 */
ListItr ListItrNext(ListItr _itr);

/** 
 * @brief Get iterator to the previous element
 * @warning if _itr is begin iterator it will be returned
 * @return an iterator pointer to the prev element 
 *         NULL if _itr is null
 */
ListItr ListItrPrev(ListItr _itr);

/** 
 * @brief Get data from the list node the iterator is pointing to
 * @params _itr : A list iterator
 * @return the data the iterator is pointing at 
 *         NULL if pointing to the end or if _itr is null
 */
void* ListItrGet(ListItr _itr);

/** 
 * @brief Set data at the node where the iterator is pointing at
 * @return the data from the node to be changed
 *         NULL if pointing to the end or if _itr is null or if _element null
 */
void* ListItrSet(ListItr _itr, void* _element);

/** 
 * @brief insert a new node with the given element value before the node pointed to by the iterator _itr
 * @return an iterator pointing at the element inserted or NULL on error
 */
ListItr ListItrInsertBefore(ListItr _itr, void* _element);

/** 
 * @brief Removes the node the iterator is pointing at
 * @params _itr : A list iterator
 * @return the removed data
 */
void* ListItrRemove(ListItr _itr);

#endif /* __LISTITR_H__ */

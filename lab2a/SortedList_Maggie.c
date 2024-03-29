// NAME: Margaret Shi
// EMAIL: margaretshi@g.ucla.edu
// ID: 704974447

#include "SortedList.h"
#include <string.h>
#include <sched.h>

/**
 * SortedList_insert ... insert an element into a sorted list
 *
 *	The specified element will be inserted in to
 *	the specified list, which will be kept sorted
 *	in ascending order based on associated keys
 *
 * @param SortedList_t *list ... header for the list
 * @param SortedListElement_t *element ... element to be added to the list
 */

void SortedList_insert(SortedList_t *list, SortedListElement_t *element)
{
  if (list == NULL) return;
  SortedList_t *p = list;

  // insert element before its key is greater than the current key
  while (p != list) {
    if (strcmp(p->key, element->key) < 0)
      break;
    p = p->next;
  }

  if (opt_yield & INSERT_YIELD)
    sched_yield();
    
  SortedList_t *temp = p->next;
  p->next = element;
  element->prev = p;
  element->next = temp;
  temp->prev = element;
  return;
}


/**
 * SortedList_delete ... remove an element from a sorted list
 *
 *	The specified element will be removed from whatever
 *	list it is currently in.
 *
 *	Before doing the deletion, we check to make sure that
 *	next->prev and prev->next both point to this node
 *
 * @param SortedListElement_t *element ... element to be removed
 *
 * @return 0: element deleted successfully, 1: corrupted prev/next pointers
 *
 */

int SortedList_delete( SortedListElement_t *element)
{
  if (element == NULL || element->next->prev != element->prev->next)
    return 1;

  if (opt_yield & DELETE_YIELD)
    sched_yield();
  
  element->next->prev = element->prev;
  element->prev->next = element->next;
  return 0;
}


/**
 * SortedList_lookup ... search sorted list for a key
 *
 *	The specified list will be searched for an
 *	element with the specified key.
 *
 * @param SortedList_t *list ... header for the list
 * @param const char * key ... the desired key
 *
 * @return pointer to matching element, or NULL if none is found
 */

SortedListElement_t *SortedList_lookup(SortedList_t *list, const char *key)
{
  SortedList_t *p = list->next;

  if (opt_yield & LOOKUP_YIELD)
    sched_yield();
  
  while (p != list) {
    if (strcmp(p->key, key) == 0)
      return p;
    else
      p = p->next;
  }
  return NULL;
}


/**
 * SortedList_length ... count elements in a sorted list
 *	While enumerating list, it checks all prev/next pointers
 *
 * @param SortedList_t *list ... header for the list
 *
 * @return int number of elements in list (excluding head)
 *	   -1 if the list is corrupted
 */
int SortedList_length(SortedList_t *list)
{
  SortedList_t *p = list->next;
  int count = 0;

  while (p != list) {
    if (p->next->prev != p->prev->next)
      return -1;
    count++;
    if (opt_yield & LOOKUP_YIELD)
      sched_yield();
    p = p->next;
  }
  return count;
}

/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q == NULL)
        return NULL;

    /* What if malloc returned NULL? */
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->q_size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */

    if (q == NULL)
        return;

    list_ele_t *tmp;
    while (q->head) {
        tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* What should you do if the q is NULL? */
    if (q == NULL)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    list_ele_t *newh;

    newh = malloc(sizeof(list_ele_t));
    /* What if either call to malloc returns NULL? */
    if (newh == NULL) {
        return false;
    }
    newh->value = malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    memset(newh->value, '\0', strlen(s) + 1);
    memcpy(newh->value, s, strlen(s));

    // queue is empty
    if (q->head == NULL) {
        // newh->next = NULL;
        // q->head = newh;
        q->tail = newh;
    }
    // queue is not empty
    // else {
    newh->next = q->head;
    q->head = newh;
    //}
    ++q->q_size;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return false;

    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }
    newh->value = (char *) malloc(sizeof(char) * (strlen(s) + 1));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    memset(newh->value, '\0', strlen(s) + 1);
    memcpy(newh->value, s, strlen(s));
    if (q->tail != NULL) {
        // newh->next = NULL;
        q->tail->next = newh;
        // q->tail = newh;
    }
    // else {
    //	q->tail->next = newh;
    //}
    q->tail = newh;
    newh->next = NULL;
    ++q->q_size;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL)
        return false;

    // list_ele_t *tmp, *prev;
    list_ele_t *tmp;

    if (sp != NULL) {
        memset(sp, '\0', bufsize);
        strncpy(sp, q->head->value, bufsize - 1);
        //*(sp + bufsize - 1) = '\0';
    }
    tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    --q->q_size;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
        return 0;
    return q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    // You need to write the code for this function
    if (q == NULL || q->head == NULL)
        return;

    list_ele_t *cur, *prev;
    for (int i = 0; i < q->q_size; i++) {
        if (i == 0) {
            if (q->head->next == NULL)
                return;

            prev = q->head;
            q->head = q->head->next;
            prev->next = NULL;
            q->tail = prev;
        } else {
            cur = q->head;
            q->head = q->head->next;
            cur->next = prev;
            prev = cur;
            if (q->head == NULL)
                q->head = prev;
        }
    }
}

/**************************************************************************
 *
 * New Beginnings Foundations Final
 *
 * Authors:
 * Logan Ballard
 * Lynnae Griffiths
 * Anna Hansen
 * Matt Krepp
 * Gavin Megson
 * Boris Popadiuk
 * Ian Winter
 * Jesse Zhu
 *
 * stack.c - Functions relating to stack management.
 *
 **************************************************************************/

#include "header.h"

/* Pop - removes top element from stack and returns node or NULL if empty. */
node *pop(stack_element ** stackaddr)
{
    stack_element *p = NULL;
    node *pnode = NULL;
    stack_element *stack = *stackaddr;

    if (stack != NULL) {
	p = stack->prev;
	pnode = stack->payload;
	free(stack);
	*stackaddr = p;
    }
    return pnode;
}

/* Push - push a node pointer to top element of stack or initalize a stack. */
void push(node * pnode, stack_element ** stackaddr)
{
    stack_element *stack = *stackaddr;
    stack_element *p = malloc(sizeof(stack_element));
    p->prev = NULL;
    p->payload = pnode;
    if (stack != NULL)
	p->prev = stack;
    *stackaddr = p;
}

/* Peek - returns top element in stack or NULL if stack is empty. */
node *peek(stack_element * stack)
{
    node *pnode = NULL;
    if (stack != NULL)
	pnode = stack->payload;
    return pnode;
}


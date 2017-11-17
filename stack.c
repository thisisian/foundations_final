/**************************************************************************
 *
 * New Beginnings Foundations Final
 *
 * Authors:
 * Gavin Megson
 * Lynnae Griffiths
 * Matt Krepp
 * Ian Winter
 *
 * stack.c - Functions relating to stack management.
 *
 **************************************************************************/

#include "header.h"

/* Pop - removes top element from stack and returns node or NULL if empty. */
 node *pop(stack_element **stackaddr)
 {
     stack_element *p = NULL;
     node *pnode = NULL;
     stack_element *stack = *stackaddr;
 
     if (stack != NULL) {
         p = stack->prev;
         pnode = stack->node;
	 #if DEBUG
         printf("Pop: %s\n", pnode->name);
	 #endif 
         free(stack);
         *stackaddr = p;
     }
     return pnode;
 }

/* Push - push a node pointer to top element of stack or initalize a stack. */
void push(node * pnode, stack_element **stackaddr)
{
   stack_element *stack = *stackaddr;
   stack_element * p = malloc(sizeof(stack_element));
   p->prev = NULL;
   p->node = pnode;
   #if DEBUG 
   printf("Push: %s\n", p->node->name);
   #endif
   if (stack != NULL)
       p->prev = stack;
   *stackaddr = p;
}

/* Peek - returns top element in stack or NULL if stack is empty. */
node *peek(stack_element *stack)
{
    node *pnode = NULL;
    if (stack != NULL)
        pnode = stack->node;
    return pnode;
}

/* Pop all elements from stack and print. */
void printstack(stack_element *stack, char end[])
{
    int i;
    for (i = 1; strcmp(stack->node->name, end) != 0; ++i){
            node a = *pop(&stack);
            printf("%d. %s\n", i, a.name);
    }
    node a = *pop(&stack);
    printf("%s\n", a.name);
}

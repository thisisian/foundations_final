
#include "functions.h"						//header file, store in local directory

/* Peek - returns top element in stack or NULL if stack is empty. */
node *peek(stack_element *stack)
{
    node *pnode = NULL;
    if (stack != NULL)
        pnode = stack->node;
    return pnode;
}

/* Pop - removes top element from stack and returns node or NULL if empty. */
 node *pop(stack_element **stackaddr)
 {
     stack_element *p = NULL;
     node *pnode = NULL;
     stack_element *stack = *stackaddr;
 
     if (stack != NULL) {
         p = stack->prev;
         pnode = stack->node;
         printf("Pop: %s\n", pnode->name); // testing
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
  
     printf("Push: %s\n", p->node->name);
  
     if (stack != NULL)
         p->prev = stack;
     *stackaddr = p;
  }
/*
 * Find path between two nodes returns an array of nodes
 * along path or NULL if there's an error.
 */
stack_element *getdirs(char start[], char end[], node *junc)
{
    int i, j;
    char s[MAXSTR];
    node *endnode = NULL;
    node *curnode = NULL;
    stack_element *dirstack = NULL;
    int dir;                            /* Holds direction of end node */
    node *dirname = NULL;               /* Holds name of junciton node */

    /* Starting at the end node */
    if ((curnode = endnode = findnode(end, junc, &dir)) ==  NULL) {
        printf("Error: End node not found!\n");
        return NULL;
    }
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Moving towards end of branch */
    while (curnode->dir[FWD] != NULL) {
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name))
            return dirstack;
        curnode = curnode->dir[FWD];
    }

    /* Checking last node in branch */
    push(curnode, &dirstack);
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Dump stack and return to end node */
    while (pop(&dirstack) != NULL)
        ;
    curnode = endnode;

    /* Move towards junction */
    while (curnode->dir[BACK] != junc) {
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name))
            return dirstack;
        curnode = curnode->dir[BACK];
    }

    /* Checking last node before junction */
    push(curnode, &dirstack);
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Getting a name for junction node */
    getdirname(dir, s);
    dirname = createnode();
    strcpy(dirname->name, s);
    push(dirname, &dirstack);

    /* Do brute force search */
    for (i = 0; i < NUMDEG; ++i) {
        if (i == dir)                 /* Avoid previously searched direction */
            continue;
        if ((curnode = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        if ((curnode = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        for (j = 0; curnode->dir[FWD] != NULL; ++j) {
            push(curnode, &dirstack);
            if (!strcmp(start, curnode->name)){
                return dirstack;
            }
            curnode = curnode->dir[FWD];
        }
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name)) {
            return dirstack;
        }
        for (j; j >= 0; --j)
            pop(&dirstack);
        curnode = junc;
    }
    printf("Start node not found!\n");
    return NULL;
}


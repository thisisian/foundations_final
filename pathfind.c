/**************************************************************************
 * New Beginnings Foundations Final
 *
 * Authors:
 * Gavin Megson
 * Lynnae Griffiths
 * Matt Krepp
 * Ian Winter
 *
 * pathfind.c - Functions relating to path finding.
 *
 **************************************************************************/

#include "header.h"

/*
 * Get path - Find path between two nodes. Returns a stack of city names
 * along path or NULL if there's an error.
 *
 * A special node 'branchname' is loaded into the stack in the case
 * where an exhaustive search is needed. This node holds the name of the
 * branch in which the end node exists and is used for displaying 
 * the direction chosen at the root.
 */
stack_element *getpath(char start[], char end[], node *root)
{
    int i, j;
    char s[MAXSTR];
    node *endnode = NULL;               /* Points to end node in search */
    node *curnode = NULL;
    stack_element *dirstack = NULL;
    int branchindex;                    /* Holds end node's branch index */
    node *branchname = NULL;            /* Holds name of root node */

    /* Starting at the end node */
    if ((curnode = endnode = findnode(end, root, &branchindex)) ==  NULL) {
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

    /* Move towards root */
    while (curnode->dir[BACK] != root) {
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name))
            return dirstack;
        curnode = curnode->dir[BACK];
    }

    /* Checking last node before root */
    push(curnode, &dirstack);
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Getting a name for root node */
    getbranchname(branchindex, s);
    branchname = createnode();
    strcpy(branchname->name, s);
    push(branchname, &dirstack);

    /* Do exhaustive search */
    for (i = 0; i < NUMDEG; ++i) {
        if (i == branchindex)          /* Skip previously searched direction */
            continue;
        if ((curnode = root->dir[i]) == NULL)    /* direction points to NULL */
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
        curnode = root;
    }
    printf("Start node not found!\n");
    return NULL;
}

/*
 * Find node - Brute force search for node pointer with name s[]. If found,
 * branch index is stored in dir and a pointer to the node is returned.
 * Otherwise, integer dir is invalid and function returns NULL.
 */
node *findnode(char s[], node *root, int *dir)
{
    int i, j;
    node *cur = NULL;

    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = root->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        *dir = i;
        while (cur->dir[FWD] != NULL) {
            if (!strcmp(cur->name, s)) {
       	 #if DEBUG
                printf("Found %s\n", cur->name);
       	 #endif
                return cur;
            }
            cur = cur->dir[FWD];
        }
        if (!strcmp(cur->name, s)) {
            #if DEBUG
            printf("Found %s\n", cur->name);
            #endif
            return cur;
        }
        cur = root;
    }
    return NULL;
}

/*
 * Get branch name - Input branch index and save name into s.
 */
void getbranchname(int branchindex, char s[]) {
  if (branchindex == 0) 
      strcpy(s, "I-5 North");
  else if (branchindex == 1)
      strcpy(s, "Highway 26 East");
  else if (branchindex == 2)
      strcpy(s, "I-5 South");
  else if (branchindex == 3)
      strcpy(s, "Highway 26 West");
  else 
      printf("getbranchname: invalid direction");
}

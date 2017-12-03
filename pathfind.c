/**************************************************************************
 *
 * New Beginnings Foundations Final
 *
 * Authors:
 * Anna Hansen
 * Logan Ballard
 * Boris Popadiuk
 * Jesse Zhu
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
 * Get path - Find path between two nodes. Returns a stack of city namesd
 * along path or NULL if there's an error.
 *
 * A special node 'exitbranchname' is loaded into the stack in the case
 * where an exhaustive search is needed. This node holds the name of the
 * branch in which the end node exists and is used for displaying
 * the direction chosen at the root.
 */
stack_element *getpath(char start[], char end[], node *root, float *cost)
{
    /*
     * getpath starts at the ending node via findnode function called
     * from within, works its way down the current branch,
     * then back up to the junction.
     */
    int i, j;
    char s[MAXSTR];
    stack_element *dirstack = NULL;	/* Create stack */
    node *curnode = NULL; 		/* Current node */
    node *endnode = NULL;	  /* Points to end node in search */
    int branchindex;	       	  /* End node's branch index */
    node *exitbranchname = NULL;  /* Name of exit node branch */
    float miles_sum = 0.0;	  /* Running sum of miles traveled*/

    /* Starting at the end node */
    endnode = findnode(end, root, &branchindex);
    if (endnode == NULL) {
	printf("Invalid destination.\n");
	return NULL;
    }

    /* Start and end are the same */
    if (!strcmp(start, endnode->name)) {
	*cost = 0.0;
	return dirstack;	/* Return stack */
    }

    /* Moving towards end of branch */
    curnode = endnode;
    for (;;) {
	push(curnode, &dirstack);
	miles_sum += curnode->cost;
	if (!strcmp(start, curnode->name)) {     /* Found start node */
	    *cost = miles_sum - endnode->cost;
	    return dirstack;	/* Return stack */
	}
        if (curnode->dir[FWD] == NULL) 
            break;
        else 
            curnode = curnode->dir[FWD];
    }

    /* Clear stack and sum; return to end node */
    while (pop(&dirstack) != NULL)
        ;
    miles_sum = 0.0;
    curnode = endnode;

    /* Move towards root */
    for (;;) {
	push(curnode, &dirstack);
	miles_sum += curnode->cost;
	if (!strcmp(start, curnode->name)) {
	    *cost = miles_sum - curnode->cost;
	    return dirstack; 		/* Return stack */
	}
        if (curnode->dir[BACK] == root)
            break;
        else
            curnode = curnode->dir[BACK];
    }

    /* Getting a n node */
    exitbranchname = createnode();
    getbranchname(branchindex, s);
    strcpy(exitbranchname->name, s);
    push(exitbranchname, &dirstack);

    /* Do exhaustive search from root */
    float const end_to_junction = miles_sum; /* Distance from endnode to root */
    for (i = 0; i < NUMDEG; ++i) {
	if (i == branchindex)	      /* Skip previously searched direction */
	    continue;
	if ((curnode = root->dir[i]) == NULL)	/* direction points to NULL */
	    continue;
	for (j = 0; ; ++j) {
	    push(curnode, &dirstack);
	    miles_sum += curnode->cost;
	    if (!strcmp(start, curnode->name)) {
		*cost = miles_sum;
		return dirstack; 	/* Return stack */
	    }
            if (curnode->dir[FWD] == NULL)
                break;
            else
                curnode = curnode->dir[FWD];
	}
        /* Start node wasn't on this branch, reset stack and sum */
	miles_sum = end_to_junction;
	for (j; j >= 0; --j)
	    pop(&dirstack);
    }
    printf("Start node not found!\n");
    return NULL;
}

/*
 * Find node - Brute force search for node pointer with name s[]. If found,
 * branch index is stored in dir and a pointer to the node is returned.
 * Otherwise, integer dir is invalid and function returns NULL.
 */
node *findnode(char s[], node * root, int *branch)
{
    int i, j;
    node *cur = NULL;

    for (i = 0; i < NUMDEG; ++i) {
	if ((cur = root->dir[i]) == NULL)	/* direction points to NULL */
	    continue;
	if (branch != NULL)
	    *branch = i;
	while (cur->dir[FWD] != NULL) {
	    if (!strcmp(cur->name, s)) {
		return cur;
	    }
	    cur = cur->dir[FWD];
	}
	if (!strcmp(cur->name, s)) {
	    return cur;
	}
	cur = root;
    }
    return NULL;
}

/*
 * Get branch name - Input branch index and save name into s.
 */
void getbranchname(int branchindex, char s[])
{
    if (branchindex == 0)
	strcpy(s, "Highway 26 East");
    else if (branchindex == 1)
	strcpy(s, "Highway 26 West");
    else if (branchindex == 2)
	strcpy(s, "I5 North");
    else if (branchindex == 3)
	strcpy(s, "I5 South");
    else
        printf("Invalid branch index");
}

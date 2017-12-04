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
stack_element *getpath(char start[], char end[], node *rootNode, float *cost)
{
    /*
     * getpath starts at the ending node via findnode function called
     * from within, works its way down the current branch,
     * then back up to the junction.
     */
    int i, j;
    char utilString[MAXSTR];		// utility string to hold city name
    stack_element *pathstack = NULL;	/* Create stack */
    node *curnode = NULL; 		/* Current node */
    node *endnode = NULL;               /* Points to end node in search */
    int branchindex;	       	        /* End node's branch index */
    node *exitbranchname = NULL;        /* Name of exit node branch */
    float miles_sum = 0.0;	        /* Running sum of miles traveled*/

    /* Starting at the end node */
    endnode = findnode(end, rootNode, &branchindex);
    if (endnode == NULL)
	return NULL;

    /* Start and end are the same */
    if (!strcmp(start, endnode->name)) {
	*cost = 0.0;
	return pathstack;	/* Return stack */
    }

    if (strcmp(end, rootNode->name)) {
    /* If the root is the end node, the following do not have to be done: */
            /* Moving towards end of branch */
            curnode = endnode;
            for (;;) {
                push(curnode, &pathstack);
                miles_sum += curnode->cost;
                if (!strcmp(start, curnode->name)) {     /* Found start node */
                    *cost = miles_sum - endnode->cost;
                    return pathstack;   /* Return stack */
                }
                if (curnode->branch[FWD] == NULL) 
                    break;
                else 
                    curnode = curnode->branch[FWD];
            }

            /* Clear stack and sum; return to end node */
            while (pop(&pathstack) != NULL)
                ;
            miles_sum = 0.0;
            curnode = endnode;

            /* Move towards root */
            for (;;) {
                push(curnode, &pathstack);
                miles_sum += curnode->cost;
                if (!strcmp(start, curnode->name)) {
                    *cost = miles_sum - curnode->cost;
                    return pathstack;           /* Return stack */
                }
                if (curnode->branch[BACK] == rootNode)
                    break;
                else
                    curnode = curnode->branch[BACK];
            }
                    
            /* Getting a n node */
            exitbranchname = createnode();
            getbranchname(branchindex, utilString);
            strcpy(exitbranchname->name, utilString);
            push(exitbranchname, &pathstack);

           /* Check if start is junction */
            if (strcmp(start, rootNode->name)==0) {
                    push(rootNode, &pathstack);
                    return pathstack;
            }
    }


    /* Do exhaustive search from root */
    float const end_to_junction = miles_sum; /* Distance from endnode to root */
    push(rootNode, &pathstack);
    for (i = 0; i < NUMDEG; ++i) {
        if (i == branchindex)         /* Skip previously searched direction */
            continue;
        if ((curnode = rootNode->branch[i]) == NULL) /* direction points to NULL */
            continue;
        for (j = 0; ; ++j) {
            push(curnode, &pathstack);
            miles_sum += curnode->cost;
            if (!strcmp(start, curnode->name)) {
                *cost = miles_sum;
                return pathstack;       /* Return stack */
            }
            if (curnode->branch[FWD] == NULL)
                break;
            else
                curnode = curnode->branch[FWD];
        }
        /* Start node wasn't on this branch, reset stack and sum */
        miles_sum = end_to_junction;
        for (j; j >= 0; --j)
            pop(&pathstack);
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

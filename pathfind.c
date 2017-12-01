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
 * Get path - Find path between two nodes. Returns a stack of city namesd
 * along path or NULL if there's an error.
 *
 * A special node 'branchname' is loaded into the stack in the case
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
    node *endnode = NULL;               /* Points to end node in search */
    node *curnode = NULL;
    stack_element *dirstack = NULL;
    int branchindex;                    /* Holds end node's branch index */
    node *branchname = NULL;            /* Holds name of root node */
	float miles_sum = 0.0;		/* Accumulates cost of path, depending on stack actions */

    /* Starting at the end node */
    if ((endnode = findnode(end, root, &branchindex)) ==  NULL) {
        printf("Invalid destination.\n");
        return NULL;
    }

    if (!strcmp(start, endnode->name)) {	/* If start and end locations are the same, cost is 0 */ 
        *cost=0.0;					
	return dirstack;
    }
    /* Moving towards end of branch */
    curnode = endnode;
    while (curnode->dir[FWD] != NULL) {
        push(curnode, &dirstack); 
		miles_sum += curnode->cost;				
        if (!strcmp(start, curnode->name)) {		/* Trip miles = accumulated sum - end node cost */
            *cost = miles_sum - endnode->cost;		/* If the start is below end, and start is not the last node on branch */		
	    return dirstack;
        }
	curnode = curnode->dir[FWD];
    }

    /* Checking last node in branch */
    push(curnode, &dirstack); 
	if (!strcmp(start, curnode->name)) {				/* Trip miles = accumulated sum - end node cost */
        miles_sum += curnode->cost;						/* If start is below end, and start is the last node in the branch */
		*cost = miles_sum - endnode->cost;			
		return dirstack;
        }

    /* Reversing direction, dumping stack, and returning to end node */
    while (pop(&dirstack) != NULL) {
        /* pops stack until empty (until back at end node) */
	}
    miles_sum = 0.0;									/* Clear accumulated sum, start node not found on branch*/	
    curnode = endnode;

    /* Move towards root */
    while (curnode->dir[BACK] != root) {
        push(curnode, &dirstack);						/* If start location is closer to junction than end location */	
		miles_sum += curnode->cost; 					/* accumulate cost from end node to junction in miles_sum variable */
        if (!strcmp(start, curnode->name)) {
	    	*cost= miles_sum - curnode->cost;
            return dirstack;
		}
		curnode = curnode->dir[BACK];
    }

    /* Checking last node before root */
    push(curnode, &dirstack); 
	miles_sum += curnode->cost; 						/*If start location is on node before junction (above end location) */
	if (!strcmp(start, curnode->name)) {				/* accumulate cost from end node to junction in miles_sum variable */
        *cost = miles_sum - curnode->cost;			
        return dirstack;
    }

    /* Getting a name for root node */
    getbranchname(branchindex, s);						/* getbranchname() prints highway name based on int from pointer array */
    branchname = createnode();							/* branchname var stores int number of branch from pointer array */
    strcpy(branchname->name, s);
    push(branchname, &dirstack);

	float branch_sum = 0.0;								/* Var used to accumulate miles sum for branch, if end and start aren't on same branch */
    float const end_to_junction  = miles_sum;		/* Prevents branch sum variable from changing if start and end are on different branches */
	/* Do exhaustive search from root */
    for (i = 0; i < NUMDEG; ++i) {
        if (i == branchindex)          /* Skip previously searched direction */
            continue;
        if ((curnode = root->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        for (j = 0; curnode->dir[FWD] != NULL; ++j) {
            push(curnode, &dirstack); 
			branch_sum += curnode->cost;			
            if (!strcmp(start, curnode->name)){
				*cost= end_to_junction + branch_sum; 				
				return dirstack;
            }
            curnode = curnode->dir[FWD];
        }
        push(curnode, &dirstack);		/* Push final node in branch */
		branch_sum += curnode->cost;			
        
		if (!strcmp(start, curnode->name)) {
	    	*cost= end_to_junction + branch_sum;
            return dirstack;
        }
	
		branch_sum = 0.0;					/* If start node isn't found on branch, reset branch_sum to 0 */
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
node *findnode(char s[], node *root, int *branch)
{
    int i, j;
    node *cur = NULL;

    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = root->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        if (branch != NULL)
            *branch = i;
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
      strcpy(s, "Highway 26 East");
  else if (branchindex == 1)
      strcpy(s, "Highway 26 West");
  else if (branchindex == 2)
      strcpy(s, "I5 North");
  else if (branchindex == 3)
      strcpy(s, "I5 South");
  else
      printf("getbranchname: invalid direction");
}

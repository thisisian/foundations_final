/**************************************************************************
 * New Beginnings Foundations Final
 *
 * Authors:
 * Gavin Megson
 * Lynnae Griffiths
 * Matt Krepp
 * Ian Winter
 *
 *
 *	FIXME add description 
 **************************************************************************/

#include "functions.h"						//header file, store in local directory

int main(void) 
{
    stack_element *pathstack = NULL;
    node *junc = loadmap("./data");
    char start[MAXSTR];
    char end[MAXSTR];

    node *cur = NULL;
    node *node = NULL;
    int i, j;

    /* Testing Traversal */
    printf("--Traversal Test--\n");
    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        for (j = 0; cur->dir[FWD] != NULL; ++j) {
            printf("%s", cur->name);
            cur = cur->dir[FWD];
        }
        printf("%s", cur->name);
        printf("\n");
        cur = junc;
    }
    printf("------------------\n\n");

    /* Find the directions, dump stack */
    for (;;) {
        printf("Start:\n");
        scanf("%s", start);
        printf("End:\n");
        scanf("%s", end);
        pathstack = getdirs(start, end, junc);
        printf("-----Directions-----\n%s -> %s\n", start, end);
        while (pop(&pathstack) != NULL)
            ;
    }

}

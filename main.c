/**************************************************************************
 * New Beginnings Foundations Final
 *
 * Authors:
 * Gavin Megson
 * Lynnae Griffiths
 * Matt Krepp
 * Ian Winter
 *
 * This program is a simple map that represents two highways, 
 * i5 and highway 26. i5 runs north/south, and 26 runs east west.
 * The highways intersect at a junction in the middle of the map.
 * Cities along the route are loaded into the map via a text file.
 * The program accepts a starting city and ending city as input, 
 * and directs the user to the best route between the two cities.
 *
 * files: main.c, functions.h, nodelib.c, stacklib.c, data
 **************************************************************************/

#include "functions.h"						//header file, store in local directory

int main(void) 
{
    stack_element *pathstack = NULL;
    node *junc = loadmap("./data");				//load cities into map from data file
    char start[MAXSTR];						//MAXSTR is maximum string length, defined in functions.h
    char end[MAXSTR];

    node *cur = NULL;						//initialize list pointers
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
	inputformat(start);
        printf("End:\n");
        scanf("%s", end);
	inputformat(end);
        pathstack = getdirs(start, end, junc);
        printf("-----Directions-----\n%s -> %s\n", start, end);
    }

}

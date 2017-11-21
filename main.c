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
 * The highways intersect at a junction (root) in the middle of the map.
 * Cities along the route (branches) are loaded into the map via a text file.
 * The program accepts a starting city and ending city as input, 
 * and directs the user to the best route between the two cities.
 *
 * The map structure is generated from an external file (see mapgen.c). 
 * The intersection, of highway 26 and I-5 is referred to as the root. 
 * There are braches extending from the root with nodes indicating 
 * individual cities. A search is performed (see pathfind.c) and directions
 * are added to a stack. The stack is then printed, giving directions.
 *
 * files: functions.h, main.c, mapgen.c, pathfind.c, stack.c, util.c
 * (compile all above files to run)
 **************************************************************************/

#include "header.h"		/* Header file, store in local directory */

int main(void) 
{
    int i;
    node *root = loadmap("./data");   /* Load cities into map from data file */
    char s[MAXSTR];

    stack_element *pathstack = NULL;
    char start[MAXSTR];               /* Name of start city */
    char end[MAXSTR];                 /* Name of end city */

    #if DEBUG
    debug_traversal();
    #endif

    while (strcmp(s, "Exit") != 0)
    {
        printmap(root);
        printf("Enter starting location:\n");
        getstr(start, MAXSTR);
	formatinput(start, MAXSTR);
        if (findnode(start, root, NULL) == NULL) {
            printf("Invalid starting location\n");
            continue;
        }
        printf("Enter ending location:\n");
        getstr(end, MAXSTR);
	formatinput(end, MAXSTR);
	if ((pathstack = getpath(start, end, root)) == NULL)
            continue;
        printf("-----Directions-----\n%s to %s:\n", start, end);
	printstack(pathstack, end);
	printf("Type \"exit\" to quit, or any key to continue:\n");
	getstr(s, MAXSTR);
        formatinput(s, MAXSTR);
    }
    return 0;
}

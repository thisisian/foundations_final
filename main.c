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
 * files: functions.h, main.c, map.c, pathfind.c, stack.c, util.c
 **************************************************************************/

#include "header.h"		/* Header file, store in local directory */

int main(void) 
{
    int i, j;
    node *cur = NULL;
    node *root = loadmap("./data");   /* Load cities into map from data file */

    stack_element *pathstack = NULL;
    char start[MAXSTR];               /* Name of start city */
    char end[MAXSTR];                 /* Name of end city */

    #if DEBUG
    debug_traversal();
    #endif

    char exit[MAXSTR];
    while (strcmp(exit, "exit") != 0)
    {
        printf("Enter starting location:\n");
        getstr(start, MAXSTR);
	formatinput(start);
        printf("Enter ending location:\n");
        getstr(end, MAXSTR);
	formatinput(end);
	if ((pathstack = getpath(start, end, root)) == NULL) {
            continue;
	}
        printf("-----Directions-----\n%s to %s:\n", start, end);
	printstack(pathstack, end);
	printf("Type \"exit\" to quit, or any key to continue:\n");
	getstr(exit, MAXSTR);
	for (int i = 0; i < strlen(exit); ++i) 
		exit[i] = (tolower(exit[i]));
    }
}

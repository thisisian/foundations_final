/**************************************************************************
 * New Beginnings Foundations Final
 *
 * Authors:
 * Logan Ballard
 * Lynnae Griffiths
 * Anna Hansen
 * Matt Krepp
 * Gavin Megson
 * Boris Popadiuk
 * Ian Winter
 * Jesse Zhu
 *
 * This program is a simple map that represents two highways,
 * I-5 and Highway 26. i5 runs north/south, and 26 runs east west.
 * The highways intersect at a junction (root) in the middle of the map.
 * Cities along the highway branches are loaded into the map via a data file.
 * The program accepts a starting city and ending city as input,
 * and directs the user to the best route between the two cities.
 *
 * The map structure is generated from an external file (see mapgen.c).
 * The intersection, of Highway 26 and I-5 is referred to as the root.
 * There are braches extending from the root with nodes indicating
 * individual cities. A search is performed (see pathfind.c) and directions
 * are added to a stack. The stack is then printed, giving directions.
 *
 * files: functions.h, main.c, mapgen.c, pathfind.c, stack.c, util.c
 * To compile run 'gcc *.c' 
 **************************************************************************/

#include "header.h"

int main(void)
{
    int i;
    char input[MAXSTR];
    node *root = loadmap("data"); /* Load cities into map from data file */

    stack_element *pathstack = NULL;
    char start[MAXSTR];		/* Name of start city */
    char end[MAXSTR];		/* Name of end city */
    float cost = 0.0;		/* Cost of trip */

    while (strcmp(input, "Exit") != 0) {
	printmap(root);
	printf("Enter starting location:\n");
	getstr(start);
	formatinput(start, MAXSTR);
	if (findnode(start, root, NULL) == NULL) {
	    printf("Invalid starting location.\n");
	    continue;
	}
	printf("Enter ending location:\n");
	getstr(end);
	formatinput(end, MAXSTR);
	if (findnode(end, root, NULL) == NULL) {
	    printf("Invalid ending location.\n");
	    continue;
	}
	if (strcmp(start, end) == 0)
	    printf("Starting location and destination are the same.\n");
	if ((pathstack = getpath(start, end, root, &cost)) == NULL)
	    continue;
	printf("-----Directions-----\n%s to %s:\n", start, end);
	printstack(pathstack, end, cost);
	printf("Type \"exit\" to quit, or any key to continue:\n");
	getstr(input);
	formatinput(input, MAXSTR);
    }
    return 0;
}

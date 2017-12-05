/**************************************************************************
 *
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
 * mapgen.c - Functions relating to map generation.
 *
 **************************************************************************/

#include "header.h"

/* Create node - create and initialize node, return pointer to node */
node *createnode()
{
    int i;
    node *newNode = malloc(sizeof(node));
    newNode->name[0] = '\0';
    for (i = 0; i < NUMDEG; ++i)
	newNode->branch[i] = NULL;
    return newNode;
}

/*
 * Load map - loads data from file, returns pointer to root.
 * Map file contains city names separated by commas. Branches are terminated
 * by END
 */
node *loadmap(char file[])
{
    int i;
    node *curNode = NULL;
    node *newNode = NULL;
    node *rootNode = NULL;
    int forward;        	    /* Holds node index pointing forward */
    float cost = 0.0;
    FILE *mfile = fopen(file, "r");

    /* Creating root node */
    curNode = rootNode = createnode();
    strcpy(rootNode->name, "Junction");

    /* Loading in branches */
    for (i = 0; i < NUMDEG; ++i) {
        curNode = rootNode;
        forward = i;
	while ((newNode = loadcity(mfile)) != NULL) {
            curNode->branch[forward] = newNode;
            newNode->branch[BACK] = curNode;
            curNode = newNode;
            curNode->branch[FWD] = NULL;
            forward = FWD;
        }
    }
    fclose(mfile);
    return rootNode;
}

/* Loads node name and cost. Returns NULL if END occurs */
node *loadcity(FILE *mfile)
{
    char utilString[MAXSTR]; // string to hold city + cost info
    node *citynode = NULL;

    getentry(mfile, utilString);
    if (!strcmp(utilString, "END"))
        return NULL;
    citynode = createnode();
    citynode->cost = atof(utilString);
    getentry(mfile, utilString);
    strcpy(citynode->name, utilString);
}

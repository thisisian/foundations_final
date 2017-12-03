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
 * mapgen.c - Functions relating to map generation.
 *
 **************************************************************************/

#include "header.h"

/* Create node - create and initialize node, return pointer to node */
node *createnode()
{
    int i;
    node *new = malloc(sizeof(node));
    new->name[0] = '\0';
    for (i = 0; i < NUMDEG; ++i)
	new->dir[i] = NULL;
    return new;
}

/*
 * Load map - loads data from file, returns pointer to root.
 * Map file contains city names separated by commas. Branches are terminated
 * by END
 */
node *loadmap(char file[])
{
    int i;
    char s[MAXSTR];			/* Holds string for manipulation */
    node *cur = NULL;
    node *new = NULL;
    node *root = NULL;
    int forward;            /* Holds node index for forward */
    float cost = 0.0;
    FILE *mfile = fopen(file, "r");

    /* Creating root node */
    cur = root = createnode();
    strcpy(root->name, "Junction");

    /* Loading in branches */
    for (i = 0; i < NUMDEG; ++i) {
        cur = root;
        forward = i;
	while ((new = loadcity(mfile)) != NULL) {
            cur->dir[forward] = new;
            new->dir[BACK] = cur;
            cur = new;
            cur->dir[FWD] = NULL;
            forward = FWD;
        }
    }
    fclose(mfile);
    return root;
}

/* Loads node name and cost. Returns NULL if END occurs */
node *loadcity(FILE *mfile)
{
    char s[MAXSTR];
    node *citynode = NULL;

    getentry(mfile, s);
    if (!strcmp(s, "END"))
        return NULL;
    citynode = createnode();
    citynode->cost = atof(s);
    getentry(mfile, s);
    strcpy(citynode->name, s);
}

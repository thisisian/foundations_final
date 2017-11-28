/**************************************************************************
 *
 * New Beginnings Foundations Final
 *
 * Authors:
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
    node *p = malloc(sizeof(node));
    p->name[0] = '\0';
    for (i = 0; i < NUMDEG; ++i)
        p->dir[i] = NULL;
    return p;
}

/*
 * Load map - loads data from file, returns pointer to root.
 * Map file contains city names separated by commas. Branches are terminated
 * by END
 */
node *loadmap(char file[]) {
    int i;
    char s[MAXSTR];
    node *cur = NULL;
    node *new = NULL;
    node *root = NULL;
    float fwdCost=0;
    float backCost=0;

#if DEBUG
    printf("---Loading Map---\n");
#endif

    FILE *mfile = fopen(file,"r");

    /* Creating root node */
    cur = root = createnode();
    strcpy(root->name, "Junction");

    /* Loading in branches */
    for (i = 0; i < NUMDEG; ++i) {
        #if DEBUG
        printf("Directon %d: ", i);
        #endif

        /* Junction to first node on branch i */
        getentry(mfile, s, &fwdCost, &backCost);
        if (!strcmp(s, "END")) {
            #if DEBUG
            printf(" - END\n");
            #endif
            continue;
        }
        new = createnode();
        strcpy(new->name, s);
	new->backCost=backCost;
	new->fwdCost=fwdCost;
        root->dir[i] = new;
        #if DEBUG
        printf(" - %s , backcost: %f, fwdCost: %f\n", new->name,
		new->backCost,new->fwdCost);
        #endif
        new->dir[BACK] = root;
        cur = new;

        /* Center nodes */
        getentry(mfile, s, &fwdCost, &backCost);
        while (strcmp(s, "END")){
            new = createnode();
            strcpy(new->name, s);
            new->backCost=backCost;
            new->fwdCost=fwdCost;
            cur->dir[FWD] = new;
            new->dir[BACK] = cur;
            cur = new;
            #if DEBUG
	    printf("name: %s, back cost:%f, next cost:%f\n",new->name,
		new->backCost,new->prevCost);
	    #endif
	    getentry(mfile, s, &fwdCost, &backCost); /* Read next entry */
        }
        /* Last node */
        cur->dir[FWD] = NULL;
        #if DEBUG
        printf(" - END\n");
        #endif
        }
        #if DEBUG
        printf("-----------------\n\n");
        #endif
        fclose(mfile);
        return root;
}

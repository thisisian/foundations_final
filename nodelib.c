
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


/*
 * Get entry - load next entry from map file into s.
 * Return 1 if EOF or newline occurs after entry is scanned.
 */
int getentry(FILE *mfile, char s[])
{
    int i;
    char c;

    for (i = 0; (c = fgetc(mfile)) != EOF && c != '\n' && c != ','; ++i)
        s[i] = c;
    s[i] = '\0';
}

/*
  * Load map - loads data from file, returns pointer to junction.
  *
  * Map file contains city names separated by commas. Branches are terminated
  * by END
  */
 node *loadmap(char file[]) {
     int i;
     node *junc = NULL;
     node *cur = NULL;
     node *new = NULL;
     char s[MAXSTR];						//FIXME s --> city?
 
     printf("---Loading Map---\n");
     FILE *mfile = fopen(file,"r");
 
     /* Creating junction node */
     cur = junc = createnode();
     strcpy(junc->name, "Junction");
 
     /* Loading in branches */
     for (i = 0; i < NUMDEG; ++i) {
         printf("Directon %d:", i);
 
         /* Junction to first node on branch i */
         getentry(mfile, s);
         if (!strcmp(s, "END")) {           /* Branch is empty */
             printf(" - END\n");
             continue;
         }
         new = createnode();
         strcpy(new->name, s);
         junc->dir[i] = new;
         printf(" - %s", new->name);
         new->dir[BACK] = junc;
         cur = new;
 
         /* Center nodes */
         getentry(mfile, s);
         while (strcmp(s, "END")){
             new = createnode();
             strcpy(new->name, s);
             cur->dir[FWD] = new;
             new->dir[BACK] = cur;
             cur = new;
             getentry(mfile, s); /* Read next entry */
	 }
         /* Last node */
         cur->dir[FWD] = NULL;
         printf(" - END\n");
     }
     printf("-----------------\n\n");
     return junc;
     fclose(file);
 }
 
 /* Create node - create and initialize node, return pointer to node */
 node * createnode()
 {
     int i;
     node *p = malloc(sizeof(node));
     p->name[0] = '\0';
     for (i = 0; i < NUMDEG; ++i)
         p->dir[i] = NULL;
     return p;
 }
 /*
  * Find node - Brute force search for node pointer with name s[]. If found,
  * direction is stored in dir and a pointer to the node is returned. Otherwise,
  * function dir is invalid and function returns a NULL.
  */
 node * findnode(char s[], node *junc, int *dir)
 {
     int i, j;
     node *cur = NULL;
 
     for (i = 0; i < NUMDEG; ++i) {
         if ((cur = junc->dir[i]) == NULL)    /* direction points to NULL */
             continue;
         *dir = i;
         while (cur->dir[FWD] != NULL) {
             if (!strcmp(cur->name, s)) {
                 printf("Found %s\n", cur->name);
                 return cur;
             }
             cur = cur->dir[FWD];
         }
         if (!strcmp(cur->name, s)) {
             printf("Found %s\n", cur->name);
             return cur;
         }
         cur = junc;
     }
     return NULL;
 }

/*
   * Get direction name. Takes an input variable and saves name into s.
   */

  void getdirname(int dir, char s[]) {
      if (dir == 0) 
          strcpy(s, "North");
      else if (dir == 1)
          strcpy(s, "East");
      else if (dir == 2)
          strcpy(s, "South");
      else if (dir == 3)
          strcpy(s, "West");
      else 
          printf("getdirname: invalid direction");
  }


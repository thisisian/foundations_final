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
 * header.h - Header file. Contains includes, defines, typedefs and function
 * prototypes.
 *
 **************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMDEG 4           /* Degree of center node */
#define MAXSTR 100         /* Max length of string array */
#define BACK 0             /* Direction towards root */
#define FWD 1              /* Direction away from root */

                           /*
                            * Note: junction node will not use BACK and FWD,
                            * but the branch number from 0 to NUMDEG. All
                            * functions involving node traversal will reflect
                            * the fact that the junction will have numbered
                            * branches, while the children will have only BACK
                            * and FWD used, despite the junction also having
                            * the same struct as the other nodes.
                            */

#define DEBUG 0            /* Debugging mode: 1 to enable, 0 to disable */


/** Typedefs **/
typedef struct node {
    char name[MAXSTR];
    struct node *branch[NUMDEG];
    float cost;
} node;

typedef struct stack_element {
    node * payload;
    struct stack_element *prev;
} stack_element;

/** Function Prototypes **/

/* Stack related functions - stack.c */
node *pop(stack_element **stackaddr);
void push(node * pnode, stack_element **stackaddr);
node *peek(stack_element *stack);

/* Map-generation functions - mapgen.c */
node *createnode();
node *loadmap(char file[]);
node *loadcity(FILE *mfile);

/* Path finding functions - pathfind.c */
stack_element *getpath(char start[], char end[], node *junc, float *cost);
node *findnode(char s[], node *junc, int *branchindex);
void getbranchname(int dir, char s[]);

/* Utility functions - util.c */
void getstr(char s[]);
void formatinput(char s[], int maxlen);
int getentry(FILE *mfile, char s[]);
void printmap(node *root);
void printPath(stack_element * stack, char end[], float cost);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMDEG 4            /* Degree of center node */
#define MAXSTR 100          /* Max length of string array */
#define BACK 0              /* Direction towards root */
#define FWD 1               /* Direction away from root */

                            /*
                             * Note: junction node will not use BACK and FWD,
                             * but the branch number from 0 to NUMDEG. All
                             * functions involving node traversal will reflect
                             * the fact that the junction will have numbered
                             * branches, while the children will have only BACK
                             * and FWD used, despite the junction also having
                             * the same struct as the other nodes.
                             */

#define DEBUG 1  	    /* Debugging mode: 1 to enable, 0 to disable */


/* Typedefs */
typedef struct node {
    char name[MAXSTR];
    struct node *dir[NUMDEG];
    float prevCityCost;
    float nextCityCost;
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
void printstack(stack_element * stack, char end[]);

/* Map-generation functions - mapgen.c */
node *createnode();
node *loadmap(char file[]);
stack_element *getpath(char start[], char end[], node *junc);

/* Path finding functions - pathfind.c */
void getstr(char s[], int maxlen);
node *findnode(char s[], node *junc, int *dir);
void getbranchname(int dir, char s[]);

/* Utility functions - util.c */
void formatinput(char s[], int maxlen);
int getentry(FILE *mfile, char s[], float *fwdCost, float *backCost);
void debug_traversal(void);
void printmap(node *root);

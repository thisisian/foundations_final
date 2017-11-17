#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMDEG 4            /* Degree of center node */
#define MAXSTR 100          /* Max length of string array */
#define BACK 0              /* Direction towards root */
#define FWD 1               /* Direction away from root */

#define DEBUG 0 	    /* Debugging mode: 1 to enable, 0 to disable */	

/* Typedefs */
typedef struct node {
    char name[MAXSTR];
    struct node *dir[NUMDEG];
} node;

typedef struct stack_element {
    node * node;
    struct stack_element *prev;
} stack_element;

/** Function Prototypes **/

/* Stack related functions */
node *pop(stack_element **stackaddr);
void push(node * pnode, stack_element **stackaddr);
node *peek(stack_element *stack);
void printstack(stack_element * stack, char end[]);

/* Map-related functions */
node *createnode();
node *loadmap(char file[]);
stack_element *getpath(char start[], char end[], node *junc);

/* Searching Related */
void getstr(char s[], int maxlen);
node *findnode(char s[], node *junc, int *dir);
void getbranchname(int dir, char s[]);

/* Utiltiy */
void formatinput(char s[]);
int getentry(FILE *mfile, char s[]);
void debug_traversal(void);
void printmap(node *root);


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMDEG 4            /* Degree of center node */
#define MAXSTR 100          /* Max length of string array */
#define BACK 0              /* Direction towards junction */
#define FWD 1               /* Direction away from function */

#define DEBUG 	 	    /* Add value to enable debugging mode, used with ifdef statements */

/* Typedefs */
typedef struct node {
    char name[MAXSTR];
    struct node *dir[NUMDEG];
} node;

typedef struct stack_element {
    node * node;
    struct stack_element *prev;
} stack_element;

/* Function Prototypes */
node *createnode();
int getentry(FILE *mfile, char s[]);
node *loadmap(char file[]);
node *peek(stack_element *stack);
node *pop(stack_element **stackaddr);
void push(node * pnode, stack_element **stackaddr);
void getdirname(int dir, char s[]);
stack_element *getdirs(char start[], char end[], node *junc);
node * findnode(char s[], node *junc, int *dir);
void inputformat(char s[]);

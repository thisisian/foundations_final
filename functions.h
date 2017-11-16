#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define NUMDEG 4            /* Degree of center node */
#define MAXSTR 100          /* Max length of string array */
#define BACK 0              /* Direction towards junction */
#define FWD 1               /* Direction away from function */

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

/* Function Prototypes */
node *peek(stack_element *stack);
node *pop(stack_element **stackaddr);
node *createnode();
node *loadmap(char file[]);
node *findnode(char s[], node *junc, int *dir);
void push(node * pnode, stack_element **stackaddr);
void getdirname(int dir, char s[]);
stack_element *getdirs(char start[], char end[], node *junc);
int getentry(FILE *mfile, char s[]);
void formatinput(char s[]);
void popall(stack_element * stack, char end[]);
void strget(char s[], int maxlen);

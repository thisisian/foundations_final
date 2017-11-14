/* 
 * New Beginnings Foundations Final
 *
 * Authors:
 * Gavin [LASTNAME]
 * Lynnae Griffiths
 * Matt Krepp
 * Ian Winter
 *
 * [DESCRIPTION]
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0
#define NUMDEG 4            /* Degree of center node */
#define MAXSTR 100
#define BACK 0
#define FWD 1

/* Typedefs */

typedef struct node {
    char name[MAXSTR];
    struct node *dir[NUMDEG];
}   node;

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

/* Funciton Implementations */

/* Peek - returns top element in stack or NULL if stack is empty. */
node * peek(stack_element *stack)
{
    node *pnode = NULL;
    if (stack != NULL)
        pnode = stack->node;
    return pnode;
}

/* Pop - removes top element from stack and returns node or NULL if empty. */
node * pop(stack_element **stackaddr)
{ 
    stack_element *p = NULL;
    node *pnode = NULL;
    stack_element *stack = *stackaddr;

    if (stack != NULL) {
        p = stack->prev;
        pnode = stack->node;
        printf("Pop: %s\n", pnode->name); // testing
        free(stack);
        *stackaddr = p;
    }
    return pnode;
}

/* Push - push a node pointer to top element of stack or initalize a stack. */
void push(node * pnode, stack_element **stackaddr)
{
   stack_element *stack = *stackaddr;
   stack_element * p = (stack_element *) malloc(sizeof(stack_element));
   p->prev = NULL;
   p->node = pnode;

   printf("Push: %s\n", p->node->name);

   if (stack != NULL)
       p->prev = stack;
   *stackaddr = p;
}

/*
 * Load map - loads data from file, returns pointer to junction.
 *
 * Map file contains city names separated by commas. Branches are separated
 * by END
 */
node * loadmap(char file[]) {
    int i;
    node *junc = NULL;
    node *cur = NULL;
    node *new = NULL;
    char s[MAXSTR];

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

        /* Filling in branch i */
        getentry(mfile, s);
        while (strcmp(s, "END")){
            new = createnode();
            strcpy(new->name, s);
            cur->dir[FWD] = new;
            new->dir[BACK] = cur;
            cur = new;
            getentry(mfile, s); /* Read next entry */
            printf(" - %s", cur->name);
        }

        /* Last node */
        cur->dir[FWD] = NULL;
        printf(" - END\n");
    }
    printf("-----------------\n\n");
    return junc;
}

/* Create node - create and initialize node, return pointer to node */
node * createnode()
{
    int i;
    node *p = (node *) malloc(sizeof(node));
    p->name[0] = '\0';
    for (i = 0; i < NUMDEG; ++i)
        p->dir[i] = NULL;
    return p;
}

/*
 * Find node - scans map from junction and returns pointer to node or NULL
 * if node isn't found
 */
node * findnode(char s[], node *junc)
{
    int i, j;
    node *cur = NULL;

    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
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
 * Get directions into a stack
 */
stack_element * getdirs(char start[], char end[], node *junc)
{
    int i, j;
    char s[MAXSTR];
    stack_element * dirstack = NULL;
    node * endnode = NULL;
    node * curnode = NULL;
    node * tempnode = NULL; /* For adding name to direction */

    /* Starting at the end node */
    if ((curnode = endnode = findnode(end, junc)) ==  NULL)
        printf("Error: End node not found!\n");
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Moving towards end of branch */
    while (curnode->dir[FWD] != NULL) {
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name))
            return dirstack;
        curnode = curnode->dir[FWD];
    }
    
    /* Checking last node in branch */
    push(curnode, &dirstack);
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Dump stack and return to end node */
    while (pop(&dirstack) != NULL)
        ;
    curnode = endnode;

    /* Move towards junction */
    while (curnode->dir[BACK] != junc) {
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name))
            return dirstack;
        curnode = curnode->dir[BACK];
    }

    /* Checking last node before junction */
    push(curnode, &dirstack);
    if (!strcmp(start, curnode->name))
        return dirstack;

    /* Do brute force scan */
    for (i = 0; i < NUMDEG; ++i) {
        if ((curnode = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        getdirname(i, s);
        printf("%s",s);
        tempnode = malloc(sizeof(node));
        strcpy(tempnode->name, s);
        push(tempnode, &dirstack);
        for (j = 0; curnode->dir[FWD] != NULL; ++j) {
            push(curnode, &dirstack);
            if (!strcmp(start, curnode->name)){
                return dirstack;
                free(tempnode);
            }
            curnode = curnode->dir[FWD];
        }
        push(curnode, &dirstack);
        if (!strcmp(start, curnode->name)) {
            return dirstack;
            free(tempnode);
        }
        for (++j; j >= 0; --j)
            pop(&dirstack);
        curnode = junc;
        free(tempnode);
    }
}

/*
 * Get direction name - Takes int argument and writes corresponding direction
 * into s
 */
void getdirname(int dir, char s[])
{
    if (dir = 0)
        strcpy(s, "I-5 North");
    else if (dir = 1)
        strcpy(s, "205 East");
    else if (dir = 2)
        strcpy(s, "I-5 South");
    else if (dir = 3)
        strcpy(s, "205 West");
}


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

int main(void)
{
    stack_element *pathstack = NULL;
    node *junc = loadmap("./data");
    char start[MAXSTR];
    char end[MAXSTR];

    node *cur = NULL;
    node *node = NULL;
    int i, j;
    
    /* Testing Traversal */
    printf("--Traversal Test--\n");
    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = junc->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        for (j = 0; cur->dir[FWD] != NULL; ++j) {
            printf("%s", cur->name);
            cur = cur->dir[FWD];
        }
        printf("%s", cur->name);
        printf("\n");
        cur = junc;
    }
    printf("\n");

    /* Find the directions */
    for (;;) {
        printf("Start:\n");
        scanf("%s", start);
        printf("End:\n");
        scanf("%s", end);
        pathstack = getdirs(start, end, junc);
        printf("-----Directions-----\n%s -> %s\n", start, end);
        while ((node = pop(&pathstack)) != NULL)
            ;
    }
}

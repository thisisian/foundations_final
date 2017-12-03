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
 * util.c - Utility functions.
 *
 **************************************************************************/

#include "header.h"

/* Copies user input from stdin of maximum length maxlen into s */
void getstr(char s[])
{
    int len;

    fgets(s, MAXSTR, stdin);
    len = strlen(s);
    if (len == 0)
        s[0] = '\0';
    else if (len > 0 && (s[len - 1] == '\n'))
       s[len - 1] = '\0';
}

/* Stores a cell from a csv file into s */
int getentry(FILE * mfile, char s[])
{
    int i;
    char c;

    s[0] = '\0';
    for (i = 0; (c = fgetc(mfile)) != EOF && c != '\n' && c != ','; ++i)
	s[i] = c;
    s[i] = '\0';
}

/*
 * Convert input string to mixed case with uppercase characters following
 * whitespace. Removes leading and trailing whitespace.
 */
void formatinput(char s[], int maxlen)
{
    int readindex, writeindex;
    int inspace = 1;		/* tracks when we're in whitespace */
    char c;

    /* skip leading whitespace */
    for (readindex = 0; readindex < maxlen && isspace(s[readindex]);
	 ++readindex)
            ;
    for (writeindex = 0; (c = s[readindex]) != '\0' && readindex < maxlen;
	 ++readindex, ++writeindex) {
	if (isspace(c))
	    inspace = 1;
	if (inspace == 1 && isalpha(c)) {
	    s[writeindex] = toupper(c);
	    inspace = 0;
	} else {
	    s[writeindex] = tolower(c);
	}
    }
    --writeindex;
    /* remove trailing whitespace */
    for (; isspace(s[writeindex]); --writeindex)
        ;
    s[++writeindex] = '\0';
}

/* Pop all elements from stack and print with numbered lines. */
/* Total cost of trip is calculated and printed */

void printPath(stack_element * stack, char end[], float cost)
{
    int i;
    float dollar_cost;
    for (i = 1; strcmp(stack->payload->name, end) != 0; ++i) {
        node a = *pop(&stack);
        printf("%2d. %s\n", i, a.name);
    }
    node cur = *pop(&stack);
    printf("%2d. %s\nTotal Miles: %.1f\n\n", i, cur.name, cost);
    dollar_cost = (cost * 2.88) / 20;
    printf
        ("Assuming gas costs $2.88 per gallon, and 20 miles/gallon"
         " your trip will cost $%.2f.\n", dollar_cost);
}


void printmap(node *rootNode)
{
    int i;
    char s[MAXSTR];
    node *curNode;

    printf("--- Map ---\n");
    for (i = 0; i < NUMDEG; ++i) {
	if ((curNode = rootNode->branch[i]) == NULL)	/* branch points to NULL */
	    continue;
	getbranchname(i, s);
	printf("%s: ", s);
	while (curNode->branch[FWD] != NULL) {
	    printf("%s->", curNode->name);
	    curNode = curNode->branch[FWD];
	}
	printf("%s\n", curNode->name);
	curNode = rootNode;
    }
    printf("-----------\n\n");
}

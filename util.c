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
 * util.c - Utility functions.
 *
 **************************************************************************/

#include "header.h"

/* Copies user input from stdin of maximum length maxlen into s */
void getstr(char s[], int maxlen)
{
    int len;

    fgets(s, maxlen, stdin);
    len = strlen(s);
    if (len == 0)
        s[0] = '\0';
    else if (len > 0 && (s[len - 1] == '\n'))
            s[len - 1] = '\0';
}

/* Copies a cell from a csv file into s */
int getentry(FILE *mfile, char s[])
{
    int i;
    char c;

    for (i = 0; (c = fgetc(mfile)) != EOF && c != '\n' && c != ','; ++i)
        s[i] = c;
    s[i] = '\0';
}

/*
 * Convert input string to mixed case with uppercase characters following
 * whitespace. Removes leading and trailing whitespace.
 */
void formatinput(char s[], int maxlen) {
    int readindex, writeindex;
    int inspace = 1;    /* tracks when we're in whitespace */
    char c;

    /* skip leading whitespace */
    for (readindex = 0; readindex < maxlen && isspace(s[readindex])
            ; ++readindex)
        ;
    for (writeindex = 0; (c = s[readindex]) != '\0' && readindex < maxlen
         ; ++readindex, ++writeindex) {
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
    printf("[%s]\n", s);
}

void printmap(node *root)
{
    int i;
    char s[MAXSTR];
    node *cur;

    printf("--- Map ---\n");
    for (i = 0; i < NUMDEG; ++i) {
        if ((cur = root->dir[i]) == NULL)    /* direction points to NULL */
            continue;
        getbranchname(i, s);
        printf("%s:", s);
        while (cur->dir[FWD] != NULL) {
            printf("%s->", cur->name);
            cur = cur->dir[FWD];
        }
        printf("%s\n", cur->name);
        cur = root;
    }
    printf("-----------\n\n");
}

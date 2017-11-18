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

/* Stores user input from stdin of maximum length maxlen into s */
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

/* Stores a cell from a csv file */
int getentry(FILE *mfile, char s[])
{
    int i;
    char c;

    for (i = 0; (c = fgetc(mfile)) != EOF && c != '\n' && c != ','; ++i)
        s[i] = c;
    s[i] = '\0';
}

/* Convert input string to all lower, then to first letter to upper */
void formatinput(char s[]){                /* converts whole string to lower */
    for(int i = 0; i<MAXSTR; i++){
        s[i] = tolower(s[i]);
    }

    s[0] = toupper(s[0]);                  /* converts letter 0 to upper */

    for(int i = 1; i<MAXSTR; i++){	   /* converts first letter of */
        if(isalpha(s[i]) && s[i-1] == ' ') /* additional words to upper */
        s[i] = toupper(s[i]);
  }
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
        printf("%s:\n", s);
        while (cur->dir[FWD] != NULL) {
            printf("%s->", cur->name);
            cur = cur->dir[FWD];
        }
        printf("%s\n", cur->name);
        cur = root;
    }
    printf("-----------\n\n");
}

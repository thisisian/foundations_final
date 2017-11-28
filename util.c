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
int getentry(FILE *mfile, char s[],float *fwdCost,float *backCost)
{
    int i; float back, fwd;
    char c;
    char cityAndLengths[MAXSTR];
    char *cityName;
    char *fwdCostStr;
    char *backCostStr;
    const char delim[2]="^";

    // get the whole entry (city + lenghts)
    for (i = 0; (c = fgetc(mfile)) != EOF && c != '\n' && c != ','; ++i)
        cityAndLengths[i] = c;
    cityAndLengths[i] = '\0';

    backCostStr=strtok(cityAndLengths,delim);
    cityName=strtok(NULL,delim);
    fwdCostStr=strtok(NULL,delim);
    back=strtof(backCostStr,NULL);
    fwd=strtof(fwdCostStr,NULL);
    *fwdCost=fwd; *backCost=back;
    strcpy(s,cityName);
/*
    #if DEBUG
    printf("backCost: %f, fwd Cost=%f, city name: %s\n",
	*backCost, *fwdCost, s);
    #endif
*/
}

/* Convert input string to all lower, then to first letter to upper */
void formatinput(char s[], int maxlen) {
    int i, j;        /* i is read index, j is write index */
    int inspace = 1; /* tracks whether or not last character was a space */
    char c;

    for (i = 0; i < maxlen && isspace(s[i]); ++i) /* skip leading whitespace */
        ;
    for (j = 0; (c = s[i]) != '\0' && i < maxlen; ++i, ++j) {
        if (isspace(c))
            inspace = 1;
        if (inspace == 1 && isalpha(c)) {
            s[j] = toupper(c);
            inspace = 0;
        } else {
            s[j] = tolower(c);
        }
    }
    --j;
    for (; isspace(s[j]); --j) /* remove trailing whitespace */
        ;
    s[++j] = '\0';
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
        printf("%s:\n", s);
        while (cur->dir[FWD] != NULL) {
            printf("%s->", cur->name);
            cur = cur->dir[FWD];
        }
        cur = root;
    }
    printf("-----------\n\n");
}

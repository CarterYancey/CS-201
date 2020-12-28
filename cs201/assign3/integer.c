#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "integer.h"

extern void Fatal(char *,...);

integer *
newInteger(int x)
    {
    integer *p = malloc(sizeof(integer));
//    if (p == 0) Fatal("out of memory\n");
    p->value = x;
    return p;
    }

int 
getInteger(integer *v)
    {
    return v->value;
    }

int 
setInteger(integer *v,int x)
    {
    int old = v->value;
    v->value = x;
    return old;
    }

void 
displayInteger(FILE *fp,void *v)
    {
    fprintf(fp,"%d",getInteger((integer *) v));
    }

int
compareInteger(void *v,void *w)
    {
	if (v==NULL && w==NULL) return 0;
	if (v == NULL) return -1;
	if (w == NULL) return 1;
    return ((integer *) v)->value - ((integer *) w)->value;
    }

void
freeInteger(integer *v)
    {
    free(v);
    }

/*
 * Integer tester, by John C. Lusth
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "integer.h"

void Fatal(char *,...);

int
main(int argc,char **argv)
    {
    if (argc != 1) Fatal("usage: %s\n",argv[0]);

    printf("integer tester, version 2\n");
    integer *x = newInteger(2);
    printf("x is %d\n",getInteger(x));
    setInteger(x,3);
    printf("x is now ");
    displayInteger(stdout,x);
    printf("\n");
    return 0;
    }

void
Fatal(char *fmt, ...)
    {
    va_list ap;

    fprintf(stderr,"An error occured: ");
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    va_end(ap);

    exit(-1);
    }


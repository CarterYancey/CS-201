#include <stdio.h>

#ifndef __COMPARATOR_INCLUDED__
#define __COMPARATOR_INCLUDED__

typedef int (*Comparator)(void*, void*);
typedef void (*Printer)(FILE*, void*);
int intComparator(void*, void*);
int stringComparator(void*, void*);
int realComparator(void*, void*);

#define PINFINITY IN_MAX
#define NINFINITY IN_MIN

#endif

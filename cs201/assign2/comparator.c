#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int intComparator(void* x, void* y){
	int xx = *(int*)x;
	int yy = *(int*)y;
//	if (xx >= yy) return 1;
	if (xx < yy) return -1;
	if (xx == yy) return 0;
	return 1;
}

int realComparator(void* x, void* y){
	double xx = *(double*)x;
	double yy = *(double*)y;
//	if (xx >= yy) return 1;
	if (xx < yy) return -1;
	if (xx == yy) return 0;
	return 1;
}

int stringComparator(void* x, void* y){
	char* xx = (char*)x;
	char* yy = (char*)y;
//	printf("------%s %s------\n", xx, yy);
//	if (strcmp(xx, yy) > 0) return 1;
//	if (strcmp(xx, yy) == 0)return 1;
	if (strcmp(xx, yy) < 0) return -1;
	if (strcmp(xx, yy) == 0) return 0;
	return 1;
}

#include <stdio.h>
#include <stdlib.h>


typedef struct DArray{ //forward declaration of the DArray struct
	void **array;
	int capacity; //total number of slots
	int size; //number of slots filled
	void (*display)(FILE *, void *);
} DArray;

DArray *newDArray(void (*display)(FILE *fp,void *v)){
	DArray *darray = malloc(sizeof(DArray));
	darray->display = display;
	darray->capacity = 1;
	darray->size = 0;
	darray->array = malloc(sizeof(void *)); 

return darray;
}

void insertDArray(DArray *a,void *v){
	if (a->size == a->capacity){
		a->capacity *= 2;
		a->array = (void*)realloc(a->array, a->capacity * sizeof(void*));
	}
	a->array[a->size] = v;
	a->size +=1;
return;
}

void *removeDArray(DArray *a){
	void *v = a->array[a->size-1];
	a->array[a->size-1] = NULL;
	a->size -= 1;
	if (a->size * 4 < a->capacity){
		a->capacity *= 0.5;
		a->array = (void*)realloc(a->array, a->capacity * sizeof(void*));
	}
return v;
}

void *getDArray(DArray *a,int index){
	if (index < 0 || index > a->size){ 
		fprintf(stderr, "Invalid index\n"); 
		return 0;
	}
	return a->array[index];
}

void setDArray(DArray *a,int index,void *value){
	if (index == a->size)
		insertDArray(a, value);
	else a->array[index] = value;
}

int sizeDArray(DArray *a){
	return a->size;
}
void displayDArray(FILE *file,DArray *a){
	fprintf(file, "[");
	for (int x=0; x<a->size; x++){
		a->display(file, getDArray(a, x));
		if (x+1 != a->size)
			fprintf(file, ",");
	}
	fprintf(file, "][%d]", a->capacity-(a->size));
return;
}

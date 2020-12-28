#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "queue.h"
#include "integer.h"
#include "real.h"
#include "scanner.h"
#include "comparator.h"
#include "darray.h"
#include "binomial.h"

typedef int (*Comparator)(void* x ,void* y);
typedef void (*Printer)(FILE* f, void* v);

typedef struct Edge{
	int vertex1;
	int vertex2;
	int weight;
} Edge;

Edge *newEdge(int v1, int v2, int w){
	Edge *e = malloc(sizeof(Edge));
	e->vertex1 = v1;
	e->vertex2 = v2;
	e->weight = w;
	return e;
}

int compareEdge(void* x, void* y){
	if (x==NULL && y == NULL) return 0;
	if (x==NULL) return -1;
	if (y==NULL) return 1;
	Edge* xx = (Edge*)x;
	Edge* yy = (Edge*)y;
	if (xx->weight < yy->weight) return -1;
	if (xx->weight == yy->weight) return 0;
	return 1;
}
void displayEdge(FILE *fp, void *v){
	Edge *e = (Edge*)v;
	fprintf(fp,"%d,%d ; %d ", e->vertex1, e->vertex2, e->weight);
}

typedef struct Vertex{
	int number;
	int distance;
	int known;
	int prev;
	int steps;
	Binomial *edges;
} Vertex;

int compareVertex(void* x, void* y){
	if (x==NULL && y == NULL) return 0;
	if (x==NULL) return -1;
	if (y==NULL) return 1;
	Vertex* xx = (Vertex*)x;
	Vertex* yy = (Vertex*)y;
	if (xx->distance < yy->distance) return -1;
	if (xx->distance == yy->distance){
		if (xx->number < yy->number) return -1;
	}
	return 1;
}

Vertex *newVertex(int n, int d, int k, Edge *e){
	Vertex *v = malloc(sizeof(Vertex));
	v->number = n;
	v->distance = d;
	v->known = k;
	v->prev = n;
	v->steps = INT_MAX;
	v->edges = newBinomial(displayEdge, compareEdge, NULL);
	insertBinomial(v->edges, e);
	return v;
}


void BruteTesting();
void printQueue(FILE *fp, queue *Q);
void displayString(FILE *fp,void *v){
	fprintf(fp, "\"%s\"", (char*)v);
}
void displayVertex(FILE *fp, void *v){
	Vertex *vv = (Vertex*)v;
	fprintf(fp, "Num: %d Dist: %d Known: %d Prev: %d Steps: %d", vv->number,vv->distance,vv->known, vv->prev, vv->steps);
}

int main(int argc, char **argv)
{
	if (argc > 5)
		fprintf(stderr, "You should not be typing this\n");
	FILE *outfile = stdout;
	FILE *infile = fopen(argv[1], "r");
	int i1, i2;
	int maxV, minV;
	if (infile != 0)
		i1 = readInt(infile);
	maxV=i1; minV=i1;
	Binomial *VertexDistance = newBinomial(displayVertex, compareVertex, NULL);

	//Find the max and min
	while (!feof(infile)){
		i2 = readInt(infile);
		char *c = readToken(infile);
		if (strcmp(c, ";") != 0){
			c = readToken(infile);
		}
		if (i1 > maxV) maxV = i1;
		if (i2 > maxV) maxV = i2;
		if (i1 < minV) minV = i1;
		if (i2 < minV) minV = i2;
		i1 = readInt(infile);
	}
	struct Vertex *vertices[maxV+1];
	for (int x = 0; x <= maxV; x++)
		vertices[x] = NULL;
	
	//Read in the Vertices	
	fclose(infile);
	infile = fopen(argv[1], "r");
	if (infile != 0)
		i1 = readInt(infile);
	while (!feof(infile)){
		i2 = readInt(infile);
		char *c = readToken(infile);
		Edge *e;
		if (strcmp(c, ";") != 0){
			int weight = atoi(c);
			e = newEdge(i1, i2, weight);
			c = readToken(infile);
		}
		else{
			e = newEdge(i1, i2, 1);
		}
		Vertex *v1 = newVertex(i1,INT_MAX,0,e);
		Vertex *v2 = newVertex(i2,INT_MAX,0,e);
		if (vertices[i1] == NULL)
			vertices[i1] = v1;
		else
			insertBinomial(vertices[i1]->edges, extractBinomial(v1->edges));
		if (vertices[i2] == NULL)
			vertices[i2] = v2;
		else
			insertBinomial(vertices[i2]->edges, extractBinomial(v2->edges));
		i1 = readInt(infile);
	}

	//Dijkstra's
	int allFound = 0;
	vertices[minV]->distance = 0;
	vertices[minV]->steps = 0;
	int maxSteps = 0;
	insertBinomial(VertexDistance, vertices[minV]);
	while (!allFound){ allFound=1;
	while (sizeBinomial(VertexDistance)){
		Vertex *vertice = extractBinomial(VertexDistance);
		vertices[vertice->number]->known = 1;
		while (sizeBinomial(vertice->edges)){
			Edge *ee = extractBinomial(vertice->edges);
			if (ee->vertex1 == vertice->number){
				if (vertices[ee->vertex2]->known == 0 && 
				 vertice->distance + ee->weight < vertices[ee->vertex2]->distance){
					vertices[ee->vertex2]->distance = vertice->distance + ee->weight;
					vertices[ee->vertex2]->prev = vertice->number;
					vertices[ee->vertex2]->steps = vertices[vertices[ee->vertex2]->prev]->steps+1;
					if (vertices[ee->vertex2]->steps > maxSteps)
						maxSteps = vertices[ee->vertex2]->steps;
					insertBinomial(VertexDistance, vertices[ee->vertex2]);
				}
			}
			else{
				if (vertices[ee->vertex1]->known == 0 && 
				 vertice->distance + ee->weight < vertices[ee->vertex1]->distance){
					vertices[ee->vertex1]->distance = vertice->distance + ee->weight;
					insertBinomial(VertexDistance, vertices[ee->vertex1]);
					vertices[ee->vertex1]->prev = vertice->number;
					vertices[ee->vertex1]->steps = vertices[vertices[ee->vertex1]->prev]->steps+1;
					if (vertices[ee->vertex1]->steps > maxSteps)
						maxSteps = vertices[ee->vertex1]->steps;
				}
			}
		}
	}
	queue *DQ = newQueue(displayVertex);
	enqueue(DQ, NULL);
	int notFound=maxV;
	for (int s = 1; s<=maxSteps; s++){
    	for (int x = minV; x <= maxV; x++){
			if (vertices[x] != NULL){
				if (vertices[x]->steps == s)
					insertBinomial(VertexDistance, vertices[x]);
				if (vertices[x]->known == 0){
					allFound=0;
					if (x <= notFound) notFound = x;
				}
			}
		}
		while (sizeBinomial(VertexDistance))
			enqueue(DQ, extractBinomial(VertexDistance));
		enqueue(DQ, NULL);
	}
	fprintf(outfile,"0 : %d", minV);
	printQueue(outfile, DQ);

	vertices[notFound]->distance = 0;
	vertices[notFound]->steps = 0;
	maxSteps = 0;
	insertBinomial(VertexDistance, vertices[notFound]);
	minV=notFound;
	}
//	BruteTesting();
return 0;
}

void printQueue(FILE *fp, queue *Q){
		int level = 0;
		Vertex *v;
		while (sizeQueue(Q)){
			v = dequeue(Q);
			if (v == NULL){
				if (sizeQueue(Q) > 0)
					fprintf(fp,"\n%d :", ++level);
			}
			else{
				fprintf(fp, " %d(%d)%d", v->number,v->prev,v->distance);
				}
			}
		fprintf(fp, "\n----\n");

return;
}

//BRUTE TESTING					
void BruteTesting(){
	printf("\n\n======BRUTE TESTING=====\n\n");
	Binomial *heap = newBinomial(displayInteger, compareInteger, NULL);
	insertBinomial(heap, newInteger(4));
	insertBinomial(heap, newInteger(14));
	insertBinomial(heap, newInteger(24));
	BinomialNode *t = insertBinomial(heap, newInteger(64));
	insertBinomial(heap, newInteger(34));
	printf("=Displaying....\n");
	displayBinomial(stdout, heap);
	extractBinomial(heap);
	printf("=Displaying....\n");
	displayBinomial(stdout, heap);
	decreaseKeyBinomial(heap, t, newInteger(3));
	printf("=Displaying....\n");
	displayBinomial(stdout, heap);
return;
}

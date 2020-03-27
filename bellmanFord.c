#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "linkedList.h"

#define INFINITY 99999

//struct for the edges of the graph
struct Edge {
    struct Node *start;    //start vertex of the edge
    struct Node *end;    //end vertex of the edge
    int w;    //weight of the edge
};
typedef struct Edge Edge;

struct Node {
    char *name;// name of the city
    int totalValue;//the value that is assigned to that city
};
typedef struct Node Node;

//Graph - it consists of edges
struct Graph {
    int numNode;    //total number of nodes in the graph
    int numEdge;    //total number of edges in the graph
    struct Edge *edge;    //array of edges
    struct Node *node; //array of nodes
};
typedef struct Graph Graph;

//this takes the source city and the destination as inputs
//and finds the most efficient route between them.
void bellman_ford(Graph *graph, char *source, char *destination) {
    //creates the list to check if the algorithm has checked it
    struct strList *visited;
    visited = strlistConstructor();

    int totalVertex = graph->numNode;
    int totalEdge = graph->numEdge;

//    sets all of the the node values to infinity and sets the source to zero
    for (int i = 0; i < totalVertex; i++) {
        graph->node[i].totalValue = INFINITY;
        if (graph->node[i].name == source) {
            graph->node[i].totalValue = 0;
        }
    }

};

//reads the file and formats and stores the data in the graph
int readIn(char *file, Graph *graph) {
    FILE *filePtr;
    int lineCnt = 0;
    char buff[255];
    char compare[255];
    char ch;

    filePtr = fopen(file, "r");

    //checks if the file can be opened
    if (!filePtr) {
        printf("something went wrong file doesn't exist");
    }

    //loop counts the number of lines in a File
    while ((ch = getc(filePtr)) != EOF) {
        if (ch == '\n') {
            lineCnt++;
        }
    }
    printf("%d\n", lineCnt);

    //sets the file position back to the top
    rewind(filePtr);

    fscanf(filePtr, "%s", buff);
    printf("1 : %s\n", buff );
    fscanf(filePtr, "%s", buff);
    printf("2: %s\n", buff );
    //getw does not work here as it only get an int
    fscanf(filePtr, "%s\n", buff);
    printf("distance is : %s\n", buff);

    //loop that reads the entire file and places the data.
    //also checks to see if it has read the entire file
    for (int i = 1; i < lineCnt; i++) {
        fscanf(filePtr, "%s", buff);
//      graph->edge[i].start->name = buff;
//      checks if city in node array already
        for (int j = 0; j <= graph->numNode; j++) {
            printf("hello");
            if(strcmp(graph->node[j].name, buff) == 0){
                graph->edge[i].start = &graph->node[j];
                j = graph->numNode;

            } else if ((strcmp(graph->node[j].name, buff) != 0) && j == graph->numNode){
                graph->node[j].name = buff;
                graph->edge[i].start = &graph->node[j];
                graph->numNode++;
            }

        }

//Need to add a find if city already added to nodes

        fscanf(filePtr, "%s", buff);
        printf("end is %s\n",buff);
        for (int k = 0; k <= graph->numNode; k++) {
            printf("in K \n");
            if (strcmp(graph->node[k].name, buff) == 0) {
                graph->edge[i].end = &graph->node[k];
                k <= graph->numNode;
            } else if ((strcmp(graph->node[k].name, buff) != 0) && k == graph->numNode) {
                graph->node[k].name = buff;
                graph->edge[i].end = &graph->node[k];
                graph->numNode++;
            }
        }

        printf("reading number");
        fscanf(filePtr, "%s", buff);
        graph->edge[i].w = atoi(buff);
        graph->numEdge++;

    }
    return 0;

};

int main(void) {
    struct Graph *g = (struct Graph *) malloc(sizeof(struct Graph));
    g->numNode = 0;
    g->numEdge = 0;

    g->edge = (struct Edge *) malloc(g->numEdge * sizeof(struct Edge));
    g->node = (struct Node *) malloc(g->numNode * sizeof(struct Node));

    readIn("energy", g);
    printf("name %s\n", g->node[0].name);
    printf("value of city %d\n", g->node[0].totalValue);
    printf("from edge %s\n", g->edge[0].start->name);
    printf("numEdge is %d\n", g->numEdge);


//    bellman_ford(g, "york", "leeds");


    return 0;
}
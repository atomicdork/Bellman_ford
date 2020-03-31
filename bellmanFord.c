#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define INFINITY 99999

//struct for the edges of the graph
struct Edge {
    char start[255];   //start vertex of the edge
    char end[255];    //end vertex of the edge
    int w;    //weight of the edge
};
typedef struct Edge Edge;

struct Node {
    char name[255];// name of the city
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

void numOfLines(char *file, Graph *graph){
    int lineCnt = 0;
    char ch;
    FILE *filePtr;
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

    graph->numEdge = lineCnt;

    //sets the file position back to the top
    rewind(filePtr);
    fclose(filePtr);
};

//this takes the source city and the destination as inputs
//and finds the most efficient route between them.
void bellman_ford(Graph *graph, char *source, char *destination) {
    //creates the list to check if the algorithm has checked it
    struct strList *visited;

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

    char buff[255];
    char compare[255];


    filePtr = fopen(file, "r");

    //checks if the file can be opened
    if (!filePtr) {
        printf("something went wrong file doesn't exist");
    }

//loop that places data into structure from the file
    for (int i = 0; i < graph->numEdge - 1; i++) {
        fscanf(filePtr, "%s" "%s" "%d", &graph->edge[i].start, &graph->edge[i].end, &graph->edge[i].w);
    }
    printf("%d\n", graph->edge[5].w);
//Need to add a find if city already added to nodes
    for (int j = 0; j < graph->numEdge; j++){
        for (int k = 0; k < graph->numNode; k++){
            printf("H");

        }
    }


};


int main(void) {
    struct Graph *g = (struct Graph *) malloc(sizeof(struct Graph));

    g->numNode = 0;
    g->numEdge = 0;

    numOfLines("energy", g);

    g->edge = (struct Edge *) malloc(g->numEdge * sizeof(struct Edge));
    g->node = (struct Node *) malloc(g->numNode * sizeof(struct Node));

    readIn("energy", g);



//    bellman_ford(g, "york", "leeds");


    return 0;
}
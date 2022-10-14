#ifndef ASTAR_H
#define ASTAR_H
#include <stdio.h>
#include <stdlib.h>

#define MAP_ROWS 15
#define MAP_COLS 19

typedef struct Pair{
    int pairRow;
    int pairCol;
}Pairs;
typedef struct Nodes{
    struct Pair parents;
    int traversable;
    int inVisited;
    int inQueue;
    int fScore;
    int gScore;
    int hScore;
}Nodes;

typedef struct Path{
    struct Pair pair;
}Paths[100];
volatile static Nodes nodesArray[MAP_ROWS][MAP_COLS];

void swap(Pairs*a, Pairs *b);

void intialiseNodes(int mazeMap[MAP_ROWS][MAP_COLS]);
int astar(int mapmaze[MAP_ROWS][MAP_COLS], int startLocRow,int startLocCol, int endLocRow, int endLocCol);
#endif
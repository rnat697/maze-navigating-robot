#ifndef ASTAR_H
#define ASTAR_H
#include <stdio.h>

#define MAP_ROWS 15
#define MAP_COLS 19


void intialiseNodes(int mazeMap[MAP_ROWS][MAP_COLS]);
int astar(int map[MAP_ROWS][MAP_COLS], int startLocRow,int startLocCol, int endLocRow, int endLocCol);
#endif
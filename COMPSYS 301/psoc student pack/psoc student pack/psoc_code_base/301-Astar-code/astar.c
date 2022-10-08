#include "astar.h"

typedef struct Pair{
    int pairRow;
    int pairCol;
}Pairs;
typedef struct Nodes{
    struct Pair parents;
    int traversable;
    int inVisited;
    int fScore;
    int gScore;
    int hScore;
}Nodes[MAP_ROWS][MAP_ROWS];

typedef struct Path{
    struct Pair pair;
}Paths[1000];
volatile static Nodes nodesArray;


// --- Priority queue implementation modified from https://www.programiz.com/dsa/priority-queue
int size = 0;
void swap(Pairs*a, Pairs *b) {
  Pairs temp = *b;
  *b = *a;
  *a = temp;
}

// Heapify the queue in order of minimum at the top of queue
void heapify(Paths array, int size, int i) {
  if (size == 1) {
    printf("Single element in the heap");
  } else {
    // Find the smallest value
    int smallest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    // Use locations at smallest, L and R to find smallest Fscore in nodesArray
    int l_row = array[l].pair.pairRow;
    int l_col = array[l].pair.pairCol;
    int small_row = array[smallest].pair.pairRow;
    int small_col = array[smallest].pair.pairCol;
    int r_row = array[r].pair.pairRow;
    int r_col = array[r].pair.pairCol;

    // Find Fscores
    int l_fscore = nodesArray[l_row][l_col].fScore;
    int r_fscore = nodesArray[r_row][r_col].fScore;
    int small_fscore = nodesArray[small_row][small_col].fScore;

    if (l < size && l_fscore < small_fscore)
      smallest = l;
    if (r < size && r_fscore < small_fscore)
      smallest = r;


    // Swap and continue heapifying if root is not smallest
    if (smallest != i) {
      swap(&array[i].pair, &array[smallest].pair);
      heapify(array, size, smallest);
    }
  }
}

// Function to insert an element into the tree
void enqueue(Paths array, Pairs newLoc) {
  if (size == 0) {
    array[0].pair = newLoc;
    size += 1;
  } else {
    array[size].pair = newLoc;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

// Function to remove first element of the queue
Pairs dequeue(Paths array) {
    Pairs locAtTop;
    locAtTop.pairRow = array[0].pair.pairRow;
    locAtTop.pairCol = array[0].pair.pairCol;

    swap(&array[0].pair, &array[size - 1].pair);
    size -= 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
    heapify(array, size, i);
    }

    return locAtTop;
}
//--- End of priority queue ---
void intialiseNodes(int mazeMap[MAP_ROWS][MAP_COLS]){
    for(int row=0; row<MAP_ROWS; row++){
        for(int col=0; col<MAP_COLS; col++){
            nodesArray[row][col].parents.pairRow = -1;
            nodesArray[row][col].parents.pairCol = -1;

            if(mazeMap[row][col] == 1){
                nodesArray[row][col].traversable = 0;
            }else{
                nodesArray[row][col].traversable = 1;
            }
            nodesArray[row][col].inVisited =  0;
            nodesArray[row][col].fScore = 0;
            nodesArray[row][col].gScore = 0;
            nodesArray[row][col].hScore = 0;
        }
    }
}

int astar(int map[MAP_ROWS][MAP_COLS], int startLocRow,int startLocCol, int endLocRow, int endLocCol){
    Paths queue;
    Paths visitedList;
    Paths steps;
    intialiseNodes(map);

    queue[0].pair.pairRow = startLocRow;
    queue[0].pair.pairCol = startLocCol;
    int prevFscore = 2000;
    int currentGcost = 0;
    int stepNum = 0;
    Pairs visiting;
    visiting.pairRow = -1;
    visiting.pairCol = -1;

    //while(visiting[0] != endLocRow && visiting[1] != endLocCol){
       visiting =  dequeue(queue);
       //printf("visiting: %d,%d",visiting.pairRow, visiting.pairCol);

    //}
    return 0;
}

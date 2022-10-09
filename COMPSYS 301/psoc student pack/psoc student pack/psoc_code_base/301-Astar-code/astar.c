#include "astar.h"


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
    int l_fscore = nodesArray[l_col][l_row].fScore;
    int r_fscore = nodesArray[r_col][r_row].fScore;
    int small_fscore = nodesArray[small_col][small_row].fScore;

    // Compare Fscores to find smallest
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
            nodesArray[col][row].parents.pairRow = -1;
            nodesArray[col][row].parents.pairCol = -1;

            if(mazeMap[col][row] == 1){ // Wall
                nodesArray[col][row].traversable = 0;
            }else{
                nodesArray[col][row].traversable = 1; // traversable path
            }
            nodesArray[col][row].inVisited =  0;
            nodesArray[col][row].inQueue =  0;
            nodesArray[col][row].fScore = 2000;
            nodesArray[col][row].gScore = 0;
            nodesArray[col][row].hScore = 0;
        }
    }
}

// calculating H score using Manhattan Distance 
void calculateHScore(Pairs current, Pairs target){
    int xloc = current.pairRow;
    int yloc = current.pairCol;
    nodesArray[yloc][xloc].hScore = abs(xloc-target.pairRow) + abs(yloc-target.pairCol);
}

// Calculating G score  
// G score is the movement score from the start point to current point. We
// add to the current cost by one each time we move away from start point.
void calculateGScore(Pairs currentpos,int currentcost){
    int xloc = currentpos.pairRow;
    int yloc = currentpos.pairCol;
    nodesArray[yloc][xloc].gScore = currentcost +1;
}

int astar(int map[MAP_ROWS][MAP_COLS], int startLocRow,int startLocCol, int endLocRow, int endLocCol){
    Paths queue;
    Paths visitedList;
    Paths steps;
    intialiseNodes(map);
    Pairs target;
    target.pairRow = endLocRow-1;
    target.pairCol = endLocCol-1;
    
    queue[0].pair.pairRow = startLocRow-1;
    queue[0].pair.pairCol = startLocCol-1;
    int currentGcost = 0;
    int stepNum = 0;
    Pairs visiting, northNeigh,eastNeigh,southNeigh,westNeigh;
    visiting.pairRow = -1;
    visiting.pairCol = -1;
    int currentVisitedIndex = 0;
    int currentRow, currentCol;

   while(visiting.pairRow != endLocRow && visiting.pairCol != endLocCol){
      visiting =  dequeue(queue);
      printf("visiting: %d,%d\n",visiting.pairRow, visiting.pairCol);
      stepNum += 1;
      // Append to visitied list
      visitedList[currentVisitedIndex].pair.pairRow = visiting.pairRow;
      visitedList[currentVisitedIndex].pair.pairCol = visiting.pairCol;
      nodesArray[visiting.pairCol][visiting.pairRow].inVisited = 1; // set flag for being in visited list
      currentVisitedIndex++;
      
      // determine neighbours of visiting node and caluclate Fscore
      currentCol = visiting.pairCol;
      currentRow = visiting.pairRow;

      northNeigh.pairRow = currentRow;
      northNeigh.pairCol = currentCol-1;
      southNeigh.pairRow = currentRow;
      southNeigh.pairCol= currentCol+1;
      eastNeigh.pairRow = currentRow+1;
      eastNeigh.pairCol = currentCol;
      westNeigh.pairRow = currentRow-1;
      westNeigh.pairCol = currentCol;
      
      // Neighbours are S, N,E, W from the current location
      Paths neighbours = {southNeigh,northNeigh,eastNeigh,westNeigh};

      //calculate Fscore if neighbour is not in closed list (visitedList --> ie visted array)
      // and not in open list (queue) and is not a wall
      for(int i=0; i<4;i++){
        Pairs adjacentPos; 
        adjacentPos = neighbours[i].pair;
        int row = adjacentPos.pairRow;
        int col = adjacentPos.pairCol;
        int newFscore = 0;
        int oldFscore;
        int currentGScore = nodesArray[col][row].gScore;
        printf("Adjacent: %d,%d\n",adjacentPos.pairRow, adjacentPos.pairCol);
        
        //not a wall and has not been visited
        if((row > 0)&&(col>0)&&(nodesArray[col][row].traversable == 1) && (nodesArray[col][row].inVisited) == 0){
          // check if open list (queue) does not contain current neighbouring position
          if(nodesArray[col][row].inQueue == 0){
            printf("Enqueuing: %d,%d\n",row,col );
            //calculate Fscore, Gscore and Hscore
            // Fscore = Gscore + Hscore
            calculateHScore(adjacentPos,target);
            calculateGScore(adjacentPos,currentGcost);
            nodesArray[col][row].fScore = nodesArray[col][row].gScore + nodesArray[col][row].hScore;

            enqueue(queue,adjacentPos);
            
            nodesArray[col][row].parents = adjacentPos; // add parent for the neighbouring node

          }else{// if it is already in open list update fscore if needed and update parent
            oldFscore = nodesArray[col][row].fScore;
            calculateHScore(adjacentPos,target);
            calculateGScore(adjacentPos,currentGcost);
            newFscore = nodesArray[col][row].gScore + nodesArray[col][row].hScore;

            //check if new Fscore is smaller than old Fscore, iif so update Fscore value
            if(newFscore < oldFscore){
                nodesArray[col][row].fScore = newFscore;
                nodesArray[col][row].parents = adjacentPos; // update parent node of neighbour to current node
            }
          }
        }
      }
   }
    return 0;
}

#include "astar.h"

// --- Priority queue implementation modified from https://www.programiz.com/dsa/priority-queue
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
    
    if(l_row < MAP_ROWS && l_col < MAP_COLS && r_row < MAP_ROWS && r_col < MAP_COLS && l_row > 0 && l_col >0 && r_col>0 && r_row>0){

      // Find Fscores
      int l_fscore = nodesArray[l_row][l_col].fScore;
      int r_fscore = nodesArray[r_row][r_col].fScore;
      int small_fscore = nodesArray[small_row][small_col].fScore;

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
}

// Function to insert an element into the tree
void enqueue(Paths array, Pairs newLoc) {
  if (size == 0) {
    array[0].pair = newLoc;
    size += 1;
  } else if(size < 0){
    array[0].pair = newLoc;
    size = 0;
  }
  else {
    array[size].pair = newLoc;
    size += 1;
    for (int i = size / 2 - 1; i >= 0; i--) {
      heapify(array, size, i);
    }
  }
}

// Function to remove first element of the queues
Pairs dequeue(Paths array) {
    Pairs locAtTop;
    locAtTop.pairRow = array[0].pair.pairRow;
    locAtTop.pairCol = array[0].pair.pairCol;
    printf("Top of queue: %d, %d \n", locAtTop.pairRow, locAtTop.pairCol);

    swap(&array[0].pair, &array[size - 1].pair);
    size -= 1;
    if (size < 0){
      size = 0;
    }
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

            if(mazeMap[row][col] == 1){ // Wall
                nodesArray[row][col].traversable = 0;
            }else{
                nodesArray[row][col].traversable = 1; // traversable path
            }
            nodesArray[row][col].inVisited =  0;
            nodesArray[row][col].inQueue =  0;
            nodesArray[row][col].fScore = 2000;
            nodesArray[row][col].gScore = 0;
            nodesArray[row][col].hScore = 0;
        }
    }
}

// calculating H score using Manhattan Distance 
void calculateHScore(Pairs current, Pairs target){
    int xloc = current.pairCol;
    int yloc = current.pairRow;
    nodesArray[yloc][xloc].hScore = abs(xloc-target.pairRow) + abs(yloc-target.pairCol);
}

// Calculating G score  
// G score is the movement score from the start point to current point. We
// add to the current cost by one each time we move away from start point.
void calculateGScore(Pairs currentpos,int currentcost){
    int xloc = currentpos.pairCol;
    int yloc = currentpos.pairRow;
    nodesArray[yloc][xloc].gScore = currentcost +1;
}

void astar(int mapmaze[MAP_ROWS][MAP_COLS], int startLocRow,int startLocCol, int endLocRow, int endLocCol){
    Paths queue;
    Paths visitedList;
    Paths steps;

    intialiseNodes(mapmaze);
    Pairs target, start;
    target.pairRow = endLocRow-1;
    target.pairCol = endLocCol-1;
    start.pairCol = startLocRow-1;
    start.pairRow = startLocRow-1;
    
    queue[0].pair.pairRow = startLocRow-1;
    queue[0].pair.pairCol = startLocCol-1;
    int currentGcost = 0;
    int stepNum = 0;
    Pairs visiting, northNeigh,eastNeigh,southNeigh,westNeigh;
    visiting.pairRow = -1;
    visiting.pairCol = -1;
    int currentVisitedIndex = 0;
    int currentRow, currentCol;

   while(!((visiting.pairRow == target.pairRow) && (visiting.pairCol == target.pairCol))){
      printf("Size of queue: %d \n", size);
      visiting =  dequeue(queue);
      printf("Size of queue after dequeue: %d \n", size);
      printf("visiting (in matlab format [col][row]): %d,%d\n", visiting.pairCol+1,visiting.pairRow+1);
      stepNum += 1;
      // Append to visitied list
      visitedList[currentVisitedIndex].pair.pairRow = visiting.pairRow;
      visitedList[currentVisitedIndex].pair.pairCol = visiting.pairCol;
      nodesArray[visiting.pairRow][visiting.pairCol].inVisited = 1; // set flag for being in visited list
      currentVisitedIndex++;
      
      // determine neighbours of visiting node and caluclate Fscore
      currentCol = visiting.pairCol;
      currentRow = visiting.pairRow;

      northNeigh.pairRow = currentRow-1;
      northNeigh.pairCol = currentCol;
      southNeigh.pairRow = currentRow+1;
      southNeigh.pairCol= currentCol;
      eastNeigh.pairRow = currentRow;
      eastNeigh.pairCol = currentCol+1;
      westNeigh.pairRow = currentRow;
      westNeigh.pairCol = currentCol-1;
      
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
        int oldFscore = 2000;
        int currentGScore = nodesArray[row][col].gScore;
        //printf("Adjacent: %d,%d\n", adjacentPos.pairCol,adjacentPos.pairRow);
        
        //not a wall and has not been visited
        if((row > 0)&&(col>0) && (row < MAP_ROWS) && (col<MAP_COLS)){
          if((nodesArray[row][col].traversable == 1) && (nodesArray[row][col].inVisited == 0)){
            // check if open list (queue) does not contain current neighbouring position
            if(nodesArray[row][col].inQueue == 0){
              printf("Enqueuing: %d,%d\n",col,row);
              //calculate Fscore, Gscore and Hscore
              // Fscore = Gscore + Hscore
              calculateHScore(adjacentPos,target);
              calculateGScore(adjacentPos,currentGcost);
              nodesArray[row][col].fScore = nodesArray[row][col].gScore + nodesArray[row][col].hScore;

              enqueue(queue,adjacentPos);
              nodesArray[row][col].inQueue == 1;
              
              nodesArray[row][col].parents.pairRow = visiting.pairRow; // add parent for the neighbouring node
              nodesArray[row][col].parents.pairCol = visiting.pairCol;

            }else{// if it is already in open list update fscore if needed and update parent
              oldFscore = nodesArray[row][col].fScore;
              calculateHScore(adjacentPos,target);
              calculateGScore(adjacentPos,currentGcost);
              newFscore = nodesArray[row][col].gScore + nodesArray[row][col].hScore;

              //check if new Fscore is smaller than old Fscore, iif so update Fscore value
              if(newFscore < oldFscore){
                  nodesArray[row][col].fScore = newFscore;
                  nodesArray[row][col].parents.pairCol = visiting.pairCol; // update parent node of neighbour to current node
                  nodesArray[row][col].parents.pairRow = visiting.pairRow;
              }
            }
            printf("Adjacent: (%d,%d), Parents: (%d,%d)\n", adjacentPos.pairCol+1,adjacentPos.pairRow+1,nodesArray[row][col].parents.pairCol+1,nodesArray[row][col].parents.pairRow+1);
          }
        }
      }
   }

    
    struct Pair currentNode;
    struct Pair parentNode;
    Paths reversedArray;
    int index = 0;
    currentNode.pairCol = target.pairCol;
    currentNode.pairRow = target.pairRow;
    reversedArray[index].pair = target;
    index = 1;

    while(!(currentNode.pairRow == start.pairRow && currentNode.pairCol == start.pairCol)){
      //printf("current reversed Nodes: (%d,%d)\n", currentNode.pairCol+1,currentNode.pairRow+1);
      parentNode = nodesArray[currentNode.pairRow][currentNode.pairCol].parents;
      //printf("parent Node: (%d,%d)\n",parentNode.pairCol+1,parentNode.pairRow+1);

      reversedArray[index].pair = parentNode;
      currentNode.pairCol = parentNode.pairCol;
      currentNode.pairRow = parentNode.pairRow;
      index++;

    }

    
    int i = 0;
    printf("Final Path\n");
    for(int j=index; j--; j>=0){
      Pairs node = reversedArray[j].pair;
      finalPath[i].pair = node;
      printf("(%d,%d)\n", node.pairCol+1,node.pairRow+1);
      i++;
    }



      
    // currentNode = targetlocation;
    // parentNode = [-1,-1]; % initialised parent node
    // reversedPath = {};
    // checkStart = 0;
    // reversedPath = append(reversedPath,currentNode); % add target to reversed path list
    
    // while(checkStart ~= 1)
    //     parentNode = parents{currentNode(1),currentNode(2)}; % find parent node associated with current node
    //     reversedPath = append(reversedPath,parentNode); % add to reversed path list
    //     currentNode = parentNode; % for next iteration
    //     checkStart = (currentNode(1) == startlocation(1) && currentNode(2)== startlocation(2));
    // end
    // retsteps = flip(reversedPath); % flips order of elements to make a path to go from start to target. 
    
    
}

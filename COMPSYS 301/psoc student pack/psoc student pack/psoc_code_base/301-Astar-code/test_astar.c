#include "map_2.h"
#include "astar.h"

int arrayPointer;
volatile static int size;
int result[10000];

enum direction{NORTH, SOUTH, WEST, EAST};

    
enum direction calculateDirection(int currentCol, int currentRow, int nextCol, int nextRow) {
    
    
    if ((nextCol == currentCol + 1) && (nextRow == currentRow)) {
        //must be going EAST
        return EAST;
    } else if ((nextCol == currentCol - 1) && (nextRow == currentRow)) {
        //must be going WEST
        return WEST;
    } else if ((nextCol == currentCol) && (nextRow == currentRow + 1)) {
        //must be going NORTH
        return SOUTH;
    } else if ((nextCol == currentCol) && (nextRow == currentRow - 1)) {
        //must be going SOUTH
        return NORTH;
    }
}

void findDirections()
{
    //declare arraypointer
    arrayPointer = 0;
    size = finalArrayIndex;
    int ind =0;
    //declare result array
    //result[size];
    //initializeFinalArray
    //initializeFinalArray();
    
    //current coordinate
        int currentCol = finalPath[arrayPointer].pair.pairCol;
        int currentRow = finalPath[arrayPointer].pair.pairRow;
    
     //next coordinate
        int nextCol = finalPath[arrayPointer + 1].pair.pairCol;
        int nextRow = finalPath[arrayPointer + 1].pair.pairRow;
    
    //record last direction
    enum direction lastdir;


    //calculate initial direction
    enum direction dir = calculateDirection(currentCol, currentRow, nextCol, nextRow);
    
    for (int i = 0;i<size-1;i++) {
        
        currentCol = finalPath[arrayPointer].pair.pairCol;
        currentRow = finalPath[arrayPointer].pair.pairRow;
    
     //next coordinate
        nextCol = finalPath[arrayPointer + 1].pair.pairCol;
        nextRow = finalPath[arrayPointer + 1].pair.pairRow;
        
        
        if (dir == NORTH) {
        //if col change postively turn right, if col change negatively turn left.

            if (lastdir == SOUTH) {
               
               result[ind] = 3;
               ind++;
            }

            if (lastdir != dir) {
               if (nextCol > currentCol) {
                  //record right turn
                  result[ind] = 2;
                  
               } else if (nextCol < currentCol) {
                  //record left turn
                  result[ind] = 0;
               } else {
                  //record straight
                  result[ind] = 1;
               }
               ind++;
            }
            
        } else if (dir == SOUTH) {
            //if col change postively turn left, if col change negatively turn right.

            if (lastdir == NORTH) {
               
               result[ind] = 3;
               ind++;
            }
            if (lastdir != dir) {
               if (nextCol > currentCol) {
                  //record left turn
                  result[ind] = 0;
                  
               } else if (nextCol < currentCol) {
                  //record right turn
                  result[ind] = 2;
               } else {
                  //record straight
                  result[ind] = 1;
               }
               ind++;
            }
               
        } else if (dir == WEST) {
            //if row change negatively turn right, if row change positively turn left.
            if (lastdir == EAST) {
               
               result[ind] = 3;
               ind++;
            }

         if (lastdir != dir) {
            if (nextRow > currentRow) {
                //record left turn
                result[ind] = 0;
                
            } else if (nextRow < currentRow) {
                //record right turn
                result[ind] = 2;
            } else {
                //record straight
                result[ind] = 1;
            }
            ind++;
         }
        } else {
            //if row change negatively turn left, if row change positively turn right.

            if (lastdir == WEST) {
               
               result[ind] = 3;
               ind++;
            }

            if (lastdir != dir) {
               if (nextRow > currentRow) {
                  //record right turn
                  result[ind] = 2;
                  
               } else if (nextRow < currentRow) {
                  //record left turn
                  result[ind] = 0;
               } else {
                  //record straight
                  result[ind] = 1;
               }
               ind++;
            }
        }

        lastdir = dir;
        
        //recalculate direction vector for future coordinate
        dir = calculateDirection(currentCol, currentRow, nextCol, nextRow);
        
        
        arrayPointer++;
        
    }
    
    for (int i=0;i<=ind;i++) {
        //0 - left, 1 - straight, 2- right
        printf("%d,", result[i]);
    }
    printf("\nQueue size: %d", arrayPointer + 1);
    
}

int main(){
   
   // in the format of  map [col][row]
   
   // map file, start row, start col, endrow, end col

   // start and end in format of [row][col] THIS IS WHAT WE CHANGE FOR THE DEMO
   int STARTROW = 1;
   int STARTCOL = 16;
   int TARGETROW = 1;
   int TARGETCOL = 1;

   int currentStartRow, currentStartCol, currentEndRow, currentEndCol;
   
   currentStartRow = STARTROW;
   currentStartCol = STARTCOL;


   for(int i=0; i<5; i++){
      int row = food_list[i][0];
       int col = food_list[i][1];
       
      // update current end node to the ones in the food list
      currentEndRow = row;
      currentEndCol = col;
      
      printf("Current Start - row:%d, col:%d\n", currentStartRow,currentStartCol);
      printf("Current End - row:%d, col:%d\n", currentEndRow,currentEndCol);
      // function call here 
      astar(map,currentStartRow,currentStartCol,currentEndRow,currentEndCol);
      
      // update current start nodes to the ones in the food list
      currentStartRow = row;
      currentStartCol = col;
   } 
   
   // update current end nodes to TARGET nodes
   currentEndCol = TARGETCOL;
   currentEndRow = TARGETROW;
   printf("Current Start - row:%d, col:%d\n", currentStartRow,currentStartCol);
   printf("Current End - row:%d, col:%d\n", currentEndRow,currentEndCol);
   // function call here 
   astar(map,currentStartRow,currentStartCol,currentEndRow,currentEndCol);


   printf("\nfinal Path woooooooooo");
   int finalRow, finalCol;
   // // Paths *finalArrayPointer;
   // finalArrayPointer = &finalPath;
   printf("finalPath size:%d\n",sizeof(finalPath) );
   printf("index = %d\n", finalArrayIndex);
   for(int j = 0; j<=finalArrayIndex; j++){
      finalRow = finalPath[j].pair.pairRow;
      finalCol = finalPath[j].pair.pairCol;
      printf("(%d,%d)\n", finalRow+1,finalCol+1); // formatting to reference matlab maze
   }


findDirections();

  


   return 0;
}



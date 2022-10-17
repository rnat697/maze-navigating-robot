#include "map_2.h"
#include "astar.h"
int arrayPointer;
volatile static int size;
int result[10000];

enum direction{NORTH, SOUTH, WEST, EAST};
volatile static int intersectionArray[MAP_ROWS][MAP_COLS];
    
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

      // previous co-ordinate
      int prevCol, prevRow;
    
    //record next direction
    //enum direction lastdir;


    //calculate initial direction
    enum direction dir = calculateDirection(currentCol, currentRow, nextCol, nextRow);
    
    for (int i = 0;i<size-1;i++) {
        
      currentCol = finalPath[i].pair.pairCol;
      currentRow = finalPath[i].pair.pairRow;
   
   //next coordinate
      nextCol = finalPath[i + 1].pair.pairCol;
      nextRow = finalPath[i + 1].pair.pairRow;
      
      
        
      if (dir == NORTH) {
      //if col change postively turn right, if col change negatively turn left.


         if (nextCol > currentCol) {
               //record right turn
               result[arrayPointer] = 2;
               arrayPointer++;
               
         } else if (nextCol < currentCol) {
               //record left turn
               result[arrayPointer] = 0;
               arrayPointer++;
         } else {
               if (prevCol  == nextCol && prevRow == nextRow) {
                  // record U
                  //if(intersectionArray[currentRow][currentCol] == 1){ // check if its actually an intersection
                     result[arrayPointer] = 3;
                     arrayPointer++; 
                  //}
               }
               //record straight
               else if(intersectionArray[currentRow][currentCol] == 1){
                  result[arrayPointer] = 1;
                  arrayPointer++;
               }
         }
         
      } else if (dir == SOUTH) {
         //if col change postively turn left, if col change negatively turn right.


         if (nextCol > currentCol) {
               //record left turn
               result[arrayPointer] = 0;
               arrayPointer++;
               
         } else if (nextCol < currentCol) {
               //record right turn
               result[arrayPointer] = 2;
               arrayPointer++;
         } else {

               if (prevCol  == nextCol && prevRow == nextRow) {
                  // uturn
                  //if(intersectionArray[currentRow][currentCol] == 1){ // check if its actually an intersection
                     result[arrayPointer] = 3;
                     arrayPointer++; 
                 // }
               }
               //record straight
               else if(intersectionArray[currentRow][currentCol] == 1){
                  result[arrayPointer] = 1;
                  arrayPointer++;
               }
         }
         
      } else if (dir == WEST) {
         //if row change negatively turn right, if row change positively turn left.
   


         if (nextRow > currentRow) {
               //record left turn
               result[arrayPointer] = 0;
               arrayPointer++;
               
         } else if (nextRow < currentRow) {
               //record right turn
               result[arrayPointer] = 2;
               arrayPointer++;
         } else {
               if (prevCol  == nextCol && prevRow == nextRow) { // U turn
                  // record uturn
                 // if(intersectionArray[currentRow][currentCol] == 1){ // check if its actually an intersection
                     result[arrayPointer] = 3;
                     arrayPointer++; 
                  //}
               }
               //record straight
               else if(intersectionArray[currentRow][currentCol] == 1){
                  result[arrayPointer] = 1;
                  arrayPointer++;
               }
         }
      } else {
         //if row change negatively turn left, if row change positively turn right.

         if (nextRow > currentRow) {
               //record right turn
               result[arrayPointer] = 2;
               arrayPointer++;
               
         } else if (nextRow < currentRow) {
               //record left turn
               result[arrayPointer] = 0;
               arrayPointer++;
         } else {
               
               if (prevCol  == nextCol && prevRow == nextRow) {
                  // record u turn
                  //if(intersectionArray[currentRow][currentCol] == 1){ // check if its actually an intersection
                     result[arrayPointer] = 3;
                     arrayPointer++; 
                  //}
               }
               else if(intersectionArray[currentRow][currentCol] == 1){
                   //record straight
                  result[arrayPointer] = 1;
                  arrayPointer++;
               }
         }
      }
      // update previous columns and rows
      prevRow = currentRow;
      prevCol = currentCol;

      

      //lastdir = dir;
      
      //recalculate direction vector for future coordinate
      dir = calculateDirection(currentCol, currentRow, nextCol, nextRow);
      
      
        
    }
    
    for (int i=0;i<=arrayPointer-1;i++) {
        //0 - left, 1 - straight, 2- right
        printf("%d,", result[i]);
    }
    printf("\n Direction array size: %d", arrayPointer);
    
}



void initialiseIntersectionArray(){
   // intersections are indicated with 1, normal pathway indicated with 0, walls indicated by 2

   for(int rowLoc =0; rowLoc < MAP_ROWS; rowLoc++){
      for(int colLoc = 0; colLoc<MAP_COLS; colLoc++){
         int currentLocTraversable = nodesArray[rowLoc][colLoc].traversable;
         int northLocTraversable = nodesArray[rowLoc-1][colLoc].traversable;
         int southLocTraversable = nodesArray[rowLoc+1][colLoc].traversable;
         int westLocTraversable = nodesArray[rowLoc][colLoc-1].traversable;
         int eastLocTraversable = nodesArray[rowLoc][colLoc+1].traversable;

         if(currentLocTraversable == 1){
            // Check for traversable intersections
            if(northLocTraversable == 1 && eastLocTraversable == 1){ // N + E intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(southLocTraversable==1 && eastLocTraversable ==1){ //S + E intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(northLocTraversable == 1 && westLocTraversable == 1){ // N + W intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else  if(southLocTraversable == 1 && westLocTraversable == 1){ // S + W intersection
               intersectionArray[rowLoc][colLoc] =1;
            
            }else if(southLocTraversable == 1 && westLocTraversable == 1 && eastLocTraversable == 1){ // S+W+E intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(northLocTraversable == 1 && westLocTraversable == 1 && eastLocTraversable ==1){ // N+W+E intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(northLocTraversable ==1 && southLocTraversable == 1 && eastLocTraversable == 1 && westLocTraversable == 1){ // N+S+E+W intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(northLocTraversable == 1 && westLocTraversable == 1 && southLocTraversable == 1){ // N +W+S intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else if(northLocTraversable == 1 && eastLocTraversable == 1 && southLocTraversable == 1){ // N+E+S intersection
               intersectionArray[rowLoc][colLoc] =1;

            }else{
               intersectionArray[rowLoc][colLoc] =0;
            }
         }else{
            intersectionArray[rowLoc][colLoc] = 2; // wall
         }
      }
   }
}

int main(){
   
   // in the format of  map [col][row]
   
   // map file, start row, start col, endrow, end col

   // start and end in format of [row][col] THIS IS WHAT WE CHANGE FOR THE DEMO
   // start_pos[2] = {13, 3};
   int STARTROW = 13;
   int STARTCOL = 3;
   // int TARGETROW = 1;
   // int TARGETCOL = 1;

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
      astar(map_final,currentStartRow,currentStartCol,currentEndRow,currentEndCol);
      
      // update current start nodes to the ones in the food list
      currentStartRow = row;
      currentStartCol = col;
   } 
   
   // update current end nodes to TARGET nodes
   // currentEndCol = TARGETCOL;
   // currentEndRow = TARGETROW;
   // printf("Current Start - row:%d, col:%d\n", currentStartRow,currentStartCol);
   // printf("Current End - row:%d, col:%d\n", currentEndRow,currentEndCol);
   // // function call here 
   // astar(map,currentStartRow,currentStartCol,currentEndRow,currentEndCol);
  
  initialiseIntersectionArray();
   // printf("\nINTERSECTION ARRAY");

   // for(int l = 0; l < MAP_ROWS; l++){
   //    printf("\n");
   //    for(int k=0; k<MAP_COLS; k++){
   //       printf(" %d ", intersectionArray[l][k]);
   //    }
   // }



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



#include "map_2.h"
#include "astar.h"
#include <stdio.h>


// void printEmtpyMaze();
// void combinePathWithMaze(int *map[][19], int *steps[]);
// void printMazeWithPath(int *mapWithPath[][19]);

// void printEmtpyMaze(){
//    int row, col;
//    printf("\n");
//    for ( row = 0; row < MAP_ROWS; row++ ) { // assume this is the same
//       for ( col = 0; col < MAP_COLS; col++ ) {
//          int location = map[row][col];
//          if(location == 1){
//             printf( "%c", '#');
//          }else{
//             printf(" ");
//          }
//       }
//       printf( "\n" );
//    }
// }

// // void combinePathWithMaze(int *map[][MAP_ROWS], int *steps[]){
// //    for(int i=0; i<sizeof(*steps); i++){
// //       int pathLocation[2];
// //       pathLocation[0] = *steps[i]; // idk
// //       *map[pathLocation[0]][pathLocation[1]] = i;
// //    }
// // }

// void printMazeWithPath(int *mapWithPath[][MAP_ROWS]){
//    printf("\n");
//    for ( int row = 0; row < MAP_ROWS; row++ ) { // assume this is the same
//       for ( int col = 0; col < MAP_COLS; col++ ) {
//          int location = *mapWithPath[col][row];
//          if(location == -1){
//             printf( "%c", '#');
//          }else if(location == 0){
//              printf(" ");
//          }
//          else{
//             printf("%d",location); // Found path 
//          }
//       }
//       printf( "\n" );
//    }
// }

// void printEmtpyMazeWith(int mapa[MAP_ROWS][MAP_COLS]){
//    int row, col;
//    printf("\n");
//    for ( row = 0; row < MAP_ROWS; row++ ) { // assume this is the same
//       for ( col = 0; col < MAP_COLS; col++ ) {
//          int location = mapa[col][row];
//          if(location == 1){
//             printf( "%c", '#');

//          }else{
//             printf(" ");
//          }
//       }
//       printf( "\n" );
//    }
// }
//volatile extern int finalArrayIndex;
// volatile Paths finalPath;
int main(){
   //printEmtpyMaze();
   //intialiseNodes(map);
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
   // astar(map,1,17, 13,7);
   // printEmtpyMazeWith(map);
  


   return 0;
}

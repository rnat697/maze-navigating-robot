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
int main(){
   //printEmtpyMaze();
   //intialiseNodes(map);
   // in the format of  map [col][row]
   
   // map file, start row, start col, endrow, end col
   astar(map,1,1, 13,7);
   //printEmtpyMazeWith(map);
  


   return 0;
}

#ifndef QUEEN_H
#define QUEEN_H
#include <iostream.h>
#include <iomanip.h>
#include <stdlib.h>
/**************************************************************************
*   Queen class 
*      This is you basic run of the mill 8 queens program. if solves
*      for all the answers and prints them out. It uses a strait forward
*      DFS (depth first search) so don't expect any preformace out of it.
*   TODO
*      Make it so we can do N queens.
*      Make a driver function. clean the whole thing up and make it prity
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/
class Queen{
   public:
      Queen();
      void placeQueen(int row);
      void printBoard();
      // solve-allNQueens(int n);  // sovle for a spesific size
      // solve-xNQueens(int n, int answer) // sovlve for a spesific answer
   private:
      int *board;      
      int check(int row,int col);
      int found;
};
#endif
/**************************************************************************
*   Queen
*      Constructor. it uhh constructs. really the only productive thing is
*      to set found to 0;
*   @param void
*   @return void
**************************************************************************/
Queen::Queen(){
   board = new int[9];
   int i;
   for(i = 1; i < 9; i++){ board[i] = 0; }
   found = 0;
}
/**************************************************************************
*   placeQueen
*      this is the main recursive prog that goes through and adds queens
*      to the bouard and calls itself.  Your basic DFS(depth first search) 
*   @param int col put a queent in this coloum.
*   @return void
**************************************************************************/
void Queen::placeQueen(int col){
   for(int row = 1;row < 9;row++){
      if(check(row,col)){
         board[col] = row;         
         if (col==8){ // we succesfully put one at the end
            printBoard();
         }else{
            placeQueen(col + 1); 
         }
      }   
   }
}
/**************************************************************************
*   check 
*      This is you basic check.  I would have writen some long ass O(n^2)
*      algorithm that whould go through and check every position and all
*      that crazy stuff.  But our friend the Math major (AL G.) should us
*      the quick way.  I gess math major are usefull.
* 
*         for all up to col {
*          if |row1 - row2| = |col1 - col2| then colition
*          if  col = same as any col
*         }
*   @param int row is the row we want to check
*   @param int col is the - you guessed it - the col we want to check
*   @return int 1 if is good, 0 is so sorry death to all Queens
**************************************************************************/
int Queen::check(int row,int col){
   int rr,cc;
   for(int c = 1; c < col; c++){
      rr = row - board[c];
      cc = col - c;
      if((abs(rr))==(abs(cc))) { return 0; }
   }
   for(int c = 1; c < col; c++){
      if(board[c]==row){ return 0; } 
   }
   return 1;
}
/**************************************************************************
*   printBoard 
*      it prints the board out .. a lovely array. and keeps track of 
*      how many solutions we have found
*   @param void
*   @return void
**************************************************************************/
void Queen::printBoard(){
   found++; cout << "\t" << setw(3) << found << "\t"; for(int i = 1; i < 9; i++){ cout << " " << board[i] ; } cout << "\n"; 
}
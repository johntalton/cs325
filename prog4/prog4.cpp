#include "queen.h"
/**************************************************************************
*   Main
*      Makes a new 8 queens prog and runs it
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/  
void main(){
   Queen q;

   cout << "\t    \t" << "1 2 3 4 5 6 7 8\n";
   cout << "\t\t" << "------------------\n";
   q.placeQueen(1);// 1 is the position we want to start at. it is a 
                   // good idea to start at one
   cout << "\nThanks for using EightQ by ¥NöP\n";
}
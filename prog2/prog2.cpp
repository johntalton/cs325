#include "graph.h"
#define ARBITRARY 1
#define BYSIZE    2
#define BYHIGHT   3
/**************************************************************************
*   Prog2:
*   This program is not really usefull for anything what it does though is
*      take some nodes and Union them together.. It can do a Arbitrary union
*      a union by size or a union by higth Now what all that means is it
*      combinds some nodes to make nifty trees. I worte this code for cs325
*      the arbitrary union and the find wrere writen for my cs220 class.
*      Spent about 5 hours working (10-24-98)
*
*   To preform the operations
*
*    - Union(x, y)
*    - Find(x)
*    - Display current array in the form
*        Index     1    2     3    4
*        Parent    0   0     2    3
*    - Start over (reinit value of n, size of array, and union criteria)
*    - Quit
*
*   TODO
*      Work on error checking when user enters something from the menu.
*      It seems to trought it into a infinit loop - C++ sucks
*
*   @see Graph.h
*   @version 0.1b
*   @author YNOP,jta001@coes.latech.edu
***************************************************************************/


/**************************************************************************
*   getInput is our standard way of geting input form the user. all
*      operations uses this so that we can esally change this is we decide
*      to change the behavor some day
*   @param x int the value in which to store the user inpute
*   @return void
**************************************************************************/
void getInput(int &x){
   cin >> x;
}
/**************************************************************************
*   printMenu prints the user menu with a listing of all options
*   @param void
*   @return void
**************************************************************************/
void printMenu(){
 cout << "1 Union x y\n"
      << "2 Find x\n"
      << "3 Display\n"
      << "4 StartOver\n"
      << "5 Quit\n"
      << ":";
}
/**************************************************************************
*   printGetUnion prompts the user for a node number to union
*   @param void
*   @return void
**************************************************************************/
void printGetUnion(){
   cout << "Enter node to Union: ";
}
/**************************************************************************
*   printFind prompts the user to enter a node in which we want to find
*      the parent of
*   @param void
*   @return void
**************************************************************************/
void printFind(){
   cout << "Enter a node Number and I will find the root:  ";
}
/**************************************************************************
*   printFound prints the results of a find (parentofi) on i
*   @param i int is the value we inputed to find parent of
*   @param parentofi int is the value we found to be the parent of i
*   @return void
**************************************************************************/
void printFound(int i,int parentofi){
   cout << "Found the root of " << i << " to be " << parentofi << "\n";
}
/**************************************************************************
*   printSize prompts the user to enter a new size for the graph, only
*      used when starting a new graph
*   @param void
*   @return void
**************************************************************************/
void printSize(){
  cout << "Enter the size of the graph:";
}
/**************************************************************************
*   printUnionType prompts the user to enter a union type corisponding to
*      1 = ARBITRARY, 2 = BYSIZE, 3 = BYHIGHT
*   @param void
*   @return void
**************************************************************************/
void printUnionType(){
   cout << "Enter the type of union you wish to preform:\n"
        << "   ARBITRARY  == 1\n"
        << "   BYSIZE     == 2\n"
        << "   BYHIGHT    == 3\n"
        << ":";
}
/**************************************************************************
*   quit just sais by and cleans up after the program
*   @param void
*   @return void
**************************************************************************/
void quit(){
   cout << "Thanks for using Union v0.1b by ¥NöP\n";
}
/**************************************************************************
*   StartOver creats a new graph and reutrnes it.
*   @param x const int just is the size for the new graph
*   @return g Grapph the newly created graph of size x
**************************************************************************/
Graph StartOver(const int x){
    Graph g(x);
   return g;
}
/**************************************************************************
*   Union just determans what type of union whe are doing and preformes
*      it on the graph g
*   @param g Graph is the graph we want to work on
*   @param utype int is the type of union we want to do 1,2,3
*   @param x int is the first node to union
*   @param y int is the second node to union with x
*   @return void
**************************************************************************/
void Union(Graph g, int utype,int x,int y){
   if(utype == ARBITRARY){
      g.Union(x,y);
   } else if(utype == BYSIZE){
      g.Union_by_size(x,y);
   } else if(utype == BYHIGHT){
      g.Union_by_hight(x,y);
   }
}
/**************************************************************************
*   main is the driver funtion just switch and thats all basicly
*   @param void
*   @return void
**************************************************************************/
void main(){
   int running = 1; // whether we are still running or quiting
   int i,x,y;       // your basic temp vars for user imput and such
   int utype;       // the type of union whe are curently doing 1,2,3
   printSize();
   getInput(x);
   Graph g = StartOver(x);
   printUnionType();
   getInput(utype);
   while(running){
      printMenu();
      getInput(i);
      switch(i){
         case 1: printGetUnion();getInput(x);printGetUnion();getInput(y);Union(g,utype,x,y);break;
         case 2: printFind();getInput(x);printFound(x,g.Find_parent(x));break;
         case 3: g.printGraph();break;
         case 4: printSize();getInput(y);delete &g;g = StartOver(y);printUnionType();getInput(utype);break;
         case 5: quit(); running = 0;break;
      }
   }
}
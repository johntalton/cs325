#include "graph.h"
/**************************************************************************
*   Main
*      is the front end of the MakeStronGraph function.  the Graph class
*      prints out nothing so if we want stuff on the screen we must put 
*      it there or ask graph to put it there.
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/  
void main(){
   char filename[13];
   cout << "Enter a graph file (non-comma file please):  ";
   cin.getline(filename, 12, '\n');
   cout << endl;
   Graph g(filename);
   cout << "Here is our original graph\n";
   g.printGraph(); cout << "\n";
   if(g.MakeStrongGraph()){
     cout << "Congradulation we now have a strongly conected graph:\n";
     g.printGraph();
   } else {
      cout << "So sorry this graph can not be made into a strongly connected graph\n\n";
   }
   cout << "Thanks for using StrongGraph 1.0. by ¥NöP\n";
}

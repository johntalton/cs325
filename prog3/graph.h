#ifndef GRAPH_H
#define GRAPH_H
#include <fstream.h>
#include <iostream.h>
#include <iomanip.h>
/**************************************************************************
*   Graph class 
*      The graph is read in form a file that is passed int to the 
*      constructor.  then the user can call MakeStrongGraph and 
*      if posible we will return that. if is stored as a dinamic
*      array of arrays - whith sizes stord in the 0th element.
*   TODO
*      Add int error checking while reading in the file
*      currently we destroy the old graph to make a new strongly 
*         connected graph. This is bad. we nead to preserver the old one
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/
class Graph{
   public:
      Graph(char *filename);
      int MakeStrongGraph();
      int drivedfs(int v,int b);
      void dfs(int v);
      void backwards_dfs(int v);
      void del_edge(int from, int to);
      void printGraph();
   private:
      int **graph;
      int numnodes;
      int *visited;
};
#endif
/**************************************************************************
*   Graph is the main constructor for the class. It takes int a filename
*      to read the graph from, the graph should be in the format of:
*
*         #Nodes
*         Node_1 #Edges Edge1 Edge2 ... EdgeN
*         Node_2 #Edges Edge1 Edge2 ... EdgeM
*         ...
*
*      Note that the edges are seperated by blank spaces " " and not 
*      commas.
*   @param filename *char the name of the file
*   @return void
**************************************************************************/
Graph::Graph(char *filename){
   delete graph;
   ifstream graphfile(filename,ios::in);
   graphfile >> numnodes;
   numnodes++;
   visited = new int[numnodes];
   graph = new int*  [numnodes];
   int x;
   int currentnode;
   int edge;
   int numedges;
   int i;
   int j;
   for(i = 1; i < numnodes; i++){
      graphfile >> currentnode;
      graphfile >> numedges;
      graph[currentnode] = new int [++numedges];
      graph[currentnode][0] = numedges;
      for(j = 1;j < numedges; j++){
         graphfile >> edge;
         graph[currentnode][j] = edge;
      }
   }
   graphfile.close();
}
/**************************************************************************
*   MakeStrongGraph is the main user-drive function for all this cool stuff
*      it is what does the first level of logic. This is also where we 
*      staticly (bad) set the node to start at - in this case 1
*   @param void
*   @return int whether we could do it or not 0 = fail  1 = succes
**************************************************************************/
int Graph::MakeStrongGraph(){
   if(drivedfs(1,1)){
      //printGraph();  cout << "\n";
      if(drivedfs(1,0)){
         //printGraph(); cout << "\n";  // if user wants printout he can do it
      } else {
         return 0;
         //cout << "\nSorry our second DFS failed - cannot form a Strongly Connected Graph\n";
      }      
   } else {
      return 0;
      //cout << "\nSorry our first DFS failed - cannot form a Strongly Connected Graph\n";
   }
   return 1;
}
/**************************************************************************
*   printGraph just the normal print out of a graph - real ugly nead to 
*      clean that up.
*   @param void
*   @return void
**************************************************************************/
void Graph::printGraph(){
   int i;
   int j;
   for(i = 1;i<numnodes;i++){ cout << i << "->";
      if(graph[i][0] == 1) { cout << "(no edges)"; }// we use 1 here because 1 means no nodes
      for(j = 1;j< graph[i][0];j++){
         cout << graph[i][j];
      } cout << "\n";
   } 
}
/**************************************************************************
*   drivedfs driver function for depth first search - it also plays a verry
*      larg role in checking if we visited all nodes ie we have a Strongly
*      connected graph.
*   @param v int the initial node to start from - this could trully be any
*      node in the graph but we usually start at "1"
*   @param b int a pramiter to tell dfs whether we are doing dels on the
*      link we folowed of the one oposit that.
*   @return int whether we sucsessfully preformed this dfs
**************************************************************************/
int Graph::drivedfs(int v,int b){
   int i;
   for(i = 0; i < numnodes;i++){ visited[i] = 0; }
   if(b){
      dfs(v);
   } else {
      backwards_dfs(v);
   }
   // this for loop check the visited array that was set by eather
   //   dfs or backwards_dfs to make shur it got all the nodes.
   for(i = 1; i < numnodes;i++){ if(!visited[i]) { return 0; } }
   return 1;
}
/**************************************************************************
*   dfs a recursive algorith to serch through a graph for a tree that goes
*      throught all nodes. Modified to delete all edges that are not the 
*      ones we follow
*   @param v int the node to start at
*   @return void
**************************************************************************/
void Graph::dfs(int v){
   int w;
   visited[v] = 1;
   for(int i = 1;i < graph[v][0];i++){//for all edges of v
      w = graph[v][i];
      if(!visited[graph[v][i]]){    // if we havent already visited that node
         //cout << v << "->" << graph[v][i] << "  ";
         dfs(w);
         del_edge(v,graph[v][i]); i--; // the i-- is because our for loop is bounded by 
      }                                //   a value that changes when we preform a del
   }
  cout << flush;
}
/**************************************************************************
*   backwards_dfs algorith to search throught a graph for a tree that goes
*      through all nodes. Modified to delete all edges that are the ones 
*      we follow
*   @param v int the node to start at
*   @return void
**************************************************************************/
void Graph::backwards_dfs(int v){
   int w;
   visited[v] = 1;
   for(int i = 1;i < graph[v][0];i++){ //for all edges of v
      w = graph[v][i];
      if(!visited[graph[v][i]]){    // if we havent already visited that node
         //cout << w << "->" << v << "  ";
         backwards_dfs(w);
         del_edge(w,v); i--; // the i-- is because our for loop is bounded by 
      }                      //   a value that changes when we preform a del
   }
  cout << flush;
}
/**************************************************************************
*   del_edge delete a edge from "from" to "to" (good var name) It also 
*      keeps all of our counter up to date and some admin stuff like that
*   @param from int the edge that goes from "from"
*   @param to int to "to"
*   @return void
**************************************************************************/
void Graph::del_edge(int from, int to){
   int position = 0;
   int i = 1;
   while((graph[from][i] != to) && (i < graph[from][0])){i++;}position = i;//find position of node to del
   if((position != graph[from][0])){ // if the node exists
      for(i = position;i<graph[from][0]-1;i++){
         graph[from][i] = graph[from][i+1];
      }
      graph[from][0] = graph[from][0] - 1;// Dec the num of edges that come off of "from"
   }
}

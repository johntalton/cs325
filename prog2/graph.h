#ifndef GRAPH_H
#define GRAPH_H
#include <iostream.h>
#include <iomanip.h>
/**************************************************************************
*   Graph.h
*   This is you greneral lib for a graph. can do union my size hight and 
*      arbitrary.  The graph is initilized to all -1 to denote that the 
*      nodes are all single higth trees with no children. The struture is
*      that the index of the array and the values int the array are the 
*      parent of that node. If the graph is to be used with union by hight
*      the hight of the graph (starting with -1) is stored in the root node
*      and is decremented to match the number of nodes in the tree. If the
*      graph is to be used for size unions the size of the graph is stored 
*      in the root node starting with -1 and decrementing. 
*   TODO
*      Currently the graph - once a union is prfomed - is only valid to
*      be used with that union.  we eather nead 3 arrays (size,hight,arb)
*      or we could store the union type in the 0th element and only alow
*      that type of union from there on out. Not a biggy for a small prog
*      like this though.
*   @version 1.0
*   @author YNOP,jta001@coes.latech.edu
**************************************************************************/
class Graph{
   public:
      Graph(int size);
      void Union(int i, int j);
      void Union_by_size(int i, int j);
      void Union_by_hight(int i, int j);
      int Find_parent(int i);
      void printGraph();
   private:
      int *parent; // the dinaminc array that stors the graph
      int cursize; // the current size of the graph
};
#endif
/**************************************************************************
*   Graph is the constructor for a new graph of size size
*   @param size int is the size of the new graph for 1 - size
*   @return void
**************************************************************************/
Graph::Graph(int size){ 
   cursize = size + 1;
   parent = new int[size + 1];
   for(int i = 1; i < cursize; i++){ parent[i] = -1;}
}
/**************************************************************************
*   Union preformes a arbitrary union on i and j ( i is the parent of j )
*   @param i int node one to union
*   @param j int node two to union with one
*   @return void
**************************************************************************/
void Graph::Union(int i,int j){ 
   int pj = Find_parent(j);
   int pi = Find_parent(i);
   parent[pj] = pi; 
}
/**************************************************************************
*   Union_by_size prefomes a union by size on i and j
*      reads the size of the tree (node i) and if i is grater than j then
*      i becoms the parent of j. and the size of the tre becomes j(size) +
*      i(size)  If the two trees(nodes) are equal than i becoms the parent
*      of j and size is i(size) + j(size)
*   @param i int node to prefom union on
*   @param j int nod to unoin with i
*   @return void
**************************************************************************/
void Graph::Union_by_size(int i,int j){
   int pj = Find_parent(j);
   int pi = Find_parent(i);
   if(pi == pj) return;
   int newsize = parent[pi] + parent[pj];
   if(parent[pi] > parent[pj]){
      parent[pj] = newsize;
      parent[pi] = pj;
   }else{
      parent[pi] = newsize;
      parent[pj] = pi;
   }
}
/**************************************************************************
*   Union_by_hight prefomes a union by hight on i and j
*      if i is greater than j then i becoms the parent of j and hight of 
*      the new tree is the hight of i(hight).  If j is greter than i that j
*      becomes the parent of i and the hight of the new tre is j(hight)
*      If i and j are equal then i becoms the parent of j and the higth 
*      of the new tree becomes i(hight) + 1
*   @param i int node to union
*   @param j int node to union with i
*   @return void
**************************************************************************/
void Graph::Union_by_hight(int i,int j){
   int pj = Find_parent(j);
   int pi = Find_parent(i);
   if(pi == pj) return;
   int newhight = 0;
   if(parent[pi] > parent[pj]){
      //Hight stays the same
      parent[pi] = pj;
   }else if(parent[pi] < parent[pj]){
      //hight stays the same
      parent[pj] = pi;
   } else if(parent[pi] == parent[pj]){
      parent[pi] = parent[pi] + -1;
      parent[pj] = pi;
   }
}
/**************************************************************************
*   Find_parent finds the parent of and returns it. If i is a root than i
*      is returned
*   @param i int the node to find the parent of 
*   @return i int the parent of i
**************************************************************************/
int Graph::Find_parent(int i){
   while(parent[i] > 0) {i = parent[i];}
   return i;
} 
/**************************************************************************
*   printGraph prints out the graph with 10 nodes and there parents per 
*      line and sets them to align to the right.  Just for readibilitys
*      sake
*   @param void
*   @return void
**************************************************************************/
void Graph::printGraph(){
   for(int x = 1; x < cursize; x = x + 10){
      for(int i = x; ((i < cursize) && (i < x + 10)); i++){ 
         cout << "   ";
         cout << setw(3) << i;
      }
      cout << "\n";
      for(int i = x; ((i < cursize) && (i < x + 10)); i++){ cout << "   " << setw(3) << parent[i]; }
      cout << "\n";
   }
}
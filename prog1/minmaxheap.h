#ifndef MINMAXHEAP_H
#define MINMAXHEAP_H
#include <iostream.h>
#define MaxSize 40
/****************************
* This is a Mim or Max Heap.
*    1 = min heap
*    0 = max heap
* it can be used with any class that
* has the > < >= <= operators defined.
*
****************************/
template <class Type> class MinMaxHeap;

template <class Type>
class Element{
   friend class MinMaxHeap<Type>;
   public:
      Type data;
};

template <class Type>
class MinMaxHeap{
   public:
      MinMaxHeap(int MinorMax);
      MinMaxHeap(int MinorMax, int heapsize);
      void Add(Type& value);
      Type* Del(Type& value);
      int isFull();
      int isEmpty();
      void Pup(int x,Type newvalue);
      void Pdown(int x,Type newvalue);
      int findItem(Type item);
      void changePri(Type j,int p);
      void remove(Type j);
      void p();
      void ptofile(int uid);
   private:
      Type *heap;
      int isMax;  // 1 = maxheap , 0 = minheap
      int current;
      int size;
      void HeapFull();
      void HeapEmpty();
      
};
#endif

template <class Type>
MinMaxHeap<Type>::MinMaxHeap(int MinorMax){
   size = MaxSize;
   heap = new Type[size + 1];
   isMax = MinorMax;
   current = 0;  
}
template <class Type>
MinMaxHeap<Type>::MinMaxHeap(int MinorMax, int heapsize){
   size = heapsize;
   heap = new Type[size + 1];
   isMax = MinorMax;
   current = 0;  
}


template <class Type>
int MinMaxHeap<Type>::isFull(){
   if(current == size){ return 1; }
   return 0;
}

template <class Type>
int MinMaxHeap<Type>::isEmpty(){
   if(current>0) return 0;
   return 1;
}

template <class Type>
void MinMaxHeap<Type>::Add(Type& value){
   if(current == size) { HeapFull(); return; }
   current++;
   Pup(current,value);
}

template <class Type>
void MinMaxHeap<Type>::Pup(int x,Type newvalue){
   int i;
   for(i = x; 1;)
   {
      if (i == 1) break;
      if(isMax){ if(newvalue <= heap[i/2]) break; }
      else{      if(newvalue >= heap[i/2]) break; } 
      heap[i] = heap[i/2];
      i /= 2;
   }
   heap[i] = newvalue;
}

template <class Type>
void MinMaxHeap<Type>::Pdown(int x,Type newvalue){
   int i;
   int j;
   for(i = x, j = x + 1; j <= current;)
   {

      if(j < current)
      {
         if(isMax){
            if (heap[j] < heap[j + 1]) j++;
         } else {
            if (heap[j] > heap[j + 1]) j++;
         }
      }
      if(isMax){
         if(newvalue >= heap[j]) break;
      } else {
         if(newvalue <= heap[j]) break;
      }
      heap[i] = heap[j];
      i = j; j *= 2;
   }
   heap[i] = newvalue;
}

template <class Type>
Type* MinMaxHeap<Type>::Del(Type& value){
   if(!current) { HeapEmpty(); return 0; }
   value = heap[1]; Type k = heap[current]; current--;
   int i;
   int j;
   for(i = 1, j = 2; j <= current;)
   {

      if(j < current)
      {
         if(isMax){
            if (heap[j] < heap[j + 1]) j++;
         } else {
            if (heap[j] > heap[j + 1]) j++;
         }
      }
      if(isMax){
         if(k >= heap[j]) break;
      } else {
         if(k <= heap[j]) break;
      }
      heap[i] = heap[j];
      i = j; j *= 2;
   }
   heap[i] = k;
   return &value;
}
      
template <class Type>
int MinMaxHeap<Type>::findItem(Type item){
   int i,found;
   found = 0;
   i = -1;
   while((i <= current) && (!found)){
      i++;
      if(heap[i] == item){ found = 1; }
   }
   if(!found){ i = -1;}
   return i;
}

template <class Type>
void MinMaxHeap<Type>::changePri(Type j,int p){
   int i;
   i = findItem(j);
   cout << "Priority is: " << heap[i].priority;
   if(i != -1){
      heap[i].priority = p;
      cout << " now: " << heap[i].priority << endl;
      Pup(i,heap[i]);
      Pdown(i,heap[i]);
      
   }
   
}

template <class Type>
void MinMaxHeap<Type>::remove(Type j){
   int i;
   i = findItem(j);
   if((i != -1) && !isEmpty()){
      heap[i] = heap[current];
      current--;
      Pdown(i,heap[i]);
      Pup(i,heap[i]);
   }
}


template <class Type>
void MinMaxHeap<Type>::HeapFull(){

 cout << "The Heap Is Full";
}
template <class Type>
void MinMaxHeap<Type>::HeapEmpty(){

 cout << "The Heap Is Empty";
}

template <class Type>
void MinMaxHeap<Type>::p(){
 int i;
 for(i = 1; i <= current; i++) cout << heap[i];
}

template <class Type>
void MinMaxHeap<Type>::ptofile(int uid){
 int i;
 char fname[20];
 char c[1];
 c[0] = uid + 48;
 char ext[5] = { ".out" };
 strcpy(fname,"cli_");
 strcat(fname,c);
 strcat(fname,ext);
 
 ofstream f(fname,ios::out);
 for(i = 1; i <= current; i++) f << heap[i];
 f.close();
}

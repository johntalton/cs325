#include <iostream.h>
#include <fstream.h>
#include "MinMaxHeap.h"
#include "Job.h"
/*****************************************************
*  CLIENT_ID		ENQUEUE	JOB_NAME	PRIORITY
*  CLIENT_ID		DEQUEUE	JOB_NAME
*  CLIENT_ID		PRIORITY	JOB_NAME	NEW_PRIORITY
*  CLIENT_ID		OUTPUT
*  CLIENT_ID		SHUTDOWN
*****************************************************/
#define ENQUEUE  1
#define DEQUEUE  2
#define PRIORITY 3
#define OUTPUT   4
#define SHUTDOWN 5

class Task{
   public:
      Task(){};
      Job j;
      int action;
      int new_p;
};

//---PROTO----------------
Task Listen();
int Handle(Task t);
void Log(Task t);
//------------------------

Task Listen(){
   Job j;
   Task t;
   
   t.j.setuid(0);
   t.j.setp(7);
   t.j.setname("MyJob");
   t.action = 5;
   return t;
}

int Handle(Task t){
   int r = 1;
   static MinMaxHeap<Job> printQ(1);    
   switch(t.action){
      case 1:printQ.Add(t.j);break;
      case 2:printQ.Del(t.j);break;
      case 3:break;
      case 4:printQ.p();break;
      case 5:r = 0;break;
      default: break;
   }
   Log(t);
   return r;
}

void Log(Task t){
   ofstream logfile;
   logfile.open("server.log",ios::out);
   switch(t.action){
      case 1:logfile << "Enqueue by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << "\n" ;break;
      case 2:logfile << "Dequeue by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << "\n";break;
      case 3:logfile << "Priority changed by uid: " << t.j.getuid() << " oldPriority:" << t.j.getp() << " nowPriotity "<< t.new_p << " Job name: " << t.j.getname() << "\n";break;
      case 4:logfile << "Print by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << "\n";break;
      case 5:logfile << "Shutdown by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << "\n";break;
      default: break;
   }


}


void main(){
   int running = 1;
   Task task;
   while(running)
   {
      task = Listen();
      running = Handle(task);
   }

 
}


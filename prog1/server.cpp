#include <iostream.h>
#include <fstream.h>
#include <string.h>
#include <sysent.h>
#include <dirent.h>
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
int Listen(MinMaxHeap<Job> &printQ);
int Handle(Task t,MinMaxHeap<Job> &printQ);
void Log(Task t);
void Print(MinMaxHeap<Job> &pQ);
//------------------------


int getfile(char *fname){
   DIR *dir;
   struct dirent * ent;
   char tempfname[256];
   int i;
   
   dir = opendir("spool");
   ent = readdir(dir);
   ent = readdir(dir);
   ent = readdir(dir);
   closedir(dir);
   if(ent != NULL){
      strcpy(fname,"spool/");
      strcpy(tempfname,ent->d_name);
      strcat(fname,tempfname);
      //cout << fname << endl;
      i = 1;
   }
   else
   {
      i = 0;
   }
   return i;


}


int  Listen(MinMaxHeap<Job> &printQ){
   Job j;
   Task t;
   
   int a,r,uid,p,run,i,k;
   int newp = 0;
   char tmp[10];
   char jobfilename[256] = { "spool/" };
   char name[20] = { "                   " };
   char datain[40];
   char ch;
   int havefile = 1;

   run = 1;
   havefile = getfile(jobfilename);
   while(havefile){      
      cout << jobfilename << "  ";
      ifstream jobfile(jobfilename,ios::in);
      i = 0;
      jobfile.get(ch);
      while(jobfile.good()){
         datain[i++] = ch;
         jobfile.get(ch);
      }
      datain[i] = ch;
      jobfile.close();
 
      a = 0;
      uid = 0;
      p = 0;
      strcpy(name," ");
      newp = 0;
      k = 0;
      //  This gest the uid...
      // -----------------------------------
      i = 0;
      k = 0;
      ch = datain[i];
      while((ch != ' ')){  // && (i < 10)
         tmp[k] = ch;
         i++;k++;
         ch = datain[i];
      }
      tmp[k] = '\0'; 
      uid = strtol(tmp,NULL,10);
      cout << uid << "  ";
      // get rid of any extra white space
      ch = datain[i];
      while((ch == ' ')){
         i++;
         ch = datain[i];
      }
      // This gets action
      // -----------------------------------
      k = 0;
      while((ch != ' ')){
         tmp[k] = ch;
         i++;k++;
         ch = datain[i];
      }
      //tmp[k] = '\0';
      a = strtol(tmp,NULL,10);
      cout << a << "  " << flush;
      // get rid of any extra white space
      ch = datain[i];
      while((ch == ' ')){
         i++;
         ch = datain[i];
      }
      // chec to see if we nead to keep reading 
      if((a == ENQUEUE) || (a == DEQUEUE) || (a == PRIORITY)){
         // This gets that job name
         // -----------------------------------
         k = 0;
         while((ch != ' ')){
            tmp[k] = ch;
            i++;k++;
            ch = datain[i];
         }
         tmp[k] = '\0';
         strcpy(name,tmp);
         cout << name << "  " << flush;
         // get rid of any extra white space
         ch = datain[i];
         while((ch == ' ')){
            i++;
            ch = datain[i];
         }
        
         if(a != DEQUEUE){
            k = 0;
            while((ch != ' ')){
               tmp[k] = ch;
               i++;k++;
               ch = datain[i];
            }
            tmp[k] = '\0';
            p = strtol(tmp,NULL,10);
            newp = p;
            cout << p << "  " << flush;
         }
      }
      cout << endl;
      /////////////////////////
      remove(jobfilename);
      ////////////////////////
      t.j.setuid(uid);
      t.j.setp(p);
      t.j.setname(name);
      t.action = a;
      t.new_p = newp;
      r = Handle(t,printQ);
      if(!r){run = 0;}
      havefile = getfile(jobfilename);
   }
   return run;
}

int Handle(Task t,MinMaxHeap<Job> &printQ){
   int r = 1;

   switch(t.action){
      case 0:break;
      case 1:if(!printQ.isFull()){ printQ.Add(t.j); }break;
      case 2:printQ.remove(t.j);break;
      case 3:printQ.changePri(t.j,t.new_p);break;
      case 4:printQ.ptofile(t.j.getuid());break;
      case 5:r = 0;break;
      default:r = 1; break;
   }
   Log(t);
   return r;
}



void Log(Task t){
   static ofstream logfile("server.log",ios::out);
   time_t systime;
   struct tm *currtime;
   systime = time(NULL);
	currtime = localtime(&systime);
	switch(t.action){
      case 0:break;
      case 1:logfile << "Enqueue by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << " @ " << asctime(currtime);break;
      case 2:logfile << "Dequeue by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << " @ " << asctime(currtime);break;
      case 3:logfile << "Priority changed by uid: " << t.j.getuid() << " oldPriority:" << t.j.getp() << " nowPriotity "<< t.new_p << " Job name: " << t.j.getname() << " @ " << asctime(currtime);break;
      case 4:logfile << "List by uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << " @ " << asctime(currtime);break;
      case 5:logfile << "Shutdown by uid: " << t.j.getuid() << " @ " << asctime(currtime);break;
      case 6:logfile << "Print job uid: " << t.j.getuid() << " Priority:" << t.j.getp() << " Job name: " << t.j.getname() << " @ " << asctime(currtime);break;
      default: break;
   }
   //logfile.close();

}

void Print(MinMaxHeap<Job> &pQ){
   Task t;
   Job p;
   int i,j;
   int a = 5;
   int b = 10;
   
   int r = rand()%(b-a+1) + a;
   
   if(!pQ.isEmpty()){
      p = *pQ.Del(p);
      t.j.setuid(p.getuid());      
      t.j.setp(p.getp());
      t.j.setname(p.getname());
      t.action = 6;
      Log(t);
      cout << "Printing " << p.getname() << flush;
      
      for(i = 0; i < r;i++){
         sleep(1);
         cout << "....." << flush;

      }
      cout << endl;
   }
  

}

void main(){
   int running = 1;
   MinMaxHeap<Job> printQ(0);    
   time_t systime;
   struct tm *currtime;
   systime = time(NULL);
	currtime = localtime(&systime);
	srand(currtime->tm_sec);
	
	
   while(running)
   {
      running = Listen(printQ);
      Print(printQ);
   }
   
   
   ///////////////////////
   //Print everythig left in the Q
   while(!printQ.isEmpty()){
      Print(printQ);
   }

 
}


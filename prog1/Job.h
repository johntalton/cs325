#ifndef JOB_H
#define JOB_H
class Job{
   public:
      Job(){};
      void setp(int p);
      int getp();
      void setuid(int u);
      int getuid();
      void setname(char *n);
      char* getname();
      int operator>(Job j);
      int operator<(Job j);
      int operator>=(Job j);
      int operator<=(Job j);
      int operator==(Job j);
      friend ostream& operator<<(ostream& os,Job j);
   private:
      int priority;
      int uid;
      char name[20];
};
#endif

void Job::setp(int p){
   priority = p;
}
int Job::getp(){
   return priority;
}
void Job::setuid(int u){
   uid = u;
}
int Job::getuid(){
   return uid;
}
void Job::setname(char *n){
   int x;
   for(x = 0; x <= 20; x++)
   {
      name[x] = n[x];
   }
}
char* Job::getname(){
   return name;
}
int Job::operator>(Job j){
   return priority > j.priority;
}
int Job::operator<(Job j){
   return priority > j.priority;
}
int Job::operator>=(Job j){
   return priority >= j.priority;
}
int Job::operator<=(Job j){
   return priority >= j.priority;
}
int Job::operator==(Job j){
   return priority == j.priority;
}
ostream& operator<<(ostream& os,Job j){
   os << j.uid << "   " << j.name << "   " << j.priority << "\n";
}


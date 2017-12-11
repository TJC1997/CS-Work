#include"location.h"

location::location()
{
  e=NULL;
}
/*
location::~location()
{
  delete e;
}*/
void location::set_event(event *ee)
{
  e=ee;
}
event* location::get_event()
{
  return e;
}
/*
void location::operator=(const location& old)
{
  int num=old.e->get_num();
  cout<<num<<endl;
  if(e!=NULL){
    delete e;
  }
  switch(num)
  {
    case 0:
            e=new noevent;
            break;
    case 1:
            e=new eventra;
            break;
    case 2:
            e=new eventrb;
            break;
    case 3:
            e=new eventfa;
            break;
    case 4:
            e=new eventfb;
            break;
    case 5:
            e=new eventpa;
            break;
    case 6:
            e=new eventpb;
            break;
    case 7:
            e=new cave;
            break;
    case 8:
            e=new stop;
            break;
  }
}
*/

    




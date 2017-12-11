#include"event.h"

event::event()
{
  num=0;
  message="Nothing is here";
}
void event::set_num(int n)
{
  num=n;
}
void event::set_message(string m)
{
  message=m;
}
int event::get_num()
{
  return num;
}
string event::get_message()
{
  return message;
}

noevent::noevent()
{
  num=0;
  message="Nothing is here";
}
void noevent::percept()
{
  int a=0;
}
eventra::eventra()
{
  num=1;
  message="Geodude(Rock) is here";
}
void eventra::percept()
{
  cout<<"Geodude(Rock) is nearby"<<endl;
}

eventrb::eventrb()
{
  num=2;
  message="Onix(Rock) is here";
}
void eventrb::percept()
{
  cout<<"Onix(Rock) is nearby"<<endl;
}

eventfa::eventfa()
{
  num=3;
  message="Charizard(fly) is here";
}
void eventfa::percept()
{
  cout<<"Charizard(fly) is nearby"<<endl;
}

eventfb::eventfb()
{
  num=4;
  message="Rayquaza(fly) is here";
}
void eventfb::percept()
{
  cout<<"Rayquaza(fly) is nearby"<<endl;
}

eventpa::eventpa()
{
  num=5;
  message="Mewtwo(Psy) is here";
}
void eventpa::percept()
{
  cout<<"Mewtwo(Psy) is nearby"<<endl;
}

eventpb::eventpb()
{
  num=6;
  message="Espeon(Psy) is here";
}
void eventpb::percept()
{
  cout<<"Espeon(Psy) is nearby"<<endl;
}

cave::cave()
{
  num=7;
  message="Cave with mega stone is here";
}
void cave::percept()
{
  cout<<"Cave is nearby"<<endl;
}

stop::stop()
{
  num=8;
  message="Poke-stop is here";
}
void stop::percept()
{
  cout<<"Poke-stop is nearby"<<endl;
}


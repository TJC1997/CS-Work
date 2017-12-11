#include"c.h"

creature::creature()
{
  type=0;
  strength=20;
  hp=100;
  name="creature";
  payoff=10;
  cost=10;
}

creature::creature(int t,int s,int h,int p,int c,string n)
{
  type=t;
  strength=s;
  hp=h;
  name=n;
  payoff=p;
  cost=c;
}
void creature::set_type(const int num)
{
  type=num;
}
void creature::set_strength(const int num)
{
  strength=num;
}
void creature::set_hp(const int num)
{
  hp=hp-num;
  cout<<name<<" have "<<hp<<" hp right now"<<endl;
}
void creature::set_name(const string n)
{
  name=n;
}
void creature::set_payoff(const int num)
{
  payoff=num;
}
void creature::set_cost(const int num)
{
  cost=num;
}
int creature::get_type()
{
  return type;
}
int creature::get_strength()
{
  return strength;
}
int creature::get_hp()
{
  return hp;
}
int creature::get_payoff()
{
  return payoff;
}
int creature::get_cost()
{
  return cost;
}
string creature::get_name()
{
  return name;
}
string creature::getspecies()
{
  switch(type)
  {
    case 0:return "Human";
    case 1:return "Elf";
    case 2:return "Cyberdemon";
    case 3:return "Balrogs";
    case 4:return "Chinese";
  }
}
demon::demon(int t,int s,int h,int p,int c,string n):creature(t,s,h,p,c,n)
{
}  
elf::elf(int t,int s,int h,int p,int c,string n):creature(t,s,h,p,c,n)
{
} 
human::human(int t,int s,int h,int p,int c,string n):creature(t,s,h,p,c,n)
{
}  
chinese::chinese(int t,int s,int h,int p,int c,string n):human(t,s,h,p,c,n)
{
}    
cyberdemon::cyberdemon(int t,int s,int h,int p,int c,string n):demon(t,s,h,p,c,n)
{
}
balrogs::balrogs(int t,int s,int h,int p,int c,string n):demon(t,s,h,p,c,n)
{
}
demon::demon():creature()
{
}
elf::elf():creature()
{
}
human::human():creature()
{
}
cyberdemon::cyberdemon():demon()
{
}
balrogs::balrogs():demon()
{
}
chinese::chinese():human()
{
}
int human::get_damage()
{
  int damage,add;
  damage=rand()%strength+1;
  cout<<getspecies()<<" "<<name<<" attacks for "<<damage<<"points!"<<endl;
  add=rand()%100;
  if (add<50)
  {
    hp=hp+damage;
    cout<<name<<" gain extra hitpoints from your damage!"<<"HP+ "<<damage<<endl;
  }
  return damage;
}
int chinese::get_damage()
{
  int a,add;
  a=human::get_damage();
  add=rand()%100;
  if(add<50)
  {
    cout<<name<<" Your ShaoLin Kungfu skills wake up from your blood. You attack 100 points more!"<<endl;
    a=a+100;    
  }
  return a;

}
int demon::get_damage()
{
  int damage,add;
  damage=rand()%strength+1;
  cout<<getspecies()<<" "<<name<<" attacks for "<<damage<<"points!"<<endl;
  add=rand()%100;
  if (add<50)
  {
    damage=damage+20;
    cout<<name<<" Demonic attack inflicts 20"<<" addtional damage points!"<<endl;
  }
  return damage;
}
int balrogs::get_damage()
{
  int a=0,b=0;
  a=demon::get_damage();
  cout<<name<<" is a balrog.You get a extra chance to attack."<<endl;
  b=demon::get_damage();
  return a+b;
}
int elf::get_damage()
{
  int damage,add;
  damage=rand()%strength+1;
  cout<<getspecies()<<" "<<name<<" attacks for "<<damage<<"points!"<<endl;
  add=rand()%100;
  if (add<50)
  {
    cout<<"Double damage!!"<<"Addtional "<<damage<<" damage points!"<<endl;
    damage=damage*2;
  }
  return damage;
}
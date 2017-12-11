#include"pokemon.h"

pokemon::pokemon()
{
  type="pokemon";
  name="poke";
  chance=0;
  stage=0;
  num=0;
}
bool pokemon::catchp()
{
  cout<<"You throw out a ball to "<<name<<endl;
	cout << "3, " << flush;
	//sleep(1);
	cout << "2, " << flush;
	//sleep(1);
	cout << "1..." << flush;
	//sleep(1);
	int a=rand()%100;
  if (a<chance)
  {
    cout<<"You catch "<<name<<" successfully!"<<endl;
    stage=stage+1;
    cout<<name<<" stage is "<<stage<<endl;
    return true;
  }
  else
  {
    cout<<"You didn't catch it. "<<name<<" ran away"<<endl;
    return false;
  }
}
void pokemon::set_stage(int s)
{
  stage=s;
}
void pokemon::set_type(string t)
{
  type=t;
}
void pokemon::set_name(string n)
{
  name=n;
}
void pokemon::set_chance(int c)
{
  chance=c;
}
void pokemon::set_num(int n)
{
  num=n;
}
string pokemon::get_type()
{
  return type;
}
string pokemon::get_name()
{
  return name;
}
int pokemon::get_chance()
{
  return chance;
}
int pokemon::get_stage()
{
  return stage;
}
int pokemon::get_num()
{
  return num;
}
rocka::rocka()
{
  type="rock";
  name="Geodude";
  chance=75;
  num=1;
}
rockb::rockb()
{
  type="rock";
  name="Onix";
  chance=75;
  num=2;
}
flya::flya()
{
  type="fly";
  name="Charizard";
  chance=50;
  num=3;
}
flyb::flyb()
{
  type="fly";
  name="Rayquaza";
  chance=50;
  num=4;
}
psychica::psychica()
{
  type="psychic";
  name="Mewtwo";
  chance=25;
  num=5;
}
psychicb::psychicb()
{
  type="psychic";
  name="Espeon";
  chance=25;
  num=6;
}
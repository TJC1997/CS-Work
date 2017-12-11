#ifndef P_H
#define P_H

#include<iostream>
#include<string>
#include <unistd.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

class pokemon
{
  protected:
    string type;
    string name;
    int chance;
    int stage;
    int num;
  public:
    pokemon();
    void set_type(string t);
    void set_name(string n);
    void set_chance(int c);
    void set_stage(int s);
    void set_num(int n);
    string get_type();
    string get_name();
    int get_chance();
    int get_stage();
    int get_num();
    bool catchp();
    
};
class rocka:public pokemon
{
  public:
    rocka();
};
class rockb:public pokemon
{
  public:
    rockb();
};
class flya:public pokemon
{
  public:
    flya();
};
class flyb:public pokemon
{
  public:
    flyb();
};
class psychica:public pokemon
{
  public:
    psychica();
};
class psychicb:public pokemon
{
  public:
    psychicb();
};










#endif
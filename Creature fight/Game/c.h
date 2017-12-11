#ifndef C_H
#define C_H

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

class creature
{
  protected:
    int type;
    int strength;
    int hp;
    string name;
    int payoff;
    int cost;
  public:
    creature();
    creature(int t,int s,int h,int p,int c,string n);
    void set_type(const int);
    void set_strength(const int);
    void set_hp(const int);
    void set_name(const string);
    void set_payoff(const int);
    void set_cost(const int);
    int get_type();
    int get_strength();
    int get_hp();
    int get_payoff();
    int get_cost();
    string get_name();
    string getspecies();
};
class demon:public creature
{
  public:
    demon();
    demon(int t,int s,int h,int p,int c,string n);
    int get_damage();
};
class elf:public creature
{
  public:
    elf();
    elf(int t,int s,int h,int p,int c,string n);
    int get_damage();
};
class human:public creature                   
{
  public:
    human();
    human(int t,int s,int h,int p,int c,string n);
    int get_damage();
};
class chinese:public human
{
  public:
    chinese(); 
    chinese(int t,int s,int h,int p,int c,string n);
    int get_damage();
};
class cyberdemon:public demon
{
  public:
    cyberdemon();
    cyberdemon(int t,int s,int h,int p,int c,string n);
};
class balrogs:public demon
{
  public:
    balrogs();
    balrogs(int t,int s,int h,int p,int c,string n);
    int get_damage();
};







#endif
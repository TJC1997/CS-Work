#ifndef E_H
#define E_H


#include<iostream>
#include<string>

using namespace std;

class event
{
  protected:
    int num;
    string message;
  public:
    event();
    void set_num(int n);
    void set_message(string m);
    int get_num();
    string get_message();
    virtual void percept()=0;
};

class noevent:public event
{
  public:
    noevent();
    void percept();
};

class eventra:public event
{
  public:
    eventra();
    void percept();
};

class eventrb:public event
{
  public:
    eventrb();
    void percept();
};

class eventfa:public event
{
  public:
    eventfa();
    void percept();
};

class eventfb:public event
{
  public:
    eventfb();
    void percept();
};

class eventpa:public event
{
  public:
    eventpa();
    void percept();
};

class eventpb:public event
{
  public:
    eventpb();
    void percept();
};

class cave:public event
{
  public:
    cave();
    void percept();
};

class stop:public event
{
  public:
    stop();
    void percept();
};

#endif
#ifndef L_H
#define L_H
#include"event.h"

class location
{
  protected:
    event *e;
  public:
    location();
    //~location();
    //void operator=(const location& old);
    void set_event(event *ee);
    event *get_event();
    
};















#endif
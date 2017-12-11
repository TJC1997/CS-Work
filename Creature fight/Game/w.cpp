#include"w.h"
world::world()
{
  playername="player";
  money=40;
  num_human=0;
  num_elf=0;
  num_cyberdemon=0;
  num_balrogs=0;
  num_chinese=0;
  h=NULL;
  e=NULL;
  c=NULL;
  b=NULL;
  ch=NULL;
}
world::~world()
{
  delete [] h;
  delete [] e;
  delete [] c;
  delete [] b;
  delete [] ch;
}
world::world(const world& old)
{
  playername=old.playername;
  money=old.money;
  num_human=old.num_human;
  num_elf=old.num_elf;
  num_cyberdemon=old.num_cyberdemon;
  num_balrogs=old.num_balrogs;
  num_chinese=old.num_chinese;
  if(num_human==0)
  {
    h=NULL;
  }
  else
  {
    h=new human[num_human];
    for(int i=0;i<num_human;i++)
    {
      h[i]=old.h[i];
    }
  }
  if(num_elf==0)
  {
    e=NULL;
  }
  else
  {
    e=new elf[num_elf];
    for(int i=0;i<num_elf;i++)
    {
      e[i]=old.e[i];
    }
  }
  if(num_cyberdemon==0)
  {
    c=NULL;
  }
  else
  {
    c=new cyberdemon[num_cyberdemon];
    for(int i=0;i<num_cyberdemon;i++)
    {
      c[i]=old.c[i];
    }
  }
  if(num_balrogs==0)
  {
    b=NULL;
  }
  else
  {
    b=new balrogs[num_balrogs];
    for(int i=0;i<num_balrogs;i++)
    {
      b[i]=old.b[i];
    }
  }
  if(num_chinese==0)
  {
    ch=NULL;
  }
  else
  {
    h=new chinese[num_chinese];
    for(int i=0;i<num_chinese;i++)
    {
      ch[i]=old.ch[i];
    }
  }
}
void world::operator=(const world& old)
{
  if(h!=NULL)
    delete [] h;
  if(e!=NULL) 
    delete [] e;
  if(c!=NULL)
    delete [] c;
  if(b!=NULL)
    delete [] b;
  if(ch!=NULL)
    delete [] ch;
  
  playername=old.playername;
  money=old.money;
  num_human=old.num_human;
  num_elf=old.num_elf;
  num_cyberdemon=old.num_cyberdemon;
  num_balrogs=old.num_balrogs;
  num_chinese=old.num_chinese;
  if(num_human==0)
  {
    h=NULL;
  }
  else
  {
    h=new human[num_human];
    for(int i=0;i<num_human;i++)
    {
      h[i]=old.h[i];
    }
  }
  if(num_elf==0)
  {
    e=NULL;
  }
  else
  {
    e=new elf[num_elf];
    for(int i=0;i<num_elf;i++)
    {
      e[i]=old.e[i];
    }
  }
  if(num_cyberdemon==0)
  {
    c=NULL;
  }
  else
  {
    c=new cyberdemon[num_cyberdemon];
    for(int i=0;i<num_cyberdemon;i++)
    {
      c[i]=old.c[i];
    }
  }
  if(num_balrogs==0)
  {
    b=NULL;
  }
  else
  {
    b=new balrogs[num_balrogs];
    for(int i=0;i<num_balrogs;i++)
    {
      b[i]=old.b[i];
    }
  }
  if(num_chinese==0)
  {
    ch=NULL;
  }
  else
  {
    h=new chinese[num_chinese];
    for(int i=0;i<num_chinese;i++)
    {
      ch[i]=old.ch[i];
    }
  }
}

void world::set_name(const string n)
{
  playername=n;
}
void world::set_money(const int m)
{
  money=m;
}
void world::set_num_human(const int n)
{
  num_human=n;
}
void world::set_num_elf(const int n)
{
  num_elf=n;
}
void world::set_num_cyber(const int n)
{
  num_cyberdemon=n;
}
void world::set_num_bal(const int n)
{
  num_balrogs=n;
}
void world::set_num_chinese(const int n)
{
  num_chinese=n;
}
void world::set_h(human*hu)
{
  h=hu;
}
void world::set_e(elf*el)
{
  e=el;
}
void world::set_cyber(cyberdemon*cy)
{
  c=cy;
}
void world::set_b(balrogs* ba)
{
  b=ba;
}
void world::set_ch(chinese *c)
{
  ch=c;
}
string world::get_name()const
{
  return playername;
}
int world::get_money()const
{
  return money;
}
int world::get_num_human()
{
  return num_human;
}
int world::get_num_elf()
{
  return num_elf;
}
int world::get_num_cyber()
{
  return num_cyberdemon;
}
int world::get_num_bal()
{
  return num_balrogs;
}
int world::get_num_chinese()
{
  return num_chinese;
}
human* world::get_human()
{
  return h;
}
elf* world::get_elf()
{
  return e;
}
cyberdemon* world::get_cyber()
{
  return c;
}
balrogs* world::get_bal()
{
  return b;
}
chinese* world::get_ch()
{
  return ch;
}
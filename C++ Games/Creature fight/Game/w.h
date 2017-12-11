#ifndef W_H
#define W_H

#include"c.h"

class world
{
  private:
    string playername;
    int money;
    int num_human;
    int num_elf;
    int num_cyberdemon;
    int num_balrogs;
    int num_chinese;
    human *h;
    elf *e;
    cyberdemon *c;
    balrogs *b;
    chinese *ch;
  public:
    world();
    ~world();
    world(const world& old);
    void operator=(const world& old);
    void set_name(const string);
    void set_money(const int);
    void set_num_human(const int);
    void set_num_elf(const int);
    void set_num_cyber(const int);
    void set_num_bal(const int);
    void set_num_chinese(const int);
    void set_h(human*);
    void set_e(elf*);
    void set_cyber(cyberdemon*);
    void set_b(balrogs*);
    void set_ch(chinese*);
    string get_name()const;
    int get_money()const;
    int get_num_human();
    int get_num_elf();
    int get_num_cyber();
    int get_num_bal();
    int get_num_chinese();
    human* get_human();
    elf* get_elf();
    cyberdemon* get_cyber();
    balrogs* get_bal();
    chinese* get_ch();
};


#endif
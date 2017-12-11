/****************************************************** 
** Program: driver.cpp 
** Author: Yuhang Chen 
** Date: 5/11/2017
** Description:creature fight
** Input: cin
** Output: infomation
******************************************************/ 

#include"c.h"
#include"w.h"
using namespace std;
/*********************************************************************   
** Function: getname
** Description: get name of user
** Parameters: string&n1,string&n2
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void getname(string&n1,string&n2)//p1 name,p2 name
{
  cout<<"Player 1,what is your name?"<<endl;
  cin>>n1;
  cout<<"Player 2,what is your name?"<<endl;
  cin>>n2;
}
/*********************************************************************   
** Function: buy
** Description: let user buy creature
** Parameters: world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void buy(world &p)
{
  int choice,money;
  money=p.get_money();
  string name;
  name=p.get_name();
  do
  {
    cout<<name<<",You have "<<money<<" $ now"<<endl;
    if(money<20)
    {
      cout<<"You don't have enough money to buy a creature"<<endl;//if money<20 user cannot buy a creature
      break;
    }
    cout<<"All creatures cost 20$. What do you want to buy?(1.Human 2.Elf 3.Cyberdemon 4.Balrogs 5.Chinese 6.Quit)"<<endl;
    cin>>choice;
    if(choice==1)
    {
      cout<<"How many Human do you want to buy?"<<endl;
      int number,cost;
      cin>>number;
      cost=number*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      p.set_num_human(number);
      human *h=new human[number];//create the dynamic memory 
      string name[number];//create array to store names
      for(int i=0;i<number;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
        h[i]=human(0,100,400,10,10,name[i]);//set name,type,strength,etc to human *h
      }
      p.set_h(h);//update creature
    }
    else if(choice==2)
    {
      cout<<"How many Elf do you want to buy?"<<endl;
      int number,cost;
      cin>>number;
      cost=number*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      p.set_num_elf(number);
      elf *e=new elf[number];//create the dynamic memory 
      string name[number];//create array to store names
      for(int i=0;i<number;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
        e[i]=elf(1,80,420,10,10,name[i]);//set name,type,strength,etc to human *h
      }
      p.set_e(e);//update creature
    }
    else if(choice==3)
    {
      cout<<"How many Cyberdemon do you want to buy?"<<endl;
      int number,cost;
      cin>>number;
      cost=number*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      p.set_num_cyber(number);
      cyberdemon *c=new cyberdemon[number];//create the dynamic memory 
      string name[number];//create array to store names
      for(int i=0;i<number;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
        c[i]=cyberdemon(2,80,420,10,10,name[i]);//set name,type,strength,etc to human *h
      }
      p.set_cyber(c);//update creature
    }
    else if(choice==4)
    {
      cout<<"How many Balrogs do you want to buy?"<<endl;
      int number,cost;
      cin>>number;
      cost=number*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      p.set_num_bal(number);
      balrogs *b=new balrogs[number];//create the dynamic memory 
      string name[number];//create array to store names
      for(int i=0;i<number;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
        b[i]=balrogs(3,120,280,10,10,name[i]);//set name,type,strength,etc to human *h
      }
      p.set_b(b);//update creature
    }
    else if(choice==5)
    {
      cout<<"How many Chinese do you want to buy?"<<endl;
      int number,cost;
      cin>>number;
      cost=number*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      p.set_num_chinese(number);
      chinese *ch=new chinese[number];//create the dynamic memory 
      string name[number];//create array to store names
      for(int i=0;i<number;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
        ch[i]=chinese(4,60,440,20,20,name[i]);//set name,type,strength,etc to human *h
      }
      p.set_ch(ch);//update creature
    }
    else if(choice==6)
    {
      break;
    }
  }while(true);
}
/*********************************************************************   
** Function: pick
** Description: pick creature from the world
** Parameters: world &p,int &type,int &num
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void pick(world &p,int &type,int &num)
{
  string name;
  name=p.get_name();
  creature *h,*e,*c,*b,*ch;//human elf cyberdemon balrogs chinese
  int h_num,e_num,c_num,b_num,ch_num;//num of creature
  h_num=p.get_num_human();
  e_num=p.get_num_elf();
  c_num=p.get_num_cyber();
  b_num=p.get_num_bal();
  ch_num=p.get_num_chinese();
  h=p.get_human();
  e=p.get_elf();
  c=p.get_cyber();
  b=p.get_bal();
  ch=p.get_ch();
  int choice; 
  do
  {
    cout<<name<<",What kind of creature do you want to pick to fight?(1.Human 2.Elf 3.Cyberdemon 4.Balrogs 5.Chinese)"<<endl;
    cin>>choice;
    if(choice==1)
    {
      if(h_num==0)//check if they have creature first
      {
        cout<<"You don't have any human."<<endl;
      }
      else
      {
        for(int i=0;i<h_num;i++)
        {
          cout<<i<<"."<<h[i].get_name()<<endl;
        }
        cout<<"which one do you want to choose?"<<endl;
        int p;
        cin>>p;
        type=choice;
        num=p;
        break;
      }
    }
    if(choice==2)
    {
      if(e_num==0)
      {
        cout<<"You don't have any elf."<<endl;
      }
      else
      {
        for(int i=0;i<e_num;i++)
        {
          cout<<i<<"."<<e[i].get_name()<<endl;
        }
        cout<<"which one do you want to choose?"<<endl;
        int p;
        cin>>p;
        type=choice;//get type num
        num=p;//get creature num
        break;
      }
    }
    if(choice==3)
    {
      if(c_num==0)
      {
        cout<<"You don't have any cyberdemon."<<endl;
      }
      else
      {
        for(int i=0;i<c_num;i++)
        {
          cout<<i<<"."<<c[i].get_name()<<endl;
        }
        cout<<"which one do you want to choose?"<<endl;
        int p;
        cin>>p;
        type=choice;
        num=p;
        break;
      }
    }
    if(choice==4)
    {
      if(b_num==0)
      {
        cout<<"You don't have any balrog."<<endl;
      }
      else
      {
        for(int i=0;i<b_num;i++)
        {
          cout<<i<<"."<<b[i].get_name()<<endl;
        }
        cout<<"which one do you want to choose?"<<endl;
        int p;
        cin>>p;
        type=choice;
        num=p;
        break;
      }
    }
    if(choice==5)
    {
      if(ch_num==0)
      {
        cout<<"You don't have any chinese."<<endl;
      }
      else
      {
        for(int i=0;i<ch_num;i++)
        {
          cout<<i<<"."<<ch[i].get_name()<<endl;
        }
        cout<<"which one do you want to choose?"<<endl;
        int p;
        cin>>p;
        type=choice;
        num=p;
        break;
      }
    }
  }while(true);
} 
/*********************************************************************   
** Function: determine_damage
** Description: get the damage of creature
** Parameters: int type,int num,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: int damage
*********************************************************************/
int determine_damage(int type,int num,world &p)
{
  if(type==1)//check type first
  {
    human *h=p.get_human();//use different type according to the type number
    return h[num].get_damage();
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    return e[num].get_damage();
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    return c[num].get_damage();
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    return b[num].get_damage();
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    return ch[num].get_damage();
  }
}
/*********************************************************************   
** Function: change_hp
** Description: change the hp of creature
** Parameters: int type,int num,int damage,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void change_hp(int type,int num,int damage,world &p)
{
  if(type==1)//check type first
  {
    human *h=p.get_human();//use different type according to the type number
    h[num].set_hp(damage);
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    e[num].set_hp(damage);
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    c[num].set_hp(damage);
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    b[num].set_hp(damage);
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    ch[num].set_hp(damage);
  }
}
/*********************************************************************   
** Function: check2
** Description: check if creature of player2 die
** Parameters: int type,int num,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: 0 or 1
*********************************************************************/
int check2(int type,int num,world &p)//check if creature of player2 die
{
  int hp;
  if(type==1)
  {
    human *h=p.get_human();//same with check 1
    hp=h[num].get_hp();
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    hp=e[num].get_hp();
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    hp=c[num].get_hp();
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    hp=b[num].get_hp();
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    hp=ch[num].get_hp();
  }
  if(hp>0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
} 

/*********************************************************************   
** Function: check1
** Description: check if creature of player1 die
** Parameters: int type,int num,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: 0 or 1
*********************************************************************/
int check1(int type,int num,world &p)//check if creature of player1 die
{
  int hp;
  if(type==1)//check type first
  {
    human *h=p.get_human();//use different type according to the type number
    hp=h[num].get_hp();
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    hp=e[num].get_hp();
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    hp=c[num].get_hp();
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    hp=b[num].get_hp();
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    hp=ch[num].get_hp();
  }
  if(hp>0)
  {
    return 0;
  }
  else
  {
    return 2;//give the winner number
  }
} 
/*********************************************************************   
** Function: get_winner
** Description: give the winner of this round
** Parameters: int type,int num,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void get_winner(int type,int num,world &p)
{
  int hp;
  string name;
  if(type==1)//check type first
  {
    human *h=p.get_human();//use different type according to the type number
    hp=h[num].get_hp();
    name=h[num].get_name();
    cout<<h[num].getspecies()<<" "<<name<<" won the fight, he has "<<hp<<" hp left"<<endl;//use getspecies to give the specie
    cout<<""<<endl;
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    hp=e[num].get_hp();
    name=e[num].get_name();
    cout<<e[num].getspecies()<<" "<<name<<" won the fight, he has "<<hp<<" hp left"<<endl;
    cout<<""<<endl;
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    hp=c[num].get_hp();
    name=c[num].get_name();
    cout<<c[num].getspecies()<<" "<<name<<" won the fight, he has "<<hp<<" hp left"<<endl;
    cout<<""<<endl;
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    hp=b[num].get_hp();
    name=b[num].get_name();
    cout<<b[num].getspecies()<<" "<<name<<" won the fight, he has "<<hp<<" hp left"<<endl;
    cout<<""<<endl;
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    hp=ch[num].get_hp();
    name=ch[num].get_name();
    cout<<ch[num].getspecies()<<" "<<name<<" won the fight, he has "<<hp<<" hp left"<<endl;
    cout<<""<<endl;
  } 
}
/*********************************************************************   
** Function: delete_loser
** Description: remove loser from the world
** Parameters: int type,int num,world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void delete_loser(int type,int num,world &p)
{
  string name;
  if(type==1)
  {
    human *h=p.get_human();//get old array
    name=h[num].get_name();
    cout<<h[num].getspecies()<<" "<<name<<" lost game,he will be removed."<<endl;
    cout<<""<<endl;
    int n=p.get_num_human();//n=num of creature
    human *new_h=new human[n-1];//set new array
    int y=0;
    for(int i=0;i<n;i++)
    {
      if(i==num)
      {
        ;
      }
      else
      {
        new_h[y]=h[i];
        y=y+1;
      }
    }
    p.set_num_human(n-1);//set new num to world
    p.set_h(new_h);//set new array to world
    delete []h;//delete old array
  }
  if(type==2)
  {
    elf *e=p.get_elf();
    name=e[num].get_name();
    cout<<e[num].getspecies()<<" "<<name<<" lost game,he will be removed."<<endl;
    cout<<""<<endl;
    int n=p.get_num_elf();//n=num of creature
    elf *new_h=new elf[n-1];
    int y=0;
    for(int i=0;i<n;i++)
    {
      if(i==num)
      {
        ;
      }
      else
      {
        new_h[y]=e[i];
        y=y+1;
      }
    }
    p.set_num_elf(n-1);
    p.set_e(new_h);
    delete []e;
  }
  if(type==3)
  {
    cyberdemon *c=p.get_cyber();
    name=c[num].get_name();
    cout<<c[num].getspecies()<<" "<<name<<" lost game,he will be removed."<<endl;
    cout<<""<<endl;
    int n=p.get_num_cyber();//n=num of creature
    cyberdemon *new_h=new cyberdemon[n-1];
    int y=0;
    for(int i=0;i<n;i++)
    {
      if(i==num)
      {
        ;
      }
      else
      {
        new_h[y]=c[i];
        y=y+1;
      }
    }
    p.set_num_cyber(n-1);
    p.set_cyber(new_h);
    delete []c;
  }
  if(type==4)
  {
    balrogs *b=p.get_bal();
    name=b[num].get_name();
    cout<<b[num].getspecies()<<" "<<name<<" lost game,he will be removed."<<endl;
    cout<<""<<endl;
    int n=p.get_num_bal();//n=num of creature
    balrogs *new_h=new balrogs[n-1];
    int y=0;
    for(int i=0;i<n;i++)
    {
      if(i==num)
      {
        ;
      }
      else
      {
        new_h[y]=b[i];
        y=y+1;
      }
    }
    p.set_num_bal(n-1);
    p.set_b(new_h);
    delete []b;
  }
  if(type==5)
  {
    chinese *ch=p.get_ch();
    name=ch[num].get_name();
    cout<<ch[num].getspecies()<<" "<<name<<" lost game,he will be removed."<<endl;
    cout<<""<<endl;
    int n=p.get_num_chinese();//n=num of creature
    chinese *new_h=new chinese[n-1];
    int y=0;
    for(int i=0;i<n;i++)
    {
      if(i==num)
      {
        ;
      }
      else
      {
        new_h[y]=ch[i];
        y=y+1;
      }
    }
    p.set_num_chinese(n-1);
    p.set_ch(new_h);
    delete []ch;
  } 
}
/*********************************************************************   
** Function: checkcontinue
** Description: check if game continue
** Parameters: world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: true or flase
*********************************************************************/
bool checkcontinue(world &p)
{
  int h_num,e_num,c_num,b_num,ch_num,all=0,money;
  h_num=p.get_num_human();
  e_num=p.get_num_elf();
  c_num=p.get_num_cyber();
  b_num=p.get_num_bal();
  ch_num=p.get_num_chinese();
  all=h_num+e_num+c_num+b_num+ch_num;
  money=p.get_money();
  cout<<"loser "<<p.get_name()<<"'s money "<<money<<endl;//cout how much money does loser left
  cout<<"loser "<<p.get_name()<<"'s number of creatures "<<all<<endl;//cout how many creature does loser left
  if(money<20 and all==0)//check if game continue
  {
    return false;
  }
  else
  {
    return true;
  }
}
/*********************************************************************   
** Function: buynew
** Description: buy new creature
** Parameters: world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: true or flase
*********************************************************************/
void buynew(world &p)
{
  int choice,money;
  money=p.get_money();
  string name;
  name=p.get_name();
  do
  {
    cout<<name<<",You have "<<money<<" $ now"<<endl;
    if(money<20)
    {
      cout<<"You don't have enough money to buy a creature"<<endl;
      break;
    }
    cout<<"All creatures cost 20$. What do you want to buy?(1.Human 2.Elf 3.Cyberdemon 4.Balrogs 5.Chinese 6.Quit)"<<endl;
    cin>>choice;
    if(choice==1)
    {
      cout<<"How many Human do you want to buy?"<<endl;
      int newnumber,cost,oldnumber,total,count=0;
      oldnumber=p.get_num_human();
      cin>>newnumber;//get how many new creature does user want to buy
      cost=newnumber*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      total=newnumber+oldnumber;
      p.set_num_human(total);
      human *new_h=new human[total];//create the dynamic memory 
      human *old_h=p.get_human();
      string name[newnumber];//create array to store names
      for(int i=0;i<newnumber;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
      }
      for(int x=0;x<oldnumber;x++)//copy old creature
      {
        new_h[x]=old_h[x];
      }
      for(int y=oldnumber;y<total;y++)//add new creature
      {
        new_h[y]=human(0,100,400,10,10,name[count]);
        count=count+1;
      }
      p.set_h(new_h);//update creature
      delete []old_h;
    }
    else if(choice==2)
    {
      cout<<"How many Elf do you want to buy?"<<endl;
      int newnumber,cost,oldnumber,total,count=0;
      oldnumber=p.get_num_elf();
      cin>>newnumber;
      cost=newnumber*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      total=newnumber+oldnumber;
      p.set_num_elf(total);
      elf *new_h=new elf[total];//create the dynamic memory 
      elf *old_h=p.get_elf();
      string name[newnumber];//create array to store names
      for(int i=0;i<newnumber;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
      }
      for(int x=0;x<oldnumber;x++)
      {
        new_h[x]=old_h[x];
      }
      for(int y=oldnumber;y<total;y++)
      {
        new_h[y]=elf(1,80,420,10,10,name[count]);
        count=count+1;
      }
      p.set_e(new_h);//update creature
      delete []old_h;
    }
    else if(choice==3)
    {
      cout<<"How many Cyberdemon do you want to buy?"<<endl;
      int newnumber,cost,oldnumber,total,count=0;
      oldnumber=p.get_num_cyber();
      cin>>newnumber;
      cost=newnumber*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      total=newnumber+oldnumber;
      p.set_num_cyber(total);
      cyberdemon *new_h=new cyberdemon[total];//create the dynamic memory 
      cyberdemon *old_h=p.get_cyber();
      string name[newnumber];//create array to store names
      for(int i=0;i<newnumber;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
      }
      for(int x=0;x<oldnumber;x++)
      {
        new_h[x]=old_h[x];
      }
      for(int y=oldnumber;y<total;y++)
      {
        new_h[y]=cyberdemon(2,80,420,10,10,name[count]);
        count=count+1;
      }
      p.set_cyber(new_h);//update creature
      delete []old_h;
    }
    else if(choice==4)
    {
      cout<<"How many Balrogs do you want to buy?"<<endl;
      int newnumber,cost,oldnumber,total,count=0;
      oldnumber=p.get_num_bal();
      cin>>newnumber;
      cost=newnumber*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      total=newnumber+oldnumber;
      p.set_num_bal(total);
      balrogs *new_h=new balrogs[total];//create the dynamic memory 
      balrogs *old_h=p.get_bal();
      string name[newnumber];//create array to store names
      for(int i=0;i<newnumber;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
      }
      for(int x=0;x<oldnumber;x++)
      {
        new_h[x]=old_h[x];
      }
      for(int y=oldnumber;y<total;y++)
      {
        new_h[y]=balrogs(3,120,280,10,10,name[count]);
        count=count+1;
      }
      p.set_b(new_h);//update creature
      delete []old_h;
    }
    else if(choice==5)
    {
      cout<<"How many Chinese do you want to buy?"<<endl;
      int newnumber,cost,oldnumber,total,count=0;
      oldnumber=p.get_num_chinese();
      cin>>newnumber;
      cost=newnumber*20;
      money=money-cost;//charge money
      p.set_money(money);//upadate money
      total=newnumber+oldnumber;
      p.set_num_chinese(total);
      chinese *new_h=new chinese[total];//create the dynamic memory 
      chinese *old_h=p.get_ch();
      string name[newnumber];//create array to store names
      for(int i=0;i<newnumber;i++)
      {
        cout<<"What is the creature name you want to give?"<<endl;
        cin>>name[i];
      }
      for(int x=0;x<oldnumber;x++)
      {
        new_h[x]=old_h[x];
      }
      for(int y=oldnumber;y<total;y++)
      {
        new_h[y]=chinese(4,60,440,20,20,name[count]);
        count=count+1;
      }
      p.set_ch(new_h);//update creature
      delete []old_h;
    }
    else if(choice==6)
    {
      break;
    }
  }while(true);



}
/*********************************************************************   
** Function: givemoney
** Description: give the winner money
** Parameters: world &p
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void givemoney(world &p)
{
  cout<<p.get_name()<<",You win 20 dollars from this round"<<endl;
  int money=p.get_money();
  money=money+20;//give the money to winner
  p.set_money(money);//set new money
}
/*********************************************************************   
** Function: main
** Description: main function
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
** Return: 0
*********************************************************************/
int main()
{ 
  srand(time(NULL));//give different damage everytime
  world p1,p2;
  cout<<"Welcome to Creature Fight!"<<endl;
  string n1,n2;
  getname(n1,n2);
  p1.set_name(n1);//set p1 name
  p2.set_name(n2);//set p2 name
  bool c;
  buy(p1);
  buy(p2);
  int type1,type2,num1,num2,damage1,damage2,win=0,choice1=0,choice2=0;
  pick(p1,type1,num1);//pick to fight
  pick(p2,type2,num2);//pick to fight
  do{
    do
    {
      damage1=determine_damage(type1,num1,p1);
      change_hp(type2,num2,damage1,p2);
      cout<<""<<endl;
      win=check2(type2,num2,p2);
      if(win==1)
        break;
      damage2=determine_damage(type2,num2,p2);
      change_hp(type1,num1,damage2,p1);
      cout<<""<<endl;
      win=check1(type1,num1,p1);
      if(win==2)
        break;
    }while(true);//fight each other and get the winner
    if(win==1)
    {
      cout<<"Player "<<n1<<" won"<<endl;
      get_winner(type1,num1,p1);
      delete_loser(type2,num2,p2);
      givemoney(p1);
      c=checkcontinue(p2);//check if game over
      if(c==false)//check if game over
      {
        cout<<"Game over!"<<n1<<" win the whole game!"<<endl;
        return 0;//quit game
      }
      cout<<"player "<<n1<<",do you want to buy a new creature?(1.Yes 2.No)"<<endl;//ask p1 to buy new
      cin>>choice1;
      if(choice1==1)
      {
        buynew(p1);
      }
      cout<<"player "<<n2<<",do you want to buy a new creature?(1.Yes 2.No)"<<endl;//ask p2 to buy new
      cin>>choice2;
      if(choice2==1)
      {
        buynew(p2);
      }
      cout<<"player "<<n2<<",You need pick another creature to fight!"<<endl;
      pick(p2,type2,num2);
    }
    if(win==2)
    {
      cout<<"Player "<<n2<<" won"<<endl;
      get_winner(type2,num2,p2);
      delete_loser(type1,num1,p1);
      givemoney(p2);
      c=checkcontinue(p1);
      if(c==false)
      {
        cout<<"Game over!"<<n2<<" win the whole game!"<<endl;
        return 0;
      }
      cout<<"player "<<n1<<",do you want to buy a new creature?(1.Yes 2.No)"<<endl;
      cin>>choice1;
      if(choice1==1)
      {
        buynew(p1);
      }
      cout<<"player "<<n2<<",do you want to buy a new creature?(1.Yes 2.No)"<<endl;
      cin>>choice2;
      if(choice2==1)
      {
        buynew(p2);
      }
      cout<<"player "<<n1<<",You need pick another creature to fight!"<<endl;
      pick(p1,type1,num1);
    }
  }while(true);
  
  
  


  
  
  
  return 0;
}
  
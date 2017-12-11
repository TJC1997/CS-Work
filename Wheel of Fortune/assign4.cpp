/****************************************************** 
** Program: Assign4.cpp 
** Author: Yuhang Chen 
** Date: 2/15/2017 
** Description: Wheel of foutune  
** Input: number and letter
** Output: winner and total money
******************************************************/ 


#include<iostream>
#include<cmath>
#include<string>
#include <cstdlib> 
#include <stdio.h>
#include <ctime>
using namespace std;
void play(int &player,int players,int &a,int &b,int &c);
int moneya(int &a,int &b,int &c,int money,int &player);
void buy(string &space, string message, int &player, int players,int &a,int &b,int &c);
string gtm();
/*********************************************************************   
** Function: guessletter
** Description: check if user give a good novowel letter
** Parameters:   none
** Pre-Conditions:  none
** Post-Conditions: none  
** Return:  letter
*********************************************************************/ 
char guessletter()//check if give a novwel letter
{
  bool again=true;
  char l;
  do
  {
    cout<<"guess a no-vowel letter"<<endl;
    cin>>l;
    if(l>='A' && l<='Z')
    {
      l=l-'A'+'a';
    }
    if((l>='a' and l<='z') and (l!='a' and l!='e' and l!='i' and l!='o' and l!='u')) 
    {
      again=false;//stop loop
      return l;//return letter
    }
    else
    {
      cout<<"wrong input"<<endl;//continue loop
    }
  }while(again);
}
/*********************************************************************   
** Function: checkvowel
** Description:  check if user give a vowel letter
** Parameters:   none
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  letter
*********************************************************************/ 
char checkvowel()//check if give a vowel letter
{
  bool again=true;
  char l;
  do
  {
    cout<<"guess a no-vowel letter"<<endl;
    cin>>l;
    if(l>='A' && l<='Z')
    {
      l=l-'A'+'a';
    }
    if(l=='a' or l=='e' or l=='i' or l=='o' or l=='u') 
    {
      again=false;//stop loop
      return l;//return letter
    }
    else
    {
      cout<<"wrong input"<<endl;
    }
  }while(again);
}
/*********************************************************************   
** Function: checkmessage
** Description:  check if user give a correct message
** Parameters:   string t
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  1 or 0
*********************************************************************/ 
int checkmessage(string t)
{
  int a=0;
  for(int i=0;i<t.length();i++)
  {
    if(t[i]>='A' && t[i]<='Z')
    {
      t[i]=tolower(t[i]);//put captial letter to lower letter
    }
    else if ((t[i]>='a'&& t[i]<='z'))//check if it's in A to Z
    {
      ;
    }
    else if(t[i]==' ')//check if it's a space
    {
      ;
    }
    else
    {
      a=1;
      break;//if it's a bad input,change a.
    }
  }
  if(a==1)
  {
    cout<<"bad message"<<endl;//if bad input, a=1
    return 1;
  }
  else
  {
    cout<<"correct message"<<endl;
    return 0;
  } 
}  
/*********************************************************************   
** Function: get message
** Description:  get message from user
** Parameters:   none
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  string m
*********************************************************************/ 
string gtm()//get message
{
  string m,t,get;
  do
  {
    cin.clear();
    cin.ignore(1000, '\n');
    cout<<"Enter a Message:"<<endl;
    getline(cin,m);//use getline to get the message with space

  }while (checkmessage(m));

  return m;
}
/*********************************************************************   
** Function: get space 
** Description:  use message to get space
** Parameters:   string message
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  space
*********************************************************************/ 
string gsom(string message)//get space of message
{
int a;//a=size
  a=message.length();
  string space="";
  for(int b=0;b<a;b++)//check every letters
  {
    if (message[b]==' ')
    {
      space=space+" ";
    }
    else
    {
      space=space+"_";
    }
  }
  cout<<"The message is "<<space<<endl;
  return space;
}
/*********************************************************************   
** Function: go bankrupt
** Description:  let player lose all money
** Parameters:   int player, int &a, int &b, int &c
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  none
*********************************************************************/ 
void go_bankrupt(int player, int &a, int &b, int &c){
    cout<<"You lose all money, change to next player!"<<endl;
    if (player==1)
    {
      a=0;
    }
    if (player==2)
    {
      b=0;
    }
    if (player==3)
    {
      c=0;
    }
}
/*********************************************************************   
** Function: spin
** Description:  spin the wheel and guess letter
** Parameters:   string &space,string message,int &player,int players,int &a,int &b,int &c
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  none
*********************************************************************/ 
void spin(string &space,string message,int &player,int players,int &a,int &b,int &c)//use int & to change two things together
{
  int random=rand()%22,found=0,money=0,amount=0;//a:player one money b:two c:three
  cout<<"Your wheel landed on "<<random<<endl;
  if (random==0)
  {
    go_bankrupt(player, a, b, c);
    player=player%players+1;//change player
  }
  else if (random==21)
  {
    cout<<"You still have the money, but change to next player!"<<endl;
    player=player%players+1;//change player
    
  }
  else
  {
    char l;//l=letter
    string test=message;
    l=guessletter();

    for (int i=0;i<message.length();i++)
    {
      if(message[i]>='A' && message[i]<='Z')
      {
        test[i]=message[i]-'A'+'a';//put capital letter to lower
      }
      if(l>='A' && l<='Z')
      {
        l=l-'A'+'a';
      }
      if(l==test[i])
      {
        space[i]=message[i];
        found=found+1;
      }
    }
    if (found==0)
    {
      cout<<"You guess wrong!Change to next player!"<<endl;
      player=player%players+1;//change player

    }
    else
    {
      money=found*random;
      amount=moneya(a,b,c,money,player);
      cout<<found<<" found. Total: "<<amount<<"$"<<endl;
      cout<<space<<endl;
    }
  }
}
/*********************************************************************   
** Function: setmoney
** Description:  clean the money of loser and give winner money
** Parameters:   int player,int &a,int &b,int &c,int &awin,int &bwin,int &cwin
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  none
*********************************************************************/ 
void setmoney(int player,int &a,int &b,int &c,int &awin,int &bwin,int &cwin)
{
  if(player==1)//clear other players money
  {
    awin+=a;
    b=0;
    c=0;
  }
  if(player==2)
  {
    bwin+=b;
    a=0;
    c=0;
  }
  if(player==3)
  {
    cwin+=c;
    a=0;
    b=0;
  }
}
/*********************************************************************   
** Function: check
** Description:  check if game over
** Parameters:   string &space, string &message, int &player, int players,int &a,int &b,int &c,int &awin,int &bwin,int &cwin
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  1 or 0
*********************************************************************/ 
int check(string &space, string &message, int &player, int players,int &a,int &b,int &c,int &awin,int &bwin,int &cwin)
{
  string guess;
  int next;
  cin.clear();
  cin.ignore(1000, '\n');//clean cin
  cout<<"Input your guess "<<endl;
  getline(cin,guess);
  if(guess!=message)
  {
    cout<<"Wrong!"<<endl;
    player=player%players+1;
    return 1;
  }
  else
  {
    cout<<"Good job!"<<endl;
    setmoney(player,a,b,c,awin,bwin,cwin);
    cout<<"player "<<player<<" win the game "<<endl; 
    for(int i=1;i<=players;i++)
    {
      if(i==1)
        cout<<"player "<<i<<" total: "<<awin<<endl;
      if(i==2)
        cout<<"player "<<i<<" total: "<<bwin<<endl;
      if(i==3)
        cout<<"player "<<i<<" total: "<<cwin<<endl;
    }      
    cout<<"Do you want next round?(1.Yes 2.No) "<<endl;
    cin>>next;
    if (next==1)
    {
      message=gtm();//g=message
      space=gsom(message);//s=space
      return 1;
    }
    else
    {
      cout<<"Good Bye!"<<endl;
      return 0;
    }
  }

}
/*********************************************************************   
** Function: checkp
** Description:  check if player have enough money to buy
** Parameters:   int &a,string message,string &space
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  none
*********************************************************************/ 
void checkp(int &a,string message,string &space)
{
  if(a<10)//check if player have enough money
  {
    cout<<"You don't have enough money"<<endl;
  }
  else
  {
    char l;//l=letter
    string test=message;
    l=checkvowel();
    for (int i=0;i<message.length();i++)
    {
      if(message[i]>='A' && message[i]<='Z')
      {
        test[i]=message[i]-'A'+'a';
      }
      if(l>='A' && l<='Z')
      {
        l=l-'A'+'a';
      }
      if(l==test[i])
      {
        space[i]=message[i];//change space to a new space
      }
    }
    cout<<"You lose 10 dollars"<<endl;
    a=a-10;
    cout<<"Total: "<<a<<endl;
    cout<<space<<endl;
    }
}

/*********************************************************************   
** Function: buy
** Description: let user buy a voel 
** Parameters:   string &space, string message, int &player, int players,int &a,int &b,int &c
** Pre-Conditions:  checkp
** Post-Conditions:   none
** Return:  none
*********************************************************************/ 
void buy(string &space, string message, int &player, int players,int &a,int &b,int &c)
{
  if (player==1)
  {
    checkp(a,message,space);
  }
  if (player==2)
  {
    checkp(b,message,space);
  }
  if (player==3)
  {
    checkp(c,message,space);
  }
}
/*********************************************************************   
** Function: play
** Description:  let user start game
** Parameters:   int &player,int players,int &a,int &b,int &c
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  none
*********************************************************************/   
void play(int &player,int players,int &a,int &b,int &c)
{
  int choose,checka=0,get=1,awin=0,bwin=0,cwin=0;
  string message="",space="";
  message=gtm();//g=message
  space=gsom(message);//s=space
  do
  {
    cout<<"Player"<<player<<endl;
    cout<<"Do you want to spin(1),solve the puzzle(2),or buy a vowel(3): "<<endl;
    cin>>choose;
    if (choose==1)
    {
      spin(space,message,player,players,a,b,c);
      checka=0;
    }
    else if (choose==2)
    {
      get=check(space,message,player,players,a,b,c,awin,bwin,cwin);
      checka=0;
    }
    else if (choose==3)
    {
      buy(space,message,player,players,a,b,c);
      checka=0;
    }
    else
    {
      checka=1;//if input wrong let checka=1 to make loop run again
    }
    }while(get or checka);
}
/*********************************************************************   
** Function: moneya
** Description:  give money to each player
** Parameters: int &a,int &b,int &c,int money,int &player  
** Pre-Conditions:  none
** Post-Conditions:   none
** Return:  a,b,c
*********************************************************************/ 
int moneya(int &a,int &b,int &c,int money,int &player)//use int& to change money
{
  if (player==1)
  {
    a=a+money;
    return a;
  }
  if (player==2)
  {
    b=b+money;
    return b;
  }
  if (player==3)
  {
    c=c+money;
    return c;
  }
}


int main()
{
  int player=1,players;//number of player
  int a=0,b=0,c=0;
  srand(time(NULL));
  while(1)//use while true to forbid wrong input
  {
    cout<<"how many players do you have?"<<endl;
    cin>>players;
    if(players>=1 and players<=3)
    {
      break;
    }
  }

  play(player,players,a,b,c);
  return 0;
}

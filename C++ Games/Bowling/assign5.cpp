/****************************************************** 
** Program: Assign5.cpp 
** Author: Yuhang Chen 
** Date: 3/2/2017
** Description: Bowling 
** Input: number and letter
** Output: winner and total score
******************************************************/ 


#include<iostream>
#include<cstring>
#include <ctime>
#include <cstdlib> 
#include<cmath>
#include <stdlib.h>
#include <stdio.h>

using namespace std;

char *table(int players,char p1[],char p2[],char p3[],char p4[],char p5[]);
void play10(char *board,int s[],int p,char p1[],char p2[],char p3[],char p4[],char p5[],int players,int s1[],int s2[],int s3[],int s4[],int s5[]);
void section10(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]);
char *table(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]);
void play(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]);

/*********************************************************************   
** Function: firstline
** Description: give the firstline of frame
** Parameters:   none
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/ 
void firstline()
{
  char form[]="Name      |1 |2 |3 |4 |5 |6 |7 |8 |9 |10 |Total|";//This is first line of form
  cout<<form<<endl;
}

/*********************************************************************   
** Function: playform
** Description: initialize the playform
** Parameters:   char p[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/ 
void playform(char p[])
{
  int i;
  for(i=10;i<42;i++)//43 room totally
  {
    if((i%3)==1)
    {
      p[i]='|';
    }
    else
    {
      p[i]=' ';
    }
  }
  p[40]=' ';
  p[41]='|';
  p[42]='\0';//put nonchar in the end
  cout<<p<<endl;
}

/*********************************************************************   
** Function: scoreform
** Description: cout scoreform
** Parameters:   int s[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/ 
void scoreform(int s[])
{
  for(int i=0;i<10;i++)//use for loop cout every elements in array
  {
    cout<<" "<<i+1<<":"<<s[i];
  }
  cout<<"   "<<s[10]<<"    "<<endl;//s[10]is total score
}

/*********************************************************************   
** Function: form
** Description: cout playform and scoreform together
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/  
void form(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[])
{
  for(int i=1; i<=players; i++){//use for loop to check i and cout each player frame
  if (i==1)
  {
    playform(p1);//cout playform first and then scoreform
    scoreform(s1);
  }
  else if (i==2)//use else if to make program quickly
  {
    playform(p2);
    scoreform(s2);
  }
  else if (i==3)
  {
    playform(p3);
    scoreform(s3);
  }
  else if (i==4)
  {
    playform(p4);
    scoreform(s4);
  }
  else if (i==5)
  {
    playform(p5);
    scoreform(s5);
  }
}
}

/*********************************************************************   
** Function: playnum
** Description: check how may players
** Parameters: none
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: players
*********************************************************************/  
int playernum()
{
  int players;
  do
  {
    cout<<"How many players(1-5)? "<<endl;
    cin>>players;
  }while (players<1 or players>5);//use do while to check if input is right
  return players;//return players to main function
}

/*********************************************************************   
** Function: getline
** Description: put the name into program 
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/  
void getline(char p[])
{
  int length;
  cin.getline(p,10);//give 10 room for name
  length=strlen(p);//get the length of p
  p[length]=' ';//change '\0' to ' '
  for(int x=length;x<38;x++)//change all room to ' '
    p[x]=' ';
}
  
/*********************************************************************   
** Function: getname
** Description: get name of users
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/    
void getname(int players,char p1[],char p2[],char p3[],char p4[],char p5[])
{
  for (int i=1;i<=players;i++)//use for loop to save space
  {
    cout<<"what's your name "<<endl;
    if (i==1)
    {
      cin.ignore(1);
      getline(p1);//call getline to get name
    }
    else if(i==2)//use else if to make program fast
    {
      getline(p2);
    }
    else if(i==3)
    {
      getline(p3);
    }
    else if(i==4)
    {
      getline(p4);
    }
    else if(i==5)
    {
      getline(p5);
    }
  }
}

/*********************************************************************   
** Function: play10
** Description: for 10th bowling
** Parameters: char *board,int s[],int p,char p1[],char p2[],char p3[],char p4[],char p5[],int players,int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/   
void play10(char *board,int s[],int p,char p1[],char p2[],char p3[],char p4[],char p5[],int players,int s1[],int s2[],int s3[],int s4[],int s5[])//p=player
{  
  int pinone,chance=1,pintwo,left;
  cout<<"Player "<<p<<",press enter to bowl."<<endl;//p=player
  cin.ignore();
  srand(time(NULL));//this make sure change the random number
  pinone=rand()%11;//random=0to10
  if (pinone==10)
  {
    cout<<"Good job! You got a strike!"<<endl;
    board[38]='x';//let play form[38] become x
    s[9]=10;//get 10 points and store it in score board
    table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);//call table to cout the frame
    cout<<"Player "<<p<<",press enter to bowl."<<endl;
    cin.ignore();
    pinone=rand()%11;
    if (pinone==10)
    {
      cout<<"Good job! You got a strike!"<<endl;
      board[39]='x';
      s[9]=20;
      table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      cout<<"Player "<<p<<",press enter to bowl."<<endl;
      cin.ignore();//this is let user enter to continue
  
      pinone=rand()%11;
      if (pinone==10)
      {
        s[9]=30;
        cout<<"Good job! You got a strike!"<<endl;
        board[40]='x';
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
      else
      {
        cout<<"You knocked down "<<pinone<<" pins"<<endl;
        s[9]=s[9]+pinone;
        int num=char(pinone);
        board[40]=char(num+48);//use aslii number  int number=char number+48
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
    }
    else if(pinone==0)
    {
      cout<<"Awe, you got a gutter ball, 0 pins."<<endl;
      board[39]='0';
      table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);//once you get a score,you need print table
      cout<<"Player "<<p<<",press enter to bowl."<<endl;
      cin.ignore();
    
      pinone=rand()%11;
      if(pinone==10)
      {
        cout<<"Good job! You got a strike!"<<endl;
        board[40]='x';
        s[9]=20;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
      else
      {
        cout<<"You knocked down "<<pinone<<" pins"<<endl;
        board[40]=char(char(pinone)+48);
        s[9]=s[9]+pinone;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
    }
    else
    {
      cout<<"You knocked down "<<pinone<<" pins"<<endl;
      int num=char(pinone);
      board[39]=char(num+48);
      s[9]=s[9]+pinone;
      table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      left=11-pinone; //use left to get what is maxinum bowl you can get
      cout<<"Player "<<p<<",press enter to bowl."<<endl;
      cin.ignore();

      pintwo=rand()%left;
      if (pinone+pintwo==10)//if first throw +second throw=10,you get a spare
      {
        cout<<"You get a spare"<<endl;
        board[40]='/';
        s[9]=20;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
      else
      {
        cout<<"You knocked down "<<pintwo<<" pins"<<endl;
        board[40]=char(char(pintwo)+48);
        s[9]=s[9]+pintwo;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
    }
   
  }
  else if(pinone==0)
  {
    cout<<"Awe, you got a gutter ball, 0 pins."<<endl;
    board[38]='0';
    s[9]=0;
    table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);

    pinone=rand()%11;
      if (pinone==10)
      {
        cout<<"You get a spare"<<endl;
        board[39]='/';
        s[9]=10;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
        cout<<"Player "<<p<<",press enter to bowl."<<endl;
        cin.ignore();

        pinone=rand()%11;
        if(pinone==10)
        {
          cout<<"Good job! You got a strike!"<<endl;
          board[40]='x';
          s[9]=20;
          table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
        } 
      }
      else
      {
        cout<<"You knocked down "<<pinone<<" pins"<<endl;
        int num=char(pinone);
        board[39]=char(num+48);
        board[40]=' ';//if you cannot get strike or spare on 10th frame,you cannot get third throw
        s[9]=s[9]+pinone;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }  
  }
  else
  {
    cout<<"You knocked down "<<pinone<<" pins"<<endl;
    board[38]=char(char(pinone)+48);
    s[9]=pinone;
    table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);

    left=11-pinone;  
    pintwo=rand()%left;
      if (pinone+pintwo==10)
      {
        cout<<"You get a spare"<<endl;
        board[39]='/';
        s[9]=10;
        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
        cout<<"Player "<<p<<",press enter to bowl."<<endl;
        cin.ignore();

        pinone=rand()%11;
        if(pinone==10)
        {
          cout<<"Good job! You got a strike!"<<endl;
          board[40]='x';
          s[9]=20;
          table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
        }
        else
        {
          cout<<"You knocked down "<<pinone<<" pins"<<endl;
          int num=char(pinone);
          s[9]=s[9]+pinone;
          board[40]=char(num+48);
          table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
        }
        
      }
      else
      {
        cout<<"You knocked down "<<pintwo<<" pins"<<endl;
        int num=char(pintwo);
        board[39]=char(num+48);
        s[9]=s[9]+pintwo;
        board[40]=' ';

        table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      }
  }
}
  
/*********************************************************************   
** Function: section10
** Description: according to players, call different play10
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/  
void section10(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[])
{
  if (players==1)
  {
    play10(p1,s1,1,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
  }
  else if (players==2)
  {
    play10(p1,s1,1,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p2,s2,2,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);//according to different players, choose different parameters
  }
  else if (players==3)
  {
    play10(p1,s1,1,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p2,s2,2,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p3,s3,3,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
  }
  else if (players==4)//use else if to make program fast
  {
    play10(p1,s1,1,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p2,s2,2,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p3,s3,3,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p4,s4,4,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
  }
  else if (players==5)
  {
    play10(p1,s1,1,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p2,s2,2,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p3,s3,3,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p4,s4,4,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
    play10(p5,s5,5,p1,p2,p3,p4,p5,players,s1,s2,s3,s4,s5);
  }
}

/*********************************************************************   
** Function: table
** Description: according to players,cout different frame
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: *char
*********************************************************************/ 
char *table(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[])
{
  firstline();
  if (players==1)
  {
    cout<<p1<<endl;
    scoreform(s1);
    return p1;//return play form
  }
  if (players==2)
  {
    cout<<p1<<endl;
    scoreform(s1);
    cout<<p2<<endl;//because players are 2, cout 2 form
    scoreform(s2);
    return p2;
  }
  if (players==3)
  {
    cout<<p1<<endl;
    scoreform(s1);
    cout<<p2<<endl;
    scoreform(s2);
    cout<<p3<<endl;
    scoreform(s3);
    return p3;
  }
  if (players==4)
  {
    cout<<p1<<endl;
    scoreform(s1);
    cout<<p2<<endl;
    scoreform(s2);
    cout<<p3<<endl;
    scoreform(s3);
    cout<<p4<<endl;
    scoreform(s4);
    return p4;
  }
  if (players==5)//same idea 
  {
    cout<<p1<<endl;
    scoreform(s1);
    cout<<p2<<endl;
    scoreform(s2);
    cout<<p3<<endl;
    scoreform(s3);
    cout<<p4<<endl;
    scoreform(s4);
    cout<<p5<<endl;
    scoreform(s5);
    return p5;
  }
}

/*********************************************************************   
** Function: check
** Description: according to position,fetch different score from playform and count the score and assign them into scoreform
** Parameters: char p[],int s[],int position
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/ 
void check(char p[],int s[],int position)
{
  int a,b;//use a,b to count score
  if (position==11 or position==12)//first frame
  {
    if (p[11]<='9' and p[11]>='0' and p[12]<='9' and p[12]>='0')//if two bowl score below 10,they can add together
    {
      a=p[11]-'0';
      b=p[12]-'0';
      s[0]=a+b;//assign first score 
    }
  }
  else if(position==14 or position==15)//second frame
  {
    if (p[14]<='9' and p[14]>='0' and p[15]<='9' and p[15]>='0')//if two bowl score below 10,they can add together
    {
      a=p[14]-'0';
      b=p[15]-'0';
      s[1]=a+b;
    }
    if (p[12]=='/' and p[14]!=' ')//if get spare and get strike,it is 20
    {
       if (p[14]=='x')
       {
         s[0]=20;
       }
       else
       {
         s[0]=10+p[14]-'0';//if get spare and get number below 10, it is 10+number
       }
    }
  }
  else if(position==17 or position==18)//third frame
  {
    if (p[17]<='9' and p[17]>='0' and p[18]<='9' and p[18]>='0')//same
    {
      a=p[17]-'0';
      b=p[18]-'0';
      s[2]=a+b;
    }
    if (p[15]=='/' and p[17]!=' ')//same
    {
       if (p[17]=='x')
       {
         s[1]=20;
       }
       else
       {
         s[1]=10+p[17]-'0';
       }
    }
    if (p[11]=='x')
    {
      if(p[14]=='x')
      {
        if(p[17]=='x')
        {
          s[0]=30;//if get 3strike,you get 30 points
        }
        else
        {
          s[0]=20+p[17]-'0';//if you get 2strike,you get 20 points +number
        }
      }
      
      else if(p[15]=='/')//same
      {
        s[0]=20;
      }
      else//same
      {
        s[0]=10+p[14]-'0'+p[15]-'0';
      }
    }
  }
  else if(position==20 or position==21)//forth frame
  {
    if (p[20]<='9' and p[20]>='0' and p[21]<='9' and p[21]>='0')//same
    {
      a=p[20]-'0';
      b=p[21]-'0';
      s[3]=a+b;
    }
    if (p[18]=='/' and p[20]!=' ')//same
    {
       if (p[20]=='x')
       {
         s[2]=20;
       }
       else
       {
         s[2]=10+p[20]-'0';
       }
    }
    if (p[14]=='x')
    {
      if(p[17]=='x')
      {
        if(p[20]=='x')//same
        {
          s[1]=30;
        }
        else
        {
          s[1]=20+p[20]-'0';
        }
      }
      
      else if(p[18]=='/')//same
      {
        s[1]=20;
      }
      else
      {
        s[1]=10+p[17]-'0'+p[18]-'0';
      }
    }
  }
  else if(position==23 or position==24)//fifth frame
  {
    if (p[23]<='9' and p[23]>='0' and p[24]<='9' and p[24]>='0')//same
    {
      a=p[23]-'0';
      b=p[24]-'0';
      s[4]=a+b;
    }
    if (p[21]=='/' and p[23]!=' ')//same
    {
       if (p[23]=='x')
       {
         s[3]=20;
       }
       else
       {
         s[3]=10+p[23]-'0';
       }
    }
    if (p[17]=='x')//same
    {
      if(p[20]=='x')
      {
        if(p[23]=='x')
        {
          s[2]=30;
        }
        else
        {
          s[2]=20+p[23]-'0';
        }
      }
      
      else if(p[21]=='/')
      {
        s[2]=20;
      }
      else
      {
        s[2]=10+p[20]-'0'+p[21]-'0';
      }
    }
  }
  else if(position==26 or position==27)//sixth frame
  {
    if (p[26]<='9' and p[26]>='0' and p[27]<='9' and p[27]>='0')//same
    {
      a=p[26]-'0';
      b=p[27]-'0';
      s[5]=a+b;
    }
    if (p[24]=='/' and p[26]!=' ')//same
    {
       if (p[26]=='x')
       {
         s[4]=20;
       }
       else
       {
         s[4]=10+p[26]-'0';
       }
    }
    if (p[20]=='x')//same
    {
      if(p[23]=='x')
      {
        if(p[26]=='x')
        {
          s[3]=30;
        }
        else
        {
          s[3]=20+p[26]-'0';
        }
      }
      
      else if(p[24]=='/')
      {
        s[3]=20;
      }
      else
      {
        s[3]=10+p[23]-'0'+p[24]-'0';
      }
    }
  }
  else if(position==29 or position==30)//seventh frame
  {
    if (p[29]<='9' and p[29]>='0' and p[30]<='9' and p[30]>='0')//same
    {
      a=p[29]-'0';
      b=p[30]-'0';
      s[6]=a+b;
    }
    if (p[27]=='/' and p[29]!=' ')//same
    {
       if (p[29]=='x')
       {
         s[5]=20;
       }
       else
       {
         s[5]=10+p[29]-'0';
       }
    }
    if (p[23]=='x')
    {
      if(p[26]=='x')
      {
        if(p[29]=='x')//same
        {
          s[4]=30;
        }
        else
        {
          s[4]=20+p[26]-'0';
        }
      }
      
      else if(p[27]=='/')
      {
        s[4]=20;
      }
      else
      {
        s[4]=10+p[26]-'0'+p[27]-'0';
      }
    }
  }
  else if(position==32 or position==33)//eighth frame
  {
    if (p[32]<='9' and p[32]>='0' and p[33]<='9' and p[33]>='0')//same
    {
      a=p[32]-'0';
      b=p[33]-'0';
      s[7]=a+b;
    }
    if (p[30]=='/' and p[32]!=' ')//same
    {
       if (p[30]=='x')
       {
         s[6]=20;
       }
       else
       {
         s[6]=10+p[32]-'0';
       }
    }
    if (p[26]=='x')
    {
      if(p[29]=='x')
      {
        if(p[32]=='x')//same
        {
          s[5]=30;
        }
        else
        {
          s[5]=20+p[29]-'0';
        }
      }
      
      else if(p[30]=='/')
      {
        s[5]=20;
      }
      else
      {
        s[5]=10+p[29]-'0'+p[30]-'0';
      }
    }
  }
  else if(position==35 or position==36)//ninth frame
  {
    if (p[35]<='9' and p[35]>='0' and p[36]<='9' and p[36]>='0')//same
    {
      a=p[35]-'0';
      b=p[36]-'0';
      s[8]=a+b;
    }
    if (p[33]=='/' and p[35]!=' ')//same
    {
       if (p[33]=='x')
       {
         s[7]=20;
       }
       else
       {
         s[7]=10+p[35]-'0';
       }
    }
    if (p[29]=='x')
    {
      if(p[32]=='x')
      {
        if(p[35]=='x')//same
        {
          s[6]=30;
        }
        else
        {
          s[6]=20+p[32]-'0';
        }
      }
      
      else if(p[33]=='/')
      {
        s[6]=20;
      }
      else
      {
        s[6]=10+p[32]-'0'+p[33]-'0';
      }
    }
  }
  
}

/*********************************************************************   
** Function: getrandom
** Description: get random number and put it into playform
** Parameters: int a,char p[],int &position,int pinone,int s[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: random number
*********************************************************************/ 
int getrandom(int a,char p[],int &position,int pinone,int s[])
{
  int random;
  check(p,s,position);
  srand(time(NULL));//make sure you get different number
  random=rand()%a;//get a from last function
  if (p[position]=='|')
  {
    position=position+1;//if it is '|',goto next position
  }
  if (random==0)
  {
    cout<<"Awe, you got a gutter ball, 0 pins."<<endl;
    p[position]='0';//assign 0 to this position
    check(p,s,position);//use check to upate scoreform
    position=position+1;//goto next position
  }
  else if (random==10)
  {
    cout<<"Good job! You got a strike!"<<endl;
    p[position]='x';
    check(p,s,position);
    position=position+3;//if you get strike,you pass next bowl and the'|'
  }
  else
  {
    cout<<"You knocked down "<<random<<" pins"<<endl;
    int num=char(random);
    p[position]=char(num+48);
    check(p,s,position);
    if ((pinone+random)==10)
    {
      cout<<"You get a spare"<<endl;
      p[position]='/';  
      check(p,s,position);
    }
    position=position+1;
  }
  s[10]=s[0]+s[1]+s[2]+s[3]+s[4]+s[5]+s[6]+s[7]+s[8]+s[9];//total number=10 frame score
  return random;
}  

/*********************************************************************   
** Function: play
** Description: let all players play the game
** Parameters: int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[]
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/
void play(int players,char p1[],char p2[],char p3[],char p4[],char p5[],int s1[],int s2[],int s3[],int s4[],int s5[])
{
  int player=1,pinone,pintwo,left,round=0,chance=0,position1=10,position2=10,position3=10,position4=10,position5=10;
  char *get;

  do
  {
    cout<<"Player "<<player<<",press enter to bowl."<<endl;
    chance=chance+1;//once you bowl, you use one chance
    cin.ignore();//use enter to continue
    if(player==1)
    {
      pinone=getrandom(11,p1,position1,0,s1);
    }
    if(player==2)
    {
      pinone=getrandom(11,p2,position2,0,s2);
    }
    if(player==3)
    {
      pinone=getrandom(11,p3,position3,0,s3);
    }
    if(player==4)
    {
      pinone=getrandom(11,p4,position4,0,s4);
    }
    if(player==5)
    {
      pinone=getrandom(11,p5,position5,0,s5);//according to different player,give different parameter
    }
    get=table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);//use get to store table

    if (pinone==10 or chance==2)
    {
      player=player%players+1;//change player
      chance=0;//initialize chance
    }
    else
    {
      left=10-pinone+1;//get the number of left
      cout<<"Player "<<player<<",press enter to bowl."<<endl;
      chance=chance+1;
      cin.ignore();
      if(player==1)
      {
        pintwo=getrandom(left,p1,position1,pinone,s1);//let left as maximun in random number
      }
      if(player==2)
      {
        pintwo=getrandom(left,p2,position2,pinone,s2);
      }
      if(player==3)
      {
        pintwo=getrandom(left,p3,position3,pinone,s3);
      }
      if(player==4)
      {
        pintwo=getrandom(left,p4,position4,pinone,s4);
      }
      if(player==5)
      {
        pintwo=getrandom(left,p5,position5,pinone,s5);
      }
      get=table(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
      player=player%players+1;//change player
    }   
  }while(get[36]==' ' and get[35]!='x');//check if run out of all the room
  section10(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);//call section10 to start frame 10
}
  
/*********************************************************************   
** Function: checkwinner
** Description: check who win the game
** Parameters: int *s1,int *s2,int *s3,int *s4,int *s5
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/
void checkwinner(int *s1,int *s2,int *s3,int *s4,int *s5)
{
  int num[5],player;
  int i;
  int a=s1[10],b=s2[10],c=s3[10],d=s4[10],e=s5[10];//fetch total score
  num[0]=a;
  num[1]=b;
  num[2]=c;
  num[3]=d;
  num[4]=e;//assign total score in same array
  int max=num[0];
  for (i=0;i<5;i++)
  {
    if (num[i]>max)
    {
      max=num[i];//upate the max number
    }
  }
  if (max==a)
    player=1;
  if (max==b)
    player=2;
  if (max==c)
    player=3;
  if (max==d)
    player=4;
  if (max==e)//check who win the game
    player=5; 
  cout<<"player"<<player<<" win the game"<<endl;//cout the name of player
}
  
/*********************************************************************   
** Function: main
** Description: head function
** Parameters: none
** Pre-Conditions:  none
** Post-Conditions: none  
** Return: none
*********************************************************************/
int main()
{
  int players;//number of players
  char p1[45],p2[45],p3[45],p4[45],p5[45];//5 players'name
  int s1[11]={0};
  int s2[11]={0};
  int s3[11]={0};
  int s4[11]={0};
  int s5[11]={0};
  players=playernum();
  getname(players,p1,p2,p3,p4,p5);
  firstline();
  form(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
  play(players,p1,p2,p3,p4,p5,s1,s2,s3,s4,s5);
  checkwinner(s1,s2,s3,s4,s5);

  
}
  
/*
Program name:  CS161#5 Farkle
Author:        Yuhang Chen (Tony)
Date:          March,6th,2018
*/

#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>

using namespace std;

//declaration
void num_of_players(int&players);
int* make_score_broad(int players);
void roll(int* &dice,int size);
void sort(int*&dice,int size);
bool single_one(int* dice,int size);
bool single_five(int* dice,int size);
bool three_x(int* dice,int size,int x); 
bool four_of_kind(int* dice,int size);
bool five_of_kind(int* dice,int size);
bool six_of_kind(int* dice,int size);
bool straight(int* dice,int size);
bool pairs(int* dice,int size);
bool four_and_pair(int* dice,int size);
bool two_triplets(int* dice,int size);
bool farkle(int *check);
bool is_valid_option(int *check,int a);
int count(int *dice,int n,int size);
int get_score(int a,int &size,int* dice);
int check_options(int* dice,int &size);
void update_score(int p,int* &score,int round_score);
void print_score(int* score,int players);
void print_farkle(int* score,int players,int p);
void bouns(int p,int &total,int &turn_score);
void play(int p,int* &score,int players);
bool check_10000(int*score,int players,int *p);
void last_round(int p,int* &score,int players);



int main(){ 
  srand(time(NULL));
  int players,p=0;
  num_of_players(players);            //get the number of players
  int*score;
  score=make_score_broad(players);    //make scoreboard
  while(true)
  {
    play(p,score,players);            //let a player to play one round
    if(check_10000(score,players,&p)==true)//check if any player get 10000 pts
    {
      cout<<"Player"<<p+1<<" hits 10000 pts!Let's play the last round!"<<endl;
      break;
    }
    p=(p+1)%players;                    //change to next player
  }
  last_round(p,score,players);          //let all other players play last round
  delete []score;                        //delete score board
  return 0;
}

/*********************************************************************
** Function:     num_of_players
** Description:  get the number of players from user
** Parameters:   players store the number of players
** Return:       None
*********************************************************************/
 
void num_of_players(int&players)//use reference to change the original value of players
{
  cout<<"How many players do you have?"<<endl;
  cin>>players;
}

/*********************************************************************
** Function:     make_score_broad
** Description:  make a 1-D score broad according to player number
** Parameters:   players store the number of players
** Return:       score board
*********************************************************************/
 
int* make_score_broad(int players)
{
  int*score=new int[players];        //create space in heap
  for(int i=0;i<players;i++)
  {
    score[i]=0;                      //set all the score to 0
  }
  return score;
}

/*********************************************************************
** Function:     play
** Description:  let one player play until farkle or he decides to store the points
** Parameters:   p is the player who is playing this round, score is the score borad, players store the number of players
** Return:       score board
*********************************************************************/
 
void play(int p,int* &score,int players)
{
  int size=6,total=0,turn_score=0;                        //number of dice start from 6
  while(true)
  {
    int *dice=new int [size],choice;          //made dynamic array to store dice
    cout<<"Hello,Player "<<p+1<<endl;
    roll(dice,size);
    sort(dice,size);
    turn_score=check_options(dice,size);          //check what options can use score
    total=total+turn_score;
    cout<<"Player "<<p+1<<",you get "<<total<<" this round so far!"<<endl;
    cout<<"You have "<<size<<" dices left"<<endl;
    delete []dice;                    //delete the old dice
    if(turn_score==0)                //if it's farkle,quit loop
      break;
    if(size==0)  
      cout<<"You can get a bouns round!"<<endl;
    cout<<"Do you want to continue?(1.Yes 2.No)"<<endl;
    cin>>choice;
    cout<<""<<endl;
    if(choice==2)                  //if choose no,break
      break;
    if(size==0)                 
    {    
      bouns(p,total,turn_score);
      break;
    }
  }
  if(turn_score!=0)                  //if it's not farkle
  {
    update_score(p,score,total);
    cout<<""<<endl;
    print_score(score,players);
    cout<<""<<endl;
  }
  else
  {
    cout<<""<<endl;
    print_farkle(score,players,p);
    cout<<""<<endl;
  }
}

/*********************************************************************
** Function:     check_options
** Description:  according to dice, check which the options are able to choosen by user and print them
** Parameters:   dice is the array to store dices, size is the array size
** Return:       the score got by user
*********************************************************************/
 
int check_options(int* dice,int &size)
{
  int check[15];                    //use check array to keep tracking which option is valid
  for(int i=0;i<15;i++)
  {
    check[i]=0;                      //set each option to flase by default
  }
  cout<<"You can choose the following options to score:"<<endl;
  if(single_one(dice,size)==1)
  {
    cout<<"1.single 1 (100 pts)"<<endl;
    check[0]=1;                      //if the option is valid,set it to check[option] to one
  }
  if(single_five(dice,size)==1)
  {
    cout<<"2.single 5 (50 pts)"<<endl;
    check[1]=1;
  }
  if(three_x(dice,size,1)==1)
  {
    cout<<"3.Three 1's (300 pts)"<<endl;
    check[2]=1;
  }
  if(three_x(dice,size,2)==1)
  {
    cout<<"4.Three 2's (200 pts)"<<endl;
    check[3]=1;
  }
  if(three_x(dice,size,3)==1)
  {
    cout<<"5.Three 3's (300 pts)"<<endl;
    check[4]=1;
  }
  if(three_x(dice,size,4)==1)
  {
    cout<<"6.Three 4's (400 pts)"<<endl;
    check[5]=1;
  }
  if(three_x(dice,size,5)==1)
  {
    cout<<"7.Three 5's (500 pts)"<<endl;
    check[6]=1;
  }
  if(three_x(dice,size,6)==1)
  {
    cout<<"8.Three 6's (600 pts)"<<endl;
    check[7]=1;
  }
  if(four_of_kind(dice,size))
  {
    cout<<"9.Four of any number (1000 pts)"<<endl;
    check[8]=1;
  }
  if(five_of_kind(dice,size))
  {
    cout<<"10.Five of any number (2000 pts)"<<endl;
    check[9]=1;
  }
  if(six_of_kind(dice,size))
  {
    cout<<"11.Six of any number (3000 pts)"<<endl;
    check[10]=1;
  }
  if(straight(dice,size))
  {
    cout<<"12.Straight (1500 pts)"<<endl;
    check[11]=1;
  }
  if(pairs(dice,size))
  {
    cout<<"13.Three pair (1500 pts)"<<endl;
    check[12]=1;
  }
  if(four_and_pair(dice,size))
  {
    cout<<"14.Four numbers + a pair (1500 pts)"<<endl;
    check[13]=1;
  }
  if(two_triplets(dice,size))
  {
    cout<<"15.Two triplets (2500 pts)"<<endl;
    check[14]=1;
  }
  if(farkle(check))                            //if all the options are not avaliable,get farkle
  {
    cout<<"Farkle!"<<endl;
    return 0;
  }
  else
  {
    int a=0;
    do{
      cout<<"Which option do you want to choose?"<<endl;
      cin>>a;
      cout<<""<<endl;
    }while(is_valid_option(check,a-1));          //use this function to check if it's a valid option
    int score=get_score(a,size,dice);            //get the final score
    return score;
  }
}

/*********************************************************************
** Function:     roll
** Description:  roll all the dices and store them into dice array
** Parameters:   dice is the array to store dices, size is the array size
** Return:       none
*********************************************************************/

void roll(int* &dice,int size)
{
  cout<<"Your dices are: ";
  for(int i=0;i<size;i++)
  {
    dice[i]=rand()%6+1;              //generate random number from 1-6
    cout<<dice[i]<<" ";
  }
  cout<<""<<endl;
}
/*********************************************************************
** Function:     sort
** Description:  sort dice form small to high
** Parameters:   dice is the array to store dices, size is the array size
** Return:       none
*********************************************************************/
void sort(int*&dice,int size)
{
  for(int i=0;i<size-1;i++)
  {
    for(int i=0;i<size-1;i++)
    {
      if(dice[i]>dice[i+1])                  //sort dice from smaller to bigger
      {
        int temp=dice[i];
        dice[i]=dice[i+1];
        dice[i+1]=temp;
      }
    }
  }
  cout<<"After sort are: ";
  for(int i=0;i<size;i++)
  {
    cout<<dice[i]<<" ";
  }
  cout<<""<<endl;
  cout<<""<<endl;
}
//check if there is a single one in dice array
bool single_one(int* dice,int size)
{
  for(int i=0;i<size;i++)
  {
    if(dice[i]==1)
    {
      return true;                          //once find a single one,return ture
    }
  }
  return false;
}
//check if there is a single 5 in dice array
bool single_five(int* dice,int size)
{
  for(int i=0;i<size;i++)
  {
    if(dice[i]==5)
    {
      return true;                            //once find a single 5,return true
    }
  }
  return false;
}
//check if there are 3 same dices
bool three_x(int* dice,int size,int x)    //three_x can check three 1/2/3/4/5/6
{
  int counter=0;    
  for(int i=0;i<size;i++)
  {
    if(dice[i]==x)
    {
      counter++;
    }
  }  
  if(counter>=3)                          //if there are more than three x, return true
  {
    return true;
  }
  else
  {
    return false;
  }
}
//check if there are 4 same dices
bool four_of_kind(int* dice,int size)
{
  if(size<4)                            //if size smaller than 4, it cannot be four of any
  {
    return false;
  }
  if(size>=4)                           //if size>=4, we can check dice index 0-3
  {
    if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3])
    {
      return true;
    }
  }
  if(size>=5)                           //if size>=5, we can check dice index 1-4
  {
    if(dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4])
    {
      return true;
    }
  }
  if(size==6)                           //if size==6, we can check dice index 2-5
  {
    if(dice[2]==dice[3] && dice[3]==dice[4] && dice[4]==dice[5])
    {
      return true;
    }
  }
  return false;                          //if 0-3,1-4,2-5 are not four of a kind, return false
}
//check if there are 5 same dices
bool  five_of_kind(int* dice,int size)
{
  if(size<5)
  {
    return false;
  }
  if(size>=5)                            //if size>=5, we can check 0-4
  {
    if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4])
    {
      return true;
    }
  }
  if(size==6)                            //if size==6, we can check 1-5
  {
    if(dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4] && dice[4]==dice[5])
    {
      return true;
    }
  }
  return false;                          //if 0-4,1-5 are not five of a kind, retrun false
}
//check if there are 6 same dices
bool six_of_kind(int* dice,int size)
{
  if(size<6)
  {
    return false;
  }
  else if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3] && dice[3]==dice[4] && dice[4]==dice[5])
  {
    return true;
  }
  else
  {
    return false;
  }
}
//check if there is a straight from 1 to 6
bool straight(int* dice,int size)
{
  if(size!=6)
  {
    return false;
  }
  for(int i=0;i<6;i++)
  {
    if(dice[i]!=i+1)                  //dice[0]=1
    {
      return false;
    }
  }
  return true;
}
//check if there are 3 pairs
bool pairs(int* dice,int size)
{
  if(size!=6)
  {
    return false;
  }
  else if(dice[0]==dice[1] && dice[2]==dice[3] && dice[4]==dice[5])
  {
    return true;
  }
  else
  {
    return false;
  }
}
//check if there is a four of a kind and a pair
bool four_and_pair(int* dice,int size)
{
  if(size!=6)
  {
    return false;
  }
  else
  {
    if(dice[0]==dice[1] && dice[1]==dice[2] && dice[2]==dice[3] && dice[4]==dice[5]) //111155
      return true;
    if(dice[0]==dice[1] && dice[2]==dice[3] && dice[3]==dice[4] && dice[4]==dice[5]) //115555
      return true;
  }
  return false;
}
//check if there are two triplets
bool two_triplets(int* dice,int size)
{
  if(size!=6)
  {
    return false;
  }
  else if(dice[0]==dice[1] && dice[1]==dice[2] && dice[3]==dice[4] && dice[4]==dice[5])//111222
  {
    return true;
  }
  else
  {
    return false;
  }
}
//check if it's farkle
bool farkle(int *check)
{
  for(int i=0;i<15;i++)
  {
    if(check[i]==1)                  //if there is a option is true,no farkle
      return false;
  }
  return true;
}
/*********************************************************************
** Function:     is_valid_option
** Description:  check if user input a valid option
** Parameters:   check is the array to store true or false for each options, a is the spefic option we want to check
** Return:       true/false
*********************************************************************/
bool is_valid_option(int *check,int a)
{
   if(check[a]==1)
   {
     return false;
   }
   else
   {
     cout<<"This is not a valid option!"<<endl;
     return true;
   } 
}
/*********************************************************************
** Function:     count(for single one and single five)
** Description:  count how many number n in this array
** Parameters:   dice is the array of dices, n is the number we want to check, size is the array size
** Return:       p
*********************************************************************/
int count(int *dice,int n,int size)
{
  int p=0;
  for(int i=0;i<size;i++)
  {
    if(dice[i]==n)
      p++;
  }
  return p;
}
/*********************************************************************
** Function:     get_score
** Description:  according to user choice,return the score points
** Parameters:   a is user choice, size is the size of array, dice is the array of dices
** Return:       score for this turn
*********************************************************************/
int get_score(int a,int &size,int* dice)
{
  int p=0;
  if(a==1)
  {
    p=count(dice,1,size);
    size=size-p;                              //change the size
    return 100*p;
  }
  else if(a==2)
  {
    p=count(dice,5,size);
    size=size-p;
    return 50*p;
  }
  else if(a==3 or a==5)
  {
    size=size-3;
    return 300;
  }
  else if(a==4)
  {
    size=size-3;
    return 200;
  }
  else if(a==6)
  {
    size=size-3;
    return 400;
  }
  else if(a==7)
  {
    size=size-3;
    return 500;
  }
  else if(a==8)
  {
    size=size-3;
    return 600;
  }
  else if(a==9)
  {
    size=size-4;
    return 1000;
  }
  else if(a==10)
  {
    size=size-5;
    return 2000;
  }
  else if(a==11)
  {
    size=size-6;
    return 3000;
  }
  else if(a==12 or a==13 or a==14)
  {
    size=size-6;
    return 1500;
  }
  else
  {
    size=size-6;
    return 2500;
  }
}
  
/*********************************************************************
** Function:     update_score
** Description:  update new score to score borad
** Parameters:   p is the player number, score is the score board, round score is the score earned by user this round
** Return:       none
*********************************************************************/
void update_score(int p,int* &score,int round_score)
{
  int new_score=score[p]+round_score;
  cout<<"Your new score will be "<<new_score<<endl;
  if(new_score>=500)                                    //if new score is bigger than 500,we can update it
  {
    cout<<"We will update your score"<<endl;
    score[p]=new_score;
  }
  else
  {
    cout<<"Your score is less than 500 points,we cannot update it to your table"<<endl;
  }
}
/*********************************************************************
** Function:     print_score
** Description:  print everyone's score
** Parameters:   score is the score board, players are total number of players
** Return:       none
*********************************************************************/
void print_score(int* score,int players)
{
  for(int i=0;i<players;i++)
  {
    cout<<"Player "<<i+1<<"      score: "<<score[i]<<endl;
  }
}
/*********************************************************************
** Function:     print_farkle
** Description:  print everyone's score and the player who get farkle
** Parameters:   score is the score board, players are total number of players, p is the player who got farkle
** Return:       none
*********************************************************************/
void print_farkle(int* score,int players,int p)
{
  for(int i=0;i<players;i++)
  {
    if(i==p)
      cout<<"Player "<<i+1<<"      score: "<<"Farkle"<<endl;          //print farkle for spefic player p
    else
      cout<<"Player "<<i+1<<"      score: "<<score[i]<<endl;
  }
}
/*********************************************************************
** Function:     bouns
** Description:  let user play boune round
** Parameters:   p is the player number, total is the total points for this round, turn_score is the score of this turn
** Return:       none
*********************************************************************/
void bouns(int p,int &total,int &turn_score)
{
  int size=6;
  while(true)
  {
    int *dice=new int [size],choice;          //made dynamic array to store dice
    cout<<"Hello,Player "<<p+1<<endl;
    roll(dice,size);
    sort(dice,size);
    turn_score=check_options(dice,size);          //check what options can use score
    total=total+turn_score;
    cout<<"Player "<<p+1<<",you get "<<total<<" this round so far!"<<endl;
    cout<<"You have "<<size<<" dices left"<<endl;
    delete []dice;                    //delete the old dice
    if(turn_score==0)                //if it's farkle,quit loop
      break;
    if(size==0)  
      cout<<"You can get a bouns round!"<<endl;
    cout<<"Do you want to continue?(1.Yes 2.No)"<<endl;
    cin>>choice;
    cout<<""<<endl;
    if(choice==2)                  //if choose no,break
      break;
    if(size==0)                     
    {
      bouns(p,total,turn_score);    //if run out of dices without getting farkle, go to play next bouns round
      break;
    }
  }
}
  
/*********************************************************************
** Function:     check_10000
** Description:  check if any player get 10000 points
** Parameters:   score is the score board, players are total number of players, p is the player who get 10000points
** Return:       true/false
*********************************************************************/
bool check_10000(int*score,int players,int *p)
{
  for(int i=0;i<players;i++)
  {
    if(score[i]>=10000)                //if someone hits 10000pts, return true
    {
      *p=i;
      return true;
    }
  }
  return false;
}
/*********************************************************************
** Function:     last_round
** Description:  let users play last round except the one who got 10000pts
** Parameters:   score is the score board, players are total number of players
** Return:       none
*********************************************************************/
void last_round(int p,int* &score,int players)
{
  for(int i=0;i<players;i++)
  {
    if(i!=p)                            //let all other player play the last round,except the p who has at least 10000 score
    {
      play(i,score,players);
    }
  }
  cout<<"The final scores are: "<<endl;
  print_score(score,players);
  int max=0,winner=0;
  for(int i=0;i<players;i++)
  {
    if(score[i]>max)
    {
      max=score[i];
      winner=i;
    }
  }
  cout<<"The winner is player"<<winner+1<<" who has "<<max<<" pts!"<<endl;
}

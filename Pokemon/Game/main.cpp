/****************************************************** 
** Program: main.cpp 
** Author: Yuhang Chen 
** Date: 5/25/2017
** Description:Pokemon!
** Input: cin
** Output: infomation
******************************************************/ 
#include"pokemon.h"
#include"event.h"
#include"location.h"

/*********************************************************************   
** Function: is_valid_arguments(int argc,char **argv)
** Description: check if arguments valid
** Pre-Conditions: none
** Post-Conditions: none
** Return: true or flase
*********************************************************************/
bool is_valid_arguments(int argc,char **argv)
{
  if(argc!=3)//check if it has 3 arguments
  {
    cout<<"You don't have 3 command statements£¨ For example, you can type a.out -s 3)"<<endl;
    return false;
  }
  if (argv[1][1]=='s')//check the symbol
  {
    if (argv[2][0]>='3'and argv[2][0]<='9')//check the size of map
    {
      return true;
    }
    else
    {
      cout<<"Your size of map is wrong£¨ For example, you can type a.out -s 3)"<<endl;
      return false;
    }
  }
  else
  {
    cout<<"You should use -s£¨ For example, you can type a.out -s 3)"<<endl;
  }
}
/*********************************************************************   
** Function: location** copy_map(int size,event*ra,event*rb,event*fa,event*fb,event*pa,event*pb,event*c,event*s,event*n,location**l)
** Description: copy map
** Pre-Conditions: none
** Post-Conditions: none
** Return: location**l
*********************************************************************/
location** copy_map(int size,event*ra,event*rb,event*fa,event*fb,event*pa,event*pb,event*c,event*s,event*n,location**l)
{
  location** lc;//set a new map and allocate size
  lc=new location*[size];
  int left=size*size-2*(size-2)-6;//minus 6pokemon,stops and caves
  for(int y=0;y<size;y++)
  {
    lc[y]=new location[size];
  }
  for(int a=0;a<size;a++)//use double for loop set events to new for loop
  {
    for(int b=0;b<size;b++)
    {
      int num=l[a][b].get_event()->get_num();
      if(num==0)
      {
        lc[a][b].set_event(n);
      }
      if(num==1)
      {
        lc[a][b].set_event(ra);
      }
      if(num==2)
      {
        lc[a][b].set_event(rb);
      }
      if(num==3)
      {
        lc[a][b].set_event(fa);
      }
      if(num==4)
      {
        lc[a][b].set_event(fb);
      }
      if(num==5)
      {
        lc[a][b].set_event(pa);
      }
      if(num==6)
      {
        lc[a][b].set_event(pb);
      }
      if(num==7)
      {
        lc[a][b].set_event(&c[0]);
      }
      if(num==8)
      {
        lc[a][b].set_event(&s[0]);
      }
    }
  }
  return lc;
}
/*********************************************************************   
** Function: location** set_map(int size,event*ra,event*rb,event*fa,event*fb,event*pa,event*pb,event*c,event*s,event*n)
** Description: set_map
** Pre-Conditions: none
** Post-Conditions: none
** Return: location**l
*********************************************************************/
location** set_map(int size,event*ra,event*rb,event*fa,event*fb,event*pa,event*pb,event*c,event*s,event*n)
{
  location** l;
  l=new location*[size];
  int left=size*size-2*(size-2)-6;//minus 6pokemon,stops and caves
  for(int y=0;y<size;y++)
  {
    l[y]=new location[size];
  }
  l[0][0].set_event(ra);
  l[0][1].set_event(rb);
  l[0][2].set_event(fa);
  l[1][0].set_event(fb);
  l[1][1].set_event(pa);
  l[1][2].set_event(pb);
 
  int x=0,y=0,z=0;//x is for cave array,z is for stop array,y is for nothing
    
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
      event *e;
      e=l[a][b].get_event();
      if(e==NULL)
      {
        l[a][b].set_event(&c[x]);//put cave into location
        x=x+1;
      }
      if(x==size-2)
      {
        break;
      }  
    }
    if(x==size-2)
    {
      break;
    }
  } 
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
      event *e;
      e=l[a][b].get_event();
      if(e==NULL)
      {
        l[a][b].set_event(&s[z]);//put cave into location
        z=z+1;
      }
      if(z==size-2)
      {
        break;
      }  
    }
    if(z==size-2)
    {
      break;
    }
  } 
  
  for(int a=0;a<size;a++)
  {
    for(int b=0;b<size;b++)
    {
      event *e;
      e=l[a][b].get_event();
      if(e==NULL)
      {
        l[a][b].set_event(n);//put noevent into location
        y=y+1;
      }
      if(y==left)
      {
        break;
      }  
    }
    if(y==left)
    {
      break;
    }
  }

  return l;  
}
/*********************************************************************   
** Function: swap(location **&l,int size)
** Description: swap
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void swap(location **&l,int size)
{
  int a,b,c,d;
  a=rand()%size;
  b=rand()%size;
  c=rand()%size;
  d=rand()%size;//generte 4 random number
  
  location temp;
  temp=l[a][b];
  l[a][b]=l[c][d];
  l[c][d]=temp;//swap the events in location
}
/*********************************************************************   
** Function: set_start(int size,location** &l,int &x,int &y,int &ox,int &oy)
** Description: set_start
** Pre-Conditions: none
** Post-Conditions: none
** Return: int
*********************************************************************/
int set_start(int size,location** &l,int &x,int &y,int &ox,int &oy)
{
  int a=0,b=0;
  for(a=0;a<size;a++)
  {
    for(b=0;b<size;b++)
    {
      if(l[a][b].get_event()->get_num()==8)//find a poke-stop to start
      {
        y=a;
        x=b;
        oy=y;//ox and oy is original position of trainer
        ox=x;
        return 0;//use return 0 to quit double for loop
      }
    }    
  }
}
/*********************************************************************   
** Function: printmap(int size,int x,int y)
** Description: printmap
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void printmap(int size,int x,int y)
{
  for(int a=0;a<size;a++)
  {
    cout<<"|";
    for(int b=0;b<size;b++)
    {
      if(a==y and b==x)//print player position
      {
        cout<<"P|";
      }
      else//print others question mark
      {
        cout<<"?|";
      }
    }
    cout<<""<<endl;
  }
}
/*********************************************************************   
** Function: printmap(int size,int x,int y)
** Description: printall
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void printall(int size,int x,int y,location** &l)
{
  for(int a=0;a<size;a++)
  {
    cout<<"|";
    for(int b=0;b<size;b++)
    {
      if(a==y and b==x)
      {
        cout<<"P1|";
      }
      else if(l[a][b].get_event()->get_num()==0)//check number and then know waht kind of event it is
      {
        cout<<"NO|";//cout symbol of each event
      }
      else if(l[a][b].get_event()->get_num()==1)
      {
        cout<<"RA|";
      }
      else if(l[a][b].get_event()->get_num()==2)
      {
        cout<<"RB|";
      }
      else if(l[a][b].get_event()->get_num()==3)
      {
        cout<<"FA|";
      }
      else if(l[a][b].get_event()->get_num()==4)
      {
        cout<<"FB|";
      }
      else if(l[a][b].get_event()->get_num()==5)
      {
        cout<<"PA|";
      }
      else if(l[a][b].get_event()->get_num()==6)
      {
        cout<<"PB|";
      }
      else if(l[a][b].get_event()->get_num()==7)
      {
        cout<<"CA|";
      }
      else if(l[a][b].get_event()->get_num()==8)
      {
        cout<<"ST|";
      }    
    }
    cout<<""<<endl;
  }
}
/*********************************************************************   
** Function: get_balls(int &balls)
** Description: getballs
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void get_balls(int &balls)
{
  int a=rand()%8+3;//get random number from 3-10
  balls=balls+a;//increase balls
  cout<<"You get "<<a<<" more balls,"<<"You have "<<balls<<" balls right now"<<endl;
  cout<<""<<endl;
}
/*********************************************************************   
** Function: runaway(location **&l,int size,int x,int y)
** Description: runaway
** Pre-Conditions: none
** Post-Conditions: none
** Return: int
*********************************************************************/
int runaway(location **&l,int size,int x,int y)
{
  int a=0,b=0;
  for(a=0;a<size;a++)
  {
    for(b=0;b<size;b++)
    {
      if(l[a][b].get_event()->get_num()==0)//find a empty event
      {
        location temp;
        temp=l[y][x];
        l[y][x]=l[a][b];
        l[a][b]=temp;//change the event of location
        return 0;//use return 0 to quit double for loop
      }
    }
  }
}
/*********************************************************************   
** Function: check_stage(location **&l,int x,int y,pokemon *&p,event *n)
** Description: check the stage of pokemon
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void check_stage(location **&l,int x,int y,pokemon *&p,event *n)
{
  int stage;
  string name;
  stage=p->get_stage();//get stage
  name=p->get_name();//get name
  if(stage==3)
  {
    cout<<name<<"'s stage is 3 now,he will be removed from the map"<<endl;
    l[y][x].set_event(n);//if stage is 3,set event to empty
  }
}
/*********************************************************************   
** Function: catchpoke(pokemon *&p,int &balls,location **&l,int size,int x,int y,event*n)
** Description: catch pokemon
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void catchpoke(pokemon *&p,int &balls,location **&l,int size,int x,int y,event*n)
{
  if(balls>0)//check balls
  {
    bool flag;
    flag=p->catchp();//the stage will change in this function
    balls=balls-1;
    cout<<"After this try,you have "<<balls<<" balls now"<<endl;
    if(flag==true)
    {
      check_stage(l,x,y,p,n);
    }
    else
    {
      runaway(l,size,x,y);//if fail,let pokemon run away
    }
  }
  else
  {
    cout<<"You don't have enough balls. You cannot catch."<<endl;
  }
}
/*********************************************************************   
** Function: update(pokemon **&p,location **&l,int size,event*n)
** Description: update pokemon in cave
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void update(pokemon **&p,location **&l,int size,event*n)
{
  cout<<"Since you are in cave now, all of your stage 2 pokemon will be envolved to stage 3!"<<endl;
  cout << "3, " << flush;
	//sleep(1);
	cout << "2, " << flush;
	//sleep(1);
	cout << "1..." << flush;
	//sleep(1);
  int stage=0;
  for(int i=0;i<6;i++)//use for loop to update all stage 2 pokemon
  {
    stage=p[i]->get_stage();
    if (stage==2)
    {
      p[i]->set_stage(3);
      string name;
      name=p[i]->get_name();
      int num=p[i]->get_num();
      int a=0,b=0;
      for(a=0;a<size;a++)
      {
        for(b=0;b<size;b++)
        {
          if(l[a][b].get_event()->get_num()==num)
          {
            cout<<name<<"'s stage is 3 now,he will be removed from the map"<<endl;
            l[a][b].set_event(n);//use double for loop to set all events of stage 3 pokemon to empty
          }
        }
      }          
    }
  }
}   
/*********************************************************************   
** Function: check_location(location **&l,int x,int y,int &balls,pokemon **&p,int size,event*n)
** Description: check the location of user
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void check_location(location **&l,int x,int y,int &balls,pokemon **&p,int size,event*n)
{
  int a=l[y][x].get_event()->get_num();//get the number of location
  switch(a)//use switch to call different case
  {
    case 1: 
            catchpoke(p[0],balls,l,size,x,y,n);
            break;
    case 2: 
            catchpoke(p[1],balls,l,size,x,y,n);
            break;
    case 3: 
            catchpoke(p[2],balls,l,size,x,y,n);
            break;
    case 4: 
            catchpoke(p[3],balls,l,size,x,y,n);
            break;
    case 5: 
            catchpoke(p[4],balls,l,size,x,y,n);
            break;
    case 6: 
            catchpoke(p[5],balls,l,size,x,y,n);
            break;
    case 7: update(p,l,size,n);
            break;
    case 8: get_balls(balls);
            break;
  }
}
/*********************************************************************   
** Function: give_percept(location**&l,int x,int y,int size)
** Description: give the percept of different events
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void give_percept(location**&l,int x,int y,int size)
{
  int up=y-1,down=y+1,left=x-1,right=x+1;//give the number of up,down,left,right
  if(up>=0)//check if it is out of range
  {
    l[up][x].get_event()->percept();
  }
  if(down<size)
  {
    l[down][x].get_event()->percept();
  }
  if(left>=0)
  {
    l[y][left].get_event()->percept();
  }
  if(right<size)
  {
    l[y][right].get_event()->percept();
  }
}
/*********************************************************************   
** Function: move(int &x,int &y,int size)
** Description: let user move
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void move(int &x,int &y,int size)
{
  int up=y-1,down=y+1,left=x-1,right=x+1;
  string a;
  cout<<"You can make a move now. Where do you want to move?"<<endl;
  if(up>=0)
  {
    cout<<"W. move up ";
  }
  if(down<size)
  {
    cout<<"S. move down ";
  }
  if(left>=0)
  {
    cout<<"A. move left ";
  }
  if(right<size)
  {
    cout<<"D. move right ";
  }
  cout<<""<<endl;
  cin>>a;
  if(a=="W" or a=="w")
    y=up;
  if(a=="S" or a=="s")
    y=down;
  if(a=="A" or a=="a")
    x=left;
  if(a=="D" or a=="d")//similiar to percept
    x=right;
}    
/*********************************************************************   
** Function: checkcontinue(int x,int y,int ox,int oy,pokemon**p)
** Description: check if game continue
** Pre-Conditions: none
** Post-Conditions: none
** Return: bool
*********************************************************************/  
bool checkcontinue(int x,int y,int ox,int oy,pokemon**p)
{
  int num[6];
  bool flag=false;
  for(int i=0;i<6;i++)
  {
    num[i]=p[i]->get_stage();//get all stage and store in array
  }
  for(int i=0;i<6;i++)
  {
    if(num[i]==3)
    {
      flag=true;
    }
    else
    {
      return false;
    }
  }
  if(flag==true)
  {
    cout<<"You have already collected all the pokemon, please go home!"<<endl;
  }
  if(x==ox and y==oy and flag==true)//check if you collect enough pokemon and if you are in orginal position
  {
    return true;
  }
  else
  {
    return false;
  }
}
/*********************************************************************   
** Function: delete_pokemon(pokemon **&p)
** Description: delete pokemon
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void delete_pokemon(pokemon **&p)
{    
  for(int i=0;i<6;i++)
  {
    delete p[i];
  }
  delete []p;
  p=NULL;
}
/*********************************************************************   
** Function: delete_location(location**&l,int size)
** Description: delete location
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void delete_location(location**&l,int size)
{
  for(int i=0;i<size;i++)
  {
    delete []l[i];
  }
  delete []l;
  l=NULL;
}
/*********************************************************************   
** Function: play(int size,int &x,int &y,int &balls,location** &l,int ox,int oy,event*n)
** Description: play the game
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void play(int size,int &x,int &y,int &balls,location** &l,int ox,int oy,event*n)
{
  pokemon **p=new pokemon*[6];//use a array to store pokemon
  bool flag=false;
  p[0]=new rocka;
  p[1]=new rockb;
  p[2]=new flya;
  p[3]=new flyb;
  p[4]=new psychica;
  p[5]=new psychicb;
  while(true)
    {
      printmap(size,x,y);
      #ifdef DEBUG
      printall(size,x,y,l);//debug mode,print all
      #endif
      cout<<l[y][x].get_event()->get_message()<<endl;//give the info of this location
      cout<<""<<endl;
      check_location(l,x,y,balls,p,size,n);//check location
      cout<<""<<endl;
      flag=checkcontinue(x,y,ox,oy,p);//check if game continue
      if(flag==true)
      {
        break;
      }
      give_percept(l,x,y,size);//give percept
      cout<<""<<endl;
      move(x,y,size);//let user make a move
    }
  delete_pokemon(p);
  //delete_events(l,size);
  //delete_location(l,size);
}
/*********************************************************************   
** Function: aimove(int &x,int &y,int size,int balls,int ox,int oy)
** Description: aimove
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void aimove(int &x,int &y,int size,int balls,int ox,int oy)
{
  int up=y-1,down=y+1,left=x-1,right=x+1;
  int a;
  if(balls==0)//check if you have enough balls and decide if you go home
  {
    cout<<"We are going to move back to stop to pick some balls first!"<<endl;
    if(x<ox)
    {
      x=x+1;
    }
    else if(x>ox)
    {
      x=x-1;
    }
    else if(y<oy)
    { 
      y=y+1;
    }
    else if(y>oy)
    {
      y=y-1;
    }
  }
  else
  {
    while(true)
    {
      a=rand()%4+1;//generate one random number to decide where do you move
      cout<<a<<endl;
      if(up>=0 and a==1)//check if you out of range
      {
        y=up;
        break;
      }
      if(down<size and a==2)
      {
        y=down;
        break;
      }
      if(left>=0 and a==3)
      {
        x=left;
        break;
      }
      if(right<size and a==4)
      {
        x=right;
        break;
      }
    }
  }
}
/*********************************************************************   
** Function: AI(int size,int &x,int &y,int &balls,location** &l,int ox,int oy,event*n)
** Description: aimove
** Pre-Conditions: none
** Post-Conditions: none
** Return: none
*********************************************************************/
void AI(int size,int &x,int &y,int &balls,location** &l,int ox,int oy,event*n)
{
  pokemon **p=new pokemon*[6];//use a array to store pokemon
  bool flag=false;
  p[0]=new rocka;
  p[1]=new rockb;
  p[2]=new flya;
  p[3]=new flyb;
  p[4]=new psychica;
  p[5]=new psychicb;
  while(true)
    {
      printmap(size,x,y);
      printall(size,x,y,l);
      cout<<l[y][x].get_event()->get_message()<<endl;
      cout<<""<<endl;
      check_location(l,x,y,balls,p,size,n);
      cout<<""<<endl;
      flag=checkcontinue(x,y,ox,oy,p);
      if(flag==true)
      {
        break;
      }
      give_percept(l,x,y,size);
      cout<<""<<endl;
      aimove(x,y,size,balls,ox,oy);//use ai move, similar to play function
    }
  delete_pokemon(p);
}
/*********************************************************************   
** Function: main(int argc,char **argv)
** Description: main
** Pre-Conditions: none
** Post-Conditions: none
** Return: 0
*********************************************************************/
int main(int argc,char **argv)
{
  srand(time(NULL));//make sure random number are different
  if(is_valid_arguments(argc,argv)==false)
  {
    return 0;
  }
  int size,x=0,y=0,ox=0,oy=0;//x and y is the position of trainer
  int balls=0;
  size=atoi(argv[2]);
  
  eventra ra;
  eventrb rb;
  eventfa fa;
  eventfb fb;
  eventpa pa;
  eventpb pb;  
  cave c[size-2];
  stop s[size-2];
  noevent n;//create different events in stack
  
  location **l;//create orginal location
  l=set_map(size,&ra,&rb,&fa,&fb,&pa,&pb,c,s,&n);
  for(int a=0;a<size;a++)    
    swap(l,size);//give random location
  set_start(size,l,x,y,ox,oy);
  location **lc;//make a map copy
  lc=copy_map(size,&ra,&rb,&fa,&fb,&pa,&pb,c,s,&n,l);
  
  cout<<"Welcome to pokemon!Here is the map."<<endl;
  cout<<"Do you want to let AI play for you?(1.Yes 2.No)"<<endl;
  int choice;
  cin>>choice;
  if(choice==1)
  {
    AI(size,x,y,balls,l,ox,oy,&n);
  }
  else
  { 
    play(size,x,y,balls,l,ox,oy,&n);
  }
  while(true)//second round
  {
    cout<<"Good job! You finished your pokemon journey!"<<endl;
    cout<<"Do you want to play another round?(1.Same configuration 2.Random configuration. 3.quit"<<endl;
    int choice;
    cin>>choice;
    delete_location(l,size);//delete old map first
    if(choice==1)
    {
      l=copy_map(size,&ra,&rb,&fa,&fb,&pa,&pb,c,s,&n,lc);//if you want to play the same map,copy the lc to l
      play(size,x,y,balls,l,ox,oy,&n);
    }
    else if(choice==2)
    {
      l=set_map(size,&ra,&rb,&fa,&fb,&pa,&pb,c,s,&n);//if you want to play a new map,create map again
      for(int a=0;a<size;a++)    
        swap(l,size);//give random location
      set_start(size,l,x,y,ox,oy);
      play(size,x,y,balls,l,ox,oy,&n);
    }
    else if(choice==3)
    {
      delete_location(lc,size);//delete copy map lc
      return 0;
    }
  }            
}

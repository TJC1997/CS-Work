/****************************************************** 
** Program: Assign3.cpp 
** Author: Yuhang Chen 
** Date: 1/31/2017 
** Description: Grade calculator!  
** Input: number
** Output: percentage of your grade
******************************************************/ 


#include<iostream>
#include<cmath>//There are some equation 

using namespace std;

int labs(string name)
{
  int a,b,c,d,e,f,point;//a is how many lab,b is vary or not,c is start number,d is get score,e is input
  double result=0;
  cout<<"how many "<<name<<endl;
  cin>>a;
  cout<<"Do the point values vary (0-no, 1-yes):"<<endl;
  cin>>b;
  if(b==0)
  {
    cout<<"Out of how many points?"<<endl;
    cin>>e;
    for(c=0;c<a;c++)
    {
      cout<<name<<c+1<<" score: ";
      cin>>d;
      result=result+d;
    }
    cout<<"Your "<<name<<" average is "<<100*result/(a*e)<<endl;
    return 100*result/(a*e);
  }
  else
  {
    result=0,point=0,f=0;
    for(c=0;c<a;c++)
    {
      cout<<name<<c+1<<" points: ";
      cin>>f;
      point=f+point;
      cout<<name<<c+1<<" score: ";
      cin>>d;
      result=result+d;
    }
    cout<<"Your "<<name<<" average is "<<100*result/point<<endl;
    return 100*result/point;
  }
}





int recitations()
{
  int qw,dw,cw,a,b,c;
  double score,all;
  cout<<"quiz weight:"<<endl;
  cin>>qw;
  cout<<"design weight:"<<endl;
  cin>>dw;
  cout<<"critique weight"<<endl;
  cin>>cw;
  all=qw+dw+cw;
  if(qw!=0)
  {
    a=labs("quiz");
  }
  if(dw!=0)
  {
    b=labs("design");
  }
  if(cw!=0)
  {
    c=labs("critique");
  }
  score=a*qw/all+b*dw/all+c*cw/all;
  cout<<"Your recitation average is "<<score<<endl;
  return score;
}

int test()
{
  int a,b,c,d=0,e,f=0;
  double result=0;
  cout<<"how many tests?"<<endl;
  cin>>a;
  for(b=1;b<=a;b++)
  {
    cout<<"test "<<b<< "points"<<endl;
    cin>>c;
    d=d+c;
    cout<<"test "<<b<< "score"<<endl;
    cin>>e;
    f=f+e;
  }
    cout<<"Your test average is "<<(double)100*f/d<<endl;
    return (double)100*f/d;
}

int tclass(double a,double b,double c,double d)
{
  double qw,dw,cw,aw,score,all;
  cout<<"Test weight:"<<endl;
  cin>>qw;
  cout<<"Recitation weight:"<<endl;
  cin>>dw;
  cout<<"Lab weight"<<endl;
  cin>>cw;
  cout<<"Assignment weight"<<endl;
  cin>>aw;
  all=qw+dw+cw+aw;

  score=a*qw/all+b*dw/all+c*cw/all+d*aw/all;
  cout<<"Your class average is "<<score<<endl;
  return score;
}
int main()
{
  while(1)
  {
    int a,l,as,r,t;
    cout<<"Would you like to calculate an average for 1) labs, 2) assignments, 3) recitations, 4) tests, 5) the class, or 6) to quit? "<<endl;
    cin>>a;
    if(a==1) 
    {
      l=labs("lab");
    }
    
    if(a==2)
    {
      as=labs("assignment");//share with labs
    }    
    if(a==3)
    {
      r=recitations();
    }  
    if(a==4)
    {
      t=test();
    }
    if(a==5)
    {
      tclass(l,as,r,t);
    }
    if(a==6)
    {
      break;
    }
  }
  return 0;
}

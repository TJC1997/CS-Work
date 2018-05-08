/*
File: main cpp file
Author: Yuhang Chen (Tony)
Date: 2018/5/1
*/
#include"hash.h"
#include<fstream>

using namespace std;

int main()
{
  hash h;//create hash table
  ifstream input;
  input.open("name.txt");//input file is name.txt
  string line,name,email;
  while(!input.eof())
  {
    name="";
    email="";
    getline(input,line);
    if(line[0]!='0')
    {
      int i=0;
      while(line[i]!='@')
      {
        i++;
      }
      while(line[i]!=' ')
      {
        i--;
      }
      for(int a=0;a<i;a++)
      {
        name=name+line[a];
      }
      for(int a=i+1;a<line.length();a++)
      {
        email=email+line[a];
      }
      h.add_item(name,email);
    }
  }
  input.close();
  h.print_all(); 
  //cout<<h.num_of_all()<<endl;
  //h.find("Andrews, Michael");
  //h.find("Yuhang, Chen");
  ofstream output;
  output.open("email.txt");//output to the email.txt file
  h.get_email(output);
  output.close();
  h.empty_all();
  
  return 0;
}

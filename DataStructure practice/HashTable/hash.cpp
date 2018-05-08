/*
File: hash table cpp file
Author: Yuhang Chen (Tony)
Date: 2018/5/1
*/
#include "hash.h"
#include<fstream>
using namespace std;

/**********************************************
** Function:     constructor
** Description:  set default value
**********************************************/
hash::hash(){
	tablesize=100;//set default tablezise to 100
  count=0;
	array=new item[100];//create space in heap
	for(int i=0;i<tablesize;i++){//go through all the index and make them empty
		array[i].name="empty";
		array[i].email="empty";
		array[i].next=NULL;
	}
};

/**********************************************
** Function:     Hash_function
** Description:  Generate the hash index number acooriding to the string,and return the number
**********************************************/
int hash::hash_number(string s){
  int index=0;
	for(int i=0;i<s.length();i++){
		index=index+(int)s[i];
	}
	return index%tablesize;//formula: add all the Ascii value of charaters in the string together and the mod them with tablesize
};

/**********************************************
** Function:     Add_item
** Description:  add one student's information into the hash table
**********************************************/
void hash::add_item(string name,string email){
	int i=hash_number(name);//get the index number based on name
	if(array[i].name=="empty"){//if the first spot is empty,add the item on the first spot
		array[i].name=name;
		array[i].email=email;
	}
	else{
		item*ptr=&(array[i]);
		while(ptr->next!=NULL){//go through all the item in the linked list until next one is NULL
			if(ptr->name==name){
				return;
			}
			ptr=ptr->next;
		}
		if(ptr->name==name){
			return;//if the name has already exist,do not add new item
		}
		else{
			ptr->next=new item;//add new item
			ptr=ptr->next;
			ptr->name=name;
			ptr->email=email;
			ptr->next=NULL;
		}
	}
};

/**********************************************
** Function:     Print_one
** Description:  Print all the students' infomation in the one index
**********************************************/
void hash::print_one(int i)
{
  item*ptr=&(array[i]);
  if(ptr->name!="empty"){
    do{
      cout<<ptr->name<<endl;
      cout<<ptr->email<<endl;
      ptr=ptr->next;
      count++;
    }while(ptr!=NULL);
  }
};

/**********************************************
** Function:     Print_all
** Description:  Go through the linked list array and print all students'infomation
**********************************************/
void hash::print_all(){
  for(int i=0;i<tablesize;i++)
  {
    print_one(i);
  }
  cout<<"The total number of items is "<<count<<endl;//prnt the total number of student
};

/**********************************************
** Function:     Get_email
** Description:  Take the email from hash table and output them into txt file
**********************************************/
void hash::get_email(ofstream& all){
  for(int i=0;i<tablesize;i++)
  {
    item*ptr=&(array[i]);
    if(ptr->name!="empty"){
      all<<ptr->email<<endl;//out put email
      while(ptr->next!=NULL){//go through all the linked list
        ptr=ptr->next;
        all<<ptr->email<<endl;
      }
    }
  }
};

/**********************************************
** Function:     Num_of_item
** Description:  Get the number of items in one index
**********************************************/
int hash::num_of_item(int i)
{
  item* ptr=&(array[i]);
  if(ptr->name=="empty")
  {
    return 0;
  }
  int count=1;
  while(ptr->next!=NULL)
  {
    count++;
    ptr=ptr->next;
  }
  return count;
};

/**********************************************
** Function:     Num_of_all
** Description:  Get the number of all items
**********************************************/
int hash::num_of_all(){
  int sum=0;
  for(int i=0;i<tablesize;i++)
  {
    sum=sum+num_of_item(i);//go through all the index and get the total number of all items
  }
  return sum;
}

/**********************************************
** Function:     Empty_one
** Description:  empty one index
**********************************************/
void hash::empty_one(int i)
{
  int number=num_of_item(i);//get how many items in this linked list
  if (number==0)
    return;
  if (number==1)//if there is only one item,set it to empty
  {
    array[i].name="empty";
		array[i].email="empty";
		array[i].next=NULL;
  }
  else{//if not,empty the last item
    item* ptr=&(array[i]);
    while(ptr->next->next!=NULL)
    {
      ptr=ptr->next;
    }
    delete ptr->next;
    ptr->next=NULL;
  }
  empty_one(i);//use recurison to empty linked list until clean every item
};

/**********************************************
** Function:     Empty_all
** Description:  empty all linked list
**********************************************/
void hash::empty_all()
{
  for(int i=0;i<tablesize;i++)
  {
    empty_one(i);
  }
};

/**********************************************
** Function:     Find item
** Description:  Find the item according to the name
**********************************************/
bool hash::find(string s){
  int i=hash_number(s);//get the index number based on the name
  item* ptr=&(array[i]);
  do{//go through the linked list and check if the name already exist
    if(ptr->name==s)
    {
      cout<<"We found it!It's at index "<<i<<endl;
      cout<<ptr->name<<" "<<ptr->email<<endl;
      return true;
    }
    ptr=ptr->next;
  }while(ptr!=NULL);
  cout<<"We didn't find it"<<endl;
  return false;
};

/**********************************************
** Function:     Delete item
** Description:  Find the specific item base on name and delete it
**********************************************/
void hash::delete_item(string s){
  bool check=find(s);//check if the item exist
  int i=hash_number(s);
  if(check==false)
  {
    cout<<"We cannot delete it"<<endl;
  }
  else{
    cout<<"All the element in index "<<i<<" was:"<<endl;
    print_one(i);
    int size=num_of_item(i);
    item* ptr=&(array[i]);
    if(size==1)
    {
      array[i].name="empty";
		  array[i].email="empty";
		  array[i].next=NULL;  
    }
    else{
      item all[size-1];//make new array to store the rest of item
      int a=0;
      do{
        if(ptr->name!=s)
        {
          all[a]=*ptr;//deep copy the rest of name
          a++;
        }
        ptr=ptr->next;
      }while(ptr!=NULL);
      empty_one(i);//clean the old array
      for(int x=0;x<size-1;x++)
      {
        add_item(all[x].name,all[x].email);//update new array to hash table
      }
    }
  }
  cout<<"We delete it successful"<<endl;
  cout<<"All the element in index "<<i<<" is:"<<endl;
  print_one(i);
};       

/**********************************************
** Function:     Destructor
** Description:  clean the space in the heap
**********************************************/
hash::~hash()
{
  delete[] array;
}
/*
File: hash table header file
Author: Yuhang Chen (Tony)
Date: 2018/5/1
*/
#include<iostream>
#include<string>
#include<fstream>
using namespace std;

//This is the item in linked list
struct item{
	string name;//store students'name
	string email;//store students'email
	item* next;//point to next list
};

//This is hash class 
class hash{
	private:
	   int tablesize;//the size of array
	   item* array;//hash table array
     int count;//store the number of items
	public:
	   hash();//constructor
     ~hash();//destructor
	   int hash_number(string s);//hash function
     void add_item(string name,string email);//add a new student with email
     void print_one(int index);//print one linked list at the index of the array
     void print_all();//print all the linked lists in array
     void get_email(ofstream& all);//get the email from hash table and output the email to the txt file
     int num_of_item(int index);//get the number of items in one linked list
     int num_of_all();//get the number of items in whole array
     bool find(string s);//find the item according to the name
     void delete_item(string s);//delete the item according to the name
     void empty_one(int index);//delete one linked list
     void empty_all();//delete all linked list
};

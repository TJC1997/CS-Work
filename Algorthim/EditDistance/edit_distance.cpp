#include<iostream>
#include<cmath>
#include<cstdlib>
#include<fstream>
#include<string>
#include<string.h>

using namespace std;


ofstream output;

struct str_pair{//string pair to store two strings
    string s1;
    string s2;
};

void set_matrix_row(int* row, char* line){
  // iterates over every comma with strtok()
  line = strtok(line,","); // seed str_tok skip the first letter.
  for(int i=0;i<5;i++){
    line = strtok(NULL,",");
    row[i]=atoi(line);
  }
}

/*set_cost_matrix
desc: parses input_file_2 and sets the cost matrix
pertainng to the cost to make every kind of edit.
input: "costfile.text"
output: 6x6 cost matrix now full of ony CHARACTERS
*** will need --atoi()-- to use any of the values.
*/
void set_cost_matrix(string filename, int cost_matrix[5][5]){
  ifstream myfile (filename.c_str());
  char matrix_line[12]; // *,-,a,g,t,c\0
  string line="";
  getline(myfile,line); // first line is not needed, only need integers.

  if(myfile.is_open()){
    for(int i=0;i<5;i++){
      getline(myfile,line);

      if(line.length() <= 12){
        strcpy(matrix_line,line.c_str());
        set_matrix_row(cost_matrix[i],matrix_line);
      }
      else{
        perror("Invalid input file, please check commandline");
        exit(1);
      }

    }
  }
  else{
    perror("Error opening File");
    exit(1);
  }

}

int readfile(string input_file,str_pair* p){
	ifstream myfile (input_file.c_str());
    string line="";
	int j=0;
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			string n1="",n2="";
			int i=0;
			while(line[i]!=','){//collect the first string
				n1=n1+line[i];
				i++;
			}
			i++;
			while(i<line.length()){//collect the second string
				n2=n2+line[i];
				i++;
			}
			p[j].s1=n1;
            p[j].s2=n2;
			j++;
		}
		myfile.close();
	}
	return j;
}

int check_single_char(char c,int cost[5][5]){
  int EE,EA,ET,EG,EC;//EE means two empty str. EA means empty and char 'A'. AT means char 'A' and char 'T'
  EE=cost[0][0];
  EA=cost[0][1];//find the cost from cost table
  ET=cost[0][2];
  EG=cost[0][3];
  EC=cost[0][4];
	if(c=='A'){
		return EA;//EA represend empty and A. It will work for the deletion and insertion
	}
	if(c=='T'){
		return ET;
	}
	if(c=='G'){
		return EG;
	}
  //default:
		return EC;
}

int check_double_char(char c1,char c2,int cost[5][5]){
  int AT,AG,AC,TG,TC,GC;//EE means two empty str. EA means empty and char 'A'. AT means char 'A' and char 'T'
  AT=cost[1][2];
  AG=cost[1][3];
  AC=cost[1][4];
  TG=cost[2][3];
  TC=cost[2][4];
  GC=cost[3][4];
	if(c1==c2){
		return 0;//if two chars are same,return 0
	}
	if((c1=='A'&& c2=='T') || (c1=='T' && c2=='A')){//accoriding to the combination of two chars,return the cost of subtitute
		return AT;
	}
	if((c1=='A'&& c2=='G') || (c1=='G' && c2=='A')){
		return AG;
	}
	if((c1=='A'&& c2=='C') || (c1=='C' && c2=='A')){
		return AC;
	}
	if((c1=='G'&& c2=='T') || (c1=='T' && c2=='G')){
		return TG;
	}
	if((c1=='C'&& c2=='T') || (c1=='T' && c2=='C')){
		return TC;
	}
//default:
		return GC;
}

/* hopefully cleans up the clutter.

takes just the characters pointed by the various functions because we are only
using one character from each src for each decision.,
rows and cols are passed by reference becasue we need to edit them for outside this functions
Inputs:
src1 and src2 are passed by value becasue they are just Rvalues
rows and cols are to increment the desicion along.
Post conditions:
the character pointed by str1 and str2 are now filled by desicion
row and col are decremented correctly outside this scope.
*/
void set_one_letter(int decision,string& str1, string& str2, int * rows, int * cols, char src1,char  src2){

  //printf("%i:\n\tstr1[i]=%c\n\tstr2[j]=%c\n",decision,src1,src2);

  switch(decision){
    case 0://moving up increments the row number
      // del=table[i-1][j]+check_single_char(origin[i-1],cost);
      str1=str1+src1;
      str2=str2+"-";
      (*rows)--;
      break;
    case 1:// moving to the left incremens the colomn number
      // ins=table[i][j-1]+check_single_char(goal[j-1],cost);
      str1=str1+"-";
      str2=str2+src2; // insert a blank space, dont increment
      (*cols)--;
      break;
    case 2:// moving diagonally increments both
    // basically means either they are equal or we are changing it.
    // sub=table[i-1][j-1]+check_double_char(origin[i-1],goal[j-1],cost);
      str1=str1+src1;
      str2=str2+src2;
      (*rows)--;
      (*cols)--;
      break;
    default:
      break;
  }
}

void reverse(string m,string& f){
  for (int i = m.length()-1; i >= 0; i--)
  {
    f=f+m[i];
  }
}

/* traces back and makes edits to the strings that
 dptable = table  of values of min edits needed at each sub string1
 origin = the pair of strings to edit.

 traces back the table and makes edits to the original str_pair.
 */
struct str_pair * traceback(struct str_pair * origin, int ** dirtable,int cost[5][5],int c){
  struct str_pair * end_pair = new str_pair;

  int cols=origin->s2.length()-1;
  int rows=origin->s1.length()-1;
  string str1_middle="";
  string str2_middle="";
  string str1_final="";
  string str2_final="";
 
  while(cols >= 0 && rows >=0){
    /* places a indication at that value to help traceback.
    values = [ ins, del, sub] or []
    0 = up;
    1 = left;
    2 = diagonal*/
    //printf("[%i][%i] = %i\n",rows,cols,dirtable[rows][cols]);
    set_one_letter(dirtable[rows][cols],str1_middle,str2_middle, &rows, &cols, origin->s1[rows], origin->s2[cols]);
  }
  while(cols>=0){
    str2_middle=str2_middle+origin->s2[cols];
    str1_middle=str1_middle+"-";
    cols--;
  }
  while(rows>=0){
    str1_middle=str1_middle+origin->s1[rows];
    str2_middle=str2_middle+"-";
    rows--;
  }
  reverse(str1_middle,str1_final);
  reverse(str2_middle,str2_final);
  output<<str1_final<<","<<str2_final<<":"<<c<<endl;
}


int ** allocTable(int rows, int cols){
  int ** table = (int**)malloc(sizeof(int*)*rows);
  for(int r=0;r<rows;r++){
    table[r]=(int*)malloc(sizeof(int)*cols);
  }
  return table;
}
void  deallocTable(int rows, int *** table){

  for(int r=0;r<rows;r++){
    free((*table)[r]);
  }
  free(*table);
}


/* places a indication at that value to help traceback.
values = [ ins, del, sub] or []
0 = up;
1 = left;
2 = diagonal*/
void setDirectionHistory(int * location, int * values){
  int result=min(values[0],values[1]);
  result=min(result,values[2]);
  if(result == values[0] ){
    *location = 0;
  }
  else if(result== values[1]){
    *location = 1;
  }
  else{//result == values[2]
    *location = 2;
  }

  /* and insert to the orign mstring measn setting the colom value.
  and delete means incrementing the target string.
  substitution means do nothing.
  */
}

void edit_distance(str_pair a,int cost[5][5]){
	string origin=a.s1;
	string goal=a.s2;
	int len1=origin.length()+1;//add extra row  origin == s1 == rows
	int len2=goal.length()+1;//add extra col goal == s2 == cols
	int ** table = allocTable(len1,len2);
  int ** directionTable= allocTable(len1-1,len2-1);
  int values[3]={0};

	table[0][0]=0;//table[0][0] is the base case,which is 0

	for(int i=1;i<len1;i++){//go through first col
		int index=i-1;//index is the index of string.Table start from [1][0],but string start from index 0
		table[i][0]=check_single_char(origin[index],cost);
		for(int j=1;j<i;j++){
			index=j-1;
			table[i][0]=table[i][0]+check_single_char(origin[index],cost);
		}
	}
	for(int i=1;i<len2;i++){
		int index=i-1;
		table[0][i]=check_single_char(goal[index],cost);
		for(int j=1;j<i;j++){
			index=j-1;
			table[0][i]=table[0][i]+check_single_char(goal[index],cost);
		}
	}


//iterate origin from 1 to i === 1 to len1
//iterate goal from 1 to j === 1 to len2
	for(int i=1;i<len1;i++){
		for(int j=1;j<len2;j++){
			int index1=i-1;//index of string1
			int index2=j-1;//index of string2
			int ins,del,sub;
			del=table[i-1][j]+check_single_char(origin[index1],cost);
			ins=table[i][j-1]+check_single_char(goal[index2],cost);
			sub=table[i-1][j-1]+check_double_char(origin[index1],goal[index2],cost);
			int result=min(ins,del);
			result=min(result,sub);

    	table[i][j]=result;//put result on table

      values[0]=del;values[1]=ins;values[2]=sub;
      setDirectionHistory(&directionTable[i-1][j-1],values);// places a flag for traceback.
    }
	}

	for(int i=0;i<len1;i++){
		for(int j=0;j<len2;j++){
			cout<<table[i][j]<<" ";
		}
		cout<<endl;
	}
  cout<<endl;
  for(int i=0;i<len1-1;i++){
		for(int j=0;j<len2-1;j++){
			cout<<directionTable[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<table[len1-1][len2-1]<<endl;//print out final result

  struct str_pair * end_pair = traceback(&a,directionTable,cost,table[len1-1][len2-1]);

  //deallocTable(len1,&table);
  //deallocTable(len1,&directionTable);
  return;
}

void read_cost(int arr[5][5],string file){
	ifstream myfile (file.c_str());
    string line="";
	int x=0,y=0;
	if (myfile.is_open())
	{
		getline (myfile,line);//skip the first line
		while ( getline (myfile,line) )
		{
			for(int i=0;i<line.length();i++){
				if(line[i]>='0' && line[i]<='9'){
					arr[x][y]=line[i]-48;//find all the number and put them into cost_arr. And the number must between 0 and 9
					y++;
				}
			}
			x++;
			y=0;//reset 0
		}
		myfile.close();
	}
}

int main(int argc,char **argv){
  if(argc != 3){
    cout<< "Wrong Command! ./a.out <costfile> <input_file>" <<endl;
    exit(1);
  }
  output.open("imp2output.txt");
	// string cost_file=argv[1];
	string input_file=argv[2];
  str_pair p[10000];
  int size=readfile(input_file,p);//read all the string pairs
	int cost_arr[5][5];
  set_cost_matrix(argv[1],cost_arr);
	// read_cost(cost_arr,cost_file);//find the cost from cost file
    for (int i = 0; i < size; i++)
    {
      cout<<p[i].s1<<endl;
      cout<<p[i].s2<<"\n"<<endl;
      edit_distance(p[i],cost_arr);
    }
  output.close();
}

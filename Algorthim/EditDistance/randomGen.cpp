#include<iostream>
#include<cstdlib>
#include<time.h>
#include<string.h>
#include<fstream>

using namespace std;

int main(int argc,char ** argv){
    int length = atoi(argv[1]);
    int random = 0;
    int letterGen;
    srand(time(NULL));

    ofstream myfile;
    myfile.open("randomInput.txt");
    if(!(myfile.is_open())){
        cout << "Fail to open the file. "<< endl;
        return 1;
    }


    
    for(int i=0;i<10;i++){
        do{
            random = rand() % length + 1;
        }while(random > (length*3/4) || random < (length/4));

        string arr1[random],arr2[length - random];

        for(int i=0;i<random;i++){
            letterGen = rand() % 4 + 1;
            if(letterGen == 1) 
                arr1[i] = 'A';
            else if (letterGen == 2)
                arr1[i] = 'T';
            else if (letterGen == 3)
                arr1[i] = 'C';
            else 
                arr1[i] = 'G';
        }

        for(int j=0;j<(length-random);j++){
            letterGen = rand() % 4 + 1;
            if(letterGen == 1) 
                arr2[j] = 'A';
            else if (letterGen == 2)
                arr2[j] = 'T';
            else if (letterGen == 3)
                arr2[j] = 'C';
            else 
                arr2[j] = 'G';        
        }

        for(int i=0;i<random;i++){
            myfile << arr1[i];
        }
        myfile << ',';
        for(int j=0;j<(length-random);j++){
            myfile << arr2[j];
        }
        myfile << endl;


    }

    return 0;

}
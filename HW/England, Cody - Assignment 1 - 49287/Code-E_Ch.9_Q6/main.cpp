/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 4:18 AM
 */

//Libraries
#include <iostream>
using namespace std;

//Function prototypes
int *getData(int &);//Read the array
int *augment(const int *,int);//Augment and copy the original array
void prntAry(const int *,int);//Print the array

//Execution begins here
int main(){
	//Declare variables
	   int size;              //Size of Array
	    
	 //Fill array
	 int *ary = getData(size);
	 
	 //Print array
	 prntAry(ary,size);
	 cout << endl;
	 size++; //Increment size to augment array
	 
	 //Augment array
	 int *augAry = augment(ary,size);
	 
	 //Print array
	 prntAry(augAry,size);
	 
	 delete []ary;                                              ////delete1
	 delete []augAry;                                           ////delete2
	 
	 //Exit stage right
	return 0;
}



int *getData(int &arySz)
{
    //Get size of the array
    cin >> arySz;
    
     //Allocate memory
    int *array = new int[arySz];                                ////Create1                
    
    //Fill the array with input numbers
    for(int i = 0; i < arySz; i++)
        cin >> *(array + i);

    return array; 
}


int *augment(const int *Arry,int arySz)
{
    //Declare and allocate an array
    int *aug = new int[arySz];                              //////create2
    *aug = 0;
    //Fill with passed array
    for(int i = 1; i < arySz; i++){
        aug[i] = Arry[i - 1];
    }
    //Return the copy
    return aug;
}


void prntAry(const int *ary,int sz)
{
    for(int i = 0; i < sz; i++){
    cout << *(ary + i);
    if(i != sz - 1)
    cout << " ";
    }
}




/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 7:47 AM
 */

//Libraries
#include <iostream>

using namespace std;
int *getData(int &);        //Return the array size and the array from the inputs
int *sumAry(const int *,int);//Return the array with successive sums
void prntAry(const int *,int);//Print the array

int main(){
//Delcare variables
    int sz,    //Size of array
    *ary = nullptr;  //Pointer array
    
    //Fill array
    ary = getData(sz);
    
    //Print intitial array
     prntAry(ary,sz);
     cout << endl;
     
     //Fill parrallel array with successive sums
     int *smAry = sumAry(ary,sz);
     
     //Print sum array
      prntAry(smAry,sz);
      
    delete []ary;                               ////delete1
    delete []smAry;                               ////delete2
    
	return 0;
}

int *getData(int &arySz)
{
    //Get size of the array
    cin >> arySz;
    
     //Allocate memory
    int *array = new int[arySz];                ////create1            
    
    //Fill the array with input numbers
    for(int i = 0; i < arySz; i++)
        cin >> *(array +i);

    return array;
}


int *sumAry(const int *ary,int arySz)
{
     //Allocate memory
    int *smAry = new int[arySz];                ////create2  
    
    *smAry = 0; //Initialize first element
    //Fill the array with input numbers
    for(int i = 0; i < arySz; i++){
        *(smAry + i) = ((i == 0) ?  *(ary + i) :
         *(smAry + i - 1) + *(ary + i));
    }

    return smAry;
}


void prntAry(const int *ary,int arySz)
{
    for(int i = 0; i < arySz; i++){
        cout << *(ary + i);
        if (i != arySz - 1)
        cout << " ";
    }
}




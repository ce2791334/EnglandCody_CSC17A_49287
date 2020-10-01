/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 12:25 AM
 */

//Libraries
#include <iostream>
#include <iomanip>
using namespace std;

//No Global Constants

//Function Prototypes
int *getData(int &);         //Return the array size and the array
void prntDat(int *,int);    //Print the integer array
float *median(int *,int);  //Fill the median Array with the Float array size, the median, and the integer array data
void prntMed(float *);     //Print the median Array

//Execution begins here
int main(){
	//Declare variables and fill
    int arySize,//Size of array
        *ary;//Pointer to the array
  
   //Call fxn to get array size
     ary = getData(arySize);
  
   //Print the integer array
    prntDat(ary,arySize);
 
   //Calculate the mode array
    float *medAry = median(ary,arySize);
    
    //Print the median information of the array
     prntMed(medAry);
    
    //Delete allocated memory
    delete []ary;
    delete []medAry;
    
    //Exit stage right
	return 0;
}


int *getData(int &arySz)
{
    //Get size of the array
    cin >> arySz;
    
     //Allocate memory
    int *array = new int[arySz];                            
    
    //Fill the array with input numbers
    for(int i = 0; i < arySz; i++)
        cin >> *(array + i);

    return array;
}


void prntDat(int *ary,int arySz)
{
    for(int i = 0; i < arySz; i++){
        cout << *(ary + i);
        if (i != arySz - 1)
        cout << " ";
    }
        cout << endl;
}


float *median(int *ary,int arySz)
{
   
    int ftSz = arySz + 2;
    //Allocate memory
    float *medAry=new float[ftSz];                            
   
   //Fill the array with elements as floats
    for(int i = 2; i < ftSz; i++)
         *(medAry + i) = *(ary + i - 2);
         
    int sum = 0;
    for (int val = 0; val < arySz; val++)
    sum += *(ary + val);
    
    //Fill first two elements with array size and median
    *medAry = ftSz;
    *(medAry + 1) = (sum / 1.0) / arySz;

    return medAry;
}


void prntMed(float *medAry)
{
    //Print array size and then formatted median
    //and elements
    //cout << "\n\n\n" << sizeof(medAry) << "\n\n\n";
    int size = 0;
    
    while (medAry[size] != 0)
    size++;
   // cout << size << "    ";
    cout << *medAry << " ";
    cout << fixed << setprecision(2);
    for(int i = 1; i < size; i++){
        cout << *(medAry + i);
        if (i != size - 1)
        cout << " ";
    }
}





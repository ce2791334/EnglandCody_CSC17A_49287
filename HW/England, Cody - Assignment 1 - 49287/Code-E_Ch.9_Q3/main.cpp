/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 12:25 AM
 */

//Libraries
#include <iostream>
using namespace std;

//Function prototpes
int *getData(int &);               //Fill the array
int *sort(const int *,int);       //Sort smallest to largest
int *reverse(const int *,int);  //Sort in reverse order
void prntDat(const int *,int); //Print the array

//Execution begins here
int main(){
	//Declare variables
	int arySize,    //Holds size of array
	    *ary = nullptr;  //Pointer array
	    
	    //Get array data
	    ary = getData(arySize);
	    
        //Sort the array
        ary = sort(ary,arySize);
         
         //Print sorted array
         prntDat(ary,arySize);
         cout << endl;
 
        //Sort the array in reverse order
         int *revAry = reverse(ary,arySize);
    
        //Print reverse sorted array
         prntDat(revAry,arySize);
    
        //Delete allocated memory
	    delete []ary;                       /////delete 1
	    delete []revAry;                    ////delete2        
	    
	//Exit stage right
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

int *sort(const int *ary,int arySz)
{
    //Declare and allocate an array copy
    int *srtAry = new int[arySz];                                              
    //Fill with passed array
    for(int i = 0; i < arySz; i++)
        *(srtAry + i) = *(ary + i);
    
    //Loop until all elements are in ascending order
    for (int maxVal = arySz -1; maxVal > 0; maxVal--)
    {
        for (int i = 0; i < maxVal; i++)
        {
            if (*(srtAry + i) > *(srtAry + i + 1))
                swap(*(srtAry + i), *(srtAry + i + 1));
        }
    }

    return srtAry;
}

int *reverse(const int *ary,int arySz)
{
    //Declare and allocate an array copy
    int *revAry = new int[arySz];                                              
    //Fill with passed array
    for(int i = 0; i < arySz; i++)
        *(revAry + i) = *(ary + i);
  
        //Loop until all elements are in ascending order
    for (int maxVal = arySz -1; maxVal > 0; maxVal--)
    {
        for (int i = 0; i < maxVal; i++)
        {
            if (*(revAry + i) < *(revAry + i + 1))
                swap(*(revAry + i), *(revAry + i + 1));
                
        }
    }   

    return revAry;
}

void prntDat(const int *ary,int arySz)
{
    for(int i = 0; i < arySz; i++){
        cout << *(ary + i);
        if (i != arySz - 1)
        cout << " ";
    }

}






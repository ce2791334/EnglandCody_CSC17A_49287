/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 9:33 AM
 */

//Libraries
#include <iostream>
using namespace std;

//Function prototypes
int **getData(int &,int &);        //Return the 2-D array and its size.
void prntDat(const int* const *,int,int);//Print the 2-D Array
void destroy(int **,int,int);       //Deallocate memory
int sum(const int * const *, int,int);    //Return the Sum

//Execution begins here
int main(){
	//Declare variables
	int   cols = 0,
	      rows = 0;
	
	//Fill 2D-array
	int **ary = getData(rows,cols);
	
	//Print 2D-array
    prntDat(ary,rows,cols);
    
    //Find the sum of the array elements and print
	int sm = sum(ary,rows,cols);
	cout << sm;
	
	//Delete allocated memory
	destroy(ary,rows,cols);
	
	//Exit stage right
	return 0;
}


int **getData(int &rw,int &cl)
{
    //Get number of rows and collumns input
    cin >> rw >> cl;
    
    int **array = new int*[rw];                                                  ////create1   
    for (int idxRw = 0; idxRw < rw; idxRw++)
        array[idxRw] = new int[cl];                                                  ////create2 
        
    //Loops to assign all input values into 2D-array
   for ( int j = 0; j < rw; j++ )
    for ( int i = 0; i < cl; i++ )
        cin >> array[j][i];
   
   return array;
}


void prntDat(const int* const *ary,int rw,int cl)
{
    //Loops to output all input values into 2D-array
   for ( int j = 0; j < rw; j++ ){
    for ( int i = 0; i < cl; i++ ){
        cout << ary[j][i];
        if (i < cl - 1)
        cout << " ";
    }
    cout << endl;
   }
}


void destroy(int **ary,int rw,int cl)
{
    //Loop to delete all allocated memory
    for ( int i = 0; i < rw; i++ )
    delete []ary[i];                                       ////delete1 
    delete []ary;                                         ////delete2
}


int sum(const int * const *ary, int rw,int cl)
{
    //Declare variables
    int sum = 0; //Sum of array elements
    //Loops to add all values in 2D-array
    for ( int j = 0; j < rw; j++ )
    for ( int i = 0; i < cl; i++ )
    sum += ary[j][i];
    
    return sum;
}




 
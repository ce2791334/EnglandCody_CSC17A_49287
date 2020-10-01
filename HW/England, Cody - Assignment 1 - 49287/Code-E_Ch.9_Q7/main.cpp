/* 
 * File:   main.cpp
 * Author: Cody England
 * Created on September 30, 2020, 4:39 AM
 */

//Libraries
#include <iostream>
using namespace std;

//Function prototypes
int **getData(int &,int &);//Get the Matrix Data
void printDat(const int * const *,int,int);//Print the Matrix
int **augment(const int * const *,int,int);//Augment the original array
void destroy(int **,int);//Destroy the Matrix, i.e., reallocate memory


//Execution begins here
int main(){
	//Declare variables
	int   cols = 0,
	      rows = 0;
	
	//Fill 2D-array
	int **ary = getData(rows,cols);
	
	//Print 2D-array
    printDat(ary,rows,cols);
  
    //Augment 2D array
    int **augAry = augment(ary,rows,cols);
	
	//Print augmented 2D-array
    printDat(augAry,rows + 1,cols + 1);
    
	//Delete allocated memory
	destroy(ary,rows);
	destroy(augAry,rows + 1);
	
	//Exit stage right
	return 0;
}


int **getData(int &rw,int &cl)
{
    //Get size of the array
    cin >> rw >> cl;
    
    int **array = new int*[rw];                                /////Create1
     //Allocate memory
     for(int i = 0; i < rw; i++)
        array[i] = new int[cl];                                ////Create2              
    
    //Loops to assign all input values into 2D-array
   for ( int j = 0; j < rw; j++ )
    for ( int i = 0; i < cl; i++ )
        cin >> array[j][i];

    return array; 
}


void printDat(const int * const *ary,int rw,int cl)
{
    int check;
    if (check < 1)
    check = 0;
    
    for(int j = 0; j < rw; j++){
    for(int i = 0; i < cl; i++){
    cout << ary[j][i];
    if(i != cl - 1)
    cout << " ";
    } 
    check++;
    if(check < ((2 * rw) - 1))
    cout << endl;
    }
}


int **augment(const int * const *ary,int rw,int cl)
{
    int augSz = rw + 1;
    int augCol = cl + 1;
     int **augAry = new int*[augSz];                               /////Create3
     //Allocate memory
     for(int i = 0; i < augSz; i++)
        augAry[i] = new int[augCol];                                ////Create4          
    
    //Loops to assign all input values into 2D-array
   for ( int j = 0; j < augSz; j++ )
    for ( int i = 0; i < augCol; i++ ){
         augAry[j][i] = ((i == 0 || j == 0) ? 0 :
                        ary[j - 1][i - 1]);
    }
    
    //Return the copy
    return augAry;
}


void destroy(int **ary,int rw)
{
    //Loop to delete all allocated memory
    for ( int i = 0; i < rw; i++ )
    delete []ary[i];                                       ////delete1,3 
    delete []ary;                                         ////delete2,4
}



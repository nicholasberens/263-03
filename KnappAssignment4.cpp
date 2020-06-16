/*#####################################################################
* File:  KnappAssignment4.cpp
*
* Written By: Justin Knapp
*
* Created On: 6/15/2020
*
*********************************************************************
*
* Detail Description: The projects main driving functions
*
*####################################################################*/
#include <iostream>
#include <climits>
#include <queue>
#include <fstream>
#include <cstring>

using namespace std;

#define max(a,b) ((a>b)? a : b)
 
class request{
	
private:
	string name;
	unsigned int availableQuantity;
	unsigned int sizeOfArray;
	double prices[15];
	
public:
	request(){};//should never call
	request(string callName,unsigned int callAvailableQuantity, unsigned int callSizeOfArray, double *arr){
		name = callName;
		sizeOfArray = callAvailableQuantity;
		availableQuantity = callAvailableQuantity;
		for(int count = 0; count < (sizeOfArray); count++){
			prices[count] = arr[count];
		}
	};
	
	//setters
	void setPrices(int values[]){
		//this should fill this requests prices.
	};
	//getters
	string getName(){
		return name;
	};
	unsigned int getAvailableQuantity(){
		return availableQuantity;
	};
	unsigned int getSizeOfArray(){
		return sizeOfArray;
	};
	double * getPrices(){
		return prices;
	};
};

void loadRequests();
void testFunction();
int determineOptimalValue(double values[], int n);

/***********************************************************************
 * @Function: main
 * @Description: The projects main driving functions
 * @Param: n/a
 * @Returns: int 0 confirming main function completed
 **********************************************************************/
int main (){
  
  	queue<request> myRequests;
	request temp{};
	string tempRequestName;
	double *tempPrices;	
	int q;
	unsigned int tempAvailableQuantity, tempSizeOfArray;
	double tempArray[15];
	
	/*string line;
	int i = 0;

	fstream file;
	string word, t, q, filename;

	// filename of the file
	filename = "sample.txt";

	// opening file
	file.open(filename.c_str());

	// extracting words from the file
	while (file >> word)
	{
    	// displaying content
    		cout << word << endl;
	}

	file.close();
	//read in all requests from a given file. 
	//place requests in array to be worked through
	*/
	
	myRequests.push(request(tempRequestName,tempAvailableQuantity,tempSizeOfArray,tempArray));
	
	
	while(!myRequests.empty()){
		temp = myRequests.front();
		tempPrices = temp.getPrices();
		for(int i = 0; i < temp.getSizeOfArray(); i++){
			cout << *(tempPrices + i) << endl;
		}
		q = determineOptimalValue(tempPrices, temp.getAvailableQuantity());
		cout << q << endl;
		myRequests.pop();
	}
	
  return 0;
}


/***********************************************************************
 * @Function: determineOptimalValue
 * @Description: 
 * @Param: n/a
 * @Returns: n/a
 **********************************************************************/
int determineOptimalValue(double values[], int n){
   int val[n+1]; 
   val[0] = 0; 
   int i, j; 

   for (i = 1; i<=n; i++) 
   { 
       double max_val = INT_MIN; 
       for (j = 0; j < i; j++) 
         max_val = max(max_val, values[j] + val[i-j-1]); 
       val[i] = max_val; 
   } 
  
   return val[n]; 
}

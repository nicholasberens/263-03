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

 
class request{
	
private:
	string name;
	unsigned int availableQuantity;
	double prices[15];
	
public:
	request();//should never call
	//request(string name,unsigned int availableQuantity): name(name), availableQuantity(availableQuantity){}
	request(string callName,unsigned int callAvailableQuantity, double *arr){
		int a = 0;
		name = callName;
		availableQuantity = callAvailableQuantity;
		for(int a = 0; a <= sizeof(arr) / sizeof(double); a++){
			prices[a] = arr[a];
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
	double * getPrices(){
		return prices;
	};
};

void loadRequests();
void testFunction();
int determineOptimalValue(int values[], int n);
int max(int a, int b) ;

/***********************************************************************
 * @Function: main
 * @Description: The projects main driving functions
 * @Param: n/a
 * @Returns: int 0 confirming main function completed
 **********************************************************************/
int main (){
  loadRequests();
  //testFunction();
  return 0;
}

/***********************************************************************
 * @Function: loadRequests
 * @Description: 
 * @Param: n/a
 * @Returns: n/a
 **********************************************************************/
void loadRequests(){
	
	
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
	
	
	
	
	
	double cats2[15] = {3.0,4.5};
	request temp("cats",3,cats2);
	cats2[1] = 45;
	double *cats3;
	cats3 = temp.getPrices();
	cout << *(cats3  + 1)<< endl;
	cout << temp.getName() << endl;
	queue<request> myRequests;
	
	myRequests.push(request("cats",3,cats2));
	//myRequests.push(request("dogs",4));
	
	
	
}

/***********************************************************************
 * @Function: 
 * @Description: 
 * @Param: n/a
 * @Returns: n/a
 **********************************************************************/
void testFunction(){
	//manually entered array
	int arr[] = {150,301,472,592,752,912,1100,1220,1368,1499};
	int n = sizeof(arr) / sizeof(int);
	int q = determineOptimalValue(arr, n);
	cout << q << endl;
}

/***********************************************************************
 * @Function: determineOptimalValue
 * @Description: 
 * @Param: n/a
 * @Returns: n/a
 **********************************************************************/
int determineOptimalValue(int values[], int n){
   int val[n+1]; 
   val[0] = 0; 
   int i, j; 

   for (i = 1; i<=n; i++) 
   { 
       int max_val = INT_MIN; 
       for (j = 0; j < i; j++) 
         max_val = max(max_val, values[j] + val[i-j-1]); 
       val[i] = max_val; 
   } 
  
   return val[n]; 
}

/***********************************************************************
 * @Function: max
 * @Description: 
 * @Param: n/a
 * @Returns: n/a
 **********************************************************************/
int max(int a, int b) { 
	return (a > b)? a : b;
}

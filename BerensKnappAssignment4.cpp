/*#####################################################################
* @Filename:  BerensKnappAssignment4.cpp
* @Authors: Nicholas Berena & Justin Knapp
* @Professor: Professor Jonathan Leidig
* @Version: 6/15/2020
*
*********************************************************************
*
* Detail Description: The purpose of this program is to design an
* algorithm that determines the most efficient way to sell a given
* quantity with a given amount. The program determines how best to
* split a given quantity into resellable partitions that offer the
* seller maximum profit. Code was used from Geeksforggeeks.com and
* used within the program by Nicholas Berens and Justin Knapp.
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
    //These private variables contain the commodity name, amount of commodity, size of data array, and set of prices
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

    //sets our prices if ever needed
    void setPrices(int values[]){
        //this should fill this requests prices.
    };
    //getters

    //gets the name of the commodity
    string getName(){
        return name;
    };

    //gets the available quantity
    unsigned int getAvailableQuantity(){
        return availableQuantity;
    };

    //gets the size of our array
    unsigned int getSizeOfArray(){
        return sizeOfArray;
    };

    //gets our price index
    double * getPrices(){
        return prices;
    };
};

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

    string line;

    int lineCount = 0;
    int numParse = 0;
    int indexCount = 0;
    int fill = 0;

    string amountOf;

    fstream file;                                                                                                           //fstream object for reading in files
    string word, filename;
    string numVal;
    // filename of the file
    filename = "C:\\Users\\NickBerens\\CIS 263\\Berens_Project4\\sample.txt";                                               //if you're using Windows, they require you to include the entire pathname. If you're using a self-respecting OS you'll only need the filename
    // opening file
    file.open(filename.c_str());
    // extracting words from the file
    while (!file.eof())                                                                                                     //while we haven't reached the end of the file
    {
        indexCount = 0;
        numParse = 0;
        getline(file, line);                                                                                         //get the current line on the text file

            //If we are on an even numbered line or line 0, it contains the commodity and available quantity
            if(lineCount == 0 || lineCount % 2 == 0) {

                //clear our values in case we have just finished a calculation and are running a new one
                tempRequestName = "";
                tempAvailableQuantity = 0;
                tempSizeOfArray = 0;
                for(fill = 0; fill < 15; fill++){
                    tempArray[fill] = 0;
                }
                amountOf = "";
                numParse = 0;

                while (line[numParse] != ' ') {                                                                             //determines the amount of available commodity
                    amountOf += line[numParse];
                    numParse++;
                }
                tempAvailableQuantity = stoi(amountOf);                                                                     //converts value to an integer

                numParse++;
                for (numParse = numParse; numParse < line.length(); numParse++) {                                           //determines the name of the commodity
                    tempRequestName += line[numParse];
                }

                cout << "The amount of available commodity is: " << tempAvailableQuantity << endl;
                cout << "The type of commodity purchased is: " << tempRequestName << endl;
            }

            //If we are on an odd numbered line, we are looking at the list of prices/data of the commodity
            else{
                indexCount = 0;
                numVal = "";

                //This for loop parses each price value and stores it into an array that will be used for profit calculation
                for(numParse = 0; numParse < line.length(); numParse++){

                    //Every time we see a space
                    if(line[numParse] == ' '){
                        tempArray[indexCount] = stoi(numVal);                                                               //convert the string to an integer and store it in our array
                        numVal = "";                                                                                        //clear numVal for the next value
                        indexCount++;                                                                                       //increment the index
                    }
                    else{
                        numVal += line[numParse];                                                                           //if no space yet, keep parsing
                    }
                }

                tempArray[indexCount] = stoi(numVal);                                                                       //accounts for the last value on the list
                tempSizeOfArray = indexCount;                                                                               //sets the size of our array

                myRequests.push(request(tempRequestName,tempAvailableQuantity,tempSizeOfArray,tempArray));               //calls the myRequests push function to push all of our important values to the queue

//
//
                while(!myRequests.empty()){                                                                                 //while the queue isn't empty
                    temp = myRequests.front();                                                                              //put the most recent request at the front
                    tempPrices = temp.getPrices();                                                                          //calls our getPrices getter function to determine prices of commodity
                    for(int i = 0; i < temp.getSizeOfArray(); i++){
                        cout << *(tempPrices + i) << endl;
                    }
                    q = determineOptimalValue(tempPrices, temp.getAvailableQuantity());                                     //sets q equal to the output of the function that determines the maximized profit
                    cout << "The maximum profit is $" << q << endl << "\n";
                    myRequests.pop();                                                                                       //pops the head of the queue
                }
            }



            lineCount++;                                                                                                    //increment to the next line
    }
    file.close();                                                                                                           //close the file
    return 0;
}


/***********************************************************************
 * @Function: determineOptimalValue
 * @Description: This function is designed to calculate the maximum
 * profit based on a combination of data. The logic was derived from
 * GeeksforGeeks at https://www.geeksforgeeks.org/cutting-a-rod-dp-13
 * and was referenced by Nicholas Berens and Justin Knapp on 6/15/2020.
 * @Param: double values[] the array of values that the maximum profit
 * will be calculated from, int n the size of the array
 * @Returns: int val[n] the maximum profit based on the data
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

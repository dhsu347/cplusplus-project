//
//  bot.cpp
//  Utility bot
//
//  Created by Yuzu on 4/10/2024
//

#include <iostream>
#include <fstream>
#include <string>
//#include <stdlib.h>
#include <array>
#include <numbers>
#include <math.h>
#include <vector>
#include <algorithm>
using namespace std;

void findIndexInFile(string);

void ticTacToe(int);
void printBoard(string[3][3]);
double findDistance(string, string);
//string[][] playerAct(string[3][3]);
//string[][] botAct(string[3][3]);
void stats(vector<string>);
double calc(string);
double operate(double, char, double);
int findNumIndex(string, bool);

int main(int argc, const char * argv[]) {

    int option;
    cout << "Welcome to Utility Bot!" << endl;
    while(option != 5){
        
        cout << "\nOptions" << endl;
        cout << "1. Find word in file" << endl;
        cout << "2. Add numbers" << endl;
        cout << "3. Set statistics" << endl;
        cout << "4. Distance between world cities" << endl;
        cout << "5. quit" << endl;
        
        while(option < 1 || option > 5){
            cout << "Select: ";
            cin >> option;
            cout << "" << endl;
        }

        if(option == 1){
            cout << "Enter filename: ";
            string filename;
            cin >> filename;
            findIndexInFile(filename);
        }
        /*
        else if(option == 3){
            cout << "Enter number of players (0, 1, or 2): ";
            int numPlayers;
            while(numPlayers < 0 || numPlayers > 2)
                cin >> numPlayers;
            ticTacToe(numPlayers);
        }
        */
        else if(option == 2){
            //cout << "Enter an expression like this: 1-2.2*3/4" << endl;
            cout << "Enter an expression like this: 2+2" << endl;
            cout << "Multiplication, division, addition, subtraction, and exponents supported" << endl;
            cout << "Only works with single expressions" << endl;

            string input;
            getline(cin, input); //
            getline(cin, input);

            cout << to_string(calc(input)) << endl;
        }
        else if(option == 3){
            cout << "Enter stats set like this: 1.1 2.2 3.3 " << endl;
            cout << "You can also do 80 3x100 120 to get 80 100 100 100 120 " << endl;

            string input;
            vector<string> set;

            getline(cin, input); //
            getline(cin, input);

            while(input.find(" ") != -1){
                set.push_back(input.substr(0, input.find(" ")));
                input = input.substr(input.find(" ") + 1);
            }
            set.push_back(input);
            stats(set);
        }
        else if(option == 4){
            string city1;
            string city2;
            cout << "Enter first city name: ";
            getline(cin, city1); //flush buffer
            getline(cin, city1);
            cout << "\nEnter second city name: ";
            getline(cin, city2);
            
            int distance = findDistance(city1, city2);
            if(distance == -1){
                cout << "\nUnable to locate one or both cities in the database." << endl;
            }
            else {
                cout << "\nDistance between the two cities: " + to_string(distance) + " mi" << endl;
            }
        }
        else if(option < 5){
            cout << "This feature has yet to be implemented. Please come back later." << endl;
        }

        if(option != 5)
            option = 0;
    }
    
    return 0;
}
//compile: g++ bot.cpp
//run: ./a.out
//open terminal: command shift `

void findIndexInFile(string fileName){
    ifstream inFile;
    inFile.open(fileName);
    string target;
    cout << "What word would you like to find? ";
    cin >> target;

    string line; 
    int lineNum = 0;
    bool indicesFound = false;

    while (getline(inFile, line)) { 
        lineNum++;

        if(lineNum == 1)
            cout << "\nFound target word \"" + target + "\" at " << endl;

        if(line.find(target) != -1){ //found target
            cout << "Line " + to_string(lineNum) + ", column " + to_string(line.find(target)) << endl;
            line = line.substr(line.find(target) + 1);

            //look along same line to find more instances of target
            while(line.find(target) != -1){
                cout << "Line " + to_string(lineNum) + ", column " + to_string(line.find(target)) << endl;
                line = line.substr(line.find(target) + 1);
            }
            indicesFound = true;
        }
    } 

    if(lineNum == 0)
        cout << "File " + fileName + " is either empty or does not exist. " << endl;
    else if(!indicesFound) 
        cout << "The target word \"" + target + "\" was not found in the file. " << endl;

    inFile.close();
}

//unimplemented
void ticTacToe(int numPlayers){
    string board[3][3] = {{" ", " ", " "}, {" ", " ", " "}, {" ", " ", " "}};
    printBoard(board);
}

//unimplemented
void printBoard(string board[3][3]){
    cout << "\n-------" << endl;
    for(int i = 0; i < *(&board + 1) - board; i++){
        for(int j = 0; j < *(&board[0] + 1) - board[0]; j++){
            cout << "|" + board[i][j];
        }
        cout << "|" << endl;
        cout << "-------" << endl;

    }
}

//find distance between two world cities using latitude/longitude
double findDistance(string city1, string city2){
    double distance = -1;

    ifstream inFile;
    inFile.open("worldcities.csv");

    double lat1;
    double long1;
    double lat2;
    double long2;

    bool found1 = false;
    bool found2 = false;
    string line;
    int lineNum = 0;
    while (getline(inFile, line)) { //get lat/long of both cities
        lineNum++; 
        if(lineNum != 0){
            string cityName = line.substr(line.find(",") + 2);
            cityName = cityName.substr(0, cityName.find(",") - 1);

            if(cityName == city1 && !found1){
                found1 = true;//
                line = line.substr(line.find(",") + 2);
                line = line.substr(line.find(",") + 2);
                lat1 = stod(line.substr(0, line.find(",") - 1));
                line = line.substr(line.find(",") + 2);
                long1 = stod(line.substr(0, line.find(",") - 1));
            }
            else if (cityName == city2 && !found2){
                found2 = true;
                line = line.substr(line.find(",") + 2);
                line = line.substr(line.find(",") + 2);
                lat2 = stod(line.substr(0, line.find(",") - 1));
                line = line.substr(line.find(",") + 2);
                long2 = stod(line.substr(0, line.find(",") - 1));
            }
        }
    }

    if(found1 && found2){
        //make earth radius constant
        int radius = 3958;
        double pi = 3.1415926535897932384626433;

        //convert to radians
        lat1 *= (pi/180);
        long1 *= (pi/180);
        lat2 *= (pi/180);
        long2 *= (pi/180);
        //use haversine formula to find spherical distance
        distance = 2 * radius * asin(sqrt(pow(sin((lat2-lat1)/2),2)+cos(lat1)*cos(lat2)*pow(sin((long2-long1)/2),2)));
        
    }

    return distance;
}

//get stats of a set
void stats(vector<string> set){
    int i = 0;
    while(i < set.size()){ //e.g. convert 3x100 to 100 100 100
        if(set.at(i).find("x") != -1){
            int mult = stoi(set.at(i).substr(0, set.at(i).find("x")));
            string str = set.at(i).substr(set.at(i).find("x") + 1);
            set.erase(set.begin()+i);
            for(int j = 0; j < mult; j++){
                set.push_back(str);
            }
        }
        else {
            i++;
        }
    }

    //convert strings to numbers
    vector<double> numSet;
    for(i = 0; i < set.size(); i++){
        numSet.push_back(stod(set.at(i)));
    }

    
    int endIndex = numSet.size() - 1;
    int maxIndex = 0;

    //sort set
    while(endIndex >= 0){
        for(int a = 0; a <= endIndex; a++){
            if(numSet.at(a) > numSet.at(maxIndex)){
                maxIndex = a;
            }
        }
        
        double temp = numSet.at(maxIndex);
        numSet.at(maxIndex) = numSet.at(endIndex);
        numSet.at(endIndex) = temp;
        endIndex--;
        maxIndex = 0;
    }

    double min = *min_element(numSet.begin(), numSet.end());
    double max = *max_element(numSet.begin(), numSet.end());
    double mean = 0;
    double meanSum = 0;
    double median = 0;
    vector<double> modes;
    int modeCount = 2;
    double stdev = 0;

    //loop to find mode
    for(i = 0; i < numSet.size(); i++){
        meanSum += numSet.at(i);

        int count = 0;
        for(int j = 0; j < numSet.size(); j++){
            if(numSet.at(i) == numSet.at(j))
                count++;
        }

        if(count > modeCount){
            modes.clear();
            modes.push_back(numSet.at(i));
            modeCount = count;
        }
        else if(count == modeCount){
            bool isDuplicate = false;

            //multiple modes
            for(int k = 0; k < modes.size(); k++){
                if(modes.at(k) == numSet.at(i))
                    isDuplicate = true;
            }

            if(!isDuplicate){
                modes.push_back(numSet.at(i));
            }
        }
    }

    if(numSet.size() != 0)
        mean = meanSum/numSet.size();
    
    if(numSet.size()%2 == 0 && numSet.size() != 0)
        median = (numSet.at(numSet.size()/2)+numSet.at(numSet.size()/2-1))/2;
    else if(numSet.size() != 0)
        median = numSet.at(numSet.size()/2);

    //find standard deviation
    vector<double> dev;
    for(i = 0; i < numSet.size(); i++){
        dev.push_back(pow(numSet.at(i) - mean, 2));
    }
    double devSum = 0;
    for(i = 0; i < dev.size(); i++){
        devSum += dev.at(i);
    }
    if(dev.size() != 0)
        stdev = sqrt(devSum/dev.size());

    cout << "\nMin: " + to_string(min) << endl;
    cout << "Max: " + to_string(max) << endl;
    cout << "Mean: " + to_string(mean) << endl;
    cout << "Median: " + to_string(median) << endl;
    cout << "Modes: ";
    for(i = 0; i < modes.size(); i++){
        cout << to_string(modes.at(i)) + " ";
    }
    cout << "\nStandard deviation " + to_string(stdev) << endl;
}

//calculate expressions
//only works with single expressions
double calc(string input){

    double result = 0;
    int openIndex;
    int closeIndex;
    
    for(int i = 0; i < input.length(); i++){

        //cout << input.substr(0, openIndex) + " pre" << endl;
        //cout << to_string(calc(input.substr(openIndex + 1, closeIndex)));
        //cout << input.substr(closeIndex + 1);

        if(input.at(i) == '('){
            openIndex = i;
        }
        else if(input.at(i) == ')'){
            closeIndex = i;
            input = input.substr(0, openIndex) + to_string(calc(input.substr(openIndex + 1, closeIndex))) + input.substr(closeIndex + 1);
        }
    }

    int index;
    double num1;
    double num2;
    int i = input.length() - 1;
    while(input.find("^") != -1 && i < input.length()){
        if(input.at(i) == '^'){

            index = i;
            int num1index = findNumIndex(input.substr(0, index), true);
            int num2index = findNumIndex(input.substr(index + 1), false);
            num1 = stod(input.substr(num1index, index));
            num2 = stod(input.substr(index + 1, index + num2index));
            //cout << input.substr(0, num1index) + " pre" << endl;
            //cout << to_string(operate(num1, input.at(i), num2)) + " expr"<< endl;
            //cout << input.substr(num2index + 1) + " post"<< endl;
            input = input.substr(0, num1index) + to_string(operate(num1, input.at(i), num2)) + input.substr(num2index + 1);
            int nextOp = max(max(0, 1), 1);
            i = input.length() - 1;
           // cout << input + " input "<< endl;
        }
        else{
            i--;
        }
    }

    i = 0;
    while((input.find("*") != -1 || input.find("/") != -1) && i < input.length()){
        if(input.at(i) == '*' || input.at(i) == '/'){

            index = i;
            int num1index = findNumIndex(input.substr(0, index), true);
            int num2index = findNumIndex(input.substr(index + 1), false);
            num1 = stod(input.substr(num1index, index));
            num2 = stod(input.substr(index + 1, index + num2index));
            //cout << input.substr(0, num1index) + " pre" << endl;
            //cout << to_string(operate(num1, input.at(i), num2)) + " expr"<< endl;
            //cout << input.substr(num2index + 1) + " post"<< endl;
            input = input.substr(0, num1index) + to_string(operate(num1, input.at(i), num2)) + input.substr(num2index + 1);
            int nextOp = max(max(0, 1), 1);
            i = 0;
            //cout << input + " input "<< endl;
        }
        else{
            i++;
        }
    }

    i = 0;
    while((input.find("+") != -1 || input.find("-") != -1 && input.find("-") != 0) && i < input.length()){
        if(input.at(i) == '+' || input.at(i) == '-' && (i > 0 || input.at(i - 1) != '+' && input.at(i - 1) != '-')){

            index = i;
            int num1index = findNumIndex(input.substr(0, index), true);
            int num2index = findNumIndex(input.substr(index + 1), false);
            num1 = stod(input.substr(num1index, index));
            num2 = stod(input.substr(index + 1, index + num2index));
            //cout << input.substr(0, num1index) + " pre" << endl;
            //cout << to_string(operate(num1, input.at(i), num2)) + " expr"<< endl;
            //cout << input.substr(num2index + 1) + " post"<< endl;
            input = input.substr(0, num1index) + to_string(operate(num1, input.at(i), num2)) + input.substr(num2index + 1);
            int nextOp = max(max(0, 1), 1);
            i = 0;
            //cout << input + " input "<< endl;
        }
        else{
            i++;
        }
        
    }

    //cout << input << endl;
    result = stod(input);
    return result;
}

double operate(double num1, char operation, double num2){
    double result = 0;

    if(operation == '+')
        result = num1 + num2;
    if(operation == '-')
        result = num1 - num2;
    if(operation == '*')
        result = num1 * num2;
    if(operation == '/')
        result = num1 / num2;
    if(operation == '^')
        result = pow(num1, num2);
    
    return result;
}

int findNumIndex(string str, bool isBackward){

    int i;
    if(isBackward){
        i = str.length() - 1;
        while(i > 0 && str.at(i - 1) != '+' && str.at(i - 1) != '-' && str.at(i - 1) != '*' && str.at(i - 1) != '/' && str.at(i - 1) != '^')
            i--;

        if(i >= 2 && str.at(i - 1) == '-' && (str.at(i - 2) != '+' || str.at(i - 2) != '-' || str.at(i - 2) != '*' || str.at(i - 2) != '/' || str.at(i - 2) != '^'))
            i--;

    }
    else{
        i = 0;
        while(i < str.length() && str.at(i) != '+' && str.at(i) != '-' && str.at(i) != '*' && str.at(i) != '/' && str.at(i) != '^')
            i++;

        if(i == 0 && i < str.length() - 1)
            i++;

    }
    
    return i;
}
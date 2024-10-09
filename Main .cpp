#include <iostream>//for input and output operations.
#include <string>//handling and manipulating string data
#include <fstream>//file handling
#include <vector>//for using dynamic arrays.
#include <map>// includes the map class, which is an associative container that stores elements in key-value pairs
#include <sstream>//for manipulating strings
using namespace std;

// Function to read teams from a CSV file
vector<vector<string>> readTeamsFromFile(const string& filename) {/*In simpler terms, a vector is a flexible
    list that lets you store and manage a collection of items, and it can adjust its size automatically*/
    vector<vector<string>> teams;
    ifstream myfile(filename);/*1.ifstream is part of the <fstream> library and it is used for reading files.
    2.This line of code opens the csv file.*/
    if (myfile.is_open()) { // checks whether the file was successfully opened
        string store;
        while (getline(myfile, store)) { // getline function reads each line of the file and stores it in the variable store.
            stringstream s(store);
            /* stringstream - used here to break down the string into individual components (name, town, stadium).
            This technique is commonly used for parsing delimited data like CSV.
            Reference: Stanley Lippman, *C++ Primer*, 5th Edition, p. 937. */
            vector<string> team(3); // Create a vector to hold team data
            getline(s, team[0], ',');
            getline(s, team[1], ',');
            getline(s, team[2], ',');

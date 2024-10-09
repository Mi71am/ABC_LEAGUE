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
            teams.push_back(team);/* The push_back() function adds the team data to the end of the teams vector.
                          Vectors in C++ are dynamic arrays that can resize themselves automatically.
                        Reference: Bjarne Stroustrup, The C++ Programming Language, 4th Edition, p. 714. */
        }
        myfile.close(); // closes the file once reading is done
    } else {
        cerr << "Could not open the file" << "\n";
    }
    return teams;
}

// Function to group teams by their towns
map<string, vector<string>> groupTeamsByTown(const vector<vector<string>>& teams) {
    /*map - an associative container that stores elements in key value pairs. key is an identifier used to access a specific value
     associative container is a type of data structure that stores elements in a way that allows for fast retrieval based on keys/
    map<string, vector<string>> towns;
    for (const auto& team : teams) {
        towns[team[1]].push_back(team[0]); /* team is the current team object from the loop.
        const auto& declares a reference to each team object in the teams vector. auto means the compiler automatically deduces that
        each element in the teams vector is of type team
        push_back adds the team object to the vector of teams from the same town
        For each team in the vector, add the team to the corresponding town in the map*/
}
return towns;
}
}

// Function to generate match fixtures based on teams
vector<vector<string>> generateFixtures(const vector<vector<string>>& teams) {
    vector<vector<string>> generatedMatches; // This vector will hold all the generated matches
    map<string, vector<string>> towns = groupTeamsByTown(teams);/*This is a data structure that organizes teams based on their local towns
     The function calls the previous function to get the map of teams grouped by town*/
    int weekend = 1;
    string days[2] = { "Saturday", "Sunday" };
    string timeOfDay[2] = { "10:00 AM", "3:00 PM" };
    for (int leg = 1; leg <= 2; ++leg) {
        // This loop runs twice, once for each leg of the tournament; leg 1 is the home game, leg 2 is the away game
        for (const auto& town : towns) {
            // Iterate over each town in the towns map
            const auto& townTeams = town.second; // Get the list of teams from the current town
            for (size_t h = 0; h < townTeams.size(); ++h) {
                // Loop through each team in the current town
                for (size_t a = h + 1; a < townTeams.size(); ++a) {
                    // Compare each team with the teams that come after it in the list
                    generatedMatches.push_back({
                        townTeams[h], // Home team
                        townTeams[a], // Away team
                        to_string(leg), // Convert leg number to string
                        to_string(weekend), // Convert weekend number to string
                        days[weekend % 2], // Alternate between Saturday (index 0) and Sunday (index 1)
                        timeOfDay[(h + a) % 2] // Alternate between 10 AM and 3 PM
                    });
#pragma once
#include <iostream>
#include <string>

using namespace std;

/*The Community Chest class will contain all of the Community Chest cards*/
class Chest{
    public:
        /*Default constructor*/
        Chest();
        /*Non-default constructor*/
        Chest(istream& inFile);
        
        /*Member function used to execute the instructions on the card*/
        void execute (int& space, double& bank, double& other_players, int& other); 
        
    private:
        /*Data members*/
        
        /*Strings, used to display instructions on the card*/
        string s1, s2;
        /*3 variables for possible card directions*/
        int move_to_space; //Moves player to certain space
        double money_bank; //Money to or from bank
        double money_players; //Money to or from other players
        int exception; //For exceptions to basic directions: 1 is get out of jail free, 2 is property repairs
};

#pragma once
#include <iostream>
#include <string>

using namespace std;

/*The Chance class will contain all of the chance cards*/
class Chance{
    public:
        /*Default constructor*/
        Chance();
        /*Non-default constructor*/
        Chance(istream& inFile);
        
        
        /*Member function, used to execute the instructions on the card*/
        void execute (int& space, double& bank, double& other_players, int& other);
        
    private:
        /*Data members*/
        
        /*Strings, used to display instructions on the card*/
        string s1, s2;
        /*3 variables for possible card directions*/
        int move_to_space; //Moves player to certain space
        double money_bank; //Money to or from the bank
        double money_players; //Money to or from other players
        int exception; //For complex instructions; 0 is property repairs, 1 is nearest railroad, 2 is nearest utility, 3 is get out of jail free.
};
        
        

#pragma once
#include <iostream>
#include <string>

using namespace std;

/*!The Community Chest class will contain all of the Community Chest cards*/
class Chest{
    public:
     /**
        *Default constructor
        */
         Chest();
        /**
*A Non default Constructer  takes one arguments 
*Reads chance cards from File chance.txt
*@param inFile file stream
*return void
*/

         Chest(istream& inFile);
        
/**
*A normal member function takes four arguments 
*Member function, used to execute the instructions on the card
*@param space current position on board
*@param bank 
*@param other_players
*@param other 
*return void
*/
        void execute (int& space, double& bank, double& other_players, int& other); 
        
    private:
      /*!Strings, used to display instructions on the card*/
        string s1, s2;
        /*!Moves player to certain space*/
        int move_to_space; 
        /*!Money to or from the bank*/
        double money_bank; 
        /*!Money to or from other players*/
        double money_players; 
        /*!For complex instructions; 0 is property repairs, 1 is nearest railroad, 2 is nearest utility, 3 is get out of jail free.*/
        int exception; 
};

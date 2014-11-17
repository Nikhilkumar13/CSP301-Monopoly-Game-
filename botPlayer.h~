#pragma once
#include <iostream>
#include <string>

using namespace std;
#include "Chest.h"
#include "Chance.h"
#include "Properties.h"
#include "Player.h"

class botPlayer:public Player {
    public:
    //     Default constructor
        botPlayer();
    //     Non-default constructor
        botPlayer(double start_money,string& player_name,bool bot);
        
        /*Getters*/
         bool isBot() const;
         int getrollsum() const;
          bool still_playing () const; //Returns if the player is still playing or not
          bool own_property (const int index) const; //Returns if the player owns a specific property
          string getName () const; //Returns the player's name
          bool getGooJF () const; //Returns if the player owns a GooJF card
          bool getJail () const; // Returns if the player in in jail
          double getMoney () const; // Returns the amount of money in the player's account
         char play()const; //Says Player to Play
        /*Special getters*/
          bool own_monopoly (const int index) const; //Returns if the player owns a monopoly on a certain color
          int RR_owned () const; //Returns the number of railroads owned
          int utilities_owned () const; //Returns the number of utilities owned
          double getAssets (Properties props[]);
        /*Setters*/
          void subMoney (const double change); //Subtracts money from player's account
          void addMoney (const double change); //Adds money to player's account
          void setProperty (const int index, const bool status); //Used for buying and selling properties
         void setGooJF (const bool status); //Used to give or take away GooJF cards
        
        /*Action member functions*/
          void roll (const int index, Properties props[], Chest chest_cards[], Chance chance_cards[], const bool roll_again,
            const bool jackpot, double& jackpot_value, int& doubles, const int num_chest, const int num_chance,
            double& money_other_player, double& money_all_players, int& exception); //Rolls 'dice' and move player
             void buy (Properties props[]); //Buy or sell houses/hotels
          void stats (Properties props[]); //Display the player's stats
          void trade (Properties props[]); //Prints out stats relevant to trading
          void mortgage(Properties props[]); //Mortgages properties
        
        /*Debt member function*/
          void debt (Properties props[]); //Determines if the player has enough money to pay off a debt
        
        // /*Friend operators*/
        // friend istream& operator>> (istream& is, Player& p);
        // friend ostream& operator<< (ostream& os, Player& p);
      };
    
    


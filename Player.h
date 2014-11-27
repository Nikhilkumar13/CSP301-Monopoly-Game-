#pragma once
#include <iostream>
#include <string>

using namespace std;
#include "Chest.h"
#include "Chance.h"
#include "Properties.h"

class Player{
    public:
        /*Default constructor*/
        Player();
        /*Non-default constructor*/
        Player(double start_money, string& player_name,bool bot);
        
        /*Getters*/
        virtual bool isBot() const;
        virtual  void getrolls(int &a,int &b);
        virtual bool still_playing () const; //Returns if the player is still playing or not
       virtual  bool own_property (const int index) const; //Returns if the player owns a specific property
       virtual  string getName () const; //Returns the player's name
       virtual  bool getGooJF () const; //Returns if the player owns a GooJF card
       virtual  bool getJail () const; // Returns if the player in in jail
       virtual  double getMoney () const; // Returns the amount of money in the player's account
       virtual char play()const; //Says Player to Play
        /*Special getters*/
       virtual  bool own_monopoly (const int index) const; //Returns if the player owns a monopoly on a certain color
       virtual  int RR_owned () const; //Returns the number of railroads owned
       virtual  int utilities_owned () const; //Returns the number of utilities owned
        virtual double getAssets (Properties props[]);
        /*Setters*/
        virtual void subMoney (const double change); //Subtracts money from player's account
       virtual  void addMoney (const double change); //Adds money to player's account
       virtual  void setProperty (const int index, const bool status); //Used for buying and selling properties
       virtual  void setGooJF (const bool status); //Used to give or take away GooJF cards
        
        virtual void roll (const int index, Properties props[], Chest chest_cards[], Chance chance_cards[], const bool roll_again,
            const bool jackpot, double& jackpot_value, int& doubles, const int num_chest, const int num_chance,
            double& money_other_player, double& money_all_players, int& exception); //Rolls 'dice' and move player
        virtual void buy (Properties props[]); //Buy or sell houses/hotels
       virtual  void stats (Properties props[]); //Display the player's stats
        virtual void trade (Properties props[]); //Prints out stats relevant to trading
        virtual void mortgage(Properties props[]); //Mortgages properties
        
        /*Debt member function*/
        virtual void debt (Properties props[]); //Determines if the player has enough money to pay off a debt
        
        /*Friend operators*/
        // friend istream& operator>> (istream& is, Player& p);
        // friend ostream& operator<< (ostream& os, Player& p);
    
    protected:
        /*Data members*/
        string name; //Player's name
        int space; //The square the player is on
        double money; //Amount of money the player owns
        bool properties_owned [40]; //If the player owns a specific property or not
        bool is_playing; //If the player is still playing or not
        bool jail; //If the player is in jail
        bool GooJF; //Get out of Jail Free card
        bool Bot;
        int rolla;
        int rollb;
};


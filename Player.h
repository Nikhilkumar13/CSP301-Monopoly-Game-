#pragma once
#include <iostream>
#include <string>

using namespace std;
#include "Chest.h"
#include "Chance.h"
#include "Properties.h"


/*! Abstract Bot Player representing  Player */

class Player{
    public:
/**
* A default Constructer 
* @return NULL
*/      
       Player();
/**
* A Non default Constructer  takes three arguments 
* using callBy refrence to pass the value of dice1 and dice2.
* @param start_money an double argument.
* @param player_name an string argument.
*@param bot boolean value whether bot or human player
* @return NULL
*/       
        Player(double start_money, string& player_name,bool bot);
 /**
* A normal member taking zero arguments 
* tells whether a player is bot or human
* @return NULL
*/
        virtual bool isBot() const;

  /**
* a normal member taking two arguments 
* using callBy refrence to pass the value of dice1 and dice2.
* @param a an integer argument.
* @param b an integer argument.
* @return NULL
*/
        virtual  void getrolls(int &a,int &b);
/**
* A normal member  taking zero argument
* tells  whether player is playing or out of game
* @return bool
*/

       virtual bool still_playing () const; 
/**
* A normal member taking two one argument index of property
*if the player owns a specific property
* @param index an integer argument.
* @return  bool
*/
       virtual  bool own_property (const int index) const; 
/**
* A normal member function with no arguments 
* name of player
* @return bool
*/
       virtual  string getName () const; 
/**
* A normal member taking two arguments 
* if the player owns a GooJF card
* @return bool
*/
       virtual  bool getGooJF () const; 
/**
* A normal member taking no arguments 
* Tells if the Player is in Jail
* @return bool
*/
       virtual  bool getJail () const; 
/**
* A normal member taking No arguments  
* returns the amount of money in the player's account
* @return double
*/
       virtual  double getMoney () const; 
/**
* A normal member taking No arguments 
*Ask User to take a action such as roll dice etc. 
* @return char
*/
      virtual char play()const; 
/**
* A normal member taking zero arguments
*  Tells if the player owns a monopoly on a certain color
* @param index a constant integer.
* @return bool
*/
      virtual  bool own_monopoly (const int index) const; 
  /**
* A normal member taking zero arguments 
* Returns the number of railroads owned
* @return Intger
*/
      virtual  int RR_owned () const; 
  /**
* A normal member taking zero arguments 
* Returns the number of utilities owned
* @return Intger
*/
      virtual  int utilities_owned () const; 
        /**
* A normal member taking one arguments
* tells total worth assests
* @param props takes in Property array.
* @return doubles
*/
      virtual double getAssets (Properties props[]);
        /**
* A normal member taking one arguments.
*Subtracts money from player's account
* @param change takes in amount to change
* @return void
*/
      virtual void subMoney (const double change); 
      /**
* A normal member taking one arguments.
* Adds money to player's account
* @param change takes in a property type array
* @return void
*/
      virtual  void addMoney (const double change); 
       /**
* A normal member taking two arguments.
* Used for buying and selling properties
* @param index takes in a property number array
* @param status takes in a status of property
* @return void
*/
      virtual  void setProperty (const int index, const bool status); 
     
     /**
* A normal member taking one arguments.
* Used to give or take away GooJF cards
* @param status of GooJF card whether own or not
* @return bool
*/ 
       virtual  void setGooJF (const bool status); 
       /**
* A most important member taking 10 arguments.
* @return void 
*/ 
      virtual void roll (const int index, Properties props[], Chest chest_cards[], Chance chance_cards[], const bool roll_again,const bool jackpot, double& jackpot_value, int& doubles, const int num_chest, const int num_chance,double& money_other_player, double& money_all_players, int& exception); //Rolls 'dice' and move player
     /**
* A normal member taking one arguments.
* Buy or sell houses/hotels
* @param props takes in a property type array
* @return void
*/   
      virtual void buy (Properties props[]); 
      /**
* A normal member taking one arguments.
* Display the player's stats
* @param props takes in a property type array
* @return void
*/ 
      virtual  void stats (Properties props[]); 
     /**
* A normal member taking one arguments.
* Prints out stats relevant to trading
* @param props takes in a property type array
* @return void
*/ 
      virtual void trade (Properties props[]); 
     
     /**
* A normal member taking one arguments.
*Mortgages properties
* @param props takes in a property type array
* @return void
*/ 
      virtual void mortgage(Properties props[]); 
   /**
* A normal member taking one arguments.
* Determines if the player has enough money to pay off a debt
* @param props takes in a property type array
* @return void
*/
      virtual void debt (Properties props[]); 
    
    protected:
      /*! Name of player */
        string name; 
      /*! Name of space */
        int space; //The square the player is on
        /*! Amount of money  the player owns*/
        double money;
        /*!If the player owns a specific property or not*/
        bool properties_owned [40]; 
        /*!If the player is still playing or not*/
        bool is_playing; 
        /*!If the player is in jail*/
        bool jail; 
        /*!Get out of Jail Free card*/
        bool GooJF; 
        /*!Bot or human*/
        bool Bot;
        /*!roll on dice a*/
        int rolla;
         /*!roll on dice b*/
        int rollb;
};


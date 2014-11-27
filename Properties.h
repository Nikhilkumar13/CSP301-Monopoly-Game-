#pragma once
#include <iostream>
#include <string>

using namespace std;

class Properties{
    public:
        /*Default constructor*/
        Properties();
        /*Non-default constructor*/
        Properties(istream& inFile);
        
        /**
        *Will return the purchase price of the property
        */
        double getPrice () const; 
        /**
        *Returns the mortgage price of the property
        */
        double getMortgage () const; 
        /**
        *Returns the house cost
        */
        double getH_cost () const; 
        /**
        *Returns the number of houses on the property
        */
        int getHouses () const; 
        /**
        *Returns the space number
        */
        int getSpace () const; 
        /**
        *Returns the id of the property
        */
        int getID () const; 
        /**
        *Prints out the color of the property
        */
        string getID_Color () const; 
        /**
        *Will print the name out to the screen
        */
        string getName () const; 
        /**
        *Return if the property is mortgaged
        */
        bool getMortgaged () const; 
        /**
        *Returns if the property is owned
        */
        bool getOwned () const; 
        /**
        *Mortgages/unmortgages the proeprty
        */
        void setMortgaged (const bool status); 
        /**
        *Add or remove houses
        */
        void setHouses (const int new_houses); 

        /**
        *Sets owned and mortgage to false, sets houses to 0
        */
        void setOwned (const bool status); 
        /**
        *Member function that restores a property to default settings when a player goes bankrupt
        */
        void return_default (); //
        /**
        *Member function for how much opposing player must pay
        */
        
        
        double payment () const; 
        /**
        *Returns railroad payment.
        */
        double RRpayment (const int h) const; 
        
    private:
        /*!Property name*/
        string name; 
        /*!Price, mortgage price, and cost of 0-4 houses & hotel*/
        double price, mortgage, h0, h1, h2, h3, h4, hotel, h_cost; 
        /*!*/
        int id;
        /*!the space number (Go = 1, Boardwalk = 40)*/
        int space;
        /*!Category (color), , number of houses on property (5 = hotel)*/
        int houses; 
        /*!Determines if property is mortgaged or not*/
        bool mortgaged; 
        /*!The player number that owns the property (not the element offset)*/
        bool owned; 
};

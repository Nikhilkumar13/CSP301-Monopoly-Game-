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
        
        /*Getters*/
        double getPrice () const; //Will return the purchase price of the property
        double getMortgage () const; //Returns the mortgage price of the property
        double getH_cost () const; //Returns the house cost
        int getHouses () const; //Returns the number of houses on the property
        int getSpace () const; //Returns the space number
        int getID () const; //Returns the id of the property
        string getID_Color () const; //Prints out the color of the property
        string getName () const; //Will print the name out to the screen
        bool getMortgaged () const; //Return if the property is mortgaged
        bool getOwned () const; //Returns if the property is owned
        /*Setters*/
        void setMortgaged (const bool status); //Mortgages/unmortgages the proeprty
        void setHouses (const int new_houses); //Add or remove houses
        void setOwned (const bool status); //Purchase or unpurchase property
        
        /*Special setter for when player is bankrupt*/
        void return_default (); //Sets owned and mortgage to false, sets houses to 0
        
        /*Member function for how much opposing player must pay*/
        double payment () const; //Returns how much the other player must pay
        double RRpayment (const int h) const; //Returns railroad payment.
   
        /*Friend operators*/     
        friend istream& operator>> (istream& is, Properties& p);
        friend ostream& operator<< (ostream& os, Properties& p);
        
    private:
        /*Data members*/
        string name; //Property name
        double price, mortgage, h0, h1, h2, h3, h4, hotel, h_cost; //Price, mortgage price, and cost of 0-4 houses & hotel
        int id, space, houses; //Category (color), the space number (Go = 1, Boardwalk = 40), number of houses on property (5 = hotel)
        bool mortgaged; //Determines if property is mortgaged or not
        bool owned; //The player number that owns the property (not the element offset)
};

istream& operator>> (istream& is, Properties& p);
ostream& operator<< (ostream& os, Properties& p);

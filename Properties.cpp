#include <iostream>
#include <string>

using namespace std;

#include "Properties.h"

/*Default constructor, not permanantly used*/
Properties::Properties(){
}
/*Non-default constructor, read in data from external source and assigns values to the data members*/
Properties::Properties(istream& inFile){
    string textIO; //Temporary variable to hold strings
    getline(inFile, textIO);
    if(!(inFile)){
        cout<<"Error reading property data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    name = textIO;
    inFile>>space;
    if(!(inFile)){
        cout<<"Error reading property data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    /*Read in no additional data for non-general property spaces*/
    if(space == 1 || space == 3 || space == 5 || space == 8 || space == 11 || space == 18 || space == 21 || space == 23 || space == 31 || space == 34 || space == 37 || space == 39){
            id=price=mortgage=h0=h1=h2=h3=h4=hotel=h_cost=houses=0; //Set unused data members = 0
            mortgaged = false;
            owned = true;
    }
    /*Read in special data for railroads*/
    else if(space == 6 || space == 16 || space == 26 || space == 36){
        inFile>>id>>price>>mortgage>>h1>>h2>>h3>>h4; //In this case, h1-h4 will be used for how many other railroads are owned
            h0=hotel=h_cost=houses=0; //Set unused data members = 0
            mortgaged = false;
            owned = false;
        if(!(inFile)){
            cout<<"Error reading property data."<<endl<<endl;
//            system("PAUSE");
//            exit(1);
        }
    }
    /*Read in special data for utilities*/
    else if (space == 13 || space == 29){
        inFile>>id>>price>>mortgage;
        if(!(inFile)){
            cout<<"Error reading property data."<<endl<<endl;
//            system("PAUSE");
//            exit(1);
        }
        h0=h1=h2=h3=h4=hotel=h_cost=houses=0; //Set unused data members = 0
        mortgaged = false;
        owned = false;
    }
    /*Read in all other properties (general properties) normally*/
    else{
        inFile>>id>>price>>mortgage>>h0>>h1>>h2>>h3>>h4>>hotel>>h_cost;
        if(!(inFile)){
            cout<<"Error reading property data."<<endl<<endl;
//            system("PAUSE");
//            exit(1);
        }
        houses = 0; //Starts with no houses
        mortgaged = false;
        owned = false;
    }
    /*The following cout statement can be used by the programmer to ensure data has been input correctly*/
    //cout<<name<<endl<<space<<" "<<id<<" "<<price<<" "<<mortgage<<" "<<h0<<" "<<h1<<" "<<h2<<" "<<h3<<" "<<h4<<" "<<hotel<<" "<<h_cost<<" "<<houses<<" "<<mortgaged<<endl;
}

/*Getters*/
double Properties::getPrice () const{ //Returns the price of the property
    return (price);
}
double Properties::getMortgage () const{ //Returns the mortgage cost of the property
    return (mortgage);
}
double Properties::getH_cost () const{ //Returns the house/hotel cost of the property
    return (h_cost);
}
int Properties::getHouses () const{ //Returns the number of houses on the property
    return (houses);
}
int Properties::getID () const{ //Returns the ID number of the property
    return (id);
}
int Properties::getSpace () const{ //Returns the space number of the property
    return (space);
}
/*Special getter function, prints the property color to the screen*/
string Properties::getID_Color () const{
    if (id == 1){
        return "indigo";
    }
    else if (id == 2){
        return "cyan";
    }
    else if (id == 3){
        return "pink";
    }
    else if (id == 4){
        return "orange";
    }
    else if (id == 5){
        return "red";
    }
    else if (id == 6){
        return "yellow";
    }
    else if (id == 7){
        return "green";
    }
    else if (id == 8){
        return "blue";
    }
    else if (id == 9){
        return "railroad";
    }
    else if (id == 10){
        return "utility";
    }
}
/*Prints out the property's name to the screen*/
string Properties::getName () const{
    return (name);
}
/*Returns if the property is mortgaged*/
bool Properties::getMortgaged () const{
    return (mortgaged);
}
/*Returns if the property is owned*/
bool Properties::getOwned () const{
    return (owned);
}
/*Member function for how much the opposing player owes*/
double Properties::payment () const{
    if(houses == 0){
        return (h0);
    }
    else if (houses == 1){
        return (h1);
    }
    else if (houses == 2){
        return (h2);
    }
    else if (houses == 3){
        return (h3);
    }
    else if (houses == 4){
        return (h4);
    }
    else if (houses == 5){
        return (hotel);
    }
}
/*Member function for how much a player must pay for landing on a RR*/
double Properties::RRpayment (const int h) const{
    if (h == 1){
        return (h1);
    }
    else if (h == 2){
        return (h2);
    }
    else if (h == 3){
        return (h3);
    }
    else if (h == 4){
        return (h4);
    }
}
    
/*Member function that mortgages or unmortgages a property*/
void Properties::setMortgaged (const bool status){
    mortgaged = status;
}
/*Member function that sets ownership status of a property*/
void Properties::setOwned (const bool status){
    owned = status;
}
/*Member function that adds or removes houses*/
void Properties::setHouses (const int new_houses){
    houses += new_houses;
}

/*Member function that restores a property to default settings when a player goes bankrupt*/
void Properties::return_default (){
    owned = false;
    mortgaged = false;
    houses = 0;
}

/*Friend operators*/     
istream& operator>> (istream& is, Properties& p){ //Used to read in data from the save file
    int in_houses;
    bool in_mortgaged, in_owned;
    if(is>>in_houses>>in_mortgaged>>in_owned){ //If the data is read in
        p.houses = in_houses;
        p.mortgaged = in_mortgaged;
        p.owned = in_owned;
    }
    else{ //If there is an error
        cout<<"Error reading property data from the save file."<<endl;
//        system("PAUSE");
//        exit(1);
    }
    return (is);
}
ostream& operator<< (ostream& os, Properties& p){ //Used to write data to the save file
    os << p.houses << " " << p.mortgaged << " " << p.owned << endl;
    return (os);
}

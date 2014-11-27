#include <iostream>
#include <string>

using namespace std;

#include "Chance.h"
#include "Player.h"

/*Default constructor, assigns no values to data members*/
Chance::Chance(){
}
/*Non-default constructor, reads data from outside source and assigns the values to the data members*/
Chance::Chance(istream& inFile){
    string textIO; //Temporary string to hold getlines
    getline(inFile, textIO);
    if (!(inFile)){ //Check for errors each time
        cout<<"Error reading chance data."<<endl<<endl;
    }
    s1 = textIO;
    getline(inFile, textIO);
    if (!(inFile)){ //Check for error
        cout<<"Error reading chance data."<<endl<<endl;

    }
    s2 = textIO;
    inFile>>move_to_space;
    if (!(inFile)){ //Check for error
        cout<<"Error reading chance data."<<endl<<endl;
    }
    inFile>>money_bank;
    if (!(inFile)){ //Check for error
        cout<<"Error reading chance data."<<endl<<endl;

    }
    inFile>>money_players;
    if (!(inFile)){ 
        cout<<"Error reading chance data."<<endl<<endl;

    }
    inFile>>exception;
    if (!(inFile)){ 
        cout<<"Error reading chance data."<<endl<<endl;

    }
    /*The following can be used by the programmer to have the program read out all data, to ensure correct data input*/
    // cout<<"========================================="<<endl;
    // cout<<s1<<endl<<s2<<endl<<move_to_space<<"\t"<<money_bank<<"\t"<<money_players<<"\t"<<exception<<endl;
     // cout<<"========================================="<<endl;

}

void Chance::execute (int& space, double& bank, double& other_players, int& other){
    cout<<s1<<endl<<s2<<endl;
    if (move_to_space > 0){ //If the card moves the player
        space = move_to_space;
    }
    else if (money_bank > 0){ //If the card moves money to/from the bank
        bank = money_bank;
    }
    else if (money_players > 0){ //If the card moves money to/from other players
        other_players = money_players;
    }
    else{ //If the card has more complicated directions on it, return the exception code
        other = exception;
    }
}

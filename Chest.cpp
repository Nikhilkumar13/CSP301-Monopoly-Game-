#include <iostream>
#include <string>

using namespace std;

#include "Chest.h"

/*Default constructor, assigns no values to data members*/
Chest::Chest(){
}
/*Non-default constructor, reads data from outside source and assigns the values to the data members*/
Chest::Chest(istream& inFile){
    string textIO; //Temporary string to hold getlines
    getline(inFile, textIO);
    if (!(inFile)){ //Check for errors each time
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    s1 = textIO;
    getline(inFile, textIO);
    if (!(inFile)){ //Check for error
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    s2 = textIO;
    inFile>>move_to_space;
    if (!(inFile)){ //Check for error
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    inFile>>money_bank;
    if (!(inFile)){ //Check for error
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    inFile>>money_players;
    if (!(inFile)){ //Check for error
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    inFile>>exception;
    if (!(inFile)){ //Check for error
        cout<<"Error reading community chest data."<<endl<<endl;
//        system("PAUSE");
//        exit(1);
    }
    /*The following can be used by the programmer to have the program read out all data, to ensure correct data input*/
    
    //cout<<s1<<endl<<s2<<endl<<move_to_space<<"\t"<<money_bank<<"\t"<<money_players<<"\t"<<exception<<endl;
}

/*The card execution member function*/
void Chest::execute (int& space, double& bank, double& other_players, int& other){
    cout<<s1<<endl<<s2<<endl; //Print out the card's contents
    if (move_to_space > 0){ //If the card moves the player
        space = move_to_space;
    }
    else if (money_bank > 0){ //If the card moves money to/from the bank
        bank = money_bank;
    }
    else if (money_players > 0){ //If the card moves money to/from other players
        other_players = money_players;
    }
    else{ //If the card contains more complicated instructions, return the exception code
        other = exception;
    } 
}

#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

#include "Player.h"
#include "Chest.h"
#include "Chance.h"
#include "Properties.h"

/*Default constructor, not permanantly used*/
Player::Player(){
}
/*Non-default constructor, read data from external source and assigns values to the data members*/
Player::Player(double start_money, string& player_name,bool bot ){
    money = start_money;
    space = 1;
    for (int i (0); i < 40; i++){
        properties_owned[i] = false;
    }
    name = player_name;
    is_playing = true;
    jail = false;
    GooJF = false;
    Bot=bot;
}
  bool Player::isBot() const
{
    return Bot;
}
  char Player::play() const
{
     char  choice;
     cout<<name<<", what would you like to do?"<<endl;
     cout<<"(R)oll"<<"\t\t"<<"(S)tats"<<endl;
     cout<<"(B)uy/sell"<<"\t"<<"(T)rade"<<endl;
     cout<<"(M)ortgage"<<endl;
     cin>>choice;
     return choice;
}
/*Member function for if the player is still playing*/
  bool Player::still_playing() const{
    return (is_playing);
}
/*Member function for if the player owns the indicated space*/
  bool Player::own_property(const int index) const{
    return (properties_owned[index]);
}
/*Member function that returns the player's name*/
  string Player::getName () const{
    return (name);
}
/*Member function that returns if the player owns a GooJF card*/
  bool Player::getGooJF () const{
    return (GooJF);
}
/*Member function that returns if the player is in jail*/
  bool Player::getJail () const{
    return (jail);
}
/*Member function that returns the amount of money in the player's account*/
  double Player::getMoney () const{
    return (money);
}
/*Member function for if the player owns an entire monopoly*/
  bool Player::own_monopoly(const int index) const{
    if (index == 1){
        return (properties_owned[1] && properties_owned[3]);
    }
    else if (index == 2){
        return (properties_owned[6] && properties_owned[8] && properties_owned[9]);
    }
    else if (index == 3){
        return (properties_owned[11] && properties_owned[13] && properties_owned[14]);
    }
    else if (index == 4){
        return (properties_owned[16] && properties_owned[18] && properties_owned[19]);
    }
    else if (index == 5){
        return (properties_owned[21] && properties_owned[23] && properties_owned[24]);
    }
    else if (index == 6){
        return (properties_owned[26] && properties_owned[27] && properties_owned[29]);
    }
    else if (index == 7){
        return (properties_owned[31] && properties_owned[32] && properties_owned[34]);
    }
    else if (index == 8){
        return (properties_owned[37] && properties_owned[39]);
    }
}
/*Member function that returns the number of railroads the player owns*/
  int Player::RR_owned () const{
    int counter (0);
    for (int i (5); i <= 35; i += 10){ //RR spaces are 6, 16, 26, and 36
        if (properties_owned[i]){
            counter++;
        }
    }
    return (counter);
}
/*Member function that returns the number of utilities the player owns*/
  int Player::utilities_owned () const{
    int counter (0);
    if (properties_owned[12]){
        counter++;
    }
    if (properties_owned[28]){
        counter++;
    }
    return (counter);
}
/*Member function that returns the player's assets*/
  double Player::getAssets(Properties props[]){
    double assets(money);
    for (int n (0); n < 40; n++){ //Calculate the player's assets
        if (properties_owned[n]){
            if(props[n].getMortgaged()){ //If mortgaged, add the mortgage price
                assets += props[n].getMortgage();
            }
            else{
                assets += props[n].getPrice(); //Otherwise, add the property price
            }
            if (props[n].getHouses() > 0){
                assets += props[n].getHouses() * props[n].getH_cost(); //Add the house price for each house on the property
            }
        }
    }
    return (assets);
}
/*Member function that subtracts money from the player's account*/
  void  Player::subMoney (const double change){
    money -= change;
}
/*Member function that adds money to the player's account*/
  void Player::addMoney (const double change){
    money += change;
}
/*Member function for returning  the rollsum of player*/
int Player::getrollsum() const
{
    return rollsum;
}
/*Member function for buying and selling properties*/
  void Player::setProperty (const int index, const bool status){
    properties_owned[index] = status;
}
/*Member function to give or take away GooJF cards*/
  void Player::setGooJF (const bool status){
    GooJF = status;
}

/*Roll member function, moves the character*/
  void Player::roll (const int index, Properties props[], Chest chest_cards[], Chance chance_cards[], const bool roll_again, const bool jackpot,
    double& jackpot_value, int& doubles, const int num_chest, const int num_chance, double& money_other_player,
    double& money_all_players, int& exception){
    cout<<endl;
    if (jail){ //If the player is in jail
        doubles = 0;
        char response; //Variable for the player input
        cout<<"You are in Jail. What would you like to do?"<<endl;
        cout<<"(R)oll"<<"\t"<<"(P)ay"<<"\t"<<"(G)et out of Jail Free card"<<endl;
        while (true){
            cin>>response;
            if (response == 'P' || response == 'p'){ //If they choose to pay $50 to get out of Jail
                if (money - 50 >= 0){
                    money -= 50;
                    jail = false;
                    cout<<"You paid $50 to get out of jail."<<endl;
                    cout<<"You now get to roll!"<<endl;
                    system("PAUSE");
                    break;
                }
                else{
                    cout<<"You do not have $50!"<<endl;
                }
            }
            else if (response == 'G' || response == 'g'){ //If they choose to use a GooJF card
                if (GooJF){
                    GooJF = false;
                    jail = false;
                    cout<<"You used your Get out of Jail Free card and were released from jail."<<endl;
                    cout<<"You now get to roll!"<<endl;
                    system("PAUSE");
                    break;
                }
                else{
                    cout<<"You don't have a Get out of Jail Free card!"<<endl;
                }
            }
            else if (response == 'R' || response == 'r'){ //If they choose to roll to get out of Jail
                int die1 ( (rand()%6)+1 );
                int die2 ( (rand()%6)+1 );
                cout<<"You rolled a "<<die1<<" and a "<<die2<<"."<<endl;
                if (die1 == die2){ //If they roll doubles, they are released
                    jail = false;
                    cout<<"You rolled doubles and were released from jail."<<endl;
                    cout<<"You now get to roll!"<<endl;
                    system("PAUSE");
                    break;
                }
                else{
                    cout<<"You did not roll doubles, and are still in jail."<<endl;
                    return;
                }
            }
            else{
                cout<<"Please enter a valid letter input."<<endl;
            }
        }
        cout<<endl;
    }
    int die1 ( (rand()%6)+1 ); //Roll 2 6-sided dice
    int die2 ( (rand()%6)+1 );
    cout<<"You rolled a "<<die1<<" and a "<<die2<<"."<<endl;
    if (die1 == die2){ //Print out if the player rolled doubles
        cout<<"You rolled doubles!"<<endl;
    }
    rollsum=die1+die2;
    space += (die1 + die2);
    while(space > 40){ //If they pass go, add $200 and subtract 40 from their space number
        space -= 40;
        cout<<"You passed Go! Collect $200!"<<endl;
        money += 200;
    }
    cout<<"You landed on "<<props[space-1].getName()<<"."<<endl; //Print out the name of the space they landed on
        
    
    /*Declare variables for use inside of switch statement*/
    /*Income tax*/
    double assets (money); //Total assets of this player
    /*Chance / Community Chest*/
    int chest_card_num (rand() % num_chest); //Chooses a random card
    int chance_card_num (rand() % num_chance); //Chooses a random card
    int new_space (0); //Holds a new space for the player to go to
    double money_bank (0), money_players (0); //Money that goes either to the bank or to other players
    
    /*Execute results based on what space the player lands on*/
    
    switch (space){
        case 0 : //Go
            break;
        case 5 : //Income tax
            for (int n (0); n < 40; n++){ //Calculate the player's assets
                if (properties_owned[n]){
                    if(props[n].getMortgaged()){
                        assets += props[n].getMortgage();
                    }
                    else{
                        assets += props[n].getPrice();
                    }
                    if (props[n].getHouses() > 0){
                        assets += props[n].getHouses() * props[n].getH_cost();
                    }
                }
            }
            /*Determine if 10% of total assets is more or less than $200*/
            assets /= 10;
            if (assets < 200){
                money -= (int) assets;
                jackpot_value += (int) assets; //Add tax to the jackpot
                cout<<"You paid 10% of your current assets, which came out to "<<(int) assets<<"."<<endl;
            }
            else{
                money -= 200;
                jackpot_value += 200; //Add tax to the jackpot
                cout<<"You paid $200."<<endl;
            }
            break;
            
        case 11 : //Jail
            cout<<"Just visiting!"<<endl;
            break;
            
        case 21 : //Free parking
            if (jackpot){ //If there is a jackpot, print out the worth and add it to the player's bank
                cout<<"You won the jackpot, which was worth $"<<jackpot_value<<"!"<<endl;
                money += jackpot_value;
                jackpot_value = 0;
            }
            else{ //If not, print out a relaxing message
                cout<<"Ahh, how relaxing!"<<endl;
            }
            break;
            
        case 31 : //Go to Jail
            jail = true;
            space = 11; //Send the player to jail
            cout<<"You have been sent to Jail!"<<endl;
            break;
            
        case 39 : //Luxury Tax
            money -= 75;
            jackpot_value += 75; //Add tax to the jackpot
            cout<<"You paid $75."<<endl;
            debt(props);
            break;
        case 3 :
        case 18: //Community Chest, fall through to last implementation
        case 34:
            cout<<"You recieved the following Community Chest card:"<<endl<<endl;
            chest_cards[chest_card_num].execute (new_space, money_bank, money_players, exception);
            
            if (new_space > 0){ //If the player moved
                if (new_space == 11){
                    space = new_space; //If the player was sent to jail
                    jail = true;
                    break;
                }
                if (new_space < space){
                    money += 200; //Collect 200 for passing go
                }
                space = new_space; //Move the player to the new space
                if (!(props[space - 1].getOwned () ) ){ //If the property is not owned, allow them to purchase it
                    char response;
                    cout<<"This property is unowned."<<endl;
                    if (money - props[space-1].getPrice() > 0){ //Make sure they have enough money
                        cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                        while (true){
                            cin>>response;
                            if (response == 'Y' || response == 'y'){ //If they say yes, purchase the property
                                money -= props[space-1].getPrice();
                                props[space-1].setOwned (true);
                                properties_owned[space-1] = true;
                                cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                                break;
                            }
                            else if (response == 'N' || response == 'n'){ //Otherwise, do not purchase the property
                                cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                                break;
                            }
                            else{
                                cout<<"Please enter a valid input."<<endl;
                            }
                        }
                    }
                    else{ //If they do not have enough money, print out this message
                        cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                    }
                }
                else{ //If the property is owned, pass in the space number as an exception
                    exception = space-1;
                }
            }
            
            else if (money_bank != 0){ //If the money to the bank is not 0, perform that direction
                money += money_bank;
                debt(props);
            }
            else if (money_players != 0){ //If money to other players is not 0, pass that back to the main function
                money_all_players = money_players;
            }
            else{
                switch (exception){ //Exceptions are used for complicated directions
                    case 1 : //GooJF card
                        GooJF = true;
                        cout<<"You now have a Get out of Jail Free card!"<<endl;
                        break;
                    case 2 : //General repairs
                        for (int n(0); n < 25; n++){
                            if (props[n].getHouses() == 5){
                                money_bank += 100;
                            }
                            else if (props[n].getHouses() > 0){
                                money_bank += 25 * props[n].getHouses();
                            }
                        }
                        money -= money_bank;
                        cout<<"You paid $"<<money_bank<<" for general repairs."<<endl;
                        debt(props);
                        break;                    
                }
                exception = 0; //Set the exception back to 0
            }
            break;            
        case 8 :
        case 23: //Chance, fall through to the last implementation
        case 37:
            cout<<"You recieved the following Chance card:"<<endl<<endl;
            chance_cards[chance_card_num].execute (new_space, money_bank, money_players, exception);
            cout<<endl;
            if (new_space > 0){ //If the player moved
                if (new_space == 11){
                    space = new_space; //If they go to jail
                    jail = true;
                    break;
                }
                if (new_space < space){
                    money += 200; //Collect 200 for passing go
                }
                space = new_space;
                if (!(props[space - 1].getOwned () ) ){ //If the property is not owned
                    char response;
                    cout<<"This property is unowned."<<endl;
                    if (money - props[space-1].getPrice() > 0){
                        cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                        while (true){
                            cin>>response;
                            if (response == 'Y' || response == 'y'){ //The player chooses to purchase the property
                                money -= props[space-1].getPrice();
                                props[space-1].setOwned (true);
                                properties_owned[space-1] = true;
                                cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                                break;
                            }
                            else if (response == 'N' || response == 'n'){ //The player does not want to purchase the property
                                cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                                break;
                            }
                            else{
                                cout<<"Please enter a valid input."<<endl;
                            }
                        }
                    }
                    else{ //The player does not have enough money to purchase the property
                        cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                    }
                }
                else{ //If the propery is owned, set the exception to the property number
                    exception = space-1;
                }
            }
            
            else if (money_bank != 0){ //If money to the bank is not 0
                money += money_bank;
                debt(props);
                break;
            }
            else if (money_players != 0){ //If money to other players is not 0, pass that number back to the main function
                money_all_players = money_players;
                break;
            }
            else{
                switch (exception){ //Used for complicated directions
                    case 0 : //Street Repairs
                        for (int n(0); n < 40; n++){
                            if (props[n].getHouses() == 5){
                                money_bank += 115;
                            }
                            else if (props[n].getHouses() > 0){
                                money_bank += 40 * props[n].getHouses();
                            }
                        }
                        money -= money_bank;
                        cout<<"You paid $"<<money_bank<<" in street repairs."<<endl;
                        debt(props);
                        break;
                        
                    case 1 : //Nearest RR
                        if (space >= 6 && space < 16){
                            space = 16;
                        }
                        else if (space >= 16 && space < 26){
                            space = 26;
                        }
                        else if (space >= 26 && space < 36){
                            space = 36;
                        }
                        else{
                            space = 6;
                        }
                        if (!(props[space - 1].getOwned () ) ){ //If the property is unowned, allow the player to purchase it
                            char response;
                            cout<<"This property is unowned."<<endl;
                            if (money - props[space-1].getPrice() > 0){
                                cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                                while (true){
                                    cin>>response;
                                    if (response == 'Y' || response == 'y'){
                                        money -= props[space-1].getPrice();
                                        props[space-1].setOwned (true);
                                        properties_owned[space-1] = true;
                                        cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                                        break;
                                    }
                                    else if (response == 'N' || response == 'n'){
                                        cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                                        break;
                                    }
                                    else{
                                        cout<<"Please enter a valid input."<<endl;
                                    }
                                }
                            }
                            else{
                                cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                            }
                        }
                        exception = space-1;
                        break;
                    case 2 : //Nearest utility
                        if (space >= 13 && space < 29){
                            space = 29;
                        }
                        else{
                            space = 13;
                        }
                        if (!(props[space - 1].getOwned () ) ){ //If the property is unowned, allow the player to purchase it
                            char response;
                            cout<<"This property is unowned."<<endl;
                            if (money - props[space-1].getPrice() > 0){
                                cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                                while (true){
                                    cin>>response;
                                    if (response == 'Y' || response == 'y'){
                                        money -= props[space-1].getPrice();
                                        props[space-1].setOwned (true);
                                        properties_owned[space-1] = true;
                                        cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                                        break;
                                    }
                                    else if (response == 'N' || response == 'n'){
                                        cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                                        break;
                                    }
                                    else{
                                        cout<<"Please enter a valid input."<<endl;
                                    }
                                }
                            }
                            else{
                                cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                            }
                        }
                        exception = space-1;
                        break;
                    case 3 : //GooJF card
                        GooJF = true;
                        exception = 0;
                        cout<<"You now have a Get out of Jail Free card!"<<endl;
                        break;
                }
            }
            break;
            
        case 6 :
        case 16:
        case 26: //Railroads, fall through to final implementation
        case 36:
            if (!(props[space - 1].getOwned () ) ){ //If the property is unowned, allow the player to purchase it
                char response;
                cout<<"This property is unowned."<<endl;
                if (money - props[space-1].getPrice() > 0){
                    cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                    while (true){
                        cin>>response;
                        if (response == 'Y' || response == 'y'){
                            money -= props[space-1].getPrice();
                            props[space-1].setOwned (true);
                            properties_owned[space-1] = true;
                            cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                            break;
                        }
                        else if (response == 'N' || response == 'n'){
                            cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                            break;
                        }
                        else{
                            cout<<"Please enter a valid input."<<endl;
                        }
                    }
                }
                else{
                    cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                }
            }
            else{
                exception = space-1;
            }
            break;
            
        default :
            if (!(props[space - 1].getOwned () ) ){ //If the property is owned, allow the player to purchase it
                char response;
                cout<<"This property is unowned."<<endl;
                if (money - props[space-1].getPrice() > 0){
                    cout<<"Would you like to purchase "<<props[space-1].getName()<<" for $"<<props[space-1].getPrice()<<"? (Y/N)"<<endl;
                    while (true){
                        cin>>response;
                        if (response == 'Y' || response == 'y'){
                            money -= props[space-1].getPrice();
                            props[space-1].setOwned (true);
                            properties_owned[space-1] = true;
                            cout<<"You now own "<<props[space-1].getName()<<"!"<<endl;
                            break;
                        }
                        else if (response == 'N' || response == 'n'){
                            cout<<"You did not purchase "<<props[space-1].getName()<<"."<<endl;
                            break;
                        }
                        else{
                            cout<<"Please enter a valid input."<<endl;
                        }
                    }
                }
                else{
                    cout<<"You do not have enough money to purchase "<<props[space-1].getName()<<"."<<endl;
                }
            }
            else{
                exception = space-1;
            }
            break;
    }
                    
    /*Check if the player rolled doubles and the game settings*/
    if (die1 == die2 && roll_again){
        if (++doubles == 3){
            cout<<endl;
            cout<<"You rolled doubles 3 times! You are arrested for speeding!"<<endl;
            doubles = 0;
            space = 11;
            jail = true;
        }
    }
    else{
        doubles = 0; //If they did not, set doubles back to 0
    }
}

/*Buy member function, used to buy and sell houses*/
  void Player::buy(Properties props[]){//Player buy function
    cout<<endl<<name<<", you own the following unmortgaged properties:"<< endl;//Show the player their unmortgaged properties
    for (int i(0); i < 40; i++){
        if(properties_owned[i] && !(props[i].getMortgaged())){ //If they own the property and its not mortgaged, list it
            cout<<"("<<i<<")"<<"\t"<<props[i].getID_Color ()<<"\t"<<"\t"<<props[i].getName () << "\t"; //Print out the space number and the name
            if (props[i].getHouses() == 5){
                cout<<"(Hotel)"<<endl;
            }
            else{
                cout << "("<< props[i].getHouses() << " houses)" << endl;
            }
        }
    }
    char input;//The players response to buy or sell
    bool flag(true);//flag for valid input
    while(flag){
    cout << endl << "Would you like to (B)uy or (S)ell? " << endl << "Enter '0' to return to the main menu." << endl;// ask if the player wants to buy or sell.
    cin >> input;
    if( input == '0'){
        return;
    }
    if( input == 'B' || input == 'b' ){
        flag = false;//set flag to false
        int response;//store the property number
        cout<< "Which property would you like to buy on? " << endl; 
        cout << "Enter the property number from the list above." << endl;//Ask what property to buy on
        cout << "Enter '0' when you are done." << endl;
        while (true){
        while(!(cin>>response)){
            string trash;
                cin.clear();
                getline(cin, trash, '\n');
                cout<<"Invalid input. Please enter a number."<<endl;
            }
        while(response >= 40){ //Ensure that the number is less than 40 
            response -= 40;
        }
        while(response < 0){ //Ensure that the number is greater than 0
            response += 40;
        }
        if (response == 0){
            return;
        }
        if(!(response==5||response==15||response==25||response==35||response==12||response==28)){
            if(properties_owned[response]){
                if (own_monopoly(props[response].getID())){//Checks to see that the player owns the monopoly
                    if(props[response].getHouses() < 5){//Checks to make sure they can still build
                        int num_Houses = props[response].getHouses();//assigns the number of houses 
                        bool flagMon(true);//Flag to make sure they are building evenly
                        for(int i(0); i< 40; i++){
                            if(props[response].getID() == props[i].getID()){
                                if(!(props[i].getHouses() == num_Houses || props[i].getHouses() == (num_Houses + 1))){//checks to see if the player is building evenly
                                    flagMon=false;// sets the flag to false if they are not building evenly
                                }
                            }
                        }
                        if(flagMon){//If the are building evenly allow them to buy
                            char input2;
                            cout << "The house you are about to buy costs $" << props[response].getH_cost() << "." << endl;//Present the player with the cost.
                            bool flagYN(true);//Valid answer flag
                            while(flagYN){
                                cout << "Are you sure you want to purcahse this house? (Y/N)" << endl;//Final check 
                                cin >> input2;
                                if( input2 == 'Y' || input2 == 'y' ){
                                    flagYN=false;// valid answer
                                    if (money - props[response].getH_cost() < 0){
                                        cout<<"You don't have enough money!"<<endl;
                                    }
                                    else{
                                        subMoney(props[response].getH_cost());//takes money from player
                                        props[response].setHouses(1);//builds a house
                                        cout << "You have purchased a house!" << endl;
                                    }
                                    
                                }else if( input2 == 'N' || input2 =='n' ){//If they cahnge their mind, it will go back
                                    flagYN=false;
                                    
                                }else{
                                    cout<< "Invalid input, please enter either Y or N." << endl;//Invalid answer, repeat loop
                                }
                            }
                    
                        }
                        else{
                            cout<< "You must buy houses evenly on all " << props[response].getID_Color() << " properties." << endl;//Error message, not building evenly
                    
                        }
                    }else{
                        cout << "You cannot build anymore, you own a hotel on that property." << endl;//Error, They cannot build anymore
                    }
                }else{
                    cout << "You must own a monopoly on " << props[response].getID_Color ()<< " before you can buy and build houses." << endl;//Error, they must own monopoly before building
                }
            
        }else{
            cout << "You do not own that property." << endl;//Error, you do not own that property
        }
        }else{
            cout<< "You cannot buy a house on " << props[response].getID_Color() << " properties." << endl;
        }
        }        
              
        }else if ( input == 'S' || input == 's' ){//Sell function
            flag = false;
            int response;//Stores their response
            cout<< "Which property would you like to sell on?" << endl;
            cout << "Enter the property number from the list above." << endl;//Ask what property to buy on
            cout << "Enter '0' when you are done."<<endl;
            while(true){
            while(!(cin>>response)){
            string trash;
                cin.clear();
                getline(cin, trash, '\n');
                cout<<"Invalid input. Please enter a number."<<endl;
            }
            while(response > 40){ //Ensure that the number is less than 40 
                response -= 40;
            }
            while(response < 0){ //Ensure that the number is greater than 0
                response += 40;
            }
            if (response == 0){
                break;
            }
            if(properties_owned[response]){//check to see that they own the property
                if(props[response].getHouses() >= 1){//checks to see that they have houses to sell
                    int num_Houses = props[response].getHouses();//stores the number of houses into int
                        bool flagMon(true);
                        for(int i(0); i< 40; i++){
                            if(props[response].getID() == props[i].getID()){
                                if(!(props[i].getHouses() == num_Houses || props[i].getHouses() == (num_Houses - 1))){//checks to see if the player is selling evenly
                                    flagMon=false;// sets the flag to false if they are not selling evenly
                                }
                            }
                        }
                        if(flagMon){
                            char input2;
                            cout << "You will receive $" << props[response].getH_cost() << " for selling your house." << endl;//Present the player with the cost.
                            bool flagYN(true);
                            while(flagYN){
                                cout << "Are you sure you want to sell this house? (Y/N)" << endl;// final check
                                cin >> input2;
                                if( input2 == 'Y' || input2 == 'y' ){
                                    flagYN=false;
                                    addMoney(props[response].getH_cost());//gives money from player
                                    props[response].setHouses(-1);//sells a house
                                    cout << "You have sold a house!" << endl;
                                    
                                }else if( input2 == 'N' || input2 =='n' ){// If they change their mind it will go back
                                    flagYN=false;
                                    
                                }else{
                                    cout<< "Invalid input, please enter either Y or N." << endl;//Invalid input, repeat loop
                                }
                            }
                    
                        }
                        else{
                            cout<< " You must sell houses evenly on all " << props[response].getID_Color() << " properties." << endl;//Error, they must sell evenly
                        }
                }
                else{
                    cout << "You do not have any houses to sell on that property." << endl;//Error, they do not own any houses there
                
            }
            }else{ 
                cout << "You do not own that property." << endl;//Error, they do not own that property
            }
            }
        }else{
            flag = true;
            cout<< "Invalid input, please enter either B, S, or 0." << endl;//Invalid input, reapeat loop
        }
    }  
}

/*Stats member function, prints out the player's stats*/
  void Player::stats (Properties props[]) {
    cout << endl << name << ", you have $" << money << "." << endl << endl; // Print out the name of the player and the amount of money the player has
    cout << "You own the following properties: " << endl; // Print out a list of the properties the player owns
    for (int i=0; i<40; i++){
        if (properties_owned[i]){ // Check to see what properties the player owns
            cout <<  props[i].getID_Color() << "\t" << props[i].getName(); //Print our color and name of properties owned
            if (props[i].getHouses() > 0) { //Check to see if there are any houses on any of the properties
                cout<<"\t(";
                if (props[i].getHouses() == 5) { //If the player owns a hotel, print it out to the screen
                    cout << "Hotel)" << "\t";
                }
                else{ //If the player owns hoses, print out how many
                    cout<<props[i].getHouses();
                    if (props[i].getHouses() == 1){
                        cout << " house)" << "\t";
                    }
                    else{
                        cout << " houses)" << "\t";
                    }
                }
            } //Inform the player if the property is mortgaged
            if (props[i].getMortgaged() ){
                cout << " (mortgaged)";
            }
            cout<<endl;
        }
    }
    cout << endl;
    /*Print out if the player owns a monopoly*/
    if (own_monopoly (1)){
        cout << "You own a monopoly on the indigo properties." << endl;
    }
    if (own_monopoly (2)){
        cout << "You own a monopoly on the cyan properties." << endl;
    }
    if (own_monopoly (3)){
        cout << "You own a monopoly on the pink properties." << endl;
    }
    if (own_monopoly (4)){
        cout << "You own a monopoly on the orange properties." << endl;
    }
    if (own_monopoly (5)){
        cout << "You own a monopoly on the red properties." << endl;
    } 
    if (own_monopoly (6)){
        cout << "You own a monopoly on the yellow properties." << endl;
    } 
    if (own_monopoly (7)){
        cout << "You own a monopoly on the green properties." << endl;
    } 
    if (own_monopoly (8)){
        cout << "You own a monopoly on the blue properties." << endl;
    }
    if (RR_owned() > 0){
        cout << "You own " << RR_owned();
        if(RR_owned() > 1){
            cout<<" Railroads.";
        }
        else{
            cout<<" Railroad.";
        }
        cout<<endl;
    }
    if (utilities_owned() > 0){
        cout << "You own " << utilities_owned();
        if(utilities_owned() > 1){
            cout<<" utilities.";
        }
        else{
            cout<<" utility.";
        }
        cout<<endl;
    }
    cout << endl;
    if (jail){ //Specify if the player is in jail
        cout<<"You are in Jail."<<endl;
    }
    else{
        cout<<"You are on: "<<props[(space - 1)].getName()<<endl;
    }
    if(GooJF){
        cout<<"You have a Get out of Jail Free card."<<endl;
    }
} 
/*Trading member function, only prints out data to player*/
  void Player::trade(Properties props[]){
    cout<<endl<<name<<" has $"<<money<<"."<<endl; //Tell the player how much money they have
    cout<<"They also own the following properties:"<<endl; //List off what properties the player owns
    for (int i(0); i < 40; i++){
        if(properties_owned[i]){ //If they own the property, list it
            cout<<"("<<i<<")"<<"\t"<<props[i].getID_Color ()<<"\t"<<"\t"<<props[i].getName ()<<"\t"; //Print out the space number and the name
            if(props[i].getHouses () > 0){ //If there are houses, show how many
                if(props[i].getHouses () == 5){ //If they own a hotel, tell them
                    cout<<"\t"<<"Hotel";
                }
                else{
                    cout<<"\t"<<props[i].getHouses (); //Print out the number of houses
                    if(props[i].getHouses () == 1){
                    cout<<" house";
                    }
                    else{
                        cout<<" houses";
                    }
                }
            }
            cout<<endl;
        }
    }
    if(GooJF){ //Print out if they player owns a GooJF card
        cout<<name<<" has a Get out of Jail Free Card."<<endl;
    }
}

/*Mortgage member function*/
  void Player::mortgage(Properties props[]){
    cout<<endl<<name<<", you have $"<<money<<"."<<endl; //Tell the player how much money they have
    cout<<"You own the following properties:"<<endl; //List off what properties the player owns
    for (int i(0); i < 40; i++){
        if(properties_owned[i]){ //If they own the property, list it
            cout<<"("<<i<<")"<<"\t"<<props[i].getID_Color ()<<"\t"<<"\t"<<props[i].getName (); //Print out the space number, color, and name
            if(props[i].getHouses () > 0){ //If there are houses, show how many
                if(props[i].getHouses () == 5){ //If they own a hotel, tell them
                    cout<<" (Hotel)";
                }
                else{
                    cout<<" ("<<props[i].getHouses (); //Print out the number of houses
                    if(props[i].getHouses () == 1){
                    cout<<" house)";
                    }
                    else{
                        cout<<" houses)";
                    }
                }
            }
            else{
                cout<<" (0 houses)";
            }
            if(props[i].getMortgaged ()){ //If mortgaged, print out the unmortgage price
                cout<<"\t"<<"Unmortgage price: "<<(props[i].getMortgage () ) * 1.1; //Unmortgage price is 10% interest on mortgage price
            }
            else{ //If unmortgaged, print out the mortgage price
                cout<<"\t"<<"Mortgage price: "<<props[i].getMortgage ();
            }
            cout<<endl;
        }
    }
    int response;
    string trash;
    /*Ask them what property they want to mortgage or unmortgage*/
    cout<<endl<<"Which property would you like to mortgage/unmortgage?"<<endl<<"(enter the property number)"<<endl;
    cout<<"Enter '0' to when you are done."<<endl;
    while(true){ //Mortgage loop
        while(!(cin>>response)){ //Ensure a valid input
            cin.clear();
            getline(cin, trash, '\n');
            cout<<"Invalid input. Please enter one of the player numbers."<<endl;
        }
        while(response >= 40){ //Ensure that the number is less than 40
            response -= 40;
        }
        while(response < 0){ //Ensure that the number is greater than 0
            response += 40;
        }
        if (response == 0){ //If they enter '0', break out of the loop
            break;
        }
        bool flag (false); //Create a flag
        if(properties_owned[response]){ //If they own that property
            int id = props[response].getID (); //Get the color id of that property
            for(int i(0); i < 40; i++){ //Go through all other properties
                if (props[i].getID () == id){ //If it is of the same color
                    if( props[i].getHouses () > 0){ //Check if they have any houses on that property
                        cout<<"You must first sell all houses on the "<<props[i].getID_Color ()<<" properties."<<endl<<endl;
                        flag = true;
                    }
                }
                if (flag){ //If there is a flag, break out of the loop
                    break;
                }
            }
            if (!(flag)){ //If they do not have houses, mortgage/unmortgage the property
                if(props[response].getMortgaged ()){
                    double value = props[response].getMortgage ();
                    if (money - (value * 1.1) < 0){ //Ensure that the player has enough money to unmortgage the property
                        cout<<"You do not have enough money to unmortgage "<<props[response].getName ()<<"."<<endl<<endl;
                    }
                    else{ //If they player has enough money, unmortgage the property
                        money -= (value * 1.1);
                        props[response].setMortgaged (false);
                        cout<<"You paid $"<<(value * 1.1)<<" to unmortgage "<<props[response].getName ()<<"."<<endl<<endl;
                    }
                }
                else{ //Mortgage the property
                    double value = props[response].getMortgage ();
                    money += value;
                    props[response].setMortgaged (true);
                    cout<<props[response].getName ()<<" has been mortaged, and you recieved $"<<value<<"."<<endl<<endl;
                }
            }                    
        }
        else{ //If they do not own that property, do not mortgage
            cout<<"You do not own "<<props[response].getName ()<<"!"<<endl<<endl;
        }
    }
}

/*Member function for debt*/
  void Player::debt(Properties props[]){
    if (money > 0){ //If they still have money left, nothing changes
        return;
    }
    else{
        double assets (0); //The total assets
        for (int n (0); n < 40; n++){ //Calculate the player's assets
            if (properties_owned[n]){
                if (props[n].getMortgaged() ){
                    assets += props[n].getMortgage();
                }
                if (props[n].getHouses() > 0){
                    assets += props[n].getHouses() * props[n].getH_cost();
                }
            }
        }
        if (abs(money) > assets){ //If they do not have enough money to pay off the debt, they lose
            cout<<"You do not have enough money to pay this debt!"<<endl;
            cout<<name<<" is bankrupt!"<<endl;
            is_playing = false; //Set this boolean value to false
            for (int n (0); n < 40; n++){ //Return all properties to the bank and remove houses or mortgages
                if (properties_owned[n]){
                    properties_owned[n] = false;
                    props[n].return_default();
                }
            }
        }
        else{
            cout<<"You will need to sell some of your possesions to pay your debt of $"<<abs(money)<<"."<<endl;
            cout<<"You own the following properties:"<<endl; //List off what properties the player owns
            for (int i(0); i < 40; i++){
                if(properties_owned[i]){ //If they own the property, list it
                    cout<<"("<<i<<")"<<"\t"<<props[i].getID_Color ()<<"\t"<<"\t"<<props[i].getName (); //Print out the space number, color, and name
                    if(props[i].getHouses () > 0){ //If there are houses, show how many
                        if(props[i].getHouses () == 5){ //If they own a hotel, tell them
                            cout<<" (Hotel)";
                        }
                        else{
                            cout<<" ("<<props[i].getHouses (); //Print out the number of houses
                            if(props[i].getHouses () == 1){
                            cout<<" house)";
                            }
                            else{
                                cout<<" houses)";
                            }
                        }
                    }
                    else{
                        cout<<" (0 houses)";
                    }
                    if(props[i].getMortgaged ()){ //If mortgaged, print out its status
                        cout<<"\t"<<"(Mortgaged)";
                    }
                    else{ //If unmortgaged, print out the mortgage price
                        cout<<"\t"<<"Mortgage price: $"<<props[i].getMortgage ();
                    }
                    cout<<endl;
                }
            }
            cout<<endl;
            cout<<"Please enter the number of the property you would like to"<<endl;
            cout<<"sell houses on or mortgage."<<endl<<endl;
            int response; 
            while (money <= 0){ //While the player is still in debt
                while(!(cin>>response)){
                    string trash;
                    cin.clear();
                    getline(cin, trash, '\n');
                    cout<<"Invalid input. Please enter a number."<<endl;
                }
                if (properties_owned[response]){ //Ensure the player ownes the property
                    if (props[response].getHouses() > 0){ //If there are houses
                        int id = props[response].getID();
                        int num_houses = props[response].getHouses();
                        bool flag (true); 
                        for(int n (0); n < 40; n++){ //Make sure the player is selling houses evenly
                            if(props[n].getID() == id){
                                if(!(props[n].getHouses() == num_houses || props[n].getHouses() == (num_houses - 1) ) ){ 
                                    flag = false;
                                }
                            }
                        }
                        if (flag){ //If they are selling evenly, allow them to sell the house
                            money += props[response].getH_cost();
                            props[response].setHouses(-1);
                            cout<<"You sold a house for $"<<props[response].getH_cost()<<endl;
                        }
                        else{ //Otherwise, print out an error message
                            cout<<"You must sell houses evenly!"<<endl;
                        }
                    }
                    else if(!(props[response].getMortgaged() )){ //If the property is not mortgaged, mortgage it
                        money += props[response].getMortgage();
                        props[response].setMortgaged(true);
                        cout<<"You mortgaged this property for $"<<props[response].getMortgage()<<endl;
                    }
                    if (money <= 0){ //If they are still in debt, show how much debt is left
                        cout<<"You are still $"<<abs(money)<<" in debt."<<endl;
                    }
                    else{ //Otherwise, inform them that their debt is paid off and break out of the loop
                        cout<<"You have paid off your debt!"<<endl;
                        break;
                    }
                }    
                else{
                    cout<<"You do not own that property"<<endl;
                }
            }
        }                   
    }
}

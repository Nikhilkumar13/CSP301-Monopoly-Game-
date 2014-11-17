
    int num_chance; //Number of Chance cards
    int num_chest; //number of chest cards
    int num_players(3);
    int players_remaining (num_players);
int currentPlayerPaying(0);
      //Create variables for the settings
    double starter_money (1500); //The amount of money that the player starts with
    bool roll_again (true); //Determines if the player is allowed to roll again if they roll doubles
    bool jackpot (false); //Determines if the player collects 'jackpot' money when they land on 'Free Parking'
    
    //Declare and initialize the remaining variables for use in the gameplay loop
    int numberOfBots(0);
    int numberOfHuman(0);
    const int start_time ( unsigned( time(0) ) ); //The start time of the game
    int current_time (0); //The current time of the game
    int previous_time (0); //Passed time from a previous game
    double jackpot_value (0); //Set the jackpot value
    int turn_counter(0); //Counts the number of turns
int duration (0); //Amount of time that has passed during the gameplay
    // int num_players; //Variable that hold the number of players    present in main file
    //Create a Yes/No variable
        Properties property[40]; //Create an array of Property objects (there will always be 40 spaces on the board
                Chest * chest_cards; //Create an array of Chest objects
      Chance* chance_cards; //Create an array of Chance objects
     string trash; //This string is only used to move the 'getline' function down a line so that it may read in the correct data

    char YN ('N');
    char wantBot('N');
    //Create an array of 'Player' objects
    Player *Players[6];
     //Max number of players is 6
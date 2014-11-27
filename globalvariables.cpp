/*!  time how long game should last*/
    int gameTimeLimit(0); 
    /*!Number of Chance cards*/ 
    int num_chance; 
   /*!number of chest cards */
    int num_chest; 
    /*! number of Players*/
    int num_players(3);
    /*! Number of players remaning*/
    int players_remaining (num_players);
    /*! which player is currently playing*/
    int currentPlayerPlaying(0);
    /*! how many rounds */
    int round_counter(0);
/*! The amount of money that the player starts with*/

    double starter_money (1500); 
    /*!Determines if the player is allowed to roll again if they roll doubles */
    bool roll_again (true); 
    /*!Determines if the player collects 'jackpot' money when they land on 'Free Parking */
    bool jackpot (false); //
    /*!Number of Computer players */
    
    int numberOfBots(0);
    /*! Number of human Players*/
    int numberOfHuman(0);
    /*! The start time of the game*/
    const int start_time ( unsigned( time(0) ) ); 
    /*! The current time of the game*/
    int current_time (0); 
    /*!Passed time from a previous game */
    int previous_time (0); //
    /*! Set the jackpot value*/
    double jackpot_value (0); 
    /*!Counts the number of turns */
    int turn_counter(0); 
    /*! Amount of time that has passed during the gameplay*/
    int duration (0); 
    /*! Create an array of Property objects (there will always be 40 spaces on the board)*/
    Properties property[40]; 
    /*! Create an array of Chest objects*/
    Chest * chest_cards; 
    /*! Create an array of Chance objects*/
      Chance* chance_cards; 
      /*! This string is only used to move the 'getline' function down a line so that it may read in the correct data*/
     string trash; 
     /*! */

    char YN ('N');
    /*!Create an array of 'Player' objects MAX 6 */
    Player *Players[6];
    /** A function to declare winner on abruptly stoping game
    *
    *return void
    */
    void declareWinner(){

        int temp(0);
        int position(0);
        for(int i(0);i<num_players;i++)
        {
            int temp2=Players[i]->getAssets(property);
            if(temp2>=temp)
            {
                temp=temp2;
                position=i;

            }
        }
     for (int i(0); i < num_players; i++){
        if ( Players[i]->still_playing() ){
            cout<< Players[i]->getName();
            cout<<"   You total assets are worth $"<< Players[i]->getAssets(property)<<"."<<endl; //Print out the player's assets
           
        }
    }
    cout<<"=========================================================================================="<<endl;
    cout<<Players[position]->getName()<<" Won by having assets of worth value $ "<<Players[position]->getAssets(property)<<endl;
    cout<<"=========================================================================================="<<endl;

            cout<<"You game lasted a total of "<<(duration / 3600)<<"hour(s), "<<((duration % 3600) / 60)<<"minute(s), and "<< (duration % 3600) % 60 << "second(s)."<<endl; //Print out the duration of gameplay
            cout<<"and was played over the course of "<<turn_counter<<" turns."<<endl; //Print out the number of turns
            cout<<"Do you Really wana quit the Game in Between press y/n"<<endl;
            char ch;
            cin>>ch;
            if(ch=='y'|ch=='Y')
            {
                exit(0);
            }

}
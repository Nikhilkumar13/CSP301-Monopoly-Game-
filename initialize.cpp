 

    ifstream in_chance ("chance.txt"); //Open the file with the chance card information
    if (!(in_chance)){ //If it does not open, report the problem and close the program
        cout<<"Error loading Chance cards."<<endl;
        cout<<"Please ensure that the chance file exists."<<endl;
        system("PAUSE");
        exit(1);
    }
    in_chance>>num_chance; //Read in the first number, which will be the number of chance cards
     chance_cards= new Chance[num_chance];
        for(int i (0); i < num_chance; i++){
            getline (in_chance, trash); //Use trash to 'tab' down to the next line
            Chance card (in_chance); //Use the non-default constructor
            chance_cards[i] = card; //Utilize the array
        }
    in_chance.close(); //Close the file
    
    //Load the community chest cards
    

    ifstream in_chest ("community_chest.txt"); //Open the file with the community chest card information
    if (!(in_chest)){ //If it does not open, report the problem and close the program
        cout<<"Error loading Community Chest cards."<<endl;
        cout<<"Please ensure that the community chest file exists."<<endl;
        system("PAUSE");
        exit(1);
    }
    in_chest>>num_chest; //Read in the first number, which will be the number of community chest cards
    chest_cards=new Chest[num_chest];
    //The following loop will utilize 'string trash' for the same purpose as above
    for(int i (0); i < num_chest; i++){
        getline(in_chest, trash); //Use trash to 'tab' down to the next line
        Chest card (in_chest); //Use the non-default constructor
        chest_cards[i] = card; //Utilize the array
    }
    in_chest.close(); //Close the file
    
    //Load the property data
    
    ifstream in_properties ("properties.txt"); //Open the file with the property information
    if(!(in_properties)){ //If it does not open, report the problem and close the program
        cout<<"Error loading Property cards."<<endl;
        cout<<"Please ensure that the property file exists."<<endl;
        system("PAUSE");
        exit(1);
    }
    //The following loop will utilize 'string trash' for the same purpose as above
    for(int i(0); i < 40; i++){
        Properties temp_prop(in_properties);
        property[i] = temp_prop;
        getline(in_properties, trash);
    }
    in_properties.close(); //Close the file 
    
   
    cout<<endl;
            
    //Start srand, using the time.h as a seed
    srand( unsigned( time(0) ));
    
    //Introduce the player to the game
    cout<<"All the files have been Succesfully Loaded"<<endl;
    cout<<"Welcome to Monopoly!";
    // system("PAUSE");
    cout<<endl;
    cout.setf(ios::boolalpha);
    
        while(true){
            //Display the settings to the user
            cout<<endl<<"These are the current settings:"<<endl;
            cout<<"\t"<<"The amount of starter money is $"<<starter_money<<"."<<endl;
            cout<<"\t"<<"Rolling again for doubles is  "<<roll_again<<"."<<endl;
            cout<<"\t"<<"Jackpot for landing on Free Parking is set to "<<jackpot<<"."<<endl;
            //Ask if the settings are ok
            while(true){
                cout<<"Are these settings OK? (Y/N) ";
                cin>>YN;
                //If a valid responce is given, break out of this while loop
                if(YN == 'Y' || YN == 'y' || YN == 'N' || YN == 'n'){
                    break;
                }
                //If an invalid response is given, Inform and reprompt the user
                else{
                    cout<<"Invalid input. Please type either 'Y' or 'N'."<<endl;
                }
            }
            
                
            //If the settings are not ok, ask the user to manually adjust the settings

            if (YN == 'N' || YN == 'n'){                
                cout<<"Please enter the desired amount of starting money: ";
                while(true){
                    while(!(cin>>starter_money)){ //If the input is invalid, cin will be 'reset', and the user will be promped to try again
                        cin.clear();
                        getline(cin, trash, '\n');
                        cout<<"Invalid input. Please enter a number."<<endl;
                    }
                    if(starter_money <= 0){ //Ensure that the user enters a positive number
                        cout<<"Please enter a positive number."<<endl;
                    }
                    else{
                        break;
                    }
                }
                cout<<"Please enter '1' if you would like to roll again for doubles,"<<endl;
                cout<<"or '0' (zero) if you would not: "; //Ask if the player want to be able to roll again if they roll doubles
                while(!(cin>>roll_again)){
                    cin.clear();
                    getline(cin, trash, '\n');
                    cout<<"Invalid input. Please enter '1' or '0'."<<endl;
                }
                cout<<"Please enter '1' if you would like to collect money for"<<endl; //Ask the player if they would like to collect money for
                cout<<"landing on Free Parking, or '0' (zero) if you would not: "; //landing on free parking
                while(!(cin>>jackpot)){
                    cin.clear();
                    getline(cin, trash, '\n');
                    cout<<"Invalid input. Please enter '1' or '0'."<<endl;
                }
            }
            //If the settings are ok, break out of the loop.
            else if (YN == 'Y' || YN == 'y'){
                cout<<endl<<"The settings have been saved."<<endl<<endl;
                break;
            }
        }
    
        //Prompt the user for the number of players
        while(true){
            cout<<"How many computer players will there? (0-5) ";
            // cout<<"we have Only One Bot"<<endl;
            while(!(cin>>numberOfBots)){
                cin.clear();
                getline(cin, trash, '\n');
                cout<<"Invalid input. Please enter a number between 0 and 5."<<endl;
            }
            if(numberOfBots >= 0 && numberOfBots <= 5){ //If a valid number is chosen, break out of the loop
                cout<<endl;
                break;
            }
            else{
                cout<<"Please enter a valid number of players between 2 and 6."<<endl<<endl; //If not, inform the user that the number was invalid
            }
        }
          while(true){
            cout<<"How many Human players will there? (0- "<<6-numberOfBots<<")  ";
            while(!(cin>>numberOfHuman)){
                cin.clear();
                getline(cin, trash, '\n');
                cout<<"Invalid input. Please enter a number between 2 and 6."<<endl;
            }
            if(numberOfHuman >= 0 && numberOfHuman <= 6 - numberOfBots){ //If a valid number is chosen, break out of the loop
                cout<<endl;
                break;
            }
            else{
                cout<<"Please enter a valid number of players between 2 and 6."<<endl<<endl; //If not, inform the user that the number was invalid
            }
        }
         num_players=numberOfHuman+numberOfBots;

        getline(cin, trash); //Use this to 'tab' down to the next line
            for(int j(0);j<numberOfBots;j++){
                string name;
                cout<<"Calling Mr. Bot "<<(j+1)<<".."<<endl<<endl;
                stringstream convert;
                convert<<j;
                name="Mr. Bot"+convert.str();
                botPlayer *temp= new botPlayer(starter_money,name,true);
                Players[j] = temp;
                cout<<endl;
            }
        for(int i(numberOfBots); i < num_players; i++){
            string name;         
            cout<<"Player "<<(i+1)<<", please enter your name."<<endl; //Ask for the player's name
            cout<<"Press 'ENTER' when you are finished."<<endl;
            getline(cin, name); //Use a getline for their name
            Player *temp =new Player(starter_money, name,false); //Utilize the non-default constructor on a temporary player object
            Players[i] = temp; //Assign the values of the temporary player object to the one in the array
            cout<<Players[i]->getName();
            cout<<endl;
        }
        //Inform the player that everything is set up
        cout<<"Enter time limit of game"<<endl;
        {
            while(true)
            {
                cin>>gameTimeLimit;
                if(gameTimeLimit>0)
                {
                    break;

                }
                else
                {
                    cout<<"Time Should be an integer"<<endl;
                }
            }
        }
        cout<<"Ok, everything's set up!"<<endl;
    
    //Inform the user that the game is set up, and they are ready to start
    cout<<"Press Enter when all the players are ready to play."<<endl<<endl;
    system("PAUSE");
    //Declare and initialize the remaining variables for use in the gameplay loop
    cout<<endl<<"Yo!, Evething Okay from initialize.cpp file lets Play!"<<endl;
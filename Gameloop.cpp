 // players_remaining = num_players; //Reset the player counter
 // for(int i(0); i < num_players; i++){
while(!Players[currentPlayerPlaying]->still_playing())
    {
        currentPlayerPlaying=(currentPlayerPlaying+1)%num_players;
        turn_counter++;
    }
               //Check to ensure that this player is still playing
int i=currentPlayerPlaying;
Players[i]->debt(property);
int doubles (0); //Number of doubles rolled

while (true){
    char selection; //char that contains commands from the user
    selection=Players[i]->play();
                    
                    
    //Player chooses to roll the dice
    if (selection == 'r' || selection == 'R'){
        int other_player (0); //Which player money goes to
        double money_other_player  (0); //Money that goes to other player
        double money_all_players (0); //Money that goes to all players
        int exception (0); //Returns exceptions (1 is generic property; 5, 15, 25, 35 is nearest RR; 12, 28 is nearest utility)
            Players[i]->roll(i, property, chest_cards, chance_cards, roll_again, jackpot, jackpot_value, doubles, num_chest, num_chance, money_other_player, money_all_players, exception);
        if (money_all_players != 0){ //If money goes to all players (such as from a chance card), perform the operation
            for (int n(0); n < num_players; n++){
                if (n != i){
                    Players[i]->addMoney(money_all_players);
                    Players[n]->subMoney(money_all_players);
                }
            }
        }

                        
        cout<<Players[i]->getrollsum()<<endl;
        // p1[i]->moven(Players[i]->getrollsum());
        p1[i]->show+=39;
        glutPostRedisplay();




                        //Perform any exception directions
                        switch (exception){
                            case 0: //If there is no exception, do not execute special directions
                                break;
                                
                            case 12:
                            case 28: //If the player lands on an owned utility, execute special directions
                                for (int n(0); n < num_players; n++){
                                    if (Players[n]->own_property(exception) ){ //Find which player owns the property
                                        if (n == i){ //If the current player owns it, break out of the case
                                            break;
                                        }
                                        int num_utilities = Players[n]->utilities_owned();
                                        //Execute special directions based on if the player owns 1 or 2 utilitie
                                        if (num_utilities == 1){
                                            cout<<Players[n]->getName()<<" owns one utility."<<endl;
                                            cout<<"You must pay 4x the dice roll."<<endl;
                                            int die1 ((rand()%6) + 1);
                                            int die2 ((rand()%6) + 1);
                                            cout<<"You rolled a "<<die1<<" and a "<<die2<<"."<<endl;
                                            cout<<"You paid "<<Players[n]->getName()<<" $"<<((die1+die2)*4)<<"."<<endl;
                                            Players[i]->subMoney((die1+die2)*4);
                                            Players[n]->addMoney((die1+die2)*4);
                                            Players[i]->debt(property);
                                        }
                                        else{
                                            cout<<Players[n]->getName()<<" owns two utilities."<<endl;
                                            cout<<"You must pay 10x the dice roll."<<endl;
                                            int die1 ((rand()%6) + 1);
                                            int die2 ((rand()%6) + 1);
                                            cout<<"You rolled a "<<die1<<" and a "<<die2<<"."<<endl;
                                            cout<<"You paid "<<Players[n]->getName()<<" $"<<((die1+die2)*10)<<"."<<endl;
                                            Players[i]->subMoney((die1+die2)*10);
                                            Players[n]->addMoney((die1+die2)*10);
                                            Players[i]->debt(property);
                                        }
                                        break;
                                    }
                                }                                           
                                break;
                            case 5 :
                            case 15:
                            case 25: //If the player lands on an owned railroad, execute special directions
                            case 35:
                                for (int n(0); n < num_players; n++){
                                    if (Players[n]->own_property(exception) ){ //Find which player owns the property
                                        if (n == i){ //If the current player owns the property, break out of the case
                                            break;
                                        }
                                        int num_RR = Players[n]->RR_owned(); //Find out how many railroads this player owns
                                        if (num_RR == 1){
                                            cout<<Players[n]->getName()<<" owns "<<num_RR<<" railroad."<<endl;
                                        }
                                        else{
                                            cout<<Players[n]->getName()<<" owns "<<num_RR<<" railroads."<<endl;
                                        }
                                        //Find out how much the current player must pay
                                        cout<<"You must pay $"<<property[exception].RRpayment(num_RR)<<"."<<endl;
                                        Players[i]->subMoney(property[exception].RRpayment(num_RR));
                                        Players[n]->addMoney(property[exception].RRpayment(num_RR));
                                        Players[i]->debt(property);
                                    }
                                }                                           
                                break;    
                                                                   
                            default: //If the player lands on a generic owned property, execute generic directions
                                for (int n(0); n < num_players; n++){
                                    if (Players[n]->own_property(exception) ){ //Find which player owns the property
                                        if (n == i){ //If the current player owns the property, break out of the case
                                            break;
                                        }
                                        cout<<Players[n]->getName()<<" owns this property."<<endl;
                                        cout<<"You must pay $"<<property[exception].payment()<<"."<<endl; //Inform the player how much they owe
                                        Players[i]->subMoney(property[exception].payment() );
                                        Players[n]->addMoney(property[exception].payment() ); //Make the payment
                                        Players[i]->debt(property); //Utilize the debt function to see if they have enough money to continue playing
                                    }
                                }
                        }
                                
                        if (doubles == 0 || !(Players[i]->still_playing() )){ //If the player did not roll doubles, or is no longer playing
                            cout<<endl;
                            break;
                        }
                        else{ //If the player rolled doubles, allow them to roll again
                            cout<<"You get to roll again!"<<endl<<endl;
                        }
                    }
                    
                    //Player chooses to view their stats
                    
                    else if (selection == 's' || selection == 'S'){
                        Players[i]->stats(property); //Utilize the 'stats' member function
                        cout<<endl;
                    }
                    
                    //Player chooses to buy or sell houses
                    
                    else if (selection == 'b' || selection == 'B'){
                        Players[i]->buy(property); //Utilize the 'buy' member function
                        cout<<endl;
                    }
                    
                    //Player chooses to trade with other players
                    
                    else if (selection == 't' || selection == 'T'){
                        for(int j(0); j < num_players; j++){ //List off what each player owns
                            Players[j]->trade(property);
                        }
                        cout<<endl<<"Enter the number of the player with whom you would like to trade."<<endl; //Ask which player to trade with
                        cout<<"Enter '0' to go back to the menu."<<endl;
                        for(int j(0); j < num_players; j++){
                            cout<<"Player "<<(j+1)<<": "<<Players[j]->getName ()<<endl; //List off each player's index
                        }
                        int response;
                        while(!(cin>>response)){ //Ensure a valid input
                            cin.clear();
                            getline(cin, trash, '\n');
                            cout<<"Invalid input. Please enter one of the player numbers."<<endl;
                        }
                        if (response == 0){
                        }
                        else if (response < 1 || response > num_players){ //Ensure a valid input
                            cout<<"Invalid player number."<<endl;
                        }
                        else if (response == (i+1)){ //The player can't choose him/herself
                            cout<<"You can't trade with yourself!"<<endl;
                        }
                        else{
                            //Note: Players[i] is the current player (trader)
                                //while Players[response] is the other player (tradee)
                            
                            response--; //Subtract the index by one for element offset
                            bool trader[40] = {false};
                            int props_trader;
                            Players[i]->trade(property);
                            cout<<endl;
                            //Ask the trader what properties they would like to trade
                            cout<<Players[i]->getName()<<", please enter the property number(s) that you would like to add"<<endl;
                            cout<<"or remove from the trade list. ";
                            cout<<"Enter '0' when you are done"<<endl;
                            while (true){
                                while(!(cin>>props_trader)){ //Ensure a valid input
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter one of the property numbers."<<endl;
                                }
                                cout<<endl;
                                if((props_trader) == 0){ //If they enter 0, break out of the loop
                                    break;
                                }
                                if (props_trader < 0 || props_trader >= 40){ //Ensure a valid property number
                                    cout<<"Invalid input. Please enter one of the property numbers."<<endl;
                                }
                                else{
 //If the player owns the property and it has not yet been added to the trade,add it to the trade
                                    if (!(trader[props_trader]) && Players[i]->own_property(props_trader)){
                                        trader[props_trader] = true;
                                        cout<<"You will trade "<<property[props_trader].getName()<<"."<<endl<<endl;
                                    }
//If the player owns the property and it has already been added to the trade,remove it from the trade
                                    else if(trader[props_trader] && Players[i]->own_property(props_trader)){
                                        trader[props_trader] = false;
                                        cout<<"You will not trade "<<property[props_trader].getName ()<<endl<<endl;
                                    }
                                    //If the player does not own the property, inform them
                                    else{
                                        cout<<"You do not own "<<property[props_trader].getName ()<<endl<<endl;
                                    }
                                }
                            }
                            //Ask the player how much money they would like to trade
                            double money_trader (0);
                            while(true){
                                cout<<"Enter how much money you will trade."<<endl;
                                cout<<"$";
                                while(!(cin>>money_trader)){ //Ensure a valid input
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter a number."<<endl;
                                    cout<<"$";
                                }
                                if(money_trader < 0){ //Ensure that the amount of money is greater than 0
                                    cout<<"You can't trade negative money!"<<endl;
                                    money_trader = 0;
                                }
                                else if(money_trader >  Players[i]->getMoney()){ //Ensure the player has enough money
                                    cout<<"You don't have enough money!"<<endl;
                                }
                                else{
                                    break;
                                }
                            }
                            //If they player owns a GooJF card, ask if they would like to trade it
                            bool GooJF_trader (false);
                            if (Players[i]->getGooJF()){
                                cout<<"Enter '1' if you would like to trade your Get out of Jail Free card,"<<endl;
                                cout<<"or '0' if you would not."<<endl;
                                while(!(cin>>GooJF_trader)){
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter '1' or '0'."<<endl;
                                }
                            }
                            
                            //Ask the tradee what properties they would like to trade
                            bool tradee[40] = {false};
                            int props_tradee;
                            Players[response]->trade(property);
                            cout<<endl;
                            cout<<Players[response]->getName()<<", please enter the property number that you would like to add"<<endl;
                            cout<<"or remove from the trade list. ";
                            cout<<"Enter '0' when you are done"<<endl;
                            while (true){
                                while(!(cin>>props_tradee)){ //Ensure a valid input
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter one of the property numbers."<<endl;
                                }
                                cout<<endl;
                                if((props_tradee) == 0){ //If they enter 0, break out of the loop
                                    cout<<endl;
                                    break;
                                }
                                if (props_tradee < 0 || props_tradee >= 40){ //Ensurea valid property number
                                    cout<<"Invalid input. Please enter one of the property numbers."<<endl<<endl;
                                }
                                else{
                                    //If the player owns the property and it has not yet been added to the trade,add it to the trade
                                    if (!(tradee[props_tradee]) && Players[response]->own_property(props_tradee)){
                                        tradee[props_tradee] = true;
                                        cout<<"You will trade "<<property[props_tradee].getName()<<"."<<endl<<endl;
                                    }
                                    //If the player owns the property and it has already been added to the trade,remove it from the trade
                                    else if(tradee[props_tradee] && Players[response]->own_property(props_tradee)){
                                        tradee[props_tradee] = false;
                                        cout<<"You will not trade "<<property[props_tradee].getName ()<<endl<<endl;
                                    }
                                    //If the player does not own the property, inform them
                                    else{
                                        cout<<"You do not own "<<property[props_tradee].getName ()<<endl<<endl;
                                    }
                                }
                            }
                            //Ask the player how much money they would like to trade
                            double money_tradee (0);
                            while(true){
                                cout<<"Enter how much money you will trade."<<endl;
                                cout<<"$";
                                while(!(cin>>money_tradee)){ //Ensure a valid input
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter a number."<<endl;
                                    cout<<"$";
                                }
                                if(money_tradee < 0){ //Ensure that the amount of money is greater than 0
                                    cout<<"You can't trade negative money!"<<endl;
                                    money_tradee = 0;
                                }
                                else if(money_tradee > Players[response]->getMoney()){ //Ensure the player has enough money
                                    cout<<"You don't have enough money!"<<endl;
                                }
                                else{
                                    break;
                                }
                            }
                            //If the player has a GooJF card, ask if they would like to trade it
                            bool GooJF_tradee (false);
                            if ( Players[i]->getGooJF()){
                                cout<<"Enter '1' if you would like to trade your Get out of Jail Free card,"<<endl;
                                cout<<"or '0' if you would not."<<endl;
                                while(!(cin>>GooJF_tradee)){ //Ensure a valid input
                                    cin.clear();
                                    getline(cin, trash, '\n');
                                    cout<<"Invalid input. Please enter one of the player numbers."<<endl;
                                }
                            }
                            cout<<endl;
                            //Perform the actual trade                        
                            //List what the trader will trade
                            cout<<Players[i]->getName()<<" will trade the following:"<<endl;
                            for(int n(0); n < 40; n++){
                                if( trader[n] ){
                                    cout<<property[n].getName()<<endl;
                                }
                            }
                            if (money_trader > 0){
                                cout<<"$"<<money_trader<<endl;
                            }
                            if (GooJF_trader){
                                cout<<"Get out of Jail Free card"<<endl;
                            }
                            cout<<endl;
                            //List what the tradee will trade
                            cout<<"In exchange, "<<Players[response]->getName()<<" will trade the following:"<<endl;
                            for(int n(0); n < 40; n++){
                                if( tradee[n] ){
                                    cout<<property[n].getName()<<endl;
                                }
                            }
                            if (money_tradee > 0){
                                cout<<"$"<<money_tradee<<endl;
                            }
                            if (GooJF_tradee){
                                cout<<"Get out of Jail Free card"<<endl;
                            }
                            cout<<endl;
                            //Confirm the trade
                            while(true){
                                cout<<"Is this trade OK? (Y/N) ";
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
                            if(YN == 'Y' || YN == 'y'){ //If they choose to perform the trade, execute it
                            //Remember: Players[i] is the trader, Players[response] is the tradee
                            
                                //Exchange the properties
                                for(int n(0); n < 40; n++){
                                    if(trader[n]){
                                        Players[i]->setProperty (n, false);
                                        Players[response]->setProperty (n, true);
                                    }
                                    if(tradee[n]){
                                        Players[response]->setProperty (n, false);
                                        Players[i]->setProperty (n, true);
                                    }
                                }
                                //Exchange money
                                Players[i]->subMoney(money_trader);
                                Players[response]->addMoney(money_trader);
                                Players[response]->subMoney(money_tradee);
                                 Players[i]->addMoney(money_tradee);
                                //Exchange GooJF cards
                                if(GooJF_trader){
                                     Players[i]->setGooJF(false);
                                     Players[i]->setGooJF(true);
                                }
                                if(GooJF_tradee){
                                     Players[i]->setGooJF(false);
                                     Players[i]->setGooJF(true);
                                }
                                //Inform the players that the trade is complete
                                cout<<endl<<"The trade is complete."<<endl;
                            }
                            else{ //If the trade was canceled
                                cout<<endl<<"The trade was canceled."<<endl;
                            }
                        }
                        cout<<endl;
                    }
                    
                    //User chooses to mortgage property 
                                     
                    else if (selection == 'm' || selection == 'M'){
                     Players[i]->mortgage(property); //Utilize the 'mortgage' member function
                    cout<<endl;
                    }
                    
                    //The following two functions are 'god' functions, allowing one player control over properties
                    //These are to be used for debugging purpose
                    /*else if (selection == 'o'){
                        for (int n(0); n < 40; n++){
                            cout<<property[n].getSpace()<<"\t"<<property[n].getName()<<endl;
                        }
                        cout<<endl;
                        int h;
                        while(true){
                            cin>>h;
                            if (h == 0){
                                break;
                            }
                            else{
                                for (int n(0); n < num_players; n++){ //Remove property ownership from all other players
                                    Players[n].setProperty(h-1, false);
                                }
                                property[h-1].setOwned(true); //Give control of the property to this one player
                                 Players[i]->setProperty(h-1, true);
                            }
                        }
                    }
                    else if (selection == 'O'){ //Gives control of all properties to 1 player
                        for (int n(0); n < 40; n++){ //Should only be used once
                            if(property[n].getPrice() > 0){
                                property[n].setOwned(true);
                                 Players[i]->setProperty(n, true);
                            }
                        }
                    }*/                  
                    
                    //Input is not one of the shown letters
                    
                    else{ //If the player enters an invalid input
                        cout<<endl<<"Invalid input. Please enter one of the shown letters."<<endl<<endl;
                    }
                }
                // if (!( Players[i]->still_playing() ) ){ //If the player stopped playing this turn, reduce the counter by 1
                //     players_remaining--;
                // }
            // }
            // else { //If the player is no longer playing, subtract the number of remaining players by 1
            //     players_remaining--;
            // }
        // }
        // if (players_remaining <= 1){ //When 1 (or possibly 0) player is remaining, break out of the gameplay loop
        //     break;
        // }

        turn_counter++; //Increase the turn counter by 1
        int temproundcounter = round_counter+turn_counter/num_players;
        current_time = unsigned( time(0) ); //Find the current time
        duration = previous_time + (current_time - start_time); //Calculate how long the players have been playing for
        cout<<"duration "<<duration<<endl;

    
    cout<<Players[currentPlayerPlaying]->getName()+" ka turn over "<<endl;
    currentPlayerPlaying=(currentPlayerPlaying+1)%num_players;
    cout<<"player "+Players[currentPlayerPlaying]->getName()+"ka turn ane wala hai"<<endl;
    //Find which player is remaining, and he is Winner
    if(temproundcounter>round_counter)
    {
    if(players_remaining<=1)
    {
        void declareWinner();
   
        cout<<"Thanks for playing! Monopoly"<<endl<<endl;

    }
    cout<<"Thanks for one round playing!"<<endl<<endl;
  }
  round_counter=temproundcounter;

  if(Players[currentPlayerPlaying]->isBot())
  {
    cout<<"bot ko kon bataye iska turn hai ab"<<endl;
    // flag=false;
  }



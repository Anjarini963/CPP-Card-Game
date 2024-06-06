#include "StackLinkedList.h"
#include "PointHandling.h"


int main() {
    // Create separate deck instances
    CardDeck unansweredDeck;
    CardDeck answeredDeck;
    discardeddeck discardedDeck;
    PlayerList players;



    //load up the unansweredDeck
    unansweredDeck.LoadQuestions();
    bool gamestatus = true;
    string userchoice;
    int playercount;
    while (gamestatus) {
        string answer;
        cout << "Welcome to the game! How would you like to start?" << endl << "1. Start New Game" << endl << "2. Leaderboard" << endl << "3. Search Leaderboard" << endl << "4. Exit" << endl;;
        cin >> userchoice;
        if (userchoice == "1") {
            players.clear();
            cout << "Please enter the amount of players:" << endl;
            cin >> playercount;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for (int i = 0; i < playercount; i++) {
                cout << "Player " << (i + 1) << ", please enter your name: ";
                string PlayerName;
                getline(cin, PlayerName);
                players.addPlayer(PlayerName);

                for (int turn = 0; turn < 3; turn++) {
                    cout << PlayerName << ", Turn " << (turn + 1) << ", please pick a card:" << endl << "1. Unanswered Deck" << endl << "2. Discarded Deck" << endl;
                    cin >> userchoice;
                    if (userchoice == "1") {

                        //logic for picking a card form unanswered deck
                        Card* card = unansweredDeck.pop();
                        cout << card->question << endl;
                        cout << "DEBUG:" << card->answer << endl;
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        getline(cin, answer);
                        answer = unansweredDeck.toLower(answer);
                        unansweredDeck.trim(answer);
                        //logic for checking answer and handling card
                        if (unansweredDeck.validateAnswer(card, answer)) {
                            PlayerData* player = players.getPlayer(i);
                            if (player) {
                                player->recordAnswer(turn, card->question, card->score);
                            }
                            else {
                                cout << "Invalid player index: " << i << endl;
                            }
                            
                            answeredDeck.push(card->question, card->answer, card->score);
                            cout << "Correct!" << endl;
                            

                            delete card;
                            //logic for player points?
                        }
                        else {
                            players.getPlayer(i)->recordAnswer(turn, card->question, 0);
                            cout << "Incorrect! The card has been sent to the discarded pile!" << endl;
                            discardedDeck.push(card->question, card->answer, card->score);


                            delete card;

                        }
                        //logic for user handling (adding information of answered card onto user info)
                    }
                    else if (userchoice == "2") {
                        //logic for dislpaying the discarded set options
                        if (discardedDeck.isEmpty()) {
                            cout << "The discarded deck is currently empty. Please select another option!" << endl;
                            turn--;
                            
                            continue;
                        }
                        discardedDeck.display();
                        cout << "Please select the card you want to answer:" << endl;
                        int index;
                        cin >> index;
                        //user selects the card here
                        discardedCard* card = discardedDeck.getCard(index - 1);
                        if (card) {
                            cout << "You selected: " << endl << card->question << endl << "What's your answer? ";
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            getline(cin, answer);
                            answer = unansweredDeck.toLower(answer);
                            unansweredDeck.trim(answer);
                            if (answer == card->answer) {
                                cout << "Correct Answer!" << endl;
                                players.getPlayer(i)->recordAnswer(turn, card->question, card->score);
                                discardedDeck.remove(index - 1);
                                

                            }
                            else {
                                players.getPlayer(i)->recordAnswer(turn, card->question, 0);
                            }
                        }

                    }
                }
                cout << "Player: " << PlayerName << ", Total Points: " << players.getPlayer(i)->totalScore << endl;
               

            } cout << "The game has ended! You can now check the leaderboard ;)" << endl;
        }
        else if (userchoice == "2") {
            if (players.isEmpty()) {
                cout << "No players have been added yet. Start a new game to populate the leaderboard." << endl;
            }
            else {
                cout << "Displaying Leaderboard:" << endl;
                players.displayFormattedScores();
                players.displayWinnersHierarchy();
                string userchoice2;
                         
                

                
            }
        }
        else if (userchoice == "3") {  
            if (players.isEmpty()) {
                cout << "The leaderboard is empty. Start a new game to populate it." << endl;
            }
            else {
                string searchName;
                cout << "Enter your name to search in the top 30 winners: ";
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Clear the input buffer
                getline(cin, searchName);

                int rank = players.searchWinner(searchName);
                if (rank != -1) {
                    cout << searchName << " is ranked #" << rank << " in the top 30 winners." << endl;
                }
                else {
                    cout << searchName << " is not in the top 30 winners." << endl;
                }
            }
}
        else if (userchoice == "4") {
            cout << "Thank you for playing!" << endl;
            gamestatus = false;
            break;
        }
        else {
            cout << "Invalid Input." << endl;
        }
    }
};

   





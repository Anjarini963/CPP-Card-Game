#include "StackLinkedList.h"


int main() {
    // Create separate deck instances
    CardDeck unansweredDeck;
    CardDeck answeredDeck;
    discardeddeck discardedDeck;



    //load up the unansweredDeck
    unansweredDeck.LoadQuestions();
    bool gamestatus = true;
    string userchoice;
    int playercount;
    while (gamestatus) {
        string answer;
        cout << "Welcome to the game! How would you like to start?" << endl << "1. Start New Game" << endl << "2. Leaderboard" << endl << "3. Exit" <<endl;
        cin >> userchoice;
        if (userchoice == "1") {
            cout << "Please enter the amount of players:" << endl;
            cin >> playercount;
            for (int i = 0; i < playercount; i++) {
                cout << "Player " << (i + 1) << ", please enter your name: ";
                string PlayerName;
                cin >> PlayerName;

                for (int i = 1; i < 4; i++) {
                    cout << PlayerName << ", Turn " << (i) << ", please pick a card:" << endl << "1. Unanswered Deck" << endl << "2. Discarded Deck" << endl;
                    cin >> userchoice;
                    if (userchoice == "1") {

                        //logic for picking a card form unanswered deck
                        Card* card = unansweredDeck.pop();
                        cout << card->question << endl;;
                        cin >> answer;
                        answer = unansweredDeck.toLower(answer);
                        unansweredDeck.trim(answer);
                        //logic for checking answer and handling card
                        if (unansweredDeck.validateAnswer(card, answer)) {
                            answeredDeck.push(card->question, card->answer, card->score);
                            cout << "Correct!" << endl;
                            delete card;
                            //logic for player points?
                        }
                        else {
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
                            i--;
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
                            cin >> answer;
                            answer = unansweredDeck.toLower(answer);
                            unansweredDeck.trim(answer);
                            if (answer == card->answer) {
                                cout << "Correct Answer!" << endl;
                                discardedDeck.remove(index - 1);
                            }
                            else {
                                cout << "Wrong Answer. The card stays." << endl;
                            }
                        }

                    }
                }

            } cout << "The game has ended! You can now check the leaderboard ;)" << endl;
        }
        else if (userchoice == "2") {
            cout << "leaderboard here" << endl;
            //logic for showing preexisting leaderboard, i.e previous game
        }
        else if (userchoice == "3") {
            cout << "Thank you for playing!" << endl;
            gamestatus = false;
            break;
        }
    }
};

   





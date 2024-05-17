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
                        string answer;
                        //logic for picking a card form unanswered deck
                        Card* card = unansweredDeck.pop();
                        cout << card->question << endl;;
                        cin >> answer;
                            //logic for checking answer and handling card
                        if (unansweredDeck.validateAnswer(card, answer)) {
                            answeredDeck.push(card->question, card->answer, card->score);
                            cout << "Correct!" << endl;
                                //logic for player points?
                        }
                        else {
                            discardedDeck.push(card->question, card->answer, card->score);
                            cout << "Incorrect! The card has been sent to the discarded pile!" << endl;

                        }
                                    //logic for user handling (adding information of answered card onto user info)
                    }
                    else if (userchoice == "2") {
                        //logic for dislpaying the discarded set options
                        discardedDeck.display();
                            //logic for picking out a card from the selected list

                        
                                //logic for checking answer
                                    //logic for handling card
                                        //logic for user handling
                                            //logic for rerunning the loop
                    }
                }
               
            }
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

    /*




    // Adding a new card to the unanswered questions deck
    string stackchoice;
    cout << "Unanswered or Discarded? U/D" << endl;
    cin >> stackchoice;
    Card* question = unansweredDeck.pop();
    string x;
    string answer;
    cout << question -> question << endl;
    cout << "Do you want to answer this question? y/n" << endl;
    cin >> x;
    if (x == "y") {
        cout << "What's your answer?: " << endl;
        cin >> answer;
        if (answer == question->answer) {
            cout << "That's the correct answer" << endl;
            
        }
        else {
            cout << "That's the wrong answer! this card will go to the discarded pile" << endl;
            discardedDeck.push(question->question, question->answer, question->score);
            discardedDeck.Display();
        }
    }
    else if (x == "n") {
        cout << "Alright. Onto the next question!" << endl;
    }
    else {
        cout << "That's not one of the options bro" << endl;
    }
    if (question) {
        cout << "Question: " << question->question << endl;
        // Let's say the player answered correctly
        answeredDeck.push(question->question, question->answer, question->score);
        delete question;  // After moving the question to another deck, we should free the memory of the popped card
    }

    // If the player answered incorrectly
    // discardedDeck.push(question->question, question->answer, question->score);

    // Let's view the top card in the answered deck
    Card* peekedCard = answeredDeck.peek();
    if (peekedCard) {
        cout << "Peeked at answered deck: " << peekedCard->question << endl;
    }

    return 0;
}
*/





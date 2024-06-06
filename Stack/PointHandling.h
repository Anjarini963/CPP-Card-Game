//POINT HANDLING HEADER
#pragma once
#include <string>
#include <iostream>
#include <iostream>
#include <string>
#include <algorithm>  // For sorting
#include <iomanip>

using namespace std;

struct PlayerData {
    string name;
    string questions[3]; // Stores each question
    int scores[3];       // Scores for each question
    int totalScore;      // Accumulated score

    PlayerData(const string& playerName) : name(playerName), totalScore(0) {
        for (int i = 0; i < 3; i++) {
            questions[i] = "";
            scores[i] = 0;
        }
    }

    void recordAnswer(int turn, const string& question, int score) {
        if (turn >= 0 && turn < 3) {
            questions[turn] = question;
            scores[turn] = score;
            totalScore += score;
        }
    }
};

class PlayerList {
private:
    PlayerData** players;
    int capacity;
    int size;

    void resize() {
        int newCapacity = capacity * 2;
        PlayerData** newPlayers = new PlayerData * [newCapacity];
        for (int i = 0; i < size; i++) {
            newPlayers[i] = players[i];
        }
        delete[] players;
        players = newPlayers;
        capacity = newCapacity;
    }

public:
    PlayerList() : capacity(10), size(0) {
        players = new PlayerData * [capacity];
    }

    ~PlayerList() {
        for (int i = 0; i < size; i++) {
            delete players[i];
        }
        delete[] players;
    }

    void addPlayer(const string& name) {
        if (size == capacity) {
            resize();
        }
        players[size++] = new PlayerData(name);
    }

    PlayerData* getPlayer(int index) {
        if (index >= 0 && index < size) {
            return players[index];
        }
        return nullptr;
    }

    void displayScores() const {
        for (int i = 0; i < size; i++) {
            cout << players[i]->name << "'s Total Score: " << players[i]->totalScore << endl;
            for (int j = 0; j < 3; j++) {
                cout << "  Q" << (j + 1) << ": " << players[i]->questions[j] << " (" << players[i]->scores[j] << " points)" << endl;
            }
        }
    }
    void displayWinnersHierarchy() {
        // Sort players directly here before displaying
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (players[j]->totalScore < players[j + 1]->totalScore) {
                    PlayerData* temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }

        // Display the sorted and hierarchically organized winners
        cout << "Displaying Winners Hierarchy:\n";
        int level = 0;
        int levels[] = { 1, 2, 4, 8, 15 }; // Indexes where new levels start
        for (int i = 0; i < size && i < 30; i++) {
            if (i == levels[level]) {
                cout << endl;  // New line for new level
                level++;
            }
            for (int j = 0; j < level; j++) cout << "  ";  // Indent for levels
            cout << i + 1 << "th Winner: " << players[i]->name << ", Score: " << players[i]->totalScore << "\n";
        }
    }
    void displayFormattedScores() const {
        if (size == 0) {
            cout << "No players to display." << endl;
            return;
        }

        // Sorting players based on totalScore in descending order using bubble sort
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (players[j]->totalScore < players[j + 1]->totalScore) {
                    PlayerData* temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }

        // Display header
        cout << left << setw(10) << "Ranking" << setw(20) << "Student"
            << setw(30) << "Round 1" << setw(30) << "Round 2"
            << setw(30) << "Round 3" << setw(15) << "Overall Score" << endl;

        // Display each player's information
        for (int i = 0; i < size; i++) {
            cout << left << setw(10) << i + 1
                << setw(20) << players[i]->name;
            for (int j = 0; j < 3; j++) {
                string question = players[i]->questions[j];
                // Truncate question if too long
                if (question.length() > 20) {
                    question = question.substr(0, 17) + "...";
                }
                cout << setw(30) << question + " (" + to_string(players[i]->scores[j]) + " points)";
            }
            cout << setw(15) << players[i]->totalScore << endl;
        }
    }
    /*
    void displayFormattedScores() const {
        // Bubble sort directly in the players array
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (players[j]->totalScore < players[j + 1]->totalScore) {
                    // Swap players[j] and players[j + 1]
                    PlayerData* temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }

        // Display the sorted scores
        for (int i = 0; i < size; i++) {
            cout << "Player #" << i + 1 << ", " << players[i]->name << ": ";
            for (int j = 0; j < 3; j++) {
                string truncatedQuestion = players[i]->questions[j];
                // Find the position of the first '?' or '.'
                auto pos = truncatedQuestion.find_first_of("?.");

                if (pos != string::npos) {
                    // Truncate the string at the found position + 1 to include the punctuation
                    truncatedQuestion = truncatedQuestion.substr(0, pos + 1);
                }

                cout << "Q" << j + 1 << ": " << truncatedQuestion << " = " << players[i]->scores[j] << " Points";
                if (j < 2) cout << " | ";
            }
            cout << " | Total: " << players[i]->totalScore << endl;
        }
    } */
    void clear() {
        // Delete each dynamically allocated PlayerData object
        for (int i = 0; i < size; i++) {
            delete players[i];
            players[i] = nullptr;  // Set the pointer to nullptr after deleting
        }
        size = 0;  // Reset the size of the list
    }



    bool isEmpty() const {
        return size == 0;
    }
    int searchWinner(const string& name) {
        int maxSearch = (size < 30) ? size : 30;  // Search up to 30 or the size of the list
        for (int i = 0; i < maxSearch; i++) {
            if (players[i]->name == name) {
                return i + 1;  // Return the ranking (1-based index)
            }
        }
        return -1;  // Return -1 if the name is not found within the top 30
    }
};

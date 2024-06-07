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


    void displayWinnersHierarchy() {
        // Sort players by total score in descending order using a bubble sort algorithm
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (players[j]->totalScore < players[j + 1]->totalScore) {
                    PlayerData* temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }

        // Display a hierarchical list of top 30 players, with indentation indicating level
        cout << "Displaying Winners Hierarchy:\n";
        int level = 0;
        int levels[] = { 1, 2, 4, 8, 15 }; // Indices at which new hierarchy levels start
        for (int i = 0; i < size && i < 30; i++) {
            if (i == levels[level]) {
                cout << endl;  // Insert a new line for each new level of the hierarchy
                level++;
            }
            for (int j = 0; j < level; j++) cout << "  ";  // Add indentation based on hierarchy level
            cout << i + 1 << "th Winner: " << players[i]->name << ", Score: " << players[i]->totalScore << "\n";
        }
    }

    void displayFormattedScores() const {
        if (size == 0) {
            cout << "No players to display." << endl;
            return;
        }

        // Sort players by totalScore in descending order for ranking purposes
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (players[j]->totalScore < players[j + 1]->totalScore) {
                    PlayerData* temp = players[j];
                    players[j] = players[j + 1];
                    players[j + 1] = temp;
                }
            }
        }

        // Display a formatted table header for player rankings and scores
        cout << left << setw(10) << "Ranking" << setw(20) << "Student"
            << setw(30) << "Round 1" << setw(30) << "Round 2"
            << setw(30) << "Round 3" << setw(15) << "Overall Score" << endl;

        // Display detailed score information for each player
        for (int i = 0; i < size; i++) {
            cout << left << setw(10) << i + 1
                << setw(20) << players[i]->name;
            for (int j = 0; j < 3; j++) {
                string question = players[i]->questions[j];
                // Ensure the question text fits in the designated column width
                if (question.length() > 20) {
                    question = question.substr(0, 17) + "...";  // Truncate and add ellipsis if too long
                }
                cout << setw(30) << question + " (" + to_string(players[i]->scores[j]) + " points)";
            }
            cout << setw(15) << players[i]->totalScore << endl;
        }
    }
    
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

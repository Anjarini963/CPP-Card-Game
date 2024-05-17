#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace std;

struct Card {
	string question;
	string answer;
	int score;
	Card* next;
	Card(string q, string a, int s, Card* n = nullptr) : question(q), answer(a), score(s), next(n) {}

	string toString() const {
		return "Question: " + question + ", Answer: " + answer + ", Score: " + to_string(score);
	}
};

struct discardedCard {
	string question;
	string answer;
	int score;
	discardedCard* next;
	discardedCard* prev;
	discardedCard(string q, string a, int s): question(q), answer(a), score(s), next(nullptr), prev(nullptr) {}
	string toString() const {
		return "Question: " + question + ", Answer: " + answer + ", Score: " + to_string(score);
	}
};

class CardDeck { //SINGLY LINKED LIST
private:
	Card* top;
public:	
	string question;
	string answer;
	int score;
	CardDeck() : top(nullptr){} //constructor

	//used out-of-line definition for readability
	bool isEmpty() const; //const is used for guaranteeing that calling this method won't change any member variables of the class
	void push(string question, string answer, int score);  
	Card* pop();	
	Card* peek() const; 	
	void Display() const;
	void LoadQuestions();
	bool validateAnswer(Card* card, const string userAnswer);
	~CardDeck();
	//trim function to be removed once question bank is updated
	static void trim(string& str) {
		size_t first = str.find_first_not_of(' ');
		size_t last = str.find_last_not_of(' ');
		if (first == string::npos || last == string::npos) {
			str = "";
		}
		else {
			str = str.substr(first, (last - first + 1));
		}
	}
};
	bool CardDeck::validateAnswer(Card* card, const string userAnswer) {
	return card->answer == userAnswer; // Simple equality check
	
}
	void CardDeck::push(string question, string answer, int score) {
	Card* newCard = new Card(question, answer, score, top);
	top = newCard;
}
	Card* CardDeck::pop() {
	if (isEmpty()) {
		return nullptr;
	}
	Card* temp = top;
	top = top->next;
	temp->next = nullptr;  // Disconnect the card from the deck
	return temp;
}
	Card* CardDeck::peek() const {
	return top;
}
	bool CardDeck::isEmpty() const {
	return top == nullptr;
}
	void CardDeck::Display() const {
	Card* current = top;
	while (current != nullptr) {
		cout << current->question << " -> " << current->answer << endl;
		current = current->next;
	}
	
}
	CardDeck::~CardDeck() {
	while (!isEmpty()) {
		Card* temp = pop();
		delete temp;
	}
}
	void CardDeck::LoadQuestions(){

	// the following until the next comment is question loading algorithm with trim function. To be removed once question bank is updated
	ifstream file("QuestionBank.txt");
	string line;

	if (!file) {
		cerr << "Unable to open file: " << "QuestionBank.txt" << endl;
		return;
	}

	while (getline(file, line)) {
		string question, answer;
		int score;
		istringstream iss(line);

		// First, try to get the question part up to the first comma
		if (!getline(iss, question, ',')) {
			cerr << "Failed to parse question from line: " << line << endl;
			continue; // Skip to the next line
		}

		// Next, try to get the answer part up to the second comma
		if (!getline(iss, answer, ',')) {
			cerr << "Failed to parse answer from line: " << line << endl;
			continue; // Skip to the next line
		}

		// Finally, try to parse the score which is the last part
		string scoreStr;
		if (!getline(iss, scoreStr)) {
			cerr << "Failed to parse score from line: " << line << endl;
			continue; // Skip to the next line
		}
		stringstream scoreStream(scoreStr);
		if (!(scoreStream >> score)) {
			cerr << "Failed to convert score from string to int: " << scoreStr << endl;
			continue;
		}

		// Trim question and answer strings
		trim(question);
		trim(answer); 

		// Use the parsed data
		push(question, answer, score);
	}

	file.close();
	/* This is question loading algorithm without trim, will be used once new question bank is given
	ifstream file("C:\\Users\\abdul\\Documents\\justfortesting\\QuestionBank.txt");
	string line;

	if (!file) {
		cerr << "Unable to open file: " << "QuestionBank.txt" << endl;
		return;
	}

	while (getline(file, line)) {
		string question, answer;
		int score;
		istringstream iss(line);

		// First, try to get the question part up to the first comma
		if (!getline(iss, question, ',')) {
			cerr << "Failed to parse question from line: " << line << endl;
			continue; // Skip to the next line
		}

		// Next, try to get the answer part up to the second comma
		if (!getline(iss, answer, ',')) {
			cerr << "Failed to parse answer from line: " << line << endl;
			continue; // Skip to the next line
		}

		// Finally, try to parse the score which is the last part
		if (!(iss >> score)) {
			cerr << "Failed to parse score from line: " << line << endl;
			continue; // Skip to the next line
		}

		// Use the parsed data
		push(question, answer, score);
	}

	file.close();
	*/
}

class discardeddeck {
	private:
		discardedCard* head;
		discardedCard* tail;

	public:
		discardeddeck() : head(nullptr), tail(nullptr) {}
		void push(string question, string answer, int score);
		discardedCard* pop();
		void display();
		discardedCard* chooseCard(int index);
		bool validateAnswer(discardedCard* card, const string userAnswer);
		~discardeddeck();
	};
	bool discardeddeck::validateAnswer(discardedCard* card, const string userAnswer) {
		return card->answer == userAnswer; // Simple equality check
	}
	void discardeddeck::push(string question, string answer, int score) {
		discardedCard* newCard = new discardedCard(question, answer, score * 0.8);
		if (tail == nullptr) {
			head = tail = newCard;
		}
		else {
			tail->next = newCard;
			newCard->prev = tail;
			tail = newCard;
		}
	}
	void discardeddeck::display() {
		discardedCard* current = head;
		int index = 1;
		while (current != nullptr) {
			cout << index++ << "." << current->question << " (Score : " << current->score << ")" << endl;
			current = current->next;
		}
	}

	discardedCard* discardeddeck::chooseCard(int index) {
		discardedCard* current = head;
		int currentIndex = 1;
		while (current != nullptr && currentIndex < index) {
			current = current->next;
			currentIndex++;
		}
		if (current != nullptr && currentIndex == index) {
			return current;
		}
		return nullptr;
	}
	discardedCard* discardeddeck::pop() {
		if (tail == nullptr) {
			return nullptr; // List is empty
		}
		discardedCard* toRemove = tail;
		if (tail->prev) {
			tail = tail->prev;
			tail->next = nullptr;
		}
		else {
			// This was the last card in the list
			head = tail = nullptr;
		}
		toRemove->prev = nullptr; // Clean up the removed card's pointers
		return toRemove; // Return the removed card
	}
	discardeddeck::~discardeddeck() {
		discardedCard* current = head;
		while (current != nullptr) {
			discardedCard* next = current->next;
			delete current; // Free the memory of the current card
			current = next; // Move to the next card
		}
		head = tail = nullptr; // Ensure the head and tail are set to nullptr
	}






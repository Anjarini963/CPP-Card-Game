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
	discardedCard(string q, string a, int s): question(q), answer(a), score(s) {}
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

		ifstream file("QuestionBank.txt");
		string line;

		if (!file) {
			cerr << "Unable to open file: QuestionBank.txt" << endl;
			return;
		}

		const int maxQuestions = 300; // Maximum number of questions
		string questions[maxQuestions];
		string answers[maxQuestions];
		int scores[maxQuestions];
		int questionCount = 0;

		while (getline(file, line) && questionCount < maxQuestions) {
			string question, answer, scoreStr;
			int score;
			istringstream iss(line);

			if (getline(iss, question, ',') && getline(iss, answer, ',') && getline(iss, scoreStr)) {
				stringstream scoreStream(scoreStr);
				if (scoreStream >> score) {
					// Format and trim question and answer
					string formattedQuestion, formattedAnswer;
					for (char ch : question) {
						formattedQuestion += ch;
						if (ch == '.' || ch == '?') formattedQuestion += '\n';
					}
					for (char ch : answer) {
						formattedAnswer += ch;
						if (ch == '.' || ch == '?') formattedAnswer += '\n';
					}

					// Trimming logic applied here within the LoadQuestions method
					auto trim = [](string& str) {
						size_t first = str.find_first_not_of(' ');
						size_t last = str.find_last_not_of(' ');
						if (first == string::npos || last == string::npos) str = "";
						else str = str.substr(first, (last - first + 1));
					};

					trim(formattedQuestion);
					trim(formattedAnswer);

					questions[questionCount] = formattedQuestion;
					answers[questionCount] = formattedAnswer;
					scores[questionCount] = score;
					questionCount++;
				}
				else {
					cerr << "Failed to convert score from string to int: " << scoreStr << endl;
				}
			}
			else {
				cerr << "Failed to parse line: " << line << endl;
			}
		}

		file.close();

		// Shuffling logic here within the LoadQuestions method
		srand(time(0));
		for (int i = 0; i < questionCount; i++) {
			int j = rand() % questionCount;
			swap(questions[i], questions[j]);
			swap(answers[i], answers[j]);
			swap(scores[i], scores[j]);
		}

		// Pushing shuffled and formatted questions to the deck
		for (int i = 0; i < questionCount; i++) {
			push(questions[i], answers[i], scores[i]);
		}
}

class discardeddeck {
private:
	discardedCard** cards; // Pointer to an array of pointers to discardedCard
	int capacity;
	int size;

	void resize();

public:
	discardeddeck() : cards(new discardedCard* [10]), capacity(10), size(0) {} // Allocate initial capacity as 10 to reduce the amount of resizing.
	~discardeddeck();
	void push(const string& question, const string& answer, int score);
	void remove(int index);
	discardedCard* getCard(int index) const;
	bool isEmpty() const;
	void display() const;
		
	};
	

void discardeddeck::resize() {
	int newCapacity = capacity == 0 ? 1 : capacity * 2;  // Handle initial case when capacity is 0
	discardedCard** newArray = new discardedCard* [newCapacity];
	for (int i = 0; i < size; i++) {  // Correct loop condition
		newArray[i] = cards[i];
	}
	delete[] cards;
	cards = newArray;
	capacity = newCapacity;

}
void discardeddeck::push(const string& question, const string& answer, int score) {
	if (size == capacity) {
		resize();
	}
	// Create a new discardedCard and add it to the array
	cards[size++] = new discardedCard(question, answer, score * 0.8);

}

void discardeddeck::remove(int index) {
	if (index < 0 || index >= size) {
		cout << "Invalid index" << endl;
		return; // Correct placement of return statement.
	}
	delete cards[index];
	for (int i = index; i < size - 1; i++) {
		cards[i] = cards[i + 1];
	}
	size--;
}
discardedCard* discardeddeck::getCard(int index) const {
	if (index < 0 || index >= size) return nullptr;
	return cards[index];

}

bool discardeddeck::isEmpty() const {
	return size == 0;
}

void discardeddeck::display() const {
	for (int i = 0; i < size; i++) {
		cout << i + 1<< "." << cards[i] -> question << " (Score: " << cards[i]->score << ")" << endl;
	}
	
}

discardeddeck::~discardeddeck() {
	for (int i = 0; i < size; i++) {
		delete cards[i];
	}
	delete[] cards;
}






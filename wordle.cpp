#include <stdio.h>
#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <ctime>
#include <random>
using namespace std;

class Wordle {
	protected: string answer;
	protected: string guess;
	protected: int guessnum = 0;
	protected: string* allowed = new string[12972];

	// public: Wordle(){
	// 	word = "crane";
	// };

	// public: Wordle(string input){
	// 	word = input;
	// }

	public: int init(){
		fstream file;
		string word, filename;
		filename = "allowed_words.txt";
		file.open(filename.c_str());
		int i = 0;
		while(file >> word){
			allowed[i] = word;
			i++;
		}
		file.close();
		filename = "possible_words.txt";
		file.open(filename.c_str());
		string* possiblewords = new string[2315];
		i = 0;
		while(file >> word){
			possiblewords[i] = word;
			// cout << word << endl;
			i++;
		}
		default_random_engine e;
		int seed = time(0);
		e.seed(seed);
		int index = e() % 2315;
		answer = possiblewords[index];
		cout << "DEBUGGING = THE WORD IS " << answer << endl;
	}

	protected: int get_valid_guess(){
		bool invalidguess = true;
		string input;
		while(invalidguess){
			// invalidguess = false;
			cout << "Place guess: ";
			cin >> input;
			// if(input.length() != word.length()){
			// 	cout <<"Invalid guess" << endl;
			// 	invalidguess = true;
			// }	
			// for(int i = 0; i < input.length(); i++){
			// 	if(!isalpha(input[i])){
			// 		cout << "Invalid guess" << endl;
			// 		invalidguess = true;
			// 	}
			// }
			for(int i = 0; i < 12972; i++){
				if(input == allowed[i]){
					invalidguess = false;
				}
			}
			if(invalidguess){
				cout << "Invalid guess" << endl;
			}
		}
		guess = input;
		return 0;
	}

	protected: int place_guess(){
		if(guess == answer){
			cout << "You win!" << endl;
			guessnum = -1;
		}
		else {
			cout << guess_compare() << endl;
			guessnum++;
		};
		return guessnum;
	};

	protected: string guess_compare(){
		string guessinfo = "";
		char answerinfo[5];
		strcpy(answerinfo, answer.c_str());
		for(int i = 0; i < guess.length(); i++){
			if(guess[i] == answer[i]){
				guessinfo += '!';
				answerinfo[i] = '!';
			}
			else{
				guessinfo += '0';
				answerinfo[i] = answer[i];
			}
		};
		for(int i = 0; i < guess.length(); i++){
			if(guessinfo[i] != '!'){
				for(int j = 0; j < guess.length(); j++){
					if(guess[i] == answerinfo[j] ){
						guessinfo[i] = '?';
						answerinfo[j] = '?';
						break;
					}
				}
			}
		}
		return guessinfo;
	}

	public: int play(){
		while(guessnum < 6){
			get_valid_guess();
			place_guess();
			if(guessnum == -1){
				return 0;
			}
		}
		cout << "Ran out of guesses. Game Over." << endl;
		return 0;
	};
};

int main(){
	Wordle word = Wordle();
	word.init();
	word.play();
	return 0;
};
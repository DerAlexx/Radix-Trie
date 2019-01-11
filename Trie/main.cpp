//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
// Version     : Alpha v0.1
// Copyright   :
// Description : Main-Program
//============================================================================

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include "Trie.h"

Trie<std::string> baum;
int input();
void insertObject();
void deleteObject();
void eraseAll();
void show();

/**
*  Main Method to work with the Trie.
*/
int main() {
    int eingabe = -1;
    std::string word;
    std::string meaning;
    while (eingabe != 0){
        eingabe = input();
        switch(eingabe){
            case 1:
                using namespace std;
                cout << "Enter the word you wanna insert: ";
                getline(cin, word);
                cout << endl << "Enter the translation of the word : " << "(" << word << ")" << endl;
                getline(cin, meaning);
                try {
                    //baum.insert(Trie<string, char>::createPair(word, "m"));
                    cout << "Added " << word << " to \'Trie\'";
                }catch (...) {
                    cout << "unable to Add a Word";
                }
                cout << endl << endl;
                break;
            case 2:
                using namespace std;
                getline(cin, word);
                try {
                    //baum.erase(word);
                } catch(...) {
                    cout << "Unable to Delete this word" << endl;
                }
                cout << "Deleted " << word << " from the \'Trie\'" << endl << endl;
                break;
            case 3:
                baum.clear();
                using namespace std;
                cout << "You just cleared the \'Trie\'" << endl << endl;
                break;
            case 4:
                //baum.showTrie();
                using namespace std;
                cout << "This is your \'Trie\'. Have fun!" << endl << endl;
                break;
            case 5:
                std::cout << std::boolalpha << "It the \'Trie\' empty? Answer: " <<  baum.empty() << std::noboolalpha << std::endl;
                break;
            case 6:
                std::cout << std::boolalpha << "Find a word " <<  baum.empty() << std::noboolalpha << std::endl; // find geht noch nicht
                using namespace std;
                getline(cin, word);
                break;
            case 7:
                using namespace std;
                cout << "Good by and see you later ...." << endl;
                return 0;
            default:
                using namespace std;
                cout << "Wrong input, please enter another number between 1. - 6." << endl;
                cout << endl << endl;
                break;
        }
    }
    return 0;
}

/**
*  Menu for the Trie.
*/
int input() {
    using namespace std;
    int eingabe;
    cout << "================================= Menu ====================================" << endl;
    cout << "(1) Insert a word " << endl;
    cout << "(2) Delete a word " << endl;
    cout << "(3) Delete the hole \'Trie\' " << endl;
    cout << "(4) Print the hole \'Trie\' " << endl;
    cout << "(5) Check whether the \'Trie\' is empty or not" << endl;
    cout << "(6) Find a word in the \'Trie\' " << endl;
    cout << "(7) Go home and do something else ...." << endl;
    cout << "===========================================================================" << endl;
    cout << "Enter a number: ";
    cin >> eingabe;
    return eingabe;
}

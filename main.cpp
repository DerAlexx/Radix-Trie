//============================================================================
// Name        : main.cpp
// Author      : Alexander M. Westphal / Paul Schroeder / Klaus Riedl
// Version     : Alpha v0.1
// Copyright   :
// Description : Main-Program
//============================================================================

#include <iostream>
#include <typeinfo>
#include <string>
#include <thread>
#include <chrono>
#include <sstream>
#include <stdlib.h>
#include "Trie.h"


Trie<std::string> baum;
int input();

/**
*  Main Method to work with the Trie.
*/
int main() {

    int eingabe = -1;
    std::string word = " ";
    std::string meaning = " ";
    std::basic_string<char> a;
    std::string b;
    while (eingabe != 0){
        eingabe = input();
        switch(eingabe){
            case 1:
                using namespace std;

                cout<<"enter word   ";
                cin>>a;

                cout<<"enter meaning   ";
                cin>>b;
                try {
                    baum.insert(pair<const basic_string<char>,string> (a, b));
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
                    baum.erase(word);
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
                baum.showTrie();
                using namespace std;
                cout << "This is your \'Trie\'. Have fun!" << endl << endl;
                break;
            case 5:
                std::cout << std::boolalpha << "It the \'Trie\' empty? Answer: " <<  baum.empty() << std::noboolalpha << std::endl;
                break;
            case 6:
                std::cout << "Suche Wort: " << std::endl;
                using namespace std;
                getline(cin, word);
                std::cout << "Die Bedeutung des Wortes ist: " << baum.find(word).operator*() << std::endl;
                break;
            case 7:
                using namespace std;
                cout << "Good by and see you later ...." << endl;
                return 0;
            default:
                using namespace std;
                cout << "Wrong input, please enter another number between 1. - 7." << endl;
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

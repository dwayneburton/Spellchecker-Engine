// Including the necessary header files
#include <iostream>
#include <string>
#include "trie.h"
#include <fstream>

int main(){
    // Variable initializations and declarations   
    bool run = true;
    std::string input;
    Trie words;

    // Loop that runs until the user enters the "exit" command
    while (run) {
        // Stores user input
        std::getline(std::cin, input);

        // Inserts all words from "corpus.txt" when the "load" command is entered
        if (input.substr(0,4) == "load") {
            std::ifstream file("corpus.txt");
            std::string word;
            while (file >> word) {
                words.insert(word);
            }
            file.close();
            std::cout << "success" << std::endl;

        // Ends the program when the "exit" command is entered
        } else if (input.substr(0,4) == "exit") {
            run = false;
        
        // If Trie is empty, print "empty 1"; otherwise print "empty 0" when the "empty" command is entered
        } else if (input.substr(0,5) == "empty") {
            if (words.getWordCount()) {
                std::cout << "empty 0" << std::endl;
            } else {
                std::cout << "empty 1" << std::endl;
            }
        
        // Deletes all words from Trie when the "clear" command is entered
        } else if (input.substr(0,5) == "clear") {
            words.clear();
            std::cout << "success" << std::endl;
        
        // Inserts a word into the Trie if it is a new word when the "i" command is entered
        } else if (input[0] == 'i') {
            std::string parameter = input.substr(2, input.substr(2).find(" "));
            if (words.insert(parameter)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }

        // Erases a word from the tries if it exists when the "e" command is entered
        } else if (input[0] == 'e') {
            std::string parameter = input.substr(2, input.substr(2).find(" "));
            if (words.erase(parameter)) {
                std::cout << "success" << std::endl;
            } else {
                std::cout << "failure" << std::endl;
            }
        
        // Prints all words in the Trie when the "p" command is entered
        } else if (input[0] == 'p') {
            words.print();

        // Prints the number of words in the Trie with a given prefix when the "c" command is entered
        } else if (input[0] == 'c') {
            std::string parameter = input.substr(2, input.substr(2).find(" "));
            int counter = words.prefix(parameter);
            if (counter) {
                std::cout << "count is " << counter << std::endl;
            } else {
                std::cout << "not found" << std::endl;
            }

        // Prints the number of words in the Trie when the "size" command is entered
        } else if (input.substr(0,4) == "size") {
            std::cout << "number of words is " << words.getWordCount() << std::endl;

        // Checks if the word is in the Trie; will suggest similar words if possible when the "spellcheck" command is entered
        } else if (input.substr(0,10) == "spellcheck") {
            std::string parameter = input.substr(11, input.substr(11).find(" "));
            words.spellcheck(parameter);
            std::cout << std::endl;
        }
    }
}
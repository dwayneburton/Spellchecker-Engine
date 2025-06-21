// Including the necessary header files
#include "trie.h"
#include <string>
#include <iostream>

// Node constructor that creates a new node and assigns isEndOfWord to false
Node::Node() {
    isEndOfWord = false;
}

// Sets a child at a given index in the array
void Node::setChild(int i, Node* curr) {
    children[i] = curr;
}

// Returns the child at a given index in the array
Node* Node::getChild(int i) {
    return children[i];
}

// Sets isEndOfWord to true or false
void Node::setEndOfWord(bool val) {
    isEndOfWord = val;
    
}

// Returns if the node is the end of a word
bool Node::getEndOfWord() {
    return isEndOfWord;
}

// Checks if the node is a leaf node
bool Node::getIsLeafNode() {
    for (int i = 0; i < 26; i++) {
        if (children[i]) {
            return true;
        }
    }
    return false;
}

// Constructor that creates a root for the Trie
Trie::Trie() {
    root = new Node();
    wordCount = 0;
}

// Destructor that deletes all nodes in the Trie by calling clear()
Trie::~Trie() {
    clear();
    delete root;
}

// Inserts a word into the Trie
bool Trie::insert(std::string &word) {
    Node *curr = root;

    // Loop checking if the current letter of the word should be added to Trie
    for (unsigned int i = 0; i < word.length(); i++) {
        if (!curr->getChild(word[i] - 'A')) {
            curr->setChild(word[i] - 'A', new Node());
        }
        curr = curr->getChild(word[i] - 'A');
    }

    // If the word is already in the Trie, return false
    if (curr->getEndOfWord()) {
        return false;
    }

    // Otherwise set it as an EndOfWord, increment total wordCount, and return true
    curr->setEndOfWord(true);
    wordCount++;
    return true;
}

// Erases a word from the Trie
bool Trie::erase(std::string &word) {
    Node* curr = root;
    bool deleted = false;

    // Calls recursive erase helper function to erase the word
    eraseHelper(curr, word, 0, deleted);

    // If the word was erased, decrement total wordCount and return true; otherwise return false
    if (deleted) {
        wordCount--;
        return true;
    }
    return false;
}

// Recursive helper function for erase
void Trie::eraseHelper(Node* curr, std::string &word, unsigned int length, bool &deleted) {
    // Base Case: If we reach the last character of the word, and it is an EndOfWord, turn unmark as EndOfWord and set deleted to true
    if (length == word.length()) {
        if (curr->getEndOfWord()) {
            curr->setEndOfWord(false);
            deleted = true;
        }
    // Otherwise, keep recursively progressing through all characters of the word
    } else {
        Node* next = curr->getChild(word[length] - 'A');
        if (next) {
            length++;
            eraseHelper(next, word, length, deleted);
            // If deleted was updated to true, we check if we can deallocate the node
            if (deleted && !next->getEndOfWord() && !next->getIsLeafNode()) {
                curr->setChild(word[length - 1] - 'A', nullptr);
                delete next;
                next = nullptr;
            }
        }
    }
}

// Deletes all words in the Trie
void Trie::clear() {
     // Call's recursive clear helper function to delete all words
    clearHelper(root);
    root = new Node();
    wordCount = 0;
}

// Recursive helper function for clear
void Trie::clearHelper(Node* curr) {
    // Progresses through all non-nullptr nodes of the Trie and deletes them recursively
    if (curr) {
        for (int i = 0; i < 26; i++) {
            clearHelper(curr->getChild(i));
        }
        delete curr;
        curr = nullptr;
    }
}

// Prints all words in the Trie
void Trie::print() {
    // Checks to see if Trie is empty
    if (wordCount) {
        // Calls recursive print helper function to print all words in the trie
        std::string word = "";
        printHelper(root, word);
        std::cout << std::endl;
    }
}

// Recursive helper function for print
void Trie::printHelper(Node* curr, std::string &word) {
    // Checks to see if the node is not a nullptr
    if (curr) {
        // If the current word is an EndOfWord, print it
        if (curr->getEndOfWord()) {
            std::cout << word << " ";
        }
        // Progresses through all child nodes of the Trie and prints them recursively if they are EndOfWords
        for (int i = 0; i < 26; i++) {
            if (curr->getChild(i)) {
                Node* nextNode = curr->getChild(i);
                std::string nextWord = word + char('A' + i);
                printHelper(nextNode, nextWord);
            }
        }
    }
}

// Prints the number of words with a given prefix
int Trie::prefix(std::string &prefix) {
    Node *curr = root;
    // Loops through prefix checking if it is in the Trie
    for (unsigned int i = 0; i < prefix.length(); i++) {
        if (!curr->getChild(prefix[i] - 'A')) {
            return 0;
        }
        curr = curr->getChild(prefix[i] - 'A');
    }
    // Calls recursive prefix helper function on a prefix that was found in the Trie
    return prefixHelper(curr);
}

// Recursive helper function for prefix
int Trie::prefixHelper(Node* curr) {
    // Increments the counter by 1 recursively for every EndOfWord found in the subtree of the prefix node
    int counter = 0;
    if (curr->getEndOfWord()) {
        counter += 1;
    }
    for (int i = 0; i < 26; i++) {
        if (curr->getChild(i)) {
            Node *child = curr->getChild(i);
            counter += prefixHelper(child);
        }
    }
    return counter;
}

// Prints "correct", words with maximum prefix or (no output) depending on the scenario
void Trie::spellcheck(std::string &word) {
    Node* curr = root;
    std::string prefix = "";

    // Checks if the first letter of the word is in the Trie
    if (curr->getChild(word[0] - 'A')) {
        // Loops through all letters of a word and prints words with a maximum prefix when the next letter is not in Trie
        for (unsigned int i = 0; i < word.length(); i++) {
            if (!curr->getChild(word[i] - 'A')) {
                printHelper(curr, prefix);
                return;
            }
            prefix += word[i];
            curr = curr->getChild(word[i] - 'A');
        }
        // Prints "correct" if word was in the Trie
        if (curr->getEndOfWord()) {
            std::cout << "correct";
        // Otherwise prints words with that prefix
        } else {
            printHelper(curr, word);
        }
    }
}

// Returns the number of words in the Trie
int Trie::getWordCount() {
    return wordCount;
}
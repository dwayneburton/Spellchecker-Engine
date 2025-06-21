// Including the necessary header files
#include <string>

// Node class definition
class Node {
    // Private member variables
    private:
    Node* children[26]{};   // Array of node pointers where each index represents a letter of the alphabet
    bool isEndOfWord;       // Boolean indicating whether the node is the end of a word

    // Public member functions
    public:
    Node();                             // Constructor that creates a new node
    void setChild(int i, Node* curr);   // Sets a child at a given index in the array
    Node* getChild(int i);              // Returns the child at a given index in the array
    void setEndOfWord(bool val);        // Sets isEndOfWord to true or false
    bool getEndOfWord();                // Returns if the node is the end of a word
    bool getIsLeafNode();               // Checks if the node is a leaf node
};

// Trie class definition
class Trie {
    // Private member variables
    private:
    Node* root;     // Pointer to the root of the Trie
    int wordCount;  // Number of words in the Trie

    // Public member functions
    public:
    Trie();                                             // Constructor that creates a root for the Trie
    ~Trie();                                            // Destructor that deletes all nodes in the Trie
    bool insert(std::string &word);                     // Inserts a word into the Trie
    bool erase(std::string &word);                      // Erases a word from the Trie
    void eraseHelper(Node* curr, std::string &word, unsigned int length, bool &deleted);    // Recursive helper function for erase
    void clear();                                       // Deletes all words in the Trie
    void clearHelper(Node* curr);                       // Recursive helper function for clear
    void print();                                       // Prints all words in the Trie
    void printHelper(Node* curr, std::string &word);    // Recursive helper function for print
    int prefix(std::string &prefix);                    // Prints the number of words with a given prefix
    int prefixHelper(Node* curr);                       // Recursive helper function for prefix
    void spellcheck(std::string &word);                 // Prints "correct", words with maximum prefix or (no output) depending on the scenario
    int getWordCount();                                 // Returns the number of words in the Trie
};
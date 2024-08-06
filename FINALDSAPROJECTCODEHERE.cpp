#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cctype>
using namespace std;
struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;
};
TrieNode* createNode() {
    TrieNode* newNode = new TrieNode;
    newNode->isEndOfWord = false;
    for (int i = 0; i < 26; ++i) {
        newNode->children[i] = nullptr;
    }
    return newNode;
}
void insert(TrieNode* root, const string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        if (!isalpha(ch)) {
            continue; 
        }
        int index = tolower(ch) - 'a'; 
        if (current->children[index] == nullptr) {
            current->children[index] = createNode();
        }
        current = current->children[index];
    }
    current->isEndOfWord = true;
}
bool search(TrieNode* root, const string& word) {
    TrieNode* current = root;
    for (char ch : word) {
        if (!isalpha(ch)) {
            continue; 
        }
        int index = tolower(ch) - 'a'; 
        if (current->children[index] == nullptr) {
            return false; 
        }
        current = current->children[index];
    }
    return current != nullptr && current->isEndOfWord;
}
void performSpellCheck(const string& sentence, TrieNode* dictionary, int& mistakeCount) {
    stringstream ss(sentence);
    string word;
    const int MAX_WORDS = 100; 
    string words[MAX_WORDS];
    string correctedWords[MAX_WORDS];
    bool misspelledFlags[MAX_WORDS];
    int wordCount = 0;

    cout << "\nAnalyzing your sentence for spelling errors...\n";
    while (ss >> word) {
        string cleanWord;
        for (char ch : word) {
            if (isalpha(ch)) {
                cleanWord += tolower(ch);
            }
        }
        words[wordCount] = word;
        if (!cleanWord.empty() && !search(dictionary, cleanWord)) {
            cout << "Misspelled word found: \"" << word << "\"";
            cout << "\nPlease enter the correct spelling: ";
            string correction;
            cin >> correction;
            correctedWords[wordCount] = correction;
            misspelledFlags[wordCount] = true;
            mistakeCount++; // Increment mistake count
        }
        else {
            correctedWords[wordCount] = word;
            misspelledFlags[wordCount] = false;
        }
        wordCount++;
    }
    cout << "\n--------------------------------------------";
    cout << "\nOriginal sentence: " << sentence;
    cout << "\nCorrected sentence: ";
    for (int i = 0; i < wordCount; ++i) {
        cout << correctedWords[i] << " ";
    }
    cout << "\n--------------------------------------------\n";
}
void deleteTrie(TrieNode* root) {
    if (root == nullptr) {
        return;
    }
    for (int i = 0; i < 26; ++i) {
        deleteTrie(root->children[i]);
    }
    delete root;
}
int main() {
    cout << "=========================================================================================================================" << endl;
    cout << "                                                                                                                        " << endl;
    cout << "                                                                                                                        " << endl;
    cout << "                                                                                                                        " << endl;
    cout << "    WW      WW  EEEEEEE  LL       CCCCC     OOOOO     MM     MM  EEEEEEE                                               " << endl;
    cout << "    WW      WW  EE       LL      CC        OO   OO    MMM   MMM  EE          | |                                      " << endl;
    cout << "    WW      WW  EE       LL      CC        OO   OO    MMMM MMMM  EE          | |                                      " << endl;
    cout << "    WW  WW  WW  EEEEE    LL      CC        OO   OO    MM MMM MM  EEEEE       | |                                      " << endl;
    cout << "    WW  WW  WW  EE       LL      CC        OO   OO    MM  M  MM  EE          |_|                                      " << endl;
    cout << "     WWW  WWW   EE       LL      CC        OO   OO    MM     MM  EE          |_|                                      " << endl;
    cout << "      W    W    EEEEEEE  LLLLLL   CCCCC     OOOO      MM     MM  EEEEEEE     (_)                                      " << endl;
    cout << "                                                                                                                        " << endl;
    cout << "                                                                                                                        " << endl;
    cout << "                                                                                                                        " << endl;
    cout << "=========================================================================================================================" << endl;
    cout << endl;
    TrieNode* dictionary = createNode();
    ifstream file("dictionary.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open dictionary file." << endl;
        return 1;
    }
    string word;
    while (file >> word) {
        insert(dictionary, word);
    }
    file.close();
    bool runAgain = true;
    while (runAgain) {
        int mistakeCount = 0; 
        cout << "Please enter a sentence for spell check: ";
        string inputSentence;
        getline(cin, inputSentence);

        performSpellCheck(inputSentence, dictionary, mistakeCount);

        cout << "\nTotal number of mistakes found: " << mistakeCount << "\n";

        char choice;
        cout << "\nWould you like to check another sentence? (y/n): ";
        cin >> choice;
        cin.ignore();  
        if (tolower(choice) != 'y') {
            runAgain = false;
        }

        cout << "------------------------------------\n";
    }
    deleteTrie(dictionary);
    cout << "Thank you for using the Spell Checker Program. Goodbye!\n";
    return 0;
}
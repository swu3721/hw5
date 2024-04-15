#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void generateWords(const std::string& fixed, const std::string& floating, const std::string& alphabet, std::string word, const std::set<std::string>& dict, int index, int numFloating, int numBlank, std::set<std::string>& result);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::set<std::string> result;

    int numBlank = 0;
    for (char c : in) {
        if (c == '-') {
            numBlank++;
        }
    }
    int numFloating = floating.length();
    generateWords(in, floating, alphabet, "", dict, 0, numFloating, numBlank, result);
    return result;
}

// Define any helper functions here
// Generate all combos of words given in (in), floating (floating), and dict, with word being the word generated and result being all words generated
void generateWords(const std::string& in, const std::string& floating, const std::string& alphabet, std::string word, const std::set<std::string>& dict, int index, int numFloating, int numBlank, std::set<std::string>& result) {
    
    
    if (in[index] != '-' && index < in.length()) { //If the current position is fixed
        word = word + in[index];
        generateWords(in, floating, alphabet, word, dict, index + 1, numFloating, numBlank, result);
    }

    if (index == in.length()) { //If the word made is the same length as fixed,
        if (numFloating == 0 && dict.find(word) != dict.end()) { //If the word is found
            result.insert(word);
        }
        return;
    }
    

    for(size_t i = 0; i < floating.size(); i++) {
        word = word + floating[i];
        std::string newFloating = floating;
        newFloating.erase(i, 1);
        generateWords(in, newFloating, alphabet, word, dict, index + 1, numFloating - 1, numBlank - 1, result);
        newFloating.insert(i, 1, floating[i]);
        word.pop_back();
    }

    if (numBlank > numFloating) {
        for (char c : alphabet) {
            word = word + c;
            generateWords(in, floating, alphabet, word, dict, index + 1, numFloating, numBlank - 1, result);
            word.pop_back();
        }
    }
}
/*
 * File: WordLadder.cpp
 * --------------------
 * Name: Casey Mills Davis
 * Section: Robert Hintz
 * This file is the starter project for the word ladder problem
 * on Assignment #2.
 * Finds the shortest word ladder between a start word and a
 * destination word, if a ladder exists.
 */

/* includes */
#include <iostream>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

/* prototypes */
Vector<string> findWordLadder(string startWord, string destWord);

/* module variables */
static const char FIRST_LETTER = 'a';
static const char LAST_LETTER = 'z';

int main() {
    // User interface
    while (true){
        string startWord = getLine("Enter start word (RETURN to quit): ");
        if (startWord == "") break;
        string destWord = getLine("Enter destination word: ");
        Vector<string> wordLadder = findWordLadder(startWord, destWord);
        cout << "Word ladder: ";
        foreach(string word in wordLadder) {
            cout << word << " ";
        }
        cout << endl;
    }
	return 0;
}

Vector<string> findWordLadder(string startWord, string destWord) {
    Lexicon words("EnglishWords.dat");
    Lexicon usedWords;
    usedWords.add(startWord);
    Lexicon sameLengthWords;
    
    // Enqueue the first ladder
    Vector<string> startLadder(1, startWord);
    Queue<Vector<string> > ladderQueue;
    ladderQueue.enqueue(startLadder);
    
    // Restrict search to words of correct length
    foreach (string str in words) {
        if (str.size() == startWord.size()){
            sameLengthWords.add(str);
        }
    }
    
    // Dequeue each ladder and enqueue new ladders (breadth first search!)
    while (!ladderQueue.isEmpty()) {
        
        Vector<string> currentLadder = ladderQueue.dequeue();
        string lastWord = currentLadder[currentLadder.size()-1];
        
        if (lastWord == destWord) {
            return currentLadder;
        }
        
        int i = 0;
        while (i < startWord.size()) {
            for (char j = FIRST_LETTER; j <= LAST_LETTER; j++) {
                
                string testWord = lastWord;
                testWord[i] = j;
                
                if (sameLengthWords.contains(testWord) && !usedWords.contains(testWord)) {
                    Vector<string> newLadder = currentLadder;
                    newLadder += testWord;
                    ladderQueue.enqueue(newLadder);
                    usedWords.add(testWord);
                    
                }
            }
            i++;
        }
        
    }
    
    Vector<string> noLadder(1, "No word ladder found.");
    return noLadder;
}
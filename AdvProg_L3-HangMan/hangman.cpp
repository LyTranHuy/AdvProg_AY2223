#include <iostream>
#include "hangman.h"

using std::string;
using std::vector;
using std::ifstream;
using std::domain_error;
using std::cin;

int generateRandomNumber(const int min, const int max)
{

    return rand() % (max - min + 1) + min;
}

vector<string> readWordListFromFile(const string& filePath)
{
    vector<string> wordList;
    string word;
    ifstream wordFile (filePath);
    if (!wordFile.is_open()) {
        throw domain_error("Unable to open file");
    }

    while (wordFile >> word) {
        wordList.push_back(word);
    }
    wordFile.close();

    return wordList;
}

bool isCharInWord(const char ch, const string& word)
{

    return word.find(ch) != string::npos;
}

string chooseWordFromList(const vector<string>& wordList, int index) 
{

    string answer = wordList.at(index);
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
    return answer;
}

string generateHiddenCharacters(string answerWord){

    string secretWord(answerWord.length(), '-');
    return secretWord;
}

char getInputCharacter() {
    char ch;
    cin >> ch;
    return tolower(ch); 
}

void updateSecretWord(string& secretWord, const char ch, const string& word)
{

    for (int i = 0; i < word.length(); i++) {
        if (word[i] == ch) {
            secretWord[i] = ch;
        }
    }
}

void updateEnteredChars(const char ch, string& chars){

    chars += ch;
}

void updateIncorrectGuess(int& incorrectGuess){

    incorrectGuess++;
}

void processData(const char ch, const string& word, 
                string& secretWord, 
                string& correctChars, 
                int& incorrectGuess, string& incorrectChars)
{
    if (isCharInWord(ch, word)) {
        updateSecretWord(secretWord, ch, word);
        updateEnteredChars(ch, correctChars);
    }
    else {
        updateIncorrectGuess(incorrectGuess);
        updateEnteredChars(ch, incorrectChars);
    }
}

#include <iostream>
#include <string>
#include <map>
#include <cctype>

using namespace std;


struct UserInput {
    string guessLetter;
    string guessType;
    int guessCount;
    string uploadedFileContent;
};


void processGuess(const UserInput& input) {
    
    map<char, int> frequency;
    for (char ch : input.uploadedFileContent) {
        if (isupper(ch)) {
            frequency[ch]++;
        }
    }

    
    if (frequency.empty()) {
        cout << "<p>No uppercase letters found in the uploaded file.</p>" << endl;
        return;
    }

    
    char targetChar = 'A';
    int targetCount = (input.guessType == "max") ? -1 : 1001;

    for (const auto& pair : frequency) {
        if ((input.guessType == "max" && pair.second > targetCount) ||
            (input.guessType == "min" && pair.second < targetCount)) {
            targetChar = pair.first;
            targetCount = pair.second;
        }
    }

    
    cout << "<h2>Guess Result</h2>";
    cout << "<p>Character Frequencies (A-Z):</p><ul>";
    for (const auto& pair : frequency) {
        cout << "<li>" << pair.first << ": " << pair.second << "</li>";
    }
    cout << "</ul>";

    cout << "<p>Correct " << (input.guessType == "max" ? "most" : "least")
         << " frequent character: <strong>" << targetChar << "</strong> ("
         << targetCount << " times)</p>";

    bool correctChar = (input.guessLetter[0] == targetChar);
    bool correctCount = (input.guessCount == targetCount);

    cout << "<p>Your character guess is "
         << (correctChar ? "<span style='color:green;'>correct</span>" : "<span style='color:red;'>incorrect</span>")
         << ".</p>";

    cout << "<p>Your count guess is "
         << (correctCount ? "<span style='color:green;'>correct</span>" : "<span style='color:red;'>incorrect</span>")
         << ".</p>";
}

#include <iostream>
#include <string>
using namespace std;

// Must exactly match the struct in get_validate_input.cpp & function.cpp
// need letter picked, max or min , number guessed, content of file upload
struct UserInput {
    string guessLetter;
    string guessType;
    int    guessCount;
    string uploadedFileContent;
};

// Forward declarations for user input and user guess.
// need to tell compiler to pull input & guess from other files.
UserInput    get_validate_input();
void         processGuess(const UserInput& input);

int main() {
    //need to call get valid input to recieve form fields and file upload content
    UserInput input = get_validate_input();

    // need to communicate with web server that its returning HTML
    // need to write the opening tags of the HTML
    cout << "Content-Type: text/html\r\n\r\n";
    cout << "<!DOCTYPE html>\n"
         << "<html>\n<head>\n"
         << "  <meta charset=\"utf-8\">\n"
         << "  <title>Guess Game Result</title>\n"
         << "</head>\n<body>\n"
         << "  <h1>Guess Game Results</h1>\n";

    //need to call processGuess to check user guess & count letters
    processGuess(input);

    // Close the document
    cout << "</body>\n</html>\n";

    return 0;
}

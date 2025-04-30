#include <iostream>
#include <string>
using namespace std;

// Must exactly match the struct in get_validate_input.cpp & function.cpp
struct UserInput {
    string guessLetter;
    string guessType;
    int    guessCount;
    string uploadedFileContent;
};

// Forward declarations for your two modules:
UserInput    get_validate_input();
void         processGuess(const UserInput& input);

int main() {
    // 1) Read & validate the POST data + file upload
    UserInput input = get_validate_input();

    // 2) Emit CGI header + page start
    cout << "Content-Type: text/html\r\n\r\n";
    cout << "<!DOCTYPE html>\n"
         << "<html>\n<head>\n"
         << "  <meta charset=\"utf-8\">\n"
         << "  <title>Guess Game Result</title>\n"
         << "</head>\n<body>\n"
         << "  <h1>Guess Game Results</h1>\n";

    // 3) Delegate all of the counting / guessing logic & HTML output
    processGuess(input);

    // 4) Close the document
    cout << "</body>\n</html>\n";

    return 0;
}

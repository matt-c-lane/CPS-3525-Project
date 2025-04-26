#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>

using namespace std;

struct UserInput {
    string guessLetter;
    string guessType;
    int guessCount;
    string uploadedFileContent;
};

string extractValue(const string& formData, const string& name) {
    size_t namePos = formData.find("name=\"" + name + "\"");
    if (namePos == string::npos) return "";

    size_t valueStart = formData.find("\r\n\r\n", namePos);
    if (valueStart == string::npos) return "";

    valueStart += 4; // skip the header delimiter
    size_t valueEnd = formData.find("\r\n--", valueStart);

    return formData.substr(valueStart, valueEnd - valueStart);
}

UserInput get_validate_input() {
    UserInput input;
    char* contentLengthStr = getenv("CONTENT_LENGTH");
    char* contentType = getenv("CONTENT_TYPE");

    if (!contentLengthStr || !contentType) {
        cerr << "Missing CONTENT_LENGTH or CONTENT_TYPE." << endl;
        exit(1);
    }

    int contentLength = atoi(contentLengthStr);
    vector<char> buffer(contentLength);
    cin.read(buffer.data(), contentLength);
    string formData(buffer.begin(), buffer.end());

    string letter = extractValue(formData, "guessLetter");
    if (letter.size() != 1 || letter[0] < 'A' || letter[0] > 'Z') {
        cerr << "Invalid guess letter input." << endl;
        exit(1);
    }
    input.guessLetter = letter;

    string type = extractValue(formData, "guessType");
    if (type != "max" && type != "min") {
        cerr << "Invalid guess type. Must be 'max' or 'min'." << endl;
        exit(1);
    }
    input.guessType = type;

    string countStr = extractValue(formData, "guessCount");
    try {
        input.guessCount = stoi(countStr);
        if (input.guessCount < 1 || input.guessCount > 1000) {
            throw out_of_range("Guess out of valid range.");
        }
    } catch (...) {
        cerr << "Invalid guess count." << endl;
        exit(1);
    }

    string fileData = extractValue(formData, "inputFile");
    if (fileData.empty()) {
        cerr << "No file uploaded or invalid file input." << endl;
        exit(1);
    }
    input.uploadedFileContent = fileData;

    return input;
}

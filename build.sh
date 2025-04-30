
g++ -std=c++11 -c main.cpp -o main.o
g++ -std=c++11 -c get_validate_input.cpp -o get_validate_input.o
g++ -std=c++11 -c function.cpp -o function.o


g++ main.o get_validate_input.o function.o -o ~/public_html/cgi-bin/guess_game

chmod 755 ~/public_html/cgi-bin/guess_game

echo "✅ Build complete! Executable is in cgi-bin"


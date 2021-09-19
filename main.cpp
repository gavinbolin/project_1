#include <iostream>
#include <fstream>
#include <string>
#include "Lexer.h"
using namespace std;

int main(int argc, char** argv) {

    Lexer* lexer = new Lexer();

    if (argc != 2) {
        //cout << "usage: " << argv[0] << " input_file" << endl;
        return 1;
    }
    ifstream in(argv[1]);
    if (!in.is_open()) {
        //cout << "File " << argv[1] << " could not be found or opened." << endl;
        return 1;
    }
    string input;
    for (string line; getline(in, line);) {
        input.append(line);
        input.append("\n");
    }
    lexer->Run(input);
    delete lexer;
    return 0;
}
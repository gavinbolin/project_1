#ifndef P1_COMMENTAUTOMATON_H
#define P1_COMMENTAUTOMATON_H
#include "Automaton.h"

class CommentAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        while(input[index] != '\r' && input[index] != EOF){
            inputRead++;
            index++;
        }inputRead+=2;
        newLines++;
        index+=2;
    }
    void S2(const std::string& input) {
        while(input[index] != '|' && input[index+1] != '#'){
            inputRead++;
            index++;
        } inputRead+=2;
    }

public:
    CommentAutomaton() : Automaton(TokenType::COMMENT) {}

    void S0(const std::string& input) { //for loop
        if (input[index] == '#' && input[index+1] == '|') {
            inputRead+=2;
            index+=2;
            S2(input);
        }
        else if (input[index] == '#') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_COMMENTAUTOMATON_H

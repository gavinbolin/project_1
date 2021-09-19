#ifndef P1_STRINGAUTOMATON_H
#define P1_STRINGAUTOMATON_H
#include "Automaton.h"

class StringAutomaton : public Automaton
{
private:
    void S1(const std::string& input) {
        while(input[index] != '\''){
            if (input[index] == '\n')
                newLines++;
            inputRead++;
            index++;
        } inputRead++;
    }

public:
    StringAutomaton() : Automaton(TokenType::STRING) {}

    void S0(const std::string& input) { //for loop
        if (input[index] == '\'') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
};

#endif //P1_STRINGAUTOMATON_H

#include "Lexer.h"
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "CommaAutomaton.h"
#include "PeriodAutomaton.h"
#include "QmarkAutomaton.h"
#include "LeftParenAutomaton.h"
#include "RightParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "AddAutomaton.h"
#include "SchemesAutomaton.h"
#include "FactsAutomaton.h"
#include "RulesAutomaton.h"
#include "QueriesAutomaton.h"
#include "IDAutomaton.h"
#include "StringAutomaton.h"
#include "CommentAutomaton.h"
#include "WhitespaceAutomaton.h"
// ID, String, Comments, Und, EOF

Lexer::Lexer() {
    CreateAutomata();
}

Lexer::~Lexer() {
    //delete automata and token vectors
    // TODO: need to clean up the memory in `automata` and `tokens`
}

void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new QmarkAutomaton());
    automata.push_back(new LeftParenAutomaton());
    automata.push_back(new RightParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new AddAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new IDAutomaton());
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new WhitespaceAutomaton());
    // TODO: Add the other needed automata here
}

void Lexer::Run(std::string& input) {
    // TODO: convert this pseudo-code with the algorithm into actual C++ code
    lineNum = 1;
    while(input.size() > 0) {
        maxRead = 0;
        maxAuto = automata[0];
        for (int i = 0; i < automata.size(); i++) {
            int inputRead = automata[i]->Start(input);
            if (inputRead > maxRead) {
                maxRead = inputRead;
                maxAuto = automata[i];
                lineNum += automata[i]->NewLinesRead();
            }
        }
        if (maxRead > 0) {
            Token *newToken = maxAuto->CreateToken(input.substr(0, maxRead), lineNum-maxAuto->NewLinesRead()); //input string, line num
            if (newToken->notWhite()){
                tokens.push_back(newToken);
            } else {
                delete newToken;
            }
        } else {
            maxRead = 1;
            Token *newToken = new Token(TokenType::UNDEFINED,input.substr(0,1),lineNum); //input string, line num
            tokens.push_back(newToken);
        }
        input.erase(0, maxRead);
    }
    //for loop for vector of tokens
    Token *eofToken = new Token(TokenType::END, "", lineNum);
    tokens.push_back(eofToken);
    for (int i = 0; i < tokens.size(); i++) {
        cout << tokens[i]->toString();
    }
    cout << "Total tokens = " << tokens.size();
}

//loop while input.size() > 0 {
//set maxRead to 0
//set maxAutomaton to the first automaton in automata

// TODO: you need to handle whitespace inbetween tokens

// Here is the "Parallel" part of the algorithm
//   Each automaton runs with the same input
/*foreach automaton in automata {
    inputRead = automaton.Start(input)
    if (inputRead > maxRead) {
        set maxRead to inputRead
        set maxAutomaton to automaton
    }
}*/
// Here is the "Max" part of the algorithm
/*if maxRead > 0 {
    set newToken to maxAutomaton.CreateToken(...)
        increment lineNumber by maxAutomaton.NewLinesRead()
        add newToken to collection of all tokens
}*/
// No automaton accepted input
// Create single character undefined token
/*else {
    set maxRead to 1
        set newToken to a  new undefined Token
        (with first character of input)
        add newToken to collection of all tokens
}
// Update `input` by removing characters read to create Token
remove maxRead characters from input
}
add end of file token to all tokens
*/
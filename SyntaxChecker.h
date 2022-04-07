#ifndef SYNTAXCHECKER_H
#define SYNTAXCHECKER_H

#include "FileProcessor.h"
#include "GenStack.h"

class SyntaxChecker{

    public:

        SyntaxChecker();
        ~SyntaxChecker();

        bool checkDelimiters(string fileInput); // adds delimiters to the stack

        void fileEnd();
        void wrongPair();
        void noErrors();

    private:

        GenStack<char> *newStack;        
        int currentLine;
        char currentChar;

        bool matchingPair(char top, char currChar);
        char getPair(char delimiter);
        bool openDelimiter(char c);
        bool closedDelimiter(char c);

};

#endif
#include "SyntaxChecker.h"
#include "LinkedList.h"
#include "GenStack.h"

SyntaxChecker::SyntaxChecker(){

    newStack = new GenStack<char>();
    currentLine = 1;
    currentChar = '\0';

}

SyntaxChecker::~SyntaxChecker(){

    delete newStack;
}

bool SyntaxChecker::checkDelimiters(string fileInput){

    FileProcessor *fileProcessor = new FileProcessor();
    string fileContents = fileProcessor->processFile(fileInput);

    //iterates through each character in the file
    for (int i = 0; i < fileContents.size(); i++){

        currentChar = fileContents[i];

        //counts which line it is on
        if (currentChar == '\n'){

            currentLine++;
        }

        //pushed open delimiter to the stack
        if (openDelimiter(currentChar)){

            newStack->push(currentChar);

        /*
        if the character is a closed delimiter, it will compare.
        first, if the stack is empty, then it means there is a missing open delimiter,
        which will lead to an error

        If the stack is not empty, it will compare (by peeking first) what is on the stack with the corresponing pair
        and if there is no match, it will return an error as well

        if the stack is empty at the end of the file,
        that means there were no errors at all
        */
        } else if (closedDelimiter(currentChar)){

            char tempChar;
            try{

                if (newStack->isEmpty()){

                    cout << "ERROR" << endl;
                    cout << "Line " << currentLine << ": expected " << getPair(currentChar) << " and found " << currentChar <<  endl;
                    currentLine = 1;
                    return false;

                } else {

                    tempChar = newStack->peek();
                    if (matchingPair(tempChar, currentChar)){
                  
                        newStack->pop();
                    
                    } else {

                        wrongPair();
                        currentLine = 1;
                        return false;
                    }
                }
                
            }
            catch (runtime_error &excpt){

                cout << excpt.what() << endl;
                wrongPair();
                currentLine = 1;
                return false;
            }
        }
    }

    if(newStack->isEmpty()){

        noErrors();
        return true;

    } else {

        fileEnd();
        currentLine = 1;
        return false;
    }

    return true;

}

//returns errors that have been found at the end of the file
void SyntaxChecker::fileEnd(){

    char leftOverDelimiter = newStack->peek();
    char missingDelimiter = getPair(leftOverDelimiter);
    cout << "ERROR" << endl;
    cout << "Reached End of File" << endl;
    cout << "Missing: " << missingDelimiter << endl;
}

//compares both delimiters and returns where and what the error was
void SyntaxChecker::wrongPair(){

    char topDelimiter = newStack->peek();
    char expectedDelimiter = getPair(topDelimiter);
    cout << "ERROR" << endl;
    cout << "Line " << currentLine << ": expected " << expectedDelimiter << " and found " << currentChar <<  endl;
}

//no errors
void SyntaxChecker::noErrors(){

    cout << "No errors detected." << endl;
}

//used to compare delimiters
char SyntaxChecker::getPair(char delimiter){

    switch(delimiter) {
        case '(':
            return ')';
        case '[':
            return ']';
        case '{':
            return '}';
        case ')':
            return '(';
        case ']':
            return '[';
        case '}':
            return '{';
        default:
            return '\0';
    }
}

//compares delimiters
bool SyntaxChecker::matchingPair(char top, char currChar){

    return (top == getPair(currChar));
}

bool SyntaxChecker::openDelimiter(char c){

    return (c == '{' || c == '(' || c == '[');
}

bool SyntaxChecker::closedDelimiter(char c){

    return (c == '}' || c == ')' || c == ']');
}
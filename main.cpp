#include "SyntaxChecker.h" 

using namespace std;

int main(int argc, char** argv){

    //creates a new syntax checker object
    SyntaxChecker *newChecker = new SyntaxChecker();

    string answer;
    string file;

    /*
    The if statement checks to see if the command line arguments are valid.
    If it is not valid, it will ask the user to try again.
    If it is valid, it will run the checkDelimiters function on the file.
    It will then ask the user if they wish to check another file and based on their
    response, it will either loop again or end the program.
    */
    if (argv[1] == false){

        cout << "Invalid arguments were passed. Try again." << endl;
    
    } else {

        newChecker->checkDelimiters(argv[1]);

        while (true){

            cout << "Would you like to check another file? [y/n]" << endl;
            cin >> answer;

            if (answer == "y"){

                cout << "Enter the file name: " << endl;
                cin >> file;
                newChecker->checkDelimiters(file);

            } else if (answer == "n"){
                break;

            } else {
                cout << "Invalid response. Try again." << endl;
                break;
            }
        }
    }
    return 0;
}
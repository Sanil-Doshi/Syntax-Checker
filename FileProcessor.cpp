#include "FileProcessor.h"

FileProcessor::FileProcessor(){}

FileProcessor::~FileProcessor(){}

string FileProcessor::processFile(string fileInput){

    string contents = "";
    string newline = "";

    
    try{

        ifstream readFile(fileInput);

        if(!readFile.is_open()){

            throw runtime_error("Error: File does not exist");
        }

        //adds lines to contents
        while(getline(readFile, newline)){
            contents += newline + "\n";
        }

        readFile.close();
    } catch (runtime_error &excpt){
        cout << excpt.what() << endl;
    }

    //returns the contents of the file
    return contents;
}


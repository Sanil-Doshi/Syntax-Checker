#include <iostream>
#include <fstream>
#include <string>
#include <exception>

using namespace std;

class FileProcessor {

public:
  FileProcessor(); //Default Constructor
  ~FileProcessor(); //Destructor


  //method that takes two file names as parameters
  string processFile(string fileInput);

};
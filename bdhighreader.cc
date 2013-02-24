#include <iostream>
#include <fstream>
#include <cstdlib> // EXIT_SUCCESS

#include "bdhighreader.h"



int main (int argc, char* argv[]){
  using namespace std;
  // normally, parameter extraction is more complicated
  cout << argc << " Parameters given" << endl;
  
  std::string fileName;
  if (2==argc){ // one parameter
    fileName = argv[1];
  }else{
    fileName = "test_heroes.prg";
  }
  return bdreader::main(fileName);
}

  
int bdreader::main(std::string inputFile){
  using std::cerr;  using std::endl; using std::cout; 
  std::string inFile;
  { // read input file
    std::ifstream inStream;
    inStream.open(inputFile.c_str());
    if (!inStream.is_open()){
      cerr << "Error opening " << inputFile << endl;
      inStream.close();
      exit(-1);
    }
    unsigned int dataCounter=0;
    while (!inStream.eof()){
      char readChar;
      inStream.get ( readChar );
      inFile+=readChar;
      dataCounter++;
    }
    inStream.close();
    cout << dataCounter << " bytes read" << endl;
  }
  cout << "String contains " << inFile.size() << " chars" << endl;
  
  unsigned int currentScoreEntry;
  for (
    currentScoreEntry  = 0;
    currentScoreEntry  < 10;
    currentScoreEntry++
    )
  {
    unsigned int entryOffset = 0x11E + currentScoreEntry*0x28;
    { // first, print the score
      unsigned int scoreCharIterator;
      for (
        scoreCharIterator  = 0;
        scoreCharIterator < 6; // score has 6 chars
        scoreCharIterator++
        )
      {
        unsigned char curChar = inFile[entryOffset+scoreCharIterator*2];
        cout << hex2char(curChar);
      }
    } // after score
    cout << "  :  ";
    entryOffset += 0xE; // after the score, read the name
    { // name
      unsigned int nameIterator;
      for (
        nameIterator  = 0;
        nameIterator < 10; // name has 10 chars
        nameIterator++
        )
      {
        unsigned char curChar = inFile[entryOffset+nameIterator*2];
        cout << hex2char(curChar);
      }
    } // name
    cout << endl;
  }
  return (EXIT_SUCCESS);
}

char bdreader::hex2char(unsigned char inChar){
  if (
    (inChar >= 0x10) &&
    (inChar < 0x20)
    )
  {
    return (inChar - 0x10+'0');
  }
  if (0x20 == inChar){ return ' '; }
  if (
    (inChar >= 0x21) &&
    (inChar <= 0x3A)
    )
  {
    return (inChar - 0x21 + 'A');
  }
  
  // fallback:
  return '?';
} // hex2char


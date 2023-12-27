#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

int main(int argc, char* argv[]){
  // Initialize variables
  LinkedList list;
  string str = "";

  // Create input and output streams
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");
  
  // string input = "input3.txt";
  // string output = "output3.txt";
  
  ifstream ifs(input);
  ofstream ofs(output); 

  // Process input files
  while(getline(ifs, str)){
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
    if (str.size() == 0) { continue; }
    if (str == "Bar1" || str == "Bar2") { continue; }
    
    list.InsertAtHead(str);
  }

  // cout << "TESTING: Undecoded ID's :" << endl;
  // list.testprint();
  // cout << endl;

  // cout << "TESTING: ID's after Decode()" << endl;
  // list.Decode();
  // list.testprint();
  // cout << endl;

  // cout << "TESTING: ID's after SortAsc():" << endl;
  // list.SortAsc();
  // list.testprint();

  // cout << "TESTING: Outputting decoded ID's to file." << endl;
  // list.print(ofs);

  // cout  << "TESTING: Implimenting the encoding function." << endl;
  // list.Encode();
  // list.TestPrint();
  
  list.Decode();
  list.SortAsc();
  
  list.printGuilty(ofs);

  list.printInnocent(ofs);
  
  ifs.close();
  ofs.close();
}
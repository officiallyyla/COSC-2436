// Lab5 follow alomg during lab

#include "ArgumentManager.h"
#include <fstream>
#include <iostream>
#include <map>
#include <string>
using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  
  int n = 0;
  string str = "";
  map<string, int> m;

  input >> n;

  for (int i = 0; i < n; i++) {
    input >> str;
    m[str]++;
  }

  map<string, int>::iterator itr;
  for (itr = m.begin(); itr != m.end(); itr++) {
    output << itr->first << ": " << itr->second << endl;
  }
  return 0; 
}

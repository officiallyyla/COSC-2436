#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "ArgumentManager.h"
using namespace std;

bool lab1(string str, int lchar, int rchar)
{
  // edge case 
  if(str.length() <= 2){
    return true; 
    
  }

  //base case
  if(lchar >= rchar) {
    return true;
  }
  
  lchar = tolower(str[lchar]);
  rchar = tolower(str[rchar]);

  
  if (!isalpha(lchar)) 
  {
    return lab1(str, lchar + 1, rchar); // recusive case
  }
  
  if (!isalpha(rchar)) 
  {
    return lab1(str, lchar, rchar - 1); // recusive case
  }
  
  if (lchar != rchar) 
  {
    return false; 
  }
  return lab1(str, lchar + 1, rchar - 1); // recursive case
}

int main(int argc, char *argv[]){
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));
  
  string in = "";

  // SEP WORKSHOP GIVEN:
  while(getline(input, in)) {
    in.erase(remove(in.begin(), in.end(), '\n'), in.end());
    in.erase(remove(in.begin(), in.end(), '\r'), in.end());
    in.erase(remove(in.begin(), in.end(), ' '), in.end());
    if (in.size() == 0) continue; 
  } 
  
  getline(input, in);
  
  if(lab1(in, 0, in.length() - 1))
  {
    output << "true";
  }
  else 
  {
    output << "false";
  }
  
  input.close();
  output.close();
  return 0; 
}
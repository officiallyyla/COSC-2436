#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

// Done: Check that the parenthesis are in correct order:
//   Valid: { [ () ] }
//   ● Curly Brackets { } are only enclosed in other curly brackets
//   ● Square Brackets [ ] are only enclosed in either curly or square brackets
//   ● Round Brackets ( ) are enclosed in either curly or square or round brackets

// Done: OutputToFile(...) function

// COMPLETED - Yla & Kelley
bool validParentheses(string exp) {
  stack<char> s;
  for (int i = 0; i < exp.size(); i++) {
    if (exp[i] == '(') {
      s.push(exp[i]);
    } 
    else if (exp[i] == '[') {
      if (s.empty() || s.top() == '{' || s.top() == '[') {
        s.push(exp[i]);
      } else {
        return false;
      }
    } 
    else if (exp[i] == '{') {
      if (s.empty() || s.top() == '{') {
        s.push(exp[i]);
      } else {
        return false;
      }
    } 
    else if (exp[i] == ')') {
      if (s.empty() || s.top() != '(') {
        return false;
      }
      s.pop();
    } 
    else if (exp[i] == ']') {
      if (s.empty() || s.top() != '[')
        return false;
      s.pop();
    } 
    else if (exp[i] == '}') {
      if (s.empty() || s.top() != '{')
        return false;
      s.pop();
    }
  }
  return s.empty();
}

// COMPLETED - Hannah
void OutputToFile(string label, queue<string> q, ofstream &output) {
  if (!q.empty()) {
    output << label << endl;
    while (!q.empty()) {
      output << q.front() << endl;
      q.pop();
    }
  }
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  // string input = "input3.txt";
  // string output = "output3.txt";

  ifstream ifs(input);
  ofstream ofs(output);

  string str;
  queue<string> invalid;
  queue<string> valid;

  while (getline(ifs, str)) {
    str.erase(remove(str.begin(), str.end(), '\n'), str.end());
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
    if (str.size() == 0) {
      continue;
    }
    
    if (validParentheses(str)) {
      valid.push(str);
    }
    else {
      invalid.push(str);
    }
  }

  OutputToFile("Invalid", invalid, ofs);
  OutputToFile("Valid", valid, ofs);
  
  ifs.close();
  ofs.close();
}
  

// Went to TA Office Hours. Sources: Stacks Powerpoint 
// Sources: SEP Workshop Week 6 - Stacks Introduction & Stacks (Infix & Postfix Notation)

#include "ArgumentManager.h"
#include "stack.h"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

int checkOperatorPriority(char op) {
  if (op == '^')
    return 3;
  else if (op == '*' || op == '/')
    return 2;
  else if (op == '+' || op == '-')
    return 1;
  else
    return -1;
}

string infixToPostfix(string infix) {
  Stack s;
  string postfix;
  stringstream ss(infix);
  string word;

  while (ss >> word) {
    if (isdigit(word[0])) {
      postfix += word + " "; // add a space to separate numbers
    } else if (word[0] == '(') {
      s.push(word[0]);
    } else if (word[0] == ')') {
      while (!s.isempty() && s.getTop() != '(') {
        postfix += s.getTop();
        // add a space to separate operands
        postfix += " ";
        s.pop();
      }
      if (!s.isempty())
        s.pop();
    } else {
      while (!s.isempty() && checkOperatorPriority(word[0]) <=
                                 checkOperatorPriority(s.getTop())) {

        postfix += s.getTop();
        // add a space to separate operands
        postfix += " ";
        s.pop();
      }
      s.push(word[0]);
    }
  }
  while (!s.isempty()) {
    postfix += s.getTop();
    // add a space to separate operands
    postfix += " ";
    s.pop();
  }

  return postfix;
}

double evaluatePostfix(string str) {
  Stack s; 
  stringstream ss(str);
  string word;
  while (ss >> word) {
    if (isdigit(word[0])) {
      // convert char to int and push to stack
      s.push(stoi(word));
    } else {
      double firstDigit = s.getTop();
      s.pop();

      double secondDigit = s.getTop();
      s.pop();

      switch (word[0]) {
      case '+':
        s.push(secondDigit + firstDigit);
        break;
      case '-':
        s.push(secondDigit - firstDigit);
        break;
      case '*':
        s.push(secondDigit * firstDigit);
        break;
      case '/':
        s.push(secondDigit / firstDigit);
        break;
      case '^':
        s.push(pow(secondDigit, firstDigit));
        break;
      }
    }
  }

  return s.getTop();
}

double evaluatePrefix(string str) {
  Stack s;
  stringstream ss(str);
  string word;
  while (ss >> word) {
    if (isdigit(word[0])) {
      // convert char to int and push to stack
      s.push(stoi(word));
    } else {
      double secondDigit = s.getTop();
      s.pop();

      double firstDigit = s.getTop();
      s.pop();

      switch (word[0]) {
      case '+':
        s.push(secondDigit + firstDigit);
        break;
      case '-':
        s.push(secondDigit - firstDigit);
        break;
      case '*':
        s.push(secondDigit * firstDigit);
        break;
      case '/':
        s.push(secondDigit / firstDigit);
        break;
      case '^':
        s.push(pow(secondDigit, firstDigit));
        break;
      }
    }
  }

  return s.getTop();
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

   // string input = "input3.txt";
   // string output = "output3.txt";

  ifstream ifs(input);
  ofstream ofs(output);

  bool postfix = false;
  bool infix = false;
  bool prefix = false;

  string expression;

  getline(ifs, input);
    // clean the inputline
    input.erase(remove(input.begin(), input.end(), '\n'), input.end());
    input.erase(remove(input.begin(), input.end(), '\r'), input.end());
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

   
    // cout << input << endl;
    if (input == "postfix") {
      postfix = true;
    } else if (input == "prefix") {
      prefix = true;
    } else if (input == "infix") {
      infix = true;
    } 

   getline(ifs, expression);


  if (postfix) {
    cout << "postfix:" << endl;
    cout << fixed << setprecision(2) << evaluatePostfix(expression) << endl;
    ofs << fixed << setprecision(2) << evaluatePostfix(expression) << endl;
  } else if (prefix) {
    stringstream ss(expression);
    string word;
    string newExpression = "";

    // reverse string
    while (ss >> word) {
      newExpression = word + " " + newExpression;
    }
    cout << newExpression << endl;
    // ofs << newExpression << endl;
    cout << fixed << setprecision(2) << evaluatePrefix(newExpression) << endl;
    ofs << fixed << setprecision(2) << evaluatePrefix(newExpression) << endl;
  } else {
    string postfixy = infixToPostfix(expression);
    ofs << fixed << setprecision(2) << evaluatePostfix(postfixy) << endl;
  }
  return 0;
}
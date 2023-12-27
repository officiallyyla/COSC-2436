// Went to TA Office Hours. Sources: Stacks Powerpoint 
// Sources: SEP Workshop Week 6 - Stacks Introduction & Stacks (Infix & Postfix Notation)

#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <stack>
#include <sstream>
using namespace std;

// must create your own stack structure.
struct Node {
  double data;
  Node *next;
};

class Stack {
private: 
  Node *top;
public:
  Stack() {top = nullptr;}
  bool isempty() {return (top == nullptr);}

void push(double val){
  Node *newNode = new Node;
  newNode->data = val;
  newNode->next = top;
  top = newNode; 
}

void pop(){
  if(top == nullptr){
    return;
  }
  Node *newNode = top;
  top = top->next; 
  delete newNode;
}

double getTop(){
  if(top != nullptr)
    return top->data; 
  return -999;
}
};

#endif
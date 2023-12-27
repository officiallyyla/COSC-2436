/*
RESOURCES: 
2023FA COSC2436 15430 - Programming and Data Structures (Lecture) - Linked Lists
2023FA COSC2436 17453 - Programming and Data Structures (Lab) - Week 3 LinkedList Code Replit. Reference TA's LinkedList Codes
  */
#include <iostream>
#include <string>
using namespace std;

class linkedList {
private:
  struct node {
    int priority;
    string instruction;
    node *next;
  };
  node *head;

public:
  linkedList() : head(nullptr) {}
  string getHead() { return head->instruction; }
  bool isEmpty() { return head == nullptr; }
  // int getSize();
  
  void insertHead(int priority, string instruction) {
    node *newNode = new node;
    newNode->priority = priority;
    newNode->instruction = instruction;

    if (isEmpty()) {
      head = newNode;
    } else {
      newNode->next = head;
      head = newNode;
    }
  }

  void removeHead() {
    node *cur = head;
    if (head->next == nullptr) {
      delete cur;
      head = nullptr;
    }

    else {
      head = head->next;
      delete cur;
    }
  }

  void insertTail(int priority, string instruction) {
    node *newNode = new node;
    newNode->priority = priority;
    newNode->instruction = instruction;

    if (isEmpty()) {
      head = newNode;
    } else {
      node *cur = head;
      while (cur->next != nullptr) {
        cur = cur->next;
      }
      cur->next = newNode;
    }
  }

  void insertPosition(int priority, string instruction) {
    node *newNode = new node;
    newNode->priority = priority;
    newNode->instruction = instruction;

    if (isEmpty()) {
      insertHead(priority, instruction);
    }
    node *tail = head;
    while (tail->next != nullptr) {
      tail = tail->next;
    }

    if (priority < head->priority) {
      insertHead(priority, instruction);
    }

    else if (priority > tail->priority) {
      insertTail(priority, instruction);
    }

    else {
      node *temp = head;
      while (temp != nullptr) {
        if (temp->next != nullptr && priority > temp->priority &&
            priority < temp->next->priority) {
          node *temp1 = temp->next;
          temp->next = newNode;
          newNode->next = temp1;
          break;
        }
        temp = temp->next;
      }
    }
  }

  void print() {
    node *cur = head;
    while (cur != nullptr) {
      cout << cur->instruction << cur->priority << endl;
      cur = cur->next;
    }
  }
};

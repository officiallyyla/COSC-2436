/* 
Resources: 
TA Office Hours hw-3 guide - Alan's.
TA's Replit - Homework3-Help https://replit.com/@EoinDonovan/Homework3-Help
*/
  
#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct node {
  int value;
  node *prev;
  node *next;
  node(int v) {
    value = v;
    prev = nullptr;
    next = nullptr;
  }
};

class LinkedList {
private:
  node *head;
  node *tail;

public:
  LinkedList() { head = nullptr; }
  void isempty() {
    if (head == nullptr) {
      return;
    }
  }

  int getSize() {
    if (head == nullptr) {
      return 0;
    }
    node *cur = head;
    int size = 0;
    while (cur != nullptr) {
      cur = cur->next;
      size++;
    }
    return size;
  }

  void insert(int v) { // Insert at tail
    node *temp = new node(v);
    if (head == nullptr) {
      head = temp;
    } else {
      node *cur = head;
      while (cur->next != nullptr) {
        cur = cur->next;
      }
      cur->next = temp;
      temp->prev = cur;
    }
  }

  // Homewor3-Help replit
  void print(ofstream &ofs) {
    node *cur = head;
    if (head == nullptr) {
      return;
    } else {
      cout << "[";
      ofs << "[";
      while (cur != nullptr) {
        cout << cur->value;
        ofs << cur->value;
        cur = cur->next;
        if (cur != nullptr) {
          cout << ",";
          ofs << ",";
        }
      }
      cout << "]";
      cout << endl;
      ofs << "]";
      ofs << endl;
    }
  }

// TA Hw-3 Guide Help. TA Help 
  void insertionSort(ofstream &ofs) {
    // check if list has one node
    if (head->next == nullptr) {
      print(ofs);
      return;
    }

    node *sorted = head;
    node *unsorted = sorted->next;
    node *insert = unsorted; // insert keeps track of the unsorted's head

    while (unsorted != nullptr) {

      while (sorted != unsorted) {           // just to travers sorted
        if (sorted->value > insert->value) { // is sorted's value greater

          break;
        }
        sorted = sorted->next;
      }

      if (sorted != unsorted) { // do we need to change pointers?
        // need to traverse unsorted before modifying insert's pointers
        unsorted = unsorted->next;

        node *insertprev = sorted->prev;
        if (sorted == head) {
          head = insert;
        }
        if (sorted->prev != nullptr) {
          sorted->prev->next = insert;
        }
        sorted->prev = insert;

        insert->prev->next = insert->next;
        if (insert->next != nullptr) {
          insert->next->prev = insert->prev;
        }

        insert->prev = insertprev;
        insert->next = sorted;

        // update insert
        insert = unsorted;
      }

      else {
        // traversing
        unsorted = unsorted->next;
        insert = unsorted;
      }

      sorted = head;
      print(ofs);
    }
  }

// TA help hw3 - guide
  void selectionSort(ofstream &ofs) {
    if (head == nullptr) {
      return;
    }
    // check if list has one node
    if (head->next == nullptr) {
      print(ofs);
      return;
    }
    int size = getSize(); //Get size
    node *cur = head;
    node *min; // Node *min

    // Outer for loop 
    for (int i = 0; i < size - 1; i++) {
      if (cur == nullptr) {
        return;
      }
      min = cur;
      node *curj = cur->next;
      while (curj != nullptr) {
        if (curj->value < min->value) {
          min = curj;
        }
        curj = curj->next;
      }
      if (cur != min) {
        swap(cur, min);
        cur = min;
      }
      cur = cur->next;
      print(ofs);
      if (cur == nullptr) {
        return;
      }
    }
  }

// Swapping Two Nodes in a linked List 
// Check if one or more nodes are head or tail
// Check if nodes are ajacent 
  void swap(node *a, node *b) {
    node *aPrev = a->prev;
    node *aNext = a->next;
    node *bPrev = b->prev;
    node *bNext = b->next;

    if (a->next == b) {
      if (aPrev != nullptr)
        aPrev->next = b;
      if (bNext != nullptr)
        bNext->prev = a;
      b->prev = aPrev;
      a->next = bNext;
      a->prev = b;
      b->next = a;
    } else {
      if (aPrev != nullptr)
        aPrev->next = b;
      if (aNext != nullptr)
        aNext->prev = b;
      if (bPrev != nullptr)
        bPrev->next = a;
      if (bNext != nullptr)
        bNext->prev = a;
      a->prev = bPrev;
      a->next = bNext;
      b->prev = aPrev;
      b->next = aNext;
    }
    if (head == a) {
      head = b;
    } else if (head == b) {
      head = a;
    }
    if (tail == a) {
      tail = b;
    } else if (tail == b) {
      tail = a;
    }
  }
};

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  // string input = "input3.txt";
  // string output = "output3.txt";

  ifstream ifs(input);
  ofstream ofs(output);

  LinkedList ll;
  int num;

  bool insertion = false;
  bool selection = false;

  getline(ifs, input); // 1 2 3 4
  input.erase(remove(input.begin(), input.end(), '\n'), input.end());
  input.erase(remove(input.begin(), input.end(), '\r'), input.end());
  if (input.empty()) {
    ofs << "Input is invalid.";
    cout << "Input is invalid.";
    return -1;
  }

  string exp;
  getline(ifs, exp);
  exp.erase(remove(exp.begin(), exp.end(), '\n'), exp.end());
  exp.erase(remove(exp.begin(), exp.end(), '\r'), exp.end());
  exp.erase(remove(exp.begin(), exp.end(), ' '), exp.end());
  // cout << input; // reads
  // cout << exp << endl;

  stringstream ss(input);
  string n;
  while (ss >> n) {
    // cout << num;
    num = stoi(n);
    ll.insert(num);
  }

  if (exp == "Selection") {
    selection = true;

  } else if (exp == "Insertion") {
    insertion = true;
  }

  if (selection == true) {
    ll.selectionSort(ofs);
  } else if (insertion == true) {
    // cout << "Insertion";
    ll.insertionSort(ofs);
  } else {
    ofs << "Input is invalid.";
  }

  return 0;
}
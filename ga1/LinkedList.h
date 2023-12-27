#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;

struct Node {
  string ID; 
  Node *next;
  
  Node(string id) {
    this->ID = id;
    next = nullptr;
  }
};

class LinkedList {
private:
  Node* head;
public: 
  LinkedList() { head = nullptr; }

  // Bobbert: Function to encode the ID's

  void TestPrint() {
    Node* curr = head;
    cout << "Encoded IDs: " << endl;
    while (curr != nullptr) {
      cout << curr->ID << endl;
      curr = curr->next;
    }
  }

  void Encode() {
    Node *curr = head;
    while(curr != nullptr) {
        string str = curr->ID;
        str = "(" + reverseStr(str) + ")";

        size_t startPos = 0;
        while((startPos = str.find("(", startPos)) != string::npos) {
            size_t endPos = str.find(")", startPos);
            if(endPos != string::npos) {
                string toReverse = str.substr(startPos + 1, endPos - startPos - 1);
                str.replace(startPos + 1, toReverse.length(), reverseStr(toReverse));
            }
            startPos++;
        }

        curr->ID = str;
        curr = curr->next;
    }
  }


//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^ Bobbert ^^^^^^
 // Function that adds to head of LL
// COMPLETED & TESTED - HANNAH
  void InsertAtHead(string id) {
    Node* temp = new Node(id);
    Node* curr = head;
    
    if (head == nullptr) {
      head = temp;
      return;
    }
    temp->next = head;
    head = temp;
  }

  // Remove an ID from head's list if it is a duplicate
// COMPLETED & TESTED - HANNAH
  void RemoveAtID(string id) {
    if (head == 0) {
      return;
    }
    Node* prev = 0;
    Node* curr = head;
    Node* temp = new Node("");
    while (curr != 0) {
      if (curr->ID == id) {
        if (curr == head) {
          head = head->next;
          delete curr;
        }
        else {
          prev->next = curr->next;
          temp = curr;
          curr = prev;
          delete temp;
        }
      }
      prev = curr;
      curr = curr->next;
    }
  }

  /*// FIXME: Not sorting properly (I think) for case 3
    void SortAsc() { // Kelley: Sort ascending
  	if(head == nullptr || head->next == nullptr){
  		return;
  	}
  	bool isSorted = false;
  	Node *cur = head;
  		while(!isSorted){
  			isSorted = true;
  			cur = head;
  		while(cur->next != nullptr){
  			if(cur->ID > cur->next->ID){
  				string temp = cur->ID;
  				cur->ID = cur->next->ID;
  				cur->next->ID = temp;
  				isSorted = false;
  			}
  			cur = cur->next;
  		}
  		}
  	} */
  
  // COMPLETED & TESTED - KELLEY: Sort ascending
  void SortAsc() {
  	if(head == nullptr || head->next == nullptr){
  		return;
  	}
  	bool isSorted = false;
  	Node *cur = head;
  		while(!isSorted){
  			isSorted = true;
  			cur = head;
  		while(cur->next != nullptr){
  			if(stoi(cur->ID) > stoi(cur->next->ID)){ // stoi: string to integer
  				string temp = cur->ID; 
  				cur->ID = cur->next->ID;
  				cur->next->ID = temp;
  				isSorted = false;
  			}
  			cur = cur->next;
  		}
  	}
  }
  
  // Function to reverse a string (helper function for DecodeIDs)
  string reverseStr(string s) {
    string returnS = "";
    for (int i = s.size() - 1; i >= 0; i--) {
      returnS += s[i];
    }
    return returnS;
  }
  
  // Function to decode all nodes in a list
  void Decode() {
    Node *curr = head;
    string str;
    string substr; // Substring used to decode each inner pair of parenthesis
    int numRevs; // Number of reverses
        
    while (curr != nullptr) {
      str.erase();
      substr.erase();
      str = curr->ID;
      numRevs = 0;
  
      // Count how many reversals we're going to make (# of '(')
      for (int n = 0; n < str.size(); n++) {
        if (str[n] == '(') {
          numRevs++;
        }
      }
    
      // Find the innermost indexes where matching '(' and ')' are
      int open;   // index where '(' is
      int closed; // index where ')' is
    
      // First for-loop, loops until no more reverses need to be made
      for (int i = 0; i < numRevs; i++) {
        // Find the index of the innermost '(' and the matching ')'
        for (int i = 0; i < str.size(); i++) {
          if (str[i] == ')') {
            closed = i;
            break;
          } 
          else if (str[i] == '(') {
            open = i;
          }
        }
      
        // Find the length of the string we're going to reverse (excluding the parenthesis for this part)
        int length = closed - open - 1;
        // Find the substring between the parenthesis (excluding those parenthesis)
        substr = str.substr(open + 1, length);
        // Reverse the substring
        substr = reverseStr(substr);
        // Replace back the new reversed substring into our original string (this time including the parenthesis for replacement)
        str.replace(open, length + 2, substr);
      }
        
      // Replace the current's id with the decoded version, then continue until we reach nullptr
      //cout << "STRING: " << str << endl;
      curr->ID = str;
      curr = curr->next;
    }
  }
  
  // COMPLETED & TESTED - YLA
  void  printInnocent(ofstream &output){
    if(head == nullptr){
      return;
    }
  
    bool isPrinted = false; // to check 
    Node *curr = head;
    while(curr != nullptr){
      int count = 0;
      Node *rurr = head;
      while (rurr != nullptr){
        if(curr->ID == rurr->ID){
          count++;
        }  
        rurr = rurr->next;
    }
      if (count == 1){ // If the ID appears only once.
        if (!isPrinted) { output << "Innocent:\n"; isPrinted = true; }
        output << curr->ID << endl;
      }
      curr = curr->next;
    } 
  }
  
  // COMPLETED & TESTED - YLA
  void  printGuilty(ofstream &output) {
    if(head == nullptr){
      return;
    }
  
    bool isPrinted = false;
    Node *curr = head;
    while(curr != nullptr){
      int count = 0;
      Node *rurr = head;
      while (rurr != nullptr){
        if(curr->ID == rurr->ID){
          count++;
        }  
        rurr = rurr->next;
    }
      if (count > 1){
        if (!isPrinted) { output << "Guilty:\n"; isPrinted = true; }
        output << curr->ID << endl;
        Node *todelete = curr;
        curr = curr->next; 
        RemoveAtID(curr->ID); 
      }
      curr = curr->next;
    }
  }
  
  // COMPLETED & TESTED - YLA
  int getSize(){
    if(head == nullptr){
      return 0;
    }
    Node *cur = head;
    int size = 0; 
    while(cur!= nullptr){
      cur = cur->next; 
      size++; 
    }
     return size;
  }
};

#endif
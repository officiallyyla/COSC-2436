#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <iostream>
#include <fstream>
using namespace std;
/* Code used in Canvas COSC2436 17453 - Programming and Data Stuctures: LinkedListCode (During lab).  */
// Office Hours with Eoin

struct node {
string value;
node *next; 
};

class LinkedList {
  private:
    node *head;
    //int size;
    
  public:  
    LinkedList(){
    head = nullptr; 
    }

    void insertAtHead(string v){
      node *temp = new node;
      temp->value = v;
      temp->next = nullptr;
      
      temp->next = head;
      head = temp; 
      
    }

    void insertAtTail(string v){
      node *temp = new node;
      temp->value = v;
      temp->next = nullptr; 

      if(head == nullptr){
        head = temp;
        return;
      }
      
      node *cur = head;
      while(cur->next != nullptr){
        cur = cur->next;
      }
      cur->next = temp; 
    }

  void insertAtPosition(string v, int p){
    node *temp = new node;
    temp->value = v;
    temp->next = nullptr;
    
    if(p == 0){
      if(head == nullptr){
        head = temp;
      }
      else{
        temp->next = head;
        head = temp;
      }
      return;
    }
    node *cur = head;
    node *prev = nullptr;
    
    for(int i = 0; i < p; i++){
      if(cur == nullptr){
        return;
      }
      prev = cur;
      cur = cur->next;
    }
    if(cur == nullptr){
      return;
    }
    prev->next = temp;
    temp->next = cur;
  }

    void removeAtHead(){
      if(head == nullptr){
        return;
      }
      node *temp = head;
      head = head->next;
      delete temp; 
    } 

    void removeAtTail(){
      if(head == nullptr){
        return;
      }
      else if(head->next == nullptr) {
        node *temp = head;
        head = nullptr;
        delete temp; 
        return;
      }
      node *cur = head;
      node *prev = nullptr;
      while(cur->next != nullptr){
        prev = cur;
        cur = cur->next; 
      }

      prev->next = nullptr; 
      delete cur; 
    }

  void removeAtPosition(int p) {
    if(head == nullptr){
      return;
    }
    else if (p == 0) {
        node *temp = head;
      head = head->next;
      delete temp;
      return; 
    }
    else if (p >= getSize() || p < 0) {
        return;
    } 
        node *cur = head;
        node *prev = nullptr;
        for (int i = 0; i < p; i++) {
            if (cur == nullptr) {
                return;
            }
            prev = cur;
            cur = cur->next;
        }
       if(cur == nullptr){
         return;
       }
            prev->next = cur->next;
            delete cur;
    }


void printHead(ofstream &output){
  if(head != nullptr ){
    output << head->value<< endl; 
  }
}

void printTail(ofstream &output){
  if (head != nullptr) {
    node *current = head;
    // traverse to the end of the LinkedList
    while(current->next != nullptr){
      current = current->next;
    }
    output << current->value << endl;  
  }
}

void printAtPosition(ofstream &output, int p) {
    if(p < 0 || p >= getSize()) {
        cout << "Invalid position!";
        return;
    }
    if(p == 0) {
        printHead(output);
        return;
    }
    node *cur = head;
    for(int i = 0; i < p; i++) {
        if(cur == nullptr) {
            return;
        }    
        cur = cur->next;
    }
    if(cur != nullptr) {
        output << cur->value << "\n";
    }
}

    int getSize(){
      node *cur = head;
      int size = 0; 
      while(cur!= nullptr){
        cur = cur->next; 
        size++; 
      }
      return size;
    }

  void printEntireList(){
    node *cur = head;
    while(cur != nullptr){
      cout << cur->value << " ";
      cur = cur->next;
    }
    cout << endl;
  }
};
#endif
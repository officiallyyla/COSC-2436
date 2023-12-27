// COSC2436 17453 - Programming and Data Structures
// Week 3: Template from hw2 help replit link & LinkedListCode
// Went to office hours

#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct node {
  string name;
  int age;
  float deposit;
  int numDrinks;
  node *next;
  int index;

  node() {
    name = "";
    age = -1;
    deposit = -1;
    numDrinks = -1;
    next = nullptr;
  }

  node(string n, int a, float d, int nDrinks) {
    name = n;
    age = a;
    deposit = d;
    numDrinks = nDrinks;
    next = nullptr;
  }
  
  node(string n, int a, float d, int nDrinks, node *nextNode) {
    name = n;
    age = a; 
    deposit = d;
    numDrinks = nDrinks;
    next = nextNode;
  }
};

class linkedList {
private:
  node *head;
public:
    linkedList() { head = nullptr; }
    node *getHead() { return head; }

    void insertAtHead(node *tempNode) {
      node *newNode = new node(tempNode->name, tempNode->age, tempNode->deposit,
      tempNode->numDrinks);
       if(head == nullptr){
       return;
     }
      newNode->next = head;
      head = newNode;
    }

// use get size for the add method since the problem says index greater than size should add to tail
  void add(string name, int age, float deposit, int numDrinks, int index) {
    node *curr = head;
  while(curr != nullptr){
    if(curr->name == name && curr->age == age){
      curr->deposit = deposit;
      curr->numDrinks = numDrinks;
      return;
    }
    curr = curr->next;
  }
    
    node *tempNode = new node(name, age, deposit, numDrinks);
    int size = getSize();
  
    if(index >=size){
      insertAtEnd(tempNode);
      return;
    }
  
    if (index == 0) {
      if (head == nullptr) {
        head = tempNode;
    } else {
      tempNode->next = head;
      head = tempNode;
    }
    return;
  }
  
  node *prev = nullptr;
  node *cur = head;
  for (int i = 0; i < index; i++) {
    if (cur == nullptr) {
      return;
    }
    prev = cur;
    cur = cur->next;
  }
  if (cur == nullptr) {
    return;
  }

  prev->next = tempNode;
  tempNode->next = cur;
}

    void insertAtEnd(node *tempNode) {
        // do something
        if (head == nullptr) {
          head = tempNode;
          return; 
        } else {
          node *curr = head; 
          
          while (curr->next != nullptr) {
            curr = curr->next;
          }
          curr->next = tempNode;
        }
    } 

    // need to remove EVERY credential with the attribute
/*void remove(string value, string attribute){
  if(head == nullptr){
    return;
  }
  node *temp = head;
  node *prev = nullptr;
  while (temp != nullptr)
  {
    if (temp->name == value){
      node *deleteNode = temp;
      if (prev == nullptr){
        head = head->next;
      } else {
        prev->next = temp->next;
      }
      temp = temp->next;
      delete deleteNode;
    } else {
      prev = temp;
      temp = temp->next;
    }
  }
}*/ 
/* void remove(int value) {
   if(head == nullptr){
    return;
  }
  node *temp = head;
  node *prev = nullptr;
  while (temp != nullptr) {
    if (temp->numDrinks == value) {
      node *deleteNode = temp;
      if (prev == nullptr){
        head = head->next;
      }
      else {
        prev->next = temp->next;
      }
      temp = temp->next;
      delete deleteNode;
    }
    else {
      prev = temp;
      temp = temp->next;
    }
  }
}*/ 

void remove(int value, string &attribute) {
    if (head == nullptr)
        return;

    node *temp = head;
    node *prev = nullptr;

    while (temp != nullptr) {
        if ((attribute == "number of drinks" && temp->numDrinks == value) ||
            (attribute == "age" && temp->age == value) ||
            (attribute == "deposit" && temp->deposit == value)) { 
            
            if (prev == nullptr) { 
                head = head->next;
            } else {
                prev->next = temp->next;
            }
            
            node *deleteNode = temp;
            temp = temp->next;
            delete deleteNode;
        }
        else {
            prev = temp;
            temp = temp->next;
        }
    }
}

    void print(ofstream &output) {
      // do something
      if(head == nullptr){
        return; 
      }
      node *current = head;
      while (current != nullptr) {
        output << "[name: " << current->name 
          << "; age: " << current->age 
          << "; deposit: " << current->deposit
          << "; number of drinks: " << current->numDrinks << "]"<< endl;
        
        current = current->next;
      }
      output.close();
    }

    // More functions
    // for sorting look at example from lab - don't swap the nodes in the linked list, swap the value - TA
   void sortDeposit(){
      node *temp = head;
      while(temp != nullptr){
        node * temp2 = temp->next;
        while(temp2 != nullptr){
          if(temp->deposit > temp2->deposit){
            swap(temp->name, temp2->name);
            swap(temp->age, temp2->age);
            swap(temp->deposit, temp2->deposit);
            swap(temp->numDrinks, temp2->numDrinks);
          }
          temp2 = temp2->next;
        }
        temp = temp->next;
      }
    }

 void sortName(){
      node *temp = head;
      while(temp != nullptr){
        node * temp2 = temp->next;
        while(temp2 != nullptr){
          if(temp->name > temp2->name){
            swap(temp->name, temp2->name);
            swap(temp->age, temp2->age);
            swap(temp->deposit, temp2->deposit);
            swap(temp->numDrinks, temp2->numDrinks);
          }
          temp2 = temp2->next;
        }
        temp = temp->next;
      }
    }

 void sortAge(){
      node *temp = head;
      while(temp != nullptr){
        node * temp2 = temp->next;
        while(temp2 != nullptr){
          if(temp->age > temp2->age){
            swap(temp->name, temp2->name);
            swap(temp->age, temp2->age);
            swap(temp->deposit, temp2->deposit);
            swap(temp->numDrinks, temp2->numDrinks);
          }
          temp2 = temp2->next;
        }
        temp = temp->next;
      }
    }

void sortDrinks(){
      node *temp = head;
      while(temp != nullptr){
        node * temp2 = temp->next;
        while(temp2 != nullptr){
          if(temp->numDrinks > temp2->numDrinks){
            swap(temp->name, temp2->name);
            swap(temp->age, temp2->age);
            swap(temp->deposit, temp2->deposit);
            swap(temp->numDrinks, temp2->numDrinks);
          }
          temp2 = temp2->next;
        }
        temp = temp->next;
      }
    }

      int getSize(){
        if(head == nullptr){
          return 0;
        }
      node *cur = head;
      int size = 0; 
      while(cur!= nullptr){
        cur = cur->next; 
        size++; 
      }
      return size;
    }
};

 

#endif
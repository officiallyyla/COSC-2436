// Code used in Canvas COSC2436 17453 - Programming and Data Structures.
// hw2 help replit link
// Went to office hours. 

#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "ArgumentManager.h"
#include "LinkedList.h"
using namespace std;

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string command = am.get("command");
  string output = am.get("output");
  
  // string input = "input2.txt";
  //string command = "command2.txt";
  //string output = "output2.txt";
  
  ifstream ifs(input);
  ifstream cmd(command);
  ofstream ofs(output); 

  // variables
  string inputline;
  string name;
  int age, nDrinks;
  float deposit;

  linkedList list;

  // Processing the input files
  // [name: Rob; age: 34; deposit: 1234; number of drinks: 1]
  while (getline(ifs, inputline)) {
    // clean the inputline
    inputline.erase(remove(inputline.begin(), inputline.end(), '\n'), inputline.end());
    inputline.erase(remove(inputline.begin(), inputline.end(), '\r'), inputline.end());
    if (inputline.size() == 0) { continue; }
    
    name = inputline.substr(7, inputline.find(';') - 7);
    //cout << name << endl;
    inputline = inputline.substr(inputline.find(';') + 2);
    //cout << "Now inputline is: " << inputline << endl;

    age = stoi(inputline.substr(5, inputline.find(';') - 5));
    inputline = inputline.substr(inputline.find(';') + 2);

    deposit = stof(inputline.substr(9, inputline.find(';') - 9));
    inputline = inputline.substr(inputline.find(';') + 2);

    nDrinks = stoi(inputline.substr(18, inputline.find(']') - 18));
    //cout << nDrinks << endl;
    
    node *temp = new node(name, age, deposit, nDrinks);
    list.insertAtEnd(temp);
  }

  // Move onto processing command files

  while (getline(cmd, command)) {
    string attribute;
    string index; 
    string name;
    string age;
    string deposit;
    string drinks;
    
    if (command.substr(0,3) == "Add") {
      int index = stoi(command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1));
      string toAdd = command.substr(command.find("["), command.find("]")+1);
      name = toAdd.substr(toAdd.find("name: ") + 6, toAdd.find("; age:") - toAdd.find("name: ") - 6);
      age = toAdd.substr(toAdd.find("; age: ") + 7, toAdd.find("; deposit:") - toAdd.find("; age: ") - 7);
      deposit = toAdd.substr(toAdd.find("; deposit: ") + 11, toAdd.find("; number of drinks:") - toAdd.find("; deposit: ") - 11);
      nDrinks = stoi(toAdd.substr(toAdd.find("; number of drinks: ") + 20, toAdd.find("]") - toAdd.find("; number of drinks: ") - 20));

         list.add(name, stoi(age), stof(deposit), nDrinks,  index);

 }
    else if (command.substr(0, 6) == "Remove") {
      string attribute = command.substr(command.find('(') + 1, command.find(":") - command.find('(') - 1);
      string value = command.substr(command.find(':') + 2);
      value = value.substr(0, value.length() - 2);
      list.remove(stoi(value), attribute); 
      }
    else if (command.substr(0, 4) == "Sort") {
      string attribute = command.substr(command.find("(") + 1, command.find(")") - command.find("(") - 1);
      if (attribute == "name") {
        list.sortName();
      }
      else if (attribute == "deposit"){
        list.sortDeposit(); 
      }
      else if(attribute == "age"){
        list.sortAge();
      }
      else{
        list.sortDrinks();
      }
      }
  }
  list.print(ofs);
}
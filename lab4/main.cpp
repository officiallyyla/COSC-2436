/*
Resources: Lab4 - Parsing Help https://replit.com/@EoinDonovan/Lab4-Parsing && TA's. 
  */ 

#include "ArgumentManager.h"
#include "linkedList.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

struct Door {
  bool isOpen;
  bool isLocked;

  Door() : isOpen(false), isLocked(false) {}
};

bool isValidLine(string input) {
  if (input.find('(') == 0)
    return false;
  if (input.find('(') == -1)
    return false;
  return true;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));

  string inputline;
  Door door;
  door.isLocked = false;
  door.isOpen = false;

  linkedList pqueue;

  while (getline(input, inputline)) {
    inputline.erase(remove(inputline.begin(), inputline.end(), '\n'),
                    inputline.end());
    inputline.erase(remove(inputline.begin(), inputline.end(), '\r'),
                    inputline.end());
    inputline.erase(remove(inputline.begin(), inputline.end(), ' '),
                    inputline.end());

    if (isValidLine(inputline)) {
      string instruction = inputline.substr(0, inputline.find('('));
      int priority = stoi(
          inputline.substr(inputline.find('(') + 1, inputline.find(')') - 1));
      pqueue.insertPosition(priority, instruction);
    }
  }

  while (!pqueue.isEmpty()) {
    string instructionToProcess = pqueue.getHead();

    if (door.isLocked) {
      if (instructionToProcess.find("unlock") != -1) {
        door.isLocked = false;
      }
    } else if (!door.isLocked) {
      if (instructionToProcess.find("lock") != -1 &&
          instructionToProcess.find("unlock") == -1) {
        door.isLocked = true;
      } else if (instructionToProcess.find("open") != -1) {
        door.isOpen = true;
      } else if (instructionToProcess.find("close") != -1) {
        door.isOpen = false;
      }
    }
    pqueue.removeHead();
  }

  if (door.isOpen) {
    cout << "the door is open";
    output << "the door is open";
  } else {
    cout << "the door is closed";
    output << "the door is closed";
  }
}
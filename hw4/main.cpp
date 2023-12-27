/* Resources:
Week 8: HastTables (Lab Powerpoint)
Week 8 - Hashing Techniques.pptx (SEP Workshop)
Week 9: HashingPractice (Lab Powerpoint)
 */ 


#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HashTable {
private:
  int tableSize;
  vector<int> table;
  int c1 = 3;
int c2 = 5;

public:
  // Hash Function
  HashTable(int x) {
    tableSize = x;
    table.resize(x);
    for (int i = 0; i < tableSize; i++) {
      table[i] = -1;
    }
  };

  vector<int> &getTable() { return table; }

  int hash(int key) { return key % tableSize; }

  void insert(int &numbers, int size){
    for(int i = 0; i < size; ++i){
      int index = hash(numbers);
      while(table[index] != -1){
        index = (index + 1) % tableSize;
      }
      table[index] = numbers;
    }
  }
  

  bool search(int number) {
    int index = hash(number);
    while (table[index] != -1) {
      if (table[index] == number) {
        return true;
      }
    }
    return false;
  }

  void directHashing(int table[], int x, int tableSize) {
    int index = x % tableSize;
    table[index] = x;
  }

  void linearProbing(int x) {
    for (int i = 0; i < tableSize; i++) {
      int index = ((x % tableSize + i) % tableSize);
      if (table[index] == -1) {
        table[index] = x;
        break;
      }
    }
  }

  void quadraticProbing(int x) {
    for (int i = 0; i < tableSize; i++) {
      int index = ((x % tableSize) + (c1 * i + c2 * i * i)) % tableSize;
      if (table[index] == -1) {
        table[index] = x;
        break;
      }
    }
  }
  // heapify
  void heapify(int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && table[l] < table[largest]) {
      largest = l;
    }
    if (r < n && table[r] < table[largest]) {
      largest = r;
    }
    if (largest != i) {
      int temp = table[largest];
      table[largest] = table[i];
      table[i] = temp;

      heapify(n, largest);
    }
  }

  // heapsort
  void heapSort(int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
      heapify(n, i);
    }
  }
};

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  ifstream ifs(input);
  ofstream ofs(output);

  int size;           // first line
  string probingType; // second line
  string numbers;     // third line

  getline(ifs, numbers);
  istringstream numbersStream(numbers);
  numbersStream >> size;
  // TESTING COMPLETED
  // cout << size << endl;

  HashTable hashtable(size); // calls the class

  string line;

  getline(ifs, line);
  // Remove \n and \r
  input.erase(remove(input.begin(), input.end(), '\n'), input.end());
  input.erase(remove(input.begin(), input.end(), '\r'), input.end());
  input.erase(remove(input.begin(), input.end(), ' '), input.end());

  if (line == "Linear probing") {
    // cout << "Linear probing" << endl;
    string numberStr;
    while (getline(ifs, numberStr, ',')) {
      int number = stoi(numberStr);
      // cout << number;
      hashtable.linearProbing(number);
    }
  } else if (line == "Quadratic probing") {
    string numberStr;
    while (getline(ifs, numberStr, ',')) {
      int number = stoi(numberStr);
      // cout << number;
      hashtable.quadraticProbing(number);
    }
  }

  // the probing type way
  string outputs = "";
  hashtable.getTable();
  for (int i = 0; i < size; i++) {
    outputs += to_string(hashtable.getTable()[i]) + ",";
  }
  ofs << outputs.substr(0, outputs.size() - 1) << endl;

  // heap sort
  hashtable.heapSort(size);
  string outputO;
  for (int i = 0; i < size; i++) {
    outputO += to_string(hashtable.getTable()[i]) + ",";
  }
  ofs << outputO.substr(0, outputs.size() - 1) << endl;

  ifs.close();
  ofs.close();
  return 0;
}

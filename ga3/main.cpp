#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

struct node {
  int value;
  node *left;
  node *right;

  node(int v) {
    value = v;
    left = nullptr;
    right = nullptr;
  }
};

class BST {
public:
  node* root;

  // Constructor for BST, initializing root
  BST() { root = nullptr; }

  // GetRoot function, for the recursion of the insert function
  node *getRoot() { return root; }

  // IMPLEMENT INSERT FUNCTION - Yla
  node *insert(int v, node *&n) { // or void insert(int v, node* &n) {...}
    if (n == nullptr) {
      return new node(v);
    } else if (v < n->value) {
      n->left = insert(v, n->left);
    } else if (v > n->value) {
      n->right = insert(v, n->right);
    }
    return n;
  }

  // Yla -- May or may not need this idk
  void preorder(node *n, vector<int> &v) {
    if (n != nullptr) {
      v.push_back(n->value);
      cout << n->value << " ";
      preorder(n->left, v);
      preorder(n->right, v);
    }
    // else {
    //   cout << endl;
    // }
  }
  
  // IMPLEMENT OUTPUT FUNCTION - Hannah, not tested
  /* TESTED 
  input 1. cout --
  [xllll] 1
  [xllrl] 4

  ANS:
  [x] 9
  [xl] 6
  [xll] 3
  [xlll] 2
  [xllll] 1
  [xllr] 5
  [xllrl] 4
  */
  void output(node *n, string s, ofstream &fout) { 
    // If node is nullptr, return
    if (n == nullptr) {
      return;
    }
    // Else if we reach a leaf, print the "]" and the value
    else if (n->left == nullptr && n->right == nullptr) {
      fout/*cout*/ << s << "] " << n->value << endl;
      return;
    }
    // Check if our node has 2 children
    else if (n->left != nullptr && n->right != nullptr) {
			fout << s << "] " << n->value << endl;
      output(n->left, s + "l", fout);
      output(n->right, s + "r", fout);
    }
    // Else if our node only has a left child, call recursively and add "l" to s
    else if (n->left != nullptr) {
			fout << s << "] " << n->value << endl;
      output(n->left, s + "l", fout);
    }
    // Else if our node only has a right child, call recursively and add "r" to s
    else if (n->right != nullptr) {
			fout << s << "] " << n->value << endl;
      output(n->right, s + "r", fout);
    }
  }
};

int main(int argc, char *argv[]) {
  // Initialize variables
  string nums;
  int number;
  BST bst;

  // Create input and output streams
  ArgumentManager am(argc, argv);
  const string input = am.get("input");
  const string output = am.get("output");

  // const string input = "input1.txt";
  // const string output = "output1.txt";

  ifstream fin(input);
  ofstream fout(output); 
  
  // TESTED - Working :) - Yla and tested by hannah 
  getline(fin, nums);
  nums.erase(remove(nums.begin(), nums.end(), '\n'), nums.end());
  nums.erase(remove(nums.begin(), nums.end(), '\r'), nums.end());
  stringstream ss(nums);
  while(ss >> number){
    bst.root = bst.insert(number, bst.root);
  }

  string s = "[x";
  bst.output(bst.root, s, fout);
  
  fin.close();
  fout.close();
}
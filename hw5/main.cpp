
#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// RESOURCES https://replit.com/@EoinDonovan/AVL
struct node {
  int value;
  node *left;
  node *right;

  node() {
    value = -999;
    left = nullptr;
    right = nullptr;
  }
  node(int v) {
    value = v;
    left = nullptr;
    right = nullptr;
  }
};

// RESOURCES @SEP POWERPOINT
class AVLTree {
private:
  node *root;
  node *insertN(node *root, int value) {
    if (root == nullptr) {
      node *newNode = new node(value);
      return newNode;
    } else if (value < root->value) {
      root->left = insertN(root->left, value);
    } else if (value > root->value) {
      root->right = insertN(root->right, value);
    } else {
      return root;
    }
    int bf = getBalanceFactor(root);
    if (bf > 1 && value < root->left->value) {
      return singleRightRotation(root);
    } else if (bf < -1 && value > root->right->value) {
      return singleLeftRotation(root);
    } else if (bf > 1 && value > root->left->value) {
      root->left = singleLeftRotation(root->left);
      return singleRightRotation(root);
    } else if (bf < -1 && value < root->right->value) {
      root->right = singleRightRotation(root->right);
      return singleLeftRotation(root);
    }
    return root;
  }

public:
  AVLTree() { root = nullptr; }
  string output = "";
  node *getHead() { return root; }
void insert(int value) { root = insertN(root, value); }
 void remove(int value) { root = removeN(root, value); }

  node *removeN(node *nodeN, int value) {
    if (nodeN == nullptr) {
      return nodeN;
    }
    if (value < nodeN->value) {
      nodeN->left = removeN(nodeN->left, value);
    } else if (value > nodeN->value) {
      nodeN->right = removeN(nodeN->right, value);
    } else {
      if (nodeN->left == nullptr) {
        node *temp = nodeN->right;
        delete nodeN;
        return temp;
      } else if (nodeN->right == nullptr) {
        node *temp = nodeN->left;
        delete nodeN;
        return temp;
      }

      node *temp = successor(nodeN);
      nodeN->value = temp->value;
      nodeN->right = removeN(nodeN->right, temp->value);
    }
    return nodeN;
  }

  node *successor(node *nodeN) {
    if (nodeN == nullptr) {
      return nullptr;
    }

    if (nodeN->right == nullptr) {
      return nodeN;
    } else {
      node *temp = nodeN;
      temp = temp->right;
      while (temp->left != nullptr) {
        temp = temp->left;
      }
      return temp;
    }
  }

  int getHeight(node *root) {
    if (root == nullptr)
      return -1;
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return 1 + max(lh, rh);
  }

  int getBalanceFactor(node *root) {
    if (root == nullptr)
      return 0;
    return getHeight(root->left) - getHeight(root->right);
  }

  node *singleLeftRotation(node *root) {
    node *newRoot = root->right;
    node *newRight = newRoot->left;
    newRoot->left = root;
    root->right = newRight;
    return newRoot;
  }

  node *singleRightRotation(node *root) {
    node *newRoot = root->left;
    node *newLeft = newRoot->right;
    newRoot->right = root;
    root->left = newLeft;
    return newRoot;
  }

 
  // ------------------------------------------

// SEP: Week 11 - BST's (Continued) similar function used implementation print insted of BST it is AVL 
  void print(node *nodeN, int lvl) {
    if (nodeN == nullptr)
      return;
    else if (lvl == 0) {
      output += to_string(nodeN->value) + " ";
    } else if (lvl > 0) {
      print(nodeN->left, lvl - 1);
      print(nodeN->right, lvl - 1);
    }
  }
};


int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  // string input = am.get("input");
  // string output = am.get("output");

  ifstream ifs(input);
  ofstream ofs(output);


  AVLTree AVL;
  string line;
  int num;
  string command;

  while (getline(ifs, line)) {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

    // USED SUBSTRING LIKE W/ MY OTHER HWS & LABS

    if (line.length() > 0) {
      command = line.substr(0, line.find('('));
      num = stoi(line.substr(line.find('(') + 1,
                             (line.find(')') - line.find('(')) - 1));
    }

    if (command == "Insert") {
      // cout << "TESTING INSERT: " << num << endl;
      AVL.insert(num);
    }
    else if (command == "Remove") {
      // cout << "TESTING REMOVE " << num << endl;
      AVL.remove(num);
    }
  }

  // LAB 6 -- USED  previously helped by TA -----

  string outputs = "";
  int height = AVL.getHeight(AVL.getHead());

  for (int i = 0; i <= height; i++) {
    AVL.print(AVL.getHead(), i);
    for (int i = 0; i < AVL.output.length(); i++) {
      if (AVL.output[i] != ' ') {
        outputs += AVL.output[i];
      }

      if (AVL.output[i] == ' ' && i == AVL.output.length() - 1) {
        ofs << outputs << endl;
        outputs = "";
      }

      else if (AVL.output[i] == ' ' && AVL.output.length() > 0) {
        ofs << outputs << " ";
        outputs = "";
      }
    }
    AVL.output = "";
  }

  ifs.close();
  ofs.close();
  return 0; 
}
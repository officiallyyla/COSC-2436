/* Resources:
Week 11 - Binary Search Trees -- Powerpoint from SEP Workshop)
Week 11 - BST's (Continued) -- Powerpoint from SEP Workshop
Week 11 - BST.pdf -- Powerpoint from lab 2023FA COSC2436 17453 - Programming and
Data Structures Attended office hours.
*/

#include "ArgumentManager.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

struct TreeNode {
  int data;
  TreeNode *left, *right;
  TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
private:
  TreeNode *root;

  TreeNode *insert(TreeNode *node, int value) {
    if (node == nullptr) {
      return new TreeNode(value);
    } else if (value < node->data) {
      node->left = insert(node->left, value);
    } else if (value > node->data) {
      node->right = insert(node->right, value);
    }
    return node;
  }

  TreeNode *remove(TreeNode *node, int value) {
    if (node == nullptr) {
      return node;
    }
    if (value < node->data) {
      node->left = remove(node->left, value);
    } else if (value > node->data) {
      node->right = remove(node->right, value);
    } else {
      if (node->left == nullptr) {
        TreeNode *temp = node->right;
        delete node;
        return temp;
      } else if (node->right == nullptr) {
        TreeNode *temp = node->left;
        delete node;
        return temp;
      }

      TreeNode *temp = findMin(node->right);
      node->data = temp->data;
      node->right = remove(node->right, temp->data);
    }
    return node;
  }

  TreeNode *findMin(TreeNode *node) {
    TreeNode *current = node;
    while (current && current->left != nullptr) {
      current = current->left;
    }
    return current;
  }

  // Change line 66 to include vector pass by referemce
  void inorder(TreeNode *node, vector<int> &v) const {
    if (node != nullptr) {
      inorder(node->left, v);
      v.push_back(node->data);
      inorder(node->right, v);
    }
  }

  void preorder(TreeNode *node, vector<int> &v) const {
    if (node != nullptr) {
      v.push_back(node->data);
      preorder(node->left, v);
      preorder(node->right, v);
    }
  }

  void postorder(TreeNode *node, vector<int> &v) const {
    if (node != nullptr) {
      postorder(node->left, v);
      postorder(node->right, v);
      v.push_back(node->data);
    }
  }

public:
  BST() : root(nullptr) {}
  TreeNode *getRoot() { return root; }

  void insert(int value) { root = insert(root, value); }
  void remove(int value) { root = remove(root, value); }

  void inorder(vector<int> &v) const { inorder(root, v); }
  void preorder(vector<int> &v) const { preorder(root, v); }
  void postorder(vector<int> &v) const { postorder(root, v); }
};

bool isMatchTraversal(const vector<int> &traversal,
                      const vector<int> &sequence) {
  if (traversal.size() != sequence.size())
    return false;

  for (size_t i = 0; i < traversal.size(); i++) {
    if (traversal[i] != sequence[i])
      return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  string input = am.get("input");
  string output = am.get("output");

  ifstream ifs(input);
  ofstream ofs(output);

  string line, command;
  BST tree;

  while (getline(ifs, line)) {
    line.erase(remove(line.begin(), line.end(), '\n'), line.end());
    line.erase(remove(line.begin(), line.end(), '\r'), line.end());

    if (line == "Insert") {
      string nums;
      int number;
      // adding get line
      getline(ifs, nums);
      nums.erase(remove(nums.begin(), nums.end(), '\n'), nums.end());
      nums.erase(remove(nums.begin(), nums.end(), '\r'), nums.end());
      stringstream ss(nums);
      while (ss >> number) {
        tree.insert(number);
      }
    } else if (line == "Remove") {
      string nums;
      int number;
      // adding get line
      getline(ifs, nums);
      nums.erase(remove(nums.begin(), nums.end(), '\n'), nums.end());
      nums.erase(remove(nums.begin(), nums.end(), '\r'), nums.end());
      stringstream ss(nums);
      while (ss >> number) {
        tree.remove(number);
      }
    } else if (line == "Traverse") {
      // int TraverseStr;
      // ss >> TraverseStr;
      getline(ifs, line);
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());

      stringstream ss(line);
      vector<int> v;
      int number = 0;
      while (ss >> number) {
        v.push_back(number);
      }

      vector<int> inorderTraversal;
      tree.inorder(inorderTraversal); // Call inorder

      vector<int> preorderTraversal;
      tree.preorder(preorderTraversal); // Call preorder

      vector<int> postorderTraversal;
      tree.postorder(postorderTraversal); // Call postorder

      bool inorderMatch = isMatchTraversal(inorderTraversal, v);
      bool preorderMatch = isMatchTraversal(preorderTraversal, v);
      bool postorderMatch = isMatchTraversal(postorderTraversal, v);

      // Output the matching traversal type
      // must only be if statements because we are allowing multiple traversals
      // as output
      if (inorderMatch) {
        ofs << "Inorder" << endl;
      }
      if (preorderMatch) {
        ofs << "Preorder" << endl;
      }
      if (postorderMatch) {
        ofs << "Postorder" << endl;
      }
      if (!inorderMatch && !preorderMatch && !postorderMatch) {
        ofs << "False" << endl; // If no match is found
      }
    }
  }
  ifs.close();
  ofs.close();
  return 0;
}

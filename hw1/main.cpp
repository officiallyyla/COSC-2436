//Given a list of numbers between 0 to 10 as input, you will need to implement a C++ program to recursively find the greatest permutation of the given numbers.
// A TA helped me

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include "ArgumentManager.h"
using namespace std;

void hw1(vector<int>  &container, int size)
{
  if(size <= 1) // base case
  {
    return;
  }
  for(int i = 0; i < size - 1; i++)
  {
    if(container[i] < container[i + 1])
    {
    int temp = container[i];
    container[i] = container[i+1];
    container[i + 1] = temp;
    }
  }
  return hw1(container, size - 1); //recursive function
}


int main(int argc, char *argv[]) {
  ArgumentManager am(argc, argv);
  //ifstream input("input1.txt");
  //ofstream output("output1.txt");
  
  ifstream input(am.get("input"));
  ofstream output(am.get("output"));


    string in = "";
    vector<int> container;

  
    while(getline(input, in)){
      for(int i = 0; i < in.length(); i++){
        if(in[i] == ' ')
          continue;
          else if (in[i] == '1' && in[i + 1] == '0') {
                container.push_back(10); 
                i++; 
          }
        else
          container.push_back(in[i] - '0'); 
      }
    }

    hw1(container, container.size());
  
    for(int i = 0; i < container.size(); i++)
      {
        output << container[i];
      }
  
    input.close();
    output.close();

    return 0;
}

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "LinkedList.h"
#include "ArgumentManager.h"
using namespace std;
// Office Hours: Got help. 

int main(int argc, char *argv[])
{
    ArgumentManager am(argc, argv);
    ifstream input(am.get("input"));  // replace with your input filepath
    ofstream output(am.get("output"));
    //ifstream input("input1.txt");
    //ofstream output("output.txt");

    LinkedList list;
    string line;

    while (getline(input, line))
    {
      line.erase(remove(line.begin(), line.end(), '\n'), line.end());
      line.erase(remove(line.begin(), line.end(), '\r'), line.end());
      if (line.size() == 0) { continue; }
      
        string command;
        // cout << line << endl;
        string location;
        string word;
        stringstream ss(line);

        ss >> command;
        if (command == "Insert")
        {
            ss >> location;

            if (location == "Head")
            {
                ss >> word;
                list.insertAtHead(word);
            }
            else if (location == "Tail")
            {
                ss >> word;
                list.insertAtTail(word);
            }
            else
            {
                int num = stoi(location);
                ss >> word; 
                list.insertAtPosition(word, num);
            }
        }

        else if (command == "Remove")
        {
            ss >> location;
            if (location == "Head")
            {
                list.removeAtHead();
            }
            else if (location == "Tail")
            {
                list.removeAtTail();
            }
          else {
            int num = stoi(location);
            list.removeAtPosition(num);
          }
        }

        else if (command == "Print")
        {
            ss >> location;

            if (location == "[Head]")
            {
                list.printHead(output);
            }
          else if (location == "[Tail]"){
                list.printTail(output);
            }
          else {
            location.erase(remove(location.begin(), location.end(), '['), location.end());
            location.erase(remove(location.begin(), location.end(), ']'), location.end());
            int num = stoi(location);
            list.printAtPosition(output, num);
          }
        }
      list.printEntireList();
    }
    input.close();
    output.close();
    return 0;
}

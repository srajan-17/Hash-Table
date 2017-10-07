/*
 Siddharth Rajan
 CSC 21200
 
 FILE: main.cpp
 This file serves as a way to test the functionality of the hash table sequence class.
 
 */

#include <iostream>
#include "table.h"
using namespace std;
using namespace sid_raj_hw5;

int main() {
    
    table<int> one;
    
    one.put(34, 100);
    cout << "Key, value pair 34, 100 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.put(45, 105);
    cout << "Key, value pair 45, 105 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.put(56, 110);
    cout << "Key, value pair 56, 110 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.put(76, 115);
    cout << "Key, value pair 76, 115 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.put(86, 120);
    cout << "Key, value pair 86, 120 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.put(96, 125);
    cout << "Key, value pair 96, 125 inserted." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.remove(86);
    cout << "Key, value pair with key 86 removed." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.remove(76);
    cout << "Key, value pair with key 76 removed." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    one.remove(45);
    cout << "Key, value pair with key 45 removed." << endl;
    cout << "Table positions used in one: " << one.size() << "\n" << endl;
    
    cout << "The value found with key 34 is " << one.get(34) << ".\n\n";
    
    cout << "The value found with key 96 is " << one.get(96) << ".\n";
    
    
    cout << "\n\n";
    
    return 0;
}

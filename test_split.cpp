/*
CSCI 104: Homework 1 Problem 1

Use this file to test your split.cpp file.

Create linked lists and split them with your split() function.

You can compile this file like this:
g++ split.cpp test_split.cpp -o test_split
*/

#include "split.h"
#include <cstddef>
#include <iostream>

int main(int argc, char* argv[])
{   

    //test a linked list with multiple element
    //create a linked list with elements 7 and 8
    Node* in = new Node(7, new Node(8, NULL)); // {7,8}
    Node* odds = NULL;
    Node* evens = NULL;
    split(in, odds, evens);   
    std::cout << odds->value << std::endl; //should print 7
    std::cout << evens->value << std::endl; //should print 8
}

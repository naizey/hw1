/*
CSCI 104: Homework 1 Problem 1

Write a recursive function to split a sorted singly-linked
list into two sorted linked lists, where one has the even 
numbers and the other contains the odd numbers. Students 
will receive no credit for non-recursive solutions. 
To test your program write a separate .cpp file and #include
split.h.  **Do NOT add main() to this file**.  When you submit
the function below should be the only one in this file.
*/

#include "split.h"
#include <cstddef>

/* Add a prototype for a helper function here if you need */

void split(Node*& in, Node*& odds, Node*& evens)
{
  /* Add code here */
// WRITE YOUR CODE HERE

  //base cases

  //if in list is empty
  if(in == NULL)
  {
    return;
  }
  
  //if in list has one element
  if(in->next == NULL) 
  {
    if(in->value % 2 == 0)
    {
      evens = in; //even and in now point to the same node (the only node in the list in) 
    }
    else
    {
      odds = in; 
    }
    in = NULL; //upon terminating split, in is set to NULL 
    return;
  }

  //recursive case

  Node* next = in->next; //WHY does this work instead of just putting in-> in the recursive call. I was getting segfaults why?  

  //if the value is even
  if(in->value % 2 == 0)
  {
    evens = in;         //point evens to the current node in the list we pull from (in) (they reference the same current node in memory)
    evens->next = NULL; //so the rest of the in values are not included in evens
    split(next, odds, evens->next); //recursive call to fxn (decreasing size of problem)
  }

  //if the value is odd
  else
  {
    odds = in;         //point odds to the current node in the list we pull from
    odds->next = NULL;
    split(next, odds->next, evens); 
  }

}
  

/* If you needed a helper function, write it here */

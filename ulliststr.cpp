#include <cstddef>
#include <stdexcept>
#include "ulliststr.h"

ULListStr::ULListStr() //constructor
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

ULListStr::~ULListStr() //destructor
{
  clear();
}

bool ULListStr::empty() const 
{
  return size_ == 0;
}

size_t ULListStr::size() const
{
  return size_;
}

// WRITE YOUR CODE HERE

void ULListStr::set(size_t loc, const std::string& val)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  *ptr = val;
}

std::string& ULListStr::get(size_t loc)
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

std::string const & ULListStr::get(size_t loc) const
{
  std::string* ptr = getValAtLoc(loc);
  if(ptr == NULL){
    throw std::invalid_argument("Bad location");
  }
  return *ptr;
}

void ULListStr::clear()
{
  while(head_ != NULL){
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}


/**
   * Adds a new value to the back of the list
   *   - MUST RUN in O(1)
*/
void ULListStr::push_back(const std::string& val)
{

  //if list is empty, create a new item and set the first value to val
  if(empty())
  {
    Item* head_ = new Item(); //creates the first item in the empty list
    head_->val[0] = val;
    head_->first = 0;     //updates indexes of first and last
    head_->last = 1;      //last is exclusive
    tail_ = head_;        //tail points to the same node as head (one node)
  }

  //not empty, current tail node has room for more values 
  else if(tail_->last < ARRSIZE)
  {
    tail_->val[tail_->last] = val;  //set the tail nodes last spot to value we want to add
    tail_->last++;                  //renew last index to next spot 
  }

  //not empty, current tail node has NO room for more values. tail_->last == ARRSIZE
  else
  {
    Item* newTail = new Item(); //create a new node to become the new tail_
    newTail->val[0] = val;      //set newTails first index to the val we want to add
    newTail->first = 0;         //update first index
    newTail->last = 1;          //update last index

    //link the new tail to old. Necessary for newTail to know its place in the list
    tail_->next = newTail;      //forward link
    newTail->prev = tail_;      //backward link 

    //assigns new tail
    tail_ = newTail;            
  }

  size_++; //size of list (array values) grows by one
}


/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back()
{
  if(empty())
  {
    return;
  }
  else 
  {
    //if current tail item has more than 1 element
    if(tail_->last - tail_->first > 1) //since first is not always at 0
    {
      tail_->last--;  //voids the legitimacy of the element at the last index (since last is exclusive)
    }
    //if current tail has only 1 element left (what we will remove)
    else
    {
      tail_ = tail_->prev; //tail node is the previous node
      delete tail_->next;  //delete old tail node holding 1 element to remove
    }
  }

  size_--; //size of list (array values) decreases by one
}


/**
 * Adds a new value to the front of the list.
 * If there is room before the 'first' value in
 * the head node add it there, otherwise, 
 * allocate a new head node.
 *   - MUST RUN in O(1)
 */
void ULListStr::push_front(const std::string& val)
{

  //same as push_back empty case
  if(empty())
  {
    head_ = new Item();  
    head_->val[0] = val;
    head_->first = 0;
    head_->last = 1;
    tail_ = head_;
  }

  //if there is room before the first value in the head node
  else if(head_->first > 0)
  {
    head_->first--;                   //move the first index back one
    head_->val[head_->first] = val;   //add the value to the new first index
  }

  //if there is NO room before the first value in the head node
  else
  {
    Item* newHead = new Item();
    newHead->val[ARRSIZE-1] = val;  //add the value to the last index of the new head node. Differs from push_back
    newHead->first = ARRSIZE-1;     
    newHead->last = ARRSIZE; 

    //link the new head to the old
    head_->prev = newHead;          
    newHead->next = head_;          

    //assign new head
    head_ = newHead;             
  }

  size_++;

}



/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front()
{
  if(empty())
  {
    return;
  }
  else
  {
    //if current head node has more than 1 element
    if(head_->last - head_->first > 1) //since the first doesn't always start at 0. First index varies
    {
      head_->first++; //voids the legitimacy of the element at the first index
    }

    //if deleting only value in head node array
    else
    {
      head_ = head_->next; 
      delete head_->prev;
    }
  }

}



/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const
{
  return tail_->val[tail_->last-1];
}


/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const
{
  return head_->val[head_->first];
}


/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  //check if loc is valid (in bounds). No need to check if loc<0 since loc is unsigned integer type (size_t - cannot represent negative values)
  if(loc >= size_)
  {
    return NULL;
  }

  //traverse list starting from head
  Item* node_cntr = new Item();
  node_cntr = head_;

  int index = 0; //counter for when inside the current node

  //traverse list starting from head
  while(index < loc)
  {
    //if the node we are in has more than one element
    if(node_cntr->last - node_cntr->first > 1)
    {
      index++;
    }

    //if the node we are in has only one element
    else
    {
      node_cntr = node_cntr->next; //move to next node while index < loc
      index++;
    }
  }
  
  return &(node_cntr->val[node_cntr->first + (loc - index)]); //return the address of the value at the index we want
  
}

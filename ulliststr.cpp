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

    tail_ = newTail;            //assigns new tail
  }

  size_++; //incerement size of list once 
}


/**
 * Removes a value from the back of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_back()
{

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
  
}



/**
 * Removes a value from the front of the list
 *   - MUST RUN in O(1)
 */
void ULListStr::pop_front()
{


}




/**
 * Returns a const reference to the back element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::back() const
{

}


/**
 * Returns a const reference to the front element
 *   - MUST RUN in O(1)
 */
std::string const & ULListStr::front() const
{

}


/** 
 * Returns a pointer to the item at index, loc,
 *  if loc is valid and NULL otherwise
 *   - MUST RUN in O(n) 
 */
std::string* ULListStr::getValAtLoc(size_t loc) const
{

}

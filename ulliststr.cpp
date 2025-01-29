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
  // If the list is empty
  if(tail_ == nullptr) 
  {
    tail_ = new Item();
    head_ = tail_;
  }

  // If there is space in the current tail item
  if(tail_->last < ARRSIZE) 
  {
    tail_->val[tail_->last] = val;
    tail_->last++;
  }
  else 
  {
    Item* newItem = new Item();
    newItem->val[newItem->last] = val;
    newItem->last++;
    newItem->prev = tail_;
    tail_->next = newItem;
    tail_ = newItem;
  }

  size_++;
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
      Item* temp = tail_;
      tail_ = tail_->prev;

      //if the current iterator on tail is not null, make the next null (for pop_back)
      if(tail_ != nullptr)
      {
        tail_->next = nullptr;
      }
      else
      {
        head_ = nullptr;
      }
      delete temp;
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
      Item* temp = head_;
      head_ = head_->next; 

      //check there is another item after, set the previous to null (for pop_front)
      if(head_ != nullptr)
      {
        head_->prev = nullptr;
      }
      else
      {
        tail_ = nullptr;
      }
      delete temp;
    }
  }

  size_--;
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



// /** 
//  * Returns a pointer to the item at index, loc,
//  *  if loc is valid and NULL otherwise
//  *   - MUST RUN in O(n) 
//  */
std::string* ULListStr::getValAtLoc(size_t loc) const
{
  // Check if loc is valid (in bounds)
  if(loc >= size_)
  {
    return NULL;
  }

  // Traverse the list to find the item containing the element at loc
  Item* current = head_;
  size_t index = loc;

  while(current != NULL)
  {
    size_t item_size = current->last - current->first; //size of the current item array

    if(index < item_size)
    {
      return &current->val[current->first + index];
    }

    //not found 

    //decrease index by the size of the current item array
    index -= item_size; 

    //check next item
    current = current->next; 
  }

  return NULL; // should never be reached if loc is valid
}
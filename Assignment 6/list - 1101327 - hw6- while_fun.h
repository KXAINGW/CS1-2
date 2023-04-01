// list standard header

#ifndef LIST
#define LIST

template< typename ValueType >
struct ListNode // list node
{
   ListNode *next;  // successor node, or first element if head
   ListNode *prev;  // predecessor node, or last element if head
   ValueType myVal; // the stored value, unused if head
};


// CLASS TEMPLATE ListVal
template< typename Ty >
class ListVal
{
public:
   using node = ListNode< Ty >;
   using nodePtr = node *;

   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   ListVal() // initialize data
      : myHead(),
        mySize( 0 )
   {
   }

   nodePtr myHead; // pointer to head node
   size_type mySize; // number of elements
};


// CLASS TEMPLATE list
template< typename Ty >
class list // bidirectional linked list
{
   using node = ListNode< Ty >;
   using nodePtr = node *;
   using ScaryVal = ListVal< Ty >;

public:
   using value_type = Ty;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = node *;
   using const_iterator = const node *;

   // empty container constructor (default constructor)
   // Constructs an empty container, with no elements.
   list()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;
   }

   // fill constructor
   // Constructs a container with "count" elements.
   // Each element is initialized as 0.
   list( size_type count ) // construct list from count * Ty()
      : myData()
   {
      myData.myHead = new node;
      myData.myHead->myVal = Ty();
      myData.myHead->prev = myData.myHead->next = myData.myHead;

      nodePtr temp = myData.myHead;
      for (size_type i = 0; i < count; ++i)
      {
          nodePtr newnode = new node;
          newnode->myVal = Ty();
          temp->next = newnode;
          newnode->prev = temp;
          temp = newnode;
      }
      myData.myHead->prev = temp;
      temp->next = myData.myHead;
      myData.mySize = count;

   }

   // copy constructor
   // Constructs a container with a copy of each of the elements in "right",
   // in the same order.
   list( const list &right )
      : myData()
   {
       // if right.size() == 0
       myData.myHead = new node;
       myData.myHead->myVal = Ty();
       myData.myHead->next = myData.myHead->prev = myData.myHead;

       nodePtr temp = myData.myHead;
       nodePtr temp2 = right.myData.myHead->next;
       for (size_type i = 0; i < right.size(); ++i)
       {
           nodePtr newnode = new node;
           newnode->myVal = temp2->myVal;
           temp2 = temp2->next;
           temp->next = newnode;
           newnode->prev = temp;
           temp = newnode;
       }
       myData.myHead->prev = temp;
       temp->next = myData.myHead;
       myData.mySize = right.size();


   }

   // List destructor
   // Destroys the container object.
   // Deallocates all the storage capacity allocated by the list container.
   ~list()
   {
      clear();
      delete myData.myHead;
   }

   // Assigns new contents to the container, replacing its current contents,
   // and modifying its size accordingly.
   // Copies all the elements from "right" into the container
   // (with "right" preserving its contents).
   list& operator=( const list &right )
   {
      if( this != &right )
      {
          size_type originalSize = myData.mySize;
          myData.mySize = right.myData.mySize;
          nodePtr temp1 = myData.myHead->next;
          nodePtr temp2 = right.myData.myHead->next;
          for (size_type i = 0; i < originalSize; ++i)
          {
              temp1->myVal = temp2->myVal;
              temp1 = temp1->next;
              temp2 = temp2->next;
          }
          temp1 = temp1->prev;
          for (size_type i = originalSize; i < right.size(); ++i)
          {
              nodePtr newnode = new node;
              newnode->myVal = temp2->myVal;
              temp1->next = newnode;
              newnode->prev = temp1;
              temp1 = newnode;
              temp2 = temp2->next;
          }
          myData.myHead->prev = temp1;
          temp1->next = myData.myHead;

      }

      return *this;
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   iterator begin()
   {
      return iterator( myData.myHead->next );
   }

   // Returns an iterator pointing to the first element in the list container.
   // If the container is empty, the returned iterator value shall not be dereferenced.
   const_iterator begin() const
   {
      return const_iterator( myData.myHead->next );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   iterator end()
   {
      return iterator( myData.myHead );
   }

   // Returns an iterator referring to the past-the-end element in the list container.
   // The past-the-end element is the theoretical element
   // that would follow the last element in the list container.
   // It does not point to any element, and thus shall not be dereferenced.
   // If the container is empty, this function returns the same as list::begin.
   const_iterator end() const
   {
      return const_iterator( myData.myHead );
   }

   // Returns the number of elements in the list container.
   size_type size() const
   {
      return myData.mySize;
   }

   // Returns whether the list container is empty (i.e. whether its size is 0).
   bool empty() const
   {
      return myData.mySize == 0;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference front()
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the first element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference front() const
   {
      return myData.myHead->next->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   reference back()
   {
      return myData.myHead->prev->myVal;
   }

   // Returns a reference to the last element in the list container.
   // Calling this function on an empty container causes undefined behavior.
   const_reference back() const
   {
      return myData.myHead->prev->myVal;
   }

   // The container is extended by inserting a new element
   // before the element at the specified position.
   // This effectively increases the list size by the amount of elements inserted.
   // Returns an iterator that points to the newly inserted element.
   iterator insert( const_iterator where, const Ty &val ) // insert val at where
   {
       // try where - myData.myHead->next
       nodePtr temp = myData.myHead;
       while (temp->next != where)
           temp = temp->next;
       nodePtr newnode = new node;
       newnode->myVal = val;
       temp->next->prev = newnode;
       newnode->next = temp->next;
       temp->next = newnode;
       newnode->prev = temp;
       ++myData.mySize;
       return iterator(newnode);



   }

   // Removes from the list container the element at the specified position.
   // This effectively reduces the container size one, which is destroyed.
   // Returns an iterator pointing to the element that followed the element erased.
   // This is the container end if the operation erased the last element in the sequence.
   iterator erase( const_iterator where )
   {       
       nodePtr temp = myData.myHead;
       while (temp->next != where)
           temp = temp->next;
       nodePtr del = temp->next;
       temp->next->next->prev = temp;
       temp->next = temp->next->next;
       --myData.mySize;
       delete del;
       return temp->next;
   }

   // Removes all elements from the list container (which are destroyed),
   // and leaving the container with a size of 0.
   void clear() // erase all
   {
      if( myData.mySize != 0 ) // the list is not empty
      {
          nodePtr temp = myData.myHead->next;
          while (myData.mySize)
              temp = erase(temp);
      }
   }

private:
   ScaryVal myData;
};

// determine if two lists are equal and return true, otherwise return false
template< typename Ty >
bool operator==( const list< Ty > &left, const list< Ty > &right )
{
    if (left.size() != right.size())
        return 0;
    ListNode<Ty>* leftLN = left.begin()->next->prev;
    ListNode<Ty>* rightLN = right.begin()->next->prev;
    for (size_t i = 0; i < left.size(); ++i, leftLN = leftLN->next, rightLN = rightLN->next)
        if (leftLN->myVal != rightLN->myVal)
            return 0;
    return 1;
    

}

template< typename Ty >
bool operator!=( const list< Ty > &left, const list< Ty > &right )
{
   return !( left == right );
}

#endif // LIST
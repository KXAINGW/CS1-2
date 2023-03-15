// string class definition.

#ifndef STRING_H
#define STRING_H

#include <iostream>
using std::ostream;

// CLASS StringVal
class StringVal
{
public:
   using value_type = char;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   StringVal()
      : bx(),
        mySize( 0 ),
        myRes( 15 )
   {
   }

   value_type* myPtr()
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   const value_type* myPtr() const
   {
      if( myRes < 16 )
         return bx.buf;
      else
         return bx.ptr;
   }

   union Bxty // storage for small buffer or pointer to larger one
   {
      value_type buf[ 16 ];
      pointer ptr;
   } bx;

   size_type mySize; // current length of string
   size_type myRes;  // current storage reserved for string
};

class string
{
   using ScaryVal = StringVal;
public:
   using value_type = char;
   using size_type = size_t;
   using difference_type = ptrdiff_t;
   using pointer = value_type *;
   using const_pointer = const value_type *;
   using reference = value_type &;
   using const_reference = const value_type &;

   using iterator = value_type *;
   using const_iterator = const value_type *;

   // the greatest possible value for an element of type size_t ( i.e., 4294967295 )
   static const size_t npos = static_cast< size_type >( -1 );

   // empty string constructor (default constructor)
   // Constructs an empty string, with a length of zero characters.
   string();

   // from buffer
   // Copies the first "count" characters from the array of characters pointed by ptr.
   string( const value_type * const ptr, const size_type count );

   // fill constructor
   // Fills the string with "count" consecutive copies of character ch.
   string( const size_type count, const value_type ch );

   // copy constructor
   // Constructs a copy of "right".
   string( const string &right );

   // String destructor
   // Destroys the string object.
   // Deallocates all the storage capacity allocated by the string.
   ~string();

   // String assignment
   // Assigns a new value to the string, replacing its current contents.
   string& operator=( const string &right );

   // String assignment
   // Assigns a new value to the string, replacing its current contents.
   string& operator=( const value_type * const ptr );

   // Assigns a new value to the string, replacing its current contents.
   // Copies the first count characters from the array of characters pointed by ptr.
//   string& assign( const char *ptr, size_type count );

   // erase elements [off, off + count)
   // Erases the portion of the string value
   // that begins at the character position off and spans count characters
   // (or until the end of the string,
   // if either the content is too short or if count is string::npos.
   // Notice that the default argument erases all characters in the string
   // ( like member function clear ).
   string& erase( size_t off, size_t count = npos );

   // Erases the contents of the string, which becomes an empty string
   // (with a length of 0 characters).
   void clear();

   // If the string is empty, the returned pointer shall not be dereferenced.
   // Returns a pointer pointing to the first character in the string.
   iterator begin();

   // If the string is empty, the returned pointer shall not be dereferenced.
   // Returns a pointer pointing to the first character in the string.
   const_iterator begin() const;

   // Returns a pointer pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character that
   // would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   iterator end();

   // Returns a pointer pointing to the past-the-end character of the string.
   // The past-the-end character is a theoretical character that
   // would follow the last character in the string.
   // It shall not be dereferenced.
   // If the object is an empty string, this function returns the same as string::begin.
   const_iterator end() const;

   // Returns a reference to the character at position pos in the string.
   reference operator[]( size_type off );

   // Returns a reference to the character at position pos in the string.
   const_reference operator[]( size_type off ) const;

   const_pointer data() const;

   // Returns the length of the string, in terms of bytes.
   // This is the number of actual bytes that conform the contents of the string,
   // which is not necessarily equal to its storage capacity.
   size_type size() const;

   // Resizes the string to a length of n characters.
   // If n is smaller than the current string length,
   // the current value is shortened to its first n character, removing the characters beyond the nth.
   // If n is greater than the current string length,
   // the current content is extended by inserting at the end as many characters as needed to reach a size of n.
   // The new elements are initialized as copies of null characters.
//   void resize( size_type newSize, const char ch = char() );

   // Searches the string for the first occurrence of the character specified by its arguments.
   // When off is specified, the search only includes characters at or after position off.
   // Returns the position of the first match. If no matches were found, the function returns string::npos.
   size_type find( value_type ch, size_type off = 0 ) const;

   size_type find( const value_type *ptr, size_type off ) const;

   // Returns a newly constructed string object with its value initialized to a copy of a substring of this object.
   // The substring is the portion of the object that starts at character position off and spans count characters
   // (or until the end of the string, whichever comes first).
   string substr( size_type off = 0, size_type count = npos ) const;

   // compare [ 0, size() ) with right for equality
   bool equal( const string &right ) const;

   // Compares the value of the string object to the string object specified by its arguments.
//   int compare( const string& right ) const;

private:
   ScaryVal myData;
}; // end class string

bool operator==( const string &left, const string &right );
bool operator!=( const string &left, const string &right );
ostream& operator<<( ostream &ostr, string &str );

#endif
// string class member-function definitions.

#include <iostream>
using std::cout;

#include "string.h" // string class definition

string::string()
   : myData()
{
}

string::string( const value_type * const ptr, const size_type count )
   : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.mySize > 15)  //Size
        myData.bx.ptr = new value_type[myData.myRes + 1]();
    for (size_type i = 0; i < count; ++i)
        myData.myPtr()[i] = ptr[i];


}

string::string( const size_type count, const value_type ch )
   : myData()
{
    myData.mySize = count;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.mySize > 15)  //Size
        myData.bx.ptr = new value_type[myData.myRes + 1]();
    for (size_type i = 0; i < count; ++i)
        myData.myPtr()[i] = ch;


}

string::string( const string &right )
   : myData()
{
    myData.mySize = right.myData.mySize;
    myData.myRes = (myData.mySize / 16) * 16 + 15;

    if (myData.mySize > 15)  //Size
        myData.bx.ptr = new value_type[myData.myRes + 1]();
    for (size_type i = 0; i < right.myData.mySize; ++i)
        myData.myPtr()[i] = right.myData.myPtr()[i];


}

string::~string()
{
   if( myData.myRes > 15 )
      delete[] myData.bx.ptr;
}

string& string::operator=( const string &right )
{
   if( this != &right )
   {
      if( right.myData.mySize > myData.myRes )
      {
          if (myData.myRes > 15)  // Res
              delete[] myData.bx.ptr;


         myData.myRes = myData.myRes * 3 / 2;
         if( myData.myRes < ( right.myData.mySize / 16 ) * 16 + 15 )
            myData.myRes = ( right.myData.mySize / 16 ) * 16 + 15;

         myData.bx.ptr = new value_type[myData.myRes + 1]();

      }
      for (size_type i = 0; i < right.myData.mySize; ++i)
          myData.myPtr()[i] = right.myData.myPtr()[i];
      myData.mySize = right.myData.mySize;


   }

   return *this;
}

string& string::operator=( const value_type * const ptr )
{
   size_t count = strlen( ptr );
   if( count > 0 )
   {
      if( count > myData.myRes )
      {

          if (myData.myRes > 15)     // Res
              delete[] myData.bx.ptr;

         myData.myRes = myData.myRes * 3 / 2;
         if( myData.myRes < ( count / 16 ) * 16 + 15 )
            myData.myRes = ( count / 16 ) * 16 + 15;

         myData.bx.ptr = new value_type[myData.myRes + 1]();

      }

      for (size_type i = 0; i < count; ++i)
          myData.myPtr()[i] = ptr[i];
      myData.mySize = count;



   }




   return *this;
}

string& string::erase( size_t off, size_t count )
{
   if( off < myData.mySize )
   {       
       /*size_type i = count - 1;
       while (--count != npos)
           myData.myPtr()[off + i - count] = myData.myPtr()[off + i - count + 1];
       myData.myPtr()[off + count] = '\0';*/

       if (count < 0)
           exit(1);
       
       string temp(myData.mySize-count, '\0');
       for (size_t i = 0; i < off; ++i)
           temp.myData.myPtr()[i] = myData.myPtr()[i];
       while (off + count < myData.mySize)
       {
           temp.myData.myPtr()[off+count] = myData.myPtr()[off+count];
           ++off;
       }
       *this = temp;
       return *this;
   }

   return *this;
}

void string::clear()
{
   myData.mySize = 0;
   myData.myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return iterator( myData.myPtr() );
}

string::const_iterator string::begin() const
{
   return const_iterator( myData.myPtr() );
}

string::iterator string::end()
{
   return iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::const_iterator string::end() const
{
   return const_iterator( myData.myPtr() + static_cast< difference_type >( myData.mySize ) );
}

string::reference string::operator[]( size_type off )
{
   // check for off out-of-range error
   if( off > myData.mySize )
   {
      cout << "\nstring subscript out of range\n";
      system( "pause" );
      exit( 1 ); // terminate program; off out of range
   }

   return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_reference string::operator[]( size_type off ) const
{
   // check for off out-of-range error
   if( off > myData.mySize )
   {
      cout << "\nstring subscript out of range\n";
      system( "pause" );
      exit( 1 ); // terminate program; off out of range
   }

   return myData.myPtr()[ off ]; // returns copy of this element
}

string::const_pointer string::data() const
{
   return myData.myPtr();
}

string::size_type string::size() const
{
   return myData.mySize;
}

string::size_type string::find( value_type ch, size_type off ) const
{
    for (size_type i = off; i < myData.mySize; ++i)
        if (myData.myPtr()[i] == ch)
            return i;
    return npos;


}

string::size_type string::find( const value_type *ptr, size_type off ) const
{

    const_iterator it = myData.myPtr();
    for (size_type i = 0; i < myData.mySize; ++i)
    {
        if (it[i] == ptr[0])
        {
            for (size_type j = 1; j < strlen(ptr); ++j)
                if (it[j] != ptr[j])
                    break;
            return i;
        }
    }
    return npos;

}

string string::substr( size_type off, size_type count ) const
{
    string subStr('\0', count);
    for (size_type i = 0; i < count; ++i)
        subStr.myData.myPtr()[i] = myData.myPtr()[i + off];
    return subStr;

}

// compare [ 0, size() ) with right for equality
bool string::equal( const string &right ) const
{
    if (myData.mySize != right.myData.mySize)
        return 0;
    for (size_type i = 0; i < myData.mySize; ++i)
        if (myData.myPtr()[i] != right.myData.myPtr()[i])
            return 0;
    return 1;


}

bool operator==( const string &left, const string &right )
{
   return left.equal( right );
//   return ( lhs.compare( rhs ) == 0 );
}

bool operator!=( const string &left, const string &right )
{
   return !left.equal( right );
}

ostream& operator<<( ostream &ostr, string &str )
{
   for( size_t i = 0; i < str.size(); i++ )
      ostr << str.data()[ i ];

   return ostr; // enables cout << x << y;
}
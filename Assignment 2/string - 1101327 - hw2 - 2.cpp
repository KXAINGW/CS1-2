#include <iostream>
using std::cout;
using std::exit;

//#include <algorithm>
//using std::max;

#include "string.h" // include definition of class String

string::string()
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
}

string::string( const char *const ptr, const size_type count )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = count;
   myRes = ( mySize / 16 ) * 16 + 15;

   if (!(mySize < 16))
       bx.ptr = new value_type[myRes + 1]();
   for (size_type i = 0; i < mySize; ++i)
       myPtr()[i] = ptr[i];

}

string::string( const size_type count, const char ch )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   // construct from count * ch
   mySize = count;
   if( count > 15 )
   {
      myRes = ( mySize / 16 ) * 16 + 15;
      bx.ptr = new value_type[myRes + 1]();


   }
   for (size_type i = 0; i < mySize; ++i)
       myPtr()[i] = ch;


}

string::string( const string &right )
   : bx(),
     mySize( 0 ),
     myRes( 15 )
{
   mySize = right.mySize;
   myRes = ( mySize / 16 ) * 16 + 15;

   if (!(mySize < 16))
   {
       if (bx.ptr)  //bx.ptr != nullptr
           delete[] bx.ptr;
       bx.ptr = new value_type[myRes + 1]();
   }
    for (size_type i = 0; i <= mySize; i++)
        myPtr()[i] = right.c_str()[i];
    
}

string::~string()
{
   if( myRes > 15 )
      delete[] bx.ptr;
}

string::value_type* string::myPtr()
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

const string::value_type* string::myPtr() const
{
   if( myRes < 16 )
      return bx.buf;
   else
      return bx.ptr;
}

string& string::assign( const string &right )
{
   if( this != &right )
   {
      if( right.mySize > myRes )
      {
          if (myRes > 15)
              delete[] bx.ptr;

         myRes = myRes * 3 / 2;
         if( myRes < ( right.mySize / 16 ) * 16 + 15 )
            myRes = ( right.mySize / 16 ) * 16 + 15;

         bx.ptr = new value_type[myRes + 1]();
      }

      mySize = right.mySize;
      for (size_type i = 0; i <= mySize; ++i)
          myPtr()[i] = right.c_str()[i];
   }

   return *this;
}

// insert ch at where
string::iterator string::insert(const_iterator where, const char ch)
{
    if (where >= myPtr() && where <= myPtr() + mySize)
    {
        size_type index = where - myPtr();
        if (mySize == myRes)
        {
            size_type newMyRes;
            if (myRes == 15 || myRes == 31)
                newMyRes = myRes + 16;
            else
                newMyRes = myRes * 3 / 2;

            if (mySize < 16)
            {
                char ctemp[16] = {};
                for (size_type i = 0; i < mySize; ++i)
                    ctemp[i] = bx.buf[i];
                bx.ptr = new value_type[newMyRes + 1]();
                for (size_t i = 0; i < mySize; ++i)
                    cout << ctemp[i];
                for (size_type i = 0; i < index; ++i)
                    bx.ptr[i] = ctemp[i];
                bx.ptr[index] = ch;
                for (size_type i = index; i <= mySize; ++i)
                    bx.ptr[i + 1] = ctemp[i];

                cout << '\n';
            }
            else
            {
                const_iterator temp = myPtr();
                bx.ptr = new value_type[newMyRes + 1]();
                for (size_type i = 0; i < index; ++i)
                {
                    bx.ptr[i] = temp[i];
                    //cout <<temp[i];
                }
                bx.ptr[index] = ch;
                //cout << temp[index];
                for (size_type i = index; i <= mySize; ++i)
                {
                    bx.ptr[i + 1] = temp[i];
                    //cout << temp[i];
                }
                delete[] temp;
                //if (temp != bx.buf)
                //    delete[] temp;
            }
            ++mySize;
            myRes = newMyRes;

        }
        else
        {
            for (size_type i = mySize; i > index; --i)
                myPtr()[i + 1] = myPtr()[i];
            myPtr()[index + 1] = myPtr()[index];
            myPtr()[index] = ch;
            ++mySize;
        }
        return myPtr() + index;
    }
    else
        return iterator(nullptr);
}

string::iterator string::erase( const_iterator where )
{
   if( where >= myPtr() && where < myPtr() + mySize )
   {
       size_type index = where - myPtr();
       for (; index < mySize; ++index)
           myPtr()[index] = myPtr()[index + 1];
       --mySize;
       return myPtr() + index;

   }
   else
      return iterator( nullptr );
}

void string::clear()
{
   mySize = 0;
   myPtr()[ 0 ] = value_type();
}

string::iterator string::begin()
{
   return myPtr();
}

string::const_iterator string::begin() const
{
   return const_iterator( myPtr() );
}

string::iterator string::end()
{
   return myPtr() + static_cast< difference_type >( mySize );
}

string::const_iterator string::end() const
{
   return const_iterator( myPtr() + static_cast< difference_type >( mySize ) );
}

string::reference string::at( const size_type off )
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::const_reference string::at( const size_type off ) const
{
   if( off > mySize )
   {
      cout << "string subscript out of range\n";
      exit( 1 );
   }

   return myPtr()[ off ];
}

string::reference string::front()
{
   return myPtr()[ 0 ];
}

string::const_reference string::front() const
{
   return myPtr()[ 0 ];
}

string::reference string::back()
{
   return myPtr()[ mySize - 1 ];
}

string::const_reference string::back() const
{
   return myPtr()[ mySize - 1 ];
}

const char* string::c_str() const
{
   return myPtr();
}

string::size_type string::size() const
{
   return mySize;
}

string::size_type string::capacity() const
{
   return myRes;
}

bool string::empty() const
{
   return mySize == 0;
}
// vector test program.
#include <iostream>
using std::cout;
using std::endl;

#include <ctime>
using std::time;

#include <vector>
#include "vector.h"

void testFillConstructor();
void testCopyConstructor();
void testAssignment1();
void testAssignment2();
void testInsert1();
void testInsert2();
void testErase();

// Determines if two vectors are equal.
bool equal( vector &left, std::vector< int > &right );

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

const int number = 300;

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testFillConstructor();
   testCopyConstructor();
   testAssignment1();
   testAssignment2();
   testInsert1();
   testInsert2();
   testErase();
   cout << endl;

   system( "pause" );
}

void testFillConstructor()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector vector1( c );
      int *first1 = vector1.begin(); // first1 = vector1.myFirst

      std::vector< int > vector2( c );
      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         int value = 1 + rand() % 99;
         first1[ i ] = value;
         first2[ i ] = value;
      }

      if( !equal( vector1, vector2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector vector1( c );
      int *first1 = vector1.begin(); // first1 = vector1.myFirst

      std::vector< int > vector2( c );
      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         int value = 1 + rand() % 99;
         first1[ i ] = value;
         first2[ i ] = value;
      }

      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myLast = vector1.myFirst + s
         *last2 = first2 + s;

         vector vector3( vector1 );
         std::vector< int > vector4( vector2 );

         if( !equal( vector3, vector4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment1()
{
   const int number = 30;
   int numErrors = 0;
   for( int c1 = 0; c1 <= number; c1++ )
   {
      vector vector1( c1 );
      std::vector< int > vector2( c1 );

      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c1; i++ )
      {
         int value = 1 + rand() % 99;
         first1[ i ] = value;
         first2[ i ] = value;
      }

      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1; // vector1.myLast = vector1.myFirst + s1
         *last2 = first2 + s1;

         for( int c2 = 0; c2 <= number; c2++ )
         {
            vector vector3( c2 );
            std::vector< int > vector4( c2 );

            int *first3 = vector3.begin(); // first3 = vector3.myFirst
            int *first4 = *( reinterpret_cast< int ** >( &vector4 ) + offset );
            // first4 points to the first element of the array in vector4

            for( int i = 0; i < c2; i++ )
            {
               int value = 1 + rand() % 99;
               first3[ i ] = value;
               first4[ i ] = value;
            }

            int **last3 = reinterpret_cast< int ** >( &vector3 ) + 1;
            // last3 points to vector3.myLast
            int **last4 = reinterpret_cast< int ** >( &vector4 ) + 1 + offset;
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               *last3 = first3 + s2; // vector3.myLast = vector3.myFirst + s2
               *last4 = first4 + s2;

               vector3.assign( vector1 );
               vector4 = vector2;

               if( !equal( vector3, vector4 ) )
                  numErrors++;
            }
         }
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
   const int n = 40;
   int numErrors = 0;
   for( int c1 = 0; c1 <= n; c1++ )
   {
      vector vector1( c1 );
      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      for( int i = 0; i < c1; i++ )
         first1[ i ] = 1 + rand() % 99;

      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast
      for( int s1 = 0; s1 <= c1; s1++ )
      {
         *last1 = first1 + s1;

         for( int c2 = 0; c2 <= n; c2++ )
         {
            vector vector2( c2 );
            int *first2 = vector2.begin(); // first2 = vector2.myFirst
            for( int i = 0; i < c2; i++ )
               first2[ i ] = 1 + rand() % 99;

            int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1;
            // last2 points to vector2.myLast
            for( int s2 = 0; s2 <= c2; s2++ )
            {
               *last2 = first2 + s2; // vector2.myLast = vector2.myFirst + s2

               vector2.assign( vector1 );

               if( vector2.capacity() == c2 && vector2.begin() != first2 )
                  numErrors++;
            }
         }
      }
   }

   // vector2.begin() == first2 if and only if
   // the array pointed by vector2.myFirst before
   // the excution of vector2 = vector1 is the same as
   // the array pointed by vector2.myFirst after
   // the excution of vector2 = vector1
   // i.e., there is no memory allocation during the excution of vector2.assign( vector1 )

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert1()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector vector1( c );
      std::vector< int > vector2( c );

      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         int value = 1 + rand() % 99;
         first1[ i ] = value;
         first2[ i ] = value;
      }

      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      // last1 points to vector1.myLast
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myLast = vector1.myFirst + s
         *last2 = first2 + s;

         int position = rand() % ( vector1.size() + 1 );
         int value = 1 + rand() % 99;

         typename vector::iterator it1;
         typename std::vector< int >::iterator it2;
         it1 = vector1.insert( vector1.begin() + position, value );
         it2 = vector2.insert( vector2.begin() + position, value );

         if (!equal(vector1, vector2) || *it1 != *it2)
             numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector v( c );
      int *first = v.begin(); // first = v.myFirst
      for( int i = 0; i < c; i++ )
         first[ i ] = 1 + rand() % 99;

      int **last = reinterpret_cast< int ** >( &v ) + 1; // last points to v.myLast
      for( int s = 0; s <= c; s++ )
      {
         *last = first + s; // v.myLast = v.myFirst + s

         int position = rand() % ( v.size() + 1 );
         int value = 1 + rand() % 99;
         v.insert( v.begin() + position, value );

         if( v.capacity() == c && v.begin() != first )
            numErrors++;
      }
   }

   // v.begin() == first if and only if
   // the array pointed by v.myFirst before
   // the excution of v.insert( v.begin() + position, value ) is the same as
   // the array pointed by v.myFirst after
   // the excution of v.insert( v.begin() + position, value )
   // i.e., there is no memory allocation during the excution of
   // v.insert( v.begin() + position, value )

   cout << "There are " << numErrors << " errors.\n";
}

void testErase()
{
   int numErrors = 0;
   for( int c = 0; c <= number; c++ )
   {
      vector vector1( c );
      std::vector< int > vector2( c );

      int *first1 = vector1.begin(); // first1 = vector1.myFirst
      int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );
      // first2 points to the first element of the array in vector2

      for( int i = 0; i < c; i++ )
      {
         int value = 1 + rand() % 99;
         first1[ i ] = value;
         first2[ i ] = value;
      }

      int **last1 = reinterpret_cast< int ** >( &vector1 ) + 1;
      int **last2 = reinterpret_cast< int ** >( &vector2 ) + 1 + offset;
      for( int s = 0; s <= c; s++ )
      {
         *last1 = first1 + s; // vector1.myLast = vector1.myFirst + s
         *last2 = first2 + s;

         if( !vector2.empty() )
         {
            int position = rand() % vector1.size();
            vector1.erase( vector1.begin() + position );
            vector2.erase( vector2.begin() + position );
         }

         if( !equal( vector1, vector2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors.\n";
}

// Determines if two vectors are equal.
bool equal( vector &vector1, std::vector< int > &vector2 )
{
   if( vector1.capacity() != vector2.capacity() )
      return false;

   if( vector1.size() != vector2.size() )
      return false;

   if( vector2.size() == 0 )
      return true;

   int *first1 = vector1.begin();
   int *first2 = *( reinterpret_cast< int ** >( &vector2 ) + offset );

   for( size_t i = 0; i < vector2.size(); ++i )
      if( first1[ i ] != first2[ i ] )
         return false;

   return true;
}
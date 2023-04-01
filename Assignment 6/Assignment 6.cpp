// HugeInteger test program.
#include <iostream>
using std::cout;
using std::endl;

#include <list>
#include "list - 1101327 - hw6- list_characteristic.h" // include definition of class template list

template< typename T >
void testList();

template< typename T >
void testFillConstructor();

template< typename T >
void testCopyConstructor();

template< typename T >
void testAssignment1();

template< typename T >
void testAssignment2();

// return true iff the addresses of nodes in list1[0 .. minSize]
// keep unchanged after assignment
template< typename T >
bool efficientAssignment( list< T > &list1, list< T > &list2 );

template< typename T >
void testInsert();

template< typename T >
void testErase();

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right );

int main()
{
   srand( static_cast< unsigned int >( time( 0 ) ) );

   testList< char >();
   testList< short >();
   testList< long >();
   testList< long long >();

   system( "pause" );
}

template< typename T >
void testList()
{
   testFillConstructor< T >();
   testCopyConstructor< T >();
   testAssignment1< T >();
   testAssignment2< T >();
   testInsert< T >();
   testErase< T >();
   cout << endl;
}

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

const int number = 500;

template< typename T >
void testFillConstructor()
{
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      if( !equal( list1, list2 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testCopyConstructor()
{
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
   {
      list< T > list1( n );
      std::list< T > list2( n );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      list< T > list3( list1 );
      std::list< T > list4( list2 );

      if( !equal( list3, list4 ) )
         numErrors++;
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testAssignment1()
{
   const int number = 50;
   int numErrors = 0;
   for( int n1 = 0; n1 < number; n1++ )
   {
      list< T > list1( n1 );
      std::list< T > list2( n1 );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
      for( int i = 1; i <= n1; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         *( p2 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
         p2 = *( reinterpret_cast< size_t ** >( p2 ) );
      }

      for( int n2 = 0; n2 < number; n2++ )
      {
         list< T > list3( n2 );
         std::list< T > list4( n2 );

         size_t *head3 = *( reinterpret_cast< size_t ** >( &list3 ) );
         size_t *head4 = *( reinterpret_cast< size_t ** >( &list4 ) + offset );
         size_t *p3 = *( reinterpret_cast< size_t ** >( head3 ) );
         size_t *p4 = *( reinterpret_cast< size_t ** >( head4 ) );
         for( int i = 1; i <= n2; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p3 + 2 ) = value;
            *( p4 + 2 ) = value;
            p3 = *( reinterpret_cast< size_t ** >( p3 ) );
            p4 = *( reinterpret_cast< size_t ** >( p4 ) );
         }

         list3 = list1;
         list4 = list2;

         if( !equal( list3, list4 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testAssignment2()
{
   const int number = 100;
   int numErrors = 0;
   for( int n1 = 0; n1 < number; n1++ )
   {
      list< T > list1( n1 );

      size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
      size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
      for( int i = 1; i <= n1; i++ )
      {
         size_t value = 1 + rand() % 99;
         *( p1 + 2 ) = value;
         p1 = *( reinterpret_cast< size_t ** >( p1 ) );
      }

      for( int n2 = 0; n2 < number; n2++ )
      {
         list< T > list2( n2 );

         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( int i = 1; i <= n2; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p2 + 2 ) = value;
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         list2 = list1;

         if( !efficientAssignment( list1, list2 ) )
            numErrors++;
      }
   }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff the addresses of nodes in list1[0 .. minSize]
// keep unchanged after assignment
template< typename T >
bool efficientAssignment( list< T > &list1, list< T > &list2 )
{
   size_t minSize = ( list1.size() < list2.size() ) ? list1.size() : list2.size();
   // let n = minSize, and node 1, node 2, ..., node n be the first n nodes of list1.

   typename list< T >::iterator *addresses = new typename list< T >::iterator[ minSize + 1 ];

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   typename list< T >::iterator p = list2.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      addresses[ i ] = p; // save the address of node i

   // addresses[ i ] is the address of node i before the excution of list2 = list1.

   list2 = list1;

   // p = list1.myData.myHead->next i.e., the address of the first node of list1
   p = list2.begin();
   for( size_t i = 1; i <= minSize; ++i, p = p->next )
      // p is the address of node i after the excution of list2 = list1
      if( addresses[ i ] != p )
         return false;

   // addresses[ i ] == p if and only if
   // node i of list2 before the excution of list2 = list1 is the same node as
   // node i of list2 after the excution of list2 = list1
   // i.e., there is no memory allocation during the excution of
   // list2 = list1

   delete[] addresses;

   return true;
}

template< typename T >
void testInsert()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
      for( int position = 0; position <= n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( int i = 1; i <= n; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p1 + 2 ) = value;
            *( p2 + 2 ) = value;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            it1 = it1->next;
            ++it2;
         }

         T value = 1 + rand() % 99;
         list1.insert( it1, value );
         list2.insert( it2, value );

         if( !equal( list1, list2 ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

template< typename T >
void testErase()
{
   const int number = 100;
   int numErrors = 0;
   for( int n = 0; n < number; n++ )
      for( int position = 0; position < n; position++ )
      {
         list< T > list1( n );
         std::list< T > list2( n );

         size_t *head1 = *( reinterpret_cast< size_t ** >( &list1 ) );
         size_t *head2 = *( reinterpret_cast< size_t ** >( &list2 ) + offset );
         size_t *p1 = *( reinterpret_cast< size_t ** >( head1 ) );
         size_t *p2 = *( reinterpret_cast< size_t ** >( head2 ) );
         for( int i = 1; i <= n; i++ )
         {
            size_t value = 1 + rand() % 99;
            *( p1 + 2 ) = value;
            *( p2 + 2 ) = value;
            p1 = *( reinterpret_cast< size_t ** >( p1 ) );
            p2 = *( reinterpret_cast< size_t ** >( p2 ) );
         }

         typename list< T >::iterator it1 = list1.begin();
         typename std::list< T >::iterator it2 = list2.begin();
         for( int i = 0; i < position; i++ )
         {
            it1 = it1->next;
            ++it2;
         }

         list1.erase( it1 );
         list2.erase( it2 );

         if( !equal( list1, list2 ) )
            numErrors++;
      }

   cout << "There are " << numErrors << " errors\n";
}

// return true iff left == right
template< typename T >
bool equal( list< T > &left, std::list< T > &right )
{
   if( left.size() != right.size() ) // different number of elements
   {
       return false;
   }

   if( right.size() == 0 )
      return true;

   typename list< T >::iterator it1 = left.begin();
   typename std::list< T >::iterator it2 = right.begin();
   for( ; it2 != right.end(); it1 = it1->next, ++it2 )
      if( it1->myVal != *it2 )
      {
          //cout << it1->myVal << " " << *it2 << endl;
          return false;
      }

   return true;
}
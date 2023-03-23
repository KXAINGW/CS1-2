#include <iostream>
using std::cout;
using std::endl;
using std::ostream;

#include <fstream>
using std::ifstream;
using std::ios;

#include "Polynomial - 1101327 - hw5-2.h"

template< typename T >
void testPolynomial();

template< typename T >
void load( ifstream &inFile, T coefficient[], T exponent[], int &numTerms );

int main()
{
   testPolynomial< short >();

   testPolynomial< long >();

   testPolynomial< long long >();
}

const int arraySize = 20;

template< typename T >
void testPolynomial()
{
   char fileName[ 30 ] = "";
   if( sizeof( T ) == 2 )
      strcpy_s( fileName, 30, "Polynomials - short.dat" );
   else if( sizeof( T ) == 4 )
      strcpy_s( fileName, 30, "Polynomials - long.dat" );
   else if( sizeof( T ) == 8 )
      strcpy_s( fileName, 30, "Polynomials - long long.dat" );

   ifstream inFile( fileName, ios::in | ios::binary );

   // exit program if ifstream could not open file
   if( !inFile )
   {
      cout << "File could not be opened" << endl;
      system( "pause" );
      exit( 1 );
   }

   const int numTestCases = 200; // the number of test cases
   int numErrors = numTestCases;
   for( int i = 0; i < numTestCases; i++ )
   {
      T coefficient[ arraySize ] = {};
      T exponent[ arraySize ] = {};
      int numTerms = 0;

      load( inFile, coefficient, exponent, numTerms );
      Polynomial< vector< Term< T > >, T > polynomial( numTerms );
      polynomial.setPolynomial( coefficient, exponent, numTerms );
      cout << "polynomial: " << polynomial << endl;

      Polynomial< vector< Term< T > >, T > squareRoot = polynomial.compSquareRoot();
      cout << "squareRoot: " << squareRoot << endl << endl;

      if( squareRoot * squareRoot == polynomial )
         numErrors--;
   }

   inFile.close();

   cout << "There are " << numErrors << " errors!\n\n";

   system( "pause" );
}

template< typename T >
void load( ifstream &inFile, T coefficient[], T exponent[], int &numTerms )
{
   inFile.read( reinterpret_cast< char * >( coefficient ), arraySize * sizeof( T ) );
   inFile.read( reinterpret_cast< char * >( exponent ), arraySize * sizeof( T ) );

   numTerms = arraySize;
   while( numTerms > 0 && coefficient[ numTerms - 1 ] == 0 )
      numTerms--;
}
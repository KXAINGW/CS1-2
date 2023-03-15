#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include "SourceLine.h" // SourceLine class definition

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< Identifier > &identifiers, size_t pos );

int main()
{
   ifstream inFile( "test2.cpp", ios::in );

   // exit program if ifstream could not open file
   if ( !inFile ) 
   {
      std::cout << "File could not be opened" << std::endl;
      system( "pause" );
      exit( 1 );
   }

   char source[ 200 ];
   SourceLine sourceLine;
   Identifier identifier;
   vector< Identifier > identifiers;
   SourceLine null;

   while( inFile.getline( source, sizeof( source ), '\n' ) )
   {
      sourceLine = source;
      sourceLine.delComments(); // deletes the comment beginning with "//" in sourceLine
      sourceLine.delStrConst(); // deletes all string constants in sourceLine
      sourceLine.delCharConst(); // deletes all character constants in sourceLine

      if( sourceLine != null )
         sourceLine.extractIdentifiers( identifiers );
         // extracts all identifiers from sourceLine, and put them into the vector identifiers
   }

   for( size_t i = 0; i < identifiers.size(); i++ )
      if( !identifiers[ i ].keyword() && !duplicate( identifiers, i ) )
         cout << identifiers[ i ] << endl;

   system( "pause" );
}

// returns true if and only if identifiers[ pos ] belongs to identifiers[ 0 .. pos-1 ]
bool duplicate( vector< Identifier > &identifiers, size_t pos )
{
   for( size_t i = 0; i < pos; ++i )
      if( identifiers[ i ] == identifiers[ pos ] )
         return true;

   return false;
}
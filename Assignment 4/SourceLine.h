// SourceLine class definition
#ifndef SOURCE_LINE_H
#define SOURCE_LINE_H

#include <vector>
using std::vector;

#include "Identifier.h" // Identifier class definition

class SourceLine
{
   friend bool operator==( const SourceLine &lhs, const SourceLine &rhs );
public:
   static const size_t npos = -1; // the maximum unsigned int value that is equal to 4294967295

   SourceLine(); // default constructor

   SourceLine& operator=( const char * const ptr );

//   void assign( const char *s, size_t n );
   void delComments(); // delete the comment beginning with "//" in sourceLine
   void delStrConst(); // deletes all string constants from sourceLine
   void delCharConst(); // deletes all character constants from sourceLine

   // extracts all identifiers from sourceLine, and put them into the vector identifiers
   void extractIdentifiers( vector< Identifier > &identifiers );

   // delete the first identifier from sourceLine, and then return the identifier
//   string delFirstIdentifier();

private:
   string sourceLine;
};

bool operator!=( const SourceLine &lhs, const SourceLine &rhs );

#endif
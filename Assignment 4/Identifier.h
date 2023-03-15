// Identifier class definition
#ifndef IDENTIFIER_H
#define IDENTIFIER_H

#include "string.h" // string class definition

class Identifier
{
   friend ostream& operator<<( ostream &output, Identifier &id );
   friend bool operator==( const Identifier &lhs, const Identifier &rhs );
public:
   Identifier(); // default constructor
   Identifier( const string ptr );
   Identifier& operator=( const string &right ); // assignment operator
   bool keyword(); // check if identifier is a C++ keyword

private:
   string identifier;
};

bool operator!=( const Identifier &lhs, const Identifier &rhs );

#endif
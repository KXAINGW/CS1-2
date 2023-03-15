// Identifier class member-function definitions.

#include "Identifier.h" // Identifier class definition

const int numKeywords = 62;
char keywords[ numKeywords ][ 20 ] = { "auto", "break", "case", "char", "const",
                                     "continue", "default", "define","do", "double",
                                     "else", "enum", "extern", "float", "for",
                                     "goto", "if", "int", "long", "register",
                                     "return", "short", "signed", "sizeof",
                                     "static", "struct", "switch", "typedef",
                                     "union", "unsigned", "void", "volatile",
                                     "while", "bool", "catch", "class",
                                     "const_cast", "delete", "dynamic_cast",
                                     "explicit", "false", "friend", "inline",
                                     "mutable", "namespace", "new", "operator",
                                     "private", "protected", "public",
                                     "reinterpret_cast", "static_cast", "template",
                                     "this", "throw", "true", "try", "typeid",
                                     "typename", "using", "virtual", "include" };

// default/conversion constructor
Identifier::Identifier()
   : identifier()
{
}

Identifier::Identifier( const string ptr )
{
   identifier = ptr;
}

// overloaded = operator; avoids self assignment
Identifier& Identifier::operator=( const string &right )
{
   identifier = right;
   return *this; // enables cascaded assignments
}

// check if identifier is a C++ keyword
bool Identifier::keyword()
{
   for( int i = 0; i < numKeywords; i++ )
      if( identifier == string( keywords[ i ], strlen( keywords[ i ] ) ) )
         return true;

   return false;
}

bool operator==( const Identifier &lhs, const Identifier &rhs )
{
   return lhs.identifier == rhs.identifier;
}

bool operator!=( const Identifier &lhs, const Identifier &rhs )
{
   return !( lhs == rhs );
}

ostream& operator<<( ostream &output, Identifier &id )
{
   output << id.identifier;
   return output; // enables cout << x << y;
}
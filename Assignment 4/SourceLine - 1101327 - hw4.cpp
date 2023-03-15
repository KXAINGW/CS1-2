// SourceLine class member-function definitions.

#include <iostream>
using std::cout;

#include "SourceLine.h" // SourceLine class definition

// default/conversion constructor
SourceLine::SourceLine()
   : sourceLine()
{
}

SourceLine& SourceLine::operator=( const char * const ptr )
{
   sourceLine = ptr;
   return *this;
}

void SourceLine::delComments()
{
	//auto ptr = sourceLine.begin();
	//typename string::pointer ptr = sourceLine.begin();

	for (size_t i = 0; i < sourceLine.size() - 1; ++i)
		if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
		{
			sourceLine.erase(i, sourceLine.size() - i);
			break;
		}
}

void SourceLine::delStrConst()
{
	int str = 0;
	int first, last;
	if (sourceLine.size() == 0)
		return;
	for (size_t i = 0; i < (sourceLine.size() - 1); ++i)
	{
		if (sourceLine[i + 1] == '\"' && sourceLine[i] != '\\')
		{
			str++;
			str % 2 ? first = i : last = i;

		}
		if (str && str % 2 == 0)
		{
			sourceLine.erase(first, last - first + 1);
			break;
		}
	}
	if (str)
		delStrConst();



}

void SourceLine::delCharConst()
{
	int ch = 0;
	int first, last;
	if (sourceLine.size() == 0)
		return;
	for (size_t i = 0; i < sourceLine.size() - 3; ++i)
	{
		if (sourceLine[i] == '\'' && sourceLine[i + 2] == '\'')
		{
			sourceLine.erase(i, 3);
			ch = 1;
			break;
		}
		if (sourceLine[i] == '\'' && sourceLine[i + 3] == '\'')
		{
			sourceLine.erase(i, 4);
			ch = 1;
			break;
		}
	}
	if (ch)
		delStrConst();


}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{



}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}
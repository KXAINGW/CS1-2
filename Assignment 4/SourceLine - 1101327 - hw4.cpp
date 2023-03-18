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
	{
		if (sourceLine[i] == '/' && sourceLine[i + 1] == '/')
		{
			sourceLine.erase(i, sourceLine.size() - i);
			break;
		}
	}
}

void SourceLine::delStrConst()
{
	int str = 0;
	int first, last;
	
	
	if (sourceLine.size() == 0)
		return;
	for (int i = 0; i < (int)sourceLine.size() - 1; ++i)
	{
		if (sourceLine[i + 1] == '\"' && sourceLine[i] != '\\')
		{
			str++;
			str % 2 ? first = i + 1 : last = i + 1;

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
	for (int i = 0; i < (int)sourceLine.size() - 3; ++i)
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
		delCharConst();


}

void SourceLine::extractIdentifiers( vector< Identifier > &identifiers )
{
	string::iterator it = sourceLine.begin();
	for (size_t i = 0; i < sourceLine.size(); ++i)
	{
		if (it[i] >= 'a' && it[i] <= 'z' || it[i]>='A' && it[i] <= 'Z' || it[i] == '_')
		{	
			size_t first = i;
			for (size_t j = i + 1; j < sourceLine.size(); ++j, ++i)
			{
				if (!(it[j] >= 'a' && it[j] <= 'z' || it[j]>='A' && it[j] <= 'Z' || it[j] == '_' || it[j]>='0' && it[j] <= '9'))
				{
					Identifier temp(sourceLine.substr(first, j - first));
					identifiers.push_back(temp);
					break;
				}
			}
		}
	}


}

bool operator==( const SourceLine &lhs, const SourceLine &rhs )
{
   return lhs.sourceLine == rhs.sourceLine;
}

bool operator!=( const SourceLine &lhs, const SourceLine &rhs )
{
   return !( lhs == rhs );
}
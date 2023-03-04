// string test program.
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ios;

#include <string>
#include "string.h"

void testFromBufferConstructor();
void testFillConstructor();
void testCopyConstructor();
void testAssignment1();
void testAssignment2();
void testInsert1();
void testInsert2();
void testErase();

// return true iff string1 == string2
bool equal(string& string1, std::string& string2);

#if _ITERATOR_DEBUG_LEVEL == 2
int offset = 1;
#else
int offset = 0;
#endif

int capacities[200];

int main()
{
    ifstream capFile("capacities.txt", ios::in);

    if (!capFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }

    for (int i = 0; i < 100; i++)
        capFile >> capacities[i];

    capFile.close();

    testFromBufferConstructor();
    testFillConstructor();
    testCopyConstructor();
    testAssignment1();
    testAssignment2();
    testInsert1();
    testInsert2();
    testErase();
    cout << endl;
}

void testFromBufferConstructor()
{
    const unsigned int number = 2000;
    int numErrors = 0;
    for (int s = 0; s < number; s++)
    {
        char str[number];
        for (int i = 0; i < s; i++)
            str[i] = static_cast<char>(97 + rand() % 26);
        str[s] = '\0';

        string string1(str, s);
        std::string string2(str, s);

        if (!equal(string1, string2))
            numErrors++;
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testFillConstructor()
{
    const unsigned int number = 2000;
    int numErrors = 0;
    for (int s = 0; s < number; s++)
    {
        string string1(s, '\0');
        std::string string2(s, '\0');

        char* p1 = string1.begin();
        char* p2;
        if (s <= 15) // capacity == 15
            p2 = reinterpret_cast<char*>(&string2) + sizeof(size_t) * offset;
        else // capacity > 15
            p2 = *(reinterpret_cast<char**>(&string2) + offset);

        for (int i = 0; i < s; i++)
        {
            char value = static_cast<char>(97 + rand() % 26);
            p1[i] = value;
            p2[i] = value;
        }
        p1[s] = '\0';
        p2[s] = '\0';

        if (!equal(string1, string2))
            numErrors++;
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testCopyConstructor()
{
    const unsigned int number = 50;
    int numErrors = 0;
    for (int i = 0; i < number; i++)
    {
        int c = capacities[i];
        for (int s = 0; s <= c; s++)
        {
            string string1;
            std::string string2;

            size_t* mySizePtr1;
            size_t* mySizePtr2;
            size_t* myCapPtr1;
            size_t* myCapPtr2;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 4; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 4 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 5; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 5 + offset; // myCapPtr2 points to string2._Myres
            }
            else // x64
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 2; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 2 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 3; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 3 + offset; // myCapPtr2 points to string2._Myres
            }

            *mySizePtr1 = s; // string1.mySize = s
            *mySizePtr2 = s; // string2._Mysize = s
            *myCapPtr1 = c; // string1.myRes = c
            *myCapPtr2 = c; // string2._Myres = c

            if (c <= 15)
            {
                char* p1 = string1.begin(); // p1 = string1.bx.buf
                char* p2 = reinterpret_cast<char*>(&string2) + sizeof(size_t) * offset; // p2 = string2._Bx._Buf
                for (int j = 0; j < s; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    p1[j] = value; // string1.bx.buf[ j ] = value
                    p2[j] = value; // string2._Bx._Buf[ j ] = value
                }
                p1[s] = '\0'; // string1.bx.buf[ i ] = '\0'
                p2[s] = '\0'; // string2._Bx._Buf[ i ] = '\0'
            }
            else
            {
                char** p1 = reinterpret_cast<char**>(&string1); // p1 points to string1.bx.ptr
                *p1 = new char[c + 1](); // i.e., string1.bx.ptr = new char[ c + 1 ]()
                char** p2 = (reinterpret_cast<char**>(&string2) + offset); // p2 points to string2._Bx._Ptr
                *p2 = new char[c + 1](); // i.e., string2._Bx._Ptr = new char[ c + 1 ]()
                for (int j = 0; j < s; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    (*p1)[j] = value; // string1.bx.ptr[ j ] = value
                    (*p2)[j] = value; // string2._Bx._Ptr[ j ] = value
                }
                (*p1)[s] = '\0'; // string1.bx.ptr[ i ] = '\0'
                (*p2)[s] = '\0'; // string2._Bx._Ptr[ i ] = '\0'
            }

            string string3(string1);
            std::string string4(string2);

            if (!equal(string3, string4))
                numErrors++;
        }
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testAssignment1()
{
    const unsigned int number = 5;
    int numErrors = 0;
    for (int i = 0; i < number; i++)
    {
        int c1 = capacities[i];
        for (int s1 = 0; s1 <= c1; s1++)
        {
            string string1;
            std::string string2;

            size_t* mySizePtr1;
            size_t* mySizePtr2;
            size_t* myCapPtr1;
            size_t* myCapPtr2;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 4; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 4 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 5; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 5 + offset; // myCapPtr2 points to string2._Myres
            }
            else // x64
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 2; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 2 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 3; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 3 + offset; // myCapPtr2 points to string2._Myres
            }

            *mySizePtr1 = s1; // string1.mySize = s1
            *mySizePtr2 = s1; // string2._Mysize = s1
            *myCapPtr1 = c1; // string1.myRes = c1
            *myCapPtr2 = c1; // string2._Myres = c1

            if (c1 <= 15)
            {
                char* p1 = string1.begin(); // p1 = string1.bx.buf
                char* p2 = reinterpret_cast<char*>(&string2) + sizeof(size_t) * offset;// p2 = string2._Bx._Buf
                for (int j = 0; j < s1; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    p1[j] = value; // string1.bx.buf[ j ] = value
                    p2[j] = value; // string2._Bx._Buf[ j ] = value
                }
                p1[s1] = '\0'; // string1.bx.buf[ i ] = '\0'
                p2[s1] = '\0'; // string2._Bx._Buf[ i ] = '\0'
            }
            else
            {
                char** p1 = reinterpret_cast<char**>(&string1); // p1 points to string1.bx.ptr
                *p1 = new char[c1 + 1](); // i.e., string1.bx.ptr = new char[ c1 + 1 ]()
                char** p2 = (reinterpret_cast<char**>(&string2) + offset); // p2 points to string2._Bx._Ptr
                *p2 = new char[c1 + 1](); // i.e., string2._Bx._Ptr = new char[ c1 + 1 ]()
                for (int j = 0; j < s1; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    (*p1)[j] = value; // string1.bx.ptr[ j ] = value
                    (*p2)[j] = value; // string2._Bx._Ptr[ j ] = value
                }
                (*p1)[s1] = '\0'; // string1.bx.ptr[ i ] = '\0'
                (*p2)[s1] = '\0'; // string2._Bx._Ptr[ i ] = '\0'
            }

            for (int j = 0; j < number; j++)
            {
                int c2 = capacities[j];
                for (int s2 = 0; s2 <= c2; s2++)
                {
                    string string3;
                    std::string string4;

                    size_t* mySizePtr3;
                    size_t* mySizePtr4;
                    size_t* myCapPtr3;
                    size_t* myCapPtr4;
                    if (sizeof(size_t) == 4) // x86
                    {
                        mySizePtr3 = reinterpret_cast<size_t*>(&string3) + 4; // mySizePtr3 points to string3.mySize
                        mySizePtr4 = reinterpret_cast<size_t*>(&string4) + 4 + offset; // mySizePtr4 points to string4._Mysize
                        myCapPtr3 = reinterpret_cast<size_t*>(&string3) + 5; // myCapPtr3 points to string3.myRes
                        myCapPtr4 = reinterpret_cast<size_t*>(&string4) + 5 + offset; // myCapPtr4 points to string4._Myres
                    }
                    else // x64
                    {
                        mySizePtr3 = reinterpret_cast<size_t*>(&string3) + 2; // mySizePtr3 points to string3.mySize
                        mySizePtr4 = reinterpret_cast<size_t*>(&string4) + 2 + offset; // mySizePtr4 points to string4._Mysize
                        myCapPtr3 = reinterpret_cast<size_t*>(&string3) + 3; // myCapPtr3 points to string3.myRes
                        myCapPtr4 = reinterpret_cast<size_t*>(&string4) + 3 + offset; // myCapPtr4 points to string4._Myres
                    }

                    *mySizePtr3 = s2; // string3.mySize = s2
                    *mySizePtr4 = s2; // string4._Mysize = s2
                    *myCapPtr3 = c2; // string3.myRes = c2
                    *myCapPtr4 = c2; // string4._Myres = c2

                    if (c2 <= 15)
                    {
                        char* p3 = string3.begin(); // p3 = string3.bx.buf
                        char* p4 = reinterpret_cast<char*>(&string4) + sizeof(size_t) * offset;// p4 = string4._Bx._Buf
                        for (int k = 0; k < s2; k++)
                        {
                            char value = static_cast<char>(97 + rand() % 26);
                            p3[k] = value; // string3.bx.buf[ k ] = value
                            p4[k] = value; // string4._Bx._Buf[ k ] = value
                        }
                        p3[s2] = '\0'; // string3.bx.buf[ i ] = '\0'
                        p4[s2] = '\0'; // string4._Bx._Buf[ i ] = '\0'
                    }
                    else
                    {
                        char** p3 = reinterpret_cast<char**>(&string3); // p3 points to string3.bx.ptr
                        *p3 = new char[c2 + 1](); // i.e., string3.bx.ptr = new char[ c2 + 1 ]()
                        char** p4 = (reinterpret_cast<char**>(&string4) + offset); // p4 points to string4._Bx._Ptr
                        *p4 = new char[c2 + 1](); // i.e., string4._Bx._Ptr = new char[ c2 + 1 ]()
                        for (int k = 0; k < s2; k++)
                        {
                            char value = static_cast<char>(97 + rand() % 26);
                            (*p3)[k] = value; // string3.bx.ptr[ k ] = value
                            (*p4)[k] = value; // string4._Bx._Ptr[ k ] = value
                        }
                        (*p3)[s2] = '\0'; // string3.bx.ptr[ i ] = '\0'
                        (*p4)[s2] = '\0'; // string4._Bx._Ptr[ i ] = '\0'
                    }

                    string3.assign(string1);
                    string4 = string2;

                    if (!equal(string3, string4))
                        numErrors++;
                }
            }
        }
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testAssignment2()
{
    const unsigned int number = 7;
    int numErrors = 0;
    for (int i = 0; i < number; i++)
    {
        int c1 = capacities[i];
        for (int s1 = 0; s1 <= c1; s1++)
        {
            string string1;

            size_t* mySizePtr1;
            size_t* myCapPtr1;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 4; // mySizePtr1 points to string1.mySize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 5; // myCapPtr1 points to string1.myRes
            }
            else // x64
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 2; // mySizePtr1 points to string1.mySize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 3; // myCapPtr1 points to string1.myRes
            }

            *mySizePtr1 = s1; // string1.mySize = s1
            *myCapPtr1 = c1; // string1.myRes = c2

            if (c1 <= 15)
            {
                char* p1 = string1.begin(); // p1 = string1.bx.buf
                for (int j = 0; j < s1; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    p1[j] = value; // string1.bx.buf[ j ] = value
                }
                p1[s1] = '\0'; // string1.bx.buf[ i ] = '\0'
            }
            else
            {
                char** p1 = reinterpret_cast<char**>(&string1); // p1 points to string1.bx.ptr
                *p1 = new char[c1 + 1](); // i.e., string1.bx.ptr = new char[ c1 + 1 ]()
                for (int j = 0; j < s1; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    (*p1)[j] = value; // string1.bx.ptr[ j ] = value
                }
                (*p1)[s1] = '\0'; // string1.bx.ptr[ i ] = '\0'
            }

            for (int j = 1; j < number; j++)
            {
                int c2 = capacities[j]; // c2 >= 31
                if (s1 <= c2) // right.mySize <>>= myRes
                {
                    for (int s2 = 0; s2 <= c2; s2++)
                    {
                        string string2;

                        size_t* mySizePtr2;
                        size_t* myCapPtr2;
                        if (sizeof(size_t) == 4) // x86
                        {
                            mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 4; // mySizePtr2 points to string2.mySize
                            myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 5; // myCapPtr2 points to string2.myRes
                        }
                        else // x64
                        {
                            mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 2; // mySizePtr2 points to string2.mySize
                            myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 3; // myCapPtr2 points to string2.myRes
                        }

                        *mySizePtr2 = s2; // string2.mySize = s2
                        *myCapPtr2 = c2; // string2.myRes = c2

                        char** p2 = reinterpret_cast<char**>(&string2); // p2 points to string2.bx.ptr
                        *p2 = new char[c2 + 1](); // i.e., string2.bx.ptr = new char[ c2 + 1 ]()
                        for (int k = 0; k < s2; k++)
                        {
                            char value = static_cast<char>(97 + rand() % 26);
                            (*p2)[k] = value; // string2.bx.ptr[ k ] = value
                        }
                        (*p2)[s2] = '\0'; // string2.bx.ptr[ i ] = '\0'

                        string2.assign(string1);

                        if (string2.capacity() == c2 && string2.begin() != *p2)
                            numErrors++;
                    }
                }
            }
        }
    }

    // string2.begin() != *p2 if and only if
    // the array pointed by string2.bx.ptr before
    // the excution of string2.assign( string1 ) is the same as
    // the array pointed by string2.bx.ptr after
    // the excution of string2.assign( string1 )
    // i.e., there is no memory allocation during
    // the excution of string2.assign( string1 )

    cout << "There are " << numErrors << " errors.\n";
}

void testInsert1()
{
    const unsigned int number = 70;
    int numErrors = 0;
    for (int i = 0; i < number; i++)
    {
        int c = capacities[i];
        for (int s = 0; s <= c; s++)
        {
            string string1;
            std::string string2;

            size_t* mySizePtr1;
            size_t* mySizePtr2;
            size_t* myCapPtr1;
            size_t* myCapPtr2;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 4; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 4 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 5; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 5 + offset; // myCapPtr2 points to string2._Myres
            }
            else // x64
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 2; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 2 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 3; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 3 + offset; // myCapPtr2 points to string2._Myres
            }

            *mySizePtr1 = s; // string1.mySize = s
            *mySizePtr2 = s; // string2._Mysize = s
            *myCapPtr1 = c; // string1.myRes = c
            *myCapPtr2 = c; // string2._Myres = c

            if (c <= 15)
            {
                char* p1 = string1.begin(); // p1 = string1.bx.buf
                char* p2 = reinterpret_cast<char*>(&string2) + sizeof(size_t) * offset;// p2 = string2._Bx._Buf
                for (int i = 0; i < s; i++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    p1[i] = value; // string1.bx.buf[ i ] = value
                    p2[i] = value; // string2._Bx._Buf[ i ] = value
                }
                p1[s] = '\0'; // string1.bx.buf[ i ] = '\0'
                p2[s] = '\0'; // string2._Bx._Buf[ i ] = '\0'
            }
            else
            {
                char** p1 = reinterpret_cast<char**>(&string1); // p1 points to string1.bx.ptr
                *p1 = new char[c + 1](); // i.e., string1.bx.ptr = new char[ c + 1 ]()
                char** p2 = (reinterpret_cast<char**>(&string2) + offset); // p2 points to string2._Bx._Ptr
                *p2 = new char[c + 1](); // i.e., string2._Bx._Ptr = new char[ c + 1 ]()
                for (int i = 0; i < s; i++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    (*p1)[i] = value; // string1.bx.ptr[ i ] = value
                    (*p2)[i] = value; // string2._Bx._Ptr[ i ] = value
                }
                (*p1)[s] = '\0'; // string1.bx.ptr[ i ] = '\0'
                (*p2)[s] = '\0'; // string2._Bx._Ptr[ i ] = '\0'
            }

            unsigned int position = rand() % (string2.size() + 1);
            char value = static_cast<char>(97 + rand() % 26);
            string1.insert(string1.begin() + position, value);
            string2.insert(string2.begin() + position, value);

            if (!equal(string1, string2))
                numErrors++;
        }
    }

    cout << "There are " << numErrors << " errors.\n";
}

void testInsert2()
{
    const unsigned int number = 80;
    int numErrors = 0;
    for (int i = 1; i < number; i++)
    {
        int c = capacities[i]; // c >= 31
        for (int s = 0; s <= c; s++)
        {
            string str;
            size_t* mySizePtr;
            size_t* myCapPtr;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr = reinterpret_cast<size_t*>(&str) + 4; // mySizePtr points to str.mySize
                myCapPtr = reinterpret_cast<size_t*>(&str) + 5; // myCapPtr points to str.myRes
            }
            else // x64
            {
                mySizePtr = reinterpret_cast<size_t*>(&str) + 2; // mySizePtr points to str.mySize
                myCapPtr = reinterpret_cast<size_t*>(&str) + 3; // myCapPtr points to str.myRes
            }

            *mySizePtr = s; // str.mySize = s
            *myCapPtr = c; // str.myRes = c

            char** p = reinterpret_cast<char**>(&str); // p points to str.bx.ptr
            *p = new char[c + 1](); // i.e., str.bx.ptr = new char[ c + 1 ]()
            for (int j = 0; j < s; j++)
            {
                char value = static_cast<char>(97 + rand() % 26);
                (*p)[j] = value; // str.bx.ptr[ j ] = value
            }
            (*p)[s] = '\0'; // str.bx.ptr[ i ] = '\0'

            unsigned int position = rand() % (str.size() + 1);
            char value = static_cast<char>(97 + rand() % 26);
            str.insert(str.begin() + position, value);

            if (str.capacity() == c && str.begin() != *p)
                numErrors++;
        }
    }

    // str.begin() == *p if and only if
    // the array pointed by str.bx.ptr before
    // the excution of str.insert( str.begin() + position, value ) is the same as
    // the array pointed by str.bx.ptr after
    // the excution of str.insert( str.begin() + position, value )
    // i.e., there is no memory allocation during the excution of
    // str.insert( str.begin() + position, value )

    cout << "There are " << numErrors << " errors.\n";
}

void testErase()
{
    const unsigned int number = 70;
    int numErrors = 0;
    for (int i = 0; i < number; i++)
    {
        int c = capacities[i];
        for (int s = 0; s <= c; s++)
        {
            string string1;
            std::string string2;

            size_t* mySizePtr1;
            size_t* mySizePtr2;
            size_t* myCapPtr1;
            size_t* myCapPtr2;
            if (sizeof(size_t) == 4) // x86
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 4; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 4 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 5; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 5 + offset; // myCapPtr2 points to string2._Myres
            }
            else // x64
            {
                mySizePtr1 = reinterpret_cast<size_t*>(&string1) + 2; // mySizePtr1 points to string1.mySize
                mySizePtr2 = reinterpret_cast<size_t*>(&string2) + 2 + offset; // mySizePtr2 points to string2._Mysize
                myCapPtr1 = reinterpret_cast<size_t*>(&string1) + 3; // myCapPtr1 points to string1.myRes
                myCapPtr2 = reinterpret_cast<size_t*>(&string2) + 3 + offset; // myCapPtr2 points to string2._Myres
            }

            *mySizePtr1 = s; // string1.mySize = s
            *mySizePtr2 = s; // string2._Mysize = s
            *myCapPtr1 = c; // string1.myRes = c
            *myCapPtr2 = c; // string2._Myres = c

            if (c <= 15)
            {
                char* p1 = string1.begin(); // p1 = string1.bx.buf
                char* p2 = reinterpret_cast<char*>(&string2) + sizeof(size_t) * offset;// p2 = string2._Bx._Buf
                for (int j = 0; j < s; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    p1[j] = value; // string1.bx.buf[ j ] = value
                    p2[j] = value; // string2._Bx._Buf[ j ] = value
                }
                p1[s] = '\0'; // string1.bx.buf[ i ] = '\0'
                p2[s] = '\0'; // string2._Bx._Buf[ i ] = '\0'
            }
            else
            {
                char** p1 = reinterpret_cast<char**>(&string1); // p1 points to string1.bx.ptr
                *p1 = new char[c + 1](); // i.e., string1.bx.ptr = new char[ c + 1 ]()
                char** p2 = (reinterpret_cast<char**>(&string2) + offset); // p2 points to string2._Bx._Ptr
                *p2 = new char[c + 1](); // i.e., string2._Bx._Ptr = new char[ c + 1 ]()
                for (int j = 0; j < s; j++)
                {
                    char value = static_cast<char>(97 + rand() % 26);
                    (*p1)[j] = value; // string1.bx.ptr[ j ] = value
                    (*p2)[j] = value; // string2._Bx._Ptr[ j ] = value
                }
                (*p1)[s] = '\0'; // string1.bx.ptr[ i ] = '\0'
                (*p2)[s] = '\0'; // string2._Bx._Ptr[ i ] = '\0'
            }

            if (string2.empty())
            {
                string1.erase(string1.begin());
                string2.erase(string2.begin());
            }
            else
            {
                unsigned int position = rand() % string2.size();
                string1.erase(string1.begin() + position);
                string2.erase(string2.begin() + position);
            }

            if (!equal(string1, string2))
                numErrors++;
        }
    }

    cout << "There are " << numErrors << " errors.\n";
}

// return true iff string1 == string2
bool equal(string& string1, std::string& string2)
{
    if (string1.capacity() != string2.capacity())
        return false;

    if (string1.size() != string2.size())
        return false;

    if (string2.size() == 0)
        return true;

    for (size_t i = 0; i <= string2.size(); i++)
        if (string1.at(i) != string2[i])
        {
            return false;
        }

    return true;
}
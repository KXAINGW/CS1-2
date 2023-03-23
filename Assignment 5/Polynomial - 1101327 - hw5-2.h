#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <cmath>
using std::sqrt;

#include "vector - 1101327 - hw5.h"

// Represents a term of a polynomial
template< typename T >
struct Term
{
   bool operator!=( const Term &right ) const
   {
      return coef != right.coef || expon != right.expon;
   }

   T coef;
   T expon;
};

// Polynomial class template definition
template< typename T1, typename T2 >
class Polynomial
{
   // Overloaded stream insertion operator
   template< typename T1, typename T2 >
   friend ostream &operator<<( ostream &output, Polynomial< T1, T2 > a );
public:

   // Constructs an empty polynomial, with no terms.
   Polynomial( size_t n = 0 )
      : polynomial( n )
   {
   }

   // Constructs a polynomial with a copy of each of the terms in polynomialToCopy.
   Polynomial( const Polynomial &right )
      : polynomial( right.polynomial )
   {
   }

   // Destructor with empty body
   ~Polynomial()
   {
   }

   // Copies all the terms from "right" into the polynomial
   const Polynomial operator=( const Polynomial &right )
   {
      if( &right != this ) // avoid self-assignment
         polynomial = right.polynomial;

      return *this; // enables x = y = z, for example
   }

   bool operator==( const Polynomial &right )
   {
      return polynomial == right.polynomial;
   }

   void setPolynomial( T2 coefficient[], T2 exponent[], int numTerms )
   {
      for( int i = 0; i < numTerms; i++ )
      {
         polynomial[ i ].coef = coefficient[ i ];
         polynomial[ i ].expon = exponent[ i ];
      }
   }

   // addition assignment operator; Polynomial += Polynomial
   void operator+=( Polynomial &op2 )
   {
       Polynomial<T1, T2> sum;
       size_t i = 0, j = 0;
       while (i < polynomial.size() && j < op2.polynomial.size())
       {
           T2 coef1 = polynomial[i].coef, coef2 = op2.polynomial[j].coef, expon1 = polynomial[i].expon, expon2 = op2.polynomial[j].expon;

           if (expon1 < expon2)
           {
               ++j;
               sum.attach(coef2, expon2);
           }
           else if (expon1 > expon2)
           {
               ++i;
               sum.attach(coef1, expon1);
           }
           else
           {
               ++i; ++j;
               T2 add = coef1 + coef2;
               if (add)
                   sum.attach(add, expon1);
               else
                   continue;
           }
       }
       while (i < polynomial.size())
       {
           sum.attach(polynomial[i].coef, polynomial[i].expon);
           ++i;
       }
       while (j < op2.polynomial.size())
       {
           sum.attach(op2.polynomial[j].coef, op2.polynomial[j].expon);
           ++j;
       }

       *this = sum;

   }

   // subtraction assignment operator; Polynomial -= Polynomial
   void operator-=( Polynomial &op2 )
   {
      Polynomial minus = -op2;
      *this += minus;
   }

   // multiplication operator; Polynomial * Polynomial
   Polynomial operator*( Polynomial &op2 )
   {
       
       Polynomial<T1, T2> product;
       bool assign = 1;
       for (size_t i = 0; i < polynomial.size(); ++i)
       {
           Polynomial<T1, T2> buffer;
           for (size_t j = 0; j < op2.polynomial.size(); ++j)
               buffer.attach(polynomial[i].coef * op2.polynomial[j].coef, polynomial[i].expon + op2.polynomial[j].expon);
           if (assign)
           {
               assign = 0;
               product = buffer;
           }
           else
               product += buffer;


       }
       return product;


   }

   // computes the square root of the current polynomial
   Polynomial compSquareRoot()
   {
       Polynomial<T1, T2> divisor;
       Polynomial<T1, T2> monomial(1);
       Polynomial<T1, T2> buffer;
       Polynomial<T1, T2> remainder(*this);
       Polynomial<T1, T2> squareRoot;
       Polynomial<T1, T2> empty;
       
       typename T1::pointer mon_ptr = monomial.polynomial.begin();
       mon_ptr[0].coef = static_cast<T2>(sqrt(remainder.polynomial[0].coef));
       mon_ptr[0].expon = static_cast<T2>(remainder.polynomial[0].expon / 2);
       divisor.attach(mon_ptr[0].coef, mon_ptr[0].expon);
       squareRoot.attach(mon_ptr[0].coef, mon_ptr[0].expon);
       buffer = divisor * monomial;
       remainder -= buffer;
       while (!(remainder == empty))
       {
           size_t index = divisor.polynomial.size() - 1;
           divisor.polynomial[index].coef = divisor.polynomial[index].coef * 2;
           mon_ptr[0].coef = remainder.polynomial.front().coef / divisor.polynomial[0].coef;
           mon_ptr[0].expon = remainder.polynomial.front().expon - divisor.polynomial[0].expon;
           divisor.attach(mon_ptr[0].coef, mon_ptr[0].expon);
           squareRoot.attach(mon_ptr[0].coef, mon_ptr[0].expon);
           buffer = divisor * monomial;
           remainder -= buffer;
       }
       return squareRoot;

   }

private:
   T1 polynomial; // a polynomial

   // Attaches a new term to the polynomial
   void attach( T2 coefficient, T2 exponent )
   {
      Term< T2 > tempTerm;
      tempTerm.coef = coefficient;
      tempTerm.expon = exponent;
      polynomial.insert( polynomial.end(), tempTerm );
   }

   // Returns the minus of the current polynomial
   Polynomial operator-()
   {
      Polynomial minus( polynomial.size() );
      typename T1::iterator it2 = minus.polynomial.begin();
      typename T1::iterator it1 = polynomial.begin();
      for( ; it1 != polynomial.end(); ++it1, ++it2 )
      {
         it2->coef = -it1->coef;
         it2->expon = it1->expon;
      }

      return minus;
   }

   // Returns true if and only if polynomial is a zero polynomial
   bool zero() const
   {
      return polynomial.empty();
   }

   // Returns the highest of degrees of polynomial's terms
   int degree() const
   {
      if( polynomial.empty() )
         return 0;
      else
         return polynomial.begin()->expon;
   }

}; // end class template Polynomial

// Overloaded stream insertion operator
template< typename T1, typename T2 >
ostream& operator<<( ostream &output, Polynomial< T1, T2 > a )
{
   if( a.zero() )
   {
      output << 0 << endl;
      return output;
   }

   typename T1::iterator it = a.polynomial.begin();

   if( it->coef < 0 )
      cout << "-" << -it->coef;
   else if( it->coef > 0 )
      cout << it->coef;

   if( it->expon > 0 )
   {
      if( it->expon == 1 )
         cout << "x";
      else
         cout << "x^" << it->expon;
   }

   for( ++it; it != a.polynomial.end(); ++it )
   {
      if( it->coef < 0 )
         cout << " - " << -it->coef;
      else if( it->coef > 0 )
         cout << " + " << it->coef;

      if( it->expon > 0 )
      {
         if( it->expon == 1 )
            cout << "x";
         else
            cout << "x^" << it->expon;
      }
   }

   return output; // enables cout << x << y;
} // end function operator<<

#endif
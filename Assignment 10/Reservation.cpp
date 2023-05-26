#include <iostream>
#include "Reservation.h" // Reservation class definition

Reservation::Reservation( string flightNoValue, string idValue,
                          string nameValue, string mobileValue, string dateValue )
{
   setFlightNo( flightNoValue );
   setId( idValue );
   setName( nameValue );
   setMobile( mobileValue );
   setDate( dateValue );
   for( int i = 0; i < 8; i++ )
      tickets[ i ] = 0;
}

void Reservation::setFlightNo( string flightNoValue )
{
   size_t length = flightNoValue.size();
   length = ( length < 8 ? length : 7 );
   for( size_t i = 0; i < length; i++ )
      flightNo[ i ] = flightNoValue[ i ];
   flightNo[ length ] = '\0';
}

string Reservation::getFlightNo()
{
   return string( flightNo );
}

void Reservation::setId( string idValue )
{
   size_t length = idValue.size();
   length = ( length < 12 ? length : 11 );
   for( size_t i = 0; i < length; i++ )
      id[ i ] = idValue[ i ];
   id[ length ] = '\0';
}

string Reservation::getId()
{
   return string( id );
}

void Reservation::setName( string nameValue )
{
   size_t length = nameValue.size();
   length = ( length < 8 ? length : 7 );
   for( size_t i = 0; i < length; i++ )
      name[ i ] = nameValue[ i ];
   name[ length ] = '\0';
}

string Reservation::getName()
{
   return string( name );
}

void Reservation::setMobile( string mobileValue )
{
   size_t length = mobileValue.size();
   length = ( length < 12 ? length : 11 );
   for( size_t i = 0; i < length; i++ )
      mobile[ i ] = mobileValue[ i ];
   mobile[ length ] = '\0';
}

string Reservation::getMobile()
{
   return string( mobile );
}

void Reservation::setDate( string dateValue )
{
   size_t length = dateValue.size();
   length = ( length < 12 ? length : 11 );
   for( size_t i = 0; i < length; i++ )
      date[ i ] = dateValue[ i ];
   date[ length ] = '\0';
}

string Reservation::getDate()
{
   return string( date );
}

void Reservation::setTickets( int inputTickets[] )
{
   for( int i = 0; i < 8; i++ )
      tickets[ i ] = inputTickets[ i ];
}

int Reservation::getTicket( int i )
{
   if( i > 0 && i < 8 )
      return tickets[ i ];
   else
      return -1;
}
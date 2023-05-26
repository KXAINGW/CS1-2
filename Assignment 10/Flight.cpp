#include <iostream>
#include <iomanip>
#include "Flight.h" // Flight class definition

Flight::Flight( string flightNoValue, int departureAirportValue,
                int arrivalAirportValue, string departureTimeValue, string arrivalTimeValue )
{
   setFlightNo( flightNoValue );
   setDepartureAirport( departureAirportValue );
   setArrivalAirport( arrivalAirportValue );
   setDepartureTime( departureTimeValue );
   setArrivalTime( arrivalTimeValue );
}

void Flight::setFlightNo( string flightNoValue )
{
   size_t length = flightNoValue.size();
   length = ( length < 8 ? length : 7 );
   for( size_t i = 0; i < length; i++ )
      flightNo[ i ] = flightNoValue[ i ];
   flightNo[ length ] = '\0';
}

string Flight::getFlightNo()
{
   return flightNo;
}

void Flight::setDepartureAirport( int departureAirportValue )
{
   departureAirport = departureAirportValue;
}

int Flight::getDepartureAirport()
{
   return departureAirport;
}

void Flight::setArrivalAirport( int arrivalAirportValue )
{
   arrivalAirport = arrivalAirportValue;
}

int Flight::getArrivalAirport()
{
   return arrivalAirport;
}

void Flight::setDepartureTime( string departureTimeValue )
{
   size_t length = departureTimeValue.size();
   length = ( length < 8 ? length : 7 );
   for( size_t i = 0; i < length; i++ )
      departureTime[ i ] = departureTimeValue[ i ];
   departureTime[ length ] = '\0';
}

string Flight::getDepartureTime()
{
   return string( departureTime );
}

void Flight::setArrivalTime( string arrivalTimeValue )
{
   size_t length = arrivalTimeValue.size();
   length = ( length < 8 ? length : 7 );
   for( size_t i = 0; i < length; i++ )
      arrivalTime[ i ] = arrivalTimeValue[ i ];
   arrivalTime[ length ] = '\0';
}

string Flight::getArrivalTime()
{
   return string( arrivalTime );
}

void Flight::display( string date )
{
   cout << setw( 6 ) << flightNo
        << setw( 12 ) << departureTime
        << setw( 10 ) << arrivalTime
        << setw( 7 ) << fullFare[ departureAirport ][ arrivalAirport ] << endl;
}
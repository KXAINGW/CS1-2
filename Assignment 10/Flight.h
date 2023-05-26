#ifndef FLIGHT_H
#define FLIGHT_H

#include <string>
using namespace std;

extern const char airportName[ 12 ][ 12 ];
extern const int fullFare[ 12 ][ 12 ];

class Flight
{
public:
   // constructor initializes data members
   Flight( string flightNoValue = "", int departureAirportValue = 0, int arrivalAirportValue = 0,
           string departureTimeValue = "", string arrivalTimeValue = "" );

   void setFlightNo( string flightNoValue );
   string getFlightNo();
   void setDepartureAirport( int departureAirportValue );
   int getDepartureAirport();
   void setArrivalAirport( int arrivalAirportValue );
   int getArrivalAirport();
   void setDepartureTime( string departureTimeValue );
   string getDepartureTime();
   void setArrivalTime( string arrivalTimeValue );
   string getArrivalTime();

   // displays flightNo, airportName[ departureAirport ], airportName[ arrivalAirport ], date,
   // departureTime, arrivalTime and fullFare[ departureAirport ][ arrivalAirport ]
   void display( string date );

private:
   char flightNo[ 8 ];      // flight number
   int departureAirport;    // departure airport code
   int arrivalAirport;      // arrival airport code
   char departureTime[ 8 ]; // departure time
   char arrivalTime[ 8 ];   // arrival time
};

#endif
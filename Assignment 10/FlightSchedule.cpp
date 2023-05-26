// FlightSchedule.cpp
// Member-function definitions for class FlightSchedule.
#include <iostream>
#include <fstream>
#include "FlightSchedule.h" // FlightSchedule class definition

// FlightSchedule default constructor loads flight schedule from the file Flight Schedule.dat
FlightSchedule::FlightSchedule()
{
   loadFlightSchedule();
}

FlightSchedule::~FlightSchedule()
{
}

int FlightSchedule::getDepartureAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getDepartureAirport();

   return 0;
}

int FlightSchedule::getArrivalAirport( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   if( it != flights.end() )
      return it->getArrivalAirport();

   return 0;
}

string FlightSchedule::getDepartureTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getDepartureTime();
}

string FlightSchedule::getArrivalTime( string flightNo )
{
   vector< Flight >::iterator it = getFlight( flightNo );

   return it->getArrivalTime();
}

bool FlightSchedule::exist( string flightNo, int departureAirport, int arrivalAirport )
{
    vector<Flight>::iterator it = getFlight(flightNo);
    if (it != flights.end())
        if (it->getDepartureAirport() == departureAirport && it->getArrivalAirport() == arrivalAirport)
            return 1;
    return 0;


}

void FlightSchedule::display( int departureAirport, int arrivalAirport, string date )
{
   cout << airportName[ departureAirport ] << " to " << airportName[ arrivalAirport ]
      << " / Depart date: " << date << ".\n\n";
   cout << "Flight   Departure   Arrival   Fare\n";

   for( vector< Flight >::iterator it = flights.begin(); it != flights.end(); ++it )
      if( it->getDepartureAirport() == departureAirport &&
          it->getArrivalAirport() == arrivalAirport )
         it->display( date );
}

vector< Flight >::iterator FlightSchedule::getFlight( string flightNo )
{
    vector<Flight>::iterator it = flights.begin();
    for (; it != flights.end(); ++it)
        if (it->getFlightNo() == flightNo)
            return it;
    return flights.end();


}

void FlightSchedule::loadFlightSchedule()
{
    ifstream inFile("Flight Schedule.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cerr << "Flight Schedule.dat could not be opened.\n";
        exit(1);
    }

    inFile.seekg(0, ios::end);
    size_t fileLen = inFile.tellg() / sizeof(Flight);
    inFile.seekg(0, ios::beg);
    for (size_t i = 0; i < fileLen; ++i)
    {
        Flight tmp;
        inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Flight));
        flights.push_back(tmp);
    }
    
    inFile.close();

}
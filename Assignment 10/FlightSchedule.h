// FlightSchedule.h
// FlightSchedule class definition. Represents the flight schedule.
#ifndef FLIGHT_SCHEDULE_H
#define FLIGHT_SCHEDULE_H

#include <vector>
#include "Flight.h" // Flight class definition

class FlightSchedule
{
public:
   FlightSchedule(); // calls loadFlightSchedule()
   ~FlightSchedule();

   int getDepartureAirport( string flightNo );

   int getArrivalAirport( string flightNo );

   string getDepartureTime( string flightNo );

   string getArrivalTime( string flightNo );

   // return true if and only if there exists a Flight object containing specified
   // flightNo, departureAirport and arrivalAirport
   bool exist( string flightNo, int departureAirport, int arrivalAirport );

   // calls the function Flight::display to display the information regarding
   // the Flight object containing specified departureAirport and arrivalAirport
   void display( int departureAirport, int arrivalAirport, string date );

private:
   vector< Flight > flights; // vector of the flights
   
   // returns an iterator that points to the first Flight object in the vector flights
   // containing specified flightNo.
   // If no such Flight object is found, the function returns flights.end().
   vector< Flight >::iterator getFlight( string flightNo );

   // puts the flight schedule, read from the file Flight Schedule.dat, into the vector flights
   void loadFlightSchedule();
}; // end class FlightSchedule

#endif // FLIGHT_SCHEDULE_H

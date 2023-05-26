// MakingReservation.h
// MakingReservation class definition. Represents a balance inquiry.
#ifndef MAKING_RESERVATION_H
#define MAKING_RESERVATION_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

class MakingReservation
{
public:
   // constructor initializes data members
   MakingReservation( ReservationDatabase &theReservationDatabase,
                      FlightSchedule &theFlightSchedule );
   void execute(); // performs booking
private:
   ReservationDatabase &reservationDatabase; // reference to the reservationDatabase
   FlightSchedule &flightSchedule; // reference to the flightSchedule

   // choose arrival airport by input its code
   void chooseArrivalAirport( int departureAirport, int &arrivalAirport );

   // input the number of tickets for each ticket type
   void inputNumTickets( int tickets[] );

   // display the information of specified reservation
   void displayReservation( Reservation reservation );
}; // end class MakingReservation

#endif // MAKING_RESERVATION_H
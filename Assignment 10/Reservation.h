// Reservation.h
// Reservation class definition. Represents a reservation.
#ifndef RESERVATION_H
#define RESERVATION_H

#include "Flight.h"

class Reservation
{
public:
   // constructor initializes data members
   Reservation( string flightNoValue = "", string idValue = "",
                string nameValue = "", string mobileValue = "", string dateValue = "" );

   void setFlightNo( string flightNoValue );
   string getFlightNo();
   void setId( string idValue );
   string getId();
   void setName( string nameValue );
   string getName();
   void setMobile( string mobileValue );
   string getMobile();
   void setDate( string dateValue );
   string getDate();
   void setTickets( int inputTickets[] );
   int getTicket( int i );

private:
   char flightNo[ 8 ]; // flight number
   char id[ 12 ];      // id number
   char name[ 8 ];     // name
   char mobile[ 12 ];  // mobile phone number
   char date[ 12 ];    // departure date
   int tickets[ 8 ];
   // tickets[ 0 ]: not used
   // tickets[ 1 ]: number of full fare tickets
   // tickets[ 2 ]: number of child tickets
   // tickets[ 3 ]: number of infant tickets
   // tickets[ 4 ]: number of senior citizen tickets
   // tickets[ 5 ]: number of impaired tickets
   // tickets[ 6 ]: number of impaired companion tickets
   // tickets[ 7 ]: number of military tickets
};

#endif
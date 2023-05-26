// InquiryRefund.h
// InquiryRefund class definition.
#ifndef VIEWING_CANCELING_H
#define VIEWING_CANCELING_H

#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

class InquiryRefund
{
public:
   // constructor initializes data members
   InquiryRefund( ReservationDatabase &theReservationDatabase,
                     FlightSchedule &theFlightSchedule );
   bool bookingInquiry( string id ); // performs booking inquiry
   void refundApplication( string id ); // performs refund application
private:
   string id; // current user's id number
   ReservationDatabase &reservationDatabase; // reference to the reservationDatabase
   FlightSchedule &flightSchedule; // reference to the flightSchedule
}; // end class InquiryRefund

#endif // VIEWING_CANCELING_H
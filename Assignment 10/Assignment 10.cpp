#include <iostream>
#include "MakingReservation.h" // MakingReservation class definition
#include "InquiryRefund.h" // InquiryRefund class definition

const char airportName[ 12 ][ 12 ] = { "", "Taipei",    "Taichung", "Chiayi",  "Tainan",
                                           "Kaohsiung", "Hualien", "Taitung",
                                           "Penghu",    "Kinmen",   "Beigan",  "Nangan" };

// row 0 and column 0 are not used,
// fullFare[ i ][ j ] is the full fare from airport i to airport j
const int fullFare[ 12 ][ 12 ] = {
   { 0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0,    0,    0,    0,    0,    0, 1781, 2460, 2296, 2618, 2197, 2197 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1769, 2236,    0, 2686 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1721, 2217,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1697, 2231,    0,    0 },
   { 0,    0,    0,    0,    0,    0,    0,    0, 1876, 2393,    0,    0 },
   { 0, 1781,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2460,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2296, 1769, 1721, 1697, 1876,    0,    0,    0, 1768,    0,    0 },
   { 0, 2618, 2236, 2217, 2231, 2393,    0,    0, 1768,    0,    0,    0 },
   { 0, 2197,    0,    0,    0,    0,    0,    0,    0,    0,    0,    0 },
   { 0, 2197, 2686,    0,    0,    0,    0,    0,    0,    0,    0,    0 } };

const int discount[ 8 ] = { 0, 100, 75, 0, 50, 50, 50, 95 };
// discount[ 0 ]: not used
// discount[ 1 ]: Full Fare Ticket
// discount[ 2 ]: Child Ticket:              25% off of the full fare
// discount[ 3 ]: Infant Ticket:             Free of charge
// discount[ 4 ]: Senior Citizen Ticket:     50% off of the full fare
// discount[ 5 ]: Impaired Ticket:           50% off of the full fare
// discount[ 6 ]: Impaired Companion Ticket: 50% off of the full fare
// discount[ 7 ]: Military Ticket:            5% off of the full fare

int enterChoice();

int main()
{
   cout << "Welcome to UNI Air Domestic Flights Booking System\n";

   ReservationDatabase reservationDatabase;
   FlightSchedule flightSchedule;
   MakingReservation makingReservation( reservationDatabase, flightSchedule );
   InquiryRefund inquiryRefund( reservationDatabase, flightSchedule );
   string id;

   int choice;
   while ( ( choice = enterChoice() ) != 4 )
   {
      switch ( choice )
      {
      case 1:
         makingReservation.execute();
         break;
      case 2:
         cout << "\nEnter ID number: ";
         cin >> id;
         inquiryRefund.bookingInquiry( id );
         break;
      case 3:
         cout << "\nEnter ID number: ";
         cin >> id;
         inquiryRefund.refundApplication( id );
         break;
      default:
         cerr << "Incorrect choice" << endl;
         break;
      }
   }

   cout << endl;
   system( "pause" );
}

int enterChoice()
{
   cout << "\nInput your choice:\n"
        << "1. Booking\n"
        << "2. Booking enquiry\n"
        << "3. Refund application\n"
        << "4. End\n? ";

   int menuChoice;
   cin >> menuChoice;
   return menuChoice;
}
// ReservationDatabase.cpp
// Member-function definitions for class ReservationDatabase.
#include <iostream>
#include <iomanip>
#include <fstream>
#include "ReservationDatabase.h" // ReservationDatabase class definition
#include "FlightSchedule.h" // FlightSchedule class definition

// ReservationDatabase default constructor loads flight reservations from the file Reservations.dat
ReservationDatabase::ReservationDatabase()
{
   loadReservations();
}

// ReservationDatabase destructor stores flight reservations into the file Reservations.dat
ReservationDatabase::~ReservationDatabase()
{
   storeReservations();
}

void ReservationDatabase::addReservation( Reservation reservation )
{
   reservations.push_back( reservation );
}

void ReservationDatabase::cancelReservation( string id, int n )
{
    if (n > reservations.size())
    {
        cout << "\nOut of range!\n";
        return;
    }
    vector<Reservation>::iterator it = reservations.begin();
    for (; it != reservations.end(); ++it)
    {
        if (it->getId() == id)
            --n;
        if (!n)
            break;
    }
    if (n)
    {
        cout << "\nOut of range!\n";
        return;
    }
    reservations.erase(it);
    cout << "\nThe seleted booking has been deleted.\n";


} // end function cancelReservation

bool ReservationDatabase::empty()
{
   return ( reservations.size() == 0 );
}

bool ReservationDatabase::existReservation( string id )
{
    vector<Reservation>::iterator it = reservations.begin();
    for (; it != reservations.end(); ++it)
        if (it->getId() == id)
            return 1;
    return 0;


}

void ReservationDatabase::display( string id )
{
   char ticketType[ 8 ][ 24 ] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                      "Senior Citizen Fare", "Impaired Fare",
                                      "Impaired Companion Fare", "Military Fare" };

   size_t reservationNum = reservations.size();
   size_t index = 1;
   for (size_t i = 0; i < reservationNum; ++i)
   {
       if (reservations[i].getId() != id)
           continue;
       cout << '\n' << index++ << ". Ticket information:\n\n";
       cout << "Date: " << reservations[i].getDate() << endl;
       cout << "Flight: B7-" << reservations[i].getFlightNo() << endl << endl;
       
       FlightSchedule flightSchedule;
       int DepartureAirPortID = flightSchedule.getDepartureAirport(reservations[i].getFlightNo());
       int ArrivalAirportID = flightSchedule.getArrivalAirport(reservations[i].getFlightNo());
       cout << right << setw(9) << airportName[DepartureAirPortID] << " -> " << airportName[ArrivalAirportID] << endl;
       cout << right << setw(9) << flightSchedule.getDepartureTime(reservations[i].getFlightNo()) << "    " << flightSchedule.getArrivalTime(reservations[i].getFlightNo()) << endl << endl;

       // discount[ 0 ]: not used
       // discount[ 1 ]: Full Fare Ticket
       // discount[ 2 ]: Child Ticket:              25% off of the full fare
       // discount[ 3 ]: Infant Ticket:             Free of charge
       // discount[ 4 ]: Senior Citizen Ticket:     50% off of the full fare
       // discount[ 5 ]: Impaired Ticket:           50% off of the full fare
       // discount[ 6 ]: Impaired Companion Ticket: 50% off of the full fare
       // discount[ 7 ]: Military Ticket:            5% off of the full fare

       int total = 0;
       int cost = 0;
       int ticketNum = 0;
       string ticket_arr[] = { "","Full","Child","Infant","Senior Citizen","Impaired","Impaired Companion","Military" };
       for (size_t j = 1; j < 8; ++j)
       {
           ticketNum = reservations[i].getTicket(j);
           if (!ticketNum)
               continue;
           // cost = (discount[j] / 100.0) * fullFare[DepartureAirPortID][ArrivalAirportID];
           cost = fullFare[DepartureAirPortID][ArrivalAirportID] * discount[j] / 100;
           cout << right << setw(18) << ticket_arr[j] << " Fare  TWD " << setw(4) << cost << " x " << ticketNum << endl;
           total += cost * ticketNum;
       }
       cout << "\nTotal: " << total << endl;


   }
   

}

void ReservationDatabase::loadReservations()
{
    ifstream inFile("Reservations.dat", ios::in | ios::binary);
    if (!inFile)
    {
        cerr << "Reservations.dat could not be opened\n";
        exit(1);
    }
    inFile.seekg(0, ios::end);
    size_t fileLen = inFile.tellg() / sizeof(Reservation);
    inFile.seekg(0, ios::beg);
    for (size_t i = 0; i < fileLen; ++i)
    {
        Reservation tmp;
        inFile.read(reinterpret_cast<char*>(&tmp), sizeof(Reservation));
        reservations.push_back(tmp);
    }
    inFile.close();

}

void ReservationDatabase::storeReservations()
{
    ofstream outFile("Reservations.dat", ios::out | ios::binary);
    for (size_t i = 0; i < reservations.size(); ++i)
        outFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
    outFile.close();


}

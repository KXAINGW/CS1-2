#ifndef MakingReservation_H
#define MakingReservation_H
#include "ReservationDatabase.h"
#include "FlightSchedule.h"
#include<iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;

// It cannot use external in cpp file
extern const char airportName[12][12];
extern const int fullFare[12][12];
extern const int discount[8];

const int maxNumReservations = 1000;
class MakingReservation
{
public:
	MakingReservation(ReservationDatabase& res, FlightSchedule& fs);
	void execute(); 
private:
	ReservationDatabase& reservation;
	FlightSchedule& flightSchedule;

	// member function 
	void chooseArrivalAirport(int departureAirport, int& arrivalAirport);
	void loadFlightSchedules(FlightSchedule& flightSchedule, int departureAirport, int arrivalAirport);
	void chooseFlight(ReservationDatabase& reservation, const FlightSchedule& flightSchedule);
	void inputNumTickets(ReservationDatabase& reservation);
	void displayReservation(ReservationDatabase& reservation, const FlightSchedule& flightSchedule);
	bool duplicate(ReservationDatabase& reservation);
	void loadReservations(ReservationDatabase reservations[], int& numReservations);
	void saveReservation(ReservationDatabase& reservation);
	void clear();
};

#endif

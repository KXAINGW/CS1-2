#ifndef InquiryRefund_H
#define InquiryRefund_H
#ifndef maxNumReservations
#define maxNumReservations 1000
#endif // !maxNumReservations

#include "ReservationDatabase.h"
#include "FlightSchedule.h"

extern const char airportName[12][12];
extern const int fullFare[12][12];
extern const int discount[8];


class InquiryRefund
{
public:
	InquiryRefund(ReservationDatabase& res, FlightSchedule& fs);
	void bookingInquiry(string id);
	void refundApplication(string id);

private:
	ReservationDatabase& reservations;
	FlightSchedule& allflightSchedule;
	bool exist;
	//member function
	void loadReservations(ReservationDatabase reservations[], int& numReservations);
	void loadFlightSchedules(FlightSchedule& flightSchedule);
	void displayReservation(ReservationDatabase& reservation, const FlightSchedule& flightSchedule);
	void clear();
};

#endif
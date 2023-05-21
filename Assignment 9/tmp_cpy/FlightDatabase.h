#ifndef FlightDatabase_H
#define FlightDatabase_H

class FlightDatabase
{
public:
	FlightDatabase();
	void setFlightNo(char new_flightNO[]);
	void setDepartureAirport(int new_departureAirport);
	void setArrivalAirport(int new_arrivalAirport);
	void setDepartureTime(char new_departureTime[]);
	void setArrivalTime(char new_arrivalTime[]);

	char* getFlightNo();
	int getDepartureAirport();
	int getArrivalAirport();
	char* getDepartureTime();
	char* getArrivalTime();

private:
	char flightNo[8];        // flight number
	int departureAirport;    // departure airport code
	int arrivalAirport;      // arrival airport code
	char departureTime[8];   // departure time
	char arrivalTime[8];     // arrival time
};

#endif
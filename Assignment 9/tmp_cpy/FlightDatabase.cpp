#include "FlightDatabase.h"

FlightDatabase::FlightDatabase() :flightNo(), departureAirport(), arrivalAirport(), departureTime(), arrivalTime() {}

void FlightDatabase::setFlightNo(char new_flightNO[])
{
	size_t i = 0;
	for (; new_flightNO[i] != '\0'; ++i)
		flightNo[i] = new_flightNO[i];
	flightNo[i] = '\0';
}

void FlightDatabase::setDepartureAirport(int new_departureAirport)
{
	departureAirport = new_departureAirport;
}

void FlightDatabase::setArrivalAirport(int new_arrivalAirport)
{
	arrivalAirport = new_arrivalAirport;
}

void FlightDatabase::setDepartureTime(char new_departureTime[])
{
	size_t i = 0;
	for (; new_departureTime[i] != '\0'; ++i)
		departureTime[i] = new_departureTime[i];
	departureTime[i] = '\0';
}

void FlightDatabase::setArrivalTime(char new_arrivalTime[])
{
	size_t i = 0;
	for (; new_arrivalTime[i] != '\0'; ++i)
		arrivalTime[i] = new_arrivalTime[i];
	arrivalTime[i] = '\0';
}

char* FlightDatabase::getFlightNo()
{
	return flightNo;
}

int FlightDatabase::getDepartureAirport()
{
	return departureAirport;
}

int FlightDatabase::getArrivalAirport()
{
	return arrivalAirport;
}

char* FlightDatabase::getDepartureTime()
{
	return departureTime;
}

char* FlightDatabase::getArrivalTime()
{
	return arrivalTime;
}

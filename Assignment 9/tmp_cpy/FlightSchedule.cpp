#include "FlightSchedule.h"

FlightSchedule::FlightSchedule() :flights() {}

FlightSchedule::~FlightSchedule()
{
	flights.clear();
}

vector<FlightDatabase> FlightSchedule::getFlightDatabase() const
{
	return flights;
}

vector<FlightDatabase>& FlightSchedule::getFlightDatabase_ref()
{
	return flights;
}

int FlightSchedule::getNumFlights() const
{
	return flights.size();
}

void FlightSchedule::add(const FlightDatabase& flight)
{
	flights.push_back(flight);
}


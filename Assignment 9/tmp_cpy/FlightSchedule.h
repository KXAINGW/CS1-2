#ifndef FlightSchedule_H
#define FlightSchedule_H
#include "FlightDatabase.h"
#include<vector>

using std::vector;
class FlightSchedule
{
public:
	FlightSchedule();
	~FlightSchedule();
	vector<FlightDatabase> getFlightDatabase() const;
	vector<FlightDatabase>& getFlightDatabase_ref();
	int getNumFlights() const;
	void add(const FlightDatabase& flight);

private:
	vector<FlightDatabase> flights;
};
#endif 
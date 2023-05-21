#include "ReservationDatabase.h"

ReservationDatabase::ReservationDatabase() :flightNo(), id(), name(), mobile(), date(), tickets() {}

void ReservationDatabase::setFlightNO(char new_flightNo[])
{
	size_t i = 0;
	for (; new_flightNo[i] != '\0'; ++i)
		flightNo[i] = new_flightNo[i];
	flightNo[i] = '\0';
}

void ReservationDatabase::setID(char new_id[])
{
	size_t i = 0;
	for (; new_id[i] != '\0'; ++i)
		id[i] = new_id[i];
	id[i] = '\0';
}

void ReservationDatabase::setName(char new_name[])
{
	size_t i = 0;
	for (; new_name[i] != '\0'; ++i)
		name[i] = new_name[i];
	name[i] = '\0';
}

void ReservationDatabase::setMobile(char new_mobile[])
{
	size_t i = 0;
	for (; new_mobile[i] != '\0'; ++i)
		mobile[i] = new_mobile[i];
	mobile[i] = '\0';
}

void ReservationDatabase::setDate(char new_date[])
{
	size_t i = 0;
	for (; new_date[i] != '\0'; ++i)
		date[i] = new_date[i];
	date[i] = '\0';

}

void ReservationDatabase::setTickets(int new_tickets[])
{
	for (size_t i = 0; i < 8; ++i)
		tickets[i] = new_tickets[i];
}

char* ReservationDatabase::getFlightNo()
{
	return flightNo;
}

char* ReservationDatabase::getID()
{
	return id;
}

char* ReservationDatabase::getName()
{
	return name;
}

char* ReservationDatabase::getMobile()
{
	return mobile;
}

char* ReservationDatabase::getDate()
{
	return date;
}

int* ReservationDatabase::getTickets()
{
	return tickets;
}

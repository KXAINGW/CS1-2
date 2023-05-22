#ifndef ReservationDatabase_H
#define ReservationDatabase_H
#include<string>
using std::string;
class ReservationDatabase
{
public:
	ReservationDatabase();
	void setFlightNO(char new_flightNo[]);
	void setID(char new_id[]);
	void setName(char new_name[]);
	void setMobile(char new_mobile[]);
	void setDate(char new_date[]);
	void setTickets(int new_tickets[]);

	char* getFlightNo();
	char* getID();
	char* getName();
	char* getMobile();
	char* getDate();
	int* getTickets();
private:
	char flightNo[8]; // flight number
	char id[12];      // ID number
	char name[8];     // name
	char mobile[12];  // mobile phone number
	char date[12];    // departure date
	int tickets[8];
};

#endif
#include "MakingReservation.h"
#include<vector>
#include<iomanip>
#include<fstream>


using std::vector;
using std::setw;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::left;
using std::right;

//error
/*
extern const char airportName[12][12];
extern const int fullFare[12][12];
extern const int discount[8];
*/

MakingReservation::MakingReservation(ReservationDatabase& res, FlightSchedule& fs) :reservation(res), flightSchedule(fs) {}

void MakingReservation::execute()
{
    int departureAirport;
    do {
        cout << "\nDeparture airport:\n";
        for (int i = 1; i <= 11; i++)
            cout << setw(2) << i << ". " << airportName[i] << endl;
        cout << "? ";

        cin >> departureAirport;
    } while (departureAirport < 1 || departureAirport > 11);

    int arrivalAirport;
    // choose arrival airport by input its code, and assign the code to arrivalAirport
    chooseArrivalAirport(departureAirport, arrivalAirport);

    ReservationDatabase reservation;  //eight zero -> int tickets[8]
    cout << "\nDeparture date (yyyy/mm/dd): ";
    char reservationDate[12];
    cin >> reservationDate;
    reservation.setDate(reservationDate);
    cout << endl;

    loadFlightSchedules(flightSchedule, departureAirport, arrivalAirport);

    /*
    vector<FlightDatabase>::iterator it = flightSchedule.getFlightDatabase().begin();
    vector<FlightDatabase>::iterator it_end = flightSchedule.getFlightDatabase().end();
    for (; it != it_end; ++it)
        cout << it->getFlightNO() << endl;
    */

    // display all flights from departureAirport to arrivalAirport
    cout << airportName[departureAirport] << " to " << airportName[arrivalAirport]
        << " / Depart date: " << reservation.getDate() << ".\n\n";
    cout << "Flight   Departure   Arrival   Fare\n";

    //start from 1
    vector<FlightDatabase>::iterator it = flightSchedule.getFlightDatabase_ref().begin();
    vector<FlightDatabase>::iterator it_end = flightSchedule.getFlightDatabase_ref().end();
    for (; it!=it_end; ++it)
        cout << setw(6) << it->getFlightNo()
        << setw(12) << it->getDepartureTime()
        << setw(10) << it->getArrivalTime()
        << setw(7) << fullFare[departureAirport][arrivalAirport] << endl;

    
    // choose a flight by input its number, and assign the number to reservation.flightNo
    chooseFlight(reservation, flightSchedule);
    
    // input the number of tickets for each ticket type,
    // and assign them to reservation.tickets
    inputNumTickets(reservation);

    int totalNumTickets = 0;
    for (int i = 1; i < 8; i++)
        totalNumTickets += reservation.getTickets()[i];
    if (totalNumTickets == 0)
    {
        cout << "Your booking could not be completed!\n";
        return;
    }

    
    displayReservation(reservation, flightSchedule);
    
    cout << "\nID number: ";
    char id[12];
    cin >>id;
    reservation.setID(id);

    // check if there is a record, x, of Reservations.dat such that
    // x.flightNo == reservation.flightNo, x.id == reservation.id and
    // x.date == reservation.date
    if (duplicate(reservation))
        return;

    char name[8];    
    char mobile[12]; 
    cout << "\nName: ";
    cin >> name;
    cout << "\nMobile: ";
    cin >> mobile;
    reservation.setName(name);
    reservation.setMobile(mobile);

    // append reservation to the end of Reservations.dat
    saveReservation(reservation);

    cout << "\nBooking completed!\n";
/*    */
}

void MakingReservation::chooseArrivalAirport(int departureAirport, int& arrivalAirport)
{
    //set fit arrivalairport
    int arrivalairportName_Index[12];
    int arrivalairportNum = 0;
    for (int i = 1; i < 12; i++)  //start from 1
        if (fullFare[i][departureAirport] != 0)
            arrivalairportName_Index[++arrivalairportNum] = i;  //arrivalairportName_Index start from 1

    //judge input arrivalAirport
    do
    {
        cout << endl;
        cout << "Arrival airport:" << endl;
        for (int i = 1; i <= arrivalairportNum; i++)  //start from 1
            cout << setw(2) << arrivalairportName_Index[i] << ". " << airportName[arrivalairportName_Index[i]] << endl;
        cout << "? ";
        cin >> arrivalAirport;
    } while ((arrivalAirport < 1 || arrivalAirport > 11) || !fullFare[departureAirport][arrivalAirport]);      //arrivalAirport so  big that fullFare overload?  ans:x64,x86 differ

}

// load all flights from departureAirport to arrivalAirport,
// and put them into the array flights
void MakingReservation::loadFlightSchedules(FlightSchedule& flightSchedule, int departureAirport, int arrivalAirport)
{
    //read Flight Schedule.dat
    ifstream inFile("Flight Schedule.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Flight Schedule.dat could not be opened.\n";
        exit(1);
    }

    inFile.seekg(0, ios::end);
    int numFlights = inFile.tellg() / sizeof(FlightDatabase);
    inFile.seekg(0, ios::beg);
    for (int i = 1; i <= numFlights; i++)  //start from 1
    {
        FlightDatabase tmp;
        inFile.read(reinterpret_cast<char*>(&tmp), sizeof(FlightDatabase));
        if(tmp.getDepartureAirport()==departureAirport&&tmp.getArrivalAirport()==arrivalAirport)
            flightSchedule.add(tmp);
    }
    inFile.close();
}

// choose a flight by input its number, and assign the number to reservation.flightNo
void MakingReservation::chooseFlight(ReservationDatabase& reservation,  const FlightSchedule& flightSchedule)
{
    bool loop = 1;
    while (loop)
    {
        char inputFightNum[8];
        cout << "\nFight number: ";
        cin >> inputFightNum;
        vector<FlightDatabase>fs_cpy(flightSchedule.getFlightDatabase());
        vector<FlightDatabase>::iterator it = fs_cpy.begin();
        vector<FlightDatabase>::iterator it_end = fs_cpy.end();
        for (; it!=it_end; ++it)  //start from 1
        {
            if (strcmp(it->getFlightNo(), inputFightNum) == 0)
            {
                char flightNo[8];
                strcpy_s(flightNo, strlen(inputFightNum) + 1, inputFightNum);
                reservation.setFlightNO(flightNo);
                loop = 0;
                break;
            }
        }
    }

}

void MakingReservation::inputNumTickets(ReservationDatabase& reservation)
{
    int* rs_tickets = reservation.getTickets();
    do {
        cout << "\nNumber of infant tickets (0 ~ 4): ";
        cin >> rs_tickets[3];
    } while (rs_tickets[3] < 0 || rs_tickets[3] > 4);

    int numTickets = 0;
    int numAdults = 0;
    do
    {
        numTickets = 0;

        cout << "\nNumber of full fare tickets (0 ~ 4): ";
        cin >> rs_tickets[1];
        numTickets += rs_tickets[1];

        cout << "\nNumber of child tickets (0 ~ 4): ";
        cin >> rs_tickets[2];
        numTickets += rs_tickets[2];

        cout << "\nNumber of senior citizen tickets (0 ~ 4): ";
        cin >> rs_tickets[4];
        numTickets += rs_tickets[4];

        cout << "\nNumber of impaired tickets (0 ~ 4): ";
        cin >> rs_tickets[5];
        numTickets += rs_tickets[5];

        cout << "\nNumber of impaired companion tickets (0 ~ 4): ";
        cin >> rs_tickets[6];
        numTickets += rs_tickets[6];

        cout << "\nNumber of military tickets (0 ~ 4): ";
        cin >> rs_tickets[7];
        numTickets += rs_tickets[7];

        numAdults = rs_tickets[1] + rs_tickets[4] +
            rs_tickets[5] + rs_tickets[6] +
            rs_tickets[7];

        if (numTickets > 4)
            cout << "\nThis booking system accepts a maximum of 4 passengers"
            << "( including children ) per booking.\n"
            << "If there are more than 4 passengers, please make multiple bookings.\n";
        else if (numAdults < rs_tickets[3])
            cout << "\nEach infant must always be accompanied by at least one adult.\n";

    } while (numTickets > 4 || numAdults < rs_tickets[3]);

    cout << endl;

}

void MakingReservation::displayReservation(ReservationDatabase& reservation, const FlightSchedule& flightSchedule)
{
    int k;
    int numFlights = flightSchedule.getNumFlights();
    vector<FlightDatabase>flights(flightSchedule.getFlightDatabase());

    for (k = 0; k < numFlights; k++)
        if (strcmp(reservation.getFlightNo(), flights[k].getFlightNo()) == 0)
            break;

    cout << "Ticket information:\n\n";
    cout << "Date: " << reservation.getDate() << endl;
    cout << "Flight: B7-" << reservation.getFlightNo() << endl << endl;

    int departureAirport = flights[k].getDepartureAirport();
    int arrivalAirport = flights[k].getArrivalAirport();

    cout << setw(9) << right << airportName[departureAirport] << " -> "
        << setw(9) << left << airportName[arrivalAirport] << endl;

    cout << setw(9) << right << flights[k].getDepartureTime() << "    ";
    cout << setw(9) << left << flights[k].getArrivalTime() << endl << endl;

    char ticketType[8][24] = { "", "Full Fare", "Child Fare", "Infant Fare",
                                       "Senior Citizen Fare",     "Impaired Fare",
                                       "Impaired Companion Fare", "Military Fare" };

    int total = 0;
    int fare;
    for (int i = 1; i <= 7; i++)
        if (reservation.getTickets()[i] > 0)
        {
            fare = fullFare[departureAirport][arrivalAirport] * discount[i] / 100;
            total += (fare * reservation.getTickets()[i]);
            cout << right << setw(23) << ticketType[i] << "  TWD "
                << setw(4) << fare << " x " << reservation.getTickets()[i] << endl;
        }

    cout << "\nTotal: " << total << endl;
}


// check if there is a record, x, of Reservations.dat such that
// x.flightNo == reservation.flightNo, x.id == reservation.id and
// x.date == reservation.date
bool MakingReservation::duplicate(ReservationDatabase& reservation )
{
    ReservationDatabase allReservation[maxNumReservations];
    int num = 0;
    loadReservations(allReservation, num);

    for (int i = 1; i <= num; i++)  //start from 1
    {
        if (strcmp(allReservation[i].getFlightNo(), reservation.getFlightNo()) == 0 && strcmp(allReservation[i].getDate(), reservation.getDate()) == 0 && strcmp(allReservation[i].getID(), reservation.getID()) == 0)
        {
            cout << "\nThe reservation appears to be a duplicate to an existing reservation!\n";
            return 1;
        }
    }
    return 0;
}

// load all reservations from Reservations.dat and put them to the array reservations
void MakingReservation::loadReservations(ReservationDatabase reservations[], int& numReservations)
{
    ifstream inFile("Reservations.dat", ios::binary);
    if (!inFile)
    {
        cerr << "Reservations.dat could not be opened.\n";
        exit(1);
    }
    inFile.seekg(0, ios::end);
    numReservations = inFile.tellg() / sizeof(ReservationDatabase);
    inFile.seekg(0, ios::beg);
    for (int i = 1; i <= numReservations; i++)  //start from 1
        inFile.read(reinterpret_cast<char*>(&reservations[i]), sizeof(ReservationDatabase));
    inFile.close();
}

// append reservation to the end of Reservations.dat
void MakingReservation::saveReservation(ReservationDatabase& reservation)
{
    ofstream outFile("Reservations.dat", ios::app | ios::binary);
    outFile.write(reinterpret_cast<const char*>(&reservation), sizeof(ReservationDatabase));
    outFile.close();
}
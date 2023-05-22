#include "InquiryRefund.h"
#include<fstream>
#include<iostream>
#include<iomanip>

using std::ifstream;
using std::ofstream;
using std::ios;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::setw;
using std::left;
using std::right;

InquiryRefund::InquiryRefund(ReservationDatabase& res, FlightSchedule& fs):reservations(res), allflightSchedule(fs)
{
}

void InquiryRefund::bookingInquiry(string id)
{
    clear();
    ReservationDatabase allReservation[maxNumReservations];
    int num = 0;
    loadReservations(allReservation, num);  //allReservation start from 1


    //read all flight schedule
    
    loadFlightSchedules(allflightSchedule);

 
    int count = 1;
    exist = 0;
    for (int i = 1; i <= num; i++)
    {
        if (strcmp(allReservation[i].getID(), id.c_str()) == 0)
        {
            cout << endl << count++ << ".  ";
            displayReservation(allReservation[i], allflightSchedule);
            exist = 1;
        }
    }
    if (exist)
        return;
    else
        cout << "\nNo reservations!\n";


}

void InquiryRefund::refundApplication(string id)
{
    clear();
    bookingInquiry(id);

    if (!exist)
        return;

    cout << "\nEnter your choice: ";
    int choice;
    cin >> choice;
    ReservationDatabase allReservation[maxNumReservations];
    int allNumReservation = 0;
    loadReservations(allReservation, allNumReservation);
    //delete allReservation[choice]
    ofstream outFile("Reservations.dat", ios::binary);
    int index = 1;
    for (int i = 1; i <= allNumReservation; i++)  //allReservation start from 1
    {
        if (strcmp(allReservation[i].getID(), id.c_str()) == 0)
            if (index++ == choice)
                continue;
        outFile.write(reinterpret_cast<char*>(&allReservation[i]), sizeof(ReservationDatabase));
    }
    cout << "\nThe seleted booking has been deleted.\n";
    outFile.close();


}


// load all reservations from Reservations.dat and put them to the array reservations
void InquiryRefund::loadReservations(ReservationDatabase reservations[], int& numReservations)
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

//read all flight schedule
void InquiryRefund::loadFlightSchedules(FlightSchedule& allflightSchedule)
{
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
        allflightSchedule.add(tmp);
    }
    inFile.close();

}

void InquiryRefund::displayReservation(ReservationDatabase& reservation, const FlightSchedule& allflightSchedule)
{
    int k;
    int numFlights = allflightSchedule.getNumFlights();
    vector<FlightDatabase>flights(allflightSchedule.getFlightDatabase());

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

// clear flightSchedule data
void InquiryRefund::clear()
{
    allflightSchedule.~FlightSchedule();
}
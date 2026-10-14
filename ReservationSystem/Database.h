#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include "Vehicle.h"

using namespace std;

class Database
{
private: 

    // Maximum number of vehicles and reservations
    static const int MaxVehicles = 50;
    static const int MaxReservations = 3;

    // Array of pointers to vehicle objects
    Vehicle* Vehicles[MaxVehicles];

    // Stores up to 3 reservation dates for each vehicle
    int Reservations[MaxVehicles][MaxReservations];

    // Number of vehicles currently in the database
    int NumVehicles;

    // Current day of the reservation system
    int CurrentDate;

public:

    // Constructor and destructor
    Database();
    ~Database();

    // Vehicle inventory functions
    bool AddVehicle(Vehicle* TheVehicle);
    int GetNumVehicles() const;
    Vehicle* GetVehicle(int VehicleIndex) const;

    // Vehicle search functions
    void SearchByMake(string TheMake) const;
    void SearchByModel(string TheModel) const;
    void SearchByYear(int TheYear) const;
    void SearchByColor(string TheColor) const;
    void SearchByPropulsionType(string ThePropulsionType) const;

    // Vehicle reservation functions
    bool ReserveVehicle(int VehicleIndex, int ReservationDate);
    bool IsVehicleAvailable(int VehicleIndex, int ReservationDate) const;

    // Display vehicle information
    void PrintAllVehicles() const;
    void PrintReservedVehicles() const;
    void PrintAvailableVehicles() const;

    // Date management functions
    void AdvanceDate();
    int GetCurrentDate() const;

};

#endif
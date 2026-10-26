#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include "Vehicle.h"

using namespace std;

class Database
{
private:
    static const int MaxVehicles = 50;
    static const int MaxReservations = 3;

    // Columns:
    // 0 = Make
    // 1 = Model
    // 2 = Year
    // 3 = Color
    // 4 = Propulsion type
    // 5 = Range
    // 6 = Efficiency
    string VehicleInfo[MaxVehicles][7];

    // Vehicle objects used for the propulsion information.
    Vehicle* Vehicles[MaxVehicles];

    // Column 0 = Vehicle number
    // Column 1 = Reservation day
    int ReservedVehicles[MaxVehicles * MaxReservations][2];

    int NumVehicles;
    int NumReservations;
    int CurrentDate;

    string GetVehicleInfo(int VehicleNumber);

public:
    Database();

    int ReadInventory(string FileName);
    int GetNumVehicles();

    string SearchByMake(string TheMake);
    string SearchByModel(string TheModel);
    string SearchByYear(string TheYear);
    string SearchByColor(string TheColor);
    string SearchByPropulsionType(string ThePropulsionType);

    bool ReserveVehicle(int VehicleNumber, int ReservationDate);
    bool IsVehicleAvailable(int VehicleNumber, int ReservationDate);

    string PrintAllVehicles();
    string PrintReservedVehicles();
    string PrintAvailableVehicles();

    void AdvanceDate();
    int GetCurrentDate();
};

#endif
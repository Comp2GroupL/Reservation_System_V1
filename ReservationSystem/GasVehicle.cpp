///////////////////////////////////////////////////////////////////////////////
// GasVehicle.cpp
// Stores capacity and efficiency, and calculates the driving range.
///////////////////////////////////////////////////////////////////////////////
#include "GasVehicle.h"
#include <sstream>
#include <iomanip>

using namespace std;

GasVehicle::GasVehicle()
{
    FuelCapacity = 0.0;
    Efficiency = 0.0;
}

void GasVehicle::SetFuelCapacity(double TheCapacity)
{
    FuelCapacity = TheCapacity;
}

void GasVehicle::SetEfficiency(double TheEfficiency)
{
    Efficiency = TheEfficiency;
}

double GasVehicle::GetFuelCapacity() const
{
    return FuelCapacity;
}

double GasVehicle::GetEfficiency() const
{
    return Efficiency;
}

string GasVehicle::GetPropulsionInfo() const
{
    // Capacity multiplied by efficiency gives the range in miles.
    double Range = FuelCapacity * Efficiency;
    ostringstream Information;

    Information << fixed << setprecision(2);
    Information << "Propulsion: Gas (ICE)"
        << " | Range: " << Range << " miles"
        << " | Efficiency: " << Efficiency << " mpg";

    return Information.str();
}

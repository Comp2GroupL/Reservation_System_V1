///////////////////////////////////////////////////////////////////////////////
// ElectricVehicle.cpp
// Stores capacity and efficiency, and calculates the driving range.
///////////////////////////////////////////////////////////////////////////////
#include "ElectricVehicle.h"
#include <sstream>
#include <iomanip>

using namespace std;

ElectricVehicle::ElectricVehicle()
{
    EnergyCapacity = 0.0;
    Efficiency = 0.0;
}

void ElectricVehicle::SetEnergyCapacity(double TheCapacity)
{
    EnergyCapacity = TheCapacity;
}

void ElectricVehicle::SetEfficiency(double TheEfficiency)
{
    Efficiency = TheEfficiency;
}

double ElectricVehicle::GetEnergyCapacity() const
{
    return EnergyCapacity;
}

double ElectricVehicle::GetEfficiency() const
{
    return Efficiency;
}

string ElectricVehicle::GetPropulsionInfo() const
{
    // Capacity multiplied by efficiency gives the range in miles.
    double Range = EnergyCapacity * Efficiency;
    ostringstream Information;

    Information << fixed << setprecision(2);
    Information << "Propulsion: Electricity (EV)"
        << " | Range: " << Range << " miles"
        << " | Efficiency: " << Efficiency << " miles/kWh";

    return Information.str();
}

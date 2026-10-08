///////////////////////////////////////////////////////////////////////////////
// ElectricVehicle.h
// Derived vehicle class with capacity and efficiency information.
///////////////////////////////////////////////////////////////////////////////
#ifndef ELECTRICVEHICLE_H
#define ELECTRICVEHICLE_H

#include "Vehicle.h"

using namespace std;

class ElectricVehicle : public Vehicle
{
private:
    double EnergyCapacity;
    double Efficiency;

public:
    ElectricVehicle();

    void SetEnergyCapacity(double TheCapacity);
    void SetEfficiency(double TheEfficiency);
    double GetEnergyCapacity() const;
    double GetEfficiency() const;

    string GetPropulsionInfo() const override;
};

#endif

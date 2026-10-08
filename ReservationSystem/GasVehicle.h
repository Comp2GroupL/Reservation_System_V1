///////////////////////////////////////////////////////////////////////////////
// GasVehicle.h
// Derived vehicle class with capacity and efficiency information.
///////////////////////////////////////////////////////////////////////////////
#ifndef GASVEHICLE_H
#define GASVEHICLE_H

#include "Vehicle.h"

using namespace std;

class GasVehicle : public Vehicle
{
private:
    double FuelCapacity;
    double Efficiency;

public:
    GasVehicle();

    void SetFuelCapacity(double TheCapacity);
    void SetEfficiency(double TheEfficiency);
    double GetFuelCapacity() const;
    double GetEfficiency() const;

    string GetPropulsionInfo() const override;
};

#endif

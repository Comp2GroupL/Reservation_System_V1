///////////////////////////////////////////////////////////////////////////////
// Vehicle.h
// Base class containing the information shared by all vehicles.
///////////////////////////////////////////////////////////////////////////////
#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

using namespace std;

class Vehicle
{
private:
    string Make;
    string Model;
    int Year;

public:
    Vehicle();
    virtual ~Vehicle();

    void SetMake(string TheMake);
    void SetModel(string TheModel);
    void SetYear(int TheYear);

    string GetMake() const;
    string GetModel() const;
    int GetYear() const;

    // Each derived class supplies its own propulsion information.
    virtual string GetPropulsionInfo() const = 0;
};

#endif

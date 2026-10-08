///////////////////////////////////////////////////////////////////////////////
// Vehicle.cpp
// Constructors, setters, and getters for the Vehicle base class.
///////////////////////////////////////////////////////////////////////////////
#include "Vehicle.h"

using namespace std;

Vehicle::Vehicle()
{
    Make = "";
    Model = "";
    Year = 0;
}

// Virtual so derived objects can be deleted through Vehicle pointers.
Vehicle::~Vehicle()
{}

void Vehicle::SetMake(string TheMake)
{
    Make = TheMake;
}

void Vehicle::SetModel(string TheModel)
{
    Model = TheModel;
}

void Vehicle::SetYear(int TheYear)
{
    Year = TheYear;
}

string Vehicle::GetMake() const
{
    return Make;
}

string Vehicle::GetModel() const
{
    return Model;
}

int Vehicle::GetYear() const
{
    return Year;
}

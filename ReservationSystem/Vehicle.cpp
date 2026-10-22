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
    Color = "";
    PropulsionType = "";
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

void Vehicle::SetColor(string TheColor)
{
    Color = TheColor;
}

void  Vehicle::SetPropulsionType(string ThePropulsionType)
{
    PropulsionType = ThePropulsionType;
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

string Vehicle::GetColor() const
{
    return Color;
}

string Vehicle::GetPropulsionType() const
{
    return PropulsionType;
}
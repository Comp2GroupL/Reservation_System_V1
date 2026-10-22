///////////////////////////////////////////////////////////////////////////////
//Currently making edits to match new 
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GasCar.h"
#include "ElectricCar.h"

int main(int argc, char* argv[])
{
    //Creates a file object to read the inventory
    std::ifstream InFile;

    //Stores each line of the inventory file as it is read
    std::string Line;

    //Creates an array to store pointers to Vehicle objects
#define DATABASE_SIZE (20)
    Vehicle* Database[DATABASE_SIZE];

    //Opens the inventory file for reading
    InFile.open("Inventory.txt");

    //Checks if the file failed to open
    if (!InFile.is_open())
    {
        //Tells the user the file could not be opened
        std::cout << "Error! Inventory file could not be opened." << std::endl;
        return -1;
    } // if()

    //Counts how many vehicles have been loaded from the file
    int NumVehicles = 0;

    //Reads the inventory file one line at a time
    while (getline(InFile, Line))
    {
        //Creates a string stream to break the line into fields
        std::istringstream Record(Line);

        //Temporary variable to hold each parsed field
        std::string Field;

        //Variables to store each field from the line
        std::string Make, Model, Year, EngineType, Capacity, Efficiency;

        //Counts how many fields have been read from the line
        int FieldCount = 0;

        //Reads each word from the line and assigns it to the correct variable
        while (Record >> Field)
        {
            FieldCount++;
            switch (FieldCount)
            {
            case 1: { Make = Field; break; }
            case 2: { Model = Field; break; }
            case 3: { Year = Field; break; }
            case 4: { EngineType = Field; break; }
            case 5: { Capacity = Field; break; }
            case 6: { Efficiency = Field; break; }
            } // switch()
        } // while()

        //Checks if the line did not contain exactly six fields
        if (FieldCount != 6)
        {
            //Tells the user the file format is incorrect
            std::cout << "Error! Inventory file is manformed." << std::endl;

            //Prints the bad line for debugging
            std::cout << Line << std::endl;

            return -2;
        } // if()

        //Checks the propulsion type and creates the correct vehicle object
        if (EngineType == "ICE")
        {
            //Creates a gas-powered car using the parsed values
            GasCar* GC = new GasCar(Make, Model, std::stoi(Year),
                std::stof(Capacity), std::stof(Efficiency));

            //Stores the gas car in the database
            Database[NumVehicles] = GC;
        } // if()
        else if (EngineType == "EV")
        {
            //Creates an electric car using the parsed values
            ElectricCar* EC = new ElectricCar(Make, Model, std::stoi(Year),
                std::stof(Capacity), std::stof(Efficiency));

            //Stores the electric car in the database
            Database[NumVehicles] = EC;
        } // if...if...else()
        else
        {
            //Tells the user the propulsion type was not recognized
            std::cout << "Error! Unrecognized propulsion type." << std::endl;
            return -3;
        } // if...else()

        //Moves to the next position in the database array
        NumVehicles++;
    } // while()
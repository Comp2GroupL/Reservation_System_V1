///////////////////////////////////////////////////////////////////////////////
// This program implements a rudimentary used car database.  It reads a text
// file that contains the list of cars in the database.  Each line of the file
// represents a single vehicle where there are six fields: Make, Model, Year,
// Engine Type (ICE or EV), Fuel/Energy Capacity, and mileage efficiency.
// The user is allowed to querry the database to see the list of vehicles that
// match their search criteria.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GasVehicle.h"
#include "ElectricVehicle.h"

int main(int argc, char* argv[])
{
    // The inventory file
    std::ifstream InFile;
    // The string for each line of the inventory file
    std::string Line;
    // The used car database as pointers to objects
#define DATABASE_SIZE (20)
    Vehicle* Database[DATABASE_SIZE];

    // Open the output file
    InFile.open("Inventory.txt");
    if (!InFile.is_open())
    {
        std::cout << "Error! Inventory file could not be opened." << std::endl;
        return -1;
    } // if()

  // Read the contents of the file one line at a time
    int NumVehicles = 0;
    while (getline(InFile, Line))
    {
        // String stream for parsing words from the line
        std::istringstream Record(Line);
        // String to hold the parsed field
        std::string Field;
        // Strings to hold the individual fields
        std::string Make, Model, Year, EngineType, Capacity, Efficiency;

        // Get the strings from the line
        int FieldCount = 0;
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
        if (FieldCount != 6)
        {
            std::cout << "Error! Inventory file is malformed." << std::endl;
            std::cout << Line << std::endl;
            return -2;
        } // if()

      // Depending on the propulsion type, instantiate a GasCar or ElectricCar,
      //   populate the fields, and put it into the database array
        if (EngineType == "ICE")
        {
            // Instantiate a gas propulsion car object
            GasVehicle* gas_ptr = new GasVehicle();
            // Set the fields
            gas_ptr->SetMake(Make);
            gas_ptr->SetModel(Model);
            gas_ptr->SetYear(stoi(Year));
            gas_ptr->SetFuelCapacity(stof(Capacity));
            gas_ptr->SetEfficiency(stof(Efficiency));
            // Insert the gas car into the database
            Database[NumVehicles] = gas_ptr;
        } // if()
        else if (EngineType == "EV")
        {
            // Instantiate an electric Propulsion car object
            ElectricVehicle* electric_ptr = new ElectricVehicle();
            // Set the fields
            electric_ptr->SetMake(Make);
            electric_ptr->SetModel(Model);
            electric_ptr->SetYear(stoi(Year));
            electric_ptr->SetEnergyCapacity(stof(Capacity));
            electric_ptr->SetEfficiency(stof(Efficiency));
            // Insert the Electric car into the database
            Database[NumVehicles] = electric_ptr;
        } // if...if...else()
        else
        {
            std::cout << "Error! Unrecognized propulsion type." << std::endl;
            return -3;
        } // if...else()

       // Increment the running counter of the cars in the inventory
        NumVehicles++;
    } // while()

    bool ExitRequested = false;
    do {
        int date = 1;
        char Command;
        // Prompt the user for the program option
        std::cout << "============== CAR RESERVATION SYSTEM ==============" << std::endl << std::endl;
        std::cout << "Current Date: Day " << date << std::endl << std::endl;
        std::cout << "1. Search Vehicles";
        std::cout << "2. Reserve a Vehicle" << std::endl;
        std::cout << "3. Display All Vehicles" << std::endl;
        std::cout << "4. Display Vehicles With Reservations" << std::endl;
        std::cout << "5. Display Fully Available Vehicles" << std::endl;
        std::cout << "6. Advance Current Date" << std::endl;
        std::cout << "7. Exit the Program" << std::endl << std::endl;
        std::cout << "Enter Command (1-7): ";
        std::cin >> Command;

        // Process the command
        switch (Command)
        {
        case '1': // Search Vehicles
        {
            
            break;
        } // case '1'
        case '2': // Reserve a Vehicle
        {
            
            break;
        } // case '2'
        case '3': // Display All Vehicles
        {
            
            break;
        } // case '3'
        case '4': // Display Vehicles with Reservations
        {
            
            break;
        } // case '4'
        case '5': // Display Fully Available Vehicles
        {
            
            break;
        } // case '5'
        case '6': // Advance Current Date
        {
            date++;
            break;
        } // case '6'
        case '7': // Exit the Program
        {
            ExitRequested = true;
            break;
        } // case '7'
       // "otherwise" is not needed, any other command is ignored
        } // switch()

    } while (!ExitRequested);

    // No error possible
    return 0;
} // main()

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
        char Command;
        // Prompt the user for the program option (search by Make, Model, Year, or
        //   or exit the program)
        std::cout << "Enter Command (? for help) > ";
        std::cin >> Command;

        // Process the command
        switch (Command)
        {
        case '?': // Help screen
        {
            std::cout << " ? = Display Help" << std::endl;
            std::cout << " A = Search by Make" << std::endl;
            std::cout << " O = Search by Model" << std::endl;
            std::cout << " Y = Search by Year" << std::endl;
            std::cout << " Q = Quit / Exit the program" << std::endl;
            break;
        } // Case '?'
        case 'a': case 'A': // Search by Make
        {
            // Prompt the user for the search criteria
            std::string DesiredMake;
            std::cout << "Enter Make > ";
            std::cin >> DesiredMake;

            // Search the database
            // Print out matching entries
            for (int i = 0; i < NumVehicles; ++i) {
                if (Database[i]->GetMake() == DesiredMake) {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << " "
                        << Database[i]->GetPropulsionInfo() << endl;
                }
            }
            break;
        } // case 'a' or 'A'
        case 'o': case 'O': // Search by Model
        {
            // Prompt the user for the search criteria
            std::string DesiredModel;
            std::cout << "Enter Model > ";
            std::cin >> DesiredModel;

            // Search the database
            // Print out matching entries
            for (int i = 0; i < NumVehicles; ++i) {
                if (Database[i]->GetModel() == DesiredModel) {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << " "
                        << Database[i]->GetPropulsionInfo() << endl;
                }
            }
            break;
        } // case 'o' or 'O'
        case 'y': case 'Y': // Search by Year
        {
            // Prompt the user for the search criteria
            int DesiredYear;
            std::cout << "Enter Year > ";
            std::cin >> DesiredYear;

            // Search the database
            // Print out matching entries
            for (int i = 0; i < NumVehicles; ++i) {
                if (Database[i]->GetYear() == DesiredYear) {
                    cout << Database[i]->GetMake() << " "
                        << Database[i]->GetModel() << " "
                        << Database[i]->GetYear() << " "
                        << Database[i]->GetPropulsionInfo() << endl;
                }
            }
            break;
        } // case 'y' or 'Y'
        case 'q': case 'Q': // Exit the program
        {
            ExitRequested = true;
            break;
        } // case 'q' or 'Q'
       // "otherwise" is not needed, any other command is ignored
        } // switch()

    } while (!ExitRequested);

    // No error possible
    return 0;
} // main()

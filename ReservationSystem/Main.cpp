///////////////////////////////////////////////////////////////////////////////
// Explanation goes here
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "GasVehicle.h"
#include "ElectricVehicle.h"
#include "Database.h"

void DisplaySearchMenu(Database& db) {
    char SearchChoice;

    cout << "\n============== SEARCH VEHICLES ==============" << endl;
    cout << "1. Search by Make" << endl;
    cout << "2. Search by Model" << endl;
    cout << "3. Search by Year" << endl;
    cout << "4. Search by Color" << endl;
    cout << "5. Search by Propulsion Type (ICE/EV)" << endl;
    cout << "Enter Choice (1-5): ";

    cin >> SearchChoice;

    string Term;

    switch (SearchChoice)
    {
    case '1':
        cout << "Enter Make: ";
        getline(cin, Term);
        cout << db.SearchByMake(Term) << endl;
        break;
    case '2':
        cout << "Enter Model: ";
        getline(cin, Term);
        cout << db.SearchByModel(Term) << endl;
        break;
    case '3':
        cout << "Enter Year: ";
        getline(cin, Term);
        cout << db.SearchByYear(Term) << endl;
        break;
    case '4':
        cout << "Enter Color: ";
        getline(cin, Term);
        cout << db.SearchByColor(Term) << endl;
        break;
    case '5':
        cout << "Enter Propulsion Type: ";
        getline(cin, Term);
        cout << db.SearchByPropulsionType(Term) << endl;
        break;
    }
}

int main(int argc, char* argv[])
{
    Database db;

    if (db.ReadInventory("Inventory.txt") != 0)
    {
        cout << "Failed to initialize database inventory. Exiting program." << endl;
        return -1;
    }

    bool ExitRequested = false;
    do {
        char Command;
        // Prompt the user for the program option
        std::cout << "\n============== CAR RESERVATION SYSTEM ==============" << std::endl << std::endl;
        std::cout << "Current Date: Day " << db.GetCurrentDate() << std::endl << std::endl;
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
            DisplaySearchMenu(db);
            break;
        } // case '1'
        case '2': // Reserve a Vehicle
        {
            int VehicleID = 0;
            int ReserveDay = 0;

            cout << "\nEnter Vehicle ID: ";
            if (!(cin >> VehicleID))
            {
                cout << "Invalid vehicle ID entered." << endl;
                break;
            }

            cout << "Enter Reservation Day: ";
            if (!(cin >> ReserveDay))
            {
                cout << "Invalid day entered." << endl;
                break;
            }
            break;

            if (db.ReserveVehicle(VehicleID, ReserveDay))
            {
                cout << "Success: Vehicle #" << VehicleID << " reserved for Day " << ReserveDay << "." << endl;
            }
            else
            {
                cout << "ERROR: Reservation failed. The vehicle may already be reserved on that date, exceeding max 3 future reservations, or invalid day provided." << endl;
            }
            break;
        } // case '2'
        case '3': // Display All Vehicles
        {
            cout << db.PrintAllVehicles() << endl;
            break;
        } // case '3'
        case '4': // Display Vehicles with Reservations
        {
            cout << db.PrintReservedVehicles() << endl;
            break;
        } // case '4'
        case '5': // Display Fully Available Vehicles
        {
            cout << db.PrintAvailableVehicles() << endl;
            break;
        } // case '5'
        case '6': // Advance Current Date
        {
            db.AdvanceDate();
            cout << "Date advanced. Current Date is now: Day " << db.GetCurrentDate() << endl;
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

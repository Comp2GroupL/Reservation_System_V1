///////////////////////////////////////////////////////////////////////////////
// Explanation goes here
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Database.h"

void DisplaySearchMenu(Database* pDatabase) {
    char Command;

    cout << "\n============== SEARCH VEHICLES ==============" << endl;
    cout << "1. Search by Make" << endl;
    cout << "2. Search by Model" << endl;
    cout << "3. Search by Year" << endl;
    cout << "4. Search by Color" << endl;
    cout << "5. Search by Propulsion Type (ICE/EV)" << endl;
    cout << "6. Return to Main Menu" << endl;
    cout << "Enter Choice (1-6): ";

    cin >> Command;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard unwanted characters currently sitting in the input buffer 

    string term;

    switch (Command)
    {
    case '1': // Search by Make
    {
        cout << "Enter Make: ";
        getline(cin, term);
        cout << pDatabase->SearchByMake(term) << endl;
        break;
    } // case '1'
    case '2': // Search by Model
    {
        cout << "Enter Model: ";
        getline(cin, term);
        cout << pDatabase->SearchByModel(term) << endl;
        break;
    } // case '2'
    case '3': // Search by Year
    {
        cout << "Enter Year: ";
        getline(cin, term);
        cout << pDatabase->SearchByYear(term) << endl;
        break;
    } // case '3'
    case '4': // Search by Color
    {
        cout << "Enter Color: ";
        getline(cin, term);
        cout << pDatabase->SearchByColor(term) << endl;
        break;
    } // case '4'
    case '5': // Search by Propulsion Type (ICE/EV)
    {
        cout << "Enter Propulsion Type: ";
        getline(cin, term);
        cout << pDatabase->SearchByPropulsionType(term) << endl;
        break;
    } // case '5'
    case '6': // Return to Main Menu
    {
        // Exits DisplaySearchMenu and goes straight back to main()
        return;
    } // case '6'
    } // switch()
    
} // DisplaySearchMenu()

int main(int argc, char* argv[])
{
    Database* pDatabase = new Database;

    if (pDatabase->ReadInventory("Inventory.txt") != 0)
    {
        cout << "Failed to initialize database inventory. Exiting program." << endl;
        return -1;
    }

    bool ExitRequested = false;
    do {
        char Command;
        // Prompt the user for the program option
        std::cout << "\n============== CAR RESERVATION SYSTEM ==============" << std::endl << std::endl;
        std::cout << "Current Date: Day " << pDatabase->GetCurrentDate() << std::endl << std::endl;
        std::cout << "1. Search Vehicles" << std::endl;
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
            DisplaySearchMenu(pDatabase);
            break;
        } // case '1'
        case '2': // Reserve a Vehicle
        {
            int VehicleID = 0;
            int ReserveDay = 0;

            cout << "\nEnter Vehicle ID: ";
            if (!(cin >> VehicleID))
            {
                cin.clear(); // reset the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard unwanted characters currently sitting in the input buffer
                cout << "Invalid vehicle ID entered." << endl;
                break;
            }

            cout << "Enter Reservation Day: ";
            if (!(cin >> ReserveDay))
            {
                cin.clear(); // reset the error flags
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard unwanted characters currently sitting in the input buffer
                cout << "Invalid day entered." << endl;
                break;
            }
            
            if (pDatabase->ReserveVehicle(VehicleID, ReserveDay))
            {
                cout << "Success: Vehicle #" << VehicleID << " reserved for Day " << ReserveDay << "." << endl;
            }
            else
            {
                cout << "Error: Reservation failed." << endl;
            }
            break;
        } // case '2'
        case '3': // Display All Vehicles
        {
            cout << pDatabase->PrintAllVehicles() << endl;
            break;
        } // case '3'
        case '4': // Display Vehicles with Reservations
        {
            cout << pDatabase->PrintReservedVehicles() << endl;
            break;
        } // case '4'
        case '5': // Display Fully Available Vehicles
        {
            cout << pDatabase->PrintAvailableVehicles() << endl;
            break;
        } // case '5'
        case '6': // Advance Current Date
        {
            pDatabase->AdvanceDate();
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

    // Clean up heap memory before exiting
    delete pDatabase;

    // No error possible
    return 0;
} // main()

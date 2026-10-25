///////////////////////////////////////////////////////////////////////////////
// Database.cpp
// Reads inventory, searches vehicles, and manages reservations.
///////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include "GasVehicle.h"
#include "ElectricVehicle.h"
#include "Database.h"

using namespace std;

Database::Database()
{
    NumVehicles = 0;
    NumReservations = 0;
    CurrentDate = 1;
}

Database::~Database()
{
    for (int i = 0; i < NumVehicles; i++)
    {
        delete Vehicles[i];
    }
}

int Database::ReadInventory(string FileName)
{
    ifstream InFile;
    string Line;

    InFile.open(FileName);

    if (!InFile.is_open())
    {
        cout << "Error! Inventory file could not be opened." << endl;
        return -1;
    } // if()

    if (NumVehicles != 0)
    {
        cout << "Error! Inventory has already been loaded." << endl;
        return -5;
    } // if()

    while (getline(InFile, Line))
    {
        if (NumVehicles >= MaxVehicles)
        {
            cout << "Error! Inventory contains more than 50 vehicles." << endl;
            return -4;
        } // if()

        istringstream Record(Line);
        string Field;
        string Make, Model, Year, PropulsionType, Color, Capacity, Efficiency;
        int FieldCount = 0;

        // File order:
        // Year Make Model PropulsionType Color Capacity Efficiency
        while (Record >> Field)
        {
            FieldCount++;

            switch (FieldCount)
            {
            case 1:
            {
                Year = Field;
                break;
            }
            case 2:
            {
                Make = Field;
                break;
            }
            case 3:
            {
                Model = Field;
                break;
            }
            case 4:
            {
                PropulsionType = Field;
                break;
            }
            case 5:
            {
                Color = Field;
                break;
            }
            case 6:
            {
                Capacity = Field;
                break;
            }
            case 7:
            {
                Efficiency = Field;
                break;
            }
            } // switch()
        } // while()

        if (FieldCount != 7)
        {
            cout << "Error! Inventory file is malformed." << endl;
            cout << Line << endl;
            return -2;
        } // if()

        if (PropulsionType != "ICE" && PropulsionType != "EV")
        {
            cout << "Error! Unrecognized propulsion type." << endl;
            cout << Line << endl;
            return -3;
        } // if()

        if (PropulsionType == "ICE")
        {
            GasVehicle* Car = new GasVehicle;

            Car->SetMake(Make);
            Car->SetModel(Model);
            Car->SetYear(stoi(Year));
            Car->SetColor(Color);
            Car->SetPropulsionType(PropulsionType);
            Car->SetFuelCapacity(stod(Capacity));
            Car->SetEfficiency(stod(Efficiency));

            Vehicles[NumVehicles] = Car;
        } // if()
        else if (PropulsionType == "EV")
        {
            ElectricVehicle* Car = new ElectricVehicle;

            Car->SetMake(Make);
            Car->SetModel(Model);
            Car->SetYear(stoi(Year));
            Car->SetColor(Color);
            Car->SetPropulsionType(PropulsionType);
            Car->SetEnergyCapacity(stod(Capacity));
            Car->SetEfficiency(stod(Efficiency));

            Vehicles[NumVehicles] = Car;
        } // if...else if()

        // Get the range already calculated by the vehicle class.
        istringstream PropulsionInfo(Vehicles[NumVehicles]->GetPropulsionInfo());
        string Label, Range;

        // Skip the propulsion description before the first |.
        getline(PropulsionInfo, Label, '|');

        // Read "Range:" followed by the range value.
        PropulsionInfo >> Label >> Range;

        // Store the information in the next row.
        VehicleInfo[NumVehicles][0] = Make;
        VehicleInfo[NumVehicles][1] = Model;
        VehicleInfo[NumVehicles][2] = Year;
        VehicleInfo[NumVehicles][3] = Color;
        VehicleInfo[NumVehicles][4] = PropulsionType;
        VehicleInfo[NumVehicles][5] = Range;
        VehicleInfo[NumVehicles][6] = Efficiency;

        NumVehicles++;
    } // while()

    InFile.close();
    return 0;
}

int Database::GetNumVehicles()
{
    return NumVehicles;
}

// Returns the information from one complete vehicle row.
string Database::GetVehicleInfo(int VehicleNumber)
{
    int Row = VehicleNumber - 1;
    ostringstream Information;

    Information << VehicleNumber << "\t"
        << VehicleInfo[Row][2] << "\t"
        << VehicleInfo[Row][0] << "\t"
        << VehicleInfo[Row][1] << "\t"
        << VehicleInfo[Row][3] << "\t"
        << VehicleInfo[Row][4] << "\t"
        << VehicleInfo[Row][5] << " mi\t"
        << VehicleInfo[Row][6];

    if (VehicleInfo[Row][4] == "ICE")
    {
        Information << " mpg";
    }
    else
    {
        Information << " miles/kWh";
    }

    return Information.str();
}

string Database::SearchByMake(string TheMake)
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== SEARCH BY MAKE ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    // Make is stored in column 0.
    for (int i = 0; i < NumVehicles; i++)
    {
        if (VehicleInfo[i][0] == TheMake)
        {
            Information << GetVehicleInfo(i + 1) << endl;
            Count++;
        } // if()
    } // for()

    if (Count == 0)
    {
        Information << "No matching vehicles found." << endl;
    }

    Information << "\nTotal: " << Count << " vehicles found." << endl;
    return Information.str();
}

string Database::SearchByModel(string TheModel)
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== SEARCH BY MODEL ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    // Model is stored in column 1.
    for (int i = 0; i < NumVehicles; i++)
    {
        if (VehicleInfo[i][1] == TheModel)
        {
            Information << GetVehicleInfo(i + 1) << endl;
            Count++;
        } // if()
    } // for()

    if (Count == 0)
    {
        Information << "No matching vehicles found." << endl;
    }

    Information << "\nTotal: " << Count << " vehicles found." << endl;
    return Information.str();
}

string Database::SearchByYear(string TheYear)
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== SEARCH BY YEAR ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    // Year is stored in column 2.
    for (int i = 0; i < NumVehicles; i++)
    {
        if (VehicleInfo[i][2] == TheYear)
        {
            Information << GetVehicleInfo(i + 1) << endl;
            Count++;
        } // if()
    } // for()

    if (Count == 0)
    {
        Information << "No matching vehicles found." << endl;
    }

    Information << "\nTotal: " << Count << " vehicles found." << endl;
    return Information.str();
}

string Database::SearchByColor(string TheColor)
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== SEARCH BY COLOR ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    // Color is stored in column 3.
    for (int i = 0; i < NumVehicles; i++)
    {
        if (VehicleInfo[i][3] == TheColor)
        {
            Information << GetVehicleInfo(i + 1) << endl;
            Count++;
        } // if()
    } // for()

    if (Count == 0)
    {
        Information << "No matching vehicles found." << endl;
    }

    Information << "\nTotal: " << Count << " vehicles found." << endl;
    return Information.str();
}

string Database::SearchByPropulsionType(string ThePropulsionType)
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== SEARCH BY PROPULSION TYPE ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    // Propulsion type is stored in column 4.
    for (int i = 0; i < NumVehicles; i++)
    {
        if (VehicleInfo[i][4] == ThePropulsionType)
        {
            Information << GetVehicleInfo(i + 1) << endl;
            Count++;
        } // if()
    } // for()

    if (Count == 0)
    {
        Information << "No matching vehicles found." << endl;
    }

    Information << "\nTotal: " << Count << " vehicles found." << endl;
    return Information.str();
}

bool Database::IsVehicleAvailable(int VehicleNumber, int ReservationDate)
{
    if (VehicleNumber < 1 || VehicleNumber > NumVehicles ||
        ReservationDate <= CurrentDate)
    {
        return false;
    }

    for (int i = 0; i < NumReservations; i++)
    {
        if (ReservedVehicles[i][0] == VehicleNumber &&
            ReservedVehicles[i][1] == ReservationDate)
        {
            return false;
        }
    }

    return true;
}

//reservation functions start after 

bool Database::ReserveVehicle(int VehicleNumber, int ReservationDate)
{
    if (!IsVehicleAvailable(VehicleNumber, ReservationDate))
    {
        return false;
    }

    // Count the reservations for this vehicle.
    int Count = 0;

    for (int i = 0; i < NumReservations; i++)
    {
        if (ReservedVehicles[i][0] == VehicleNumber)
        {
            Count++;
        }
    }

    if (Count >= MaxReservations)
    {
        return false;
    }

    // Store the vehicle number and its reservation day.
    ReservedVehicles[NumReservations][0] = VehicleNumber;
    ReservedVehicles[NumReservations][1] = ReservationDate;

    NumReservations++;
    return true;
}

// All lines from here are 100% Ai Zayne use as refrence it similler to the code I coded above but no clue what it is I jsut told it in need it to print out this way and gave it the read me file
string Database::PrintAllVehicles()
{
    ostringstream Information;

    Information << "\n========== ALL VEHICLES ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << endl;
    Information << "Total Vehicles: " << NumVehicles << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    for (int i = 0; i < NumVehicles; i++)
    {
        Information << GetVehicleInfo(i + 1) << endl;
    }

    if (NumVehicles == 0)
    {
        Information << "No vehicles in the inventory." << endl;
    }

    Information << "\nTotal: " << NumVehicles << " vehicles found." << endl;
    return Information.str();
}

string Database::PrintReservedVehicles()
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== VEHICLES WITH RESERVATIONS ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency\tReserved Days" << endl;
    Information << "----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < NumVehicles; i++)
    {
        bool Found = false;

        for (int j = 0; j < NumReservations; j++)
        {
            if (ReservedVehicles[j][0] == i + 1)
            {
                // Print the vehicle information only once.
                if (!Found)
                {
                    Information << GetVehicleInfo(i + 1) << "\t";
                    Found = true;
                    Count++;
                }
                else
                {
                    Information << ", ";
                }

                Information << ReservedVehicles[j][1];
            }
        }

        if (Found)
        {
            Information << endl;
        }
    }

    if (Count == 0)
    {
        Information << "No vehicles currently have reservations." << endl;
    }

    Information << "\nTotal Reserved Vehicles: " << Count << endl;
    Information << "Total Reservations: " << NumReservations << endl;

    return Information.str();
}

string Database::PrintAvailableVehicles()
{
    ostringstream Information;
    int Count = 0;

    Information << "\n========== FULLY AVAILABLE VEHICLES ==========\n\n";
    Information << "Current Date: Day " << CurrentDate << "\n\n";
    Information << "ID\tYear\tMake\tModel\tColor\tType\tRange\tEfficiency" << endl;
    Information << "------------------------------------------------------------------------" << endl;

    for (int i = 0; i < NumVehicles; i++)
    {
        bool Reserved = false;

        for (int j = 0; j < NumReservations; j++)
        {
            if (ReservedVehicles[j][0] == i + 1)
            {
                Reserved = true;
                break;
            }
        }

        // Skip this row if its vehicle number is reserved.
        if (Reserved)
        {
            continue;
        }

        Information << GetVehicleInfo(i + 1) << endl;
        Count++;
    }

    if (Count == 0)
    {
        Information << "No fully available vehicles." << endl;
    }

    Information << "\nTotal Available Vehicles: " << Count << endl;

    if (Count == NumVehicles && NumVehicles > 0)
    {
        Information << "\nAll vehicles are currently available with no reservations." << endl;
    }

    return Information.str();
}

void Database::AdvanceDate()
{
    CurrentDate++;
    int NextRow = 0;

    for (int i = 0; i < NumReservations; i++)
    {
        // Keep reservations until their reserved day has passed.
        if (ReservedVehicles[i][1] >= CurrentDate)
        {
            ReservedVehicles[NextRow][0] = ReservedVehicles[i][0];
            ReservedVehicles[NextRow][1] = ReservedVehicles[i][1];
            NextRow++;
        }
    }

    NumReservations = NextRow;
}

int Database::GetCurrentDate()
{
    return CurrentDate;
}
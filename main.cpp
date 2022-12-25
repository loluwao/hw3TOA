/* CSCE 1040 001
 * Temi Akinyoade - ta0257
 * TemiloluwaAkinyoade@my.unt.edu
 * Homework 3: This is some sort of transportation application.
 * User can "register" passengers and drivers for rides.
 * They can also edit, delete, print, and do many other things with these drivers, passengers, and rides.
 */
#include "main.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
using namespace std;

int main() {
    cout << "Temi Akinyoade - TemiloluwaAkinyoade@my.unt.edu" << endl;
    cout << "CSCE 1040 001: Homework 3" << endl;

	Rides allRides;
	Drivers allDrivers;
	Passengers allPassengers;

	/* stream variables */
	ofstream fop;
	ifstream fip;
	string fileName;
    int p;
    
	cout << "Enter the name of your load file: ";
	cin >> fileName;
    fip.open(fileName);
    if (!fip.is_open()) { // check if file is open
        cout << "Issue opening file." << endl;
        return -1; // quit
    }
    cout << "1 - Load Data" << endl << "2 - Start New" << endl;
    cout << "What would you like to do? ";
    cin >> p;
    while (cin.fail() || !(p == 1 || p == 2)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "What would you like to do? ";
            cin >> p;
        }
        while (!(p == 1 || p == 2)) {
            cout << "Invalid..." << endl << "What would you like to do? ";
            cin >> p;
        }
    }
    if (p == 1) {
    char obj; // r for ride, p for passenger, d for driver, or e for end of data
    fip >> obj;
    while (obj != 'e') {
        if (obj == 'd') {
            /* vars for reading from file */
            char* firstName = (char*)malloc(sizeof(char) * 20);
            char* lastName = (char*)malloc(sizeof(char) * 20);
            float rating;
            int driverID, capacity, typeOfVehicle, handicapped, allowsPets, available;
            string notes;
            DriverInfo *d = (DriverInfo*)malloc(sizeof(DriverInfo));
            /* read all data from file and make driver objects */
            fip >> firstName;
            fip >> lastName;
            fip >> driverID;
            d->SetName(firstName, lastName);
            d->SetID(driverID);
            fip >> capacity;
            d->SetCapacity(capacity);
            fip >> typeOfVehicle;
            d->SetType(typeOfVehicle);
            fip >> rating;
            d->SetRating(rating);
            fip >> handicapped;
            d->SetHandicapped(handicapped);
            fip >> allowsPets;
            d->SetPetsAllowed(allowsPets);
            fip >> available;
            d->SetAvailable(available);
            fip.ignore();
            getline(fip, notes);
            d->SetNotes(notes);
            allDrivers.AddDriver(*d); // append driver to collection
            free(d);
        }
        else if (obj == 'p') {
            /* vars for reading from file */
            char* firstName = (char*)malloc(sizeof(char) * 20);
            char* lastName = (char*)malloc(sizeof(char) * 20);
            float rating;
            int passengerID, paymentMethod, handicapped, hasPets;
            PassengerInfo *p = (PassengerInfo*)malloc(sizeof(PassengerInfo));
            /* read from file and make passenger objects */
            fip >> firstName;
            fip >> lastName;
            fip >> passengerID;
            p->SetName(firstName, lastName);
            p->SetID(passengerID);
            fip >> rating;
            p->SetRating(rating);
            fip >> paymentMethod;
            p->SetPayment(paymentMethod);
            fip >> handicapped;
            p->SetHandicapped(handicapped);
            fip >> hasPets;
            p->SetPets(hasPets);
            allPassengers.AddPassenger(*p); // add passenger to collection
            free(p);
        }
        else if (obj == 'r') {
            /* vars for reading from file */
            float rating;
            int passengerID, driverID, rideID, partySize, hasPets, status;
            string pickLocation, dropLocation;
            long int pickTime, dropTime;
            RideInfo *r = (RideInfo*)malloc(sizeof(RideInfo));
            /* read from file and make ride objects */
            fip >> driverID;
            r->SetDriver(driverID);
            fip >> passengerID;
            r->SetPassenger(passengerID);
            fip >> rideID;
            r->SetID(rideID);
            fip >> partySize;
            r->SetPartySize(partySize);
            fip.ignore();
            getline(fip, pickLocation);
            r->SetPickLocation(pickLocation);
            getline(fip, dropLocation);
            r->SetDropLocation(dropLocation);
            fip >> pickTime;
            r->SetPickTime(pickTime);
            fip >> dropTime;
            r->SetDropTime(dropTime);
            fip >> hasPets;
            r->SetPets(hasPets);
            fip >> status;
            r->SetStatus(status);
            fip >> rating;
            r->SetRating(rating);

            allRides.AddRide(*r); // add ride to rides collection
            free(r);
        }
        fip >> obj;
    }
    }

	fop.open(fileName); // open file to write to

	/* for adding drivers */
	string option; // user's input for what they'd like to do next
	cout << setw(75) << "************* WELCOME TO THE MEAN GREEN EAGLELIFT SYSTEM *************" << endl << endl;
	PrintMenu();

	cin >> option;
	while (option != "q") { // q = quit program
		cout << endl;

		/* DRIVER OPTIONS */

		if (option == "ad") { // add driver
			cout << "ADDING DRIVER..." << endl;
			char* firstName;
			char* lastName;
			// allocate memory for name
			firstName = (char*)malloc(20 * sizeof(char));
			lastName = (char*)malloc(20 * sizeof(char));

			/* prompt for driver's name */
			cout << "Enter the driver's first and last name: ";
			scanf("%s %s", firstName, lastName);
			allDrivers.Add(firstName, lastName); // call add driver function
		}
		else if (option == "fd") { // search for driver
			cout << "FINDING DRIVER..." << endl;
			int driverToFindID;
			/* prompt for driver's name */
			cout << "Enter the driver's ID: ";
			cin >> driverToFindID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the driver's ID: ";
                cin >> driverToFindID;
            }
			if (allDrivers.DriverExists(driverToFindID)) { // confirm driver exists
				allDrivers.Find(driverToFindID, true); // if driver exists, search
			}
			else {
				printf("The driver with the ID %d could not be found.\n", driverToFindID); // tell user driver doesn't exist
			}
		}
		else if (option == "pdi") { // print a driver's info
			cout << "PRINTING DRIVER INFORMATION..." << endl;
			int driverToPrintID;
			/* prompt for driver's ID */
			cout << "Enter the driver's ID: ";
			cin >> driverToPrintID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the driver's ID: ";
                cin >> driverToPrintID;
            }
			if (allDrivers.DriverExists(driverToPrintID)) { // confirm driver user wants exists
				//cout << endl;
				allDrivers.PrintDriver(driverToPrintID); // print driver
			}
			else {
				printf("The driver with the ID %d could not be found.\n", driverToPrintID); // tell user driver does not exist
			}
		}
		else if (option == "pad") { // print al drivers under certain conditions
			cout << "PRINTING ALL DRIVERS..." << endl;
			int o; // option, 1 - 5
			cout << "1 - Available Drivers" << endl;
			cout << "2 - Drivers That Allow Pets" << endl;
			cout << "3 - Drivers With A Handicapped-Capable Vehicle" << endl;
			cout << "4 - Drivers With A Rating Above _" << endl;
			cout << "5 - Drivers With A Capacity Over _" << endl;
			cout << "6 - All Drivers" << endl;
			// prompt for option
			cout << "What would you like to print? ";
			cin >> o;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "What would you like to print? ";
                cin >> o;
            }
			allDrivers.PrintAll(o);
		}

		else if (option == "ed") { // edit driver
			int driverToEditID;
			/* prompt for driver's ID */
            allDrivers.PrintAll(6);
			cout << "Enter the ID of the driver you want to edit: ";
			cin >> driverToEditID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the driver you want to edit: ";
                cin >> driverToEditID;
            }
			if (allDrivers.DriverExists(driverToEditID)) { // confirm driver user wants to edit exists
				int i = allDrivers.Find(driverToEditID, false).first; // find index of driver in collection
				cout << "EDITING DRIVER INFORMATION..." << endl;
				int newID;
				int o; // user's option
                cout << "1 - Edit Vehicle Type" << endl << "2 - Edit Notes" << endl;
                cout << "3 - Edit If Vehicle is Handicapped-Capable" << endl;
                cout << "4 - Edit If Driver Allows Pets" << endl << "5 - Edit Availability" << endl;
                cout << "6 - Edit Rating" << endl;
				// prompt for user option
				cout << "What would you like to edit? ";
				cin >> o;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid data type..." << endl;
                    cout << "What would you like to edit? ";
                    cin >> o;
                }
                if ((o == 3 || o == 4 || o == 5 || o == 6) && allRides.RideExistsByDriver(driverToEditID)) {
                    cout << "Cannot edit that because this driver has registered rides." << endl;
                }
                else {
                    allDrivers.Edit(o, i); // edit passenger
                }
			}
			else {
				printf("The driver with the ID %d could not be found.\n", driverToEditID); // tell user driver does not exist
			}
		}
		else if (option == "dd") {
            allDrivers.PrintAll(6);
			cout << "DELETING DRIVER..." << endl;
			int driverToDelID;
			/* prompt for driver's name */
			cout << "Enter the ID of the driver you want to delete: ";
			cin >> driverToDelID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the driver you want to delete: ";
                cin >> driverToDelID;
            }
			if (allDrivers.DriverExists(driverToDelID)) { // check if driver exists
				allDrivers.Delete(driverToDelID); // delete driver
			}
			else {
				printf("The driver with the ID %d could not be found.\n", driverToDelID); // tell user driver does not exist
			}
		}

		/* PASSENGER OPTIONS */

		else if (option == "ap") { // add passenger
			cout << "ADDING PASSENGER..." << endl;
			char* firstName;
			char* lastName;
			// allocate memory for name strings
			firstName = (char*)malloc(20 * sizeof(char));
			lastName = (char*)malloc(20 * sizeof(char));

			/* prompt for passenger's ID */
			cout << "Enter the passenger's first and last name: ";
			scanf("%s %s", firstName, lastName);
			allPassengers.Add(firstName, lastName);
		}
		else if (option == "fp") { // search for passenger
			cout << "FINDING PASSENGER..." << endl;
			int findPassengerID;

			/* prompt for passenger's name */
			cout << "Enter the passenger's ID: ";
			cin >> findPassengerID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the passenger's ID: ";
                cin >> findPassengerID;
            }
			if (allPassengers.PassengerExists(findPassengerID)) { // confirm passenger exists
				allPassengers.Find(findPassengerID, true);
			}
			else {
				printf("The passenger with the ID %d could not be found.\n", findPassengerID); // tell user passenger couldn't be found
			}
		}
		else if (option == "ppi") { // print a passenger's info
			cout << "PRINTING PASSENGER INFORMATION..." << endl;
			int passengerPrintID;
			/* prompt for passenger's ID */
			cout << "Enter the passenger's ID: ";
			cin >> passengerPrintID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the passenger's ID: ";
                cin >> passengerPrintID;
            }
			if (allPassengers.PassengerExists(passengerPrintID)) { // confirm driver user wants exists
				cout << endl;
				allPassengers.PrintPassenger(passengerPrintID); // print
			}
			else {
				printf("The passenger with the ID %d could not be found.\n", passengerPrintID); // tell user driver does not exist
			}
		}
		else if (option == "pap") { // print all passengers
			cout << "PRINTING ALL PASSENGERS..." << endl;
			allPassengers.PrintAll();
		}

		else if (option == "ep") { // edit passenger
			int passengerToEditID;
			/* prompt for passenger's ID */
            allPassengers.PrintAll();
			cout << "Enter the ID of the passenger you want to edit: ";
			cin >> passengerToEditID;

			if (allPassengers.PassengerExists(passengerToEditID)) { // confirm passenger user wants to edit exists
				int i = allPassengers.Find(passengerToEditID, false).first; // find index of passenger in collection
				int newID; // new ID
				cout << "EDITING PASSENGER INFORMATION..." << endl;
				int o; // user's option
				cout << "1 - Edit Payment Preference" << endl << "2 - Edit Default Rating" << endl;
                cout << "3 - Edit If Passsenger is Handicapped" << endl << "4 - Edit If Passenger Has Pets" << endl;
				// prompt for user option
				cout << "What would you like to edit? ";
				cin >> o;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid data type..." << endl;
                    cout << "What would you like to edit? ";
                    cin >> o;
                }
                if ((o == 3 || o == 4) && allRides.RideExistsByPassenger(passengerToEditID)) {
                    cout << "Cannot edit that because this passenger has registered rides." << endl;
                }
                else {
                    allPassengers.Edit(o, i); // edit passenger
                }
			}
			else {
				printf("The passenger with the ID %d could not be found.\n", passengerToEditID); // tell user passenger does not exist
			}
		}
		else if (option == "dp") { // delete passenger
            allPassengers.PrintAll();
			cout << "DELETING PASSENGER..." << endl;
			int passengerToDelID;
			/* prompt for passenger's ID */
			cout << "Enter the ID of the passenger you want to delete: ";
			cin >> passengerToDelID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the passenger you want to delete: ";
                cin >> passengerToDelID;
            }
			if (allPassengers.PassengerExists(passengerToDelID)) { // check if passenger exists
				allPassengers.Delete(passengerToDelID); // delete passenger
			}
			else {
				printf("The passenger with the ID %d could not be found.\n", passengerToDelID); // tell user passenger does not exist
			}
		}

		/* RIDE OPTIONS */

		else if (option == "ar") { // add ride
			if (allDrivers.Count() == 0 || allPassengers.Count() == 0) {
				if (allDrivers.Count() == 0) {
					cout << "There are no drivers. Add a driver first." << endl;
				}
				if (allPassengers.Count() == 0) {
					cout << "There are no passengers. Add a passenger first." << endl;
				}
			}
			else {
				cout << "ADDING RIDE..." << endl;
                int passengerID, partySize;
				/* print all drivers and passengers and prompt their IDs */
				allPassengers.PrintAll(); // print all passengers
				// prompt for passenger ID
				cout << "Enter the ID of this ride's passenger: ";
				cin >> passengerID;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid data type..." << endl;
                    cout << "Enter the ID of this ride's passenger: ";
                    cin >> passengerID;
                }
                cout << "Enter the party size for this ride: ";
                cin >> partySize;
                while (cin.fail() || partySize < 1) {
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(100, '\n');
                        cout << "Invalid data type..." << endl;
                        cout << "Enter the party size for this ride: ";
                        cin >> partySize;
                    }
                    while (partySize < 1) {
                        cout << "Invalid data type..." << endl;
                        cout << "Enter the party size for this ride: ";
                        cin >> partySize;
                    }
                }
				/* verify driver and passenger exists */
				if (!allPassengers.PassengerExists(passengerID)) { // if driver or passenger doesn't exist
					if (!allPassengers.PassengerExists(passengerID)) {
						printf("The passenger with the ID %d could not be found.\n", passengerID); // tell user passenger does not exist
					}
				}
				else { // if driver AND passenger DO both exist
					PassengerInfo ridesPassenger = allPassengers.Find(passengerID, false).second; // passenger with user-entered ID
					/* check to see if driver and passenger will be compatible */
					allRides.UpdateStatuses();
                    allRides.Add(allDrivers, ridesPassenger, partySize); // d is the ID of this driver
				}
			}
		}
		else if (option == "pri") { // print ride info
			cout << "PRINTING RIDE INFORMATION..." << endl;
			int rideID;
			/* prompt for ride ID */
			cout << "Enter the ID of the ride: ";
			cin >> rideID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the ride: ";
                cin >> rideID;
            }
			if (allRides.RideExists(rideID)) { // check if ride exists
				allRides.UpdateStatuses();
				allRides.PrintRide(rideID); // print ride
			}
		}
		else if (option == "par") { // print all rides
			cout << "PRINTING ALL RIDES..." << endl;
            int o;
            cout << "1 - Active Rides" << endl;
            cout << "2 - Cancelled Rides" << endl;
            cout << "3 - Completed Rides" << endl;
            cout << "4 - All Rides" << endl;
            // prompt for option
            cout << "Enter an option between 1 - 4: ";
            cin >> o;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter an option between 1 - 4: ";
                cin >> o;
            }
			allRides.UpdateStatuses();
			allRides.PrintAll(o);
		}
		else if (option == "er") { // edit ride
			int rideToEditID;
			/* prompt for ride ID */
            allRides.PrintAll(4);
			cout << "Enter the ID of the ride you would like to edit: ";
			cin >> rideToEditID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the ride you would like to edit: ";
                cin >> rideToEditID;
            }
			if (allRides.RideExists(rideToEditID)) {
				int i = allRides.Find(rideToEditID).first; // find index of ride in collection
				cout << "EDITING RIDE INFORMATION..." << endl;
				int o; // user's option
				cout << "1 - Edit Pickup Location" << endl << "2 - Edit Drop-Off Location" << endl << "3 - Edit Rating" << endl;
				// prompt for user option
				cout << "What would you like to edit? ";
				cin >> o;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Invalid data type..." << endl;
                    cout << "What would you like to edit? ";
                    cin >> o;
                }
				allRides.Edit(o, i);
			}
			else { // o
				printf("The ride with the ID %d could not be found.\n", rideToEditID);
			}
		}
		else if (option == "ppr") {
			int passengerID;
			cout << "PRINTING PASSENGER'S RIDES..." << endl;
			/* prompt for passenger's ID */
            allPassengers.PrintAll();
			cout << "Enter the passenger's ID: ";
			cin >> passengerID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the passenger's ID: ";
                cin >> passengerID;
            }
			if (allPassengers.PassengerExists(passengerID)) { // check if passenger exists
				if (allRides.RideExistsByPassenger(passengerID)) { // check if passenger has rides
					allRides.UpdateStatuses();
					allRides.PrintPassengersRides(passengerID); // print passenger's rides
				}
				else {
					cout << "This passenger does not have any rides." << endl;
				}
			}
			else {
				printf("The passenger with the %d could not be found.\n", passengerID);
			}
		}
		else if (option == "pdr") {
			int driverID;
            allDrivers.PrintAll(6);
			cout << "PRINTING DRIVER'S RIDES..." << endl;
			/* prompt for driver's ID */
			cout << "Enter the driver's ID: ";
			cin >> driverID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the driver's ID: ";
                cin >> driverID;
            }
			if (allDrivers.DriverExists(driverID)) { // check if driver exists
				if (allRides.RideExistsByDriver(driverID))  { // check if driver has any rides
                    allRides.UpdateStatuses();
					allRides.PrintDriversRides(driverID); // print driver's rides
				}
				else {
					cout << "This driver does not have any rides." << endl;
				}
			}
			else {
				printf("The driver with the ID %d could not be found.\n", driverID);
			}
		}
		else if (option == "cr") { // cancel ride
			int rideToCancelID;
            allRides.PrintAll(4);
			cout << "CANCELLING RIDE..." << endl;
			/* prompt for ride ID */
			cout << "Enter the ID of the ride you want to cancel: ";
			cin >> rideToCancelID;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the ID of the ride you want to cancel: ";
                cin >> rideToCancelID;
            }
			if (allRides.RideExists(rideToCancelID)) { // check if ride exists
				allRides.Cancel(rideToCancelID); // cancel ride with ID
			}
			else {
				printf("The ride with the ID %d does not exists.\n", rideToCancelID);
			}
		}
        else if (option == "dr") { // delete rides
            cout << "DELETING COMPLETED/CANCELLED RIDES" << endl;
            allRides.UpdateStatuses();
            allRides.DeleteRides();
        }

		cout << endl;
		PrintMenu();
		cin >> option; // get input for next method

		if (option == "q"){
			int i;
			/* write drivers' info to file */
			for (i = 0; i < allDrivers.Count(); i++) {
				fop << "d" << endl;
				DriverInfo d = allDrivers.GetDriver(i);
				fop << d.GetFirstName() << endl << d.GetLastName() << endl;
				fop << d.GetID() << endl << d.GetCapacity() << endl;
				fop << d.GetType() << endl << d.GetRating() << endl;
				fop << d.IsHandicappedCapable() << endl << d.PetsAllowed() << endl;
				fop << d.IsAvailable() << endl << d.GetNotes() << endl;
			}
			/* write passengers' info to file */
			for (i = 0; i < allPassengers.Count(); i++) {
				fop << "p" << endl;
				PassengerInfo p = allPassengers.GetPassenger(i);
				fop << p.GetFirstName() << endl << p.GetLastName() << endl;
				fop << p.GetID() << endl << p.GetRating() << endl;
				fop << p.GetPaymentMet() << endl << p.IsHandicapped() << endl;
				fop << p.HasPets() << endl;
			}
			/* write rides' info to file */
			for (i = 0; i < allRides.Count(); i++) {
				fop << "r" << endl;
				RideInfo r = allRides.GetRide(i);
				fop << r.GetDriver() << endl << r.GetPassenger() << endl;
				fop << r.GetID() << endl << r.GetPartySize() << endl;
				fop << r.GetPickLocation() << endl << r.GetDropLocation() << endl;
				fop << r.GetPickTime() << endl << r.GetDropTime() << endl;
				fop << r.HasPets() << endl;
				fop << r.GetStatus() << endl << r.GetRating() << endl;
			}
			fop << "e"; // signifies end of file
		}

	}
	// close file
	fop.close();
	fip.close();

	return 0;
}

void PrintMenu() {
    cout << left << setw(32) << "PASSENGERS" << setw(32) << "DRIVERS" << setw(32) << "RIDES" << endl;
    cout << left << setw(32) << "Add Passenger (ap)" << setw(32) << "Add Driver (ad)" <<  "Add Ride (ar)" << setw(32) << endl;
    cout << left << setw(32) << "Edit Passenger (ep)" << setw(32) << "Edit Driver (ed)" << setw(32) << "Edit Ride (er)" << endl;
    cout << left << setw(32) << "Delete Passenger (dp)" << setw(32) << "Delete Driver (dd)" << setw(32) << "Cancel Ride (cr)" << endl;
    cout << left << setw(32) << "Find Passenger (fp)" << setw(32) << "Find Driver (fd)" << setw(32) << "Find Ride (fr)" << endl;
    cout << left << setw(32) << "Print All Passengers (pap)" << setw(32) << "Print All Drivers (pad)" << setw(32) << "Print All Rides (par)" << endl;
    cout << left << setw(32) << "Print Passenger Info (ppi)" << setw(32) << "Print Driver Info (pdi)" << setw(32) << "Print Ride Info (pri)" << endl;
    cout << left << setw(32) << "Print Passenger's Rides (ppr)" << setw(32) << "Print Driver's Rides (pdr)" << setw(32) << "Delete Completed/Cancelled Rides (dr)" << endl;
    cout << "Enter one of the keys in parentheses to perform a method. Enter q to quit: ";
    
}



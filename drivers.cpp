#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>
#include "drivers.h"
using namespace std;

int Drivers::Count() {
	return drivers.size();
}

void Drivers::Add(char* f, char* l) {
	DriverInfo* newDriver = (DriverInfo*)malloc(sizeof(DriverInfo));
	int id, capacity; // id of driver and their vehicle capacity
	float rating;
	string notes; // driver's vehicle, and notes
	string choice; // for yes/no
    srand(time(NULL)); // intialize random seed
	int pets, handicapCapable, vType, a;
    bool idAlreadyRegistered = false;

	/* make ID */
    id = rand() % 900000 + 100000;
    do { // check if ID has already been made
        idAlreadyRegistered = false;
        for (int i = 0; i < drivers.size(); i++) {
            if (id == drivers.at(i).GetID()) {
                idAlreadyRegistered = true;
                break;
            }
        }
        id = rand() % 900000 + 100000;
    } while (idAlreadyRegistered);
    
    cout << "DRIVER ID: " << id << endl;
    
	/* prompt for vehicle information */

	cout << "1 - 2-Door Compact" << endl << "2 - 4-Door Sedan" << endl;
	cout << "3 - SUV" << endl << "4 - Van" << endl << "5 - Other" << endl;
	cout << "Enter the driver's vehicle type (1 - 5): ";
	cin >> vType;
    
    // check if input is valid
    while (cin.fail() || (vType > 5 || vType < 1)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Enter the driver's vehicle type (1 - 5): ";
            cin >> vType;
        }
        while (vType < 1 || vType > 5) {
            cout << "Inavlid number..." << endl;
            cout << "Enter the driver's vehicle type (1 - 5): ";
            cin >> vType;
        }
    }


	cout << "Enter the number of passengers this vehicle can have: ";
	cin >> capacity;
	// check for validity of capacity
    while (cin.fail() || (capacity <= 0 || capacity > 10)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Enter the number of passengers this vehicle can have: ";
            cin >> capacity;
        }
        while (capacity <= 0 || capacity > 10) {
            cout << "Invalid number..." << endl;
            cout << "Enter the number of passengers this vehicle can have: ";
            cin >> capacity;
        }
    }

	/* prompt for driver's rating */

	cout << "Enter the driver's average rating (0 - 5): ";
	cin >> rating;
	// check that rating is valid
    while (cin.fail() || (rating > 5 || rating < 0)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Enter the driver's average rating (0 - 5): ";
            cin >> rating;
        }
        while (rating > 5 || rating < 0) {
            cout << "Invalid number..." << endl;
            cout << "Enter the driver's average rating (0 - 5): ";
            cin >> rating;
        }
    }

	/* prompt for driver's other details */

	cout << "0 - no" << endl;
	cout << "1 - yes" << endl;
	cout << "Does this driver allow pets in their vehicle? 0 or 1: ";
	cin >> pets;
    // check validity
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid data type..." << endl;
        cout << "Does this driver allow pets in their vehicle? 0 or 1: ";
        cin >> pets;
    }

	cout << "0 - no" << endl;
	cout << "1 - yes" << endl;
	cout << "Is this driver's vehicle handicapped capable? 0 or 1: ";
	cin >> handicapCapable;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid data type..." << endl;
        cout << "Is this driver's vehicle handicapped capable? 0 or 1: ";
        cin >> handicapCapable;
    }

	cout << "0 - no" << endl << "1 - yes" << endl;
	cout << "Is this driver available? 0 or 1: ";
	cin >> a;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid data type..." << endl;
        cout << "Is this driver available? 0 or 1: ";
        cin >> a;
    }


	/* prompt for notes about driver */

	cout << "Would you like to enter any notes for the driver? yes or no: ";
	cin >> choice;
	// check for valid entry
	while (!(choice == "yes" || choice == "no")) {
		cout << "Invalid...Enter yes or no: ";
		cin >> choice;
	}
	if (choice == "yes") {
		cin.ignore();
		cout << "Enter notes: ";
		getline(cin, notes);
	}
	else {
		notes = "-";
	}

	// call mutator functions
	newDriver->SetPetsAllowed(pets);
	newDriver->SetHandicapped(handicapCapable);
	newDriver->SetName(f, l);
	newDriver->SetID(id);
	newDriver->SetType(vType);
	newDriver->SetCapacity(capacity);
	newDriver->SetRating(rating);
	newDriver->SetNotes(notes);
	newDriver->SetAvailable(a);
	drivers.push_back(*newDriver);
	free(newDriver);
}

bool Drivers::DriverExists(int id) {
	for (int i = 0; i < drivers.size(); i++) {
		if (id == drivers.at(i).GetID()) {
			return true;
		}
	}
	return false;
}
pair<int, DriverInfo> Drivers::Find(int id, bool printID) { // parameters: ID of driver and whether i want to print its info or not
	int i; // index of driver in collection
	for (i = 0; i < drivers.size(); i++) {
		if (id == drivers.at(i).GetID()) {
			if (printID) {
				printf("Name: %s %s\t\tID: %d\n", drivers.at(i).GetFirstName(), drivers.at(i).GetLastName(), id); // print driver name and id
			}
			break;
		}
	}
	return make_pair(i, drivers.at(i)); // returns index of driver and DriverInfo object
}

void Drivers::Delete(int id) { // ID of driver
	int i = Find(id, false).first; // find index of driver
	drivers.erase(drivers.begin() + i); // delete driver
}

void Drivers::PrintDriver(int id) {
	Find(id, false).second.Print();
}
void Drivers::PrintAll(int option) { // available
	int i, n = 0;
	if (option == 1) {
		for (i = 0; i < drivers.size(); i++) {
			if (drivers.at(i).IsAvailable()) {
				n++;
				cout << "- DRIVER #" << i + 1 << " -" << endl;
				drivers.at(i).Print();
				cout << endl;
			}
		}
		if (n == 0) {
			cout << "There are no available drivers." << endl;
		}
	}
	else if (option == 2) { // allow pets
		for (i = 0; i < drivers.size(); i++) {
			if (drivers.at(i).PetsAllowed()) {
                n++;
				cout << "- DRIVER #" << i + 1 << " -" << endl;
				drivers.at(i).Print();
				cout << endl;
			}
		}
		if (n == 0) {
			cout << "There are no drivers that allow pets." << endl;
		}
	}
	else if (option == 3) { // handicapped capable
		for (i = 0; i < drivers.size(); i++) {
			if (drivers.at(i).IsHandicappedCapable()) {
                n++;
				cout << "- DRIVER #" << i + 1 << " -" << endl;
				drivers.at(i).Print();
				cout << endl;
			}
		}
		if (n == 0) {
			cout << "There are no drivers with handicapped capable vehicles." << endl;
		}
	}
	else if (option == 4) { // rating or higher
		float min;
		cout << "Print drivers with a rating over: ";
		cin >> min;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Print drivers with a rating over: ";
            cin >> min;
        }
		for (i = 0; i < drivers.size(); i++) {
            n++;
			if (drivers.at(i).GetRating() >= min) {
				cout << "- DRIVER #" << i + 1 << " -" << endl;
				drivers.at(i).Print();
				cout << endl;
			}
		}
		if (n == 0) {
			cout << "There are no drivers with a rating above " << min << "." << endl;
		}
	}
	else if (option == 5) {
		int min;
		cout << "Print drivers with a capacity over: ";
		cin >> min;
        while (cin.fail()) { // check for valid data type
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Print drivers with a capacity over: ";
            cin >> min;
        }
		for (i = 0; i < drivers.size(); i++) {
			if (drivers.at(i).GetCapacity() >= min) {
                n++;
				cout << "- DRIVER #" << i + 1 << " -" << endl;
				drivers.at(i).Print();
				cout << endl;
			}
		}
		if (n == 0) {
			cout << "There are no drivers with a capacity above " << min << "." << endl;
		}
	}
	else if (option == 6) { // all
		cout << "THERE IS A TOTAL OF " << drivers.size() << " DRIVERS" << endl;
		for (int i = 0; i < drivers.size(); i++) {
			cout << "- DRIVER #" << i + 1 << " -" << endl;
			drivers.at(i).Print();
			cout << endl;
		}
	}
}

void Drivers::Edit(int option, int index) { // returns new ID
    if (option == 1) { // edit vehicle type
		int newType;
		/* prompt for new vehicle type */
		cout << "1 - 2-Door Compact" << endl;
		cout << "2 - 4-Door Sedan" << endl;
		cout << "3 - SUV" << endl;
		cout << "4 - Van" << endl;
		cout << "5 - Other" << endl;
		cout << "Enter the driver's new vehicle type (1 - 5): ";
		cin >> newType;
        while (cin.fail() || (newType < 1 || newType > 5)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the driver's new vehicle type (1 - 5): ";
                cin >> newType;
            }
            while (newType < 1 || newType > 5) {
                cout << "Inavlid..." << endl;
                cout << "Enter the driver's new vehicle type (1 - 5): ";
                cin >> newType;
            }
        }
		drivers.at(index).SetType(newType); // set new type
	}
	else if (option == 2) { // edit notes
		string newNotes;
		/* prompt user for new notes */
		cout << "Enter the new notes for this driver: ";
		getline(cin, newNotes);

		drivers.at(index).SetNotes(newNotes); // set new notes for driver
	}
    else if (option == 3) { // edit handicapped capable
        int h;
        cout << "0 - no" << endl;
        cout << "1 - yes" << endl;
        cout << "Is this driver's vehicle handicapped capable? 0 or 1: ";
        cin >> h;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Is this driver's vehicle handicapped capable? 0 or 1: ";
            cin >> h;
        }
        drivers.at(index).SetHandicapped(h);
    }
    else if (option == 4) { // edit pets policy
        int p;
        cout << "0 - no" << endl;
        cout << "1 - yes" << endl;
        cout << "Does this driver allow pets? 0 or 1: ";
        cin >> p;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Does this driver allow pets? 0 or 1: ";
            cin >> p;
        }
        drivers.at(index).SetPetsAllowed(p);
    }
    else if (option == 5) { // edit availability
        int a;
        cout << "0 - no" << endl;
        cout << "1 - yes" << endl;
        cout << "Is this driver available? 0 or 1: ";
        cin >> a;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Is this driver available? 0 or 1: ";
            cin >> a;
        }
        drivers.at(index).SetAvailable(a);
    }
    else if (option == 6) { // edit rating
        float newRating;
        /* prompt for new rating */
        cout << "Enter the new rating for this driver: ";
        cin >> newRating;
        while (cin.fail() || newRating < 0 || newRating > 5) {
            while (newRating < 0 || newRating > 5) {
                cout << "Invalid..." << endl;
                cout << "Rating must be between 0 and 5: ";
                cin >> newRating;
            }
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the new rating for this driver: ";
                cin >> newRating;
            }
        }
        drivers.at(index).SetRating(newRating); // set new rating
    }
}

/* for file wrting */
DriverInfo Drivers::GetDriver(int i) {
	return drivers.at(i);
}

void Drivers::AddDriver(DriverInfo d) {
	drivers.push_back(d);
}







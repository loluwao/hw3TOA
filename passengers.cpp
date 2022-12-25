#include "passengers.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <utility>
using namespace std;

int Passengers::Count() {
	return passengers.size();
}
bool Passengers::PassengerExists(int id) {
	for (int i = 0; i < passengers.size(); i++) {
		if (id == passengers.at(i).GetID()) {
			return true;
			break;
		}
	}
	return false;
}
void Passengers::Add(char* f, char* l) {

	PassengerInfo *newPassenger = (PassengerInfo*)malloc(sizeof(PassengerInfo));
	int id, paymentPref; // id of passenger and their payment preference
	float rating;
	int isHandicapped, hasPets;
    bool idAlreadyRegistered;
    
    srand(time(NULL));
    id = rand() % 900000 + 100000;
	/* make ID */
    do { // check if ID has already been made
        idAlreadyRegistered = false;
        for (int i = 0; i < passengers.size(); i++) {
            if (id == passengers.at(i).GetID()) {
                idAlreadyRegistered = true;
                break;
            }
        }
        id = rand() % 900000 + 100000;
    } while (idAlreadyRegistered);
    
    cout << "PASSENGER ID: " << id << endl;

	/* prompt for payment preference */

	cout << "0 - cash\n1 - credit\n2 - debit\nEnter the passengers's payment preference: ";
	cin >> paymentPref;
	/* check for validity of payement preference */
	while (cin.fail() || (paymentPref > 2 || paymentPref < 0)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "0 - cash\n1 - credit\n2 - debit\nEnter the passengers's payment preference: ";
            cin >> paymentPref;
        }
        while (paymentPref > 2 || paymentPref < 0) {
            cout << "Invalid..." << endl;
            cout << "0 - cash\n1 - credit\n2 - debit\nEnter the passengers's payment preference: ";
            cin >> paymentPref;
        }
	}

	/* prompt for passengers's rating */

	cout << "Enter the passengers's default rating (0 - 5): ";
	cin >> rating;
	// check that rating is valid
	while (cin.fail() || (rating > 5 || rating < 0)) {
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Enter the passenger's required rating (0 - 5): ";
            cin >> rating;
        }
        while (rating > 5 || rating < 0) {
            cout << "Invalid..." << endl;
            cout << "Enter the passengers's required rating (0 - 5): ";
            cin >> rating;
        }
	}

	/* prompt for passengers's other details */

	cout << "0 - no" << endl;
	cout << "1 - yes" << endl;
	cout << "Does this passenger have pets? 0 or 1: ";
	cin >> hasPets;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid data type..." << endl;
        cout << "Does this passenger have pets? 0 or 1: ";
        cin >> hasPets;
    }

	cout << "0 - no" << endl;
	cout << "1 - yes" << endl;
	cout << "Is this passenger handicapped? 0 or 1: ";
	cin >> isHandicapped;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Invalid data type..." << endl;
        cout << "Is this passenger handicapped? 0 or 1: ";
        cin >> isHandicapped;
    }

	// call mutator functions
	newPassenger->SetPets(hasPets);
	newPassenger->SetHandicapped(isHandicapped);
	newPassenger->SetName(f, l);
	newPassenger->SetID(id);
	newPassenger->SetPayment(paymentPref);
	newPassenger->SetRating(rating);
	passengers.push_back(*newPassenger);
	free(newPassenger);
}
pair<int, PassengerInfo> Passengers::Find(int id, bool printName) {
	int i;
	for (i = 0; i < passengers.size(); i++) {
		if (id == passengers.at(i).GetID()) {
			if (printName) {
				printf("Name: %s %s\t\tID: %d\n", passengers.at(i).GetFirstName(), passengers.at(i).GetLastName(), id); // print driver name and id
			}
			break;
		}
	}
	return make_pair(i, passengers.at(i));
}

void Passengers::Delete(int id) {
	int i = Find(id, false).first; // find index of driver
	passengers.erase(passengers.begin() + i); // delete driver
}

void Passengers::PrintPassenger(int id) {
	Find(id, false).second.Print();
}
void Passengers::PrintAll() {
	cout << "THERE IS A TOTAL OF " << passengers.size() << " PASSENGERS" << endl;
	for (int i = 0; i < passengers.size(); i++) {
		cout << "- PASSENGER #" << i + 1 << " -" << endl;
		passengers.at(i).Print();
		cout << endl;
	}
}

void Passengers::Edit(int option, int index) {
    if (option == 1) { // edit payment preference
		int newPaymentPref;
		/* prompt for new vehicle type */
		cout << "0 - cash" << endl << "1 - credit" << "2 - debit" << endl << "Enter the new payment preference for this passenger: ";
		cin >> newPaymentPref;
        
        while (cin.fail() || (newPaymentPref > 2 || newPaymentPref < 0)) {
            while (cin.fail()) {
                cout << "Invalid data type..." << endl;
                cout << "0 - cash" << endl << "1 - credit" << "2 - debit" << endl << "Enter the new payment preference for this passenger: ";
                cin.clear();
                cin.ignore(100, '\n');
                cin >> newPaymentPref;
            }
            while (newPaymentPref > 2 || newPaymentPref < 0) {
                cout << "Invalid..." << endl << "0 - cash" << endl << "1 - credit" << endl << "2 - debit" << endl;
                cout << "Enter this passenger's payment preference: ";
                cin >> newPaymentPref;
            }
        }
		passengers.at(index).SetPayment(newPaymentPref); // set new type
	}
	else if (option == 2) { // edit default rating
		float newRating; // new rating for driver
		/* prompt for new rating */
		cout << "Enter the new default rating for this passenger: ";
		cin >> newRating;
        while (cin.fail() || (newRating < 0 || newRating > 5)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the new default rating for this passenger: ";
                cin >> newRating;
            }
            while (newRating < 0 || newRating > 5) {
                cout << "Invalid...Rating must be between 0 and 5: ";
                cin >> newRating;
            }
        } // check for validity

		passengers.at(index).SetRating(newRating); // set new rating for driver
	}
    else if (option == 3) { // edit if handicapped
        int h;
        cout << "0 - no" << endl;
        cout << "1 - yes" << endl;
        cout << "Is this passenger handicapped? 0 or 1: ";
        cin >> h;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Is this driver's vehicle handicapped capable? 0 or 1: ";
            cin >> h;
        }
        passengers.at(index).SetHandicapped(h);
    }
    else if (option == 4) { // edit pets
        int p;
        cout << "0 - no" << endl;
        cout << "1 - yes" << endl;
        cout << "Does this passenger have pets? 0 or 1: ";
        cin >> p;
        while (cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Invalid data type..." << endl;
            cout << "Does this passenger have pets? 0 or 1: ";
            cin >> p;
        }
        passengers.at(index).SetPets(p);
    }
    else if (option == 5) { // edit rating
        float newRating;
        /* prompt for new rating */
        cout << "Enter the new default rating for this passenger: ";
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
                cout << "Enter the new default rating for this passenger: ";
                cin >> newRating;
            }
        }
        passengers.at(index).SetRating(newRating); // set new rating
    }
}

PassengerInfo Passengers::GetPassenger(int i) {
	return passengers.at(i);
}
void Passengers::AddPassenger(PassengerInfo p) {
	passengers.push_back(p);
}









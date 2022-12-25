#include "rides.h"
#include <iostream>
#include <ios>
#include <iomanip>
#include <vector>
#include <ctime>
using namespace std;

int Rides::Count() {
	return rides.size();
}

void Rides::Add(Drivers ds, PassengerInfo p, int party) {
    bool driverFound = false;
    int indexOfDriver;
    for (int i = 0; i < ds.Count(); i++) {
        bool petsCompatible = false, handicappedCompatible = false, ratingCompatible = false, driverAvailable = false, anotherRideActive = false, capacityCompatible = false;
        DriverInfo d = ds.GetDriver(i);
        for (int j = 0; j < rides.size(); j++) {
            if (rides.at(j).GetDriver() == p.GetID()) { // if driver has ride
                if (rides.at(j).GetStatus() == 1) {
                    anotherRideActive = true;
                    break;
                }
            }
        }
        if ((p.HasPets() && d.PetsAllowed()) || (!p.HasPets() && d.PetsAllowed()) || (!p.HasPets() && !d.PetsAllowed())) { // if passenger has pets but driver doesn't allow pets
            //cout << "This ride cannot be made because the driver does not allow pets." << endl;
            petsCompatible = true;
        }
        if ((p.IsHandicapped() && d.IsHandicappedCapable()) || (!p.IsHandicapped() && d.IsHandicappedCapable()) || (!p.IsHandicapped() && !d.IsHandicappedCapable())) { // if passenger is handicapped but driver's vehicle is not handicapped capable
            //cout << "This ride cannot be made because the driver's vehicle is not handicapped capable." << endl;
            handicappedCompatible = true;
        }
        if (p.GetRating() <= d.GetRating()) { // if driver doesn't meet minimum rating
            //cout << "This ride cannot be made because the driver does not meet the passenger's minimum rating." << endl;
            ratingCompatible = true;
        }
        if (d.IsAvailable()) { // if driver isn't available
           // cout << "This ride cannot be made because the driver is not currently available." << endl;
            driverAvailable = true;
        }
        if (d.GetCapacity() >= party) {
            capacityCompatible = true;
        }
        if (petsCompatible && handicappedCompatible && ratingCompatible && driverAvailable && !anotherRideActive && capacityCompatible) {
            driverFound = true;
            indexOfDriver = i;
            break;
        }
    }

    if (driverFound) {
        RideInfo *rideToAdd = (RideInfo*)malloc(sizeof(RideInfo));
        DriverInfo d = ds.GetDriver(indexOfDriver);
        string pickUpLocation;
        string dropOffLocation;
        int partySize;
        float passengersRating;
        time_t now = time(0); // current time in seconds
        long int timeEst; // estimated length of ride
        int id;
        srand(time(NULL)); // intialize random seed
        bool idAlreadyRegistered = false;
        id = rand() % 90000000 + 10000000; // give ride random id
        tm *pickUpTime = localtime(&now); // pick up time
        int hours, minutes, date, month;
        
        do { // check if ID has already been made
            idAlreadyRegistered = false;
            for (int i = 0; i < rides.size(); i++) {
                if (id == rides.at(i).GetID()) {
                    idAlreadyRegistered = true;
                    break;
                }
            }
            id = rand() % 90000000 + 10000000;
        } while (idAlreadyRegistered);
        
        cout << "RIDE ID: " << id << "\t";
        cout << "Enter the month for this ride (1 - 12): ";
        cin >> month;
        while (cin.fail() || (month > 12 || month < 1)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the month for this ride: ";
                cin >> month;
            }
            while (month > 12 || month < 1) {
                cout << "Invalid..." << endl;
                cout << "Enter the month for this ride: ";
                cin >> month;
            }
        }
        month -= 1;
        pickUpTime->tm_mon = month;
        cout << "Enter the date for this ride: ";
        cin >> date;
        while (cin.fail() || (date < 1 || date >= 31) || (pickUpTime->tm_mon % 2 != 0 && date == 31)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the date for this ride: ";
                cin >> date;
            }
            while (date < 1 || date > 31) {
                cout << "Invalid..." << endl;
                cout << "Enter the date for this ride: ";
                cin >> date;
            }
            while (pickUpTime->tm_mon % 2 != 0 && date == 31) { // if month < 31 days
                cout << "That month has less than 31 days. Enter a valid date: ";
                cin >> date;
            }
        }
        
        cout << "Enter the time for pickup in HH:MM format (hours in military time): ";
        scanf("%d:%d", &hours, &minutes);
        while (cin.fail() || (hours < 0 || hours >= 23) || (minutes < 0 || minutes > 59)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the time for pickup in HH:MM format (hours in military time): ";
                scanf("%d:%d", &hours, &minutes);
            }
            while (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) {
                cout << "Invalid..." << endl;
                cout << "Enter the time for pickup in HH:MM format (hours in military time): ";
                scanf("%d:%d", &hours, &minutes);
            }
        }
        pickUpTime->tm_mday = date;
        pickUpTime->tm_min = minutes;
        pickUpTime->tm_hour = hours;
        cout << "PICKUP TIME: ";
        
        now = mktime(pickUpTime);
        rideToAdd->SetPickTime(now);
        cout << ctime(&now);
        cout << endl;
        
        time_t then = now; // pickup time
        /* prompt user for pickup and drop-off info */
        cout << "Enter the estimated time of this ride (in minutes): ";
        cin >> timeEst;
        while (cin.fail() || (timeEst > 1440 || timeEst < 0)) {
            while (cin.fail()) {
                cin.clear();
                cin.ignore(100, '\n');
                cout << "Invalid data type..." << endl;
                cout << "Enter the estimated time of this ride (in minutes): ";
                cin >> timeEst;
            }
            while (timeEst > 1440) {
                cout << "Rides cannot exceed 24 hours..." << endl;
                cout << "Enter the estimated time of this ride (in minutes): ";
                cin >> timeEst;
            }
            while (timeEst < 0) {
                cout << "Invalid..." << endl;
                cout << "Enter the estimated time of this ride (in minutes): ";
                cin >> timeEst;
            }
        }
        then += timeEst * 60; // calc drop-off time
        tm *dropOffTime = localtime(&then);
        cout << "Enter the pick up location: ";
        cin.ignore();
        getline(cin, pickUpLocation);
        cout << "Enter the drop-off location: ";
        getline(cin, dropOffLocation);
        
        /* call mutator functions */
        rideToAdd->SetDropTime(then);
        rideToAdd->SetRating(3.5);
        rideToAdd->SetPets(p.HasPets());
        rideToAdd->SetID(id);
        rideToAdd->SetPassenger(p.GetID());
        rideToAdd->SetDriver(d.GetID());
        rideToAdd->SetPickLocation(pickUpLocation);
        rideToAdd->SetDropLocation(dropOffLocation);
        rideToAdd->SetPartySize(party);
        rideToAdd->SetStatus(-1);
        rides.push_back(*rideToAdd); // add to rides collection
        free(rideToAdd);
    }
    else {
        cout << "No driver found for this passenger." << endl;
    }

}

bool Rides::RideExistsByDriver(int id) {
	for (int i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetDriver()) {
			return true;
		}
	}
	return false;
}
bool Rides::RideExistsByPassenger(int id) {
	for (int i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetPassenger()) {
			return true;
		}
	}
	return false;
}
bool Rides::RideExists(int id) {
	for (int i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetID()) {
			return true;
			break;
		}
	}
	return false;
}
pair<int, RideInfo> Rides::Find(int id) {
	int i;
	for (i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetID()) {
			break;
		}
	}
	return make_pair(i, rides.at(i));
}
pair<int, RideInfo> Rides::FindByDriver(int id) {
	int i;
	for (i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetDriver()) {
			break;
		}
	}
	return make_pair(i, rides.at(i));
}
pair<int, RideInfo> Rides::FindByPassenger(int id) {
	int i;
	for (i = 0; i < rides.size(); i++) {
		if (id == rides.at(i).GetPassenger()) {
			break;
		}
	}
	return make_pair(i, rides.at(i));
}

void Rides::PrintRide(int id) {
	time_t now = time(0);
	if (Find(id).second.GetStatus() != 0) {
		if (now > Find(id).second.GetDropTime()) {
			rides.at(Find(id).first).SetStatus(2); // update ride to say it's complete
		}
	}
	Find(id).second.Print();
}

void Rides::PrintAll(int o) {
    if (o == 1) { // active rides
        for (int i = 0; i < rides.size(); i++) {
            if (rides.at(i).GetStatus() == 1) {
                cout << "- RIDE #" << i + 1 << " -" << endl;
                rides.at(i).Print();
                cout << endl;
            }

        }
    }
    if (o == 2) { // cancelled rides
        for (int i = 0; i < rides.size(); i++) {
            if (rides.at(i).GetStatus() == 0) {
                cout << "- RIDE #" << i + 1 << " -" << endl;
                rides.at(i).Print();
                cout << endl;
            }
            
        }
    }
    if (o == 3) { // completed rides
        for (int i = 0; i < rides.size(); i++) {
            if (rides.at(i).GetStatus() == 2) {
                cout << "- RIDE #" << i + 1 << " -" << endl;
                rides.at(i).Print();
                cout << endl;
            }
            
        }
    }
    else if (o == 4) { // all
        cout << "THERE IS A TOTAL OF " << rides.size() << " RIDES" << endl;
        for (int i = 0; i < rides.size(); i++) {
            cout << "- RIDE #" << i + 1 << " -" << endl;
            rides.at(i).Print();
            cout << endl;
        }
    }

}

void Rides::UpdateStatuses() {
	time_t t = time(0); // current timete
	for (int i = 0; i < rides.size(); i++) {
		RideInfo r = rides.at(i);
        if (r.GetStatus() != 0) { // if ride isn't cancelled
            if (t > r.GetPickTime() && t < r.GetDropTime()) {
                rides.at(i).SetStatus(1); // set to active
            }
            else if (t > r.GetDropTime()) {
                rides.at(i).SetStatus(2); // set to complete
            }
            else if (t < r.GetPickTime()) {
                rides.at(i).SetStatus(-1); // ride is registered, hasn't started
            }
        }
	}
}

void Rides::DeleteRides() {
    bool doneDeleting;
    int i;
    do {
        doneDeleting = true;
        for (i = 0; i < rides.size(); i++) {
            if (rides.at(i).GetStatus() == 0) { // if ride is cancelled
                rides.erase(rides.begin() + i); // delete ride
                doneDeleting = false;
            }
            else if (rides.at(i).GetStatus() == 2) { // if ride is complete
                rides.erase(rides.begin() + i); // delete ride
                doneDeleting = false;
            }
        }
     } while (!doneDeleting);
}

void Rides::Edit(int option, int index) {
	if (option == 1) { // edit pickup location
		string newPickUpLocation;
		cin.ignore();
		/* prompt for new pickup location */
		cout << "Enter the new pickup location: ";
		getline(cin, newPickUpLocation);
		rides.at(index).SetPickLocation(newPickUpLocation); // set new location
	}
	else if (option == 2) { // edit dropoff location
		string newDropOffLocation;
		cin.ignore();
		/* prompt for new drop-off location */
		cout << "Enter the new drop-off location: ";
		getline(cin, newDropOffLocation);
		rides.at(index).SetDropLocation(newDropOffLocation); // set new location
	}
	else if (option == 3) { // edit rating
		float newRating;
		/* prompt for new rating */
		cout << "Enter the new rating for this ride: ";
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
                cout << "Enter the new rating for this ride: ";
                cin >> newRating;
            }
        }
        rides.at(index).SetRating(newRating); // set new rating
	}
}

void Rides::PrintDriversRides(int id) {
	for (int i = 0; i < rides.size(); i++) {
		if (rides.at(i).GetDriver() == id) {
			rides.at(i).Print();
		}
	}
}
void Rides::PrintPassengersRides(int id) {
	for (int i = 0; i < rides.size(); i++) {
		if (rides.at(i).GetPassenger() == id) {
			rides.at(i).Print();
		}
	}
}

void Rides::Cancel(int id) {
	rides.at(Find(id).first).SetStatus(0); // set ride to cancelled
}

RideInfo Rides::GetRide(int i) {
	return rides.at(i);
}

void Rides::AddRide(RideInfo r) {
	rides.push_back(r);
}




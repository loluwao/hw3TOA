#include "rideinfo.h"
#include <ios>
#include <iomanip>
using namespace std;

enum Status {REGISTERED = -1, CANCELLED, ACTIVE, COMPLETE};

RideInfo::RideInfo() {
	rID = 0;
	dID = 0;
	pID = 0;
	pickUpL = "None";
	dropOffL = "None";
	party = 0;
	includesPets = false;
	status = -1;
	rating = -1.0;
}

void RideInfo::SetPassenger(int p) {
	pID = p;
}
void RideInfo::SetDriver(int d) {
	dID = d;
}
void RideInfo::SetID(int id) {
	rID = id;
}
void RideInfo::SetPickLocation(string pL) {
	pickUpL = pL;
}
void RideInfo::SetDropLocation(string dL) {
	dropOffL = dL;
}
void RideInfo::SetPartySize(int p) {
	party = p;
}
void RideInfo::SetPets(bool pets) {
	includesPets = pets;
}
void RideInfo::SetPickTime(time_t pT) {
	pickUpT = pT;
}
void RideInfo::SetDropTime(time_t dT) {
	dropOffT = dT;
}
void RideInfo::SetStatus(int s) {
	status = s;
}
void RideInfo::SetRating(float r) {
	rating = r;
}

int RideInfo::GetDriver() {
	return dID;
}
int RideInfo::GetPassenger() {
	return pID;
}
int RideInfo::GetID() {
	return rID;
}
string RideInfo::GetPickLocation() {
	return pickUpL;
}
string RideInfo::GetDropLocation() {
	return dropOffL;
}
int RideInfo::GetPartySize() {
	return party;
}
bool RideInfo::HasPets() {
	return includesPets;
}
time_t RideInfo::GetPickTime() {
	return pickUpT;
}
time_t RideInfo::GetDropTime() {
	return dropOffT;
}
int RideInfo::GetStatus() {
	return status;
}
float RideInfo::GetRating() {
	return rating;
}
void RideInfo::Print() {
	cout << left << setw(10) << "ID" << setw(10) << "DRIVER" << setw(12) << "PASSENGER" << setw(30) << "PICK-UP LOCATION" << setw(30) << "DROP-OFF LOCATION" << endl;
	cout << setw(10) << rID << setw(10) << dID << setw(12) << pID << setw(30) << pickUpL << setw(30) << dropOffL << endl;
	cout << left << setw(12) << "PARTY SIZE" << setw(15) << "INCLUDES PETS" << setw(10) << "STATUS" << setw(20) << "RATING" << endl;
	cout << setw(12) << party;
	if (includesPets) {
		cout << setw(15) << "yes";
	}
	else {
		cout << setw(15) << "no";
	}

	if (status == CANCELLED) {
		cout << setw(10) << "cancelled";
	}
    else if (status == REGISTERED) {
        cout << setw(10) << "registered";
    }
	else if (status == ACTIVE) {
		cout << setw(10) << "active";
	}
	else {
		cout << setw(10) << "complete";
	}
	cout << fixed << setprecision(2) << setw(20) << rating << endl;
    cout << "PICKUP TIME: " << ctime(&pickUpT) << endl << "DROP-OFF TIME: " << ctime(&dropOffT) << endl;
}






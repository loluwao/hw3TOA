#include "driverinfo.h"
#include <ios>
#include <iomanip>
#include <cstring>
using namespace std;

enum Cars {COMPACT2DR = 1, SEDAN4DR, SUV, VAN, OTHER};

DriverInfo::DriverInfo() {
	dID = -1;
	capacity = 0;
	vehicleType = 0;
	handiFriendly = 'x';
	available = false;
	petsAllowed = 'x';
	notes = "None";
	rating = -1;
}

void DriverInfo::SetID(int id) {
	dID = id;
}
void DriverInfo::SetName(char *f, char *l) {
	//f = (char*)malloc(20 * )
	fName = f;
	lName = l;
}
void DriverInfo::SetCapacity(int c) {
	capacity = c;
}
void DriverInfo::SetType(int v) {
	vehicleType = v;
}
void DriverInfo::SetHandicapped(bool h) {
	handiFriendly = h;
}
void DriverInfo::SetAvailable(bool a) {
	available = a;
}
void DriverInfo::SetPetsAllowed(bool p) {
	petsAllowed = p;
}
void DriverInfo::SetNotes(string n) {
	notes = n;
}
void DriverInfo::SetRating(float r) {
	rating = r;
}

int DriverInfo::GetID() {
	return dID;
}
char *DriverInfo::GetFirstName() {
	return fName;
}
char *DriverInfo::GetLastName() {
	return lName;
}
int DriverInfo::GetCapacity() {
	return capacity;
}
int DriverInfo::GetType() {
	return vehicleType;
}
bool DriverInfo::IsHandicappedCapable() {
	return handiFriendly;
}
bool DriverInfo::IsAvailable() {
	return available;
}
bool DriverInfo::PetsAllowed() {
	return petsAllowed;
}
string DriverInfo::GetNotes() {
	return notes;
}
float DriverInfo::GetRating() {
	return rating;
}

void DriverInfo::Print() {
	char fullName[40];
	strcpy(fullName, fName);
	strcat(fullName, " ");
	strcat(fullName, lName);
	cout << left << setw(30) << "NAME" << setw(10) << "ID" << setw(18) << "VEHICLE TYPE" << setw(20) << "VEHICLE CAPACITY" << setw(12) << "RATING" << endl;
	cout << setw(30) << fullName;
	cout << setw(10) << dID;
	if (vehicleType == COMPACT2DR) {
		cout << setw(18) << "2-Door Compact";
	}
	else if (vehicleType == SEDAN4DR) {
		cout << setw(18) << "4-Door Sedan";
	}
	else if (vehicleType == SUV) {
		cout << setw(18) << "SUV";
	}
	else if (vehicleType == VAN) {
		cout << setw(18) << "Van";
	}
	else if (vehicleType == OTHER) {
		cout << setw(18) << "Other";
	}
	cout << setw(20) << capacity;
	cout << setw(12) << fixed << setprecision(2) << rating << endl;
	if (handiFriendly) {
		cout << setw(30) << "HANDICAPPED CAPABLE: yes\t";
	}
	else {
		cout << setw(30) << "HANDICAPPED CAPABLE: no\t";
	}
	if (petsAllowed) {
		cout << setw(20) << "PETS ALLOWED: yes\t";
	}
	else {
		cout << setw(20) << "PETS ALLOWED: no\t";
	}
	if (available) {
		cout << "CURRENTLY AVAILABLE: yes\n";
	}
	else {
		cout << "CURRENTLY AVAILABLE: no\n";
	}
	cout << "NOTES: " << notes << endl;
}


#include "passengerinfo.h"
#include <ios>
#include <iomanip>
#include <cstring>
#include <cstdlib>
#include <cstdio>
using namespace std;

PassengerInfo::PassengerInfo() {
	pID = -1;
	paymentM = -1;
	handicapped = 'x';
	pRating = -1.0;
	hasPets = 'x';
}
void PassengerInfo::SetName(char* f, char* l) {
	fName = f;
	lName = l;
}
void PassengerInfo::SetID(int id) {
	pID = id;
}
void PassengerInfo::SetPayment(int p) {
	paymentM = p;
}
void PassengerInfo::SetHandicapped(int h) {
	handicapped = h;
}
void PassengerInfo::SetRating(float r) {
	pRating = r;
}
void PassengerInfo::SetPets(int pets) {
	hasPets = pets;
}
char* PassengerInfo::GetFirstName() {
	return fName;
}
char* PassengerInfo::GetLastName() {
	return lName;
}
int PassengerInfo::GetID() {
	return pID;
}
int PassengerInfo::GetPaymentMet() {
	return paymentM;
}
bool PassengerInfo::IsHandicapped() {
	return handicapped;
}
float PassengerInfo::GetRating() {
	return pRating;
}
bool PassengerInfo::HasPets() {
	return hasPets;
}

void PassengerInfo::Print() {
	char fullName[40];
	strcpy(fullName, fName);
	strcat(fullName, " ");
	strcat(fullName, lName);
	cout << left << setw(30) << "NAME" << setw(10) << "ID" << setw(15) << "DEFAULT RATING" << endl;
	cout << setw(30) << fullName;
	cout << setw(10) << pID;
	cout << setw(15) << fixed << setprecision(1) << pRating << endl;
	cout << "IS HANDICAPPED: ";
	if (handicapped) {
		cout << "yes\t";
	}
	else {
		cout << "no\t";
	}
	cout << "HAS PETS: ";
	if (hasPets) {
		cout << "yes\n";
	}
	else {
		cout << "no\n";
	}

	cout << "PAYMENT PREFERENCE: ";
	if (paymentM == 0) {
		cout << "cash\n";
	}
	else if (paymentM == 1) {
		cout << "credit\n";
	}
	else {
		cout << "debit\n";
	}
}

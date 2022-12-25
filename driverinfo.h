#ifndef DRIVER_INFO_H
#define DRIVER_INFO_H
#include <vector>
#include <cstdio>
#include <iostream>
using namespace std;

class DriverInfo {
	private:
		int dID;
		char* fName;
		char* lName;
		int capacity;
		int vehicleType; // vehicle type
		float rating;
		bool handiFriendly; // handicap friendly?
		bool available;
		bool petsAllowed;
		string notes;
	public:
		DriverInfo();
		void SetID(int id);
		void SetName(char* f, char* l);
		void SetCapacity(int c);
		void SetType(int v);
		void SetHandicapped(bool h);
		void SetAvailable(bool a);
		void SetPetsAllowed(bool p);
		void SetNotes(string n);
		void SetRating(float r);

		int GetID();
		char *GetFirstName();
		char *GetLastName();
		int GetCapacity();
		int GetType();
		bool IsHandicappedCapable();
		bool IsAvailable();
		bool PetsAllowed();
		string GetNotes();
		float GetRating();

		void Print();
};
#endif

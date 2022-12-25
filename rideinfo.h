#include <iostream>
#include <ctime>
#include "driverinfo.h"
#include "passengerinfo.h"
using namespace std;

class RideInfo {
	private:
		int pID; // passenger ID
		int dID; // driver ID
		int rID; // ride ID
		string pickUpL, dropOffL;
		int party;
		bool includesPets; // whether there's pets on the ride or not
		time_t pickUpT;
		time_t dropOffT;
		int status; // 0 = cancelled, 1 = active, 2 = complete
		float rating;
	public:
		RideInfo();
		void SetPassenger(int p);
		void SetDriver(int d);
		void SetID(int id);
		void SetPickLocation(string pL);
		void SetDropLocation(string dL);
		void SetPartySize(int p);
		void SetPets(bool pets);
		void SetPickTime(time_t pT);
		void SetDropTime(time_t dT);
		void SetStatus(int s);
		void SetRating(float r);

		int GetDriver();
		int GetPassenger();
		int GetID();
		string GetPickLocation();
		string GetDropLocation();
		int GetPartySize();
		bool HasPets();
		time_t GetPickTime();
		time_t GetDropTime();
		int GetStatus();
		float GetRating();
    
        void PrintTime(time_t t);
		void Print();

};

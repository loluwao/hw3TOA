#ifndef RIDES_H
#define RIDES_H
#include <iostream>
#include <vector>
#include <utility>
#include "rideinfo.h"
#include "drivers.h"
using namespace std;

class Rides {
	private:
		vector<RideInfo> rides;
	public:
		int Count();
		void Add(Drivers ds, PassengerInfo p, int party);
		void PrintRide(int id); // prints ride info
		void PrintAll(int o); // print all rides
		void PrintDriversRides(int id);
		void PrintPassengersRides(int id);
		void Edit(int option, int index);
		void Cancel(int id);

		bool RideExists(int id);
		bool RideExistsByDriver(int id);
		bool RideExistsByPassenger(int id);
		pair<int, RideInfo> Find(int id); // returns index in collection AND ride
		pair<int, RideInfo> FindByDriver(int id); // returns index in collection AND ride
		pair<int, RideInfo> FindByPassenger(int id); // returns index in collection AND ride
		void UpdateStatuses();
        void DeleteRides();
		RideInfo GetRide(int i); // returns ride at index i in vector
		void AddRide(RideInfo r); // add direct RideInfo object to vector
};
#endif

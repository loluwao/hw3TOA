#include <iostream>
#include <vector>
#include <utility>
#include "passengerinfo.h"
using namespace std;

class Passengers {
	private:
		vector<PassengerInfo> passengers;
	public:
		int Count(); // returns size of collection
		bool PassengerExists(int id);
		void Add(char* f, char* l);
		pair<int, PassengerInfo> Find(int id, bool printName);
		void Delete(int id);
		void PrintPassenger(int id);
		void PrintAll();
		void Edit(int option, int index); // returns new ID

		/* for file writing */
		PassengerInfo GetPassenger(int i); // returns passenger at index i in vector
		void AddPassenger(PassengerInfo p); // adds direct PassengerInfo object to vector

};

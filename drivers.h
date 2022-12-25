#ifndef DRIVER_H
#define DRIVER_H
#include <vector>
#include <iostream>
#include "driverinfo.h"
using namespace std;

class Drivers {
	private:
		vector<DriverInfo> drivers;
	public:
		int Count();
		bool DriverExists(int id); // parameters: id of driver we're checking for. returns whether they exist or not
		void Add(char* f, char* l); // parameters: first and last name of driver
		pair<int, DriverInfo> Find(int id, bool printID); // parameters: id of driver to find and whether i want to print ID or not. returns index of driver in vector and DriverInfo object
		void PrintDriver(int id); // parameters: id of driver to print
		void PrintAll(int option); // parameters: prints drivers that specifically ___
		void Edit(int option, int index); // thing to edit and index of driver in vector
		void Delete(int id); // id of driver to delete

		/* for file writing */
		DriverInfo GetDriver(int i); // returns driver at index i
		void AddDriver(DriverInfo d); // adds direct DriverInfo object to collection
};
#endif

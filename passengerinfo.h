#ifndef PASSENGER_INFO_H
#define PASSENGER_INFO_H
#include <iostream>
using namespace std;

class PassengerInfo {
	private:
		char* fName;
		char* lName;
		int pID;
		int paymentM; // payment method. 0 = cash, 1 = credit, 2 = debit, -1 = not set
		bool handicapped;
		float pRating;
		bool hasPets;
	public:
		PassengerInfo();
		void FreeName(); // frees memory for passenger name
		void SetName(char* f, char* l);
		void SetID(int id);
		void SetPayment(int p);
		void SetHandicapped(int h);
		void SetRating(float r);
		void SetPets(int pets);

		char* GetFirstName();
		char* GetLastName();
		int GetID();
		int GetPaymentMet();
		bool IsHandicapped();
		float GetRating();
		bool HasPets();

		void Print();
};
#endif

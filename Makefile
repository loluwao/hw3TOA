pro.exe: main.o passengers.o drivers.o rides.o driverinfo.o passengerinfo.o rideinfo.o
	g++ main.o  passengers.o drivers.o rides.o driverinfo.o passengerinfo.o rideinfo.o
main.o: main.cpp main.h
	g++ -c main.cpp
passengers.o: passengers.cpp passengers.h
	g++ -c passengers.cpp
drivers.o: drivers.cpp drivers.h
	g++ -c drivers.cpp
rides.o: rides.cpp rides.h
	g++ -c rides.cpp
passengerinfo.o: passengerinfo.cpp passengerinfo.h
	g++ -c passengerinfo.cpp
driverinfo.o: driverinfo.cpp driverinfo.h
	g++ -c driverinfo.cpp
rideinfo.o: rideinfo.cpp rideinfo.h
	g++ -c rideinfo.cpp
clean:
	rm *.o pro.exe

#pragma once
#include <iostream>
#include <string>

class Customer { // Un customer contient un nom, un nom de rue et un numero civique

	public:
		Customer(std::string name, std::string streetName, int civicNumber);
		std::string getName();
		std::string getStreetName();
		int getCivicNumber();
		std::string toString();
		Customer* getPrevious();
		Customer* getNext();
		void setPrevious(Customer* newPrevious);
		void setNext(Customer* newNext);

	private:
		std::string name;
		std::string streetName;
		int civicNumber;
		Customer* next;
		Customer* previous;
};
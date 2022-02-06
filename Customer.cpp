#include "Customer.h"
#include <string>

Customer::Customer(std::string name, std::string streetName, int civicNumber) {
	this->name = name;
	this->streetName = streetName;
	this->civicNumber = civicNumber;
	this->previous = nullptr;
	this->next = nullptr;
}
std::string Customer::getName() {
	return this->name;
}
std::string Customer::getStreetName() {
	return this->streetName;
}
int Customer::getCivicNumber() {
	return this->civicNumber;
}

std::string Customer::toString() {
	return this->getName() + "\n" + this->getStreetName() + "\n" + std::to_string(this->getCivicNumber()) + "\n";
}

Customer* Customer::getPrevious() {
	return this->previous;
}

Customer* Customer::getNext() {
	return this->next;
}

void Customer::setPrevious(Customer* newPrevious) {
	this->previous = newPrevious;
}
void Customer::setNext(Customer* newNext) {
	this->next = newNext;
}
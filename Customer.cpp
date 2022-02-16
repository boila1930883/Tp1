// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#include "Counter.h"
#include "Customer.h"
#include <string>

Customer::Customer(std::string name, std::string streetName, int civicNumber) 
{
	this->name = name;
	this->streetName = streetName;
	this->civicNumber = civicNumber;
	this->previous = nullptr;
	this->next = nullptr;

	Counter::addConstrutor();
}

Customer::~Customer() 
{
	Counter::addDestructor();
}

/*
	Accesseur du nom
*/
std::string Customer::getName() 
{
	return this->name;
}

/*
	Accesseur du nom de rue
*/
std::string Customer::getStreetName() 
{
	return this->streetName;
}

/*
	Accesseur du numéro civique
*/
int Customer::getCivicNumber() 
{
	return this->civicNumber;
}

/*
	Retourne le client (pour affichage)
*/
std::string Customer::toString() 
{
	return this->getName() + "\n" + this->getStreetName() + "\n" + std::to_string(this->getCivicNumber()) + "\n";
}

/*
	Accesseur du client précédent
*/
Customer* Customer::getPrevious() 
{
	return this->previous;
}

/*
	Accesseur du client suivant
*/
Customer* Customer::getNext() 
{
	return this->next;
}

/*
	Mutateur du client précédent
*/
void Customer::setPrevious(Customer* newPrevious) 
{
	this->previous = newPrevious;
}

/*
	Mutateur du client suivant
*/
void Customer::setNext(Customer* newNext) 
{
	this->next = newNext;
}
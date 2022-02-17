// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#pragma once

#include <iostream>
#include <string>

/*
Liste de clients contenent un client, un pointeur sur le client suivant et un pointeur sur le client précédent.
Un client contient un nom, un numero civique et un nom de rue
*/
class Customer {

	public:
		Customer(std::string name, std::string streetName, int civicNumber);
		~Customer();

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
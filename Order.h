// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#pragma once

#include <string>
#include "Cookie.h"
#include "Customer.h"

/*
Liste de commandes contenent une commande, un pointeur sur la commande suivante et un pointeur sur la commande précédente.
Une commande contient une source, un destinatire et une liste de biscuits
*/
class Order {


	public:
		Order(Customer* sender, Customer* receiver);
		~Order(); 

		void AddTypeOfCookie(Cookie* cookie);
		Cookie* getList();
		Customer* getSender();
		Customer* getReceiver();
		std::string toString();

		Order* getPrevious();
		Order* getNext();
		void setNext(Order* newNext);
		void setPrevious(Order* newPrevious);

	private:
		Cookie* cookieList;
		Customer* sender;
		Customer* receiver;
		Order* previous;
		Order* next;
};
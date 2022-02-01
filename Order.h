#pragma once
#include <string>
#include "Cookie.h"
#include "Customer.h"

class Order { // Une commande contient un Customer From, To et une liste de Cookie qui ont ete commandes


	public:
		Order(Customer* sender, Customer* receiver);
		~Order(); // Detruire la cookieList

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
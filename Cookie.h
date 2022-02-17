// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#pragma once

#include <string>

/*
Liste de biscuits contenant un biscuit et un pointeur sur le biscuit suivant.
Un biscuit contient un nom et une quantité.
*/
class Cookie {	

	public:
		Cookie(std::string name);
		Cookie(std::string name, int quantity);
		~Cookie();

		std::string getName(void);
		Cookie* getNext(void);
		int getNbCookiesOrdered(void);
		std::string toString();
		void setNext(Cookie* newNext);
		void setQuantity(int newQuantity);

	private:
		std::string name;
		Cookie* next;
		int nbCookiesOrdered;
};

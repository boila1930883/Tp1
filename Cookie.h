#pragma once
#include <string>

class Cookie {	// Un biscuit contient le nom du biscuit et une quantite

	// Ce type sert a conserver les types de biscuits existants, puisqu'on n'a pas de liste exhaustive, on va s'assurer qu'elle soit toujours exhaustive.
	// Cela permettra aussi de faciliter les recherches du nombre de biscuits vendus/dans les commandes.
	// On parcourera cette liste dans un seul sens, il ne sera pas nécessaire de supprimer des types de biscuits

	public:
		Cookie(std::string name);
		Cookie(std::string name, int quantity);
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

#pragma once
#include "Customer.h"
#include "Order.h"
#include "Cookie.h"

class GeneralManager {

	public:
		GeneralManager(void);
		~GeneralManager(void); // Détruire les 3 listes

		void AddCustomer(Customer* newCustomer); // La fonction attend l'addresse memoire du nouveau client

		// Ajout avec indice specifie
		bool AddCustomer(Customer* newCustomer, int index); // Retourne false si l'index > taille liste
		bool RemoveCustomer(std::string name);

		void AddOrder(Order* newOrder);
		bool RemoveAllOrdersFrom(std::string sender);
		std::string GetDescriptionOfAllOrdersFrom(std::string sender);
		Cookie* getMostPopularCookie(void);
		
		Cookie* getCookieTypeList(void);
		Customer* getCustomerList(void);
		Customer* getCustomer(std::string name);
		Order* getOrderList(void);
		void AddCookieType(Cookie* cookieType);
		Cookie* FindCookieType(std::string name);

		std::string getOrderListDescription(void);
		std::string getCustomerListDescription(void);
		std::string getCookieListDescription(void);
		int getNbCustomer(void);

		int getCookiePrice(void);

	private:
		const int COOKIE_PRICE = 1;

		Customer* customersList;
		Order* orderList;
		Cookie* cookieList;
		int nbCustomer;
};
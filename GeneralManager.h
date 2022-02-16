// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#pragma once

#include "Customer.h"
#include "Order.h"
#include "Cookie.h"

/*
Le directeur général fait la gestion des listes de clients, de commandes et de biscuits
*/
class GeneralManager {

	public:
		GeneralManager(void);
		~GeneralManager(void); 

		void AddCustomer(Customer* newCustomer); 
		bool AddCustomer(Customer* newCustomer, int index); 
		bool RemoveCustomer(std::string name);
		Customer* getCustomerList(void);
		Customer* getCustomer(std::string name);
		std::string getCustomerListDescription(void);

		void AddOrder(Order* newOrder);
		bool RemoveAllOrdersFrom(std::string sender);
		std::string GetDescriptionOfAllOrdersFrom(std::string sender);
		Order* getOrderList(void);
		std::string getOrderListDescription(void);

		Cookie* getMostPopularCookie(void);
		Cookie* getCookieTypeList(void);
		void AddCookieType(Cookie* cookieType);
		Cookie* FindCookieType(std::string name);
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
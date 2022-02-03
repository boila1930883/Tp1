#include <fstream>
#include <iostream>
#include <string>
#include "Cookie.h"
#include "Customer.h"
#include "Order.h";
#include "GeneralManager.h"

using namespace std;

void loadLists(GeneralManager*); // Pour charger les listes de clients et de commandes

int main(void) {
	
	GeneralManager* gm = new GeneralManager();

	loadLists(gm);

	// Pour tester les classes
	Cookie* c0 = new Cookie("Aux patates", 3);
	Cookie* c1 = new Cookie("Aux amandes", 4);
	Cookie* c2 = new Cookie("Au chocolat", 10);

	Customer* cu0 = new Customer("Galio", "Mid", 10);
	Customer* cu1 = new Customer("Vayne", "Bot", 20);
	Customer* cu2 = new Customer("Viktor", "Mid", 15);
	Customer* cu3 = new Customer("Asol", "Jg", 11);

	Order* o1 = new Order(cu0, cu1);
	Order* o2 = new Order(cu1, cu3);

	cout << "order " << o1->toString();
	cout << "order" << o2->toString();

	o1->AddTypeOfCookie(c0);
	o1->AddTypeOfCookie(c1);
	cout << "order " << o1->toString();
	cout << "order" << o2->toString();

	GeneralManager gm = GeneralManager();
	gm->AddCustomer(cu0);
	gm->AddCustomer(cu0);
	gm->AddCustomer(cu1);
	gm->AddCustomer(cu2);
	gm->AddCustomer(cu3, 2);
	cout << "Liste des customers:\n" << gm->getCustomerListDescription();

	gm->AddOrder(o1);
	gm->AddOrder(o2);
	cout << "Liste des Commandes:\n" << gm->getOrderListDescription();
	cout << "Liste des Types de biscuits\n" << gm->getCookieListDescription();

	gm->RemoveAllOrdersFrom("Galio");
	cout << "Liste des Commandes:\n" << gm->getOrderListDescription();
	cout << "Liste des Types de biscuits\n" << gm->getCookieListDescription();



	delete gm;
	gm = nullptr;

	return 0;
}

// Charger les listes de Clients et de Commandes
void loadLists(GeneralManager*) {
	
	
	//gm.AddCustomer()
}
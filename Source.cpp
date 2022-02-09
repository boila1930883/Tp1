#include <fstream>
#include <iostream>
#include <string>
#include "Cookie.h"
#include "Customer.h"
#include "Order.h"
#include "GeneralManager.h"
#include "TransactionManager.h"

using namespace std;

void loadLists(GeneralManager* gm, string customerFileName, string orderFileName); // Pour charger les listes de clients (customer) et de commandes (order)
void saveLists(GeneralManager* gm, string customerFileName, string orderFileName); // Pour enregistrer les listes de clients (customer) et de commandes (order)
void manageTransactions(GeneralManager* gm, string transactionFileName); //Lecture et application des transactions

int main(void) {
	
	string transactionFileName("PRESIDENTS_TRANSACTIONS.txt");
	// Pour le moment, car le nom du fichier sera lu à partir du fichier de transactions

	GeneralManager* gm = new GeneralManager();


	setlocale(LC_CTYPE, "fr-FR");

	manageTransactions(gm, transactionFileName);

	/* Pour tester les classes
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
	//*/

	
	delete gm;
	gm = nullptr;
	
	system("pause");
	return 0;
}

/* PROBLÈME EN RE-LECTURE DU FICHIER SAUVEGARDÉ
	- Premier/Dernier client de la liste est en double
	- Premier/Dernier commande en double et mauvais formatage des biscuits (voir printScreen)
*/ 

// Charger les listes de clients (customer) et de commandes (order)
void loadLists(GeneralManager* gm, string customerFileName, string orderFileName) {
	
	//----- Charger la liste de clients (customer) -----//
	string name, streetName;
	int civicNumber;
	Customer* ptrCustomer;
	ifstream customerFile;

	customerFile.open(customerFileName);	
	if (!customerFile.fail())
	{
		while (!customerFile.eof())
		{
			customerFile >> name >> civicNumber >> streetName;
			//cout << "Reading : " << name << " " << civicNumber << " " << streetName;
			ptrCustomer = new Customer(name, streetName, civicNumber);
			gm->AddCustomer(ptrCustomer);
			cout << ptrCustomer->toString() << endl;
		}
		customerFile.close();

		cout << "Liste des customers:\n" << gm->getCustomerListDescription();
	}
	else
		cout << "Erreur d'ouverture du fichier de clients !" << endl;


	//----- Charger la liste de commandes (orders) -----//
	string sender, receiver, cookie;
	int quantity;
	Order* ptrOrder;
	Cookie* ptrCookie;
	ifstream orderFile;
	
	orderFile.open(orderFileName);
	if (!orderFile.fail())
	{
		while (!orderFile.eof())
		{
			orderFile >> sender >> receiver;
			
			ptrOrder = new Order(gm->getCustomer(sender), gm->getCustomer(receiver)); 
			// On prend pour acquis que le client source (sender) et le client destinataire (receiver) sont inscrit à la liste de clients lors du chargement

			orderFile >> cookie;

			do
			{
				orderFile >> quantity;
				ptrCookie = new Cookie(cookie, quantity);
				ptrOrder->AddTypeOfCookie(ptrCookie);

				orderFile >> cookie;
			} while (cookie != "&");
			cout << ptrOrder->toString();
			gm->AddOrder(ptrOrder);
		}
		orderFile.close();

		cout << "Liste des Commandes:\n" << gm->getOrderListDescription();
	}
	else
		cout << "Erreur d'ouverture du fichier de commandes !" << endl;
	
}

void saveLists(GeneralManager* gm, string customerFileName, string orderFileName) {
	
	//----- Sauvegarde de la liste de clients (customer) -----//
	Customer* currentCustomer;
	ofstream customerFile;

	customerFile.open(customerFileName);
	if (!customerFile.fail())
	{
		currentCustomer = gm->getCustomerList();
		while (currentCustomer != nullptr)
		{
			customerFile << endl << currentCustomer->getName() << endl << currentCustomer->getCivicNumber() << endl << currentCustomer->getStreetName();
			cout << "Ecriture de " << currentCustomer->toString();
			currentCustomer = currentCustomer->getNext();
		}
		customerFile.close();

		cout << "Écriture du fichier de clients réussie !" << endl;
	}
	else
		cout << "Erreur d'écriture du fichier de clients !" << endl;


	//----- Sauvegarde de la liste de commandes (order) -----//
	Order* currentOrder;
	Cookie* currentCookie;
	ofstream orderFile;
	
	orderFile.open(orderFileName); 
	if (!orderFile.fail())
	{
		currentOrder = gm->getOrderList();
		while (currentOrder != nullptr)
		{
			orderFile << endl << currentOrder->getSender()->getName() << endl;
			orderFile << currentOrder->getReceiver()->getName() << endl;

			currentCookie = currentOrder->getList();
			while (currentCookie != nullptr)
			{
				orderFile << currentCookie->getName() << " " << currentCookie->getNbCookiesOrdered() << endl;
				currentCookie = currentCookie->getNext();
			}
			orderFile << "&";

			currentOrder = currentOrder->getNext();
		}
		orderFile.close();

		cout << "Écriture du fichier de commandes réussie !" << endl;
	}
	else
		cout << "Erreur d'écriture du fichier de commandes !" << endl;
}

void manageTransactions(GeneralManager* gm, string transactionFileName) {
	// variables
	char opCode;
	int tempInt;
	string tempString, tempLine, orderFileName, custumerFileName;
	ifstream transFile;
	TransactionManager trm(gm);

	transFile.open(transactionFileName);

	if (!transFile.fail()) {
	//tant que le ficher n'est pas fini
		while (!transFile.eof()) {
			//lecture de ligne
			transFile >> opCode;

			//traitements
			switch (opCode) {
				//supresion de client
			case '-':
				transFile >> tempString;
				trm.surpimerClient(tempString);
				break;
				//ajout de client
			case '+':
				transFile >> tempString;
				transFile >> tempInt;
				transFile >> tempLine;
				trm.ajouterClient(tempString, tempInt, tempLine);
				break;
				//ajout de commande
			case '=':
				tempString = "";
				tempLine = "";
				do {	
					tempLine += tempString;
					tempLine += '-';
					transFile >> tempString;
				} while (tempString != "&");
				trm.ajouterCommande(tempLine);
				break;
				// afficher toutes les commandes d'un client
			case '?':
				transFile >> tempString;
				trm.afficherComamndes(tempString);
				break;
				// Affciher le biscuit plus populaire
			case '$':
				trm.afficherPopulaire();
				break;
				// Lire les fichers
			case 'O':
				transFile >> custumerFileName >> orderFileName;
				loadLists(gm, custumerFileName, orderFileName);
				break;
				// enregistrer les ficher.
			case 'S':
				transFile >> custumerFileName >> orderFileName;
				saveLists(gm, custumerFileName, orderFileName);
				break;
			default:
				cout << "Probleme de lecture de Ficher transactions!" << endl;
				break;
			}	
		}
		//fermeture
			transFile.close();
	}
	else {
		cout << "Erreur d'ouverture du fichier de transactions !" << endl;
	}
}
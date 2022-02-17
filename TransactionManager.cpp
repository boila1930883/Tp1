// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#include "Counter.h"
#include "TransactionManager.h"
#include "GeneralManager.h"
#include "Customer.h"
#include "Cookie.h"
#include <iostream>
#include <fstream>

using namespace std;

TransactionManager::TransactionManager(GeneralManager* gm) 
{
	this->gManager = gm;

	Counter::addConstrutor();
}

TransactionManager::~TransactionManager() 
{
	this->gManager = nullptr;
	
	Counter::addDestructor();
}

/*
	Fonctionnalité de lecture de fichiers et chargement des listes
*/
void TransactionManager::chargementListes(string customerFileName, string orderFileName)
{
	//----- Charger la liste de clients (customer) -----//
	string name, streetName;
	int civicNumber, nbCustomer(0);
	Customer* ptrCustomer;
	ifstream customerFile;

	customerFile.open(customerFileName);
	if (!customerFile.fail())			// Si l'ouverture du fichier a réussie
	{
		cout << "Ouverture et chargement de la liste de clients" << endl;
		while (!customerFile.eof())		// Tant que l'on est pas à la fin du fichier
		{
			customerFile >> name >> civicNumber >> streetName;		// Lecteur des informations du clients
			ptrCustomer = new Customer(name, streetName, civicNumber);
			gManager->AddCustomer(ptrCustomer, nbCustomer);		// Ajout du client à la liste
			nbCustomer = gManager->getNbCustomer();
		}
		customerFile.close();

		cout << "Liste des clients:\n" << gManager->getCustomerListDescription() << endl;	// Affichage de la liste de clients
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
	if (!orderFile.fail())			// Si l'ouverture du fichier a réussie
	{
		cout << "Ouverture et chargement de la liste de commandes" << endl;
		while (!orderFile.eof())	// Tant que l'on est pas à la fin du fichier
		{
			orderFile >> sender >> receiver;	// Lecture de la source et du destinataire

			ptrOrder = new Order(gManager->getCustomer(sender), gManager->getCustomer(receiver));
			// On prend pour acquis que le client source (sender) et le client destinataire (receiver) sont inscrit à la liste de clients lors du chargement

			// Lecture des biscuits tant que l'on atteint pas '&' (fin de la commande) dans le fichier
			orderFile >> cookie;

			do {
				orderFile >> quantity;
				ptrCookie = new Cookie(cookie, quantity);
				ptrOrder->AddTypeOfCookie(ptrCookie);		// Ajout du biscuit à la commande

				orderFile >> cookie;
			} while (cookie != "&");
			//cout << ptrOrder->toString();
			gManager->AddOrder(ptrOrder);				// Ajout de la commande à la liste
		}
		orderFile.close();

		cout << "Liste des commandes:\n" << gManager->getOrderListDescription() << endl;	// Affichage de la liste des commandes
	}
	else
		cout << "Erreur d'ouverture du fichier de commandes !" << endl;

}

/*
	Fonctionnalité de sauvegarde des listes
*/
void TransactionManager::sauvegardeListes(string customerFileName, string orderFileName)
{
	//----- Sauvegarde de la liste de clients (customer) -----//
	Customer* currentCustomer;
	ofstream customerFile;

	customerFile.open(customerFileName);
	if (!customerFile.fail())			// Si l'ouverture du fichier a réussie
	{
		currentCustomer = gManager->getCustomerList();		// Récupérer la liste de clients
		while (currentCustomer != nullptr)				// Tant qu'on a pas atteint la fin de la liste
		{
			customerFile << endl << currentCustomer->getName() << endl << currentCustomer->getCivicNumber() << endl << currentCustomer->getStreetName();
			//cout << "Ecriture de " << currentCustomer->toString();
			currentCustomer = currentCustomer->getNext();	// Récupérer le prochain client de la liste
		}
		customerFile.close();

		cout << "Sauvegarde de la liste de client réussie" << endl;
	}
	else
		cout << "Erreur d'écriture du fichier de clients !" << endl;


	//----- Sauvegarde de la liste de commandes (order) -----//
	Order* currentOrder;
	Cookie* currentCookie;
	ofstream orderFile;

	orderFile.open(orderFileName);
	if (!orderFile.fail())				// Si l'ouverture du fichier a réussie
	{
		currentOrder = gManager->getOrderList();		// Récupérer la liste de ccommandes
		while (currentOrder != nullptr)			// Tant qu'on a pas atteint la fin de la liste
		{
			//cout << currentOrder->toString()<< endl;
			orderFile << endl << currentOrder->getSender()->getName() << endl;
			orderFile << currentOrder->getReceiver()->getName() << endl;

			currentCookie = currentOrder->getList();	// Récupérer la liste de biscuits
			while (currentCookie != nullptr)			// Tant qu'on a pas atteint la fin de la liste
			{
				orderFile << currentCookie->getName() << " " << currentCookie->getNbCookiesOrdered() << endl;
				currentCookie = currentCookie->getNext();
			}
			orderFile << "&";		// Ajout du '&' marquant la fin de la commande

			currentOrder = currentOrder->getNext();		// Récupérer la prochaine commande de la liste
		}
		orderFile.close();

		cout << "Sauvegarde de la liste de commandes réussie" << endl;
	}
	else
		cout << "Erreur d'écriture du fichier de commandes !" << endl;
}

/*
	Fonctionnalité de suppression de client
*/
void TransactionManager::supprimerClient(string nomClient) 
{
	// Appel au GeneralManager et affiche le résultat de l'opération
	if (this->gManager->RemoveAllOrdersFrom(nomClient)) 
	{
		cout <<  "Commandes du client " << nomClient << " supprimées." << endl;
	}
	else 
	{
		cout << "Échec de suppression des commandes!\n";
	}

	if (this->gManager->RemoveCustomer(nomClient)) 
	{
		cout << "Client " << nomClient << " suprimé." << endl;
	}
	else 
	{
		cout << "Échec de suppression du client!\n\n";
	}
}

/*
	Fonctionnalité d'ajout de client
*/
void TransactionManager::ajouterClient(string nomClient, int NSocial, string adresse) 
{
	Customer* cust = new Customer(nomClient, adresse, NSocial);
	// Appel au GeneralManager et affiche le résultat de l'opération
	if (this->gManager->AddCustomer(cust, 0)) 
	{
		cout << "Client " << nomClient << " ajouté.\n" << endl;
	}
	else 
	{
		cout << "Échec de l'ajout du client!\n";
	}
}

/*
	Fonctionnalité d'ajout de commande
*/
void TransactionManager::ajouterCommande(string ligneListe) 
{
	string substrng, nomSender, nomReciver, nomCookie;
	int end = 0, qtt = 0;
	char delim = '-';

	ligneListe = ligneListe.substr(1, ligneListe.size() -2);

	substrng = ligneListe.substr(end, (ligneListe.size() - end));
	end = substrng.find(delim);

	// Si la ligne a lire est vide, faire signe
	if (ligneListe.size() == 0) 
	{
		cout << "Échec de l'ajout de commande: ligne mal lu.";
		return;
	}
	// premier mot: nom du sender
	nomSender = substrng.substr(0, end);

	// deuxieme mot: nom du receiver
	substrng = substrng.substr(end + 1, (substrng.size() - end));
	end = substrng.find(delim);
	nomReciver = substrng.substr(0, end);

	// creation de nouvelle commande
	Customer* sender = this->gManager->getCustomer(nomSender);
	Customer* receiver = this->gManager->getCustomer(nomReciver);

	if (sender == nullptr || receiver == nullptr) {
		cout << "Commande invalide.\n\n";
		return;
	}

	Order* ord = new Order( sender,	receiver);

	// tant qu'il reste d'information...
	while (end > 0) 
	{
		// les noms et la quantite de biscuits alternent, fait deux decoupages par biscuit
		substrng = substrng.substr(end + 1, (substrng.size() - end));
		end = substrng.find(delim);
		nomCookie = substrng.substr(0, end);

		substrng = substrng.substr(end + 1, (substrng.size() - end));
		end = substrng.find(delim);
		qtt = stoi(substrng.substr(0, end));
		
		//creation et ajout de biscuit a la commande
		Cookie* cookie = new Cookie(nomCookie, qtt);

		ord->AddTypeOfCookie(cookie);
	}
	// ajouter la commande a la liste
	this->gManager->AddOrder(ord);
}

/*
	Fonctionnalité d'affichage des commandes d'un client
*/
void TransactionManager::afficherCommandes(string nomClient) 
{
	string description;
	// Appel au GeneralManager et affiche le résultat de l'opération
	description = this->gManager->GetDescriptionOfAllOrdersFrom(nomClient);

	cout << "Commandes faites pour " << nomClient << ": " << endl << description << endl;
}

void TransactionManager::afficherPopulaire() 
{
	// On trouve le biscuit le plus populaire
	Cookie* mostPopularCookie = this->gManager->getMostPopularCookie();

	cout << "Le Biscuit plus populaire est: " << mostPopularCookie->getName();
	cout << ".\nAussi, il a rapporté " << mostPopularCookie->getNbCookiesOrdered() << " $\n\n" ;
}
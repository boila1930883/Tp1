#include "TransactionManager.h"
#include "GeneralManager.h"
#include "Customer.h"
#include "Cookie.h"


TransactionManager::TransactionManager(GeneralManager* gm) {
	this->gManager = gm;
}

TransactionManager::~TransactionManager() {
	this->gManager = nullptr;
	std::cout << "destruction de TransactionManager";
}

void TransactionManager::surpimerClient(std::string nomClient) {
	// appelle au GeneralManager, afficher le resultat de l'operation
	if (this->gManager->RemoveAllOrdersFrom(nomClient)) {
		std::cout <<  "Commandes du client " << nomClient << " suprimées." << std::endl;
	}
	else {
		std::cout << "Échec de supresion de commandes!\n";
	}
	if (this->gManager->RemoveCustomer(nomClient)) {
		std::cout << "client " << nomClient << " suprimé." << std::endl;
	}
	else {
		std::cout << "Échec de supresion de client!\n";
	}
}

void TransactionManager::ajouterClient(std::string nomClient, int positionListe, std::string adresse) {
	Customer* cust = new Customer(nomClient, adresse, 0);
	// appelle au GeneralManager, afficher le resultat de l'operation
	if (this->gManager->AddCustomer(cust, positionListe)) {
		std::cout << "client " << nomClient << " ajouté." << std::endl;
	}
	else {
		std::cout << "Échec de ajout de client!\n";
	}
}

void TransactionManager::ajouterCommande(std::string ligneListe) {
	std::string substrng, nomSender, nomReciver, nomCookie;
	int end = 0, qtt = 0;
	char delim = '-';

	ligneListe = ligneListe.substr(1, ligneListe.size() -2);

	substrng = ligneListe.substr(end, (ligneListe.size() - end));
	end = substrng.find(delim);

	// si la ligne a lire est vide, faire signe
	if (ligneListe.size() == 0) {
		std::cout << "Échec de ajout de commande: ligne mal lu.";
		return;
	}
	// premier mot: nom du sender
	nomSender = substrng.substr(0, end);

	// deuxieme mot: nom du reciver
	substrng = substrng.substr(end + 1, (substrng.size() - end));
	end = substrng.find(delim);
	nomReciver = substrng.substr(0, end);

	// creation de nouvelle commande
	Order* ord = new Order( this->gManager->getCustomer(nomSender),
		this->gManager->getCustomer(nomReciver));

	// tant qu'il reste d'information...
	while (end > 0) {
		// les noms et la quantite de biscuits alternent, fait deux decoupages par biscuit
		substrng = substrng.substr(end + 1, (substrng.size() - end));
		end = substrng.find(delim);
		nomCookie = substrng.substr(0, end);

		substrng = substrng.substr(end + 1, (substrng.size() - end));
		end = substrng.find(delim);
		qtt = std::stoi(substrng.substr(0, end));
		
		//creation et ajout de biscuit a la commande
		Cookie* cookie = new Cookie(nomCookie, qtt);

		ord->AddTypeOfCookie(cookie);
	}
	
	// ajouter la commande a la liste
	this->gManager->AddOrder(ord);

}

void TransactionManager::afficherComamndes(std::string nomClient) {
	std::string description;
	// appelle au GeneralManager, afficher l'information
	description = this->gManager->GetDescriptionOfAllOrdersFrom(nomClient);

	std::cout << "Commandes faites pour " << nomClient << ": " << std::endl << description;
}

void TransactionManager::afficherPopulaire() {
	std::string nomcookie;
	// appelle au GeneralManager, afficher l'information
	nomcookie = this->gManager->getMostPopularCookie()->getName();

	std::cout << "Le Biscuit plus populaire est: " << nomcookie << std::endl;
}
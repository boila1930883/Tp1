#pragma once
#include "GeneralManager.h"


class TransactionManager {
private:
	//attributs
	GeneralManager gManager;
public:
	//constructeur
	TransactionManager(GeneralManager gm);
	//destructeur
	~TransactionManager();
	//methodes
	void surpimerClient(std::string nomClient);
	void ajouterClient(std::string nomClient, int positionListe, std::string adresse);
	void ajouterCommande(std::string ligneListe);
	void afficherComamndes(std::string nomClient);
	void afficherPopulaire();
};

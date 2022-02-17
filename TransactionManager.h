// Projet: 8INF259 - TP1 Commandes de biscuits
// �tudiants : Andr� Alano, Audrey B�dard et Laurie - Ann Boily

#pragma once

#include "GeneralManager.h"

/*
Le responsable des transactions effectue les transactions avec les listes provenant du directeur g�n�ral
*/
class TransactionManager {

public:
	TransactionManager(GeneralManager* gm);
	~TransactionManager();

	void chargementListes(std::string customerFileName, std::string orderFileName);
	void sauvegardeListes(std::string customerFileName, std::string orderFileName);
	void supprimerClient(std::string nomClient);
	void ajouterClient(std::string nomClient, int positionListe, std::string adresse);
	void ajouterCommande(std::string ligneListe);
	void afficherCommandes(std::string nomClient);
	void afficherPopulaire();

private:
	GeneralManager* gManager;
};

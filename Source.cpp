/*
Projet: 8INF259 - TP1 Commandes de biscuits
Étudiants: André Alano, Audrey Bédard et Laurie-Ann Boily 
Date: 18 février 2022
Description: Programme qui permet la gestion des listes de clients, de commandes et facilite leur traitement
*/

#include <fstream>
#include <iostream>
#include <string>
#include "Counter.h"
#include "Cookie.h"
#include "Customer.h"
#include "Order.h"
#include "GeneralManager.h"
#include "TransactionManager.h"

using namespace std;

void manageTransactions(GeneralManager* gm, string transactionFileName); // Lecture et application des transactions
void displayClassBalance(); // Pour valider le balancement des constructeurs et des destructeurs

/*
	Fonction principale
*/
int main(void) {
	
	string transactionFileName("PRESIDENTS_TRANSACTIONS.txt");	// Nom du fichier de transactions
	
	GeneralManager* gm = new GeneralManager();

	setlocale(LC_CTYPE, "fr-FR");

	manageTransactions(gm, transactionFileName);	// Traitement des transactions
	
	delete gm;
	gm = nullptr;

	displayClassBalance();	// Affichage du nombre de construteurs/destructeurs
	
	system("pause");
	return 0;
}

/*
	Lecture et application des transactions
*/
void manageTransactions(GeneralManager* gm, string transactionFileName) {
	// variables
	char opCode;
	int tempInt;
	string tempString, tempLine, orderFileName, customerFileName;
	ifstream transFile;
	TransactionManager trm(gm);

	transFile.open(transactionFileName);

	if (!transFile.fail()) {		// Si l'ouverture du fichier a réussie
		while (!transFile.eof()) {	// Tant que l'on est pas à la fin du fichier
			
			transFile >> opCode;	// Lecture de l'opcode

			//----- Choix du traitement en fonction de l'opcode -----//
			switch(opCode) {	
			
			// Supprimer un client ainsi que toutes ses commandes associées de la liste
			case '-':				
				transFile >> tempString;	// Lecture du nom du client à supprimer
				trm.supprimerClient(tempString);
				break;

			// Ajouter un client et ses informations associés
			case '+':				
				transFile >> tempString;	// Lecture du nom du client
				transFile >> tempInt;		// Lecture du no. civique
				transFile >> tempLine;		// Lecture du nom de rue
				trm.ajouterClient(tempString, tempInt, tempLine);
				break;
			
			// Ajouter une commande
			case '=':
				tempString = "";		// Compilation des éléments de la commande sous forme d'un texte qui sera déchiffrée par la fonctionalité d'ajout
				tempLine = "";
				do {	
					tempLine += tempString;
					tempLine += '-';
					transFile >> tempString;
				} while (tempString != "&");
				trm.ajouterCommande(tempLine);
				break;
				
			// Afficher toutes les commandes d'un client
			case '?':
				transFile >> tempString;	// Lecture du nom du client
				trm.afficherCommandes(tempString);
				break;

			// Affichier le biscuit plus populaire et le montant total reçu pour ce dernier
			case '$':
				trm.afficherPopulaire();
				break;

			// Ouvrir et charger les fichiers "CLIENTS" et " COMMANDES "
			case 'O':
				transFile >> customerFileName >> orderFileName;		// Lecture des noms de fichiers
				trm.chargementListes(customerFileName, orderFileName);
				break;

			// Enregistrer dans les fichiers "CLIENTS" et " COMMANDES "
			case 'S':
				transFile >> customerFileName >> orderFileName;		// Lecture des noms de fichiers
				trm.sauvegardeListes(customerFileName, orderFileName);
				break;

			default:
				cout << "Problème de lecture du ficher de transactions!" << endl;
				break;
			}	
		}
		transFile.close();
	}
	else {
		cout << "Erreur d'ouverture du fichier de transactions !" << endl;
	}
}

/*
	Valider le balancement des constructeurs et des destructeurs
	Permet de valider l'absence de fuite de mémoire liée aux objets (class)
*/
void displayClassBalance() {
	cout << endl << endl;
	cout << endl << "-----------------------------" << endl
		<< "NB constructeurs           : " << Counter::getNbConstructors() << endl
		<< "NB destructeurs            : " << Counter::getNbDestructors() << endl;
}
// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#include "Counter.h"
#include "GeneralManager.h"

GeneralManager::GeneralManager(void) 
{
	this->customersList = nullptr;
	this->orderList = nullptr;
	this->cookieList = nullptr;
	this->nbCustomer = 0;

	Counter::addConstrutor();
}

GeneralManager::~GeneralManager(void) 
{ 
	Customer* currentCustomer = this->getCustomerList();
	Order* currentOrder = this->getOrderList();
	Cookie* currentCookie = this->getCookieTypeList();

	// Detruire la liste de clients
	while (this->getCustomerList() != nullptr) 
	{
		this->customersList = this->customersList->getNext();
		delete currentCustomer;
		currentCustomer = this->customersList;
	}

	// Detruire la liste de commandes
	while (this->getOrderList() != nullptr) 
	{
		this->orderList = this->orderList->getNext();
		delete currentOrder;
		currentOrder = this->orderList;
	}

	// Detruire la liste de biscuits
	while (this->getCookieTypeList() != nullptr) 
	{
		this->cookieList = this->cookieList->getNext();
		delete currentCookie;
		currentCookie = this->cookieList;
	}

	Counter::addDestructor();
}

/*
	Ajouter un client à la liste de client
*/
void GeneralManager::AddCustomer(Customer* newCustomer) 
{ 
	this->AddCustomer(newCustomer, 0);		// Appel à la méthode d'ajout de client avec position
}

/*
	Ajouter un client à une certaine position de la liste de client
	Retourne false si la position est supérieure à la taille de la liste
*/
bool GeneralManager::AddCustomer(Customer* newCustomer, int index) {

	int currentIndex = 0;

	Customer* currentCustomer = this->getCustomerList();	// Récupérer la liste de clients

	if (index > this->getNbCustomer() || index < 0)			// Si la position n'est pas valide
	{
		return false;
	}

	//std::cout << "Ajout d'un client : " << newCustomer->toString();

	nbCustomer ++;

	if (this->getCustomerList() == nullptr)			// Si la liste est vide
	{
		this->customersList = newCustomer;			// Ajouter le client comme premier élément
		return true;
	}

	if (index == 0)									// Pour ajouter en tête de liste
	{
		currentCustomer->setPrevious(newCustomer);
		newCustomer->setNext(currentCustomer);
		this->customersList = newCustomer;
		return true;
	}

	while (currentIndex != index)					// Pour récupérer l'élément X de la liste
	{
		if (currentCustomer->getNext() != nullptr)	// Si l'élément suivant existe (la liste n'est pas entrain d'être créée)
		{
			currentCustomer = currentCustomer->getNext();
		}
		currentIndex++;
	}
	
	if (index = nbCustomer - 1)						// Pour ajouter en queue de liste
	{ 
		newCustomer->setPrevious(currentCustomer);
		newCustomer->setNext(nullptr);
		currentCustomer->setNext(newCustomer) ;
		return true;
	}

	// Pour ajouter à la position récupérée (sauf en tête et en queue)
	newCustomer->setNext(currentCustomer) ;
	newCustomer->setPrevious(currentCustomer->getPrevious());
	currentCustomer->getPrevious()->setNext(newCustomer);
	currentCustomer->setPrevious(newCustomer);
	return true;
}

/*
	Retirer un client de la liste
	Recoit le nom du client à retirer
	Retourne false si le client n'est pas dans la liste
*/
bool GeneralManager::RemoveCustomer(std::string name) 
{
	Customer* currentCustomer = this->getCustomerList();		// Récupérer la liste de clients

	while (currentCustomer != nullptr && currentCustomer->getName() != name)  // Recherche du client au nom X
	{
		currentCustomer = currentCustomer->getNext();
	}

	if (currentCustomer == nullptr)		// Si le client n'est pas trouvé
	{
		return false;
	}
	
	nbCustomer--;

	if (this->getCustomerList() == currentCustomer)		// Pour retirer en tête de liste
	{ 
		this->customersList = currentCustomer->getNext();
		currentCustomer->getNext()->setPrevious(nullptr);
		delete currentCustomer;
		return true;
	}

	if (currentCustomer->getNext() == nullptr)			// Pour retirer en queue de liste
	{	
		currentCustomer->getPrevious()->setNext(nullptr);
		delete currentCustomer;
		return true;
	}
	
	currentCustomer->getPrevious()->setNext(currentCustomer->getNext());
	currentCustomer->getNext()->setPrevious(currentCustomer->getPrevious());

	delete currentCustomer;
	return true;
}

/*
	Ajouter une commande à la liste de commandes
*/
void GeneralManager::AddOrder(Order* newOrder) 
{
	Order* currentOrder = this->getOrderList();			// Récupérer la liste de commandes
	Cookie* currentOrderCookie = newOrder->getList();	// Récupérer la liste de biscuits associée à la commande
	Cookie* cookieType = nullptr;
	
	while (currentOrderCookie != nullptr) 
	{
		cookieType = FindCookieType(currentOrderCookie->getName());

		if (cookieType == nullptr) 
		{
			AddCookieType(currentOrderCookie);
		}
		else
		{
			cookieType->setQuantity(cookieType->getNbCookiesOrdered() + currentOrderCookie->getNbCookiesOrdered());
		}
		currentOrderCookie = currentOrderCookie->getNext();
		cookieType = nullptr;
	}

	if (this->getOrderList() == nullptr) {			// Si la liste est vide
		this->orderList = newOrder;
		return;
	}
	
	newOrder->setNext(currentOrder);
	currentOrder->setPrevious(newOrder);
	this->orderList = newOrder;
}

/*
	Retirer toutes les commandes prevenant d'un client X (source)
*/
bool GeneralManager::RemoveAllOrdersFrom(std::string sender) 
{
	Order* currentOrder = this->getOrderList();		//	Récupérer la liste de commandes
	Order* ptrOrder;
	Cookie* currentCookie = nullptr;
	
	while (currentOrder->getNext() != nullptr)		// Parcourir toute la liste et récupérer toutes les commandes associées au client X
	{
		if (currentOrder->getSender()->getName() == sender || currentOrder->getReceiver()->getName() == sender) 
		{
			// On soustrait les biscuits annulés
			currentCookie = currentOrder->getList();
			while (currentCookie != nullptr) 
			{
				this->FindCookieType(currentCookie->getName())->setQuantity(FindCookieType(currentCookie->getName())->getNbCookiesOrdered() - currentCookie->getNbCookiesOrdered());
				currentCookie = currentCookie->getNext();
			}
						
			if (currentOrder->getNext() == nullptr)		// Si on atteint la fin de la liste
			{	// Si queue
				currentOrder->getPrevious()->setNext(nullptr);
				delete currentOrder;
				return true;
			}

			if (currentOrder == this->getOrderList())	// Si c'est en tête de liste
			{ 
					currentOrder->getNext()->setPrevious(nullptr);
					this->orderList = currentOrder->getNext();
				    delete currentOrder;		
					currentOrder = this->orderList;
					continue;
			}
			else										// Si c'est ni en tête, ni en queue de liste
			{
				currentOrder->getPrevious()->setNext(currentOrder->getNext());
				currentOrder->getNext()->setPrevious(currentOrder->getPrevious());

				ptrOrder = currentOrder->getNext();

				delete currentOrder;
				currentOrder = ptrOrder;
				continue;
			}
		}
		currentOrder = currentOrder->getNext();
	}
	return true;
}

/*
	Retourne la liste de toutes les commandes effectuées par le client X
*/
std::string GeneralManager::GetDescriptionOfAllOrdersFrom(std::string sender) 
{
	std::string description = "";
	Order* currentOrder = this->getOrderList();		// Récupérer la lite de commandes

	while (currentOrder != nullptr)					// Parcourir la liste et récupérer toutes les commandes du client X
	{
		if (currentOrder->getSender()->getName() == sender) 
		{
			description += currentOrder->toString();
			description += '\n';
		}
		currentOrder = currentOrder->getNext();
	}
	return description;
}

/*
	Retourne le biscuit dont le nom est X
	Retourne nullptr si le biscuit n'existe pas dans la liste
*/
Cookie* GeneralManager::FindCookieType(std::string name) 
{	
	Cookie* currentCookie = this->cookieList;		// Récupérer la liste de biscuits

	while (currentCookie != nullptr)		// Parcourir la liste et renvoyer le biscuit au nom X
	{
		if (currentCookie->getName() == name)
		{
			return currentCookie;
		}
		currentCookie = currentCookie->getNext();
	}
	return nullptr;
}

/*
	Ajoute un biscuit à la liste des biscuits existants
*/
void GeneralManager::AddCookieType(Cookie* cookieType) 
{
	Cookie* newCookieType = new Cookie(cookieType->getName(), cookieType->getNbCookiesOrdered());
	newCookieType->setNext (this->cookieList) ;
	this->cookieList = newCookieType;
}

/*
	Retourne le biscuit le plus populaire
*/
Cookie* GeneralManager::getMostPopularCookie(void) 
{
	
	Cookie* currentCookie = this->getCookieTypeList();
	Cookie* mostPopularCookie = currentCookie;

	while (currentCookie != nullptr) 
	{
		if (currentCookie->getNbCookiesOrdered() > mostPopularCookie->getNbCookiesOrdered())
		{
			mostPopularCookie = currentCookie;
		}
		currentCookie = currentCookie->getNext();
	}
	return mostPopularCookie;
}

/*
	Accesseur de la liste complète des biscuits
*/
Cookie* GeneralManager::getCookieTypeList(void) 
{
	return this->cookieList;
}

/*
	Accesseur de la liste de clients
*/
Customer* GeneralManager::getCustomerList(void) 
{
	return this->customersList;
}

/*
	Accesseur de la liste de commandes
*/
Order* GeneralManager::getOrderList(void) 
{
	return this->orderList;
}

/*
	Retourne le client au nom X
*/
Customer* GeneralManager::getCustomer(std::string name) 
{ 
	Customer* currentCustomer = this->getCustomerList();	// Récupérer la liste de clients

	while (currentCustomer != nullptr)		// Parcourir la liste et retourne le client au nom X
	{
		if (currentCustomer->getName () == name) 
		{
			return currentCustomer;
		}
		currentCustomer = currentCustomer->getNext();
	}
	// Création d'un client "temporaire" si le client n'existe pas dans la liste
	std::cout << "Customer non trouvé, creation de custumer temporaire. ";
	Customer* newCus = new Customer(name, "adresse non-trouvé", 0);
	this->AddCustomer(newCus);
	return newCus;
}

/*
	Retourne toutes les commandes de la liste (pour affichage)
*/
std::string GeneralManager::getOrderListDescription(void) 
{
	std::string description = "";
	Order* currentOrder = this->getOrderList();		// Récupérer la liste

	while (currentOrder != nullptr)					// Parcourir la liste et extraire chaque élément
	{
		description += currentOrder->toString();
		currentOrder = currentOrder->getNext();
	}
	return description;
}

/*
	Retourne tous les clients de la liste (pour affichage)
*/
std::string GeneralManager::getCustomerListDescription(void) 
{
	std::string description = "";
	Customer* currentCustomer = this->getCustomerList();	// Récupérer la liste

	while (currentCustomer != nullptr)						// Parcourir la liste et extraire chaque élément
	{
		description += currentCustomer->toString();
		currentCustomer = currentCustomer->getNext();
	}
	return description;
}

/*
	Retourne tous les biscuits de la liste (pour affichage)
*/
std::string GeneralManager::getCookieListDescription(void) 
{
	std::string description = "";
	Cookie* currentCookie = this->getCookieTypeList();		// Récupérer la liste

	while (currentCookie != nullptr)						// Parcourir la liste et extraire chaque élément
	{
		description += currentCookie->toString();			
		currentCookie = currentCookie->getNext();
	}
	return description;
}

/*
	Accesseur du prix de biscuits
*/
int GeneralManager::getCookiePrice() 
{
	return this->COOKIE_PRICE;
}

/*
	Accesseur du nombre de clients
*/
int GeneralManager::getNbCustomer() 
{
	return this->nbCustomer;
}
// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#include "Counter.h"
#include "Order.h"

Order::Order(Customer* sender, Customer* receiver) 
{
	this->sender = sender;
	this->receiver = receiver;
	this->cookieList = nullptr;
	this->next = nullptr;
	this->previous = nullptr;

	Counter::addConstrutor();
}

Order::~Order()				
{
	// Destruction de la liste de biscuit
	Cookie* currentList = this->getList();
	Cookie* currentCookie = currentList;

	while (currentList != nullptr) 
	{
		currentList = currentList->getNext();
		delete currentCookie;
		currentCookie = currentList;
	}
	
	Counter::addDestructor();
}

/*
	Ajouter un biscuit à la liste
*/
void Order::AddTypeOfCookie(Cookie* cookie) 
{
	Cookie* currentCookie = this->getList();		// Récupérer la liste
	if (currentCookie == nullptr)					// Si la liste est vide
	{
		this->cookieList = cookie;
		return;
	}
	cookie->setNext(currentCookie);				// Sinon, ajouter en tête de liste
	this->cookieList = cookie;
}

/*
	Accesseur de la liste de biscuits
*/
Cookie* Order::getList() 
{
	return this->cookieList;
}

/*
	Accesseur du client source
*/
Customer* Order::getSender() 
{
	return this->sender;
}

/*
	Accesseur du client destinataire
*/
Customer* Order::getReceiver() 
{
	return this->receiver;
}

/*
	Retourne la commande incluant la liste de biscuit (pour affichage)
*/
std::string Order::toString() 
{
	std::string orderDescription = "";
	Cookie* currentCookieType = this->getList();

	orderDescription += (this->sender->getName() + "\n" + this->receiver->getName() + "\n");

	while (currentCookieType != nullptr) 
	{
		orderDescription += (currentCookieType->toString());
		currentCookieType = currentCookieType->getNext();
	}

	orderDescription += "&\n";
	return orderDescription;
}

/*
	Accesseur de la commande précédente
*/
Order* Order::getPrevious() 
{
	return this->previous;
}

/*
	Accesseur de la commande suivante
*/
Order* Order::getNext() 
{
	return this->next;
}

/*
	Mutateur de la commande suivante
*/
void Order::setNext(Order* newNext) 
{
	this->next = newNext;
}

/*
	Mutateur de la commande précédente
*/
void Order::setPrevious(Order* newPrevious) 
{
	this->previous = newPrevious;
}
// Projet: 8INF259 - TP1 Commandes de biscuits
// Étudiants : André Alano, Audrey Bédard et Laurie - Ann Boily

#include "Counter.h"
#include "Cookie.h"
#include <string>

using namespace std;

Cookie::Cookie(string name) 
{
	this->name = name;
	this->next = nullptr;
	this->nbCookiesOrdered = 0;

	Counter::addConstrutor();
}

Cookie::Cookie(string name, int quantity) 
{
	this->name = name;
	this->next = nullptr;
	this->nbCookiesOrdered = quantity;

	Counter::addConstrutor();
}

Cookie::~Cookie() 
{
	Counter::addDestructor();
}

/*
	Accesseur du nom 
*/
string Cookie::getName() 
{
	return this->name;
}

/*
	Accesseur du biscuit suivant
*/
Cookie* Cookie::getNext() 
{
	return this->next;
}

/*
	Accesseur de la quantité de biscuits
*/
int Cookie::getNbCookiesOrdered() 
{
	return this->nbCookiesOrdered;
}

/*
	Retourne le biscuit (pour affichage)
*/
string Cookie::toString() 
{
	return this->getName() + " " + to_string (this->getNbCookiesOrdered()) + "\n";
}

/*
	Mutateur du biscuit suivant
*/
void Cookie::setNext(Cookie* newNext) 
{
	this->next = newNext;
}

/*
	Matateur de la quantité de biscuits
*/
void Cookie::setQuantity(int newQuantity) 
{
	this->nbCookiesOrdered = newQuantity;
}
#include "Cookie.h"
#include <string>

Cookie::Cookie(std::string name) {
	this->name = name;
	this->next = nullptr;
	this->nbCookiesOrdered = 0;
}

Cookie::Cookie(std::string name, int quantity) {
	this->name = name;
	this->next = nullptr;
	this->nbCookiesOrdered = quantity;
}

std::string Cookie::getName() {
	return this->name;
}

Cookie* Cookie::getNext() {
	return this->next;
}

int Cookie::getNbCookiesOrdered() {
	return this->nbCookiesOrdered;
}

std::string Cookie::toString() {
	return this->getName() + " " + std::to_string (this->getNbCookiesOrdered()) + "\n";
}

void Cookie::setNext(Cookie* newNext) {
	this->next = newNext;
}

void Cookie::setQuantity(int newQuantity) {
	this->nbCookiesOrdered = newQuantity;
}
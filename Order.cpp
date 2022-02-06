#include "Order.h"

Order::Order(Customer* sender, Customer* receiver) {
	this->sender = sender;
	this->receiver = receiver;
	this->cookieList = nullptr;
	this->next = nullptr;
	this->previous = nullptr;
}
Order::~Order() {
	// Detruire la cookieList
	if (this->getList() == nullptr)
		return;

	Cookie* currentCookie1 = this->getList();
	Cookie* currentCookie2 = nullptr;

	while (currentCookie2 != nullptr) {
		delete currentCookie1;
		currentCookie1 = currentCookie2;
	}

	this->cookieList = nullptr;
}
void Order::AddTypeOfCookie(Cookie* cookie) {
	Cookie* currentCookie = this->getList();
	if (currentCookie == nullptr) {
		this->cookieList = cookie;
		return;
	}

	cookie->setNext(currentCookie);
	this->cookieList = cookie;
}

Cookie* Order::getList() {
	return this->cookieList;
}
Customer* Order::getSender() {
	return this->sender;
}

Customer* Order::getReceiver() {
	return this->receiver;
}
std::string Order::toString() {
	std::string orderDescription = "";
	Cookie* currentCookieType = this->getList();

	orderDescription += (this->sender->getName() + "\n" + this->receiver->getName() + "\n");

	while (currentCookieType != nullptr) {
		orderDescription += (currentCookieType->toString());
		currentCookieType = currentCookieType->getNext();
	}

	orderDescription += "&\n";
	return orderDescription;
}

Order* Order::getPrevious() {
	return this->previous;
}
Order* Order::getNext() {
	return this->next;
}

void Order::setNext(Order* newNext) {
	this->next = newNext;
}
void Order::setPrevious(Order* newPrevious) {
	this->previous = newPrevious;
}
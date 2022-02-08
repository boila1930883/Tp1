#include "GeneralManager.h"

GeneralManager::GeneralManager(void) {
	this->customersList = nullptr;
	this->orderList = nullptr;
	this->cookieList = nullptr;
	this->nbCustomer = 0;
}
GeneralManager::~GeneralManager(void) { // Détruire les 3 listes

	Customer* currentCustomer = this->getCustomerList();
	Order* currentOrder = this->getOrderList();
	Cookie* currentCookie = this->getCookieTypeList();

	// Detruire liste customers
	while (this->getCustomerList() != nullptr) {
		std::cout << "Delete de :\n" << currentCustomer->toString();
		this->customersList = this->customersList->getNext();
		delete currentCustomer;
		currentCustomer = this->customersList;
	}

	// Detruire liste commandes
	while (this->getOrderList() != nullptr) {
		this->orderList = this->orderList->getNext();
		delete currentOrder;
		currentOrder = this->orderList;
	}

	// Detruide liste des CookieTypes
	while (this->getCookieTypeList() != nullptr) {
		this->cookieList = this->cookieList->getNext();
		delete currentCookie;
		currentCookie = this->cookieList;
	}

}
void GeneralManager::AddCustomer(Customer* newCustomer) { // La fonction recoit l'addresse memoire du nouveau client
	this->AddCustomer(newCustomer, 0);
}
// Ajout avec indice specifie
bool GeneralManager::AddCustomer(Customer* newCustomer, int index) { // Retourne false si l'index > taille liste
	int currentIndex = 0;
	Customer* currentCustomer = this->getCustomerList ();
	if (index > this->getNbCustomer() || index < 0) {
		return false;

	}

	//std::cout << "Ajout d'un client : " << newCustomer->toString();

	nbCustomer ++;

	if (this->getCustomerList () == nullptr) {
		this->customersList = newCustomer;
		return true;
	}

	if (index == 0) {						// Ajout à la tête lors du chargement de la liste
		currentCustomer->setPrevious(newCustomer);
		newCustomer->setNext(currentCustomer);
		this->customersList = newCustomer;
		return true;
	}

	while (currentIndex != index) {
		if (currentCustomer->getNext() != nullptr)
		{
			currentCustomer = currentCustomer->getNext();
		}
		currentIndex++;
	}
	
	if (index = nbCustomer - 1) {			// Si on ajoute a la queue
		newCustomer->setPrevious(currentCustomer);
		newCustomer->setNext(nullptr);
		currentCustomer->setNext(newCustomer) ;
		return true;
	}

	newCustomer->setNext(currentCustomer) ;
	newCustomer->setPrevious(currentCustomer->getPrevious());
	currentCustomer->getPrevious()->setNext(newCustomer);
	currentCustomer->setPrevious(newCustomer);
	return true;
}
bool GeneralManager::RemoveCustomer(std::string name) {
	Customer* currentCustomer = this->getCustomerList();

	while (currentCustomer != nullptr && currentCustomer->getName() != name) {
		currentCustomer = currentCustomer->getNext();
	}

	if (currentCustomer == nullptr)
		return false;

	nbCustomer--;

	if (this->getCustomerList() == currentCustomer) { // si tete de la liste
		this->customersList = currentCustomer->getNext();
		currentCustomer->getNext()->setPrevious(nullptr);
		delete currentCustomer;
		return true;
	}

	if (currentCustomer->getNext() == nullptr) {	// queue de la liste
		currentCustomer->getPrevious()->setNext(nullptr);
		delete currentCustomer;
		return true;
	}
	std::cout << "previous : " << currentCustomer->getNext();
	std::cout << "next:" << currentCustomer->getPrevious();
	currentCustomer->getPrevious()->setNext(currentCustomer->getNext());
	std::cout << "previous : " << currentCustomer->getNext();
	std::cout << "next:" << currentCustomer->getPrevious();
	currentCustomer->getNext()->setPrevious(currentCustomer->getPrevious());

	delete currentCustomer;
	return true;
}

void GeneralManager::AddOrder(Order* newOrder) {
	Order* currentOrder = this->getOrderList();
	Cookie* currentOrderCookie = newOrder->getList();
	Cookie* cookieType = nullptr;
	std::cout << "New Order: " << newOrder->toString();
	while (currentOrderCookie != nullptr) {
		cookieType = FindCookieType(currentOrderCookie->getName());
		if (cookieType == nullptr)
			AddCookieType(currentOrderCookie);
		else
			cookieType->setQuantity(cookieType->getNbCookiesOrdered() + currentOrderCookie->getNbCookiesOrdered());

		currentOrderCookie = currentOrderCookie->getNext();
		cookieType = nullptr;
	}
	if (this->getOrderList() == nullptr) { // si premier element
		this->orderList = newOrder;
		return;
	}
	// sinon
	newOrder->setNext(currentOrder);
	currentOrder->setPrevious(newOrder);
	this->orderList = newOrder;

}

bool GeneralManager::RemoveAllOrdersFrom(std::string sender) {
	Order * currentOrder = this->getOrderList();
	Cookie* currentCookie = nullptr;
	
	while (currentOrder != nullptr) {
		if (currentOrder->getSender()->getName() == sender) {
			// On soustrait les biscuits annules
			currentCookie = currentOrder->getList();
			while (currentCookie != nullptr) {
				this->FindCookieType(currentCookie->getName())->setQuantity(FindCookieType(currentCookie->getName())->getNbCookiesOrdered() - currentCookie->getNbCookiesOrdered());
				currentCookie = currentCookie->getNext();
			}

			if (currentOrder == this->getOrderList()) { // Tete
				currentOrder->getNext()->setPrevious(nullptr);
				this->orderList = currentOrder->getNext();
				delete currentOrder;
			}
			else if (currentOrder->getNext() == nullptr) {	// Si queue
				currentOrder->getPrevious()->setNext(nullptr);
				delete currentOrder;
				return true;
			}

			// Si ni queue ni tete
			currentOrder->getPrevious()->setNext(currentOrder->getNext());
			currentOrder->getNext()->setPrevious(currentOrder->getPrevious());

			

			delete currentOrder;
		}
		currentOrder = currentOrder->getNext();
	}

	return true;
}

std::string GeneralManager::GetDescriptionOfAllOrdersFrom(std::string sender) {
	std::string description = "";
	Order* currentOrder = this->getOrderList();

	while (currentOrder != nullptr) {
		if (currentOrder->getSender()->getName() == sender)
			description += currentOrder->toString();
	}

	return description;
}

Cookie* GeneralManager::FindCookieType(std::string name) {	// Retourne nullptr si le biscuit n'est pas encore repertorie

	Cookie* currentCookie = this->cookieList;

	while (currentCookie != nullptr) {
		if (currentCookie->getName() == name)
			return currentCookie;

		currentCookie = currentCookie->getNext();
	}

	return nullptr;
}

void GeneralManager::AddCookieType(Cookie* cookieType) {
	Cookie* newCookieType = new Cookie(cookieType->getName(), cookieType->getNbCookiesOrdered());
	newCookieType->setNext (this->cookieList) ;
	this->cookieList = newCookieType;
}

Cookie* GeneralManager::getMostPopularCookie(void) {
	
	Cookie* currentCookie = this->getCookieTypeList();
	Cookie* mostPopularCookie = currentCookie;

	while (currentCookie != nullptr) {
		if (currentCookie->getNbCookiesOrdered() > mostPopularCookie->getNbCookiesOrdered())
			mostPopularCookie = currentCookie;
	}

	return mostPopularCookie;
}

Cookie* GeneralManager::getCookieTypeList(void) {
	return this->cookieList;
}

Customer* GeneralManager::getCustomerList(void) {
	return this->customersList;
}

Order* GeneralManager::getOrderList(void) {
	return orderList;
}

Customer* GeneralManager::getCustomer(std::string name) { // Retourne null si le customer n'existe pas
	Customer* currentCustomer = this->getCustomerList();

	while (currentCustomer != nullptr) {
		if (currentCustomer->getName () == name) {
			return currentCustomer;
		}
		currentCustomer = currentCustomer->getNext();
	}

	return currentCustomer;
}

std::string GeneralManager::getOrderListDescription(void) {
	std::string description = "";
	Order* currentOrder = this->getOrderList();

	while (currentOrder != nullptr) {
		description += currentOrder->toString();
		currentOrder = currentOrder->getNext();
	}

	return description;
}
std::string GeneralManager::getCustomerListDescription(void) {
	std::string description = "";
	Customer* currentCustomer = this->getCustomerList();

	while (currentCustomer != nullptr) {
		description += currentCustomer->toString();
		currentCustomer = currentCustomer->getNext();
	}

	return description;
}
std::string GeneralManager::getCookieListDescription(void) {
	std::string description = "";
	Cookie* currentCookie = this->getCookieTypeList();

	while (currentCookie != nullptr) {
		description += currentCookie->toString();
		currentCookie = currentCookie->getNext();
	}

	return description;
}

int GeneralManager::getCookiePrice() {
	return this->COOKIE_PRICE;
}

int GeneralManager::getNbCustomer() {
	return this->nbCustomer;
}
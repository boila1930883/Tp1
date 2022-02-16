#pragma once

class Counter
{
private:
	static int constructor;			// Comptabilise le nombre de constructeurs appel�
	static int destructor;			// Comptabilise le nombre de destructeurs appel�

public:
	Counter();
	~Counter();

	static void addConstrutor() { constructor++; }
	static void addDestructor() { destructor++; }
	static int getNbConstructors() { return constructor; }
	static int getNbDestructors() { return destructor; }
};


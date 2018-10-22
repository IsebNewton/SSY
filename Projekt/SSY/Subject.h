#pragma once
#include <list>
#include "Observer.h"

class Subject
{
private:
	std::list<Observer<Subject>*> observers;

public:
	void addObserver(Observer<Subject>* observer);
	void removeObserver(Observer<Subject>* observer);

protected:
	void notify(const Subject& entity);
};


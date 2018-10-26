#pragma once
#include <list>
#include "Observer.h"

static const int MAX_OBSEVERS = 20;

template <class T>
class Subject
{
private:
	Observer<T> *observers[MAX_OBSEVERS];
	int count = 0;

public:
	void addObserver(Observer<T>* observer)
	{
		if (observer == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Observer NULL kann nicht hinzugefügt werden");
		}
		else if (count < MAX_OBSERVERS)
		{
			observer[count++] = observer;
		}
	}

	void removeObserver(Observer<T>* observer)
	{
		if (observer == NULL)
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Observer NULL kann nicht entfernt werden");
		}
		else if (count > 0)
		{
			for (int i = 0; i < count; i++)
			{
				if (observer == observers[i])
				{
					if (i != (count - 1))
					{
						// Observer ist nicht am Ende also den letzten Observer
						// in den freien Slot packen
						observers[i] = observers[count - 1];
					}
					count--;
				}
			}
		}
	}

protected:
	void notify()
	{
		for (int i = 0; i < count; i++)
		{
			observers[i]->onNotify(this);
		}
	}
};


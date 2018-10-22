#include "Subject.h"
#include <SDL.h>

void Subject::addObserver(Observer<Subject>* observer)
{
	if (observer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Observer NULL kann nicht hinzugefügt werden");
	}
	else if (std::find(observers.begin(), observers.end(), observer) == observers.end())
	{
		observers.push_back(observer);
	}
}

void Subject::removeObserver(Observer<Subject>* observer)
{
	if (observer == NULL)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Observer NULL kann nicht entfernt werden");
	}
	observers.remove(observer);
}

void Subject::notify(const Subject & entity)
{
	for (std::list<Observer<Subject>*>::iterator it = observers.begin(); it != observers.end(); ++it)
	{
		(*it)->onNotify(entity);
	}
}

#pragma once

template <class Entiny>
class Observer
{
public:
	virtual ~Observer() {};
	virtual void onNotify(const Entiny& entity) = 0;
};


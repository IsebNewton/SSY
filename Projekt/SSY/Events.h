#pragma once

class Events
{
public:
	virtual void onMouseOver() = 0;
	virtual void onMouseLeave() = 0;
	virtual void onClick() = 0;
	virtual void onResize() = 0;
};


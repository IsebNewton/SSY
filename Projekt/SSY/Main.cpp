// SSY.cpp: Definiert den Einstiegspunkt für die Konsolenanwendung.
//

#include <iostream>
#include "Core.h"

int main(int argc, char* args[])
{
	Core core = Core();
	try
	{
		core.startGame();
	}
	catch (const GenericError error)
	{
		std::cerr << error.what();
	}

    return 0;
}

 
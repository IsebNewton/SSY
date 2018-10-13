#pragma once

enum class ButtonState
{
	UP,
	UP_NOW,
	DOWN,
	DOWN_NOW
};

struct PauseState
{
	bool pauseNow = false;
	bool pause = false;
	bool resumeNow = false;
	bool resume = false;
};

class InputWrapper
{
public:
	//Verhindert das Instanziieren der Utitlity-Klasse:
	InputWrapper() = delete;

	//Initialisiert die Felder usw.
	static void initialize();
	static bool isInitialized();

	//Aktualisiert die Inhalte mithilfe der aktuellen SDL-Events
	static void updateEvents();

	//Abruf der Position der Maus:
	static int getMouseX();
	static int getMouseY();

	//Abruf der Maus-Tastenzustände:
	static bool isMouseButtonUp(int key);
	static bool isMouseButtonUpNow(int key);
	static bool isMouseButtonDown(int key);
	static bool isMouseButtonDownNow(int key);
	static ButtonState getMouseButtonState(int key);

	//Abruf der Tastatur-Tastenzustände:
	static bool isKeyUp(int key);
	static bool isKeyUpNow(int key);
	static bool isKeyDown(int key);
	static bool isKeyDownNow(int key);
	static ButtonState getKeyState(int key);

	//Sonder-Events:
	static bool isQuit();
	static bool isPause();
	static bool isPauseNow();
	static bool isResumeNow();
	static bool isResume();

private:
	static ButtonState keyStates[285];
	static ButtonState mouseStates[3];
	static int mouseX;
	static int mouseY;

	static bool quit;
	static PauseState pauseState;

	static bool initialized;
};
//Name:				InputWrapper
//Funktionalität:	Wrapped die SDL_EVENT-Funktionalität als Utility-Klasse


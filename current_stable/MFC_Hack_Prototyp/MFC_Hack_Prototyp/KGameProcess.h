#pragma once

#include "Utility.h"


class K_GameProcess
{
public:
	// C-Tor
	K_GameProcess(std::string psWindowName);
	
	// D-Tor
	~K_GameProcess();

	// Prüfen
	bool checkGameProcess();

	// Prüf Methoden
	bool isValidProcessID();
	bool isValidWindowHandle();
	bool attachToGameProcess();

	void refresh();

	// Getter
	HWND getGameWindowHandle(); 
	HANDLE getProcessHandle();
	std::string getErrorMessage();

protected:

	// Member
	std::string m_sWindowName;
	HWND m_hGameWindowHandle;
	DWORD m_dwProcessID;
	HANDLE m_hProcessHandle;
	std::string m_sErrorMessage;
};


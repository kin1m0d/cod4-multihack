#include "KGameProcess.h"

//
// C-tor
//
K_GameProcess::K_GameProcess(std::string psWindowName)
{
	this->m_sWindowName = psWindowName;
	this->m_hGameWindowHandle = FindWindowA(NULL, (LPCSTR)psWindowName.c_str());
	GetWindowThreadProcessId(this->m_hGameWindowHandle, &this->m_dwProcessID);
	this->m_sErrorMessage = "";
}


//
// D-Tor
//
K_GameProcess::~K_GameProcess()
{
}


//
// Ruft isValidProcessID() und attachToGameProcess()
//
bool K_GameProcess::checkGameProcess()
{
	if (this->isValidProcessID())
	{
		if (this->attachToGameProcess())
		{
			return True;
		}
	}
	return False;
}


//
// Prüft ob die PID gültig ist
//
bool K_GameProcess::isValidProcessID()
{
	if (this->m_dwProcessID != 0)
	{
		this->attachToGameProcess();
		return True;
	}
	this->m_sErrorMessage = "attachToGameProcess() - invalid process id: " + this->m_dwProcessID ;
	return False;
}


// 
// Öffnet den Ziel Prozess
//
bool K_GameProcess::attachToGameProcess()
{
	this->m_hProcessHandle = OpenProcess(PROCESS_ALL_ACCESS, False, this->m_dwProcessID);

	if (this->m_hProcessHandle == INVALID_HANDLE_VALUE)
	{
		this->m_sErrorMessage = "attachToGameProcess() - INVALID_HANDLE_VALUE";
		return False;
	}
	else if (this->m_hProcessHandle == NULL)
	{
		this->m_sErrorMessage = "attachToGameProcess() - could not open process";
		return False;
	}
	return True;	// Process is open
}


//
// Getter
//
HWND K_GameProcess::getGameWindowHandle()
{
	return this->m_hGameWindowHandle;
}

std::string K_GameProcess::getErrorMessage()
{
	return this->m_sErrorMessage;
}

HANDLE K_GameProcess::getProcessHandle()
{
	return this->m_hProcessHandle;
}



// MFC_Hack_Prototyp.h: Hauptheaderdatei für die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei für PCH einschließen"
#endif

#include "resource.h"		// Hauptsymbole


// HackApp:
// Siehe MFC_Hack_Prototyp.cpp für die Implementierung dieser Klasse
//

class HackApp : public CWinApp
{
public:
	HackApp();

// Überschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern HackApp theApp;
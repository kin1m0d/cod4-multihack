
// MFC_Hack_Prototyp.h: Hauptheaderdatei f�r die PROJECT_NAME-Anwendung
//

#pragma once

#ifndef __AFXWIN_H__
	#error "'stdafx.h' vor dieser Datei f�r PCH einschlie�en"
#endif

#include "resource.h"		// Hauptsymbole


// HackApp:
// Siehe MFC_Hack_Prototyp.cpp f�r die Implementierung dieser Klasse
//

class HackApp : public CWinApp
{
public:
	HackApp();

// �berschreibungen
public:
	virtual BOOL InitInstance();

// Implementierung

	DECLARE_MESSAGE_MAP()
};

extern HackApp theApp;
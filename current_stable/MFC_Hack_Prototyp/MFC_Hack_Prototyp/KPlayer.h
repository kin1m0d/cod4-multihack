#pragma once

#include "Utility.h"


class K_Player
{
public:
	K_Player();
	K_Player(HANDLE pProcessHandle);
	~K_Player();


	// Gibt die Spieler Position (x, y, z) als 3D Vector zurück
	K_Vector3D getPlayerPos3D() const   { return K_Vector3D(m_fPlayerPosX, m_fPlayerPosY, m_fPlayerPosZ); }

	// Gibt die Distanz zwischen zwei Spielern als float zurück
	float Get3dDistance(K_Player& pkPlayer);



	void setProcessHandle(HANDLE pProcessHandle);
	virtual bool readPlayerValues();



	//
	// Spieler Variablen
	//







	float m_fMousePosX;			// Maus Position X
	float m_fMousePosY;			// Maus Position Y
	float m_fPlayerPosX;		// Spieler Position X
	float m_fPlayerPosY;		// Spieler Position Y
	float m_fPlayerPosZ;		// Spieler Position Z
	int m_iClientNumber;
	int m_iTeam;
	int m_iHealth;
	DWORD m_dwIsInGame;




	HBRUSH m_ColorBrush;				// Farbe die dem Spieler zugeordnet wird für das ESP
	COLORREF m_ColorRGB;				// Farbe 
	

protected:
	HANDLE m_hProcessHandle;
};




class K_OtherPlayer : public K_Player
{
public:
	K_OtherPlayer();
	K_OtherPlayer(HANDLE pProcessHandle);

	virtual bool readPlayerValues(int piOffset = 0);

	char m_chName[16];
	int m_iIsValid;
	int m_iIsAlive;
	int m_iPose;				// Haltung (liegend, hockend, stehend)
	
};




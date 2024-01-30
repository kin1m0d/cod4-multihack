#pragma once

class K_Player2dCoord
{
public:
	// C-Tor
	K_Player2dCoord();
	K_Player2dCoord(int piW, int piH, float pfX, float pfY);

	// D-Tor
	~K_Player2dCoord();

	// Setter
	void setCoords(int piW, int piH, float pfX, float pfY);

	// Getter
	int getPointXasInt()	{ return static_cast<int>(this->m_fPointX); }
	int getPointYasInt()	{ return static_cast<int>(this->m_fPointY); }

	// Member
	int m_iBorderWidth;		// Wie Breit der Spieler ist (für den Rahmen)
	int m_iBorderHeight;	// Wie Hoch der Spieler ist (für den Rahmen)
	float m_fPointX;		// 2D Positon des Spielers
	float m_fPointY;		// 2D Positon des Spielers

	float m_fDistance;		// Distanz zwischen eigenem und dem Gegnerischen Spieler (aber im 3D Raum)
};


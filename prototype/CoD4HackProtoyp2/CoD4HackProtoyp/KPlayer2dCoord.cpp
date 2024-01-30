#include "KPlayer2dCoord.h"

//
// Standard C-Tor
//
K_Player2dCoord::K_Player2dCoord()
{
}

//
// C-Tor
//
K_Player2dCoord::K_Player2dCoord(int piW, int piH, float pfX, float pfY)
{
	this->m_iBorderWidth = piW;
	this->m_iBorderHeight = piH;
	this->m_fPointX = pfX;
	this->m_fPointY = pfY;
}


//
// D-Tor
//
K_Player2dCoord::~K_Player2dCoord()
{
}


//
// Setter
//
void K_Player2dCoord::setCoords(int piW, int piH, float pfX, float pfY)
{
	this->m_iBorderWidth = piW;
	this->m_iBorderHeight = piH;
	this->m_fPointX = pfX;
	this->m_fPointY = pfY;
}
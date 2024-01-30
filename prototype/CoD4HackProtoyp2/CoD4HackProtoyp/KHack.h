#pragma once

#include "Utility.h"
#include "KDrawController.h"
#include "KGameView.h"
#include "KPlayer.h"
#include "KPlayer2dCoord.h"



class K_Hack
{
public:
	K_Hack();
	K_Hack(HANDLE pProcessHandle, K_DrawController lkDrawer);
	~K_Hack();

	void initHack();
	void runHack();
	void loopHack();

	bool searchPlayers(AT_SearchPlayerOptions paOption = aFindAll);
	void setSearchPlayerOptions(AT_SearchPlayerOptions paOption){ this->m_aSearchPlayerOption = paOption; };

	HANDLE m_hProcessHandle;
	K_DrawController m_kDrawer;
	K_GameView m_kGameView;

	HBRUSH m_FriendlyBrush;
	HBRUSH m_EnemyBrush;
	COLORREF m_FriendlyColor;
	COLORREF m_EnemyColor;

	void turnOnOff_Crosshair()				{ this->m_b_drawCrosshair			= !this->m_b_drawCrosshair; };
	void turnOnOff_ESP()					{ this->m_b_drawESP					= !this->m_b_drawESP; };
	void turnOnOff_Snapline()				{ this->m_b_drawSnapline			= !this->m_b_drawSnapline; };
	void turnOnOff_Invincible()				{ this->m_b_drawInvincible			= !this->m_b_drawInvincible; };
	void turnOnOff_HealthDistanceRange()	{ this->m_b_drawHealthDistanceRange = !this->m_b_drawHealthDistanceRange; };
	void turnOnOff_Collision()				{ this->m_b_drawCollision			= !this->m_b_drawCollision; };
	void turnOnOff_SuperJump()				{ this->m_b_drawSuperJump			= !this->m_b_drawSuperJump; };
	void turnOnOff_HighSpeed()				{ this->m_b_drawHighSpeed			= !this->m_b_drawHighSpeed; };

protected:
	bool m_b_drawCrosshair				= True;
	bool m_b_drawESP					= True;
	bool m_b_drawSnapline				= True;
	bool m_b_drawInvincible				= True;
	bool m_b_drawHealthDistanceRange	= True;
	bool m_b_drawCollision				= True;
	bool m_b_drawSuperJump				= True;
	bool m_b_drawHighSpeed				= True;

	void drawCrosshair(COLORREF pColorRGB, int piBreiteHoehe, int piSizeOfCrosshair = 1);
	void drawESP(int piPlayerIndex);
	void drawSnapline(int piPlayerIndex);
	void drawHealthDistanceRange(int piPlayerIndex);
	void drawInvincible();
	void drawCollision();
	void drawSuperJump(float piHoehe = 39.0);
	void drawHighSpeed(int piSpeed = 190);
	void drawMiniMap();
	void drawDebug();

	K_Player2dCoord* m_pkTempPlayerCoords;			// Temporärer Gegner
	K_Player* m_pkI;								// Hier werde ich als K_Player gespeichert
	std::vector<K_OtherPlayer>* m_pcoPlayerList;	// Hier werden alle anderen Spieler als K_OtherPlayer gespeichert
	AT_SearchPlayerOptions m_aSearchPlayerOption;	// Such Option (alle Spieler oder nur Feinde finden)
};


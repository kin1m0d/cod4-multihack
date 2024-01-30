#pragma once

#include "Utility.h"
#include "KGameProcess.h"
#include "KDrawController.h"
#include "KGameView.h"
#include "KPlayer.h"
#include "KPlayer2dCoord.h"
#include "K_Convert.h"
#include <thread>

class K_Hack
{
public:
	K_Hack();
	K_Hack(HANDLE pProcessHandle, K_DrawController lkDrawer);
	K_Hack(K_GameProcess pkGameProcess);
	~K_Hack();

	void initHack();
	void runHacks();
	void runGDIHacks();
	void runHackAsThread();
	void loopHack();

	bool searchPlayers();
	void stopHack();

	HANDLE m_hProcessHandle;
	K_DrawController m_kDrawer;
	K_GameView m_kGameView;
	K_Convert cast;

	////////////////////////////////////////////////////////////////////////////////////////////

	// GDI Hacks - Player
	void turnOnOff_ESP()					{ this->m_b_hackESP					= !this->m_b_hackESP; };
	void turnOnOff_Snapline()				{ this->m_b_hackSnapline			= !this->m_b_hackSnapline; };
	void turnOnOff_HealthDistanceRange()	{ this->m_b_hackHealthDistanceRange = !this->m_b_hackHealthDistanceRange; };
	// GDI Hacks
	void turnOnOff_Crosshair()				{ this->m_b_hackCrosshair			= !this->m_b_hackCrosshair; };
	void turnOnOff_MiniMap()				{ this->m_b_hackMiniMap				= !this->m_b_hackMiniMap; };
	void turnOnOff_ShowInfo()				{ this->m_b_hackShowInfo			= !this->m_b_hackShowInfo; };

	// Normal Hacks
	void turnOnOff_Invincible()				{ this->m_b_hackInvincible			= !this->m_b_hackInvincible; };
	void turnOnOff_SuperJump()				{ this->m_b_hackSuperJump			= !this->m_b_hackSuperJump; };
	void turnOnOff_Collision()				{ this->m_b_hackCollision			= !this->m_b_hackCollision; };
	void turnOnOff_HighSpeed()				{ this->m_b_hackHighSpeed			= !this->m_b_hackHighSpeed; };


	////////////////////////////////////////////////////////////////////////////////////////////

	AT_SearchPlayerOptions m_aSearchPlayerOption = aFindAll;
	float m_fSuperJumpValue = 39.0;
	int m_iHighSpeedValue = 190;

	int m_iESPLineWidth = 1;
	int m_iSnapLineLineWidth = 1;

	int m_iCrosshairLineWidth = 1;
	int m_iCrosshairSize = 2000;

	HBRUSH m_BrushAllies;
	HBRUSH m_BrushEnemys;

	COLORREF m_ColorAllies;
	COLORREF m_ColorEnemys;
	COLORREF m_ColorCrosshair;

	////////////////////////////////////////////////////////////////////////////////////////////

	void setSearchPlayerOptions(AT_SearchPlayerOptions paOption)		{ this->m_aSearchPlayerOption = paOption; };

	////////////////////////////////////////////////////////////////////////////////////////////

protected:
	bool m_b_hackESP					= HACK_OFF;
	bool m_b_hackSnapline				= HACK_OFF;
	bool m_b_hackHealthDistanceRange	= HACK_OFF;
	bool m_b_hackCrosshair				= HACK_OFF;
	bool m_b_hackMiniMap				= HACK_OFF;
	bool m_b_hackShowInfo				= HACK_OFF;

	bool m_b_hackInvincible				= HACK_OFF;
	bool m_b_hackSuperJump				= HACK_OFF;
	bool m_b_hackCollision				= HACK_OFF;
	bool m_b_hackHighSpeed				= HACK_OFF;

	bool m_bStopHack = False;




	// GDI Hacks
	void hackESP(int piPlayerIndex);
	void hackSnapline(int piPlayerIndex);
	void hackHealthDistanceRange(int piPlayerIndex);

	void hackCrosshair();
	void hackMiniMap();
	void hackShowInfo();


	// Normal Hacks
	void hackInvincible();
	void hackCollision();
	void hackSuperJump();
	void hackHighSpeed();

	void hackAimbot();


	K_Player2dCoord* m_pkTempPlayerCoords;			// Temporärer Gegner
	K_Player* m_pkI;								// Hier werde ich als K_Player gespeichert
	std::vector<K_OtherPlayer>* m_pcoPlayerList;	// Hier werden alle anderen Spieler als K_OtherPlayer gespeichert
};


#include "stdafx.h"
#include "KHack.h"

#include "HackDlg.h"

#include "KColor.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
K_Hack::K_Hack()
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
K_Hack::K_Hack(HANDLE pProcessHandle, K_DrawController pkDrawer)
{
	this->m_hProcessHandle = pProcessHandle;
	this->m_kDrawer = pkDrawer;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
K_Hack::K_Hack(K_GameProcess pkGameProcess)
{
	this->m_hProcessHandle = pkGameProcess.getProcessHandle();
	K_DrawController lkDrawer(::GetDC(pkGameProcess.getGameWindowHandle()));
	this->m_kDrawer = lkDrawer;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
K_Hack::~K_Hack()
{
	KS_DELETE(this->m_pkI);
	KS_DELETE(this->m_pcoPlayerList);
	KS_DELETE(this->m_pkTempPlayerCoords);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::initHack()
{
	this->m_ColorAllies = RGB(0, 255, 0);						// Grün
	this->m_ColorEnemys = RGB(255, 0, 0);						// Rot
	this->m_BrushEnemys = CreateSolidBrush(RGB(255, 0, 0));		// Roter Brush
	this->m_BrushAllies = CreateSolidBrush(RGB(0, 255, 0));		// Grüner Brush

	this->m_pkI = new K_Player(this->m_hProcessHandle);
	this->m_pkI->readPlayerValues();
	this->m_pcoPlayerList = new std::vector <K_OtherPlayer>;
	this->m_pkTempPlayerCoords = new K_Player2dCoord;

	this->m_kGameView.initialize(this->m_hProcessHandle);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::loopHack()
{
	while (!this->m_bStopHack)
	{
		this->runHacks();
		this->runGDIHacks();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::stopHack()
{
	this->m_bStopHack = True;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::runHackAsThread()
{
	std::thread lkWorkerThread(&K_Hack::loopHack, this);		// Thread starten
	lkWorkerThread.detach();									// Thread ohne warten abfeuern
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool K_Hack::searchPlayers()
{
	assert(this->m_pkI->readPlayerValues());

	if (this->m_pkI->m_dwIsInGame > 0)
	{
		int liMaxSizeOfPlayer = 64;										// Maximaler Schleifendurchlauf
		int liPlayerNotFoundCounter = 0;								// Abbruch counter

		for (int i = 0; i < liMaxSizeOfPlayer; i++)
		{
			K_OtherPlayer lkOtherPlayer(this->m_hProcessHandle);		// Player erstellen
			lkOtherPlayer.readPlayerValues(i);							// Player initialisieren

			if (lkOtherPlayer.m_iIsValid == IS_VALID && lkOtherPlayer.m_iClientNumber != this->m_pkI->m_iClientNumber)
			{
				if (lkOtherPlayer.m_iTeam == this->m_pkI->m_iTeam)		// Player ist in meinem Team
				{
					if (this->m_aSearchPlayerOption == AT_SearchPlayerOptions::aFindOnlyTeam2) { Continue; }
					lkOtherPlayer.m_ColorBrush = this->m_BrushAllies;
					lkOtherPlayer.m_ColorRGB = this->m_ColorAllies; 
				}
				else													// Player ist im Gegner Team
				{
					if (this->m_aSearchPlayerOption == AT_SearchPlayerOptions::aFindOnlyTeam1) { Continue; }
					lkOtherPlayer.m_ColorBrush = this->m_BrushEnemys;
					lkOtherPlayer.m_ColorRGB = this->m_ColorEnemys;
				}
				this->m_pcoPlayerList->push_back(lkOtherPlayer);		// Player dem Container hinzufügen
			}
			else
			{
				if (liPlayerNotFoundCounter == 3)	{ Break; }			// Falls 3 mal kein Spieler gefunden wurd, Schleife abbrechen!
				++liPlayerNotFoundCounter;
			}
		} // for schleife zu ende
		return True;
	}
	return False;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::runHacks()
{
	this->hackCrosshair();
	this->hackInvincible();
	this->hackCollision();
	this->hackHighSpeed();
	this->hackSuperJump();
	//this->hackAimbot();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::runGDIHacks()
{
	//assert(this->searchPlayers(this->m_aSearchPlayerOption));

	if (!this->searchPlayers()) { return; }

	this->hackMiniMap();
	this->hackShowInfo();

	if (this->m_pkI->m_dwIsInGame > 0)
	{
		for (unsigned int i = 0; i < this->m_pcoPlayerList->size(); i++)
		{
			// Durch 48, damit die Distanz in Metern auch stimmt !!! Wichtig!
			this->m_pkTempPlayerCoords->m_fDistance = this->m_pkI->getPlayerPos3D().SubVectorDist(this->m_pcoPlayerList->at(i).getPlayerPos3D()).GetLaenge() / 48;
	
			K_Vector3D lkLocal = this->m_pcoPlayerList->at(i).getPlayerPos3D().SubVectorDist(this->m_pkI->getPlayerPos3D());
			
			// 3D zu 2D Koordinaten
			if (this->m_kGameView.WorldToScreen(lkLocal, this->m_pkTempPlayerCoords->m_fPointX, this->m_pkTempPlayerCoords->m_fPointY))
			{
				this->m_pkTempPlayerCoords->m_iBorderWidth = static_cast<int>(800.0f / this->m_pkTempPlayerCoords->m_fDistance);
				this->m_pkTempPlayerCoords->m_iBorderHeight = (this->m_pkTempPlayerCoords->m_iBorderWidth * 2);

				this->hackESP(i);
				this->hackSnapline(i);
				this->hackHealthDistanceRange(i);
				this->hackAimbot();
			} 
		}
	}
	this->m_pcoPlayerList->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackCrosshair()
{
	if (!this->m_b_hackCrosshair) { return; }

	int liX = this->m_kGameView.m_iScreenCenter[X];
	int liY = this->m_kGameView.m_iScreenCenter[Y];
	this->m_kDrawer.drawLine(liX, liY - this->m_iCrosshairSize, liX, liY + this->m_iCrosshairSize, this->m_ColorCrosshair, this->m_iCrosshairLineWidth);
	this->m_kDrawer.drawLine(liX - this->m_iCrosshairSize, liY, liX + this->m_iCrosshairSize, liY, this->m_ColorCrosshair, this->m_iCrosshairLineWidth);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackESP(int piPlayerIndex)
{
	if (!this->m_b_hackESP) { return; }

	if (this->m_pcoPlayerList->at(piPlayerIndex).m_iPose == PLAYER_LIEGT)	// liegt
		this->m_pkTempPlayerCoords->m_iBorderHeight = this->m_pkTempPlayerCoords->m_iBorderWidth / 2;

	if (this->m_pcoPlayerList->at(piPlayerIndex).m_iPose == PLAYER_HOCKT)	// hockt
		this->m_pkTempPlayerCoords->m_iBorderHeight = this->m_pkTempPlayerCoords->m_iBorderWidth;

	if (this->m_pcoPlayerList->at(piPlayerIndex).m_iPose == PLAYER_STEHT)	// steht
		this->m_pkTempPlayerCoords->m_iBorderHeight = (this->m_pkTempPlayerCoords->m_iBorderWidth * 2);

	this->m_kDrawer.drawBorderBox(
		this->m_pkTempPlayerCoords->getPointXasInt() - (this->m_pkTempPlayerCoords->m_iBorderWidth / 2),
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight,
		this->m_pkTempPlayerCoords->m_iBorderWidth,
		this->m_pkTempPlayerCoords->m_iBorderHeight,
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorBrush,
		this->m_iESPLineWidth
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackSnapline(int piPlayerIndex)
{
	if (!this->m_b_hackSnapline) { return; }

	this->m_kDrawer.drawLine(this->m_kGameView.m_iScreenResolution[0] / 2,
		this->m_kGameView.m_iScreenResolution[1],
		this->m_pkTempPlayerCoords->getPointXasInt(),
		this->m_pkTempPlayerCoords->getPointYasInt(),
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB,
		this->m_iSnapLineLineWidth
		);

	//SetCursorPos(this->m_pkTempPlayerCoords->getPointXasInt(), this->m_pkTempPlayerCoords->getPointYasInt());
}

void K_Hack::hackAimbot()
{
	if (GetAsyncKeyState('J' /*VK_RBUTTON*/ ))
	{
		RECT wndRect;
		HWND Handle = FindWindow(0, _T("Call of Duty 4"));
		GetWindowRect(Handle, &wndRect);
		//put our mouse on the enemy, WindowRect is grabbed on our constructor at the top
		//And this is optimized for Windowed Games but will work just fine on Non Windowed
		
		float lfx, lfy;

		K_Vector3D lkLocal = this->m_pcoPlayerList->at(0).getPlayerPos3D().SubVectorDist(this->m_pkI->getPlayerPos3D());
		this->m_kGameView.WorldToScreen(lkLocal, lfx, lfy);

		POINT curserPos;
		GetCursorPos(&curserPos);

		int xDist = abs(curserPos.x - this->m_pkTempPlayerCoords->getPointXasInt());

		//SetCursorPos(/*wndRect.left + */(int)lfx / this->m_pkTempPlayerCoords->m_fDistance, /*wndRect.top + */(int)lfy / this->m_pkTempPlayerCoords->m_fDistance);
		
		if (curserPos.x > this->m_pkTempPlayerCoords->getPointXasInt())
		{
			SetCursorPos(curserPos.x - xDist, curserPos.y);
		}
		else
		{
			SetCursorPos(curserPos.x + xDist, curserPos.y);
		}

		
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackInvincible()
{
	if (!this->m_b_hackInvincible) { return; }

	DWORD AdressHealth = 0x012886A0;
	int ValueHealth = 0;
	WriteProcessMemory(this->m_hProcessHandle, (BYTE*)AdressHealth, (LPCVOID)&ValueHealth, sizeof(ValueHealth) - 1, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackHealthDistanceRange(int piPlayerIndex)
{
	if (!this->m_b_hackHealthDistanceRange) { return; }
		
	int liOffsetX = 4;

	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight,
		std::to_string(this->m_pcoPlayerList->at(piPlayerIndex).m_iHealth) + " HP",
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);

	/////////////////////////////////////////////////////////////////////////////
	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight + 20,
		this->m_pcoPlayerList->at(piPlayerIndex).m_chName,
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);

	/////////////////////////////////////////////////////////////////////////////
	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight + 40,
		std::to_string(static_cast<int>(this->m_pkTempPlayerCoords->m_fDistance)) + " m",
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackCollision()
{
	if (!this->m_b_hackCollision)
	{
		DWORD Adress = 0x01328624;
		int Value = 0;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
		return;
	}

	DWORD Adress = 0x01328624;
	int Value = 1;
	WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackSuperJump()
{
	DWORD Adress = 0x0CBBBCBC;
	
	if (!this->m_b_hackSuperJump)
	{
		float Val = 39.0;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Val, sizeof(Val), NULL);
		return;
	}

	float Value = this->m_fSuperJumpValue;
	WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value), NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackHighSpeed()
{
	DWORD Adress = 0x0CBC0AD0;

	if (!this->m_b_hackHighSpeed)
	{
		int Value = 190;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
		return;
	}

	int Value = this->m_iHighSpeedValue;
	WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackShowInfo()
{
	if (!this->m_b_hackShowInfo)
	{
		return;
	}

	this->m_kDrawer.drawString(10, 250, "PosX = " + this->cast.to_string(this->m_pkI->m_fPlayerPosX), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 270, "PosY = " + this->cast.to_string(this->m_pkI->m_fPlayerPosY), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 290, "PosZ = " + this->cast.to_string(this->m_pkI->m_fPlayerPosZ), RGB(255, 0, 0));

	this->m_kDrawer.drawString(10, 320, "Health = " + this->cast.to_string(this->m_pkI->m_iHealth), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 340, "JumpHeigth = " + this->cast.to_string(static_cast<int>(this->m_fSuperJumpValue)), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 360, "HighSpeed = " + this->cast.to_string(this->m_iHighSpeedValue), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 380, "Collision = " + this->cast.to_string(this->m_b_hackCollision), RGB(255, 0, 0));
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::hackMiniMap()
{

#ifdef DEBUG

	if (!this->m_b_hackMiniMap)
	{
		return;
	}

	int ichX = 102;
	int ichY = 115;
	float faktor = 8.152173913;

	//HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
	this->m_kDrawer.drawBorderBox(10, 30, 185, 185, this->m_BrushEnemys, 3);
	this->m_kDrawer.drawPoint(ichX, ichY, this->m_BrushEnemys);



	float liOffset = 750.0;
	float Ax, Ay, Bx, By;
	float distX, distY;


	// ca. 10m im Spiel sind 500.0f
	// also 15m = 750.0f

	for (unsigned int i = 0; i < this->m_pcoPlayerList->size(); i++)
	{
		Ax = this->m_pkI->m_fPlayerPosX;
		Ay = this->m_pkI->m_fPlayerPosY;

		Bx = this->m_pcoPlayerList->at(i).m_fPlayerPosX;
		By = this->m_pcoPlayerList->at(i).m_fPlayerPosY;

		distX = abs(Ax - Bx);
		distY = abs(Ay - By);


		bool istImBereich = False;
		bool istHigherX;
		bool istHigherY;

		if (Bx < (Ax + liOffset) && Bx >(Ax - liOffset))
		{
			if (By < (Ay + liOffset) && By >(Ay - liOffset))
			{
				istImBereich = True;
				//this->m_kDrawer.drawPoint(ichX + (distX / faktor), ichY + (distY / faktor), this->m_BrushAllies);
			}
		}

		if (istImBereich)
		{
			if (Bx > Ax)
			{
				istHigherX = True;
			}
			else
			{
				istHigherX = False;
			}


			if (By > Ay)
			{
				istHigherY = True;
			}
			else
			{
				istHigherY = False;
			}


			if (istHigherX == True && istHigherY == True)
			{
				this->m_kDrawer.drawPoint(ichX + (distX / faktor), ichY - (distY / faktor), this->m_pcoPlayerList->at(i).m_ColorBrush);
			}

			if (istHigherX == False && istHigherY == False)
			{
				this->m_kDrawer.drawPoint(ichX - (distX / faktor), ichY + (distY / faktor), this->m_pcoPlayerList->at(i).m_ColorBrush);
			}

			if (istHigherX == True && istHigherY == False)
			{
				this->m_kDrawer.drawPoint(ichX + (distX / faktor), ichY + (distY / faktor), this->m_pcoPlayerList->at(i).m_ColorBrush);
			}

			if (istHigherX == False && istHigherY == True)
			{
				this->m_kDrawer.drawPoint(ichX - (distX / faktor), ichY - (distY / faktor), this->m_pcoPlayerList->at(i).m_ColorBrush);
			}
		}
	}
#endif
}















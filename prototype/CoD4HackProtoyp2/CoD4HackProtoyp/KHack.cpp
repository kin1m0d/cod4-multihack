#include "KHack.h"




K_Hack::K_Hack()
{
}

K_Hack::K_Hack(HANDLE pProcessHandle, K_DrawController lkDrawer)
{
	this->m_hProcessHandle = pProcessHandle;
	this->m_kDrawer = lkDrawer;
}


K_Hack::~K_Hack()
{
	KS_DELETE(this->m_pkI);
	KS_DELETE(this->m_pcoPlayerList);
	KS_DELETE(this->m_pkTempPlayerCoords);
}



void K_Hack::initHack()
{
	this->m_FriendlyColor = RGB(0, 255, 0);						// Grün
	this->m_EnemyColor = RGB(255, 0, 0);						// Rot
	this->m_EnemyBrush = CreateSolidBrush(RGB(255, 0, 0));		// Roter Brush
	this->m_FriendlyBrush = CreateSolidBrush(RGB(0, 255, 0));	// Grüner Brush

	this->m_pkI = new K_Player(this->m_hProcessHandle);
	this->m_pkI->readPlayerValues();
	this->m_pcoPlayerList = new std::vector <K_OtherPlayer>;
	this->m_pkTempPlayerCoords = new K_Player2dCoord;

	this->m_kGameView.initialize(this->m_hProcessHandle);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::loopHack()
{
	while (True)
	{
		this->runHack();
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool K_Hack::searchPlayers(AT_SearchPlayerOptions paOption)
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
					if (paOption == AT_SearchPlayerOptions::aFindOnlyEnemys) { Continue; }
					lkOtherPlayer.m_ColorBrush = this->m_FriendlyBrush;
					lkOtherPlayer.m_ColorRGB = this->m_FriendlyColor; 
				}
				else													// Player ist im Gegner Team
				{
					lkOtherPlayer.m_ColorBrush = this->m_EnemyBrush;
					lkOtherPlayer.m_ColorRGB = this->m_EnemyColor;
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
void K_Hack::runHack()
{
	assert(this->searchPlayers(this->m_aSearchPlayerOption));

	this->drawCrosshair(RGB(255, 0, 0), 10);
	this->drawInvincible();
	this->drawCollision();
	this->drawHighSpeed();
	this->drawSuperJump();

	this->drawMiniMap();
	this->drawDebug();

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

				this->drawESP(i);
				this->drawSnapline(i);
				this->drawHealthDistanceRange(i);
			} 
		} // ende for schleife
	}

	this->m_pcoPlayerList->clear();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawCrosshair(COLORREF pColorRGB, int piBreiteHoehe, int piSizeOfCrosshair)
{
	if (!this->m_b_drawCrosshair)
		return;

	int liX = this->m_kGameView.m_iScreenCenter[X];
	int liY = this->m_kGameView.m_iScreenCenter[Y];
	this->m_kDrawer.drawLine(liX, liY - piBreiteHoehe, liX, liY + piBreiteHoehe, pColorRGB, piSizeOfCrosshair);
	this->m_kDrawer.drawLine(liX - piBreiteHoehe, liY, liX + piBreiteHoehe, liY, pColorRGB, piSizeOfCrosshair);
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawESP(int piPlayerIndex)
{
	if (!this->m_b_drawESP)
		return;

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
		1
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawSnapline(int piPlayerIndex)
{
	if (!this->m_b_drawSnapline)
		return;

	this->m_kDrawer.drawLine(this->m_kGameView.m_iScreenResolution[0] / 2,
		this->m_kGameView.m_iScreenResolution[1],
		this->m_pkTempPlayerCoords->getPointXasInt(),
		this->m_pkTempPlayerCoords->getPointYasInt(),
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB,
		1
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawInvincible()
{
	if (!this->m_b_drawInvincible)
		return;

	DWORD AdressHealth = 0x012886A0;
	int ValueHealth = 0;
	WriteProcessMemory(this->m_hProcessHandle, (BYTE*)AdressHealth, (LPCVOID)&ValueHealth, sizeof(ValueHealth) - 1, NULL);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawHealthDistanceRange(int piPlayerIndex)
{
	if (!this->m_b_drawHealthDistanceRange) 
		return;
		

	int liOffsetX = 4;

	//std::stringstream lkStreamHealth;
	//lkStreamHealth << this->m_pcoPlayerList->at(piPlayerIndex).m_iHealth << " HP";

	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight,
		//lkStreamHealth.str().c_str(),
		std::to_string(this->m_pcoPlayerList->at(piPlayerIndex).m_iHealth),
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);

	/////////////////////////////////////////////////////////////////////////////

	//std::stringstream lkStreamName;
	//lkStreamName << std::string(this->m_pcoPlayerList->at(piPlayerIndex).m_chName);

	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight + 20,
		//lkStreamName.str().c_str(),
		//std::to_string(this->m_pcoPlayerList->at(piPlayerIndex).m_chName),
		this->m_pcoPlayerList->at(piPlayerIndex).m_chName,
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);

	/////////////////////////////////////////////////////////////////////////////

	//std::stringstream lkStreamDistance;
	//lkStreamDistance << floorf(this->m_pkTempPlayerCoords->m_fDistance) << " m";

	this->m_kDrawer.drawString(
		this->m_pkTempPlayerCoords->getPointXasInt() + (this->m_pkTempPlayerCoords->m_iBorderWidth / 2) + liOffsetX,
		this->m_pkTempPlayerCoords->getPointYasInt() - this->m_pkTempPlayerCoords->m_iBorderHeight + 40,
		//lkStreamDistance.str().c_str(),
		std::to_string(this->m_pkTempPlayerCoords->m_fDistance),
		this->m_pcoPlayerList->at(piPlayerIndex).m_ColorRGB
		);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawCollision()
{
	if (this->m_b_drawCollision)
	{
		DWORD Adress = 0x01328624;
		int Value = 0;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
	}
	else
	{
		DWORD Adress = 0x01328624;
		int Value = 1;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawSuperJump(float piHoehe)
{
	DWORD Adress = 0x0CBBBCBC;

	if (this->m_b_drawSuperJump)
	{
		float Value = 900;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value), NULL);
	}
	else
	{
		float Value = piHoehe;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) , NULL);
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawHighSpeed(int piSpeed)
{
	DWORD Adress = 0x0CBC0AD0;

	if (this->m_b_drawHighSpeed)
	{
		int Value = 500;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
	}
	else
	{
		int Value = piSpeed;
		WriteProcessMemory(this->m_hProcessHandle, (BYTE*)Adress, (LPCVOID)&Value, sizeof(Value) - 1, NULL);
	}
}








/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawDebug()
{
	std::stringstream Xpos;
	Xpos << "X-Achse: " << this->m_pkI->m_fPlayerPosX;
	std::stringstream Ypos;
	Ypos << "Y-Achse: " << this->m_pkI->m_fPlayerPosY;
	std::stringstream Zpos;
	Zpos << "Z-Achse: " << this->m_pkI->m_fPlayerPosZ;

	this->m_kDrawer.drawString(10, 250, Xpos.str(), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 270, Ypos.str(), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 290, Zpos.str(), RGB(255, 0, 0));

	//std::stringstream MausPosX;
	//MausPosX << "Maus X: " << this->m_pkI->m_fMousePosX;
	//std::stringstream MausPosY;
	//MausPosY << "Maus Y: " << this->m_pkI->m_fMousePosY;

	//this->m_kDrawer.drawString(10, 320, MausPosX.str(), RGB(255, 0, 0));
	//this->m_kDrawer.drawString(10, 340, MausPosY.str(), RGB(255, 0, 0));


	std::stringstream Xpos2;
	Xpos2 << "X-Achse: " << this->m_pcoPlayerList->at(0).m_fPlayerPosX;
	std::stringstream Ypos2;
	Ypos2 << "Y-Achse: " << this->m_pcoPlayerList->at(0).m_fPlayerPosY;
	std::stringstream Zpos2;
	Zpos2 << "Z-Achse: " << this->m_pcoPlayerList->at(0).m_fPlayerPosZ;

	this->m_kDrawer.drawString(10, 320, Xpos2.str(), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 340, Ypos2.str(), RGB(255, 0, 0));
	this->m_kDrawer.drawString(10, 360, Zpos2.str(), RGB(255, 0, 0));

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void K_Hack::drawMiniMap()
{
	int ichX = 102;
	int ichY = 115;
	float faktor = 8.152173913;

	//HBRUSH brush = CreateSolidBrush(RGB(0, 255, 255));
	this->m_kDrawer.drawBorderBox(10, 30, 185, 185, this->m_EnemyBrush, 3);
	this->m_kDrawer.drawPoint(ichX, ichY, this->m_EnemyBrush);



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
				//this->m_kDrawer.drawPoint(ichX + (distX / faktor), ichY + (distY / faktor), this->m_FriendlyBrush);
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
}















#include "KPlayer.h"


//
// C-tor
//
K_Player::K_Player()
{
}

K_Player::K_Player(HANDLE pProcessHandle)
{
	this->m_hProcessHandle = pProcessHandle;
}




//
// D-tor
//
K_Player::~K_Player()
{
}




float K_Player::Get3dDistance(K_Player& pkPlayer)
{
	return (sqrt(
		((this->m_fPlayerPosX - pkPlayer.m_fPlayerPosX) * (this->m_fPlayerPosX - pkPlayer.m_fPlayerPosX)) +
		((this->m_fPlayerPosY - pkPlayer.m_fPlayerPosY) * (this->m_fPlayerPosY - pkPlayer.m_fPlayerPosY)) +
		((this->m_fPlayerPosZ - pkPlayer.m_fPlayerPosZ) * (this->m_fPlayerPosZ - pkPlayer.m_fPlayerPosZ))
		));
}

bool K_Player::readPlayerValues()
{
	assert(this->m_hProcessHandle != nullptr);

	if (this->m_hProcessHandle == nullptr)
	{
		return False;
	}

	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x12886A0, &this->m_iHealth, 4, NULL);			// Leben
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x74E35C, &this->m_dwIsInGame, 4, NULL);		// Ist im Game
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x74E338, &this->m_iClientNumber, 4, NULL);	// Klientnummer
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x83928C, &this->m_iTeam, 4, NULL);			// Team
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x797618, &this->m_fPlayerPosX, 4, NULL);		// Spieler Position X
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x79761C, &this->m_fPlayerPosY, 4, NULL);		// Spieler Position Y
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x797620, &this->m_fPlayerPosZ, 4, NULL);		// Spieler Position Z

	return True;
}


void K_Player::setProcessHandle(HANDLE pProcessHandle)
{
	assert(this->m_hProcessHandle != nullptr);
	this->m_hProcessHandle = pProcessHandle;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





K_OtherPlayer::K_OtherPlayer()
{
}

K_OtherPlayer::K_OtherPlayer(HANDLE pProcessHandle)
{
	this->m_hProcessHandle = pProcessHandle;
}





bool K_OtherPlayer::readPlayerValues(int piOffset)
{
	assert(this->m_hProcessHandle != nullptr);

	if (this->m_hProcessHandle == nullptr)
	{
		return False;
	}

	for (int i = 0; i < 16; i++)
	{
		ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + (0xC + i)), &this->m_chName[i], 1, NULL);	// Spielername
	}
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC), &this->m_iIsValid, 4, NULL);				// Ist gültig?
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x84F2D8 + piOffset * 0x1DC + 0x1C0), &this->m_iIsAlive, 4, NULL);		// Is am leben?
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x84F2D8 + piOffset * 0x1DC + 0xCC), &this->m_iClientNumber, 4, NULL);	// Klientnummer
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + 0x1C), &this->m_iTeam, 4, NULL);			// Team
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x12886A0 + piOffset * 0x274), &this->m_iHealth, 4, NULL);				// Leben
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + 0x398), &this->m_fPlayerPosX, 4, NULL);		// 0x4CC ist die Größe eines Player Struct
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + 0x39C), &this->m_fPlayerPosY, 4, NULL);		// Pos
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + 0x3A0), &this->m_fPlayerPosZ, 4, NULL);		// Pos
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)(0x839270 + piOffset * 0x4CC + 0x470), &this->m_iPose, 4, NULL);			// Haltung

	return True;
}







































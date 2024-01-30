#pragma once

#include "Utility.h"


class K_GameView
{
public:
	K_GameView();
	~K_GameView();

	void initialize(HANDLE pProcessHandle);
	bool WorldToScreen(K_Vector3D &pkLocal, float& pPointX, float& pPointY);

	HANDLE m_hProcessHandle = nullptr;

	int m_iScreenResolution[2];			// Bildschirm Auflösung z.B. 1920x1080
	int m_iScreenCenter[2];				// Mittelpunkt des Fensters

	float m_fov[2];
	K_Vector3D m_viewAngles;
	K_Vector3D* m_vForward;
	K_Vector3D* m_vRight;
	K_Vector3D* m_vUpward;

protected:
	void readFieldOfView();
	void AngleVectors(K_Vector3D* ppkVec1, K_Vector3D* ppkVec2, K_Vector3D* ppkVec3);
};


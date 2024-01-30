#include "stdafx.h"
#include "KGameView.h"


//
// C-Tor
//
K_GameView::K_GameView()
{
	this->m_vForward = new K_Vector3D();
	this->m_vRight = new K_Vector3D();
	this->m_vUpward = new K_Vector3D();
}

//
// D-Tor
//
K_GameView::~K_GameView()
{
	KS_DELETE(this->m_vForward);
	KS_DELETE(this->m_vRight);
	KS_DELETE(this->m_vUpward);
}






//
// ReadProcessMemory: ScreenResolution wird gelesen und ProcessHandle übergeben
//
void K_GameView::initialize(HANDLE pProcessHandle)
{
	assert(pProcessHandle != nullptr);

	this->m_hProcessHandle = pProcessHandle;
	
	ReadProcessMemory(pProcessHandle, (PVOID)0xD573F34, &this->m_iScreenResolution[0], 4, NULL);
	ReadProcessMemory(pProcessHandle, (PVOID)0xD573F38, &this->m_iScreenResolution[1], 4, NULL);
	this->m_iScreenCenter[X] = this->m_iScreenResolution[X] / 2;
	this->m_iScreenCenter[Y] = this->m_iScreenResolution[Y] / 2;
}





//
// ReadProcessMemory: fov und viewAngles werden gelesen
//
void K_GameView::readFieldOfView()
{
	assert(this->m_hProcessHandle != nullptr);

	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x797610, &m_fov[0], 4, NULL);
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x797614, &m_fov[1], 4, NULL);
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x79B698, &m_viewAngles.x, 4, NULL);
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x79B69C, &m_viewAngles.y, 4, NULL);
	ReadProcessMemory(this->m_hProcessHandle, (PVOID)0x79B6A0, &m_viewAngles.z, 4, NULL);
}








//
// 3D Koordinaten werden in 2D umgerechnet
//
bool K_GameView::WorldToScreen(K_Vector3D &pkLocal, float& pPointX, float& pPointY)
{
	this->readFieldOfView();

	K_Vector3D vTransForm;

	AngleVectors(this->m_vForward, this->m_vRight, this->m_vUpward);

	vTransForm.x = pkLocal.GetKreuzProdukt(*m_vRight);
	vTransForm.y = pkLocal.GetKreuzProdukt(*m_vUpward);
	vTransForm.z = pkLocal.GetKreuzProdukt(*m_vForward);

	if (vTransForm.z < 0.01)
		return False;

	pPointX = m_iScreenCenter[X] + (m_iScreenCenter[X] / vTransForm.z * (1 / m_fov[0])) * vTransForm.x;
	pPointY = m_iScreenCenter[Y] - (m_iScreenCenter[Y] / vTransForm.z * (1 / m_fov[1])) * vTransForm.y;

	return True;
}




void K_GameView::AngleVectors(K_Vector3D* ppkVec1, K_Vector3D* ppkVec2, K_Vector3D* ppkVec3)
{
	float lfAngle;
	float sr, sp, sy, cr, cp, cy, cpi = (3.141f * 2 / 360);

	lfAngle = m_viewAngles.y * cpi;

	sy = sin(lfAngle);
	cy = cos(lfAngle);
	lfAngle = m_viewAngles.x * cpi;

	sp = sin(lfAngle);
	cp = cos(lfAngle);
	lfAngle = m_viewAngles.z * cpi;

	sr = sin(lfAngle);
	cr = cos(lfAngle);

	ppkVec1->x = cp * cy;
	ppkVec1->y = cp * sy;
	ppkVec1->z = -sp;
	
	ppkVec2->x = (-1 * sr * sp * cy + -1 * cr * -sy);
	ppkVec2->y = (-1 * sr * sp * sy + -1 * cr * cy);
	ppkVec2->z = -1 * sr * cp;
	
	ppkVec3->x = (cr * sp * cy + -sr * -sy);
	ppkVec3->y = (cr * sp * sy + -sr * cy);
	ppkVec3->z = cr * cp;
}








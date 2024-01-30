
#pragma once


#include <iostream>
#include <Windows.h>
#include <string>
#include <list>
#include <vector>
#include <sstream>
#include <assert.h>
#include "KVector3D.h"

#define PLAYER_STEHT 2
#define PLAYER_HOCKT 4
#define PLAYER_LIEGT 8

#define X 0
#define Y 1

#define IS_VALID 1
#define KS_DELETE(x) delete x; x = nullptr;

#define True true
#define False false
#define Break break
#define Continue continue

enum AT_SearchPlayerOptions
{
	aFindAll = 0,
	aFindOnlyEnemys
};













/*
class K_Convert
{
public:

	std::string toString(float pfValue);


	//std::string toString(int piValue);

};


std::string K_Convert::toString(float pfValue)
{
	//std::stringstream ss;
	//ss << pfValue;

	std::stringstream lkStreamDistance;
	lkStreamDistance << floorf(pfValue) << " m";

	std::string s;

	s = lkStreamDistance.str().c_str();

	return s;
}


/*
std::string K_Convert::toString(int piValue)
{
	std::stringstream ss;
	ss << piValue << " asd";

	return ss.str().c_str();
}



*/










/*
float g_fScreenX, g_fScreenY;
int g_iResolution[2];
bool g_bGotRes = False;
int g_iScreencenter[2];



float g_fov[2];
K_Vector3D g_viewAngles;



K_Vector3D *g_vForward, *g_vRight, *g_vUpward;
RECT * g_windowRectangle; // stores our window's data
int g_i_ScaleESP = 1;// Draw all ESP's at medium size
*/






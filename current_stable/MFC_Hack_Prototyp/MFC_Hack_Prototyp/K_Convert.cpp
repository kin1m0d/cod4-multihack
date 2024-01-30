/////////////////////////////////////////////////////
//
// Zuletzt bearbeitet am 15.07.2015
//
/////////////////////////////////////////////////////

// Funktioniert nur mit Unicode-Zeichensatz !!!


#include "stdafx.h"
#include <string>
#include <afx.h> // Für den CString
#include "K_Convert.h"


K_Convert::K_Convert()
{

}

K_Convert::~K_Convert()
{

}

///////////////////////////////////////////////////////////////////////////////////////////
// to int

int K_Convert::to_int(std::string pString)						// string to int
{
	return atoi(pString.c_str());
}

int K_Convert::to_int(CString pCString)							// CString to int
{
	return to_int(to_string(pCString));
}


///////////////////////////////////////////////////////////////////////////////////////////
// to double


double K_Convert::to_double(std::string pString)				// string to double
{
	return atof(pString.c_str());
}

double K_Convert::to_double(CString pCString)					// CString to double
{
	return to_double(to_string(pCString));
}


///////////////////////////////////////////////////////////////////////////////////////////
// to char*


char* K_Convert::to_charPtr(std::string pString)				// string to char*
{
	return const_cast<char*>(pString.c_str());
}

char* K_Convert::to_charPtr(CString pCString)					// CString to char*
{
	return to_charPtr(to_string(pCString));
}






///////////////////////////////////////////////////////////////////////////////////////////
// to CString




CString K_Convert::to_CString(std::string pString)				// string to CString
{
	CString temp;
	temp.Format(_T("%S"), pString.c_str());
	return temp;
}

CString K_Convert::to_CString(char *pCharPtr)					// char* to CString
{
	return to_CString(this->to_string(pCharPtr));
}

CString K_Convert::to_CString(TCHAR *pTCHAR)					// TCHAR* to CString
{
	std::string str = this->to_string(pTCHAR);
	return this->to_CString(str);
}

CString K_Convert::to_CString(double pDouble)					// double to CString
{
	return to_CString(this->to_string(pDouble));
}

CString K_Convert::to_CString(float pFloat)						// float to CString
{
	return to_CString(this->to_string(pFloat));
}

CString K_Convert::to_CString(int pInt)							// int to CString
{
	return to_CString(this->to_string(pInt));
}

CString K_Convert::to_CString(size_t pSizeT)					// size_t to CString
{
	return to_CString(this->to_string((int)pSizeT));
}




///////////////////////////////////////////////////////////////////////////////////////////
// to string




std::string K_Convert::to_string(CString pCString)				// CString to string
{
	std::wstring wStr = pCString;
	std::string Str(wStr.begin(), wStr.end());
	return Str;
}

std::string K_Convert::to_string(std::wstring pWstring)			// wstring to string
{
	std::string Str(pWstring.begin(), pWstring.end());
	return Str;
}





std::string K_Convert::to_string(TCHAR *pTCHAR)					// TCHAR* to string
{
	std::wstring tempWStr(&pTCHAR[0]);
	std::string str(tempWStr.begin(), tempWStr.end());
	return str;
}





std::string K_Convert::to_string(char *pCharPtr)				// char* to string
{
	std::string s = pCharPtr;
	return s;
}

std::string K_Convert::to_string(double pDouble)				// double to string
{
	return std::to_string(pDouble);
}

std::string K_Convert::to_string(float pFloat)					// float to string
{
	return std::to_string(pFloat);
}

std::string K_Convert::to_string(int pInt)						// int to string
{
	return std::to_string(pInt);
}

std::string K_Convert::to_string(size_t pSizeT)					// size_t to string
{
	return std::to_string((int) pSizeT);
}



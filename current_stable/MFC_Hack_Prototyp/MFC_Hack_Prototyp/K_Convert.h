/////////////////////////////////////////////////////
//
// Zuletzt bearbeitet am 15.07.2015
//
/////////////////////////////////////////////////////



#pragma once
#include <string>

class K_Convert
{

public:
	K_Convert();
	~K_Convert();


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// to int
	int to_int(std::string pString);						// string	to int
	int to_int(CString pCString);							// CString	to int


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// to double
	double to_double(std::string pString);					// string	to double
	double to_double(CString pCString);						// CString	to double


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// to char*
	char* to_charPtr(std::string pString);					// string	to char*
	char* to_charPtr(CString pCString);						// CString	to char*


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// to CString
	CString to_CString(std::string pString);				// string	to CString
	CString to_CString(TCHAR *pTCHAR);						// tchar	to CString
	CString to_CString(char *pCharPtr);						// char*	to CString
	CString to_CString(double pDouble);						// double	to CString
	CString to_CString(float pFloat);						// float	to CString
	CString to_CString(int pInt);							// int		to CString
	CString to_CString(size_t pSizeT);						// size_t	to CString 

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// to string
	std::string to_string(CString pCString);				// CString	to string
	std::string to_string(std::wstring pWstring);			// wstring	to string
	std::string to_string(TCHAR *pTCHAR);					// tchar*	to string
	std::string to_string(char *pCharPtr);					// char*	to string
	std::string to_string(double pDouble);					// double	to string
	std::string to_string(float pFloat);					// float	to string
	std::string to_string(int pInt);						// int		to string
	std::string to_string(size_t pSizeT);					// size_t	to string




	//C++ string to WINDOWS UNICODE string			// klappt das?????
	std::wstring s2ws(const std::string& s)
	{
		int len;
		int slength = (int) s.length() + 1;
		len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
		wchar_t* buf = new wchar_t[len];
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
		std::wstring r(buf);
		delete[] buf;
		return r;
	}


};
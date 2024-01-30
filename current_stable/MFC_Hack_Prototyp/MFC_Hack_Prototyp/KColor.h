#pragma once






class K_Color
{
public:
	K_Color(CString psColorName, COLORREF pColorRGB);
	~K_Color();

	CString m_sColorName;
	COLORREF m_cColorRGB;
};





/*
K_Color Blue(_T("Blue"), RGB(0, 0, 255));
K_Color DarkBlue(_T("DarkBlue"), RGB(0, 0, 139));
K_Color LightBlue(_T("LightBlue"), RGB(191, 239, 255));
K_Color Green(_T("Green"), RGB(0, 255, 0));
K_Color DarkGreen(_T("DarkGreen"), RGB(0, 100, 0));
K_Color Orange(_T("Orange"), RGB(255, 165, 0));
K_Color Red(_T("Red"), RGB(255, 0, 0));
K_Color DarkRed(_T("DarkRed"), RGB(139, 0, 0));
K_Color Pink(_T("Pink"), RGB(255, 192, 203));
K_Color Violet(_T("Violet"), RGB(238, 130, 238));
K_Color Purple(_T("Purple"), RGB(160, 32, 240));
K_Color Maroon(_T("Maroon"), RGB(176, 48, 167));
K_Color Yellow(_T("Yellow"), RGB(255, 255, 0));
K_Color White(_T("White"), RGB(0, 0, 0));
K_Color Black(_T("Black"), RGB(255, 255, 255));
K_Color Gray(_T("Gray"), RGB(127, 127, 127));

*/
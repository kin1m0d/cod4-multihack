#pragma once

#include "Utility.h"

class K_DrawController
{
public:
	K_DrawController();
	K_DrawController(HDC pDC);
	~K_DrawController();

	void drawFilledRect(int piX, int piY, int piW, int piH, HBRUSH pBrush);
	void drawLine(int piStartX, int piStartY, int piEndX, int piEndY, COLORREF pColorRGB, int piPenWidth = 2);
	void drawBorderBox(int piX, int piY, int piW, int piH, HBRUSH pBrush, int liThickness = 2);
	void drawString(int piX, int piY, const std::string psText, COLORREF pColorRGB);
	void drawPoint(int piX, int piY, HBRUSH pBrush);

protected:

	HDC dc;
};


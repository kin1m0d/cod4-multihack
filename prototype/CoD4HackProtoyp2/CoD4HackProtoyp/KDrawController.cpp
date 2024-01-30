#include "KDrawController.h"


//
// C-tor
//
K_DrawController::K_DrawController()
{
}

K_DrawController::K_DrawController(HDC pDC) : dc(pDC)
{
}



//
// D-tor
//
K_DrawController::~K_DrawController()
{
}



//
// Draw Methoden
//
void K_DrawController::drawLine(int piStartX, int piStartY, int piEndX, int piEndY, COLORREF pColorRGB, int piPenWidth)
{
	HPEN lkPenNew = CreatePen(PS_SOLID, piPenWidth, pColorRGB);		// Neuen Pen erstellen
	HPEN lkPenOld = (HPEN)SelectObject(this->dc, lkPenNew);			// Alten Pen Speichern und neuen setzen
	MoveToEx(this->dc, piStartX, piStartY, NULL);					// Startpunkt setzen
	LineTo(this->dc, piEndX, piEndY);								// Bis zum Endpunkt zeichnen
	DeleteObject(SelectObject(this->dc, lkPenOld));					// Alten Pen wieder benutzen und neuen löschen
}


void K_DrawController::drawBorderBox(int piX, int piY, int piW, int piH, HBRUSH pBrush, int liThickness)
{
	drawFilledRect(piX, piY, piW, liThickness, pBrush);						// Obere horizontale Linie
	drawFilledRect(piX, piY, liThickness, piH, pBrush);						// Linke vertikale Linie
	drawFilledRect(piX + piW, piY, liThickness, piH, pBrush);				// Rechte vertikale Linie
	drawFilledRect(piX, piY + piH, piW + liThickness, liThickness, pBrush);	// Untere horizontale Linie
}


void K_DrawController::drawString(int piX, int piY, const std::string psText, COLORREF pColorRGB)
{
	SetTextAlign(this->dc, NULL | TA_NOUPDATECP);		// Ausrichtung setzen
	SetBkColor(this->dc, RGB(0, 0, 0));					// Background color setzen
	SetBkMode(this->dc, TRANSPARENT);					// Background modus transparent setzen
	SetTextColor(this->dc, pColorRGB);					// Textfarbe setzen
	HFONT lkFont(NULL);									// Font erstellen
	SelectObject(this->dc, lkFont);						// Font auswählen
	TextOutA(this->dc, piX, piY, psText.c_str(), strlen(psText.c_str()));
	DeleteObject(lkFont);
}


void K_DrawController::drawFilledRect(int piX, int piY, int piW, int piH, HBRUSH pBrush)
{
	RECT lkRect = { piX, piY, piX + piW, piY + piH };
	FillRect(this->dc, &lkRect, pBrush);
}


void K_DrawController::drawPoint(int piX, int piY, HBRUSH pBrush)
{
	this->drawFilledRect(piX - 2, piY - 2, 5, 5, pBrush);
}
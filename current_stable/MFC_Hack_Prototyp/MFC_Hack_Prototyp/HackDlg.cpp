
#include "stdafx.h"
#include "MFC_Hack_Prototyp.h"
#include "HackDlg.h"
#include "afxdialogex.h"


#define ON_HOTKEY_SUPERJUMP 100
#define ON_HOTKEY_HIGHSPEED 200
#define ON_HOTKEY_COLLISION 300


static UINT NEAR WM_TEST_MSG{ RegisterWindowMessage(L"LOLOL") };


LRESULT HackDlg::OnMsgTest(WPARAM wParam, LPARAM lParam)
{
	AfxMessageBox(_T("test msg"));
	return 0;
}




#ifdef _DEBUG
	#define new DEBUG_NEW
#endif




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CAboutDlg-Dialogfeld für Anwendungsbefehl "Info"
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();
// Dialogfelddaten
	enum { IDD = IDD_ABOUTBOX };
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
// Implementierung
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD){}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////






/////////////////////////////////////////////////////////////////////////////////////////////////////////////
HackDlg::HackDlg(K_GameProcess pkGameProcess, CWnd* pParent /*=NULL*/) : CDialogEx(HackDlg::IDD, pParent)
{
	this->m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	this->m_pkHack = new K_Hack(pkGameProcess);
	this->m_pkHack->initHack();
	this->m_pkHack->runHackAsThread();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
HackDlg::~HackDlg()
{
	if (this->m_pkHack != nullptr) { KS_DELETE(this->m_pkHack);	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_cSliderSuperJump);
	DDX_Control(pDX, IDC_EDIT_SUPERJUMP, m_cEditSuperJump);
	DDX_Control(pDX, IDC_SLIDER2, m_cSliderHighSpeed);
	DDX_Control(pDX, IDC_EDIT_HIGHSPEED, m_cEditHighSpeed);
	DDX_Control(pDX, IDC_COMBO1, m_cDDLSearchPlayerOption);
	DDX_Control(pDX, IDC_COMBO5, m_cDDLCrosshairLineWidth);
	DDX_Control(pDX, IDC_COMBO4, m_cDDLSnaplineLineWidth);
	DDX_Control(pDX, IDC_COMBO2, m_cDDLESPLineWidth);
	DDX_Control(pDX, IDC_COMBO6, m_cDDLCrosshairSize);
	DDX_Control(pDX, IDC_COMBO3, m_cDDLColorAllies);
	DDX_Control(pDX, IDC_COMBO8, m_cDDLColorEnemys);
	DDX_Control(pDX, IDC_COMBO7, m_cDDLColorCrosshair);
	DDX_Control(pDX, IDC_CHECK8, m_cCheckSuperJump);
	DDX_Control(pDX, IDC_CHECK7, m_cCheckCollision);
	DDX_Control(pDX, IDC_CHECK9, m_cCheckHighSpeed);
	DDX_Control(pDX, IDC_CHECK5, m_cCheckMiniMap);
}

BEGIN_MESSAGE_MAP(HackDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &HackDlg::OnChangeSliderSuperJump)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER2, &HackDlg::OnChangeSliderHighSpeed)
	ON_BN_CLICKED(IDC_CHECK2, &HackDlg::OnClickedSnapline)
	ON_BN_CLICKED(IDC_CHECK3, &HackDlg::OnClickedPlayerInfo)
	ON_BN_CLICKED(IDC_CHECK1, &HackDlg::OnClickedESP)
	ON_BN_CLICKED(IDC_CHECK6, &HackDlg::OnClickedInvincible)
	ON_BN_CLICKED(IDC_CHECK7, &HackDlg::OnClickedCollision)
	ON_BN_CLICKED(IDC_CHECK8, &HackDlg::OnClickedSuperJump)
	ON_BN_CLICKED(IDC_CHECK9, &HackDlg::OnClickedHighSpeed)
	ON_BN_CLICKED(IDC_CHECK4, &HackDlg::OnClickedCrosshair)
	ON_BN_CLICKED(IDC_CHECK5, &HackDlg::OnClickedMiniMap)
	ON_BN_CLICKED(IDC_CHECK10, &HackDlg::OnClickedShowInfo)
	ON_CBN_SELCHANGE(IDC_COMBO4, &HackDlg::OnChangedSnaplineLineWidth)
	ON_CBN_SELCHANGE(IDC_COMBO5, &HackDlg::OnChangedCrosshairLineWidth)
	ON_CBN_SELCHANGE(IDC_COMBO2, &HackDlg::OnChangedESPLineWidth)
	ON_CBN_SELCHANGE(IDC_COMBO6, &HackDlg::OnChangedCrosshairSize)
	ON_CBN_SELCHANGE(IDC_COMBO3, &HackDlg::OnChangedColorAllies)
	ON_CBN_SELCHANGE(IDC_COMBO8, &HackDlg::OnChangedColorEnemys)
	ON_CBN_SELCHANGE(IDC_COMBO7, &HackDlg::OnChangedColorCrosshair)
	ON_CBN_SELCHANGE(IDC_COMBO1, &HackDlg::OnChangeSearchPlayerOptions)
	ON_BN_CLICKED(IDC_BUTTON1, &HackDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &HackDlg::OnClickedStop)
	ON_REGISTERED_MESSAGE(WM_TEST_MSG, &HackDlg::OnMsgTest)
	ON_WM_HOTKEY()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
BOOL HackDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden
	// TODO: Hier zusätzliche Initialisierung einfügen


	//
	// Hotkeys registrieren
	//
	RegisterHotKey(GetSafeHwnd(), ON_HOTKEY_SUPERJUMP, MOD_CONTROL, VK_NUMPAD1);
	RegisterHotKey(GetSafeHwnd(), ON_HOTKEY_COLLISION, MOD_CONTROL, VK_NUMPAD2);
	RegisterHotKey(GetSafeHwnd(), ON_HOTKEY_HIGHSPEED, MOD_CONTROL, VK_NUMPAD3);

	//
	// Farben erstellen
	//
	this->m_coColorList.push_back(K_Color(_T("Blue"), RGB(0, 0, 255)));
	this->m_coColorList.push_back(K_Color(_T("DarkBlue"), RGB(0, 0, 139)));
	this->m_coColorList.push_back(K_Color(_T("LightBlue"), RGB(191, 239, 255)));
	this->m_coColorList.push_back(K_Color(_T("Green"), RGB(0, 255, 0)));
	this->m_coColorList.push_back(K_Color(_T("DarkGreen"), RGB(0, 100, 0)));
	this->m_coColorList.push_back(K_Color(_T("Orange"), RGB(255, 165, 0)));
	this->m_coColorList.push_back(K_Color(_T("Red"), RGB(255, 0, 0)));
	this->m_coColorList.push_back(K_Color(_T("DarkRed"), RGB(139, 0, 0)));
	this->m_coColorList.push_back(K_Color(_T("Pink"), RGB(255, 192, 203)));
	this->m_coColorList.push_back(K_Color(_T("Violet"), RGB(238, 130, 238)));
	this->m_coColorList.push_back(K_Color(_T("Purple"), RGB(160, 32, 240)));
	this->m_coColorList.push_back(K_Color(_T("Maroon"), RGB(176, 48, 167)));
	this->m_coColorList.push_back(K_Color(_T("Yellow"), RGB(255, 255, 0)));
	this->m_coColorList.push_back(K_Color(_T("Black"), RGB(0, 0, 0)));
	this->m_coColorList.push_back(K_Color(_T("White"), RGB(255, 255, 255)));
	this->m_coColorList.push_back(K_Color(_T("Gray"), RGB(127, 127, 127)));


	//
	// Farben in die Dropdown Listen füllen
	//
	for (size_t i = 0; i < this->m_coColorList.size(); i++)
	{
		this->m_cDDLColorAllies.InsertString(i, this->m_coColorList.at(i).m_sColorName);
		this->m_cDDLColorEnemys.InsertString(i, this->m_coColorList.at(i).m_sColorName);
		this->m_cDDLColorCrosshair.InsertString(i, this->m_coColorList.at(i).m_sColorName);
	}


	//
	// Standard einstellungen für die Steuerelemente setzen
	//
	this->m_cSliderSuperJump.SetRange(39, 1000);
	this->m_cSliderHighSpeed.SetRange(190, 1000);
	this->m_cDDLSearchPlayerOption.SetCurSel(0);
	this->m_cDDLCrosshairLineWidth.SetCurSel(0);
	this->m_cDDLCrosshairSize.SetCurSel(0);
	this->m_cDDLESPLineWidth.SetCurSel(0);
	this->m_cDDLSnaplineLineWidth.SetCurSel(0);
	this->m_cDDLColorAllies.SetCurSel(2);
	this->m_cDDLColorEnemys.SetCurSel(5);
	this->m_cDDLColorCrosshair.SetCurSel(12);
	this->OnChangedColorAllies();
	this->OnChangedColorEnemys();
	this->OnChangedColorCrosshair();



	//
	// MiniMap Hack für Release ausschalten
	//
#ifndef DEBUG
	this->m_cCheckMiniMap.EnableWindow(False);
	this->SetWindowTextW(_T("CoD 4 - Multihack"));
#else
	this->SetWindowTextW(_T("CoD 4 - Multihack - Debug"));
#endif



	return TRUE;  // TRUE zurückgeben, wenn der Fokus nicht auf ein Steuerelement gesetzt wird
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // Gerätekontext zum Zeichnen

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Symbol in Clientrechteck zentrieren
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Symbol zeichnen
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////.
HCURSOR HackDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangeSliderSuperJump(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;
	
	int liRange = this->m_cSliderSuperJump.GetPos();
	this->m_cEditSuperJump.SetWindowTextW(cast.to_CString(liRange));
	this->m_pkHack->m_fSuperJumpValue = static_cast<float>(liRange);

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangeSliderHighSpeed(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	*pResult = 0;

	int liRange = this->m_cSliderHighSpeed.GetPos();
	this->m_cEditHighSpeed.SetWindowTextW(cast.to_CString(liRange));
	this->m_pkHack->m_iHighSpeedValue = liRange;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnBnClickedButton1()
{
	// Button1
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedESP()
{
	this->m_pkHack->turnOnOff_ESP();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedSnapline()
{
	this->m_pkHack->turnOnOff_Snapline();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedPlayerInfo()
{
	this->m_pkHack->turnOnOff_HealthDistanceRange();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedInvincible()
{
	this->m_pkHack->turnOnOff_Invincible();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedCollision()
{
	this->m_pkHack->turnOnOff_Collision();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedSuperJump()
{
	this->m_pkHack->turnOnOff_SuperJump();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedHighSpeed()
{
	this->m_pkHack->turnOnOff_HighSpeed();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedCrosshair()
{
	this->m_pkHack->turnOnOff_Crosshair();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedMiniMap()
{
	this->m_pkHack->turnOnOff_MiniMap();
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnCancel()
{
	this->m_pkHack->stopHack();
	CDialogEx::OnCancel();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedStop()
{
	this->m_pkHack->stopHack();
	CDialogEx::OnOK();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangeSearchPlayerOptions()
{
	if (this->m_cDDLSearchPlayerOption.GetCurSel() == 0)
	{
		this->m_pkHack->m_aSearchPlayerOption = AT_SearchPlayerOptions::aFindAll;
	}
	else if (this->m_cDDLSearchPlayerOption.GetCurSel() == 1)
	{
		this->m_pkHack->m_aSearchPlayerOption = AT_SearchPlayerOptions::aFindOnlyTeam1;
	}
	else
	{
		this->m_pkHack->m_aSearchPlayerOption = AT_SearchPlayerOptions::aFindOnlyTeam2;
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedCrosshairLineWidth()
{
	CString lsLineWidth;
	this->m_cDDLCrosshairLineWidth.GetLBText(this->m_cDDLCrosshairLineWidth.GetCurSel(), lsLineWidth);
	this->m_pkHack->m_iCrosshairLineWidth = cast.to_int(lsLineWidth);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedSnaplineLineWidth()
{
	CString lsLineWidth;
	this->m_cDDLSnaplineLineWidth.GetLBText(this->m_cDDLSnaplineLineWidth.GetCurSel(), lsLineWidth);
	this->m_pkHack->m_iSnapLineLineWidth = cast.to_int(lsLineWidth);
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedESPLineWidth()
{
	CString lsLineWidth;
	this->m_cDDLESPLineWidth.GetLBText(this->m_cDDLESPLineWidth.GetCurSel(), lsLineWidth);
	this->m_pkHack->m_iESPLineWidth = cast.to_int(lsLineWidth);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedCrosshairSize()
{
	CString lsLineWidth;
	this->m_cDDLCrosshairSize.GetLBText(this->m_cDDLCrosshairSize.GetCurSel(), lsLineWidth);
	this->m_pkHack->m_iCrosshairSize = cast.to_int(lsLineWidth);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnClickedShowInfo()
{
	this->m_pkHack->turnOnOff_ShowInfo();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedColorAllies()
{
	CString lsColor;
	this->m_cDDLColorAllies.GetLBText(this->m_cDDLColorAllies.GetCurSel(), lsColor);

	for (size_t i = 0; i < this->m_coColorList.size(); i++)
	{
		if (this->m_coColorList.at(i).m_sColorName == lsColor)
		{
			this->m_pkHack->m_ColorAllies = this->m_coColorList.at(i).m_cColorRGB;
			this->m_pkHack->m_BrushAllies = CreateSolidBrush(this->m_coColorList.at(i).m_cColorRGB);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedColorEnemys()
{
	CString lsColor;
	this->m_cDDLColorEnemys.GetLBText(this->m_cDDLColorEnemys.GetCurSel(), lsColor);

	for (size_t i = 0; i < this->m_coColorList.size(); i++)
	{
		if (this->m_coColorList.at(i).m_sColorName == lsColor)
		{
			this->m_pkHack->m_ColorEnemys = this->m_coColorList.at(i).m_cColorRGB;
			this->m_pkHack->m_BrushEnemys = CreateSolidBrush(this->m_coColorList.at(i).m_cColorRGB);
			return;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnChangedColorCrosshair()
{
	CString lsColor;
	this->m_cDDLColorCrosshair.GetLBText(this->m_cDDLColorCrosshair.GetCurSel(), lsColor);

	for (size_t i = 0; i < this->m_coColorList.size(); i++)
	{
		if (this->m_coColorList.at(i).m_sColorName == lsColor)
		{
			this->m_pkHack->m_ColorCrosshair = this->m_coColorList.at(i).m_cColorRGB;
			return;
		}
	}
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void HackDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	/*
	switch (nHotKeyId)
	{
		case ON_HOTKEY_COLLISION:
		{
			this->OnClickedCollision();
			if (this->m_cCheckCollision.GetCheck() == BST_UNCHECKED)	{ this->m_cCheckCollision.SetCheck(True); }
			else														{ this->m_cCheckCollision.SetCheck(False); }
			break;
		}

		case ON_HOTKEY_SUPERJUMP:
		{
			this->OnClickedSuperJump();
			if (this->m_cCheckSuperJump.GetCheck() == BST_UNCHECKED)	{ this->m_cCheckSuperJump.SetCheck(True); }
			else														{ this->m_cCheckSuperJump.SetCheck(False); }
			break;
		}

		case ON_HOTKEY_HIGHSPEED:
		{
			this->OnClickedHighSpeed();
			if (this->m_cCheckHighSpeed.GetCheck() == BST_UNCHECKED)	{ this->m_cCheckHighSpeed.SetCheck(True); }
			else														{ this->m_cCheckHighSpeed.SetCheck(False); }
			break;
		}


	default:
		break;
	}
	*/
}
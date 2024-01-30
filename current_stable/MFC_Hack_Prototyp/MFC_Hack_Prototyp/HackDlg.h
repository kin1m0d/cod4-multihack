
// HackDlg.h: Headerdatei
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#include "K_Convert.h"
#include "KColor.h"

//////////////////////////////////////////////////////////////
// Vom Hack
#include "KGameProcess.h"
#include "KDrawController.h"
#include "KHack.h"
//////////////////////////////////////////////////////////////

#include "resource.h"

// HackDlg-Dialogfeld
class HackDlg : public CDialogEx
{
public:

	//
	// C-Tor / D-Tor
	//
	HackDlg(K_GameProcess pkGameProcess, CWnd* pParent = NULL);	// Standardkonstruktor
	~HackDlg();


	//
	// Dialog Oberfläche
	//
	enum { IDD = IDD_HACK_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV-Unterstützung


protected:

	DECLARE_MESSAGE_MAP()

	//
	// Standard Events
	//
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();


	//
	// Variablen
	//
	HICON m_hIcon;
	K_Hack* m_pkHack = nullptr;
	K_Convert cast;
	std::vector<K_Color> m_coColorList;


public:

	//
	// Events der Steuerelemente
	//
	afx_msg void OnClickedESP();
	afx_msg void OnClickedSnapline();
	afx_msg void OnClickedPlayerInfo();
	afx_msg void OnClickedHighSpeed();
	afx_msg void OnClickedCrosshair();
	afx_msg void OnClickedMiniMap();
	afx_msg void OnClickedInvincible();
	afx_msg void OnClickedCollision();
	afx_msg void OnClickedSuperJump();
	afx_msg void OnClickedShowInfo();
	afx_msg void OnChangeSearchPlayerOptions();
	afx_msg void OnChangedESPLineWidth();
	afx_msg void OnChangedCrosshairSize();
	afx_msg void OnChangedSnaplineLineWidth();
	afx_msg void OnChangeSliderSuperJump(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangeSliderHighSpeed(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnChangedCrosshairLineWidth();
	afx_msg void OnChangedColorAllies();
	afx_msg void OnChangedColorEnemys();
	afx_msg void OnChangedColorCrosshair();
	afx_msg void OnClickedStop();
	afx_msg void OnCancel();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnBnClickedButton1();
	afx_msg LRESULT OnMsgTest(WPARAM wParam, LPARAM lParam);

	//
	// Variablen der Steuerelemente
	//
	CSliderCtrl m_cSliderSuperJump;
	CSliderCtrl m_cSliderHighSpeed;
	CEdit m_cEditHighSpeed;
	CEdit m_cEditSuperJump;
	CComboBox m_cDDLSearchPlayerOption;
	CComboBox m_cDDLCrosshairLineWidth;
	CComboBox m_cDDLSnaplineLineWidth;
	CComboBox m_cDDLESPLineWidth;
	CComboBox m_cDDLCrosshairSize;
	CComboBox m_cDDLColorAllies;
	CComboBox m_cDDLColorEnemys;
	CComboBox m_cDDLColorCrosshair;
	CButton m_cCheckSuperJump;
	CButton m_cCheckCollision;
	CButton m_cCheckHighSpeed;
	CButton m_cCheckMiniMap;
};

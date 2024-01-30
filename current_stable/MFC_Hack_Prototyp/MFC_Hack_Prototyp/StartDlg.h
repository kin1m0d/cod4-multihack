#pragma once

#include "afxwin.h"
#include "afxcmn.h"
#include "KGameProcess.h"
#include "K_Convert.h"



class StartDlg : public CDialogEx
{
	//DECLARE_DYNAMIC(StartDlg)
public:
	StartDlg(CWnd* pParent = NULL);		// Standardkonstruktor
	virtual ~StartDlg();				// Destruktor

	void StartDlg::OnRefresh();

// Dialogfelddaten
	enum { IDD = IDD_START_DIALOG };

protected:
	HICON m_hIcon;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV-Unterstützung
	BOOL OnInitDialog();

	K_Convert cast;
	K_GameProcess* m_pkGameProcess = nullptr;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedStartHack();
	afx_msg void OnClickedRefresh();
	afx_msg void OnClickedExit();

	CButton m_cButtonStart;
	CListCtrl m_cListe;
};

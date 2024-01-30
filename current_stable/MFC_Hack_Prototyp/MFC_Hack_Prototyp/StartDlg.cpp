// StartDlg.cpp: Implementierungsdatei
//

#include "stdafx.h"
#include "MFC_Hack_Prototyp.h"
#include "StartDlg.h"
#include "afxdialogex.h"


#include "HackDlg.h"


// StartDlg-Dialogfeld

//IMPLEMENT_DYNAMIC(StartDlg, CDialogEx)

//
// C-tor
//
StartDlg::StartDlg(CWnd* pParent /*=NULL*/)	: CDialogEx(StartDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	this->m_pkGameProcess = new K_GameProcess("Call of Duty 4");

//#ifndef DEBUG
//	this->SetWindowTextW(_T("CoD 4 - Multihack"));
//#else
//	this->SetWindowTextW(_T("CoD 4 - Multihack - Debug"));
//#endif

}

//
// D-tor
//
StartDlg::~StartDlg()
{
	if (this->m_pkGameProcess != nullptr)
	{
		KS_DELETE(this->m_pkGameProcess);
	}
}

void StartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_cListe);
	DDX_Control(pDX, IDC_BUTTON1, m_cButtonStart);
}

BEGIN_MESSAGE_MAP(StartDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &StartDlg::OnClickedStartHack)
	ON_BN_CLICKED(IDC_BUTTON2, &StartDlg::OnClickedRefresh)
	ON_BN_CLICKED(IDC_BUTTON5, &StartDlg::OnClickedExit)
END_MESSAGE_MAP()

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StartDlg::OnRefresh()
{
	this->m_cButtonStart.EnableWindow(False);
	this->m_pkGameProcess->refresh();
	this->m_cListe.DeleteAllItems();

	int i = 0;
	bool lbCheckPID = this->m_pkGameProcess->isValidProcessID();
	bool lbCheckWnd = this->m_pkGameProcess->isValidWindowHandle();
	bool lbAttachTo = this->m_pkGameProcess->attachToGameProcess();

	CString lsMsg1 = _T("CheckProcessID = ");
	CString lsMsg3 = _T("CheckWindowHandle = ");
	CString lsMsg2 = _T("AttachToGameProcess = ");

	lsMsg1 += lbCheckPID ? _T("success") : _T("error");
	lsMsg3 += lbCheckWnd ? _T("success") : _T("error");
	lsMsg2 += lbAttachTo ? _T("success") : _T("error");

	this->m_cListe.InsertItem(++i, _T("Multihack v1.0 - Call of Duty 4 (v1.7.568)"));
	this->m_cListe.InsertItem(++i, _T("------------------------------------------------------"));
	this->m_cListe.InsertItem(++i, lsMsg1);
	this->m_cListe.InsertItem(++i, lsMsg3);
	this->m_cListe.InsertItem(++i, lsMsg2);
	this->m_cListe.InsertItem(++i, _T("------------------------------------------------------"));

	if (lbCheckPID && lbAttachTo && lbCheckWnd)
	{
		this->m_cListe.InsertItem(++i, _T("Hack is ready!"));
		this->m_cButtonStart.EnableWindow(True);
		return;
	}


	if (!lbCheckPID) { this->m_cListe.InsertItem(++i, _T("Invalid process id!")); }
	if (!lbCheckWnd) { this->m_cListe.InsertItem(++i, _T("Invalid window handle!")); }
	if (!lbAttachTo) { this->m_cListe.InsertItem(++i, _T("Could not open process!")); }

	this->m_cListe.InsertItem(++i, _T("------------------------------------------------------"));
	this->m_cListe.InsertItem(++i, _T("Press refresh to try again"));
	this->m_cButtonStart.EnableWindow(False);

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void StartDlg::OnClickedStartHack()
{
	this->OnRefresh();
	ShowWindow(SW_HIDE);				// Fenster verstecken

	HackDlg dlg(*this->m_pkGameProcess);
	INT_PTR nResponse = dlg.DoModal();

	if (nResponse == IDOK)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "OK" zu steuern
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Fügen Sie hier Code ein, um das Schließen des
		//  Dialogfelds über "Abbrechen" zu steuern
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "Warnung: Fehler bei der Dialogfelderstellung, unerwartetes Beenden der Anwendung.\n");
		TRACE(traceAppMsg, 0, "Warnung: Wenn Sie MFC-Steuerelemente im Dialogfeld verwenden, ist #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS nicht möglich.\n");
	}
	
	ShowWindow(SW_SHOW);				// Fenster zeigen
	this->OnRefresh();
}


BOOL StartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Großes Symbol verwenden
	SetIcon(m_hIcon, FALSE);		// Kleines Symbol verwenden

	this->OnRefresh();

	return TRUE;
}

void StartDlg::OnClickedRefresh()
{
	this->OnRefresh();
}

void StartDlg::OnClickedExit()
{
	CDialogEx::OnCancel();
}

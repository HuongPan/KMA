
// RC4Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "RC4.h"
#include "RC4Dlg.h"
#include "afxdialogex.h"
#include <Windows.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif
DWORD WINAPI doRC4(LPVOID lpParameter);

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CRC4Dlg dialog



CRC4Dlg::CRC4Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RC4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRC4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, btn_start);
	DDX_Control(pDX, IDC_EDIT_KEY, key);
	DDX_Control(pDX, IDC_EDIT_PLAINTEXT, plaintext);
	DDX_Control(pDX, IDC_EDIT_CIPHERTEXT, ciphertext);
	DDX_Control(pDX, IDC_EDIT_HEXBTN, hex_value);
}

BEGIN_MESSAGE_MAP(CRC4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT_KEY, &CRC4Dlg::OnEnChangeEditKey)
	ON_BN_CLICKED(IDC_BUTTON_START, &CRC4Dlg::OnBnClickedButtonStart)
	ON_EN_CHANGE(IDC_EDIT_HEXBTN, &CRC4Dlg::OnEnChangeEditHexbtn)
END_MESSAGE_MAP()


// CRC4Dlg message handlers

BOOL CRC4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CRC4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRC4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRC4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CRC4Dlg::OnEnChangeEditKey()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CRC4Dlg::OnBnClickedButtonStart()
{
	// TODO: Add your control notification handler code here
	CString str_key;
	CString str_plaintext;
	key.GetWindowText(str_key);
	plaintext.GetWindowText(str_plaintext);

	int len_key = str_key.GetLength();
	int len_plaintext = str_plaintext.GetLength();

	if (len_key == 0 || len_plaintext == 0) {
		MessageBox(L"Please fill key and plaintext box!", L"Error");
	}
		
	int status = btn_start.GetWindowTextLength();

	btn_start.EnableWindow(FALSE);
	if (status == wcslen(L"START")) {
		hConnThread = CreateThread(NULL, 0, doRC4, (LPVOID)this, 0, NULL);
		if (hConnThread == NULL) {
			MessageBox(L"Cannot handle", L"ERROR");
			return;
		}
		else {
			btn_start.SetWindowText(L"RESET");
		}
		btn_start.EnableWindow(TRUE);
		return;

	}

	if (hConnThread != NULL && TerminateThread(hConnThread, NULL)) {
		btn_start.SetWindowText(L"START");
		key.SetWindowTextW(L"");
		plaintext.SetWindowTextW(L"");
		ciphertext.SetWindowTextW(L"");
	}
	btn_start.EnableWindow(TRUE);

}


void CRC4Dlg::OnEnChangeEditHexbtn()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}

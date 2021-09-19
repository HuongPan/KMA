
// RC4Dlg.h : header file
//

#pragma once


// CRC4Dlg dialog
class CRC4Dlg : public CDialogEx
{
// Construction
public:
	CRC4Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RC4_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HANDLE hConnThread ;
	CButton btn_start;
	CEdit key;
	CEdit plaintext;
	CEdit ciphertext;
	CEdit hex_value;
	afx_msg void OnEnChangeEditKey();
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnEnChangeEditHexbtn();
};

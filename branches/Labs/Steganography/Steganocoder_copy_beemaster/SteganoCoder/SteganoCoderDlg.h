// SteganoCoderDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CSteganoCoderDlg dialog
class CSteganoCoderDlg : public CDialog
{
// Construction
public:
	CSteganoCoderDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_STEGANOCODER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton4();
	CEdit OpenBMPEdit;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	CEdit OpenSaveTXTEdit;
	CEdit SaveBMPEdit;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	CButton EncDecRadio;
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	CComboBox chckMthdCombo;
	afx_msg void OnCbnSelchangeCombo1();
	CEdit KeyEdit;
	CComboBox chckBitCombo;
};

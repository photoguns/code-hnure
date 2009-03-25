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
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSaveTXT();
	afx_msg void OnBnClickedButtonProceed();
	afx_msg void OnBnClickedButtonSaveBMP();
	afx_msg void OnBnClickedButtonOpenBMP();
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnCbnSelchangeCombo1();
	CEdit OpenBMPEdit;
	CEdit OpenSaveTXTEdit;
	CEdit SaveBMPEdit;
	CEdit KeyEdit;
	CButton EncDecRadio;
	CComboBox chckMthdCombo;
};

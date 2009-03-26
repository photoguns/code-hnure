// SteganoCoderDlg.cpp : implementation InBMPFile
//

#include "stdafx.h"
#include "SteganoCoder.h"
#include "SteganoCoderDlg.h"
#include "Stegano.class\stegano.h"

const int MaxPath=260;
const short KeyLen=10;
enum mode{LSBm,PRIm,PRSm,BLOCKm};

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CSteganoCoderDlg dialog

CSteganoCoderDlg::CSteganoCoderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSteganoCoderDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSteganoCoderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, OpenBMPEdit);
	DDX_Control(pDX, IDC_EDIT2, OpenSaveTXTEdit);
	DDX_Control(pDX, IDC_EDIT3, SaveBMPEdit);
	DDX_Control(pDX, IDC_RADIO1, EncDecRadio);
	DDX_Control(pDX, IDC_COMBO1, chckMthdCombo);
	DDX_Control(pDX, IDC_EDIT5, KeyEdit);
}

BEGIN_MESSAGE_MAP(CSteganoCoderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON4, &CSteganoCoderDlg::OnBnClickedButtonOpenBMP)
	ON_BN_CLICKED(IDC_BUTTON1, &CSteganoCoderDlg::OnBnClickedButtonSaveTXT)
	ON_BN_CLICKED(IDC_BUTTON2, &CSteganoCoderDlg::OnBnClickedButtonSaveBMP)
	ON_BN_CLICKED(IDC_BUTTON3, &CSteganoCoderDlg::OnBnClickedButtonProceed)
	ON_BN_CLICKED(IDC_RADIO2, &CSteganoCoderDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CSteganoCoderDlg::OnBnClickedRadio1)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CSteganoCoderDlg::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CSteganoCoderDlg message handlers

BOOL CSteganoCoderDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	EncDecRadio.SetCheck(1);
	chckMthdCombo.SetCurSel(0);
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSteganoCoderDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSteganoCoderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSteganoCoderDlg::OnBnClickedButtonOpenBMP()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  OpenBMPEdit.SetWindowText(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButtonSaveTXT()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  OpenSaveTXTEdit.SetWindowText(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButtonSaveBMP()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  SaveBMPEdit.SetWindowText(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButtonProceed()
{

	Stegano *sys=0;
	char fnames[3][MaxPath];

	int mod=chckMthdCombo.GetCurSel();
	if(EncDecRadio.GetCheck()) {


		if(mod==LSBm) {	
			sys = new LSB();
		}
		else if(mod==PRIm) {
			sys = new PRI();
		}
		else if(mod==PRSm) {
			sys = new PRS();
		}
		else if(mod==BLOCKm) {
			sys = new BLOCK();
		}
		OpenBMPEdit.GetWindowText(fnames[0],MaxPath);
		OpenSaveTXTEdit.GetWindowText(fnames[1],MaxPath);
		SaveBMPEdit.GetWindowText(fnames[2],MaxPath);
		char key[KeyLen];
		KeyEdit.GetWindowText(key,KeyLen);
		sys->encrypt(fnames[0],fnames[1],fnames[2],key);// here must be try-catch block
		SaveBMPEdit.SetWindowText("Done!!!");

	}
	else {

		if(mod==LSBm) {
			sys = new LSB();
		}
		else if(mod==PRIm) {
			sys = new PRI();
		}
		else if(mod==PRSm) {
			sys = new PRS();
		}
		else if(mod==BLOCKm) {
			sys = new BLOCK();
		}
		OpenBMPEdit.GetWindowText(fnames[0],MaxPath);
		OpenSaveTXTEdit.GetWindowText(fnames[1],MaxPath);
		char key[KeyLen];
		KeyEdit.GetWindowText(key,KeyLen);
		sys->decrypt(fnames[0],fnames[1],key); // here must be try-catch block
		OpenSaveTXTEdit.SetWindowText("Done!!!");
	}
	delete sys;
}

void CSteganoCoderDlg::OnBnClickedRadio2()
{
	OpenBMPEdit.SetWindowText("");
	OpenSaveTXTEdit.SetWindowText("");
	SaveBMPEdit.SetWindowText("");
	SaveBMPEdit.ShowWindow(SW_HIDE);

	CWnd *p=GetDlgItem(IDC_STATIC1);
	p->SetWindowText("Decoding");
	p=GetDlgItem(IDC_BUTTON1);
	p->SetWindowText("TXT To Save");
	p=GetDlgItem(IDC_BUTTON2);
	p->ShowWindow(SW_HIDE);
}

void CSteganoCoderDlg::OnBnClickedRadio1()
{
	OpenBMPEdit.SetWindowText("");
	OpenSaveTXTEdit.SetWindowText("");
	SaveBMPEdit.SetWindowText("");
	SaveBMPEdit.ShowWindow(SW_SHOW);

	CWnd *p=GetDlgItem(IDC_STATIC1);
	p->SetWindowText("Encoding");
	p=GetDlgItem(IDC_BUTTON1);
	p->SetWindowText("Open TXT");
	p=GetDlgItem(IDC_BUTTON2);
	p->ShowWindow(SW_SHOW);
}

void CSteganoCoderDlg::OnCbnSelchangeCombo1()
{
	CWnd *p=GetDlgItem(IDC_STATIC3);
	if (chckMthdCombo.GetCurSel()>=1) {
		p->ShowWindow(SW_SHOW);
		KeyEdit.ShowWindow(SW_SHOW);
	}
	else {
		p->ShowWindow(SW_HIDE);
		KeyEdit.ShowWindow(SW_HIDE);
	}
}
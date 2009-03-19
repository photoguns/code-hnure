// SteganoCoderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SteganoCoder.h"
#include "SteganoCoderDlg.h"
#include <fstream>

using namespace std;

#define MAX_PATH 260
#define BLOCK_LEN 10

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
	DDX_Control(pDX, IDC_COMBO2, chckBitCombo);
}

BEGIN_MESSAGE_MAP(CSteganoCoderDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON4, &CSteganoCoderDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CSteganoCoderDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CSteganoCoderDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CSteganoCoderDlg::OnBnClickedButton3)
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
	chckBitCombo.SetCurSel(0);
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



void CSteganoCoderDlg::OnBnClickedButton4()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  OpenBMPEdit.SetWindowTextA(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButton1()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  OpenSaveTXTEdit.SetWindowTextA(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButton2()
{
	CFileDialog fd(true);
          if (fd.DoModal()==IDOK) 
			  SaveBMPEdit.SetWindowTextA(fd.m_ofn.lpstrFile);
}

void CSteganoCoderDlg::OnBnClickedButton3()
{
	
	BITMAPFILEHEADER sbfh;
	BITMAPINFOHEADER sbih;
	fstream file, filem, fileo, filet;
	int offset=0, i=0, j=0, fsize=0, mod, width=0, t=0, 
		height=0, capasity=0, seed=0, mask=0, c=0, pm[BLOCK_LEN];
	char buf=0, key[10], lett=0, fname[MAX_PATH];
	unsigned char msg, bf,smsg[BLOCK_LEN],temp[BLOCK_LEN];
	bool match=0;

	if(EncDecRadio.GetCheck()==1) {

		OpenBMPEdit.GetWindowTextA((fname),MAX_PATH);
		file.open(fname,ios::in | ios::binary);
		if(!file) {
			OpenBMPEdit.SetWindowTextA("Error file opening!!!");
			return;
		}

		OpenSaveTXTEdit.GetWindowTextA(fname,MAX_PATH);
		filem.open(fname,ios::in | ios::binary);
		if(!filem) {
			OpenSaveTXTEdit.SetWindowTextA("Error file opening!!!");
			return;
		}

		SaveBMPEdit.GetWindowTextA(fname,MAX_PATH);
		fileo.open(fname,ios::out | ios::binary);


		file.read((char*)&sbfh,sizeof(BITMAPFILEHEADER));
		if(sbfh.bfType!='MB'){
			OpenBMPEdit.SetWindowTextA("This is not a BMP!!!");
			return;
		}
		file.read((char*)&sbih,sizeof(BITMAPINFOHEADER));

		offset=sbfh.bfOffBits;
		width=sbih.biWidth;
		height=(sbih.biHeight>0) ? sbih.biHeight : -sbih.biHeight;

		capasity=(width*height*3/8)-offset-32;

		filem.seekg(0,ios::end);
		fsize=filem.tellg();
		filem.seekg(0,ios::beg);
		
		file.seekg(0);
		for(i=0;i<offset;i++)
			fileo.put(file.get());

		if(capasity<fsize*8) {
			OpenSaveTXTEdit.SetWindowTextA("Too large txt!!!");
			return;
		}
		
		int tmp=fsize;
		for(i=0;i<32;i++) {
			file.read((char *)&bf,1);
			if(tmp%2)
				bf |= 1;
			else bf &= 0xFE;
			fileo.put(bf);
			tmp/=2;
		}

		while(!file.eof()){
			file.get(buf);
			fileo.put(buf);
		}
		file.clear();
		file.seekg(offset+32);
		fileo.seekg(offset+32);
		mask=1<<chckBitCombo.GetCurSel();
		t=file.tellg();

		if(chckMthdCombo.GetCurSel()==0) {
			while(!filem.eof()) {
				filem.get((char &)msg);
				for(i=0;i<8;i++) {
					file.get((char &)bf);
					if(msg%2)
						bf |= mask;
					else bf &= ~mask;
					fileo.put(bf);
					t=fileo.tellg();
					msg/=2;
				}
			}
		}

		else if(chckMthdCombo.GetCurSel()==1){
			KeyEdit.GetWindowTextA(key,10);
			for(j=0;j<strlen(key);j++)
				seed+=key[j];
			srand(seed);
			mod=capasity/fsize/8;
			while(!filem.eof()) {
				filem.get((char &)msg);
				for(i=0;i<8;i++) {
					file.read((char *)&bf,1);
					if(msg%2)
						bf |= mask;
					else bf &= ~mask;
					fileo.put(bf);
					int ofs=(rand()%mod);
					file.seekg(ofs,ios::cur);
					fileo.seekg(ofs,ios::cur);
					msg/=2;
				}
			}
		}

		else if(chckMthdCombo.GetCurSel()==2){
			KeyEdit.GetWindowTextA(key,10);
			for(j=0;j<strlen(key);j++)
				seed+=key[j];
			srand(seed);

			pm[0]=rand()%BLOCK_LEN;
			for(i=1;i<BLOCK_LEN;i++) {
				match=0;
				t=rand()%BLOCK_LEN;
				for(j=0;j<i;j++) {
					if(pm[j]==t) {
						match=1;break;
					}
				}
				if(match) i--;
				else pm[i]=t;
			}


			while(!filem.eof()) {
				ZeroMemory(temp,sizeof(temp));
				filem.read((char *)temp,sizeof(temp));
				for(j=0;j<BLOCK_LEN;j++)
					smsg[j]=temp[pm[j]];
				for(c=0;c<BLOCK_LEN;c++) {
					for(i=0;i<8;i++) {
						file.read((char *)&bf,1);
						if(smsg[c]%2)
							bf |= mask;
						else bf &= ~mask;
						fileo.put(bf);
						smsg[c]/=2;
					}
				}
			}
		}

		fileo.close(); file.close(); filem.close();
		SaveBMPEdit.SetWindowTextA("Done!");

	}
	else {

		OpenBMPEdit.GetWindowTextA(fname,MAX_PATH);
		fileo.open(fname,ios::in | ios::binary);
		if(!fileo) {
			OpenBMPEdit.SetWindowTextA("Error file opening!!!");
			return;
		}

		OpenSaveTXTEdit.GetWindowTextA(fname,MAX_PATH);
		filet.open(fname,ios::out | ios::binary);

		fileo.read((char*)&sbfh,sizeof(BITMAPFILEHEADER));
		if(sbfh.bfType!='MB'){
			OpenBMPEdit.SetWindowTextA("This is not a BMP!!!");
			return;
		}
		fileo.read((char*)&sbih,sizeof(BITMAPINFOHEADER));

		offset=sbfh.bfOffBits;
		width=sbih.biWidth;
		height=sbih.biHeight;

		capasity=(width*height*3/8)-offset-32;

		fileo.seekg(offset);
		for(i=0;i<32;i++) {
			fileo.get(buf);
			fsize+=((abs(buf%2))*(1<<i));
		}

		if(chckMthdCombo.GetCurSel()==0) {
			int tmp=fsize*8;
			while(!fileo.eof() && tmp) {
				fileo.get((char &)bf);
				for(i=0;i<chckBitCombo.GetCurSel();i++)
					bf/=2;
				lett+=((abs(bf%2))*(1<<c));
				if(c!=7)
					c++;
				else {
					c=0;filet<<lett;lett=0;
				}
				tmp--;
			}
		}
		else if(chckMthdCombo.GetCurSel()==1){
			KeyEdit.GetWindowTextA(key,10);
			for(int j=0;j<strlen(key);j++)
				seed+=key[j];
			srand(seed);
			mod=capasity/fsize/8;
			c=0;
			for(int j=0;j<fsize*8;j++) {
				fileo.get((char &)bf);
				for(i=0;i<chckBitCombo.GetCurSel();i++)
					bf/=2;
				lett+=((abs(bf%2))*(1<<c));
				fileo.seekg(rand()%mod, ios::cur);
				if(c!=7)
					c++; 
				else {
					c=0;filet<<lett;lett=0;
				}
			}
			
		}
		else if(chckMthdCombo.GetCurSel()==2){

			KeyEdit.GetWindowTextA(key,10);
			for(j=0;j<strlen(key);j++)
				seed+=key[j];
			srand(seed);

			pm[0]=rand()%BLOCK_LEN;
			for(i=1;i<BLOCK_LEN;i++) {
				match=0;
				t=rand()%BLOCK_LEN;
				for(j=0;j<i;j++) {
					if(pm[j]==t) {
						match=1;break;
					}
				}
				if(match) i--;
				else pm[i]=t;
			}

			int tmp=fsize;
			ZeroMemory(smsg,sizeof(smsg));
			ZeroMemory(temp,sizeof(temp));
			while(!fileo.eof() && tmp>0) {
				for(i=0;i<BLOCK_LEN;i++) {
					for(j=0;j<8;j++) {
						fileo.get((char &)bf);
						for(c=0;c<chckBitCombo.GetCurSel();c++)
							bf/=2;
						smsg[i]+=((abs(bf%2))*(1<<j));
					}
				}
				for(i=0;i<BLOCK_LEN;i++)
					for(j=0;j<BLOCK_LEN;j++) {
						if(pm[j]==i) {
							temp[i]=smsg[j];
							break;
						}
					}

				filet.write((char*)temp,sizeof(temp));
				ZeroMemory(smsg,sizeof(smsg));
				ZeroMemory(temp,sizeof(temp));
				tmp-=BLOCK_LEN;
			}


			
		}
		fileo.close();
		OpenSaveTXTEdit.SetWindowTextA("Done!");

	}
}

void CSteganoCoderDlg::OnBnClickedRadio2()
{
	OpenBMPEdit.SetWindowTextA("");
	OpenSaveTXTEdit.SetWindowTextA("");
	SaveBMPEdit.SetWindowTextA("");
	SaveBMPEdit.ShowWindow(SW_HIDE);

	CWnd *p=GetDlgItem(IDC_STATIC1);
	p->SetWindowTextA("Decoding");
	p=GetDlgItem(IDC_BUTTON1);
	p->SetWindowTextA("TXT To Save");
	p=GetDlgItem(IDC_BUTTON2);
	p->ShowWindow(SW_HIDE);
}

void CSteganoCoderDlg::OnBnClickedRadio1()
{
	OpenBMPEdit.SetWindowTextA("");
	OpenSaveTXTEdit.SetWindowTextA("");
	SaveBMPEdit.SetWindowTextA("");
	SaveBMPEdit.ShowWindow(SW_SHOW);

	CWnd *p=GetDlgItem(IDC_STATIC1);
	p->SetWindowTextA("Encoding");
	p=GetDlgItem(IDC_BUTTON1);
	p->SetWindowTextA("Open TXT");
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
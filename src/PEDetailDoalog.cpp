/******************************************************************* 
 *  File Nmae  : PEDetailDoalog.h
 *  Description: Detail dialog box of PE structure class 
 *   
 *  Version	:1.0 
 *  author	:Zephyr 
 *  Date	:2017-05-30 
 ******************************************************************/
//

#include "stdafx.h"
#include "PEParseTool.h"
#include "PEDetailDoalog.h"
#include "afxdialogex.h"


// PEDetailDoalog

IMPLEMENT_DYNAMIC(PEDetailDoalog, CDialog)

PEDetailDoalog::PEDetailDoalog(CWnd* pParent /*=NULL*/)
	: CDialog(PEDetailDoalog::IDD, pParent)
{

}

PEDetailDoalog::~PEDetailDoalog()
{
}

void PEDetailDoalog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DETAIL_LIST, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(PEDetailDoalog, CDialog)
	ON_WM_PAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// PEDetailDoalog


void PEDetailDoalog::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// CDialog::OnPaint()
	SetWindowTextW(m_windowTitle);
}

BOOL PEDetailDoalog::SetWindowTitle(CString *string)
{
	if(NULL == string){
		return FALSE;
	}
	m_windowTitle = *string;

	return TRUE;
}

void PEDetailDoalog::OnInitCtrlList()
{
	CRect rect;
	GetClientRect(&rect);

	m_ListCtrl.SetTextColor(RGB(50,153,255));
	m_ListCtrl.ModifyStyle(0,LVS_REPORT|LVS_SHOWSELALWAYS);
	m_ListCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES |LVS_OWNERDRAWFIXED);

	m_ListCtrl.InsertColumn(0,L"LVCFMT1",LVCFMT_LEFT,rect.Width()/3);
	m_ListCtrl.InsertColumn(1,L"ֵ(HEX)",LVCFMT_LEFT,rect.Width()/6);
	m_ListCtrl.InsertColumn(2,L"LVCFMT2",LVCFMT_LEFT,rect.Width()/6);
	m_ListCtrl.InsertColumn(3,L"LVCMT3",LVCFMT_LEFT,rect.Width()/2);

	return;
}

void PEDetailDoalog::AddToCtrlList(CString* strName,CString* strValue, CString* strSubSt, CString* strContent)
{
	int index = m_ListCtrl.GetItemCount();
	m_ListCtrl.InsertItem(index, *strName);
	m_ListCtrl.SetItemText(index, 1, *strValue);
	m_ListCtrl.SetItemText(index, 2, *strSubSt);
	m_ListCtrl.SetItemText(index, 3, *strContent);

	return;
}

void PEDetailDoalog::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	
	if (m_ListCtrl.GetSafeHwnd())
	{
		CRect   rect; 
		GetClientRect(&rect); 
		int nWidth	= rect.Width(); 
		int nheight	= rect.Height(); 

		m_ListCtrl.SetWindowPos(this, rect.left, rect.top, nWidth, nheight, \
			SWP_SHOWWINDOW|SWP_NOZORDER);
	}

	return;
}

/******************************************************************* 
 *  File Nmae  : PEDetailDoalog.h
 *  Description: Detail dialog box of PE structure class implement
 *   
 *  Version	:1.0 
 *  author	:Zephyr 
 *  Date	:2017-05-30 
 ******************************************************************/
#pragma once

// PEDetailDoalog

class PEDetailDoalog : public CDialog
{
	DECLARE_DYNAMIC(PEDetailDoalog)

public:
	PEDetailDoalog(CWnd* pParent = NULL);
	virtual ~PEDetailDoalog();

	enum { IDD = IDD_PEDETAILDOALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);

	DECLARE_MESSAGE_MAP()

public:
	BOOL SetWindowTitle(CString *string);
	void AddToCtrlList(CString *strName, CString *strValue, CString *strSubSt, CString *strContent);
	void OnInitCtrlList();
	CListCtrl m_ListCtrl;
	afx_msg void OnPaint();
private:
	CString m_windowTitle;
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

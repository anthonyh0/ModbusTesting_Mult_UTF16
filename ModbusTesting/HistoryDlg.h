#pragma once
#include "afxcmn.h"
#include <vector>
#include "PublicFunDef.h"
#include "INI.h"
#include "Resource.h"
#include "afxwin.h"
using namespace std;

// HistoryDlg 对话框

class HistoryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HistoryDlg)

public:
	HistoryDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~HistoryDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_HISTORY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listControl_history;
	virtual BOOL OnInitDialog();

	//std::map<CString, CString> mapHistory;
	std::map<CString, CString>::iterator iter;
	CButton m_button_clear;
	afx_msg void updateRecordList();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnNMDblclkListHistory(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClose();

private:
	CWnd *m_pParentWnd;;
};

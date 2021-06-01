// HistoryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HistoryDlg.h"
#include "afxdialogex.h"
#include "ModbusTesting.h"
#include "ModbusTestingDlg.h"
// HistoryDlg 对话框

IMPLEMENT_DYNAMIC(HistoryDlg, CDialogEx)


HistoryDlg::HistoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(HistoryDlg::IDD, pParent)
{

}

HistoryDlg::~HistoryDlg()
{
}

void HistoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_HISTORY, m_listControl_history);
	DDX_Control(pDX, IDC_BUTTON_CLEAR, m_button_clear);
}


BEGIN_MESSAGE_MAP(HistoryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &HistoryDlg::OnBnClickedButtonClear)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_HISTORY, &HistoryDlg::OnNMDblclkListHistory)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// HistoryDlg 消息处理程序


BOOL HistoryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	m_listControl_history.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_listControl_history.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	m_listControl_history.SetTextColor(RGB(255, 0, 0));                  //显示字体的颜色
	DWORD dwStyle = m_listControl_history.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SHOWSELALWAYS;
	m_listControl_history.SetExtendedStyle(dwStyle);
	m_listControl_history.SetBkColor(RGB(240, 247, 233));             //选中此列是的颜色
	m_listControl_history.SetTextBkColor(RGB(240, 247, 233));

	m_listControl_history.InsertColumn(0, _T("编号"), LVCFMT_LEFT, 50, 0);
	m_listControl_history.InsertColumn(1, _T("时间"), LVCFMT_LEFT, 120, 1);
	m_listControl_history.InsertColumn(2, _T("记录"), LVCFMT_LEFT, 500, 2);
	updateRecordList();



	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void HistoryDlg::updateRecordList()
{
	m_listControl_history.DeleteAllItems();
	g_CINI.getIniRecord();
	int nCount = 0;
	for (iter = g_CINI.mapHistory.begin(); iter != g_CINI.mapHistory.end(); iter++) {
		m_listControl_history.InsertItem(nCount, to_string(nCount + 1).c_str());
		m_listControl_history.SetItemText(nCount, 1, iter->first);
		m_listControl_history.SetItemText(nCount, 2, iter->second);
		nCount++;
	}
	UpdateWindow();
}

void HistoryDlg::OnBnClickedButtonClear()
{
	// TODO:  在此添加控件通知处理程序代码
	g_CINI.addIniRecord(TRUE, "","");
	updateRecordList();
}


void HistoryDlg::OnNMDblclkListHistory(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	POSITION ps;
	int nIndex;

	ps = m_listControl_history.GetFirstSelectedItemPosition();
	nIndex = m_listControl_history.GetNextSelectedItem(ps);
	//TODO:添加多选的操作。
	if (nIndex == -1)
	{
		//m_list.SetItemState(-1,LVNI_SELECTED,LVNI_SELECTED);

	}
	m_listControl_history.SetItemState(nIndex, LVS_EX_FULLROWSELECT, LVS_EX_FULLROWSELECT);

	CString str = "";

	str = str + m_listControl_history.GetItemText(nIndex, 2);
	CModbusTestingDlg modbusMainDlg = new CModbusTestingDlg();
	modbusMainDlg.passValue = str;
	int aStr = str.GetLength();
	//modbusMainDlg.handlePassValue(str);
	((CModbusTestingDlg*)GetParent())->m_editValue_sendText = str;
	((CModbusTestingDlg*)GetParent())->UpdateData(FALSE);
	//modbusMainDlg.m_edit_sendText.SetWindowTextA(str);
	//::SendMessage(m_pParentWnd->m_hWnd, WM_CLOSE, 0, 0);
	OnClose();

	
}


void HistoryDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	//GetParent()->DestroyWindow();//子窗口关闭 父窗口也同样关闭
	EndDialog(0);
	CDialogEx::OnClose();
}

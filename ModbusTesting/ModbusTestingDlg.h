
// ModbusTestingDlg.h : 头文件
//

#pragma once
#include <string>
#include <map>
#include <vector>
#include "afxwin.h"
#include <windows.h>
#include <Winsock2.h>
#include "INI.h"
#include "afxcmn.h"
#include "HistoryDlg.h"

enum isCheck
{
	uncheck,
	check
};
enum isConnect
{
	disconnectStaus,
	connectStaus
};
enum protocolType
{
	UDP,
	TCP_CLIENT,
	TCP_SERVER
};
enum logType
{
	sending,
	receiving,
	cntStatus,
	polling
};
enum eLanguage
{
	mandarin = 1, //普通话 - 1
	english = 2, //英语 - 2
	cantonese = 4, //粤语 - 4
	mandarinAndCantonese = 5 //普通话和粤语 - 5
};
enum ctrlCodeLen
{
	HeadCodeLen = 13,
	areaCodeLen = 160,
	msgCodeLen = 40,
	textCodeLen = 500,
	registerNo351Len = 2,
	intervalAndLoopCheckCodeLen = 2,
	loopTimesCodeLen = 2

};
struct  StructControlCoding
{
	uint8_t headCode[HeadCodeLen];
	uint8_t areaCode[areaCodeLen];
	uint8_t msgCode[msgCodeLen];
	uint8_t textCode[textCodeLen];
	uint8_t	registerNo351[registerNo351Len]; //语种(3)+操作员ID(5)+预留(4)+消息源(4)
	uint8_t intervalAndLoopCheckCode[intervalAndLoopCheckCodeLen];
	uint8_t loopTimesCode[loopTimesCodeLen];
	void initControlCodeing(){
		memset(headCode, 0x00, sizeof(headCode));
		memset(areaCode, 0x00, sizeof(areaCodeLen));
		memset(msgCode, 0x00, sizeof(msgCodeLen));
		memset(textCode, 0x00, sizeof(textCodeLen));
		memset(registerNo351, 0x00, sizeof(registerNo351Len));
		memset(intervalAndLoopCheckCode, 0x00, sizeof(intervalAndLoopCheckCodeLen));
		memset(loopTimesCode, 0x00, sizeof(loopTimesCodeLen));
	}
};


// CModbusTestingDlg 对话框
class CModbusTestingDlg : public CDialogEx
{
// 构造
public:
	CModbusTestingDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MODBUSTESTING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	bool isPol;
	int gloIsConnect;
	int m_Row;
	int m_Col;
	std::string strTTSCode;
	uint8_t uint8TTSCode;
	WSADATA wsaData;
	SOCKET socket_fd; 
	CCriticalSection m_critical;

	CString passValue;
	CString m_editValue_tts;
	CString m_editValue_loopTimes;
	CEdit m_edit_tts;
	CEdit m_edit_Item;
	CEdit m_edit_sendText;
	CComboBox m_combox_station;
	CComboBox m_combo_protocol;
	CComboBox m_combo_ip;
	CComboBox m_combo_port;
	CComboBox m_combox_operater;
	CComboBox m_combox_msgSource;
	CButton m_button_connect;
	CButton m_check_loop;
	CButton m_check_mandarin;
	CButton m_check_english;
	CButton m_check_cantonese;
	CEdit m_edit_log;
	CEdit m_edit_loopTimes;
	CEdit m_edit_interval;
	CListCtrl m_listControl_stationList;
	CListCtrl m_listControl_msgNum;
	CSpinButtonCtrl m_spin_as;
	CSpinButtonCtrl m_spin_interval;
	std::map<int, std::string> mapIniStation;
	std::map<int, stationRegister>::iterator iter;
	

public:
	afx_msg int  initStationInfo();
	afx_msg void initializationUI();
	afx_msg void initprotocolInfo();
	afx_msg void initMsgNumInfo();
	afx_msg void comboxSelectionHandle(CString station);
	afx_msg void OnCbnSelchangeComboStation();
	afx_msg void OnEnChangeEditTts();
	afx_msg void OnBnClickedButtonConnect();
	afx_msg void OnBnClickedButtonPollingCmd();
	afx_msg void printLogFunc(logType type, std::string message, int nLen = 0);
	afx_msg void socketSendAndRecv(SOCKET &s, uint8_t *sendMsg, int sendLen, uint8_t *recvMsg, int &recvLen);
	afx_msg void traversalToSave();
	afx_msg void OnBnClickedButtonClearstation();
	afx_msg void OnNMClickListStationlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkListStationlist(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpinAs(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCheckLoop();
	afx_msg void OnBnClickedCheckMandarin();
	afx_msg void OnBnClickedCheckCantonese();
	afx_msg void OnBnClickedCheckEnglish();
	afx_msg void OnStnClickedStaticStatus();
	afx_msg void OnEnKillfocusEditItem();
	afx_msg void OnNMDblclkListMsgnum(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg CString printfIpAndPort(std::string ip, std::string port, int isConnect);

	afx_msg void OnBnClickedButtonControlCmd();
	afx_msg void OnCbnSetfocusComboStation();
	afx_msg void OnBnClickedButtonSend();
	afx_msg void OnBnClickedButtonHistory();
	afx_msg void handlePassValue(CString passValue);
	CString m_editValue_sendText;
	afx_msg void OnBnClickedButtonClean();
	afx_msg std::string pollingMsgParsing(uint8_t* polMsg);
};

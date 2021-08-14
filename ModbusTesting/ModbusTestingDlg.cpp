
// ModbusTestingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModbusTesting.h"
#include "ModbusTestingDlg.h"
#include "afxdialogex.h"
#include "PublicFunDef.h"
#include <mutex>
#include <thread>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


StructControlCoding ctrlCoding;
auto CTRL_HEAD_CODE = "0001000002C904100001016100";


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CModbusTestingDlg �Ի���



CModbusTestingDlg::CModbusTestingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModbusTestingDlg::IDD, pParent)
	, m_editValue_tts(_T(""))
	, m_editValue_loopTimes(_T(""))
	, m_editValue_sendText(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CModbusTestingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_STATION, m_combox_station);
	DDX_Control(pDX, IDC_EDIT_TTS, m_edit_tts);
	DDX_Text(pDX, IDC_EDIT_TTS, m_editValue_tts);
	DDX_Control(pDX, IDC_COMBO_PROTOCOL, m_combo_protocol);
	DDX_Control(pDX, IDC_COMBO_IP, m_combo_ip);
	DDX_Control(pDX, IDC_COMBO_PORT, m_combo_port);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_button_connect);
	DDX_Control(pDX, IDC_EDIT_LOG, m_edit_log);
	DDX_Control(pDX, IDC_LIST_STATIONLIST, m_listControl_stationList);
	DDX_Control(pDX, IDC_EDIT_LOOPTIMES, m_edit_loopTimes);
	DDX_Text(pDX, IDC_EDIT_LOOPTIMES, m_editValue_loopTimes);
	DDX_Control(pDX, IDC_SPIN_AS, m_spin_as);
	DDX_Control(pDX, IDC_COMBO_OPERATER, m_combox_operater);
	DDX_Control(pDX, IDC_COMBO_MSGSOUR, m_combox_msgSource);
	DDX_Control(pDX, IDC_CHECK_LOOP, m_check_loop);
	DDX_Control(pDX, IDC_EDIT_INTERVAL, m_edit_interval);
	DDX_Control(pDX, IDC_SPIN_INTERVAL, m_spin_interval);
	DDX_Control(pDX, IDC_CHECK_MANDARIN, m_check_mandarin);
	DDX_Control(pDX, IDC_CHECK_ENGLISH, m_check_english);
	DDX_Control(pDX, IDC_CHECK_CANTONESE, m_check_cantonese);
	DDX_Control(pDX, IDC_LIST_MSGNUM, m_listControl_msgNum);
	DDX_Control(pDX, IDC_EDIT_ITEM, m_edit_Item);
	DDX_Control(pDX, IDC_EDIT1, m_edit_sendText);
	DDX_Text(pDX, IDC_EDIT1, m_editValue_sendText);
}

BEGIN_MESSAGE_MAP(CModbusTestingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO_STATION, &CModbusTestingDlg::OnCbnSelchangeComboStation)
	ON_EN_CHANGE(IDC_EDIT_TTS, &CModbusTestingDlg::OnEnChangeEditTts)
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CModbusTestingDlg::OnBnClickedButtonConnect)
	ON_BN_CLICKED(IDC_BUTTON_POLLING_CMD, &CModbusTestingDlg::OnBnClickedButtonPollingCmd)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STATIONLIST, &CModbusTestingDlg::OnNMClickListStationlist)
	ON_BN_CLICKED(IDC_BUTTON_CLEARSTATION, &CModbusTestingDlg::OnBnClickedButtonClearstation)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STATIONLIST, &CModbusTestingDlg::OnNMDblclkListStationlist)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_AS, &CModbusTestingDlg::OnDeltaposSpinAs)
	ON_BN_CLICKED(IDC_CHECK_LOOP, &CModbusTestingDlg::OnBnClickedCheckLoop)
	ON_BN_CLICKED(IDC_CHECK_MANDARIN, &CModbusTestingDlg::OnBnClickedCheckMandarin)
	ON_BN_CLICKED(IDC_CHECK_CANTONESE, &CModbusTestingDlg::OnBnClickedCheckCantonese)
	ON_BN_CLICKED(IDC_CHECK_ENGLISH, &CModbusTestingDlg::OnBnClickedCheckEnglish)
	ON_EN_KILLFOCUS(IDC_EDIT_ITEM, &CModbusTestingDlg::OnEnKillfocusEditItem)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_MSGNUM, &CModbusTestingDlg::OnNMDblclkListMsgnum)
	ON_BN_CLICKED(IDC_BUTTON_CONTROL_CMD, &CModbusTestingDlg::OnBnClickedButtonControlCmd)
	ON_CBN_SETFOCUS(IDC_COMBO_STATION, &CModbusTestingDlg::OnCbnSetfocusComboStation)
	ON_BN_CLICKED(ID_BUTTON_SEND, &CModbusTestingDlg::OnBnClickedButtonSend)
	ON_BN_CLICKED(IDC_BUTTON_HISTORY, &CModbusTestingDlg::OnBnClickedButtonHistory)
	ON_BN_CLICKED(IDC_BUTTON_CLEAN, &CModbusTestingDlg::OnBnClickedButtonClean)
END_MESSAGE_MAP()


// CModbusTestingDlg ��Ϣ�������

BOOL CModbusTestingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	initializationUI();

	ctrlCoding.initControlCodeing();
	//��ʼ��ͷ 0001000002C904100001016100
	uint8_t uint8Temp[13] = { 0 };
	Ascii2Hex(uint8Temp, (uint8_t*)CTRL_HEAD_CODE, 26);
	memcpy(ctrlCoding.headCode, uint8Temp, 13);

	isPol = false;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CModbusTestingDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CModbusTestingDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CModbusTestingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�㲥����Ա��c����ʼ��
std::string strOperate[20] = {
	"����ֵ������(�ܵ�)", "���Ļ���", "�����е�1", "�����е�2",
	"�����е�3", "Ԥ��", "Ԥ��", "Ԥ��",
	"Ԥ��", "Ԥ��", "Ԥ��", "��վ����",
	"Ԥ��", "�γ����޵���", "��վֵ��", "�г���վ�Զ��㲥",
	"Ԥ��", "Ԥ��", "Ԥ��", "Ԥ��"
};
//��ϢԴ��ţ�d����ʼ��
std::string chStrMsgSource[10] = {
	"�˹��㲥(ʵʱ�㲥)", "�ճ�Ԥ��㲥", "��ӹ㲥(��������)", "ֹͣ�˹��㲥(ʵʱ�㲥)", "ֹͣ�ճ�Ԥ��㲥",
	"ֹͣ��ӹ㲥(��������)", "��ʼ�����㲥", "ֹͣ�����㲥", "��ʼ�ı��㲥", "ֹͣ�ı��㲥"
};

void CModbusTestingDlg::initializationUI()
{
	initStationInfo();

	initprotocolInfo();

	initMsgNumInfo();

	//��ʼ��TTS��������
	m_edit_tts.SetLimitText(500);
	m_check_mandarin.SetCheck(check);

	//radioButtonĬ������
	CButton* radio;
	radio = (CButton*)GetDlgItem(IDC_RADIO_HEX);
	radio->SetCheck(1);

	radio = (CButton*)GetDlgItem(IDC_RADIO_HEX2);
	radio->SetCheck(1);

	//ѭ������spin�ؼ���ʼ��
	m_edit_loopTimes.EnableWindow(FALSE);
	m_spin_as.EnableWindow(FALSE);
	m_spin_as.SetRange32(1, 65535);//��ʾ��ֵֻ����0��10�ڱ仯
	m_spin_as.SetBase(10);//���ý�����,ֻ����10���ƺ�16����



	for (size_t i = 1; i < 21;i++)
	{
		CString comboxList_operater = "";
		comboxList_operater.Format("ID:%d  0x%02X  %s", i, i, strOperate[i-1].c_str());
		m_combox_operater.AddString(comboxList_operater);
	}
	m_combox_operater.SetCurSel(0);


	for (size_t i = 1; i < 11; i++)
	{
		CString comboxList_msgSource = "";
		comboxList_msgSource.Format("%d  0x%02X  %s", i, i-1, chStrMsgSource[i - 1].c_str());
		m_combox_msgSource.AddString(comboxList_msgSource);
	}
	m_combox_msgSource.SetCurSel(0);

	//���ʱ��
	m_spin_interval.SetRange(0, 200);
	m_spin_interval.SetBase(10);
}

int CModbusTestingDlg::initStationInfo()
{
	gloIsConnect = disconnectStaus;
	m_button_connect.SetWindowText("����");

	char listSelection[32] = { 0 };
	//std::map<int, stationRegister>::iterator iter;
	for (iter = g_CINI.mapStationList.begin(); iter != g_CINI.mapStationList.end(); iter++) {
		sprintf(listSelection, "%d.%s", iter->first, transcoding2utf8((char*)iter->second.name.c_str()).c_str());
		m_combox_station.AddString(listSelection);
		memset(listSelection, 0x00, sizeof(listSelection));
	}

	m_combox_station.SetCurSel(0);

	//LONG lStyle;
	//lStyle = GetWindowLong(m_listControl_stationList.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	//lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	//lStyle |= LVS_REPORT; //����style
	//lStyle |= LVS_SINGLESEL;//��ѡģʽ
	//SetWindowLong(m_listControl_stationList.m_hWnd, GWL_STYLE, lStyle);//����style

	//DWORD dwStyle = m_listControl_stationList.GetExtendedStyle();
	//dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	//dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	//m_listControl_stationList.SetExtendedStyle(dwStyle); //������չ���
	m_listControl_stationList.ModifyStyle(0, LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS);
	m_listControl_stationList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);
	//m_listControl_stationList.SetTextColor(RGB(255, 0, 0));                  //��ʾ�������ɫ
	DWORD dwStyle = m_listControl_stationList.GetStyle();
	dwStyle |= LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_SHOWSELALWAYS;
	m_listControl_stationList.SetExtendedStyle(dwStyle);



	m_listControl_stationList.InsertColumn(0, "����", LVCFMT_CENTER, 60, 0);
	m_listControl_stationList.InsertColumn(1, "����������", LVCFMT_CENTER, 78, 1);
	m_listControl_stationList.InsertColumn(2, "վ��", LVCFMT_CENTER, 240, 2);


	OnCbnSelchangeComboStation();
	return 0;
}

void CModbusTestingDlg::initprotocolInfo()
{

	m_combo_ip.EnableWindow(true);
	m_combo_port.EnableWindow(true);
	m_combo_protocol.EnableWindow(true);

	m_combo_protocol.ResetContent();
	m_combo_protocol.AddString("TCP Client");
	m_combo_protocol.SetCurSel(0);

	m_combo_port.ResetContent();
	m_combo_ip.ResetContent();

	for each (std::string var in g_CINI.vecIp)
	{
		m_combo_ip.AddString(var.c_str());
	}
	m_combo_ip.SetCurSel(0);

	for each (std::string var in g_CINI.vecPort)
	{
		m_combo_port.AddString(var.c_str());
	}
	m_combo_port.SetCurSel(0);

	//UpdateWindow();
}

void CModbusTestingDlg::initMsgNumInfo()
{
	LONG lStyle;
	lStyle = GetWindowLong(m_listControl_msgNum.m_hWnd, GWL_STYLE);//��ȡ��ǰ����style
	lStyle &= ~LVS_TYPEMASK; //�����ʾ��ʽλ
	lStyle |= LVS_REPORT; //����style
	lStyle |= LVS_SINGLESEL;//��ѡģʽ
	SetWindowLong(m_listControl_msgNum.m_hWnd, GWL_STYLE, lStyle);//����style

	DWORD dwStyle = m_listControl_msgNum.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	m_listControl_msgNum.SetExtendedStyle(dwStyle); //������չ���
	m_listControl_msgNum.InsertColumn(0, "��Ϣ���ID", LVCFMT_CENTER, 100, 0);
	m_listControl_msgNum.InsertColumn(1, "��Ϣ���", LVCFMT_CENTER, 120, 1);
	m_listControl_msgNum.InsertColumn(2, "ȡֵ��Χ", LVCFMT_CENTER, 162, 2);

	for (size_t i = 0; i < 20;i++)
	{
		CString strMsgId = "";
		strMsgId.Format("b%02d", i + 1);
		m_listControl_msgNum.InsertItem(i, strMsgId);
		m_listControl_msgNum.SetItemText(i, 1, "0");
		m_listControl_msgNum.SetItemText(i, 2, "1-1024");
	}
	m_Row = 0;
	m_Col = 0;
	m_edit_Item.ShowWindow(SW_HIDE);

}

CString CModbusTestingDlg::printfIpAndPort(std::string ip, std::string port, int isConnect)
{
	CString resultStr;
	if (isConnect < 0)
	{
		//connect Fail
		resultStr.Format("����ʧ�ܣ�#%s:%s:%d", ip.c_str(), port.c_str(), socket_fd);
		m_button_connect.SetWindowText("����");
		gloIsConnect = disconnectStaus;
		m_combo_ip.EnableWindow(true);
		m_combo_port.EnableWindow(true);
		m_combo_protocol.EnableWindow(true);
	} 
	else
	{
		//conect Success
		resultStr.Format("���ӳɹ���#%s:%s:%d", ip.c_str(), port.c_str(), socket_fd);
		m_button_connect.SetWindowText("�Ͽ�");
		gloIsConnect = connectStaus;
		g_CINI.addIpAndPortToIni(ip, port);
		//initprotocolInfo();
		m_combo_ip.EnableWindow(false);
		m_combo_port.EnableWindow(false);
		m_combo_protocol.EnableWindow(false);

	}
	printLogFunc(cntStatus, resultStr.GetBuffer());
	resultStr.ReleaseBuffer();
	return resultStr;
}

void CModbusTestingDlg::traversalToSave()
{
	CString station;
	m_combox_station.GetLBText(m_combox_station.GetCurSel(), station);
	VecString selectValueTemp;
	selectValueTemp = vSplitString(station.GetBuffer(), ".");
	station.ReleaseBuffer();
	int id = atoi(selectValueTemp[0].c_str());
	iter = g_CINI.mapStationList.find(id);

	int nItem, i;
	vector<int> vecStatusList;
	nItem = m_listControl_stationList.GetItemCount();
	for (i = 0; i < nItem; ++i)
	{
		if (m_listControl_stationList.GetCheck(i))
		{
			vecStatusList.push_back(check);
		}
		else
		{
			vecStatusList.push_back(uncheck);
		}
	}

	if (iter != g_CINI.mapStationList.end())
	{
		//���
		iter->second.vecStationCheckList.clear();
		//������ֵ
		iter->second.vecStationCheckList = vecStatusList;
	}


}

void CModbusTestingDlg::comboxSelectionHandle(CString station)
{
	CString partStr;
	vector<std::string> selectValueTemp;
	selectValueTemp = vSplitString(station.GetBuffer(), ".");
	station.ReleaseBuffer();
	int id = atoi(selectValueTemp[0].c_str());
	iter = g_CINI.mapStationList.find(id);
	if (iter != g_CINI.mapStationList.end())
	{
		m_listControl_stationList.DeleteAllItems();
		int rNum = iter->second.low;
		int partNum = 0;
		int partTempNum = 0;
		for (size_t i = 0; i < iter->second.vecStationCheckList.size(); i++)
		{

			if (i <= 15)
			{
				partNum = iter->second.partitionNum1;
			}
			else
			{
				partNum = iter->second.partitionNum2;
			}
			
			partStr.Format("%s - P%d", transcoding2utf8((char*)iter->second.name.c_str()).c_str(),++partTempNum);
			m_listControl_stationList.InsertItem(i, std::to_string(rNum).c_str());
			m_listControl_stationList.SetItemText(i, 1, std::to_string(partNum).c_str());
			m_listControl_stationList.SetItemText(i, 2, partStr);
			m_listControl_stationList.SetCheck(i, iter->second.vecStationCheckList.at(i));

			rNum++;
		}
	}
	UpdateWindow();

}

void CModbusTestingDlg::OnCbnSelchangeComboStation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString station;
	m_combox_station.GetLBText(m_combox_station.GetCurSel(), station);
	comboxSelectionHandle(station);
}


void CModbusTestingDlg::OnEnChangeEditTts()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������


}


void CModbusTestingDlg::OnBnClickedButtonConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	if (gloIsConnect == connectStaus)
	{
		WSACleanup();
		closesocket(socket_fd);
		m_button_connect.SetWindowText("����");
		gloIsConnect = disconnectStaus;
		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("�ѶϿ�������");
		printLogFunc(cntStatus, "�ѶϿ�������");
		socket_fd = 0;
		m_combo_ip.EnableWindow(true);
		m_combo_port.EnableWindow(true);
		m_combo_protocol.EnableWindow(true);
		return;
	}

	CString strType, strIp, strPort;
	m_combo_protocol.GetWindowText(strType);
	m_combo_ip.GetWindowText(strIp);
	m_combo_port.GetWindowText(strPort);

	if (strType.Compare("UDP") == 0)
	{

	}
	else if (0 == strType.Compare("TCP Client"))
	{
		
		int ret = -1;
		
		//����ϵͳ���������Socket�汾��������Ӧ��Socket�⣬�˴�ʹ��socket2.2�汾
		if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)//0��ʾ��ʼ���ɹ�
		{
			return ;
		}
		if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
		{
			WSACleanup();
			return ;
		}
		struct sockaddr_in serveraddr;
		socket_fd = socket(PF_INET, SOCK_STREAM, 0);
		if (socket_fd == -1)
		{
			AfxMessageBox("Failed to create socket!");
			return ;
		}
		
		int nTimeout = 1000;
		//���÷��ͳ�ʱΪ1000ms
		if (SOCKET_ERROR == setsockopt(socket_fd, SOL_SOCKET, SO_SNDTIMEO,
			(char *)&nTimeout, sizeof(int)))
		{
			//fprintf(stderr, "Set SO_SNDTIMEO error !\n");
		}
		//���ý��ճ�ʱΪ1000ms
		if (SOCKET_ERROR == setsockopt(socket_fd, SOL_SOCKET, SO_RCVTIMEO,
			(char *)&nTimeout, sizeof(int)))
		{
			//fprintf(stderr, "Set SO_RCVTIMEO error !\n");
		}

		fd_set rfd;      //�������� ��������������Ƿ����
		struct timeval timeout;  //ʱ��ṹ��
		FD_ZERO(&rfd);//�����һ����������
		FD_SET(socket_fd, &rfd);
		timeout.tv_sec = 0;//��
		timeout.tv_usec = 50000;//һ�����֮һ�룬΢��

		u_long ul = 1;//���������
		ioctlsocket(socket_fd, FIONBIO, &ul);//����Ϊ����������



		serveraddr.sin_family = AF_INET;
		serveraddr.sin_port = htons(atoi(strPort));
		serveraddr.sin_addr.s_addr = inet_addr(strIp); //inet_addr ���ַ���תΪ����
		ret = connect(socket_fd,
			(struct sockaddr *)&serveraddr, //��һ����ַ
			sizeof(struct sockaddr));


		ret = select(0, 0, &rfd, 0, &timeout);
		if (ret <= 0)
		{
			//��ʱ
			WSACleanup();
			closesocket(socket_fd);
			m_button_connect.SetWindowText("����");
			gloIsConnect = disconnectStaus;
			GetDlgItem(IDC_STATIC_STATUS)->SetWindowText("���ӳ�ʱ������");
			printLogFunc(cntStatus, "���ӳ�ʱ������");
			socket_fd = 0;
			m_combo_ip.EnableWindow(true);
			m_combo_port.EnableWindow(true);
			m_combo_protocol.EnableWindow(true);
			return;
		}
		ul = 0;
		ioctlsocket(socket_fd, FIONBIO, &ul);


		GetDlgItem(IDC_STATIC_STATUS)->SetWindowText(printfIpAndPort(strIp.GetBuffer(), strPort.GetBuffer(), ret));
		strIp.ReleaseBuffer();
		strPort.ReleaseBuffer();
	}
	else //TCP SERVER
	{

	}
}

void CModbusTestingDlg::OnBnClickedButtonPollingCmd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (socket_fd == 0)
	{
		AfxMessageBox("δ��������");
		isPol = false;
		return;
	}
	isPol = true;
	std::mutex x;
	x.lock();
	uint8_t recvMsgHex[LENGTH_A] = { 0 };
	int recvLen = 0;
	int sendLen = g_CINI.pollCmd.length();
	socketSendAndRecv(socket_fd, (uint8_t*)g_CINI.pollCmd.c_str(), sendLen, recvMsgHex, recvLen);
	memset(recvMsgHex, 0x00, sizeof(recvMsgHex));

	x.unlock();
}


void CModbusTestingDlg::printLogFunc(logType type, std::string message, int nLen)
{ 
	CString outMessage;

	switch (type)
	{
	case sending:
		outMessage.Format("[%s] SEND Length:%d\r\n%s\r\n", GetGmtTime(), nLen, message.c_str());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(), GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel(outMessage);
		replace(message, " ", "");
		//g_CINI.mapHistory.insert(make_pair(GetGmtTime(), message.c_str()));
		g_CINI.addIniRecord(FALSE, message.c_str(), GetGmtTime().GetBuffer());
		break;
	case receiving:
		outMessage.Format("[%s] RECV Length:%d\r\n%s\r\n", GetGmtTime(), nLen, message.c_str());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(), GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel(outMessage);

		break;
	case cntStatus:
		outMessage.Format("[%s] %s\r\n", GetGmtTime(),message.c_str());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(), GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel(outMessage);
		break;
	case polling:
		outMessage.Format("%s", message.c_str());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(), GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
		((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel(outMessage);
		break;
	default:
		break;
	}
	((CEdit*)GetDlgItem(IDC_EDIT_LOG))->SetSel(GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength(), GetDlgItem(IDC_EDIT_LOG)->GetWindowTextLength());
	((CEdit*)GetDlgItem(IDC_EDIT_LOG))->ReplaceSel("\r\n");
}
/************************************************************************/
/* ��Ϣ�շ�                                                             */
/************************************************************************/
void CModbusTestingDlg::socketSendAndRecv(SOCKET &s, uint8_t *sendMsg, int sendLen, uint8_t *recvMsg, int &recvLen)
{

	int sendingType = 0;
	sendingType = ((CButton *)GetDlgItem(IDC_RADIO_HEX))->GetCheck();
	int recvingType = 0;
	recvingType = ((CButton *)GetDlgItem(IDC_RADIO_HEX2))->GetCheck();
	int ret = -1;
	uint8_t recvMsgHex[LENGTH_A] = { 0 };
	uint8_t uint8SendMsg[LENGTH_A] = { 0 };
	uint8_t recvMsgAscii[LENGTH_A] = { 0 };
	uint8_t Ascii[LENGTH_A] = { 0 };
	std::string asciiStr, hexStr;
	m_critical.Lock();
	switch (sendingType)
	{
	case 0: //ASCII ֱ��ת������
		ret = send(s, (char*)sendMsg, sendLen, 0); //����
		printLogFunc(sending, (char*)sendMsg, ret);
		break;
	case 1: //HEX ѹ���ַ����ȷ���
		asciiStr = "";
		Ascii2Hex(uint8SendMsg, sendMsg, sendLen);
		//ret = send(s, (char*)uint8SendMsg, sendLen, 0); //����
		//printLogFunc(sending, uint8Str2HexStr(uint8SendMsg, sendLen), ret);
		ret = send(s, (char*)uint8SendMsg, sendLen / 2, 0); //����
		printLogFunc(sending, uint8Str2HexStr(uint8SendMsg, sendLen / 2), ret);
		break;
	default:
		break;
	}
	Sleep(50);
	recvLen = recv(s, (char*)recvMsg, LENGTH_A, 0); //����
	int i = 0;
	char recvTemp[LENGTH_A] = { 0 };
	memcpy(recvTemp, recvMsg, recvLen);
	char a = recvTemp[8];
	char b = recvTemp[7];
	switch (recvingType)
	{
	case 0: //ASCII ��ʾ
		//i = Hex2Ascii(recvMsgHex, recvMsg, recvLen);
		//HexStr2CharStr((char*)recvMsgHex, (char*)recvMsgAscii, i);
		printLogFunc(receiving, (char*)recvMsg, recvLen);
		break;
	case 1: //HEX ��ʾ
		printLogFunc(receiving, uint8Str2HexStr(recvMsg, recvLen), recvLen);
		if (isPol && b == 0x04) {
			isPol = false;
			printLogFunc(polling,pollingMsgParsing(recvMsg),0);
		}

		break;
	default:
		break;
	}
	m_critical.Unlock();
}


/************************************************************************/
/* listControl ����ѡ��                                                 */
/************************************************************************/
void CModbusTestingDlg::OnNMClickListStationlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//�������泵վ��Ϣ
	traversalToSave();
}


void CModbusTestingDlg::OnBnClickedButtonClearstation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	std::vector<int> stationCheckList1(g_CINI.STATION_REG_LEN, 0); //��ʼ��32��0Ԫ�ص�vector
	if (MessageBox(_T("ȷ��������г�վ��ѡ��Ϣ��?"), _T("��ʾ"), MB_YESNO | MB_ICONWARNING) == IDYES)
	{
		for (iter = g_CINI.mapStationList.begin(); iter != g_CINI.mapStationList.end(); iter++) {
			iter->second.vecStationCheckList = stationCheckList1;
		}
	}
	OnCbnSelchangeComboStation();
	//��ղ����ͷ��ڴ�
	stationCheckList1.clear();
	std::vector <int>().swap(stationCheckList1);
}

/************************************************************************/
/* listControl ˫��ѡ��                                                 */
/************************************************************************/
void CModbusTestingDlg::OnNMDblclkListStationlist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	POSITION pos = m_listControl_stationList.GetFirstSelectedItemPosition();
	int nItem = m_listControl_stationList.GetNextSelectedItem(pos);
	if (m_listControl_stationList.GetCheck(nItem) == 1)
	{
		m_listControl_stationList.SetCheck(nItem, FALSE);
	}
	else
	{
		m_listControl_stationList.SetCheck(nItem, TRUE);
	}
	traversalToSave();
}


void CModbusTestingDlg::OnDeltaposSpinAs(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

}


void CModbusTestingDlg::OnBnClickedCheckLoop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_check_loop.GetCheck())
	{
	case 0:
		m_edit_loopTimes.EnableWindow(FALSE);
		m_spin_as.EnableWindow(FALSE);
		break;
	case 1:
		m_edit_loopTimes.EnableWindow(TRUE);
		m_spin_as.EnableWindow(TRUE);
		m_edit_loopTimes.SetWindowTextA("1");
		break;
	default:
		break;
	}
}


void CModbusTestingDlg::OnBnClickedCheckMandarin()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_check_mandarin.GetCheck())
	{
	case 0:
		if (0 == m_check_cantonese.GetCheck())
		{
			m_check_english.SetCheck(check);
		}
		break;
	case 1:
		m_check_english.SetCheck(uncheck);
		break;
	default:
		break;
	}
	
}


void CModbusTestingDlg::OnBnClickedCheckCantonese()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	switch (m_check_cantonese.GetCheck())
	{
	case 0:
		if (0 == m_check_mandarin.GetCheck())
		{
			m_check_english.SetCheck(check);
		}
		break;
	case 1:
		m_check_english.SetCheck(uncheck);
		break;
	default:
		break;
	}
}


void CModbusTestingDlg::OnBnClickedCheckEnglish()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (check == m_check_cantonese.GetCheck() || check == m_check_mandarin.GetCheck())
	{
		m_check_cantonese.SetCheck(uncheck);
		m_check_mandarin.SetCheck(uncheck);
	}

}


void CModbusTestingDlg::OnEnKillfocusEditItem()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString tem;
	m_edit_Item.GetWindowText(tem);    //�õ��û�������µ�����
	if ("" == tem.Trim())
	{
		m_listControl_msgNum.SetItemText(m_Row, m_Col, "0");   //���ñ༭���������
	}
	else
	{
		m_listControl_msgNum.SetItemText(m_Row, m_Col, tem);   //���ñ༭���������

	}
	m_edit_Item.ShowWindow(SW_HIDE);                //���ر༭��
}


void CModbusTestingDlg::OnNMDblclkListMsgnum(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	CRect rc;
	m_Row = pNMListView->iItem;//���ѡ�е���
	//m_Col = pNMListView->iSubItem;//���ѡ����
	m_Col = 1;//�����޸ĵ�һ��

	if (pNMListView->iSubItem != 0) //���ѡ���������;
	{
		m_listControl_msgNum.GetSubItemRect(m_Row, m_Col, LVIR_LABEL, rc);//��������RECT��
		m_edit_Item.SetParent(&m_listControl_msgNum);//ת������Ϊ�б���е�����
		m_edit_Item.MoveWindow(rc);//�ƶ�Edit��RECT���ڵ�λ��;
		m_edit_Item.SetWindowText(m_listControl_msgNum.GetItemText(m_Row, m_Col));//���������е�ֵ����Edit�ؼ��У�
		m_edit_Item.ShowWindow(SW_SHOW);//��ʾEdit�ؼ���
		m_edit_Item.SetWindowTextA("");
		m_edit_Item.SetFocus();//����Edit����
		m_edit_Item.ShowCaret();//��ʾ���
		m_edit_Item.SetSel(-1);//������ƶ������
	}
	*pResult = 0;
}

void CModbusTestingDlg::OnBnClickedButtonControlCmd()
{
	traversalToSave();
	if (socket_fd == 0)
	{
		AfxMessageBox("δ��������");
		return;
	}


	/*��ȡ��վ���*/
	int nIndex = 7, nIndex2 = -1;
	uint8_t uint8StationList[400];
	uint8_t uchStation[8] = { 0 };
	memset(uint8StationList, 0x00, sizeof(uint8StationList));
	for (iter = g_CINI.mapStationList.begin(); iter != g_CINI.mapStationList.end(); iter++) {
		nIndex = 7;
		int j = g_CINI.STATION_REG_LEN - 1;
		for (; j > 0; j -= 4)
		{
			int bitTemp1 = iter->second.vecStationCheckList.at(j);
			int bitTemp2 = iter->second.vecStationCheckList.at(j - 1);
			int bitTemp3 = iter->second.vecStationCheckList.at(j - 2);
			int bitTemp4 = iter->second.vecStationCheckList.at(j - 3);
			uchStation[nIndex] = (bitTemp1 << 3) | (bitTemp2 << 2) | (bitTemp3 << 1) | (bitTemp4);
			nIndex--;
		}
		uint8StationList[++nIndex2] = ((uchStation[3] << 4) & 0xff) | (uchStation[2] & 0x0f);
		uint8StationList[++nIndex2] = ((uchStation[1] << 4) & 0xff) | (uchStation[0] & 0x0f);
		uint8StationList[++nIndex2] = ((uchStation[7] << 4) & 0xff) | (uchStation[6] & 0x0f);
		uint8StationList[++nIndex2] = ((uchStation[5] << 4) & 0xff) | (uchStation[4] & 0x0f);
		memset(uchStation, 0x00, sizeof(uchStation));
	}
	memcpy(ctrlCoding.areaCode, uint8StationList, areaCodeLen);

	/*��ȡ��Ϣ���*/

	int nItem = m_listControl_msgNum.GetItemCount();
	uint8_t uint8MsgNum[40] = { 0 };
	wchar_t wchMsgNum = 0;
	int uIndex = -1;
	for (size_t i = 0; i < 20; i++)
	{
		CString strMsgNum = m_listControl_msgNum.GetItemText(i, 1);//��ȡָ���У�Ϊ�ַ�����ʽ
		wchMsgNum = atoi(strMsgNum);
		uint8MsgNum[++uIndex] = (wchMsgNum >> 8) & 0x00ff;
		uint8MsgNum[++uIndex] = (wchMsgNum)& 0x00ff;
	}
	memcpy(ctrlCoding.msgCode, uint8MsgNum, msgCodeLen);

	/*��ȡTTSת���ı�*/
	CString ttsStr;
	m_edit_tts.GetWindowTextA(ttsStr);
	std::wstring utfCode = L"";
	uint8_t uint8Tts[500];
	memset(uint8Tts, 0x00, sizeof(uint8Tts));
	int iIndex = 0;
	switch (IncludeChinese(ttsStr.GetBuffer()))
	{
	case 0: //����������
		//utfCode = Utf8ToUnicode(ttsStr);  //Ӣ�� UTF8���루"well" -> 77656C6C��
		utfCode = AnsiToUnicode(ttsStr);  //Ӣ�� UTF16BE���루"well" -> 770065006C006C00)
		for each (auto utfTemp in utfCode)
		{
			uint8Tts[iIndex] = (utfTemp >> 8) & 0x00ff;////
			uint8Tts[++iIndex] = utfTemp & 0x00ff;
			//uint8Tts[iIndex] = utfTemp & 0x00ff;
			iIndex++;
		}
		break;
	case 1: //��������
		utfCode = AnsiToUnicode(ttsStr);  //���� UTF16BE���루"��ӭ" -> FEFF6B228FCE)
		for each (auto utfTemp in utfCode)
		{
			uint8Tts[iIndex] = (utfTemp >> 8) & 0x00ff;
			uint8Tts[++iIndex] = utfTemp & 0x00ff;
			iIndex++;
		}
		break;
	default:
		break;
	}
	ttsStr.ReleaseBuffer();


	memcpy(ctrlCoding.textCode, uint8Tts, textCodeLen);

	/*��ȡ����ѡ��*/
	uint8_t language = 0x00;//����
	if (check == m_check_mandarin.GetCheck() && check == m_check_cantonese.GetCheck())
	{
		language = mandarinAndCantonese;
	}
	else if (check == m_check_mandarin.GetCheck())
	{
		language = mandarin;
	}
	else if (check == m_check_cantonese.GetCheck())
	{
		language = cantonese;
	}
	else if (check == m_check_english.GetCheck())
	{
		language = english;
	}

	/*��ȡ��ϢԴ*/
	uint8_t uint8MsgSoure = m_combox_msgSource.GetCurSel(); // ��ȡ��ϢԴѡ��������

	/*��ȡ�㲥����ID*/
	uint8_t uint8OperaterId = m_combox_operater.GetCurSel() + 1;// ��ȡ�㲥����IDѡ��������

	//�ϲ� ����(3)+����ԱID(5)+Ԥ��(4)+��ϢԴ(4)
	uint8_t uint8Reserved = 0x00;  //Ԥ���Ĵ���
	uint8_t uint8RegisterTemp[2] = { 0 };
	uint8RegisterTemp[0] = (language << 5) | uint8OperaterId;
	uint8RegisterTemp[1] = uint8Reserved | uint8MsgSoure;
	memcpy(ctrlCoding.registerNo351, uint8RegisterTemp, registerNo351Len);

	/*�Ƿ�ѭ����ѭ������*/
	CString strloopTimes = "";
	uint8_t uint8IsCheck = 0x00;
	wchar_t wchLoopTimes = 0x0000;
	uint8_t uint8LoopTimes[2] = { 0 };
	if (check == m_check_loop.GetCheck())
	{
		uint8IsCheck = 0x01;
		m_edit_loopTimes.GetWindowText(strloopTimes);
		wchLoopTimes = atoi(strloopTimes);
	}
	uint8LoopTimes[0] = (wchLoopTimes >> 8) & 0x00ff;
	uint8LoopTimes[1] = wchLoopTimes & 0x00ff;
	memcpy(ctrlCoding.loopTimesCode, uint8LoopTimes, loopTimesCodeLen);

	/*��ȡ���ʱ��*/
	CString strInterval = "";
	m_edit_interval.GetWindowTextA(strInterval);
	wchar_t wchInterval = atoi(strInterval);
	uint8_t uint8IntervalAndLoopCheck[2] = { 0 };
	wchar_t IntervalAndLoopCheck = 0x0000;
	IntervalAndLoopCheck = ((wchInterval << 1) | uint8IsCheck);

	uint8IntervalAndLoopCheck[0] = (IntervalAndLoopCheck >> 8) & 0x00ff;
	uint8IntervalAndLoopCheck[1] = IntervalAndLoopCheck & 0x00ff;
	memcpy(ctrlCoding.intervalAndLoopCheckCode, uint8IntervalAndLoopCheck, intervalAndLoopCheckCodeLen);
	
	/*�ϲ�����*/
	uint8_t uint8CtrlSendCode[719] = { 0 };
	int nLenIndex = 0;
	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.headCode, HeadCodeLen);
	nLenIndex += HeadCodeLen;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.areaCode, areaCodeLen);
	nLenIndex += areaCodeLen;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.msgCode, msgCodeLen);
	nLenIndex += msgCodeLen;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.textCode, textCodeLen);
	nLenIndex += textCodeLen;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.registerNo351, registerNo351Len);
	nLenIndex += registerNo351Len;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.intervalAndLoopCheckCode, intervalAndLoopCheckCodeLen);
	nLenIndex += intervalAndLoopCheckCodeLen;

	memcpy(uint8CtrlSendCode + nLenIndex, ctrlCoding.loopTimesCode, loopTimesCodeLen);
	nLenIndex += loopTimesCodeLen;

	/*����*/
	uint8_t recvMsgHex[LENGTH_A] = { 0 };
	//socketSendAndRecv(socket_fd, uint8CtrlSendCode, nLenIndex, recvMsgHex, recvLen);

	int ret = 0;
	uint8_t recvMsg[LENGTH_A] = { 0 };
	char charstr[LENGTH_A] = { 0 };
	ret = send(socket_fd, (char*)uint8CtrlSendCode, nLenIndex, 0); //����
	printLogFunc(sending, uint8Str2HexStr(uint8CtrlSendCode, nLenIndex),ret);

	int recvLen = 0;
	recvLen = recv(socket_fd, (char*)recvMsg, LENGTH_A, 0); //����

	int recvingType = 0;
	recvingType = ((CButton *)GetDlgItem(IDC_RADIO_HEX2))->GetCheck();
	switch (recvingType)
	{
	case 0: //ASCII ��ʾ
		printLogFunc(receiving, (char*)recvMsg, recvLen);
		break;
	case 1: //HEX ��ʾ
		printLogFunc(receiving, uint8Str2HexStr(recvMsg, recvLen), recvLen);
		break;
	default:
		break;
	}
	memset(uint8CtrlSendCode, 0x00, sizeof(uint8CtrlSendCode));
	memset(recvMsgHex, 0x00, LENGTH_A);

	ctrlCoding.initControlCodeing();
	uint8_t uint8Temp[13] = { 0 };
	Ascii2Hex(uint8Temp, (uint8_t*)CTRL_HEAD_CODE, 26);
	memcpy(ctrlCoding.headCode, uint8Temp, 13);
}


void CModbusTestingDlg::OnCbnSetfocusComboStation()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	traversalToSave();

}


void CModbusTestingDlg::OnBnClickedButtonSend()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	/*��ȡeditcontrol����*/
	CString sendText;
	m_edit_sendText.GetWindowTextA(sendText);
	if (socket_fd == 0 || sendText == "")
	{
		return;
	}

	uint8_t uint8Recv[LENGTH_A] = { 0 };
	int recvLen = 0;
	int sendLen = sendText.GetLength();
	socketSendAndRecv(socket_fd, (uint8_t*)sendText.Trim().GetBuffer(sendLen), sendText.GetLength(), uint8Recv, recvLen);
	sendText.ReleaseBuffer(sendLen);
	
}


void CModbusTestingDlg::OnBnClickedButtonHistory()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	HistoryDlg hisDlg;
	//hisDlg.mapHistory = mapHistory;
	hisDlg.DoModal();


}

void CModbusTestingDlg::handlePassValue(CString passValue)
{
	m_edit_sendText.SetWindowTextA("");
	m_edit_sendText.SetWindowTextA(passValue);
}



void CModbusTestingDlg::OnBnClickedButtonClean()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_edit_log.SetWindowTextA("");
}

//����̨Կ�׿���״̬
string operationKeyArray[2] = { "�ر�","����" };
//��Ƶ��Ͳ״̬
string microphoneStatusArray[3] = { "����","����","ռ��" };
//�㲥ϵͳ����״̬
string paFaultStatusArray[2] = { "����","����" };
//�㲥��ռ��״̬
string partitionOccupancyArray[2] = { "����","ռ��" };
//����״̬
std::string strBroadcastStatus[7] = {
"�޹㲥", "�˹��㲥", "�ճ�Ԥ��㲥", "��ӹ㲥",
"TTS�㲥", "����", "����"
};
//�㲥����Ա��c����ʼ��
std::string pollOperate[21] = {
	"��","����ֵ������(�ܵ�)", "���Ļ���", "�����е�1", "�����е�2",
	"�����е�3", "Ԥ��", "Ԥ��", "Ԥ��",
	"Ԥ��", "Ԥ��", "Ԥ��", "��վ����",
	"Ԥ��", "�γ����޵���", "��վֵ��", "�г���վ�Զ��㲥",
	"Ԥ��", "Ԥ��", "Ԥ��", "Ԥ��"
};
std::string CModbusTestingDlg::pollingMsgParsing(uint8_t* polMsg)
{
	//char* strHeadMsg = { 0 };
	CString phoneticTypes;
	string strmega;
	CString strTempMsg;
	int n1 = 0, n2, n3, n4;
	int operationKey = 0;		//����̨Կ�׿���״̬
	int microphoneStatus = 0;	//��Ƶ��Ͳ״̬
	int paFaultStatus = 0;		//�㲥ϵͳ����״̬

	n1 = polMsg[10];
	operationKey = (n1 & 0x01);
	microphoneStatus = (n1 >> 1) & 0x03;
	paFaultStatus = (n1 >> 3) & 0x01;
	strTempMsg.Format("����̨:%s , ��Ƶ��Ͳ:%s , PAϵͳ:%s", operationKeyArray[operationKey].c_str(), microphoneStatusArray[microphoneStatus].c_str(), paFaultStatusArray[paFaultStatus].c_str());
	strmega.append(strTempMsg.GetBuffer());
	strmega.append("\r\n");
	strTempMsg.ReleaseBuffer();
	int j = 11;
	for (int i = 0; i < 32; i++)
	{
		int broadCastStatus;//����״̬
		int isOccupy;//�Ƿ�ռ��
		phoneticTypes = "";
		n1 = polMsg[j];   //01
		n2 = polMsg[++j]; //07
		n3 = polMsg[++j]; //04
		n4 = polMsg[++j]; //02
		j++;
		wchar_t wcharisOccupy = '\0';
		wcharisOccupy = ((n3 << 8) | (n4));
		broadCastStatus = (n2 >> 1) & 0x07;
		isOccupy = n2 & 0x01;
		
		strTempMsg.Format("\r\n[P%02d] -����״̬��%s , ���ȼ���%s , �㲥��״̬��%s", i + 1, (char*)strBroadcastStatus[broadCastStatus].c_str(), (char*)pollOperate[n1].c_str(), partitionOccupancyArray[isOccupy].c_str());
		if (broadCastStatus != 0)
		{
			int seg = wcharisOccupy;

			if (seg == 1025)
			{
				phoneticTypes = "          �㲥������: �ı�����";
			}
			else if (seg == 1026)
			{
				phoneticTypes = "          �㲥������: ��������";
			}
			else {
				phoneticTypes.Format("          �㲥������: Ԥ¼������ (ID: %d)", seg);
			}
			strmega.append(strTempMsg);
			strmega.append("\r\n");
			strmega.append(phoneticTypes);
		}
		else
		{
			strmega.append(strTempMsg);
		}
	}


	return strmega;
}

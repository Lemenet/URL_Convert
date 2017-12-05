
// URL_ConvertDlg.cpp : 实现文件
//

#include "stdafx.h"
#include <utility>
#include <map>
#include "URL_Convert.h"
#include "URL_ConvertDlg.h"
#include "StringHelper.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CURL_ConvertDlg 对话框



CURL_ConvertDlg::CURL_ConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_URL_CONVERT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CURL_ConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CURL_ConvertDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_ConvertButton, &CURL_ConvertDlg::OnBnClickedConvertbutton)
END_MESSAGE_MAP()


// CURL_ConvertDlg 消息处理程序

BOOL CURL_ConvertDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	((CButton*)GetDlgItem(IDC_bDeleteBack))->SetCheck(TRUE);

	((CComboBox*)GetDlgItem(IDC_TailList))->AddString(_T("&p"));
	((CComboBox*)GetDlgItem(IDC_TailList))->AddString(_T("html"));
	SetDlgItemText(IDC_TailList, _T("html"));

	InitURLCharacSet();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CURL_ConvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CURL_ConvertDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CURL_ConvertDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CURL_ConvertDlg::ConvertURLText()
{
	CString AimText;
	GetDlgItemText(IDC_RawString, AimText);
	CString ResultString = FindHttpWords(AimText);
	CString AimTail;
	GetDlgItemText(IDC_TailList,AimTail);
	
	if (((CButton*)GetDlgItem(IDC_bDeleteBack))->GetCheck())
	{
		ResultString = CutAfterTail(ResultString, AimTail);
	}
	else
	{
		ResultString = CutFromTail(ResultString, AimTail);
	}

	SetDlgItemText(IDC_ResultString, ResultString);
}

CString CURL_ConvertDlg::FindHttpWords(CString InText)
{
	if (InText.IsEmpty())
	{
		return CString("");
	}
	CString Result = InText;
	int AimIndex = StringHelper::FindSub(Result.GetBuffer(), "http", 2);		//需要跳过前几个字符开始查找
	if (AimIndex > 0)
	{
		Result = Result.Right(Result.GetLength() - AimIndex);
	}
	Result = SearchURLChar(Result);


	return Result;
}

void CURL_ConvertDlg::InitURLCharacSet()
{
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%20"), _T(" ")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%21"), _T("!")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%22"), _T("\"")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%23"), _T("#")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%24"), _T("$")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%25"), _T("%")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%26"), _T("&")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%27"), _T("\'")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%28"), _T("(")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%29"), _T(")")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2A"), _T("*")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2B"), _T("+")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2C"), _T(",")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2D"), _T("-")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2E"), _T(".")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2F"), _T("/")));
	
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2a"), _T("*")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2b"), _T("+")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2c"), _T(",")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2d"), _T("-")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2e"), _T(".")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%2f"), _T("/")));
												
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%30"), _T("0")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%31"), _T("1")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%32"), _T("2")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%33"), _T("3")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%34"), _T("4")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%35"), _T("5")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%36"), _T("6")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%37"), _T("7")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%38"), _T("8")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%39"), _T("9")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3A"), _T(":")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3B"), _T(";")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3C"), _T("<")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3D"), _T("=")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3E"), _T(">")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3F"), _T("?")));
													
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3a"), _T(":")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3b"), _T(";")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3c"), _T("<")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3d"), _T("=")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3e"), _T(">")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%3f"), _T("?")));
											
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%40"), _T("@")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%41"), _T("A")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%42"), _T("B")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%43"), _T("C")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%44"), _T("D")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%45"), _T("E")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%46"), _T("F")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%47"), _T("G")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%48"), _T("H")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%49"), _T("I")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4A"), _T("J")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4B"), _T("K")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4C"), _T("L")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4D"), _T("M")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4E"), _T("N")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4F"), _T("O")));
											
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4a"), _T("J")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4b"), _T("K")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4c"), _T("L")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4d"), _T("M")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4e"), _T("N")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%4f"), _T("O")));
										
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%50"), _T("P")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%51"), _T("Q")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%52"), _T("R")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%53"), _T("S")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%54"), _T("T")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%55"), _T("U")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%56"), _T("V")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%57"), _T("W")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%58"), _T("X")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%59"), _T("Y")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5A"), _T("Z")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5B"), _T("[")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5C"), _T("\\")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5D"), _T("]")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5E"), _T("^")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5F"), _T("_")));
												
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5a"), _T("Z")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5b"), _T("[")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5c"), _T("\\")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5d"), _T("]")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5e"), _T("^")));
	URLCharacSet.insert(std::make_pair<CString, CString>(_T("%5f"), _T("_")));

}

CString CURL_ConvertDlg::SearchURLChar(CString InString)
{
	CString Result = TEXT("");
	int CurrentIndex = InString.Find(_T("%"));
	int i = 0;
	CString Mark;
	while (i < InString.GetLength())
	{
		if (InString[i] != '%')
		{
			Result += InString[i];
			++i;
		}
		else
		{
			Mark += InString[i];
			Mark += InString[i + 1];
			Mark += InString[i + 2];
			Result += URLCharacSet[Mark];
			i += 3;
			Mark = "";
			if (i > InString.GetLength())
			{
				break;
			}
		}
	}

	return Result;
}



CString CURL_ConvertDlg::CutAfterTail(CString InString, CString AimTail)
{
	if (InString == "")
	{
		return InString;
	}
	int Index = StringHelper::FindSubReverse(InString.GetBuffer(), AimTail.GetBuffer());
	InString = InString.Left(Index + AimTail.GetLength());

	return InString;
}

CString CURL_ConvertDlg::CutFromTail(CString InString, CString AimTail)
{
	if (InString == "")
	{
		return InString;
	}
	int Index = StringHelper::FindSubReverse(InString.GetBuffer(), AimTail.GetBuffer());
	InString = InString.Left(Index);

	return InString;
}

void CURL_ConvertDlg::OnBnClickedConvertbutton()
{
	// TODO: 在此添加控件通知处理程序代码

	ConvertURLText();

}

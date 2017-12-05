
// URL_ConvertDlg.h : 头文件
//

#pragma once
#include <map>

// CURL_ConvertDlg 对话框
class CURL_ConvertDlg : public CDialogEx
{
// 构造
public:
	CURL_ConvertDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URL_CONVERT_DIALOG };
#endif

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

// 属性
private:

	// URL对应的字符配对
	std::map<CString, CString> URLCharacSet;

	/* 私有函数 */
private:

	/* 将TxtB_Source当中的文字转换为过滤后的URL地址并且设置到TxtB_Result当中 */
	void ConvertURLText();

	/* Widget的属性 */
public:

	/* 查找http字符串，确定真正的网址开头，从下标为2的位置开始查找，过滤掉第一个http字符串 */
	CString FindHttpWords(CString InText);

	/* 初始化URLCharacSet当中存储的键值 */
	void InitURLCharacSet();

	/* 转换InString当中的URL转义字符
	* 在URLCharacSet当中通过%XX的键值去查找所对应的字母 */
	CString SearchURLChar(CString InString);

	/* 去掉tail字符以后的文字（有些情况在.html之后还有一些包裹的修饰符，需要去除html开始以后的文字） */
	CString CutAfterTail(CString InString, CString AimTail = _T("html"));

	/* 去掉tail对应字符串开始往后的文字（有时网站是以&p结尾，但是&p不属于网址） */
	CString CutFromTail(CString InString, CString AimTail = _T("html"));

	afx_msg void OnBnClickedConvertbutton();
};

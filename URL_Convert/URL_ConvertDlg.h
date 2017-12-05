
// URL_ConvertDlg.h : ͷ�ļ�
//

#pragma once
#include <map>

// CURL_ConvertDlg �Ի���
class CURL_ConvertDlg : public CDialogEx
{
// ����
public:
	CURL_ConvertDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_URL_CONVERT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

// ����
private:

	// URL��Ӧ���ַ����
	std::map<CString, CString> URLCharacSet;

	/* ˽�к��� */
private:

	/* ��TxtB_Source���е�����ת��Ϊ���˺��URL��ַ�������õ�TxtB_Result���� */
	void ConvertURLText();

	/* Widget������ */
public:

	/* ����http�ַ�����ȷ����������ַ��ͷ�����±�Ϊ2��λ�ÿ�ʼ���ң����˵���һ��http�ַ��� */
	CString FindHttpWords(CString InText);

	/* ��ʼ��URLCharacSet���д洢�ļ�ֵ */
	void InitURLCharacSet();

	/* ת��InString���е�URLת���ַ�
	* ��URLCharacSet����ͨ��%XX�ļ�ֵȥ��������Ӧ����ĸ */
	CString SearchURLChar(CString InString);

	/* ȥ��tail�ַ��Ժ�����֣���Щ�����.html֮����һЩ���������η�����Ҫȥ��html��ʼ�Ժ�����֣� */
	CString CutAfterTail(CString InString, CString AimTail = _T("html"));

	/* ȥ��tail��Ӧ�ַ�����ʼ��������֣���ʱ��վ����&p��β������&p��������ַ�� */
	CString CutFromTail(CString InString, CString AimTail = _T("html"));

	afx_msg void OnBnClickedConvertbutton();
};

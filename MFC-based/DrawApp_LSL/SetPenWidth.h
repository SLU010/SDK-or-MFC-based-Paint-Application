#pragma once


// CSetPenWidth �Ի���

class CSetPenWidth : public CDialogEx
{
	DECLARE_DYNAMIC(CSetPenWidth)

public:
	CSetPenWidth(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CSetPenWidth();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEN_WIDTH };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	// ���С��5
	UINT m_width;
public:
	UINT getWidth() { return m_width; }
	VOID setWidth(int x) { m_width = x; }
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};

#pragma once


// CEraser �Ի���

class CEraser : public CDialogEx
{
	DECLARE_DYNAMIC(CEraser)

public:
	CEraser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CEraser();
	
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ERASER };
#endif
public:
	UINT m_size;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRadio3();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
};

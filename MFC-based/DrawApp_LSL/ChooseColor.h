#pragma once


// CChooseColor �Ի���

class CChooseColor : public CDialogEx
{
	DECLARE_DYNAMIC(CChooseColor)

public:
	CChooseColor(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChooseColor();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

private:
	COLORREF m_color;
public:
	COLORREF getColor() { return m_color; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPenColorchoose();
};

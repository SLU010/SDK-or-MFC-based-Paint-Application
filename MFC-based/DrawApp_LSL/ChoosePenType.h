#pragma once


// CChoosePenType �Ի���

class CChoosePenType : public CDialogEx
{
	DECLARE_DYNAMIC(CChoosePenType)

public:
	CChoosePenType(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CChoosePenType();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PEN_TYPE };
#endif
private:
	UINT select;
public:
	VOID InitDialog()
	{
		/*CButton* radio = (CButton*)GetDlgItem(IDC_SOLID);
		radio->SetCheck(1);*/
	}
	UINT getType() { return select; }
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClickedDash();
	afx_msg void OnClickedDashdot();
	afx_msg void OnClickedDashdotdot();
	afx_msg void OnClickedDot();
	afx_msg void OnClickedSolid();
};

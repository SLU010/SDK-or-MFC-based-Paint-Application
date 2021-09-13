#pragma once
#include "Fig.h"
class CMyText :public CFig
{
private:
	TCHAR m_szText[128];
public:
	CMyText();
	virtual ~CMyText();
	virtual BOOL Draw(CDC*);
	TCHAR *getText() { return m_szText; }
	VOID setText(CString s) { strcpy_s(m_szText, s); }
	virtual VOID Save(CArchive &ar);
	virtual VOID Load(CArchive &ar);
};


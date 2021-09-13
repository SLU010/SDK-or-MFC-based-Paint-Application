#pragma once
#include"User1.h"
#include"User2.h"
#include"User3.h"

// CSheet

class CSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CSheet)
private:
	CUser1 m_user1;
	CUser2 m_user2;
	CUser3 m_user3;
public:
	CSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CSheet();

protected:
	DECLARE_MESSAGE_MAP()
};



#include "stdafx.h"
#include "MyFree.h"
#include"AllTypeNum.h"

CMyFree::CMyFree()
{
	setFigType(DRAW_MODE_FREE);
	
}


CMyFree::~CMyFree()
{
	
}

BOOL CMyFree::Draw(CDC* pDC)
{
	CPen pen;
	CPen *pOldPen;
	pen.CreatePenIndirect(&getLogPen());
	pOldPen = pDC->SelectObject(&pen);

	pDC->MoveTo(m_pt.GetAt(0));
	for(int i=0;i<m_pt.GetSize();i++)
		pDC->LineTo(m_pt.GetAt(i));

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();
	return TRUE;
}
VOID CMyFree::Save(CArchive &ar)
{
	ar << m_pt.GetSize();
	for (int i = 0; i < m_pt.GetSize(); i++)
		ar << m_pt.GetAt(i);
	ar  << getLogPen().lopnColor << getLogPen().lopnStyle
		<< getLogPen().lopnWidth;
}
VOID CMyFree::Load(CArchive &ar)
{
	LOGPEN logP;
	int count = 0;
	ar >> count;
	CPoint *pt = new CPoint[count];
	for (int i = 0; i < count; i++)
		ar >> *(pt + i);
	for (int i = 0; i < count; i++)
		m_pt.Add(*(pt+i));
	ar  >> logP.lopnColor >> logP.lopnStyle
		>> logP.lopnWidth;
	setLogPen(logP);
}
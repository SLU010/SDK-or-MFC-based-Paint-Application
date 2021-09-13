#include "stdafx.h"
#include "MyLine.h"
#include"AllTypeNum.h"

CMyLine::CMyLine()
{
	//m_logPen.lopnColor = RGB(0, 0, 0);
	//m_logPen.lopnStyle = PS_SOLID;
	//m_logPen.lopnWidth.x = 1;
	setFigType(DRAW_MODE_LINE);
}


CMyLine::~CMyLine()
{
}


BOOL CMyLine::Draw(CDC *pDC)
{
	CPen pen;
	CPen *pOldPen;
	pen.CreatePenIndirect(&getLogPen());
	pOldPen=pDC->SelectObject(&pen);

	pDC->MoveTo(getPtS());
	pDC->LineTo(getPtE());

	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();

	return TRUE;
}
VOID CMyLine::Save(CArchive& ar)
{
	ar << getPtS() << getPtE()
		<< getLogPen().lopnColor << getLogPen().lopnStyle<< getLogPen().lopnWidth;
	//ar.Write(&getLogPen(), sizeof(getLogPen()));
}
VOID CMyLine::Load(CArchive& ar)
{
	LOGPEN logP;
	CPoint ptS, ptE;
	ar >> ptS >> ptE>>logP.lopnColor>>logP.lopnStyle
		>>logP.lopnWidth;
	setPtS(ptS);
	setPtE(ptE);
	setLogPen(logP);
	
}
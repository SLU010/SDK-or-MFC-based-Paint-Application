#include "stdafx.h"
#include "MyEllipse.h"
#include"AllTypeNum.h"

CMyEllipse::CMyEllipse()
{
	//m_logBrush.lbColor = RGB(255, 255, 255);
	//m_logBrush.lbHatch = 0;
	//m_logBrush.lbStyle = BS_SOLID;

	//m_logPen.lopnColor = RGB(0, 0, 0);
	//m_logPen.lopnStyle = PS_SOLID;
	//m_logPen.lopnWidth.x = 1;
	setFigType(DRAW_MODE_ELLIPSE);
}


CMyEllipse::~CMyEllipse()
{
}

BOOL CMyEllipse::Draw(CDC *pDC)
{
	CBrush brush;
	CBrush *oldBrush;
	CRect rect;
	CPen pen;
	CPen *pOldPen;

	pen.CreatePenIndirect(&getLogPen());
	pOldPen = pDC->SelectObject(&pen);
	brush.CreateBrushIndirect(&getLogBrush());
	oldBrush = pDC->SelectObject(&brush);

	rect.SetRect(getPtS(), getPtE());
	pDC->Ellipse(rect);

	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	oldBrush->DeleteObject();
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();

	return TRUE;
}

VOID CMyEllipse::Save(CArchive& ar)
{
	ar << getPtS() << getPtE() << getLogPen().lopnColor << getLogPen().lopnStyle
		<< getLogPen().lopnWidth << getLogBrush().lbColor << getLogBrush().lbHatch << getLogBrush().lbStyle;
}
VOID CMyEllipse::Load(CArchive& ar)
{
	LOGPEN logP;
	LOGBRUSH logB;
	CPoint ptS, ptE;
	ar >> ptS >> ptE >> logP.lopnColor >> logP.lopnStyle
		>> logP.lopnWidth >> logB.lbColor >> logB.lbHatch >> logB.lbStyle;
	setPtS(ptS);
	setPtE(ptE);
	setLogPen(logP);
	setLogBrush(logB);

}
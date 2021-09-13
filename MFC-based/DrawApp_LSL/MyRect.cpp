#include "stdafx.h"
#include "MyRect.h"
#include"AllTypeNum.h"

CMyRect::CMyRect()
{
	setFigType(DRAW_MODE_RECT);
}


CMyRect::~CMyRect()
{
}

BOOL CMyRect::Draw(CDC *pDC)
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
	pDC->Rectangle(rect);

	pDC->SelectObject(oldBrush);
	brush.DeleteObject();
	oldBrush->DeleteObject();
	pDC->SelectObject(pOldPen);
	pen.DeleteObject();
	pOldPen->DeleteObject();

	return TRUE;
}
VOID CMyRect::Save(CArchive &ar)
{
	ar << getPtS() << getPtE() << getLogPen().lopnColor << getLogPen().lopnStyle
		<< getLogPen().lopnWidth << getLogBrush().lbColor << getLogBrush().lbHatch << getLogBrush().lbStyle;
}
VOID CMyRect::Load(CArchive &ar) 
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
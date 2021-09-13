#include "stdafx.h"
#include "MyText.h"
#include"AllTypeNum.h"

CMyText::CMyText()
{
	setFigType(DRAW_MODE_TEXT);
}


CMyText::~CMyText()
{
}

BOOL CMyText::Draw(CDC* pDC)
{
	CFont font;
	CFont *oldFont;
	CRect rect;
	CPoint ptE;
	CSize size;
	font.CreateFontIndirectA(&getLogFont());
	oldFont=pDC->SelectObject(&font);
	pDC->SetTextColor(getTextColor());
	/*ptE.x = getPtS().x;
	ptE.y = getPtS().y;
	rect.SetRect(getPtS(), ptE);*/
	pDC->TextOut(getPtS().x, getPtS().y, m_szText);
	size = pDC->GetTextExtent(m_szText, strlen(m_szText));//获得文本的长度
	int nWidth = size.cx;
	ptE.x = getPtS().x + nWidth;//计算文本的长度 方便框八爪鱼
	ptE.y = getPtS().y + fabs(getLogFont().lfHeight+2);
	setPtE(ptE);
	//pDC->DrawText(m_szText, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	pDC->SelectObject(&oldFont);
	font.DeleteObject();
	oldFont->DeleteObject();
	return TRUE;
}
VOID CMyText::Save(CArchive &ar)
{
	CString string = getLogFont().lfFaceName;
	ar << getPtS() << getTextColor() << 
		string <<
		getLogFont().lfCharSet <<
		getLogFont().lfClipPrecision <<
		getLogFont().lfEscapement <<
		getLogFont().lfHeight <<
		getLogFont().lfItalic <<
		getLogFont().lfOrientation <<
		getLogFont().lfOutPrecision <<
		getLogFont().lfPitchAndFamily <<
		getLogFont().lfQuality <<
		getLogFont().lfStrikeOut <<
		getLogFont().lfUnderline <<
		getLogFont().lfWeight <<
		getLogFont().lfWidth;
	ar.Write(m_szText, 128);
}
VOID CMyText::Load(CArchive &ar)
{
	CPoint ptS;
	LOGFONT font;
	CString string;
	COLORREF color;
	ar >> ptS >> color >> 
		string >> 
		font.lfCharSet >>
		font.lfClipPrecision >>
		font.lfEscapement >>
		font.lfHeight >>
		font.lfItalic >>
		font.lfOrientation >>
		font.lfOutPrecision >>
		font.lfPitchAndFamily >>
		font.lfQuality >>
		font.lfStrikeOut >>
		font.lfUnderline >>
		font.lfWeight >>
		font.lfWidth;
	strcpy_s(font.lfFaceName, string);
	ar.Read(m_szText, 128);
	setPtS(ptS);
	setTextColor(color);
	setTextFont(font);
}
#include "stdafx.h"
#include "Fig.h"
#include"AllTypeNum.h"

CFig::CFig()
{
	m_select = FALSE;
	m_ptS = { 0,0 };
	m_ptE = { 0,0 };

	m_logBrush.lbColor = RGB(255, 255, 255);
	m_logBrush.lbHatch = 0;
	m_logBrush.lbStyle = BS_SOLID;

	m_logPen.lopnColor = RGB(0, 0, 0);
	m_logPen.lopnStyle = PS_SOLID;
	m_logPen.lopnWidth.x = 1;

	m_figType = DRAW_MODE_SELECT;
	m_memoryTimes = 1;

	m_textColor = RGB(0, 0, 0);
	memset(&m_logFont, 0, sizeof(LOGFONT));
	strcpy_s(m_logFont.lfFaceName, "ËÎÌו");
	m_logFont.lfWeight = 16;
	m_logFont.lfHeight = 16;
}


CFig::~CFig()
{
}

//BOOL CFig::Draw(CDC* pDC)
//{
//	pDC->Rectangle(200, 200, 300, 400);
//	return TRUE;
//}


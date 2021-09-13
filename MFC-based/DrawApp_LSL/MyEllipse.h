#pragma once
#include "Fig.h"
class CMyEllipse :public CFig
{
//private:
//	LOGBRUSH m_logBrush;
//	LOGPEN m_logPen;
public:
	CMyEllipse();
	virtual ~CMyEllipse();
	virtual BOOL Draw(CDC*);
	virtual VOID Save(CArchive &ar);
	virtual VOID Load(CArchive &ar);
	//LOGBRUSH getLogBrush() { return m_logBrush; }
	//VOID setLogBrush(LOGBRUSH brush) { m_logBrush = brush; }
	//LOGPEN getLogPen() { return m_logPen; }
	//VOID setLogPen(LOGPEN logPen) { m_logPen = logPen; }
};


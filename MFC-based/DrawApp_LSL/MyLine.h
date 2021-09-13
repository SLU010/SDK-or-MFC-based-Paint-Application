#pragma once
#include "Fig.h"
class CMyLine :public CFig
{
//private:
//	LOGPEN m_logPen;
public:
	CMyLine();
	virtual ~CMyLine();
	//LOGPEN getLogPen() { return m_logPen; }
	//VOID setLogPen(LOGPEN logPen) { m_logPen = logPen; }
	virtual BOOL Draw(CDC*);
	virtual VOID Save(CArchive &ar);
	virtual VOID Load(CArchive &ar);
};


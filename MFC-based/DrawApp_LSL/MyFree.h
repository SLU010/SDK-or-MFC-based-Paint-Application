#pragma once
#include "Fig.h"
class CMyFree : public CFig
{
public:
	CArray<CPoint, CPoint&> m_pt;
public:
	CMyFree();
	virtual ~CMyFree();
	virtual BOOL Draw(CDC*);
	virtual VOID Save(CArchive &ar);
	virtual VOID Load(CArchive &ar);
};


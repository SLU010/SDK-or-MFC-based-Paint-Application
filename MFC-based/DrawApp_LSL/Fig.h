#pragma once

class CFig
{
private:
	CPoint m_ptS;
	CPoint m_ptE;
	BOOL m_select;
	LOGBRUSH m_logBrush;
	LOGPEN m_logPen;
	UINT m_figType;
	UINT m_memoryTimes;
	LOGFONT m_logFont;
	COLORREF m_textColor;
public:
	CFig();
	virtual ~CFig();
	CPoint getPtS() { return m_ptS; }
	CPoint getPtE() { return m_ptE; }
	BOOL getSelect(){ return m_select; }
	UINT getFigType() { return m_figType; }
	UINT getMemoryTimes() { return m_memoryTimes; }
	VOID setMemoryTimes(UINT x) { m_memoryTimes = x; }
	VOID setPtS(CPoint pt) { m_ptS = pt; }
	VOID setPtE(CPoint pt) { m_ptE = pt; }
	VOID setSelect(BOOL flag) { m_select = flag; }
	LOGBRUSH getLogBrush() { return m_logBrush; }
	VOID setLogBrush(LOGBRUSH brush) { m_logBrush = brush; }
	LOGPEN getLogPen() { return m_logPen; }
	VOID setLogPen(LOGPEN logPen) { m_logPen = logPen; }
	VOID setPenColor(COLORREF color) { m_logPen.lopnColor = color; }
	VOID setBrushColor(COLORREF color) { m_logBrush.lbColor = color; }
	VOID setLineType(UINT type) { m_logPen.lopnStyle = type; }
	VOID setLineWidth(UINT width) { m_logPen.lopnWidth.x = width; }
	VOID setFigType(UINT type) { m_figType = type; }
	LOGFONT getLogFont() { return m_logFont; }
	COLORREF getTextColor() { return m_textColor; }
	VOID setTextFont(LOGFONT font) { m_logFont = font; }
	VOID setTextColor(COLORREF color) { m_textColor = color; }
	virtual BOOL Draw(CDC*) = 0;
	virtual VOID Save(CArchive &ar) = 0;
	virtual VOID Load(CArchive &ar) = 0;
};


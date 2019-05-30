#pragma once

#include <afxtempl.h>

struct CParagraphInstant
{
	CParagraphInstant():color(0),pageFromStart(0){hitRect.SetRectEmpty();}
	CString sParagraph;
	CString sArg;
	CRect hitRect;
	COLORREF color;
	int pageFromStart;
};

struct CParagraphArr :public CArray<CParagraphInstant, CParagraphInstant&>
{
	CParagraphArr(){}
	CParagraphArr(CParagraphArr& ob){*this = ob;}
	CParagraphArr& operator = (CParagraphArr& ob)
	{
		Copy(ob);
		return *this;
	}
};

struct CChapPage
{
	CChapPage& operator = (CChapPage& ob)
	{
		page = ob.page;
		startY = ob.startY;
		sChap = ob.sChap;
		paragraphs = ob.paragraphs;
		return *this;
	}
	CChapPage(CChapPage& ob){*this = ob;}
	CChapPage():page(0),startY(0){}
	int page;
	int startY;
	CString sChap;
	CParagraphArr paragraphs;
};

typedef CArray<CChapPage, CChapPage&> CChapPageArr;

// CChaptersParagraphs command target

class CChaptersParagraphs : public CObject
{
public:
	DECLARE_SERIAL( CChaptersParagraphs )
	CChaptersParagraphs();
	virtual ~CChaptersParagraphs();
public:
	virtual void Serialize(CArchive& archive);
public:
	void Save(CArchive& archive);
public:
	void Load(CArchive& archive);

	CChapPageArr m_chapPageArr;
};



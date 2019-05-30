// ChaptersParagraphs.cpp : implementation file
//

#include "stdafx.h"
#include "TabsFrame.h"
#include "ChaptersParagraphs.h"


// CChaptersParagraphs
IMPLEMENT_SERIAL( CChaptersParagraphs, CObject, 1 )

CChaptersParagraphs::CChaptersParagraphs()
{
}

CChaptersParagraphs::~CChaptersParagraphs()
{
}


// CChaptersParagraphs member functions

void CChaptersParagraphs::Serialize(CArchive& archive)
{
    // call base class function first
    // base class is CObject in this case
    CObject::Serialize( archive );

    // now do the stuff for our specific class
    if( archive.IsStoring() )
        Save(archive);// << m_name << m_number;
    else
        Load(archive);// >> m_name >> m_number;
}

void CChaptersParagraphs::Save(CArchive& archive)
{
	int size = (int)m_chapPageArr.GetCount();
	archive << size;
	for(int i = 0; i < size; ++i)
	{
		CChapPage &cp = m_chapPageArr[i];
		int paragrapSize = (int)cp.paragraphs.GetCount();
		archive << cp.page << cp.startY << cp.sChap << paragrapSize;
		for(int j = 0; j < paragrapSize; ++j)
		{
			CParagraphInstant &pi = cp.paragraphs[j];
			archive << pi.sParagraph << pi.sArg << pi.hitRect << pi.color << pi.pageFromStart;
		}
	}
}

void CChaptersParagraphs::Load(CArchive& archive)
{
	m_chapPageArr.RemoveAll();
	int size = 0;
	archive >> size;

	for(int i = 0; i < size; ++i)
	{
		int paragrapSize = 0;
		CChapPage cp;
		archive >> cp.page >> cp.startY >> cp.sChap >> paragrapSize;
		for(int j = 0; j < paragrapSize; ++j)
		{
			CParagraphInstant pi;
			archive >> pi.sParagraph >> pi.sArg >> pi.hitRect >> pi.color >> pi.pageFromStart;
			cp.paragraphs.Add(pi);
		}
		m_chapPageArr.Add(cp);
	}
}

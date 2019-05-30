#include "StdAfx.h"
#include "TabsFrame.h"
#include "Slider.h"

CSlider::CSlider(CView *pView, CRect rc, CSlider::types type)
: m_rc(rc)
, m_type(type)
, m_pView(pView)
, m_pt(0)
, m_lastpos(0)
, m_bNotDefaultColor(false)
, m_bkColor(0)
, m_frameColor(0)
, m_rcDeflate(0,0,0,0)
, m_sCaption(_T(""))
, m_nTopCapHieght(80)
, m_nBotCapHieght(80)
, m_minVal(0)
, m_maxVal(0)
, m_nFontSize(-20)
, m_sFaceName(_T("Guttman Stam"))
, m_stepsToVal(0)
, m_turn(0)
, m_textColor(0)
, m_sFormatResult(_T("%.0f"))
, m_left(15)
, m_right(15)
, m_rangeTop(1000000)
, m_rangeBottom(-10000000)
{
	switch(m_type)
	{
	case simpleVertical:
		m_pt = m_rc.CenterPoint();
		break;
	case VerCaptionResultMazalot:
		m_pt.y = m_rc.bottom - m_nBotCapHieght;
		m_rangeTop = m_maxVal = 360.0;
		m_lastpos = m_pt.y;
		m_stepsToVal = 
			m_maxVal / (double)((m_rc.bottom - m_nBotCapHieght) - 
			(m_rc.top + m_nTopCapHieght));
		break;
	case VerMin90Plus90:
		m_pt = m_rc.CenterPoint();
		m_rangeTop = m_maxVal = 90.0;
		m_rangeBottom = m_minVal = -90.0;
		m_lastpos = m_pt.y;
		m_stepsToVal = 
			(m_maxVal - m_minVal) / (double)((m_rc.bottom - m_nBotCapHieght) - 
			(m_rc.top + m_nTopCapHieght));
		break;
	case simpleHorizontal360:
		m_pt.x = m_rc.left + m_left;
		m_maxVal = 360.0;
		m_lastpos = m_pt.x;
		m_stepsToVal = 
			m_maxVal / (double)((m_rc.right - m_right) - (m_rc.left + m_left));
		break;
	case simpleHorizontal:
		m_pt = m_rc.CenterPoint();
		m_left = m_right = 30;
		m_maxVal = 180.0;
		m_minVal = -180.0;
		m_lastpos = m_pt.x;
		m_stepsToVal = 
			(m_maxVal - m_minVal) / (double)((m_rc.right - m_right) - (m_rc.left + m_left));
		break;
	}
}

CSlider::~CSlider(void)
{
}

void CSlider::AddButtonId(unsigned int id)
{
	m_onButtonsShow.Add(id);
}

void CSlider::InitOnSubHeadButton(void)
{
	UINT id = (UINT)m_pView->SendMessage(WM_GET_WND_SUBTYPE);
	bool bIsOneOfId = IsOneOfId(id);
	if(bIsOneOfId)
	{
		PaintBk();
		m_textColor = GetDefaultColor();
		CClientDC dc(m_pView);
		m_pView->OnPrepareDC(&dc);
		Paint(dc);
		PaintResult(dc);
		PaintPos(m_lastpos, dc);
	}
}

bool CSlider::IsOneOfId(unsigned int id)
{
	int size = (int)m_onButtonsShow.GetSize();
	if(size == 0)
		return true;

	for(int i = 0; i < size; ++i)
		if(m_onButtonsShow[i] == id)
			return true;

	return false;
}

void CSlider::Init(void)
{
	CClientDC dc(m_pView);
	COLORREF color = m_bNotDefaultColor? m_frameColor : GetDefaultColor();
	
	CBrush br(color);
	CRect rc(0,0,m_rc.Width(), m_rc.Height());

	switch(m_type)
	{
	case simpleVertical:
		m_memDc.CreateCompatibleDC(&dc);
		m_memBm.CreateCompatibleBitmap(&dc, m_rc.Width(), m_rc.Height());
		m_memDc.SelectObject(&m_memBm);
		break;
	case VerCaptionResultMazalot:
		{
			m_memDc.CreateCompatibleDC(&dc);
			m_memBm.CreateCompatibleBitmap(&dc, m_rc.Width(), m_rc.Height());
			m_memDc.SelectObject(&m_memBm);
			CreateFont();
			m_bmMazalot.LoadBitmap(IDB_BITMAP_MAZALOT);
			m_dcMazalot.CreateCompatibleDC(&dc);
			m_dcMazalot.SelectObject(&m_bmMazalot);
		}
		break;
	case VerMin90Plus90:
		{
			m_memDc.CreateCompatibleDC(&dc);
			m_memBm.CreateCompatibleBitmap(&dc, m_rc.Width(), m_rc.Height());
			m_memDc.SelectObject(&m_memBm);
			CreateFont();
		}
		break;
	case simpleHorizontal360:
		{
			m_memDc.CreateCompatibleDC(&dc);
			m_memBm.CreateCompatibleBitmap(&dc, m_rc.Width(), m_rc.Height());
			m_memDc.SelectObject(&m_memBm);
			CreateFont();
		}
		break;
	case simpleHorizontal:
		{
			m_memDc.CreateCompatibleDC(&dc);
			m_memBm.CreateCompatibleBitmap(&dc, m_rc.Width(), m_rc.Height());
			m_memDc.SelectObject(&m_memBm);
			CreateFont();
		}
		break;
	}
}

unsigned long CSlider::GetDefaultColor(void)
{
	UINT id = (UINT)m_pView->SendMessage(WM_GET_WND_SUBTYPE);
	UINT idx = (UINT)m_pView->SendMessage(WM_GET_IDX_PEREK);
	CChapPage &cp = theApp.m_chaptersParagraphs.m_chapPageArr[idx];
	COLORREF color = cp.paragraphs[id].color;
	return color;
}

void CSlider::SetDeflate(int left, int top, int right, int bottom)
{
	m_rcDeflate.SetRect(left,top,right, bottom);
}

void CSlider::Deflate(CRect& rc)
{
	rc.DeflateRect(m_rcDeflate.left,m_rcDeflate.top,m_rcDeflate.right,m_rcDeflate.bottom);
}

void CSlider::Paint(CClientDC& dc)
{
	dc.BitBlt(m_rc.left,
		m_rc.top,m_rc.Width(),m_rc.Height(),
		&m_memDc,0,0,SRCCOPY);
}

bool CSlider::PtInRect(CPoint& p, double& turn, bool bReversed)
{
	if(m_rc.PtInRect(p) == FALSE)
		return false;
	switch(m_type)
	{
	case simpleVertical:
		turn = p.y - m_pt.y;
		break;
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		if(p.y < (m_rc.top + m_nTopCapHieght))
			p.y = m_rc.top + m_nTopCapHieght;
		else if(p.y > (m_rc.bottom - m_nBotCapHieght))
			p.y = m_rc.bottom - m_nBotCapHieght;
		turn = m_pt.y - p.y;
		turn *= m_stepsToVal;
		if(m_pt.y == m_rc.bottom - m_nBotCapHieght)
			turn += m_minVal;
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		if(p.x < (m_rc.left + m_left))
			p.x = m_rc.left + m_left;
		else if(p.x > (m_rc.right - m_right))
			p.x = m_rc.right - m_right;
		turn = p.x - m_pt.x;
		turn *= m_stepsToVal;
		if(m_pt.x == m_rc.left + m_left)
			turn += m_minVal; 
		break;
	}

	if(bReversed)
		turn = -turn;
	m_turn = turn;
	
	switch(m_type)
	{
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		{
			CClientDC dc(m_pView);
			m_pView->OnPrepareDC(&dc);
			CleanPos(dc);
			if(turn > m_rangeTop)
			{
				m_turn = turn = SetVal(m_rangeTop);
				p.y = m_lastpos;
			}
			else if(turn < m_rangeBottom)
			{
				m_turn = turn = SetVal(m_rangeBottom);
				p.y = m_lastpos;
			}
			else
			{
				m_lastpos = p.y;
			}
			PaintResult(dc);
			PaintPos(p.y,dc);
		}
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		{
			CClientDC dc(m_pView);
			m_pView->OnPrepareDC(&dc);
			CleanPos(dc);
			PaintResult(dc);
			PaintPos(p.x,dc);
			m_lastpos = p.x;
		}
		break;
	}
	return true;
}

void CSlider::SetCaption(const CString& str)
{
	m_sCaption = str;
}

void CSlider::CreateFont(void)
{
	VERIFY(m_font.CreateFont(
		m_nFontSize,              // nHeight
		0,                       // nWidth
		0,                       // nEscapement
		0,                       // nOrientation
		FW_SEMIBOLD,               // nWeight
		FALSE,                   // bItalic
		FALSE,                   // bUnderline
		0,                       // cStrikeOut
		HEBREW_CHARSET,          // nCharSet
		OUT_CHARACTER_PRECIS,      // nOutPrecision
		CLIP_CHARACTER_PRECIS,     // nClipPrecision
		PROOF_QUALITY,         // nQuality
		DEFAULT_PITCH | FF_SWISS,// nPitchAndFamily
		m_sFaceName));        // lpszFacename
}

void CSlider::PaintPos(int pos, CClientDC& dc)
{
	CPen* op = dc.SelectObject(&m_pen);
	CRect d = m_rcDeflate;

	switch(m_type)
	{
	case simpleVertical:
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		dc.MoveTo(m_rc.left + (10 + d.left),pos);
		dc.LineTo(m_rc.right - (10 + d.right), pos);
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		dc.MoveTo(pos,m_rc.top + 10 + m_rcDeflate.top);
		dc.LineTo(pos, m_rc.bottom - 10 - m_rcDeflate.bottom);
		break;
	}

	dc.SelectObject(op);
}

void CSlider::CleanPos(CClientDC& dc)
{
	CRect d = m_rcDeflate;
	switch(m_type)
	{
	case simpleVertical:
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		dc.BitBlt(m_rc.left+(3 + d.left),
			m_lastpos-1,m_rc.Width()-(6 + d.left + d.right),3,
			&m_memDc,(3 + d.left),m_lastpos-m_rc.top,SRCCOPY);
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		dc.BitBlt(m_lastpos-1,m_rc.top+3+m_rcDeflate.top,3,
			m_rc.Height() - (6+m_rcDeflate.top+m_rcDeflate.bottom),
			&m_memDc,m_lastpos - m_rc.left,3+m_rcDeflate.top,SRCCOPY);
		break;
	}
}

void CSlider::PaintResult(CClientDC& dc)
{
	dc.SetBkMode(TRANSPARENT);
	CFont *pOFont = dc.SelectObject(&m_font);
	CRect rc = m_rc;
	CString sRes;
	sRes.Format(m_sFormatResult,m_turn);
	COLORREF color = dc.SetTextColor(m_textColor);

	switch(m_type)
	{
	case simpleVertical:
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		rc.top = rc.bottom - (m_nBotCapHieght * 2 / 3);
		rc.DeflateRect(4 + (m_rcDeflate.left + m_rcDeflate.right)/2,6);
		dc.FillSolidRect(rc,m_bkColor);
		dc.DrawText(sRes, rc, 
			DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
		break;
	case simpleHorizontal360:
		{
			int deflate = (rc.Width() - 80) / 2;
			int minTop = rc.Height()/2;
			rc.DeflateRect(deflate,minTop, deflate, 3 + m_rcDeflate.bottom);
			dc.FillSolidRect(rc,m_bkColor);
			dc.DrawText(sRes, rc, 
				DT_CENTER | DT_WORDBREAK | /*DT_TOP | */DT_RTLREADING);
		}
		break;
	}



	dc.SetTextColor(color);
	dc.SelectObject(pOFont);
}

void CSlider::PaintBk(void)
{
	COLORREF color = m_bNotDefaultColor? m_frameColor : GetDefaultColor();
	
	CBrush br(color);
	CRect rc(0,0,m_rc.Width(), m_rc.Height());

	switch(m_type)
	{
	case simpleHorizontal:
		m_pen.DeleteObject();
		m_pen.CreatePen(PS_SOLID, 1, color);
	case simpleVertical:
		m_memDc.FillSolidRect(m_rc,m_bkColor);
		Deflate(rc);
		m_memDc.FrameRect(rc, &br);
		break;
	case VerCaptionResultMazalot:
		{
			CFont *pOFont = m_memDc.SelectObject(&m_font);
			m_pen.DeleteObject();
			m_pen.CreatePen(PS_SOLID, 1, color);
			m_memDc.FillSolidRect(m_rc,m_bkColor);
			Deflate(rc);
			m_memDc.FrameRect(rc, &br);
			m_memDc.SetTextColor(color);
			CRect rc2(3,5,m_rc.Width()-3,m_nTopCapHieght);
			Deflate(rc2);
			m_memDc.DrawText(m_sCaption, rc2, 
				DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
			m_memDc.SelectObject(pOFont);

			double mazHight = 
				(double)(m_rc.Height() - (m_nBotCapHieght + m_nTopCapHieght)) / 12.0;
			double memPos = m_rc.Height() - (m_nBotCapHieght + 26);
			int yMaz = 0;
			int xPos = (m_rc.Width() - 60) / 2;
			for(int i = 0; i < 12; ++i, yMaz += 26, memPos -= mazHight)
			{
				int nPos = (int)memPos;
				m_memDc.BitBlt(xPos,nPos,60,26,&m_dcMazalot,20,yMaz,SRCCOPY );
			}
		}
		break;
	case VerMin90Plus90:
		{
			CFont *pOFont = m_memDc.SelectObject(&m_font);
			m_pen.DeleteObject();
			m_pen.CreatePen(PS_SOLID, 1, color);
			m_memDc.FillSolidRect(m_rc,m_bkColor);
			Deflate(rc);
			m_memDc.FrameRect(rc, &br);
			m_memDc.SetTextColor(color);
			CRect rc2(3,5,m_rc.Width()-3,m_nTopCapHieght);
			Deflate(rc2);
			m_memDc.DrawText(m_sCaption, rc2, 
				DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
			m_memDc.SelectObject(pOFont);
		}
		break;
	case simpleHorizontal360:
		{
			CFont *pOFont = m_memDc.SelectObject(&m_font);
			m_pen.DeleteObject();
			m_pen.CreatePen(PS_SOLID, 1, color);
			m_memDc.FillSolidRect(m_rc,m_bkColor);
			Deflate(rc);
			m_memDc.FrameRect(rc, &br);
			m_memDc.SetTextColor(color);
			CRect rc2 = rc;
			rc2.DeflateRect(5,5);
			m_memDc.DrawText(m_sCaption, rc2, 
				DT_CENTER | DT_WORDBREAK | DT_TOP | DT_RTLREADING);
			m_memDc.SelectObject(pOFont);
		}
		break;
	}
}

double CSlider::SetVal(double val)
{
	CClientDC dc(m_pView);
	m_pView->OnPrepareDC(&dc);
	CleanPos(dc);

	if(val < m_minVal)
		val = m_minVal;
	else if(val > m_maxVal)
		val = m_maxVal;
	m_turn = val;

	double range = m_maxVal - m_minVal;


	switch(m_type)
	{
	case simpleVertical:
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		{
			double pixsels = (double)(m_rc.Height() - (m_nBotCapHieght + m_nTopCapHieght));
			double bottom = (double)(m_rc.bottom -  m_nBotCapHieght);
			m_lastpos = (int)(bottom - (pixsels / range * (m_turn - m_minVal)));
		}
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		{
			double pixsels = (double)(m_rc.Width() - (m_right + m_left));
			double left = (double)(m_rc.left +  m_left);
			m_lastpos = (int)(left + (pixsels / range * (m_turn - m_minVal)));
		}
		break;
	}
	PaintResult(dc);
	PaintPos(m_lastpos,dc);
	return m_turn;
}

void CSlider::SetMinMax(double fMin, double fMax)
{
	m_rangeBottom = m_minVal = fMin;
	m_rangeTop = m_maxVal = fMax;

	switch(m_type)
	{
	case simpleVertical:
	case VerCaptionResultMazalot:
	case VerMin90Plus90:
		m_stepsToVal = 
			(m_maxVal - m_minVal) / (double)((m_rc.bottom - m_nBotCapHieght) - 
			(m_rc.top + m_nTopCapHieght));
		break;
	case simpleHorizontal360:
	case simpleHorizontal:
		m_stepsToVal = 
			(m_maxVal - m_minVal) / (double)((m_rc.right - m_right) - 
			(m_rc.left + m_left));
		break;
	}
}

void CSlider::SetRefPoint(pointPos pos)
{
	switch(pos)
	{
	case middle:
		m_pt = m_rc.CenterPoint();
		break;
	case bottom:
		m_pt.y = m_rc.bottom - m_nBotCapHieght;
		break;
	}
}

void CSlider::SetResultFormat(CString sFormat)
{
	m_sFormatResult = sFormat;
}

void CSlider::SetFontSize(int size)
{
	m_nFontSize = size;
}

void CSlider::SetFrameColor(unsigned long col)
{
	m_frameColor = col;
	m_bNotDefaultColor = true;
}

void CSlider::SetMinMaxRange(double fMin, double fMax)
{
	m_rangeBottom = fMin;
	m_rangeTop = fMax;
}

bool CSlider::PntInRect(CPoint& p)
{
	return m_rc.PtInRect(p)?true:false;
}

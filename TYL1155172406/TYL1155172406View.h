
// TYL1155172406View.h : interface of the CTYL1155172406View class
//

#pragma once


class CTYL1155172406View : public CView
{
protected: // create from serialization only
	CTYL1155172406View() noexcept;
	DECLARE_DYNCREATE(CTYL1155172406View)

// Attributes
public:
	CTYL1155172406Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTYL1155172406View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TYL1155172406View.cpp
inline CTYL1155172406Doc* CTYL1155172406View::GetDocument() const
   { return reinterpret_cast<CTYL1155172406Doc*>(m_pDocument); }
#endif


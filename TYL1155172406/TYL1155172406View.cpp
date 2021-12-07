
// TYL1155172406View.cpp : implementation of the CTYL1155172406View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "TYL1155172406.h"
#endif

#include "TYL1155172406Doc.h"
#include "TYL1155172406View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTYL1155172406View

IMPLEMENT_DYNCREATE(CTYL1155172406View, CView)

BEGIN_MESSAGE_MAP(CTYL1155172406View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTYL1155172406View construction/destruction

CTYL1155172406View::CTYL1155172406View() noexcept
{
	// TODO: add construction code here

}

CTYL1155172406View::~CTYL1155172406View()
{
}

BOOL CTYL1155172406View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTYL1155172406View drawing

void CTYL1155172406View::OnDraw(CDC* /*pDC*/)
{
	CTYL1155172406Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CTYL1155172406View printing

BOOL CTYL1155172406View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTYL1155172406View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTYL1155172406View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTYL1155172406View diagnostics

#ifdef _DEBUG
void CTYL1155172406View::AssertValid() const
{
	CView::AssertValid();
}

void CTYL1155172406View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTYL1155172406Doc* CTYL1155172406View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTYL1155172406Doc)));
	return (CTYL1155172406Doc*)m_pDocument;
}
#endif //_DEBUG


// CTYL1155172406View message handlers

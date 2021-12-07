
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
	vector<float> t1;
	vector<float> t2;
	vector<float> t3;
	vector<float> t4;
	HGLRC m_hRC;
	int Cx;
	int Cy;
	bool SetupPixelFormat();

	void SetupViewingFrustum(double aspect);
	void SetupViewingTransform();
	void RenderScene();

	float xtrans;
	float ytrans;
	float ztrans;

	CPoint current_point;
	CPoint last_point;
	float xrot;
	float yrot;
	float m_fScale;
	void Lighting();
	void Material();

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
public:
	afx_msg void OnFileOpen();
	afx_msg void OnDestroy();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in TYL1155172406View.cpp
inline CTYL1155172406Doc* CTYL1155172406View::GetDocument() const
{
	return reinterpret_cast<CTYL1155172406Doc*>(m_pDocument);
}
#endif


// TestScrollOpenglView.h : interface of the CTestScrollOpenglView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSCROLLOPENGLVIEW_H__CFE84EEE_1B32_43D5_A07D_560FC1D43DFB__INCLUDED_)
#define AFX_TESTSCROLLOPENGLVIEW_H__CFE84EEE_1B32_43D5_A07D_560FC1D43DFB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTestScrollOpenglView : public CScrollView
{
protected: // create from serialization only
	CTestScrollOpenglView();
	DECLARE_DYNCREATE(CTestScrollOpenglView)
		
		// Attributes
protected:
	// 指向显示设备
	CClientDC *m_pDC;
	
public:
	CTestScrollOpenglDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestScrollOpenglView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL bSetPixelFormat();
	void IniOpenGL();
	virtual ~CTestScrollOpenglView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestScrollOpenglView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in TestScrollOpenglView.cpp
inline CTestScrollOpenglDoc* CTestScrollOpenglView::GetDocument()
   { return (CTestScrollOpenglDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSCROLLOPENGLVIEW_H__CFE84EEE_1B32_43D5_A07D_560FC1D43DFB__INCLUDED_)

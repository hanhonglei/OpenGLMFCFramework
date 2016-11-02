// TestScrollOpenglDoc.h : interface of the CTestScrollOpenglDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTSCROLLOPENGLDOC_H__D5FAB48C_9158_4BBF_9874_AE81401D7725__INCLUDED_)
#define AFX_TESTSCROLLOPENGLDOC_H__D5FAB48C_9158_4BBF_9874_AE81401D7725__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Texture.h"

class CTestScrollOpenglDoc : public CDocument
{
protected: // create from serialization only
	CTestScrollOpenglDoc();
	DECLARE_DYNCREATE(CTestScrollOpenglDoc)

// Attributes
public:
	bool	m_isLoaded;
	Texture m_texture;

protected:
	CSize	m_docSize;


// Operations
public:
	CSize	GetDocSize();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestScrollOpenglDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawScene(CPoint upLeft, CPoint downRight);
	virtual ~CTestScrollOpenglDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTestScrollOpenglDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTSCROLLOPENGLDOC_H__D5FAB48C_9158_4BBF_9874_AE81401D7725__INCLUDED_)

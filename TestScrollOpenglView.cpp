/*
* Copyright (c) 2005,DECA LAB
* All rights reserved.
* �ļ����ƣ�MainFrm.cpp
* ժ    Ҫ��ע���Ҹ���ע�͵ĵط�
* ��ǰ�汾��1.0
* ��    �ߣ�DECA LAB:������
* ������ڣ�2005��3��17��
*/  
/////////////////////////////////////////////////////////////////
// TestScrollOpenglView.cpp : implementation of the CTestScrollOpenglView class
//

#include "stdafx.h"
#include "TestScrollOpengl.h"

#include "TestScrollOpenglDoc.h"
#include "TestScrollOpenglView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView

IMPLEMENT_DYNCREATE(CTestScrollOpenglView, CScrollView)

BEGIN_MESSAGE_MAP(CTestScrollOpenglView, CScrollView)
//{{AFX_MSG_MAP(CTestScrollOpenglView)
ON_WM_CREATE()
ON_WM_SIZE()
ON_WM_DESTROY()
ON_WM_ERASEBKGND()
//}}AFX_MSG_MAP
// Standard printing commands
ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView construction/destruction

CTestScrollOpenglView::CTestScrollOpenglView()
{
	// TODO: add construction code here
	// leo : ��ʼ��
	m_pDC = NULL;
	
}

CTestScrollOpenglView::~CTestScrollOpenglView()
{
	// �ͷ�ָ��
	if (m_pDC != NULL)
	{
		delete m_pDC;
	}
}

BOOL CTestScrollOpenglView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView drawing

void CTestScrollOpenglView::OnDraw(CDC* pDC)
{
	CTestScrollOpenglDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	// ��������������������ͼ�����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
	// �������ͼ��ɹ�������л���
	if (pDoc->m_isLoaded)
	{
		// �����������ʵ�ʴ�С����
		CSize docSize = pDoc->GetDocSize();
		CPoint upLeft, downRight;
		upLeft  = CPoint(0, 0);
		downRight = CPoint(docSize.cx, docSize.cy);
		// Ϊ����ȷ��ӳ�������仯�������߼��������豸�����ת��
		pDC->LPtoDP(&upLeft);
		pDC->LPtoDP(&downRight);
		// ����doc�Ļ��ƺ������л���
		pDoc->DrawScene(upLeft, downRight);
	}
	// �������浽�豸��ʾ
	SwapBuffers(wglGetCurrentDC());
}

void CTestScrollOpenglView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	// 	CSize sizeTotal;
	// TODO: calculate the total size of this view
	// 	sizeTotal.cx = sizeTotal.cy = 100;
	// 	SetScrollSizes(MM_TEXT, sizeTotal);
	// ��ȷ�����������ķ�Χ
	SetScrollSizes(MM_TEXT, GetDocument()->GetDocSize());
	
}

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView printing

BOOL CTestScrollOpenglView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTestScrollOpenglView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTestScrollOpenglView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView diagnostics

#ifdef _DEBUG
void CTestScrollOpenglView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CTestScrollOpenglView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CTestScrollOpenglDoc* CTestScrollOpenglView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestScrollOpenglDoc)));
	return (CTestScrollOpenglDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglView message handlers

int CTestScrollOpenglView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;
	// leo : ��ʼ��opengl
	IniOpenGL();
	
	return 0;
}

void CTestScrollOpenglView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	// �����Ӵ�	
	// TODO: Add your message handler code here
    CRect aRect;
    GetClientRect(&aRect);
	
	int nWinWidth  = aRect.right-aRect.left;
	int nWinHeight = aRect.bottom-aRect.top;
	if(nWinHeight == 0)
	{
		nWinHeight = 1;
	}
	
	glViewport ( 0, 0, nWinWidth, nWinHeight );
	
    /* setup perspective m_camera with OpenGL */
    glMatrixMode(GL_PROJECTION);
	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glLoadIdentity();
// �޸�Ϊ��������Ĳ�������͸������ϵ
//    gluPerspective(/*vertical field of view*/ 45.,
//		/*aspect ratio*/ /*(double) viewport.width/viewport.height,*/(double)nWinWidth/nWinHeight,
//		/*znear*/ .1, /*zfar*/ 50.);
	
	glOrtho(0.0f, nWinWidth, nWinHeight, 0.0f, -1.0f, 1.0f);			// Create Ortho 640x480 View (0,0 At Top Left)
	/* from here on we're setting modeling transformations */
	glMatrixMode(GL_MODELVIEW);
	// leo:ʹ�ú󱸻�����ƣ�������˸
	glDrawBuffer (GL_BACK);
}

void CTestScrollOpenglView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	// leo:Ӧ�������Щ�ͷ���Դ�Ĳ���
	HGLRC   hrc;
	
	hrc = ::wglGetCurrentContext();
	
	::wglMakeCurrent(NULL,  NULL);
	
	if (hrc)
		::wglDeleteContext(hrc);	
	
}
// leo:�����б������������������Σ�������˸
BOOL CTestScrollOpenglView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}
// leo : ��ʼ��openggl��ͼ����
void CTestScrollOpenglView::IniOpenGL()
{
	m_pDC = new CClientDC(this);
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	//����һ�����������ĵľ��
	HGLRC   hrc;
	
	//��ʼ����������Ҫ���ǳ�ʼ����һ���ͻ������豸����ָ��
	ASSERT(m_pDC != NULL);
	
	//����Ӧ����������ظ�ʽ�����뵱ǰ�豸�����������
	if (!bSetPixelFormat())
		return;
	
	//�õ�ָ���豸����������ģʽ����
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	
	//��������õ�������ֵ������һ������ģʽ
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	
	//����һ���������豸����
	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	
	//�������ɵ��豸������ָ����Ϊ��ǰ����
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);		
	
	//�úڱ���
	glClearColor(0.0,0.0,0.0,0.0);		
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glShadeModel(GL_SMOOTH);
	
	// ���û�ɫ����ȡ�ð�͸��Ч��
	//	glBlendFunc(GL_SRC_ALPHA,GL_ONE); 	
	//	glEnable(GL_BLEND); 
	
	//ƽ������
    glEnable (GL_LINE_SMOOTH);
	//    glEnable (GL_BLEND);
	
	//��ʼ��������Ϊ RGBA ģʽ��ͬʱ���� alpha ��ϡ���ʾ������
	//		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//		glEnable (GL_BLEND);
	
	// ������ϸ��͸������
	glHint (GL_POLYGON_SMOOTH_HINT|GL_LINE_SMOOTH_HINT, GL_NICEST);
	
	//������Ȳ���
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
}
// leo ����������OpenGLʹ�õ����ظ�ʽ
BOOL CTestScrollOpenglView::bSetPixelFormat()
{
	//����һ�����ظ�ʽ
	static PIXELFORMATDESCRIPTOR pfd =
	{   
		sizeof(PIXELFORMATDESCRIPTOR),			// size of this pfd
			1,									// version number
			PFD_DRAW_TO_WINDOW |				// support window
			PFD_SUPPORT_OPENGL |				// support OpenGL  ֧��OpenGL
			PFD_DOUBLEBUFFER,					// double buffered ֧���ֻ���
			PFD_TYPE_RGBA,						// RGBA typeʹ��RGBAģʽ�����õ�ɫ��
			24,									// 24-bit color depth  ʹ��24λ���ɫ
			0, 0, 0, 0, 0, 0,					// color bits ignored
			0,									// no alpha buffer
			0,									// shift bit ignored
			0,									// no accumulation buffer
			0, 0, 0, 0,							// accum bits ignored
			32,									// 32-bit z-buffer   32λZ�Ỻ��
			0,									// no stencil buffer
			0,									// no auxiliary buffer
			PFD_MAIN_PLANE,						// main layer
			0,									// reserved
			0, 0, 0								// layer masks ignored
	};
	int pixelformat;
	
	//������Եõ�ָ�������ظ�ʽ
	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == FALSE )
	{
		AfxMessageBox("ChoosePixelFormat failed");
		return false;
	}
	
	//������ȡ���ĸ�ʽ�����豸����
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox("SetPixelFormat failed");
		return false;
	}
	return true;
}

/*
* Copyright (c) 2005,DECA LAB
* All rights reserved.
* 文件名称：MainFrm.cpp
* 摘    要：注意我给出注释的地方
* 当前版本：1.0
* 作    者：DECA LAB:韩红雷
* 完成日期：2005年3月17日
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
	// leo : 初始化
	m_pDC = NULL;
	
}

CTestScrollOpenglView::~CTestScrollOpenglView()
{
	// 释放指针
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
	// 进行清楚操作，避免产生图像残留
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			// Clear The Screen And The Depth Buffer
	// 如果载入图像成功，则进行绘制
	if (pDoc->m_isLoaded)
	{
		// 以载入纹理的实际大小绘制
		CSize docSize = pDoc->GetDocSize();
		CPoint upLeft, downRight;
		upLeft  = CPoint(0, 0);
		downRight = CPoint(docSize.cx, docSize.cy);
		// 为了正确反映滚动条变化，进行逻辑坐标向设备坐标的转换
		pDC->LPtoDP(&upLeft);
		pDC->LPtoDP(&downRight);
		// 利用doc的绘制函数进行绘制
		pDoc->DrawScene(upLeft, downRight);
	}
	// 交换缓存到设备显示
	SwapBuffers(wglGetCurrentDC());
}

void CTestScrollOpenglView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();
	
	// 	CSize sizeTotal;
	// TODO: calculate the total size of this view
	// 	sizeTotal.cx = sizeTotal.cy = 100;
	// 	SetScrollSizes(MM_TEXT, sizeTotal);
	// 正确决定滚动条的范围
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
	// leo : 初始化opengl
	IniOpenGL();
	
	return 0;
}

void CTestScrollOpenglView::OnSize(UINT nType, int cx, int cy) 
{
	CScrollView::OnSize(nType, cx, cy);
	// 调整视窗	
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
// 修改为依靠传入的参数决定透视坐标系
//    gluPerspective(/*vertical field of view*/ 45.,
//		/*aspect ratio*/ /*(double) viewport.width/viewport.height,*/(double)nWinWidth/nWinHeight,
//		/*znear*/ .1, /*zfar*/ 50.);
	
	glOrtho(0.0f, nWinWidth, nWinHeight, 0.0f, -1.0f, 1.0f);			// Create Ortho 640x480 View (0,0 At Top Left)
	/* from here on we're setting modeling transformations */
	glMatrixMode(GL_MODELVIEW);
	// leo:使用后备缓存绘制，避免闪烁
	glDrawBuffer (GL_BACK);
}

void CTestScrollOpenglView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	// TODO: Add your message handler code here
	// leo:应该添加这些释放资源的操作
	HGLRC   hrc;
	
	hrc = ::wglGetCurrentContext();
	
	::wglMakeCurrent(NULL,  NULL);
	
	if (hrc)
		::wglDeleteContext(hrc);	
	
}
// leo:不进行背景清除，以免绘制两次，产生闪烁
BOOL CTestScrollOpenglView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
}
// leo : 初始化openggl绘图环境
void CTestScrollOpenglView::IniOpenGL()
{
	m_pDC = new CClientDC(this);
	PIXELFORMATDESCRIPTOR pfd;
	int n;
	//定义一个绘制上下文的句柄
	HGLRC   hrc;
	
	//初始化过程中主要就是初始化了一个客户区的设备环境指针
	ASSERT(m_pDC != NULL);
	
	//建立应用所需的像素格式，并与当前设备上下文相关连
	if (!bSetPixelFormat())
		return;
	
	//得到指定设备环境的象素模式索引
	n = ::GetPixelFormat(m_pDC->GetSafeHdc());
	
	//根据上面得到的索引值来声明一个象素模式
	::DescribePixelFormat(m_pDC->GetSafeHdc(), n, sizeof(pfd), &pfd);
	
	//创建一个上下文设备环境
	hrc = wglCreateContext(m_pDC->GetSafeHdc());
	
	//将刚生成的设备上下文指针设为当前环境
	wglMakeCurrent(m_pDC->GetSafeHdc(), hrc);		
	
	//置黑背景
	glClearColor(0.0,0.0,0.0,0.0);		
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);	
	glShadeModel(GL_SMOOTH);
	
	// 设置混色函数取得半透明效果
	//	glBlendFunc(GL_SRC_ALPHA,GL_ONE); 	
	//	glEnable(GL_BLEND); 
	
	//平滑线条
    glEnable (GL_LINE_SMOOTH);
	//    glEnable (GL_BLEND);
	
	//初始化反走样为 RGBA 模式，同时包括 alpha 混合、提示的设置
	//		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//		glEnable (GL_BLEND);
	
	// 真正精细的透视修正
	glHint (GL_POLYGON_SMOOTH_HINT|GL_LINE_SMOOTH_HINT, GL_NICEST);
	
	//充许深度测试
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL); 
}
// leo ：设置适于OpenGL使用的像素格式
BOOL CTestScrollOpenglView::bSetPixelFormat()
{
	//定义一种像素格式
	static PIXELFORMATDESCRIPTOR pfd =
	{   
		sizeof(PIXELFORMATDESCRIPTOR),			// size of this pfd
			1,									// version number
			PFD_DRAW_TO_WINDOW |				// support window
			PFD_SUPPORT_OPENGL |				// support OpenGL  支持OpenGL
			PFD_DOUBLEBUFFER,					// double buffered 支持又缓冲
			PFD_TYPE_RGBA,						// RGBA type使用RGBA模式，不用调色板
			24,									// 24-bit color depth  使用24位真彩色
			0, 0, 0, 0, 0, 0,					// color bits ignored
			0,									// no alpha buffer
			0,									// shift bit ignored
			0,									// no accumulation buffer
			0, 0, 0, 0,							// accum bits ignored
			32,									// 32-bit z-buffer   32位Z轴缓冲
			0,									// no stencil buffer
			0,									// no auxiliary buffer
			PFD_MAIN_PLANE,						// main layer
			0,									// reserved
			0, 0, 0								// layer masks ignored
	};
	int pixelformat;
	
	//如果可以得到指定的像素格式
	if ( (pixelformat = ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd)) == FALSE )
	{
		AfxMessageBox("ChoosePixelFormat failed");
		return false;
	}
	
	//用上面取到的格式设置设备环境
	if (SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd) == FALSE)
	{
		AfxMessageBox("SetPixelFormat failed");
		return false;
	}
	return true;
}

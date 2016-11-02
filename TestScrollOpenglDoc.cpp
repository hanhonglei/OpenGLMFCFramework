/*
* Copyright (c) 2005,DECA LAB
* All rights reserved.
* �ļ����ƣ�MainFrm.cpp
* ժ    Ҫ������mfcҪ����serialize��ʵ���ļ�������
* ��ǰ�汾��1.0
* ��    �ߣ�DECA LAB:������
* ������ڣ�2005��3��17��
*/  
/////////////////////////////////////////////////////////////////
// TestScrollOpenglDoc.cpp : implementation of the CTestScrollOpenglDoc class
//

#include "stdafx.h"
#include "TestScrollOpengl.h"

#include "TestScrollOpenglDoc.h"

#include "Tga.h"
#include <gl\gl.h>
#include <gl\glu.h>												// Header File For The GLu32 Library

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglDoc

IMPLEMENT_DYNCREATE(CTestScrollOpenglDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestScrollOpenglDoc, CDocument)
	//{{AFX_MSG_MAP(CTestScrollOpenglDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglDoc construction/destruction

CTestScrollOpenglDoc::CTestScrollOpenglDoc()
{
	// TODO: add one-time construction code here
	m_texture.imageData = NULL;
	m_isLoaded = FALSE;
	m_docSize = CSize(0, 0);
}

CTestScrollOpenglDoc::~CTestScrollOpenglDoc()
{
}

BOOL CTestScrollOpenglDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglDoc serialization

void CTestScrollOpenglDoc::Serialize(CArchive& ar)
{
	CFile *file = ar.GetFile();
	int fileLen = file->GetLength();
	char *sFileName = new char [fileLen+1];
	strcpy(sFileName, file->GetFilePath());
	
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
		glEnable(GL_TEXTURE_2D);
		if (LoadTGA(&m_texture, sFileName))
		{
			glGenTextures(1, &m_texture.texID);				// Create The Texture ( CHANGE )
			glBindTexture(GL_TEXTURE_2D, m_texture.texID);
			glTexImage2D(GL_TEXTURE_2D, 0, m_texture.bpp / 8, m_texture.width, m_texture.height
				, 0, m_texture.type, GL_UNSIGNED_BYTE, m_texture.imageData);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
			// ����ĵ��Ĵ�С���Ա�ȷ���������ķ�Χ
			m_docSize = CSize(m_texture.width, m_texture.height);
			
			if (m_texture.imageData)						// If Texture Image Exists ( CHANGE )
			{
				free(m_texture.imageData);					// Free The Texture Image Memory ( CHANGE )
				m_texture.imageData = NULL;
			}
			m_isLoaded = TRUE;
		}
	}	
	// �ͷ�ָ��
	delete sFileName;
}

CSize CTestScrollOpenglDoc::GetDocSize()
{
	return m_docSize;
}

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglDoc diagnostics

#ifdef _DEBUG
void CTestScrollOpenglDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestScrollOpenglDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestScrollOpenglDoc commands

// ��ɻ���.��һ�������ǻ���ͼ�����Ͻǵ����꣬��һ�������½ǵ�����
void CTestScrollOpenglDoc::DrawScene(CPoint upLeft, CPoint downRight)
{
	glPushMatrix();
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, m_texture.texID);
	
	glBegin(GL_QUADS);											// ������ѡ���Ĺؼ���������ƹؼ���
		glTexCoord2f(0.0f, 1.0f);
		glVertex2i(upLeft.x, upLeft.y);
		glTexCoord2f(1.0f, 1.0f);
		glVertex2i(downRight.x, upLeft.y);
		glTexCoord2f(1.0f, 0.0f);
		glVertex2i(downRight.x, downRight.y);
		glTexCoord2f(0.0f, 0.0f);
		glVertex2i(upLeft.x, downRight.y);
	glEnd();
	glPopMatrix();
	
}

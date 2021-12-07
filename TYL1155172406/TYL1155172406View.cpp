
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
ifstream in;
ofstream out;


// CTYL1155172406View

IMPLEMENT_DYNCREATE(CTYL1155172406View, CView)

BEGIN_MESSAGE_MAP(CTYL1155172406View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, &CTYL1155172406View::OnFileOpen)
	ON_WM_DESTROY()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// CTYL1155172406View construction/destruction

CTYL1155172406View::CTYL1155172406View() noexcept
{
	// TODO: add construction code here
	m_hRC = 0;
	Cx = 0;
	Cy = 0;

	xtrans = 0.0;
	ytrans = 0.0;
	ztrans = 0.0;
	xrot = 0.0;
	yrot = 0.0;
	m_fScale = 1.0;
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

void CTYL1155172406View::OnDraw(CDC* pDC)
{
	CTYL1155172406Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	wglMakeCurrent(pDC->m_hDC, m_hRC);
	//draw here
	glViewport(0, 0, Cx, Cy);
	SetupViewingFrustum((double)Cx / (double)Cy);
	SetupViewingTransform();
	Lighting();
	Material();
	RenderScene();

	wglMakeCurrent(pDC->m_hDC, NULL);
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


void CTYL1155172406View::OnFileOpen()
{
	// TODO: Add your command handler code here
	CString szFilter;
	szFilter = "txt|*.txt|*.*|*.*||";
	CFileDialog FD(TRUE, _T("txt"), _T("*.txt"), OFN_HIDEREADONLY, szFilter);
	string tmp;
	float a, b, c, d;
	a = b = c = d = 0.0;


	if (FD.DoModal() == IDOK)
	{
		in.open(FD.GetPathName());
		while (!in.eof())
		{
			in >> tmp;
			if (tmp.compare("marks") == 0)
			{
				in >> a >> b >> c >> d;
				t1.push_back(a);
				t2.push_back(b);
				t3.push_back(c);
				t4.push_back(d);
			}
		}
		in.close();
		out.open("check.txt");
		for (int i = 0; i < t1.size(); i++)
		{
			out << t1[i] << " " << t2[i] << " " << t3[i] << " " << t4[i] << endl;
		}
		out.close();
	}
}
bool CTYL1155172406View::SetupPixelFormat()
{
	static PIXELFORMATDESCRIPTOR pfd =
	{
			sizeof(PIXELFORMATDESCRIPTOR), // Size of this pfd
			1, // Version number
			PFD_DRAW_TO_WINDOW | // Support window
			PFD_SUPPORT_OPENGL | // Support OpenGL
			PFD_TYPE_RGBA, // RGBA type
			32, // 32-bit color depth
			0, 0, 0, 0, 0, 0, // Color bits ignored
			0, // No alpha buffer
			0, // Shift bit ignored
			0, // No accumulation buffer
			0, 0, 0, 0, // Accum bits ignored
			16, // 16-bit z-buffer
			0, // No stencil buffer
			0, // No auxiliary buffer
			PFD_MAIN_PLANE, // Main layer
			0, // Reserved
			0, 0, 0 // Layer masks ignored
	};
	int pixelformat;
	CClientDC clientDC(this); //get device context
	// match pixel format supported by a device context to given spec
	if ((pixelformat = ::ChoosePixelFormat(clientDC.m_hDC, &pfd)) == 0)
		return false;
	//apply pixel format to view
	if (!(::SetPixelFormat(clientDC.m_hDC, pixelformat, &pfd)))
		return false;
	// bridge OpenGL rendering context with device context
	m_hRC = wglCreateContext(clientDC.m_hDC);
	return true;
}


void CTYL1155172406View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	//remove connection between CDC and HGLRC
	::wglDeleteContext(m_hRC);
}


int CTYL1155172406View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	if (!SetupPixelFormat())
		return -1;
	return 0;
}


void CTYL1155172406View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	Cx = cx;
	Cy = cy;
	InvalidateRect(0, FALSE);
}

void CTYL1155172406View::SetupViewingFrustum(double aspect)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, aspect, 1, 100.0);
}

void CTYL1155172406View::SetupViewingTransform()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 10.0,
		0.0, 0.0, 0.0,
		0.0, 1.0, 0.0);
}

void CTYL1155172406View::RenderScene()
{
	//clear background color of OpenGL scene
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//clear the screen and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glShadeModel(GL_SMOOTH);

	glScalef(m_fScale, m_fScale, m_fScale);
	glTranslatef(xtrans, ytrans, ztrans);
	glRotatef(xrot, 1, 0, 0);
	glRotatef(yrot, 0, 1, 0);

	glBegin(GL_QUADS);

	glNormal3f(0, 0, 1);
	//////Front///////////////
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(10.0, 5.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);

	glNormal3f(0, 0, -1);
	/////Back //////////////////
	glVertex3f(0.0, 0.0, -5.0);
	glVertex3f(0.0, 5.0, -5.0);
	glVertex3f(10.0, 5.0, -5.0);
	glVertex3f(10.0, 0.0, -5.0);

	glNormal3f(1, 0, 0);
	//////Right///////////////
	glVertex3f(10.0, 0.0, 0.0);
	glVertex3f(10.0, 0.0, -5.0);
	glVertex3f(10.0, 5.0, -5.0);
	glVertex3f(10.0, 5.0, 0.0);

	glNormal3f(-1, 0, 0);
	//////Left///////////////
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 5.0, 0.0);
	glVertex3f(0.0, 5.0, -5.0);
	glVertex3f(0.0, 0.0, -5.0);

	glNormal3f(0, 1, 0);
	//////Top///////////////
	glVertex3f(0.0, 5.0, 0.0);
	glVertex3f(10.0, 5.0, 0.0);
	glVertex3f(10.0, 5.0, -5.0);
	glVertex3f(0.0, 5.0, -5.0);

	glNormal3f(0, -1, 0);
	//////Bottom///////////////
	glVertex3f(0.0, 0.0, 0.0);
	glVertex3f(0.0, 0.0, -5.0);
	glVertex3f(10.0, 0.0, -5.0);
	glVertex3f(10.0, 0.0, 0.0);
	glEnd();


	glFlush();
}

void CTYL1155172406View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	if (nChar == VK_RIGHT) //Right button on keyboard
		xtrans += 0.1;
	// Redraw the scene once
	InvalidateRect(0, FALSE);

	if (nChar == VK_LEFT) //Left button on keyboard
		xtrans -= 0.1;
	// Redraw the scene once
	InvalidateRect(0, FALSE);

	if (nChar == VK_UP) //Up button on keyboard
		ytrans += 0.1;
	// Redraw the scene once
	InvalidateRect(0, FALSE);

	if (nChar == VK_DOWN) //Down button on keyboard
		ytrans -= 0.1;
	// Redraw the scene once
	InvalidateRect(0, FALSE);

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CTYL1155172406View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	current_point = point;

	if (nFlags == MK_LBUTTON && current_point.y > last_point.y + 2)
		xrot += 5.5;
	else
		if (nFlags == MK_LBUTTON && current_point.y < last_point.y - 2)
			xrot -= 5.5;
	//check the location of cursor in x direction to perform rotation about y axis
	if (nFlags == MK_LBUTTON && current_point.x > last_point.x + 2)
		yrot += 5.5;
	else if (nFlags == MK_LBUTTON && current_point.x < last_point.x - 2)
		yrot -= 5.5;
	last_point = point; //record the last point
	InvalidateRect(0, FALSE);

	CView::OnMouseMove(nFlags, point);
}


BOOL CTYL1155172406View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	if (zDelta > 0)
		m_fScale += 0.1f;
	else if (m_fScale > 0.1f)
		m_fScale -= 0.1f;
	InvalidateRect(NULL, FALSE);

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTYL1155172406View::Lighting()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE); // force the length of surface normal to be 1 so that the lighting and material effect can be calculated correctly
	glEnable(GL_DEPTH_TEST);


	glEnable(GL_LIGHT0);

	GLfloat light_position[] = { 1.0f, 0.0f, 1.0f, 0.0f }; //directional light
	GLfloat light_ambient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
	GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_specular[] = { 1.0f,1.0f,1.0f,1.0f };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
}


void CTYL1155172406View::Material()
{
	//glEnable(GL_COLOR_MATERIAL);  ///Set the object's color with glColor3f();
	//glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);  /// With using  glColor3f(), allow object's color to interact with light
	GLfloat mat_diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	GLfloat mat_specular[] = { 0.2f,0.2f,0.2f,1.0f };
	GLfloat mat_shininess[] = { 50.0f };
	GLfloat mat_emission[] = { 0.2f, 0.2f, 0.2, 1.0f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, mat_emission);

}


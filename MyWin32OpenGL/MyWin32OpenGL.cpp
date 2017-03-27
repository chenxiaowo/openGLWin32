// MyWin32OpenGL.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MyWin32OpenGL.h"
#include "resource.h"
#define MAX_LOADSTRING 100

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>




void SetupPixelFormat(HDC hDC);
int InitGL(GLvoid);
void ChangeSize(int width, int height);
void RenderScene();
int roundmy(const float a);
void lineDDA(int x0, int y0, int xEnd, int yEnd);

void MyRender(int r);


int radius = 0;

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam);

HINSTANCE hgAppInst;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

												// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	hgAppInst = hInstance;

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_MYWIN32OPENGL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYWIN32OPENGL));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYWIN32OPENGL));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MYWIN32OPENGL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HGLRC hRC; //���ƻ���  
	static HDC hDC; //�豸����  

	switch (message)
	{

	

	case WM_CREATE: {
		hDC = GetDC(hWnd); //�õ���ǰ���ڵ��豸����  
		SetupPixelFormat(hDC); //�������ظ�ʽ���ú���  
		hRC = wglCreateContext(hDC); //����OpenGL��ͼ����������һ��ָ��OpenGL���ƻ����ľ��  
		wglMakeCurrent(hDC, hRC); //�����ݹ����Ļ��ƻ�������ΪOpenGL��Ҫ���л��Ƶĵ�ǰ���ƻ���  
								  //      SetTimer(hwnd, 33, 1, NULL);  
		InitGL();
		return 0;
	}
					break;

	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		int x0 = 0, y0 = 0, xEnd = 100, yEnd = 100;
		//scanf("%d%d%d%d",&x0,&y0,&xEnd,&yEnd);
		
		// Parse the menu selections:
		//HWND hdlg = CreateDialog(hgAppInst, MAKEINTRESOURCE(MY_DIALOG), hWnd, (DLGPROC)DlgProc);
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//EndDialog(hdlg, LOWORD(wParam));
			
		}

		char ch1[10];
		int r;
		switch (wmId)
		{
		
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_TEST:
			//DialogBox(hInst, MAKEINTRESOURCE(MY_DIALOG), hWnd, DlgProc);
			// ��ʾ�Ի���  
			//ShowWindow(hdlg, SW_SHOWNA);
			//GetDlgItemText(hdlg, MY_NUM, ch1, 10);
			radius = 30;
			MyRender(radius);
			SwapBuffers(hDC);
			ValidateRect(hWnd, NULL);
			
			break;
		case MY_LINE:
			lineDDA(x0, y0 + 1, xEnd, yEnd);//����DDA���ߺ���
			SwapBuffers(hDC);
			ValidateRect(hWnd, NULL);

			break;


		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	break;
	case WM_PAINT:
	{
		/*RenderScene();
		SwapBuffers(hDC);
		ValidateRect(hWnd, NULL);*/

		//RenderScene();
		SwapBuffers(hDC);
		ValidateRect(hWnd, NULL);
	}
	break;

	case WM_SIZE:
	{
		//ChangeSize(LOWORD(lParam), HIWORD(lParam));  
		ChangeSize(LOWORD(lParam), HIWORD(lParam));
	}
	break;
	case WM_DESTROY:
		wglMakeCurrent(hDC, NULL);
		wglDeleteContext(hRC);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



//###############################################33333
void SetupPixelFormat(HDC hDC) //Ϊ�豸�����������ظ�ʽ  
{
	int nPixelFormat; //���ظ�ʽ����  
	static PIXELFORMATDESCRIPTOR pfd = { sizeof(PIXELFORMATDESCRIPTOR), //���ݽṹ��С  
		1, //�汾�ţ�����Ϊ1  
		PFD_DRAW_TO_WINDOW | //֧�ִ���  
		PFD_SUPPORT_OPENGL | //֧��OpenGL  
		PFD_DOUBLEBUFFER, //֧��˫����  
		PFD_TYPE_RGBA, //RGBA��ɫģʽ  
		32, //32λ��ɫģʽ  
		0, 0, 0, 0, 0, 0, //������ɫΪ����ʹ��  
		0, //��alpha����  
		0, //����ƫ��λ  
		0, //���ۻ�����  
		0, 0, 0, 0, //�����ۻ�λ  
		16, //16λz-buffer��z���棩��С  
		0, //��ģ�建��  
		0, //�޸�������  
		PFD_MAIN_PLANE, //������ƽ��  
		0, //������������  
		0, 0, 0 }; //���Բ�����ģ  
				   //ѡ����ƥ������ظ�ʽ����������ֵ  
	nPixelFormat = ChoosePixelFormat(hDC, &pfd);
	//���û����豸�����ظ�ʽ  
	SetPixelFormat(hDC, nPixelFormat, &pfd);
}
int InitGL(GLvoid)                           // �˴���ʼ��OpenGL������������  
{
	glShadeModel(GL_SMOOTH);                 // ������Ӱƽ��  
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    // ��ɫ����  
	glClearDepth(1.0f);                      // ������Ȼ���  
	glEnable(GL_DEPTH_TEST);                 // ������Ȳ���  
	glDepthFunc(GL_LEQUAL);                  // ������Ȳ��Ե�����  
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);// ����ϵͳ��͸�ӽ�������  
	return TRUE;                             // ��ʼ�� OK  
}
void ChangeSize(int width, int height)
{
	glViewport(0, 0, width, height);         // ���õ�ǰ���ӿ�glMatrixMode(GL_PROJECTION);  
	glMatrixMode(GL_PROJECTION);             // ѡ��ͶӰ����  
	glLoadIdentity();                        // ����ͶӰ����  
											 // ����ͶӰģʽΪ͸��ͶӰ  
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//void RenderScene()
//{
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����������Ȼ�����  
//	glLoadIdentity();        // ���õ�ǰ��ģ�͹۲����  
//	glTranslatef(-1.5f, 0.0f, -26.0f);       // ���� 1.5 ��λ����������Ļ 6.0  
//	glBegin(GL_TRIANGLES);        // ����������  
//	glVertex3f(0.0f, 1.0f, 0.0f);      // �϶���  
//	glVertex3f(-1.0f, -1.0f, 0.0f);      // ����  
//	glVertex3f(1.0f, -1.0f, 0.0f);      // ����  
//	glEnd();         // �����λ��ƽ���  
//	glTranslatef(3.0f, 0.0f, 0.0f);       // ����3��λ  
//	glRotatef(45, 1, 1, 0);
//	glutWireCube(2);
//	//�˴���ӻ�ͼ����  
//	//glutSwapBuffers();  
//	// glFlush();  
//}



INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	static   HWND   hwnd_static;   //   Static   �ؼ��ľ��   
	switch (message)
	{
	case WM_INITDIALOG:
		hwnd_static = GetDlgItem(hDlg, MY_TEXT);
		SetWindowText(hwnd_static,"������뾶��");
		

		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			//GetDlgItemText(hdlg, MY_NUM, ch1, 10);
			BOOL flag;
			int test = GetDlgItemInt(hDlg,MY_NUM,&flag,true);
			EndDialog(hDlg, LOWORD(wParam));
			radius = test;

			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



void lineDDA(int x0, int y0, int xEnd, int yEnd)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����������Ȼ�����  
	glLoadIdentity();        // ���õ�ǰ��ģ�͹۲����  
	glTranslatef(-1.5f, 0.0f, -6.0f);       // ���� 1.5 ��λ����������Ļ 6.0  
	glScalef(0.05f, 0.05f, 1.0f);
	glColor3f(0.0f, 1.0f, 0.0f);

	int dx = xEnd - x0;
	int dy = yEnd - y0;
	int steps, k;
	float xIncrement, yIncrement, x = x0, y = y0;

	if (fabs(dx) > fabs(dy))
		steps = fabs(dy);
	else
		steps = fabs(dx);
	xIncrement = (float)(dx) / (float)(steps);
	yIncrement = (float)(dy) / (float)(steps);

	glBegin(GL_POINTS);
	glVertex2i(roundmy(x), roundmy(y));
	glEnd();
	glFlush();
	for (k = 0; k<steps; k++)
	{
		x += xIncrement;
		y += yIncrement;
		glBegin(GL_POINTS);
		glVertex2i(roundmy(x),roundmy(y));
		glEnd();
		glFlush();
		
		
	}
}

int roundmy(const float a)
{
	return (int)(a + 0.5);
}

void MyRender(int r)
{

	int x, y, d;
	int x0 = 4, y0 = 5;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //�����������Ȼ�����  
	glLoadIdentity();        // ���õ�ǰ��ģ�͹۲����  
	glTranslatef(-1.5f, 0.0f, -6.0f);       // ���� 1.5 ��λ����������Ļ 6.0  
	glScalef(0.05f, 0.05f, 1.0f);
	glColor3f(1.0f, 0.0f, 0.0f);


	glBegin(GL_POINTS);        // ���ƿ�ʼ
	x = 0;   y = r;   d = 1.25 - r;
	while (x <= y)
	{
		glVertex2i(x, y);
		glVertex2i(-x, -y);

		glVertex2i(-x, y);
		glVertex2i(x, -y);

		glVertex2i(y, x);
		glVertex2i(-y, -x);

		glVertex2i(-y, x);
		glVertex2i(y, -x);

		if (d <= 0)         d += 2 * x + 3;
		else { d += 2 * (x - y) + 5; y--; }
		x++;
	}

	glEnd();         // ���ƽ���  
	glFlush();

}

// MFCApplication6Dlg.cpp : файл реализации
//

#include "stdafx.h"
#include "MFCApplication6.h"
#include "MFCApplication6Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace Gdiplus;

IMPLEMENT_DYNAMIC(Drawer, CStatic)

// диалоговое окно CMFCApplication6Dlg



CMFCApplication6Dlg::CMFCApplication6Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCApplication6Dlg::IDD, pParent)

{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication6Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, angle_value);
	DDX_Control(pDX, IDC_SLIDER1, angle);
	DDX_Control(pDX, IDC_MY_DRAW, Picture);
	DDX_Control(pDX, IDC_EDIT2, X);
	DDX_Control(pDX, IDC_EDIT3, Y);
}

BEGIN_MESSAGE_MAP(CMFCApplication6Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// обработчики сообщений CMFCApplication6Dlg

BOOL CMFCApplication6Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	angle.SetRange(-45, 45, TRUE);
	angle.SetPos(0);
	angle.SetTicFreq(1);
	angle_value.SetWindowTextW(L"0");

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CMFCApplication6Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CMFCApplication6Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BEGIN_MESSAGE_MAP(Drawer, CStatic)
END_MESSAGE_MAP()


Drawer::Drawer()
{
	GdiplusStartupInput input;
	Status s;
	s = GdiplusStartup(&work, &input, NULL);
	rotate = 0;
	rotation_point = PointF(0., 0.);
}


void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO:  Добавьте исходный код для отображения указанного элемента
	Graphics g(lpDrawItemStruct->hDC);
	Bitmap buffer(lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, &g);
	Graphics gr(&buffer);
	gr.SetSmoothingMode(SmoothingModeAntiAlias);


	//-------------------Фон----------------------------------------------------------------------------


	//gr.Clear(Color(50, 175, 238, 238)); // альфа-компонента - эффект следа (увеличивается с уменьшение параметра)
	gr.Clear(Color(255, 211, 211, 211)); // альфа-компонента - эффект следа (увеличивается с уменьшение параметра)

	Matrix matr;
	matr.RotateAt(rotate, rotation_point);
	gr.SetTransform(&matr);

	auto rect_picture = lpDrawItemStruct->rcItem;


	//-------------------Окружность----------------------------------------------------------------------


	RectF rect_ellipse(
		/*
		(rect_picture.right - rect_picture.left) / 3 + rect_picture.right / 4,
		(rect_picture.bottom - rect_picture.top) / 3 + rect_picture.bottom / 4,
		(rect_picture.right - rect_picture.left) / 3,
		(rect_picture.bottom - rect_picture.top) / 3);
		*/
		160 + rect_picture.right / 3, 160 - 30, 160, 160);


	//Контур для круга

	//Pen my_pen_ellipse(Color(255, 0, 0, 0));      //Чёрный
	Pen my_pen_ellipse(Color(255, 56, 150, 50));    //Тёмно-Зелёный  альфа-компонента - толщину контура меняет
	gr.DrawEllipse(&my_pen_ellipse, rect_ellipse);


	//Центральный градиент для круга

	// Создайте контур, состоящий из одного эллипса.
	GraphicsPath path;
	path.AddEllipse(rect_ellipse);

	/*
	// Используйте контур для создания кисти.
	PathGradientBrush pthGrBrush_ellipse(&path);

	// Установите цвет в центре контура на синий.
	pthGrBrush_ellipse.SetCenterColor(Color(200, 255, 166, 0));   //Оранжевый
	//альфа-компонента - интенсивность цвета с центра (0 = прозрачный)

	// Установите цвет вдоль всей границы о пути к акве.
	Color color_ellipse[] = { Color(255, 255, 227, 155) }; //Светло-жёлтый
	//альфа-компонента - интенсивность цвета с краёв (0 = прозрачный)
	int count = 1;
	pthGrBrush_ellipse.SetSurroundColors(color_ellipse, &count);
	*/


	//Линейный градиент для прямоугольника

	//LinearGradientBrush pthGrBrush_rectangle(PointF(95, 97), PointF(302, 200), Color(0, 0, 255), Color(255, 0, 0));
	LinearGradientBrush pthGrBrush_ellipse(PointF(353, 130), PointF(515, 291), Color(255, 255, 255), Color(255, 165, 0));



	gr.FillEllipse(&pthGrBrush_ellipse, rect_ellipse);


	//-------------------Прямоугольник------------------------------------------------------------------


	RectF rect_rectangle(
		/*
		(rect_picture.right - rect_picture.left) / 3 - rect_picture.right / 4,
		(rect_picture.bottom - rect_picture.top) / 3,
		(rect_picture.right - rect_picture.left) / 3,
		(rect_picture.bottom - rect_picture.top) / 3);
		*/

		0 + rect_picture.right / 6, 0 + rect_picture.right / 6, 200, 100);

	/* На весь размер окна
	(rect_picture.right - rect_picture.left) / 1 - rect_picture.right,
	(rect_picture.bottom - rect_picture.top) / 1 - rect_picture.bottom,
	(rect_picture.right - rect_picture.left) / 1,
	(rect_picture.bottom - rect_picture.top) / 1);
	*/


	//Контур для прямоугольника

	Pen my_pen_rectangle(Color(255, 0, 0, 255));       //Синий
	gr.DrawRectangle(&my_pen_rectangle, rect_rectangle);


	//Центральный градиент для прямоугольника

	// Создайте контур, состоящий из одного эллипса.
	GraphicsPath path_rectangle;
	path_rectangle.AddRectangle(rect_rectangle);

	/*
	// Используйте контур для создания кисти.
	PathGradientBrush pthGrBrush_rectangle(&path_rectangle);

	// Установите цвет в центре контура на синий.
	pthGrBrush_rectangle.SetCenterColor(Color(200, 153, 0, 255)); //Фиолетовый
	//альфа-компонента - интенсивность цвета с центра (0 = прозрачный)

	// Установите цвет вдоль всей границы о пути к акве.
	Color colors_rectanglr[] = { Color(200, 0, 153, 255) }; //Синий
	pthGrBrush_rectangle.SetSurroundColors(colors_rectanglr, &count);
	//альфа-компонента - интенсивность цвета с центра (0 = прозрачный)
	*/


	//Линейный градиент для прямоугольника

	//LinearGradientBrush pthGrBrush_rectangle(PointF(95, 97), PointF(302, 200), Color(0, 0, 255), Color(255, 0, 0));
	LinearGradientBrush pthGrBrush_rectangle(PointF(95, 97), PointF(302, 200), Color(0, 255, 255), Color(255, 0, 255));

	gr.FillRectangle(&pthGrBrush_rectangle, rect_rectangle);


	//--------------------------Точка-----------------------------------------------------------


	float radius = 5.;
	RectF rect_point(rotation_point.X - radius, rotation_point.Y - radius, 2 * radius, 2 * radius);

	Pen pen_point(Color(0, 0, 0, 0)); //Контур
	gr.DrawEllipse(&pen_point, rect_point);
	SolidBrush brush_point(Color(255, 255, 0, 0)); //Заливка
	gr.FillEllipse(&brush_point, rect_point);

	g.DrawImage(&buffer, 0, 0, 0, 0, lpDrawItemStruct->rcItem.right, lpDrawItemStruct->rcItem.bottom, UnitPixel);
}


Drawer::~Drawer()
{
	GdiplusShutdown(work);
}


void CMFCApplication6Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	CWnd* my_wnd = FromHandle(GetDlgItem(IDC_MY_DRAW)->GetSafeHwnd());
	CRect frame;
	my_wnd->GetClientRect(frame);
	if (frame.PtInRect(point))
	{
		Picture.rotation_point = Gdiplus::PointF(point.x, point.y);

		Picture.rotate = 0;
		angle.SetPos(0);
		angle_value.SetWindowTextW(L"0");
		CString str_x;
		CString str_y;
		str_x.Format(L"%d", point.x);
		str_y.Format(L"%d", point.y);
		X.SetWindowTextW(str_x);
		Y.SetWindowTextW(str_y);
		Picture.Invalidate(FALSE);
	}
}


void CMFCApplication6Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	Picture.rotate = angle.GetPos();
	CString str;
	str.Format(L"%d", Picture.rotate);
	angle_value.SetWindowTextW(str);
	Picture.Invalidate(FALSE);
}

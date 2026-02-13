
// MFCApplication6Dlg.h : файл заголовка
//

#pragma once
#include <gdiplus.h>
#include "afxwin.h"

class Rotate : public CStatic
{
	DECLARE_DYNAMIC(Rotate)

protected:
	DECLARE_MESSAGE_MAP()
public:
	Rotate();
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	ULONG_PTR work;
	int flip;
	Gdiplus::PointF rotation_point;
	virtual ~Rotate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

// диалоговое окно CMFCApplication6Dlg
class CMFCApplication6Dlg : public CDialogEx
{
	// Создание
public:
	CMFCApplication6Dlg(CWnd* pParent = NULL);	// стандартный конструктор

	// Данные диалогового окна
	enum { IDD = IDD_MFCAPPLICATION6_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Rotate Picture;
	CEdit angle_value, X, Y;
	CSliderCtrl angle;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
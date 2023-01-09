#pragma once

#include "define.h"
class CTexture;

class CCore
{
	SINGLE(CCore); 
	//public:static type* GetInst() { static type mgr; return &mgr; } private:type(); ~type();
private:
	HWND m_hWnd;          // 메인 윈도우 핸들
	POINT m_ptRseolution; // 메인 윈도우 해상도
	HDC m_hDC;            // 메인 윈도우 Draw 할 DC

	CTexture* m_pMemTex;  // 백버퍼 덱스처

	// 자주 사용하는 GDI Object
	HBRUSH  m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN    m_arrPen[(UINT)PEN_TYPE::END];

public:
	int init(HWND _hWnd, POINT _ptResolution);
	void progress();

private:
	void CreateBrushPen();

public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC  GetMainDC() { return m_hDC; }
	POINT GetResolution(){ return m_ptRseolution; }
	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }

};

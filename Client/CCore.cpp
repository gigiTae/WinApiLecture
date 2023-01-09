#include "pch.h"
#include "CCore.h"

#include "CTimeMgr.h"
#include "CkeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CObject.h"
#include "CUIMgr.h"

#include "CResMgr.h"
#include "CTexture.h"

CCore::CCore()
	:m_hWnd(0)
	,m_ptRseolution{}
	,m_hDC(0)
	,m_arrBrush{}
	,m_arrPen{}
{

}

CCore::~CCore()
{
	ReleaseDC(m_hWnd, m_hDC); // main 윈도우 DC 는 릴리즈


	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
}


int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	m_hWnd = _hWnd;
	m_ptRseolution = _ptResolution;

	// 해상도에 맞게 윈도우 크기 조정
	RECT rt = { 0, 0,_ptResolution.x, _ptResolution.y };
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, true); // window 설정스타일에 맞는 rt값을 반환해준다.
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);

	m_hDC = GetDC(m_hWnd);

	// 이중 버퍼링 용도의 텍스처 한장을 만든다
	m_pMemTex = CResMgr::GetInst()->CreateTexture(L"BackBuffer", (UINT)m_ptRseolution.x, (UINT)m_ptRseolution.y);

	// 자주 사용 할 펜 브러쉬 생성
	CreateBrushPen();


	//Manager 초기화
	CPathMgr::GetInst()->init();
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CCamera::GetInst()->init();
	CSceneMgr::GetInst()->init();


	return S_OK;
}


void CCore::progress()
{
	// ==============
	// Manager Update
	// ==============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// ============
	// Scene Update
 	// =============
	CSceneMgr::GetInst()->update();

	// 충돌체크
	CCollisionMgr::GetInst()->update();

	// UI 이벤트 체크
	CUIMgr::GetInst()->update();


	// ============
	//   Redering
	// ============
	// 화면 Clear
	Rectangle(m_pMemTex->GetDC(), -1, -1, m_ptRseolution.x + 1, m_ptRseolution.y + 1);

	CSceneMgr::GetInst()->render(m_pMemTex->GetDC());
	CCamera::GetInst()->render(m_pMemTex->GetDC());

	BitBlt(m_hDC, 0, 0, m_ptRseolution.x, m_ptRseolution.y
		, m_pMemTex->GetDC(), 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// ================
	// 이벤트 지연처리
	// ================
	CEventMgr::GetInst()->update();


}

void CCore::CreateBrushPen()
{

	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);

    // red pen	// green pen	// blue pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
}


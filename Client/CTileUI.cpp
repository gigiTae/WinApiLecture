#include "pch.h"
#include "CTileUI.h"
#include "CUI.h"

#include "CResMgr.h"
#include "CTexture.h"
#include "CCamera.h"
#include "CScene.h"
#include "CScene_Tool.h"


CTileUI::CTileUI()
	:CUI(false)
	, m_pTex(nullptr)
	, m_pScene(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"NewTileTex", L"texture\\NewTile.bmp");
}

CTileUI::~CTileUI()
{
}

void CTileUI::render(HDC _dc)
{
	CUI::render(_dc);
	
	int iWidth = (int)m_pTex->Whidth();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetFinalPos();

	TransparentBlt(_dc
		, (int)(vPos.x)
		, (int)(vPos.y)
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));


}


void CTileUI::MouseLbtnClicked()
{
	m_pScene->SetImgIdx(8);
}
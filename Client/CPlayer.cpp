#include "pch.h"
#include "CPlayer.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CkeyMgr.h"
#include "CTimeMgr.h"

#include "CMissile.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"

CPlayer::CPlayer()
	: m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"Player1Tex", L"texture\\c1.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 10.f));
	GetCollider()->SetScale(Vec2(25.f, 20.f));
	
	//// Texture 로딩하기
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\PlayerAnimation.bmp");
	//
	//CreateAnimator();
	//GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.1f, 3);
	//GetAnimator()->Play(L"WALK_DOWN", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"WALK_DOWN");
	//for (UINT i = 0; i < pAnim->GetMaxFrame(); ++i)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f, -20.f);

}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	Vec2 vPos = GetPos();

	if (KEY_HOLD(KEY::W))
	{
		vPos.y -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::S))
	{
		vPos.y += 200.f * fDT;
	}
	if (KEY_HOLD(KEY::A))
	{
		vPos.x -= 200.f * fDT;
	}
	if (KEY_HOLD(KEY::D))
	{
		vPos.x += 200.f * fDT;
	}
	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	SetPos(vPos); // 상속을 받았으므로 수정해주기 위해서 함수를 호출한다.

	GetAnimator()->update();
}

void CPlayer::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Whidth();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	BLENDFUNCTION bf = {};
	bf.BlendOp = AC_SRC_OVER;
	bf.BlendFlags = 0;
	bf.AlphaFormat = 0;
	bf.SourceConstantAlpha = 126;

	AlphaBlend(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, bf);


	// 컴포넌트 (충돌체 ,etc...)가 있는경우
	component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissilePos = GetPos();
	vMissilePos.y -= GetScale().y / 2.f;


	// Missile Object
	CMissile* pMissile = new CMissile;
	pMissile->SetName(L"Missile_Player");
	pMissile->SetPos(vMissilePos);
	pMissile->SetScale(Vec2(25.f, 25.f));
	pMissile->SeDir(0.f, -1.f);

	CreateObject(pMissile, GROUP_TYPE::PROJ_PLAYER );
}


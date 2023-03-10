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
#include "CGravity.h"

#include "CRigidBody.h"


CPlayer::CPlayer()
	: m_pTex(nullptr)
	, m_eCurState(PLAYER_STATE::IDLE)
	, m_iDir(KEY::S)
	, m_ePrevState(PLAYER_STATE::IDLE)

{
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"Player1Tex", L"texture\\c1.bmp");

	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 24.f));
	GetCollider()->SetScale(Vec2(32.f, 28.f));
	
	CreateRigidBody();

	// Texture ?ε??ϱ?
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\PlayerAnimation.bmp");
	
	CreateAnimator();

	GetAnimator()->CreateAnimation(L"IDLE", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 3);
	GetAnimator()->CreateAnimation(L"WALK_LEFT", pTex, Vec2(0.f, 192.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_RIGHT", pTex, Vec2(0.f, 64.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_UP", pTex, Vec2(0.f, 128.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->CreateAnimation(L"WALK_DOWN", pTex, Vec2(0.f, 0.f), Vec2(64.f, 64.f), Vec2(64.f, 0.f), 0.2f, 4);
	GetAnimator()->Play(L"IDLE", true);

	CreateGravity();

}

CPlayer::~CPlayer()
{

}

void CPlayer::update()
{
	update_gravity();

	update_move();

	update_state();

	update_animation();


	if (KEY_TAP(KEY::SPACE))
	{
		CreateMissile();
	}

	GetAnimator()->update();

	m_ePrevState = m_eCurState;
}

void CPlayer::render(HDC _dc)
{

	//int iWidth = (int)m_pTex->Whidth();
	//int iHeight = (int)m_pTex->Height();

	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);
	//
	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = 0;
	//bf.SourceConstantAlpha = 126;

	//AlphaBlend(_dc
	//	, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeight / 2))
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, iWidth, iHeight
	//	, bf);


	// ??????Ʈ (?浹ü ,etc...)?? ?ִ°???
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

void CPlayer::update_state()
{
	if (KEY_TAP(KEY::A))
	{
		m_iDir = KEY::A;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::D))
	{
		m_iDir = KEY::D;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::W))
	{
		m_iDir = KEY::W;
		m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_TAP(KEY::S))
	{
		m_iDir = KEY::S;
		m_eCurState = PLAYER_STATE::IDLE;
	}

}

void CPlayer::update_move()
{

	CRigidBody* pRigid = GetRigidBody();

	if (KEY_HOLD(KEY::W))
	{
		pRigid->AddForce(Vec2(0.f, -200.f));
	}
	if (KEY_TAP(KEY::W))
	{
		pRigid->AddVelocity(Vec2(0.f, -100.f));
	}

	if (KEY_HOLD(KEY::S))
	{
		pRigid->AddForce(Vec2(0.f, 200.f));
	}
	if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}

	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_TAP(KEY::A))
	{
		pRigid->AddVelocity(Vec2(-100.f, 0.f));
	}

	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->AddVelocity(Vec2(100.f, 0.f));
	}

}

void CPlayer::update_animation()
{
	if (m_ePrevState != m_eCurState)
		return;

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		GetAnimator()->Play(L"IDLE", true);
	}
		break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == KEY::D)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else if (m_iDir == KEY::A)
			GetAnimator()->Play(L"WALK_LEFT", true);
		else if (m_iDir == KEY::W)
			GetAnimator()->Play(L"WALK_UP", true);
		else if (m_iDir == KEY::S)
			GetAnimator()->Play(L"WALK_DOWN", true);
	}

		break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DEAD:

		break;
	default:

		break;
	}
}

void CPlayer::update_gravity()
{
//	GetRigidBody()->AddForce(Vec2(0.f,500.f));

}


#include "pch.h"
#include "CTraceState.h"

#include "CScene.h"
#include "CSceneMgr.h"
#include "CPlayer.h"
#include "CMonster.h"

#include "CTimeMgr.h"



CTraceState::CTraceState()
	:CState(MON_STATE::TRACE)
{
}

CTraceState::~CTraceState()
{
}

void CTraceState::update()
{
	// Å¸°ÙÆÃ µÈ Player ¸¦ ÂÑ¾Æ°£´Ù.
	CPlayer* pPlayer = (CPlayer*)CSceneMgr::GetInst()->GetCurScene()->GetPlayer();
	Vec2 vPlayerpos = pPlayer->GetPos();

	Vec2 vMonPos = GetMonster()->GetPos();
	
	Vec2 vMonDir = vPlayerpos - vMonPos;
	vMonDir.Nomalize();

	vMonPos += vMonDir * GetMonster()->GetInfo().m_fSpeed * fDT;

	GetMonster()->SetPos(vMonPos);
	
};

void CTraceState::Enter()
{
}

void CTraceState::Exit()
{
}
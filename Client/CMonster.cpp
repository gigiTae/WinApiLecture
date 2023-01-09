#include "pch.h"
#include "CMonster.h"

#include "AI.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CResMgr.h"
#include "CCamera.h"

CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f, 0.f))
	, m_fSpeed(100.f)
	, m_fMaxDistance(50.f)
	, m_iDir(1)
	, m_HP(5)
	,m_pTex(nullptr)
{
	m_pTex = CResMgr::GetInst()->LoadTexture(L"BossTex", L"texture\\boss.bmp");

	
	CreateCollider();

	GetCollider()->SetScale(Vec2(25.f, 50.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}

void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI;
	m_pAI->m_pOwner = this;
}

void CMonster::update()
{
	m_pAI->update();
}

void CMonster::render(HDC _dc)
{
	int iWidth = (int)m_pTex->Whidth();
	int iHeight = (int)m_pTex->Height();

	Vec2 vPos = GetPos();

	//BitBlt(_dc
	//	, (int)(vPos.x - (float)(iWidth / 2))
	//	, (int)(vPos.y - (float)(iHeight / 2))
	//    , iWidth, iHeight
	//    , m_pTex->GetDC()
	//    , 0, 0, SRCCOPY);

	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	TransparentBlt(_dc
		, (int)(vPos.x - (float)(iWidth / 2))
		, (int)(vPos.y - (float)(iHeight / 2))
		, iWidth, iHeight
		, m_pTex->GetDC()
		, 0, 0, iWidth, iHeight
		, RGB(255, 0, 255));


	component_render(_dc);
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj =_pOther->GetObj();

	if (pOtherObj->GetName() == L"Missile_Player")
	{
		--m_HP;
		if (0 >= m_HP)
			DeleteObject(this);
	}
}
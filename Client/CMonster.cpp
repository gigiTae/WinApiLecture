#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CCollider.h"
#include "CResMgr.h"

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
	
}

void CMonster::update()
{
	return;
	Vec2 vCurPos = GetPos();

	// 진행 방향으로 시간당 m_fSpeed 만큼 이동
	vCurPos.x +=  m_fSpeed * m_iDir;

	// 배회 거리 기준점을 넘어섰는지 확인
	float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;

	if(0.f < fDist)
	{
		// 방향 변경
		m_iDir *= -1;
		vCurPos.x += fDist * m_iDir;
	}

	SetPos(vCurPos);
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
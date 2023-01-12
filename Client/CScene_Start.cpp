#include "pch.h"
#include "CScene_Start.h"

#include "CObject.h"

#include "CPlayer.h"
#include "CMonster.h"

#include "CCore.h"

#include "CPathMgr.h"
#include "CTexture.h"

#include "CCollisionMgr.h"
#include "CCollider.h"

#include "CKeyMgr.h"
#include "CSceneMgr.h"

#include "CCamera.h"
#include "AI.h"
#include "CIdleState.h"
#include "CTraceState.h"

#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

#include "CGround.h"

CScene_Start::CScene_Start()
	:m_bUseForce(false)
	,m_fForceRadius(500.f)
	,m_fCurRadius(0.f)
	,m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}

void CScene_Start::update()
{

	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)i);

		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					if (fLen < m_fForceRadius)
					{
						float fRatio = 1.f -(fLen / m_fForceRadius);
						float fForce = m_fForce * fRatio;

						vecObj[j]->GetRigidBody()->AddForce(vDiff.Nomalize() * fForce);
					}
				}
				vecObj[j]->update();
			}
		}
	}


	if (KEY_TAP(KEY::ENTER))
	{
		ChangeScene(SCENE_TYPE::TOOL);
	}

	//if (KEY_TAP(KEY::LBTN))
	//{
	//	Vec2 vLookAt =CCamera::GetInst()->GetRealPos(MOUSE_POS);
	//	CCamera::GetInst()->SetLookAt(vLookAt);
	//}

}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;

	SelectGDI gdi(_dc, BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 3.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}
	Vec2 vRenderPos =CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));
}



void CScene_Start::Enter()
{ 
	// Object 추가
	CObject* pObj = new CPlayer;
	
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	RegisterPlayer(pObj);

	//CObject* pOtherPlayer = pObj->Clone();
	//pOtherPlayer->SetPos(Vec2(340.f, 384.f));
	//AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);

	//CCamera::GetInst()->SetTarget(pObj);


	 //Monster Object 추가
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NOMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

	// 땅 물체 배치
	CObject* pGround = new CGround();
	pGround->SetPos(Vec2(640.f, 500.f));
	pGround->SetScale(Vec2(200.f ,60.f));
	AddObject(pGround, GROUP_TYPE::GROUND);


	// 타일 로딩
	LoadTile(L"Tile\\STAGE");

	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌 체크
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::TILE);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution/2.f);

	// Camera 효과 지정
	/*CCamera::GetInst()->FadeOut(5.f);
	CCamera::GetInst()->FadeIn(5.f);
	CCamera::GetInst()->BligBling(5.f);*/

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	CCollisionMgr::GetInst()->Reset();


}

void CScene_Start::CreateForce()
{

	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);

}

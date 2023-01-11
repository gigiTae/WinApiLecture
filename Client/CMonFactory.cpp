#include "pch.h"
#include "CMonFactory.h"

#include "CRigidBody.h"
#include "CMonster.h"
#include "AI.h"

#include "CTraceState.h"
#include "CIdleState.h"

CMonster* CMonFactory::CreateMonster(MON_TYPE _eType, Vec2 _vPos)
{
	CMonster* pMon = nullptr;


	switch (_eType)
	{
	case MON_TYPE::NOMAL:
		pMon = new CMonster;
		pMon->SetPos(_vPos);
		tMonInfo info = {};
		info.m_fAtt = 10.f;
		info.m_fAttRange = 50.f;
		info.m_fHp = 10.f;
		info.m_fRecogRange = 100.f;
		info.m_fSpeed = 150.f;

		pMon->SetMonInfo(info);

		pMon->CreateRigidBody();
		pMon->GetRigidBody()->SetMass(1.f);

		//AI* pAI = new AI;
		//pAI->AddState(new CIdleState);
		//pAI->AddState(new CTraceState);
		//pAI->SetCurState(MON_STATE::IDLE);

		//pMon->SetAI(pAI);

		break;
	//case MON_TYPE::RANGE:
	//	break;

	}

 	assert(pMon);

	return pMon;
}

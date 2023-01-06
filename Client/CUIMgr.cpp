#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CkeyMgr.h"

CUIMgr::CUIMgr()
	: m_pFocusedUI(nullptr)
{
}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI 확인
	m_pFocusedUI = GetFocusedUI();

	if (!m_pFocusedUI)
		return;

	// 2. Focused UI내에서 , 부모 UI포함, 자식 UI들 중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTarGetUI = GetTargetedUI(m_pFocusedUI);


	bool bLbtmAway = KEY_AWAY(KEY::LBTN);
	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	if (nullptr != pTarGetUI)
	{
		pTarGetUI->MouseOn();

		if (bLbtnTap)
		{
			pTarGetUI->MouseLbtnDown();
			pTarGetUI->m_bLbtnDown = true;
		}
		else if (bLbtmAway)
		{
			pTarGetUI->MouseLbtnUp();

			if (pTarGetUI->m_bLbtnDown)
			{
				pTarGetUI->MouseLbtnClicked();
			}

			// 왼쪽버튼 떼면 ,눌렸던 체크를 다시 해제한다.
			pTarGetUI->m_bLbtnDown = false;
		}
	}
}

void CUIMgr::SetFocusedUI(CUI* _pUI)
{
	// 이미 포커싱 중인 경우 or 포커싱 해제요청인 경우
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return; 
	}

	m_pFocusedUI = _pUI;

	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			break;
		}
	}

	vecUI.erase(iter);
	vecUI.push_back(m_pFocusedUI);
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	bool bLbtnTap = KEY_TAP(KEY::LBTN);

	// 기존 포커싱 ui 를 받아두고 변경되었는지 확인
	CUI* pFocusedUI = m_pFocusedUI;

	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// 왼쪽버튼 TAP이 발생햇다는 전제하
	vector<CObject*>::iterator targeriter =vecUI.end();
	vector<CObject*>::iterator iter = vecUI.begin();

	for (; iter != vecUI.end(); ++iter)
	{
		if (((CUI*)*iter)->IsMouseOn())
		{
			targeriter = iter;
		}

	}
	// 이번에 Focus 된 UI가 없다.
	if (vecUI.end() == targeriter)
	{
		return nullptr;
	}

	pFocusedUI = (CUI*)*targeriter;

	// 벡터 내에서 맨 뒤로  순번 교체
	vecUI.erase(targeriter);
	vecUI.push_back(pFocusedUI);

	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{

	bool bLbtmAway = KEY_AWAY(KEY::LBTN);


	// 1. 부모 UI 포함, 자식 UI 들중 실제 타겟팅 된 UI를 가져온다.
	CUI* pTargetUI = nullptr;

	static list<CUI*> queue;
	static vector<CUI*> vecNoneTarget;

	queue.clear();
	vecNoneTarget.clear();

	queue.push_back(_pParentUI);

	while (!queue.empty())
	{
		// 큐에서 데이터 하나 꺼내기
		CUI* pUI =queue.front();
		queue.pop_front();

		// 큐에서 꺼내온 UI가 TargetUI 인지 확인
	    // 2. 타겟 UI 들 중, 더 우선순위가 높은 기준은 더 낮을 계층의 자식 UI

		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}

			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	}
	// 왼쪽버튼 뗴면, 눌렸던 체크를 다시 해제한다.
	if (bLbtmAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{
			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	return pTargetUI;
}

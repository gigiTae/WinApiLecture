#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"

#include "CkeyMgr.h"

CUIMgr::CUIMgr()
{
}
CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);

	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtmAway = KEY_AWAY(KEY::LBTN);

	for (size_t i = 0; i < vecUI.size(); ++i)
	{
		CUI* pUI = (CUI*)vecUI[i];

		pUI = GetTargetedUI(pUI);

		if (nullptr != pUI)
		{
			pUI->MouseOn();

			if (bLbtnTap)
			{
				pUI->MouseLbtnDown();
				pUI->m_bLbtnDown = true;
			}
			else if (bLbtmAway)
			{
				pUI->MouseLbtnUp();

				if (pUI->m_bLbtnDown)
				{
					pUI->MouseLbtnClicked();
				}

				// 왼쪽버튼 떼면 ,눌렸던 체크를 다시 해제한다.
				pUI->m_bLbtnDown = false;
			}
		}

	}
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
 				vecNoneTarget.push_back(pUI);
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

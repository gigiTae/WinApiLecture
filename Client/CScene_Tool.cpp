#include "pch.h"
#include "CScene_Tool.h"

#include "CkeyMgr.h"
#include "CSceneMgr.h"
#include "CTile.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"

#include "CCore.h"
#include "CResMgr.h"

#include "resource.h"
#include "CUI.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CUIMgr.h"

void ChangeScsene(DWORD_PTR, DWORD_PTR);

CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)
{
}

CScene_Tool::~CScene_Tool()
{
}

void CScene_Tool::Enter()
{
	// 타일 생성
	CreateTile(5, 5);

	// UI 하나 만들어 보기
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f, 150.f));
	pPanelUI->SetPos(Vec2(vResolution.x-pPanelUI->GetScale().x, 0.f));


	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 30.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));
	pBtnUI->SetClikedCallBack(ChangeScsene,0 ,0);

	pPanelUI ->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	//CUI* pClonePannel = pPanelUI->Clone();
	//pClonePannel->SetPos(pClonePannel ->GetPos() + Vec2(-300.f, 0.f));
	//AddObject(pClonePannel, GROUP_TYPE::UI);

	//m_pUI = pClonePannel;

	// Camera Look 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);
}

void CScene_Tool::Exit()
{
	DeleteAll();
}

void CScene_Tool::update()
{
	CScene::update();

	SetTileIdx();

	if (KEY_TAP(KEY::LSHIFT))
	{
		//CUIMgr::GetInst()->SetFocusedUI(m_pUI);
		SaveTile(L"tile\\Test.tile");
	}

	if (KEY_TAP(KEY::CTRL))
	{
		LoadTile(L"tile\\Test.tile");
	}

}

void CScene_Tool::SetTileIdx()
{
	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;
		int iRow = (int)vMousePos.y / TILE_SIZE;

		if (vMousePos.x < 0.f || iTileX <= iCol 
			|| vMousePos.y <0.f || iTileY <=iRow)
			return;

		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);
		((CTile*)vecTile[iIdx])->AddImgIdx();
	}



}

void CScene_Tool::SaveTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;

	// 커널 오브젝트
	FILE* pFile = nullptr;
	
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	assert(pFile);
	
	// 데이터 저장
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);



	fclose(pFile);

}


void ChangeScsene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}



// =============================
//    Tile Count Window Proc
// =============================


INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK) 
		{
			UINT iXCount = GetDlgItemInt(hDlg, IDC_EDIT1, nullptr, false);
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

			// ToolScene 확인
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);

			pToolScene->DeleteGroup(GROUP_TYPE::TILE);
			pToolScene->CreateTile(iXCount,iYCount);

			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
#include "pch.h"
#include "CTile.h"

#include "CTexture.h"

CTile::CTile()
	:m_pTileTex(nullptr)
	,m_iIdx(24)
{
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	if (nullptr == m_pTileTex || -1 == m_iIdx)
		return;
	UINT iWidth  =m_pTileTex->Whidth();
	UINT iHeight =m_pTileTex->Height();

	UINT iMaxCol =iWidth / TILE_SIZE;
	UINT iMaxRow = iWidth / TILE_SIZE;


	UINT iCurRow = (UINT)m_iIdx / iMaxCol;
	UINT iCurCol = (UINT)m_iIdx & iMaxCol;

	// �̹��� ������ ��� �ε���
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(_dc
		, int(vRenderPos.x)
		, int(vRenderPos.y)
		, int(vScale.x)
		, int(vScale.y)
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);


}

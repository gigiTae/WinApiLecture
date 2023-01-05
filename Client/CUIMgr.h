#pragma once

class CUI;


class CUIMgr
{
	SINGLE(CUIMgr);

private:



public:
	void update();

private:
	CUI* GetTargetedUI(CUI* _pParentUI); // 부모 UI내에서 실제로 타겟팅된 UI를 찾아서 반환한다.

};


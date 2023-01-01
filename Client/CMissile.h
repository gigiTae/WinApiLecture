#pragma once
#include "CObject.h"

class CMissile :
	public CObject
{
private:
	float      m_fTheta; // 이동 방향

	Vec2       m_vDir;
public:
	void SeDir(float _x, float _y) 
	{ 
		m_vDir.x = _x;
		m_vDir.y = _y;
	}
public:
	virtual void update();
	virtual void render(HDC _dc);

public:
	virtual void OnCollisionEnter(CCollider* _pOther);

	CLONE(CMissile);
public:
	CMissile();
	~CMissile();
};


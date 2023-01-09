#pragma once
#include "CObject.h"
#include "CTexture.h"

class AI;

class CMonster :
    public CObject
{
private:
    CTexture* m_pTex;
    Vec2      m_vCenterPos;

    float     m_fSpeed; 
    int       m_HP;
    AI*       m_pAI;

public:
    float GetSpeed() { return m_fSpeed; }
    void  SetSpeed(float _f) { m_fSpeed = _f; }

    void SetAI(AI* _AI);

public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    virtual void OnCollisionEnter(CCollider* _pOther);
   
    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();
};


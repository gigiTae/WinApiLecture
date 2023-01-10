#pragma once
#include "CObject.h"
class CTextrue;

struct tMonInfo
{
    float   m_fHp;         // 체력
    float   m_fSpeed;      // 속도
    float   m_fRecogRange; // 인지 범위 
    float   m_fAttRange;   // 공격 범위
    float   m_fAtt;        // 공격력
};

class AI;

class CMonster :
    public CObject
{
private:
    CTexture* m_pTex;
    tMonInfo  m_tInfo;
    AI*       m_pAI;

public:
    float GetSpeed() { return m_tInfo.m_fSpeed; }
    void  SetSpeed(float _f) { m_tInfo.m_fSpeed = _f; }
    void SetAI(AI* _AI);
    const tMonInfo& GetInfo() { return m_tInfo; }


private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }

public:
    virtual void update();
    virtual void render(HDC _dc);

public:

    virtual void OnCollisionEnter(CCollider* _pOther);
   
    CLONE(CMonster);
public:
    CMonster();
    ~CMonster();

    friend class CMonFactory;
};


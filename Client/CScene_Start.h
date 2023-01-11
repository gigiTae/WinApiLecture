#pragma once
#include "CScene.h"


class CScene_Start :
    public CScene
{
private:
    Vec2   m_vForcePos;
    float  m_fForceRadius;
    float  m_fCurRadius;
    float  m_fForce;
    bool   m_bUseForce;


public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter(); // 부모쪽에서 상속받은 가상함수르 virtual 을 이용해서 표시하자
    virtual void Exit();

public:
    void CreateForce();

    
public:
    CScene_Start();
    ~CScene_Start();

};


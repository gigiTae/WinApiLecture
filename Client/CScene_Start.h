#pragma once
#include "CScene.h"


class CScene_Start :
    public CScene
{
public:
    virtual void update();
    virtual void Enter(); // 부모쪽에서 상속받은 가상함수르 virtual 을 이용해서 표시하자
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();

};


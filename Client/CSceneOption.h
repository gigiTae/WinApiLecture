#pragma once
#include "CScene.h"
class CSceneOption :
    public CScene
{
private:
    virtual void Enter();
    virtual void Exit();


public:
    CSceneOption();
    ~CSceneOption();

};


#pragma once
#include "CUI.h"

class CTexture;
class CScene_Tool;

class CTileUI :
    public CUI
{
private:
    CTexture* m_pTex;
    CScene_Tool* m_pScene;
public:

    virtual void MouseLbtnClicked();
    virtual void render(HDC _dc);
    void SetToolScene(CScene_Tool* _scene) { m_pScene = _scene; }

    CLONE(CTileUI);

public:
    CTileUI();
    ~CTileUI();

};


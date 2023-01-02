#pragma once
#include "CObject.h"
class CUI :
    public CObject
{

private:
    vector<CUI*>   m_vecChildUI;
    CUI* m_ParentUI;

    Vec2           m_vFinalPos;

public:

    Vec2 GetFinalPos() { return m_vFinalPos; }

    CUI* GetParent() { return m_ParentUI; }
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_ParentUI = this; }

public:
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);

    CLONE(CUI);
    
private:
    void update_child();
    void finalupdate_child();
    void render_child(HDC _dc);
public:

    CUI();
    ~CUI();
};


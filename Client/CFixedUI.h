#pragma once
#include "CUI.h"
class CFixedUI :
    public CUI
{

private:

public:
    virtual void update();
 
    CLONE(CFixedUI);
public:
    CFixedUI();
    ~CFixedUI();

};


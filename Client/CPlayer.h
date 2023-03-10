#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    JUMP,
    DEAD,
};

enum class PLAYER_ATTACK_STATE
{
    NOMAL_ATT_1,
    NOMAL_ATT_2,
    NOMAL_ATT_3,

    SKILL_ATT_1,
    // ..
};


enum class KEY;
class CTexture;

class CPlayer :
    public CObject
{
private:
    CTexture*   m_pTex;

    PLAYER_STATE   m_eCurState;
    PLAYER_STATE   m_ePrevState;
    KEY            m_iDir;

public:
    virtual void update();
    virtual void render(HDC _dc);

private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

    CLONE(CPlayer);
public:
    CPlayer();
    ~CPlayer();

};


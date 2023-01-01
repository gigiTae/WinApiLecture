#pragma once


// 프레임 동기화
// 동일 프레임 내에서 같은 키에 대해, 입력 이벤트를 가져단다.

// 2. 키 입력 이벤트 처리
// tap, hold, away




enum class KEY_STATE
{
	NONE, // 눌리지 않음, 이전에도 눌리지 않은 상태
	TAP, // 막 누른 시점
	HOLD, // 누르고 있는
	AWAY, // 막 뗸 시점
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,

	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	SPACE,
	ENTER,
	ESC,

	LAST,

};

struct tKeyInfo
{
	// KEY ekey -> 본인의 인덱스가 곧 키이므로 저장할 필요가 없다.
	KEY_STATE eState; // 키의 상태값
	bool      bPrevPush;  // 이전 프레임에서 눌렸는지 여부
};

class CKeyMgr
{
	SINGLE(CKeyMgr);
private:
	vector<tKeyInfo> m_vecKey; // 벡터와 이넘클래스, 구조체 이용해서 공간 만드는 방법 다시 숙지하자

public:
	void init();
	void update();

public:
	KEY_STATE GetKeyState(KEY _eKey)
	{
		return m_vecKey[(int)_eKey].eState;
	}

};


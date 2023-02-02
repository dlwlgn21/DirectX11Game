#pragma once
#include "Engine.h"
#include "jhMath.h"

using namespace jh::math;

namespace jh
{
	enum class eKeyCode
	{
		// Alphabet
		Q, W, E, R, T, Y, U, I, O, P,
		A, S, D, F, G, H, J, K, L,
		Z, X, C, V, B, N, M,

		// Special Key
		ENTER, ESC, L_SHIFT, L_ALT, L_CTRL,
		SPACE, LEFT, RIGHT, UP, DOWN,
		L_BUTTON, R_BUTTON,

		// NumPad
		NUM_0, NUM_1, NUM_2,
		NUM_3, NUM_4, NUM_5,
		NUM_6, NUM_7, NUM_8,
		NUM_9,

		// Num Line
		N_0, N_1, N2, N_3, N_4, N5, N_6, N_7, N8, N_9,

		COUNT
	};

	enum class eKeyState
	{
		DOWN,
		PRESSED,
		UP,
		NONE
	};

	class Input
	{
	public:
		struct Key
		{
			eKeyCode keyCode;
			eKeyState state;
			bool bIsPressed;
		};

	public:
		static void Initialize();
		static void Update();
		static void Render(HDC hdc);
		static eKeyState GetKeyState(eKeyCode keyCode);
		static Vector2 GetMousePos() { return mMousePos; }
		static Vector2 GetMousePos(HWND hwnd);

	private:
		static std::vector<Key> mKeys;
		static Vector2 mMousePos;
		static HWND mHwnd;

	};
}
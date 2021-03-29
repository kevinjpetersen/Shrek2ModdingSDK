/*
	Copyright (c) 2021 Kevin J. Petersen https://github.com/kevinjpetersen/
*/

#pragma once
class Shrek2Input
{
public:
	enum Keys {
		A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NUMBER_0, NUMBER_1, NUMBER_2, NUMBER_3, NUMBER_4, NUMBER_5, NUMBER_6, NUMBER_7, NUMBER_8, NUMBER_9,
		TAB, ENTER, ESCAPE
	};

	bool OnKeyPress(Keys key);
	bool EnableConsoleProtection = true;
private:
	void ClearKeyInputBuffer();
	int KeyToVKey(Keys key);
	bool AllowKeyInput = true;
};


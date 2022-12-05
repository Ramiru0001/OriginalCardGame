#pragma once
#include <Gllibrary.h>
#include "../Base/Base.h"
#include "../Settings.h"

class SelectScene :public Base {
	enum {
		//ゲームタイトルのstateを作る
		eState_GameTitle
	};
private:
	char game_title[10][100] = {"gametitle","ABC","ABC"};
	CFont title_text;
	CFont select_title_text;
public:
	SelectScene();
	void Draw();
	void Update();
};
#pragma once
#include <Gllibrary.h>
#include "../Base/Base.h"
#include "../FreeNum.h"

class SelectScene :public Base {
	enum {
		//ゲームタイトルのstateを作る
		eState_Normal,
		eState_Random,
		eState_Auto,
	};
private:
	char game_title[10][100] = {"NormalMode(未実装)","RandomMode","DebugMode(Auto)"};
	CFont title_text;
	CFont select_title_text;
public:
	SelectScene();
	~SelectScene();
	void Draw();
	void Update();
};
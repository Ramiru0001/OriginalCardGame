#pragma once
#include <Gllibrary.h>
#include "../Base/Base.h"
#include "../FreeNum.h"

class SelectScene :public Base {
	enum {
		//ゲームタイトルのstateを作る
		eState_Normal,
		eState_Random,
		eState_Debug,
	};
private:
	char game_title[10][100] = {"NormalMode","RandomMode","DebugMode"};
	CFont title_text;
	CFont select_title_text;
	CImage ScreenDesign;
	CImage BackGround;
public:
	SelectScene();
	~SelectScene();
	void Draw();
	void Update();
};
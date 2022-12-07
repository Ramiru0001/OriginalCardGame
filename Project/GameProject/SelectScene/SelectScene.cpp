#include "SelectScene.h"
#include "../FreeNum.h"
#include "../Card/BaseCard.h"
#include <iostream>

SelectScene::SelectScene():Base(eType_Scene)
,title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64)
,select_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 80) {
	FreeNum::GameNum = 0;
}
SelectScene::~SelectScene() {
	//Base::KillAll();
}
void SelectScene::Draw() {
	//選択中のタイトルを大きく表示
	for (int i = 0; i < FreeNum::MaxGame; i++) {
		if (FreeNum::GameNum != i) {
			title_text.Draw(274, 214 + i * 150, 0, 0, 0, game_title[i]);
		}
		else {
			select_title_text.Draw(274, 214 + i * 150, 0, 0, 0, game_title[i]);
		}
	}
}
void SelectScene::Update() {
	//std::cout << "SelectScene" << std::endl;
	//std::cout << Base::m_list.size()<<std::endl;
	if (PUSH(CInput::eUp)) {
		if (FreeNum::GameNum > 0) {
			FreeNum::GameNum--;
		}
	}
	if (PUSH(CInput::eDown)) {
		if (FreeNum::GameNum < FreeNum::MaxGame - 1) {
			FreeNum::GameNum++;
		}
	}
	if (PUSH(CInput::eButton10)) {
		Base::KillAll();
		switch (FreeNum::GameNum) {
		case eState_Normal:
			Base::Add(new BaseCard(eState_Normal));
			break;
		case eState_Random:
			Base::Add(new BaseCard(eState_Random));
			break;
		case eState_Debug:
			Base::Add(new BaseCard(eState_Debug));
			break;
		}
	}
}

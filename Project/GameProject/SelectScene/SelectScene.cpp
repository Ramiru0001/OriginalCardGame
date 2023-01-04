#include "SelectScene.h"
#include "../FreeNum.h"
#include "../Card/BaseCard.h"
#include <iostream>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

SelectScene::SelectScene():Base(eType_Scene)
,title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64 * SCREEN_WIDTH / 1280)
,select_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 80 * SCREEN_WIDTH / 1280 ) {
	ScreenDesign= COPY_RESOURCE("BackGroundDesign1", CImage); 
	ScreenDesign.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	BackGround= COPY_RESOURCE("BackGround", CImage);
	BackGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	FreeNum::GameNum = 0;
}
SelectScene::~SelectScene() {
	//Base::KillAll();
}
void SelectScene::Draw() {
	BackGround.Draw();
	ScreenDesign.Draw();
	//選択中のタイトルを大きく表示
	for (int i = 0; i < FreeNum::MaxGame; i++) {
		if (FreeNum::GameNum != i) {
			title_text.Draw(274 * SCREEN_WIDTH / 1280 , (214 + i * 150) * SCREEN_HEIGHT / 720 , 1, 1, 1, game_title[i]);
		}
		else {
			select_title_text.Draw(274 * SCREEN_WIDTH / 1280 , (214 + i * 150) * SCREEN_HEIGHT / 720 , 1, 1, 1, game_title[i]);
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

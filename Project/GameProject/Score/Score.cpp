#include "Score.h"
#include "../Base/Base.h"
#include <iostream>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
//#include "ScoreTemp.h"
ScoreDraw::ScoreDraw() :Base(eType_Score) {
	Score::ScoreAdd();
	Score = Score::score;
	if (Score < 0) {
		Score = 0;
	}
	ImageSet();
}
void ScoreDraw::Draw() {
	int i = 0;
	Temp = Score;
	while (i<5) {
		int k;
		k = Temp % 10;
		Temp = Temp / 10;
		//printf("%d::k\n", k);
		m_img[k].SetPos(SCREEN_WIDTH * (1350-i*100) / 1920, SCREEN_HEIGHT * 750 / 1080);
		m_img[k].Draw();
		i++;
	}
}
void ScoreDraw::ImageSet() {
	for (int i = 0; i < 10; i++) {
		m_img[i] = COPY_RESOURCE("BrNumber", CImage);
		m_img[i].SetRect(i*39, 0, (i+1) * 39, 77);
		m_img[i].SetSize(SCREEN_WIDTH * 100 / 1920, SCREEN_HEIGHT * 190 / 1080);
	}
}
void ScoreDraw::Update() {
	//std::cout << Score << std::endl;
}
int Score::score = 0;
int Score::OpeCount = 0;
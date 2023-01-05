#pragma once
#include "../Base/Base.h"

class ScoreDraw :public Base {
private:
	CImage m_img[11];
	int Score;
	int Temp;
public:
	ScoreDraw();
	void Update();
	void ScorePlus();
	void Draw();
	void ImageSet();
};
class Score {
public:
	static int score;
	static int OpeCount;
	static void ScoreOpeReset() {
		score = 0;
		OpeCount = 0;
	}
	static void ScoreAdd() {
		score = (300 - OpeCount) * 150;
	}
	static void OpeCountUp() {
		OpeCount++;
	}
	static int ScoreOutPut() {
		return score;
	}
};
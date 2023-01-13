#include "Title.h"
#include "../Game/Play.h"
#include "../SelectScene/SelectScene.h"
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

Title::Title():Base(eType_Scene),
m_title_text("C:\\Windows\\Fonts\\msgothic.ttc", 64 * SCREEN_WIDTH / 1280)
{
	m_img = COPY_RESOURCE("Title",CImage);
	m_img.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT);
}

Title::~Title()
{
	//�^�C�g���j�����ɃQ�[���V�[���ֈڍs
	//Base::Add(new Play(0));
	Base::Add(new SelectScene());
}

void Title::Update()
{
	//�{�^���P�Ń^�C�g���j��
	if (PUSH(CInput::eButton10)) {
		m_kill = true;
	}
}

void Title::Draw()
{
	m_img.Draw();
	//�����\��
	m_title_text.Draw(64, 256, 0 ,0, 0, "PUSH Enter");
	//m_title_text.Draw(64, 512, 0, 0, 0, "Push Z");
}

#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
#include <Gllibrary.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
std::random_device rnd;
std::default_random_engine eng(rnd());
//�J�[�h���������Ƃ��ɌĂ΂��B
BaseCard::BaseCard():Base(eType_Card){
	ImageSet();
	CardListSet();
}
BaseCard::~BaseCard() {
}
void BaseCard::Update() {
	//���X�g����
	//ReserveOpen���X�g�́A��ԍŌ�̉摜�̂����Ń}�E�X�̍��N���b�N�������ăh���b�O���ė������Ƃ�
		//��ԋ߂��̃J�[�h�̏�ɍڂ����邩�𔻒肵�āA������������߂��A�\�Ȃ炻�̂܂܂ɂ���B

	//�܂��A�������Ƃ��ɂǂꂩ�̃J�[�h�͈͓̔����ǂ������������B
	//�͈͓���������A���X�g����Ԃ�
	InsideOrOutsideTheCard();
}
void BaseCard::ImageSet() {
	//�摜�̃R�s�[�A�؂���A�T�C�Y�ݒ�A���O�ݒ�B
	for (int i = 0; i<13; i++) {
		//�摜�̃R�s�[
		heart[i] = COPY_RESOURCE("TrumpCard", CImage);
		diamond[i] = COPY_RESOURCE("TrumpCard", CImage);
		club[i] = COPY_RESOURCE("TrumpCard", CImage);
		spade[i] = COPY_RESOURCE("TrumpCard", CImage);
		//�؂���
		spade[i].SetRect(23 + 293.6 * i, 23, 294 + 293.6 * i, 23 + 406);
		heart[i].SetRect(23 + 293.6 * i, 452, 294 + 293.6 * i, 452 + 406);
		diamond[i].SetRect(23 + 293.6 * i, 881, 294 + 293.6 * i, 881 + 406);
		club[i].SetRect(23 + 293.6 * i, 1310, 294 + 293.6 * i, 1310 + 406);
		//�T�C�Y�w��
		heart[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		diamond[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		club[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		spade[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
	}//�J�[�h�̌��̉摜�̃Z�b�g
	BehindCard = COPY_RESOURCE("TrumpBehind", CImage);
	BehindCard.SetRect(23, 23, 294, 429);
	BehindCard.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
}
void BaseCard::Draw() {
	//Foundation_list
	/*heart[0].SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	heart[0].SetPos(SCREEN_WIDTH * 0 / 1920, SCREEN_HEIGHT * 0 / 1080);
	heart[0].Draw(); 
	diamond[0].SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	diamond[0].SetPos(SCREEN_WIDTH * 210 / 1920, SCREEN_HEIGHT * 0 / 1080);
	diamond[0].Draw();
	club[0].SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	club[0].SetPos(SCREEN_WIDTH * 420 / 1920, SCREEN_HEIGHT * 0 / 1080);
	club[0].Draw();
	spade[0].SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	spade[0].SetPos(SCREEN_WIDTH * 630 / 1920, SCREEN_HEIGHT * 0 / 1080);
	spade[0].Draw();*/
	//Stock_list
	/*BehindCard.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	BehindCard.SetPos(SCREEN_WIDTH * 1710 / 1920, SCREEN_HEIGHT * 0 / 1080);
	BehindCard.Draw();*/
	//Waste_list
	/*heart[0].SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
	heart[0].SetPos(SCREEN_WIDTH * 1500 / 1920, SCREEN_HEIGHT * 0 / 1080);
	heart[0].Draw();*/
	//Reserve_list
	/*heart[0].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 0) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw();*/ 
	/*heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 1) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw(); 
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 2) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw(); 
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 3) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw(); 
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 4) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw(); 
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 5) / 1920, SCREEN_HEIGHT * 350 / 1080);
	heart[0].Draw();
	BehindCard.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
	BehindCard.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 6) / 1920, SCREEN_HEIGHT * 350 / 1080);
	BehindCard.Draw();
	heart[0].SetPos(SCREEN_WIDTH * (25 + (250 + 20) * 6) / 1920, SCREEN_HEIGHT * 380 / 1080);
	heart[0].Draw();*/

	//���X�g��ǂݍ���ŁA���̃��X�g�̐����̉摜��\��������
	LoadTheListAndDraw();
}
void BaseCard::CardListSet() {
	//std::cout << Remaining_list.size() << std::endl;
	while (!Remaining_list.empty()) {
		//std::cout << Remaining_list.size() << std::endl;
		//�c���Ă���J�[�h�̐�
		int RemainingCard_num = Remaining_list.size();
		//�c���Ă���J�[�h�̐��̒��ŁA�����𐶐�����֐����쐬�B
		std::uniform_int_distribution<int> CardRan(0, RemainingCard_num - 1);
		//Itr�́A���X�g��N�Ԗڂ��w���B�ŏ��̗v�f������
		auto Itr = Remaining_list.begin();
		//CardRan(eng)�Ԗڂ̗v�f���擾�BItr�̃|�C���^�����̐���
		std::advance(Itr, CardRan(eng));
		//���ɏ�������J�[�h�̐���
		int NextProcessCardNum = *Itr;
		//Remaining_list����A�g�p�����l���폜
		Remaining_list.remove(NextProcessCardNum);
		//�J�[�h�̐������e���X�g�ɓ����
		switch (RemainingCard_num) {
		case 52:
			Reserve_listOpen0.push_front(NextProcessCardNum);
			break;
		case 51:
			Reserve_listOpen1.push_front(NextProcessCardNum);
			break;
		case 50:
			Reserve_list1.push_front(NextProcessCardNum);
			break;
		case 49:
			Reserve_listOpen2.push_front(NextProcessCardNum);
			break;
		case 48:
		case 47:
			Reserve_list2.push_front(NextProcessCardNum);
			break;
		case 46:
			Reserve_listOpen3.push_front(NextProcessCardNum);
			break;
		case 45:
		case 44:
		case 43:
			Reserve_list3.push_front(NextProcessCardNum);
			break;
		case 42:
			Reserve_listOpen4.push_front(NextProcessCardNum);
			break;
		case 41:
		case 40:
		case 39:
		case 38:
			Reserve_list4.push_front(NextProcessCardNum);
			break;
		case 37:
			Reserve_listOpen5.push_front(NextProcessCardNum);
			break;
		case 36:
		case 35:
		case 34:
		case 33:
		case 32:
			Reserve_list5.push_front(NextProcessCardNum);
			break;
		case 31:
			Reserve_listOpen6.push_front(NextProcessCardNum);
			break;
		case 30:
		case 29:
		case 28:
		case 27:
		case 26:
		case 25:
			Reserve_list6.push_front(NextProcessCardNum);
			break;
		default:
			Stock_list.push_front(NextProcessCardNum);
			break;
		}
	}
	//std::cout << Remaining_list.size() << std::endl;
	std::cout << "Stock :";
	for (auto const& i : Stock_list) {
		std::cout << "," << i ;
	}
	std::cout <<std::endl<< " Reserve_list0 :" ; 
	for (auto const& i : Reserve_list0) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list1 :" ;
	for (auto const& i : Reserve_list1) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list2 :" ;
	for (auto const& i : Reserve_list2) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list3 :" ;
	for (auto const& i : Reserve_list3) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list4 :" ;
	for (auto const& i : Reserve_list4) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list5 :" ;
	for (auto const& i : Reserve_list5) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list6 :" ;
	for (auto const& i : Reserve_list6) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Foundation_list :" ;
	/*for (auto const& i : Foundation_list) {
		std::cout << "," << i;
	}*/
}
void BaseCard::CardNumToImage(int ThatCardNumber) {
	//�Ă΂ꂽ��A���̈����̃J�[�h��m_img�Ɏw��
	if (ThatCardNumber < 13) {
		m_img = heart[ThatCardNumber];
	}
	else if (ThatCardNumber < 26) {
		m_img = diamond[ThatCardNumber - 12];
	}
	else if (ThatCardNumber < 39) {
		m_img = club[ThatCardNumber - 25];
	}
	else{
		m_img = spade[ThatCardNumber - 38];
	}
}
void BaseCard::LoadTheListAndDraw() {
	auto Itr = Reserve_list0.begin();
	int LineNum = 0;//�s�i���o�[
	int RowNum = 0;//��i���o�[
	int ListCount = 0;//���X�g��N�Ԗ�
	int Space = 20;//��D�̋�
	//Reserve_listOpen0:1�ԍ�
	RowNum = 0;
	while (ListCount < Reserve_list0.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen0.begin();
	while (ListCount < Reserve_listOpen0.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen1:2���
	RowNum = 1;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list1.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen1.begin();
	while (ListCount < Reserve_listOpen1.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen2:3���
	RowNum = 2;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list2.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen2.begin();
	while (ListCount < Reserve_listOpen2.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen3:4���
	RowNum = 3;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list3.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen3.begin();
	while (ListCount < Reserve_listOpen3.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen4:5���
	RowNum = 4;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list4.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen4.begin();
	while (ListCount < Reserve_listOpen4.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen5:6���
	RowNum = 5;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list5.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen5.begin();
	while (ListCount < Reserve_listOpen5.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen6:7���
	RowNum = 6;
	LineNum = 0;
	ListCount = 0;
	while (ListCount < Reserve_list6.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	ListCount = 0;
	Itr = Reserve_listOpen6.begin();
	while (ListCount < Reserve_listOpen6.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080);
		m_img.Draw();
		LineNum++;
		ListCount++;
	}
	//Stock_list:1���ł���������w�i�摜��\��
	if (0 < Stock_list.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 1710 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Waste_list:1���ł���������Ō�̉摜��\��
	if (0 < Waste_list.size()) {
		Itr = Waste_list.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 1500 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Foundation_list0
	if (0 < Foundation_list0.size()) {
		Itr = Foundation_list0.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 0 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Foundation_list1
	if (0 < Foundation_list1.size()) {
		Itr = Foundation_list1.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 210 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Foundation_list2
	if (0 < Foundation_list2.size()) {
		Itr = Foundation_list2.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 420 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Foundation_list3
	if (0 < Foundation_list3.size()) {
		Itr = Foundation_list3.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 630 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
}
void BaseCard::InsideOrOutsideTheCard() {
	//��i���o�[
	int RowNum = 0;
	//�s�i���o�[
	int LineNum = Reserve_listOpen0.size() + Reserve_list0.size() - 1;
	CVector2D mouse_pos = CInput::GetMousePoint();
	//Reserve0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve0;
		ClickCard = true;
	}
	//Reserve1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen1.size() + Reserve_list1.size() - 1;
	RowNum = 1;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve1;
		ClickCard = true;
	}
	//Reserve2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen2.size() + Reserve_list2.size() - 1;
	RowNum = 2;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve2;
		ClickCard = true;
	}
	//Reserve3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen3.size() + Reserve_list3.size() - 1;
	RowNum = 3;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve3;
		ClickCard = true;
	}
	//Reserve4�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen4.size() + Reserve_list4.size() - 1;
	RowNum = 4;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve4;
		ClickCard = true;
	}
	//Reserve5�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen5.size() + Reserve_list5.size() - 1;
	RowNum = 5;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve5;
		ClickCard = true;
	}
	//Reserve6�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen6.size() + Reserve_list6.size() - 1;
	RowNum = 6;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (300 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_Reserve6;
		ClickCard = true;
	}
	//Foundation0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 0 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 200 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation0;
		ClickCard = true;
	}
	//Foundation1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 210 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 410 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation1;
		ClickCard = true;
	}
	//Foundation2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 420 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 620 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation2;
		ClickCard = true;
	}
	//Foundation3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 630 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 830 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation3;
		ClickCard = true;
	}
	//stock�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 1710 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 1910 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_stock;
		ClickCard = true;
	}
}
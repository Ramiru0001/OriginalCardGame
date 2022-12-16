#pragma warning( disable : 4789 )
#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
#include <Gllibrary.h>
#include <algorithm>
#include <vector>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
std::random_device rnd;
std::default_random_engine eng(rnd());
//�J�[�h���������Ƃ��ɌĂ΂��B
BaseCard::BaseCard(int GameMode):Base(eType_Card){
	SelectMode = GameMode;
	DebugMode_State = eState_Normal;
	ImageSet();
	CardListSet();
}
BaseCard::~BaseCard() {
}
void BaseCard::Update() {
	MousePos = CInput::GetMousePoint();
	switch (SelectMode) {
	case eState_Normal:
		NormalMode();
		break;
	case eState_Random:
		RandomMode();
		break;
	case eState_Debug:
		DebugMode();
		break;
	case eState_Auto:
		AutoMode();
		break;
	}
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
	//���X�g��ǂݍ���ŁA���̃��X�g�̐����̉摜��\��������
	//MouseOverCard��true�Ȃ�}�E�X�̂Ƃ���ɃJ�[�h���w��
	LoadTheListAndDraw();
	MovingCardDraw();
}
void BaseCard::CardListSet() {
	switch (SelectMode) {
	case eState_Random:
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
		break;
	case eState_Normal:
	case eState_Auto:
	case eState_Debug:
		while (!Remaining_list.empty()) {
			//�󔒃��X�g���X�V
			AddEmpty4CardList();
			//std::cout << Remaining_list.size() << std::endl;
			//std::cout << Empty_list.size() << std::endl;
			//�c���Ă�J�[�h���X�g�̒��ŗ���
			std::uniform_int_distribution<int> CardRanN(0, Remaining_list.size() - 1);
			std::uniform_int_distribution<int> CardRan4(0, Empty_list4Types.size() - 1);
			//std::cout << "make ran" << std::endl;
			//���ׂẴC�e���[�^�쐬
			auto RemainingItr = Remaining_list.begin();
			//auto EmptyItr = Empty_list.begin();
			auto HeartItr = HeartCard_list.end();
			auto DiamondItr = DiamondCard_list.end();
			auto ClubItr = ClubCard_list.end();
			auto SpadeItr = SpadeCard_list.end();
			auto Empty4Itr = Empty_list4Types.begin();
			//std::cout << "makeItr" << std::endl;
			//�����_���ȏꏊ�ɓ���邽�߂̗�������
			//�l���X�g�̍ŏ��ɃJ�[�h��ǉ�
			std::advance(RemainingItr, CardRanN(eng));
			//std::cout << "itrRanfin" << std::endl;
			//�ړ�������J�[�h�̎�ނ�I�ԁB
			std::advance(Empty4Itr, CardRan4(eng));
			int Addlist = *Empty4Itr;
			int AddNum;//�ړ������鐔��
			//AddNum�ɑ�����āA�l���폜
			/*std::cout << "Heart :" << HeartCard_list.size() << std::endl;
			std::cout << "Diamond :" << DiamondCard_list.size() << std::endl;
			std::cout << "Club :" << ClubCard_list.size() << std::endl;
			std::cout << "Spade :" << SpadeCard_list.size() << std::endl;*/
			switch (Addlist) {
			case eNum_Heart:
				//std::cout << "heart" << std::endl;
				HeartItr--;
				AddNum = *HeartItr;
				HeartCard_list.pop_back();
				break;
			case eNum_Club:
				//std::cout << "Club" << std::endl;
				ClubItr--;
				AddNum = *ClubItr;
				ClubCard_list.pop_back();
				break;
			case eNum_Spade:
				//std::cout << "Spade" << std::endl;
				SpadeItr--;
				AddNum = *SpadeItr;
				SpadeCard_list.pop_back();
				break;
			case eNum_Diamond:
				//std::cout << "Diamond" << std::endl;
				DiamondItr--;
				AddNum = *DiamondItr;
				DiamondCard_list.pop_back();
				break;
			}
			//std::cout << "listchoicefin" << std::endl;
			//std::cout << "RemainingItr: " << *RemainingItr << std::endl;
			//�J�[�h�̐������e���X�g�ɓ����
			switch (*RemainingItr) {
			case 0:
				Reserve_list0.push_back(AddNum);
				break;
			case 1:
			case 2:
				Reserve_list1.push_back(AddNum);
				break;
			case 3:
			case 4:
			case 5:				
				Reserve_list2.push_back(AddNum);
				break;
			case 6:
			case 7:
			case 8:
			case 9:
				Reserve_list3.push_back(AddNum);
				break;
			case 10:
			case 11:
			case 12:
			case 13:
			case 14:
				Reserve_list4.push_back(AddNum);
				break;
			case 15:
			case 16:
			case 17:
			case 18:
			case 19:
			case 20:
				Reserve_list5.push_back(AddNum);
				break;
			case 21:
			case 22:
			case 23:
			case 24:
			case 25:
			case 26:
			case 27:
				Reserve_list6.push_back(AddNum);
				break;
			default:
				Stock_list.push_front(AddNum);
				break;
			}
			//std::cout << "switchfin" << std::endl;
			Remaining_list.remove(*RemainingItr);
		}
		//std::cout << "�z�u��" << std::endl;
		//std::cout << Stock_list.size() << std::endl;
		int CountNum = Stock_list.size();
		while (CountNum > 0) {
			auto StockItr = Stock_list.begin();
			std::uniform_int_distribution<int> CardRanS(Stock_list.size()- CountNum, Stock_list.size() - 1);
			std::advance(StockItr, CardRanS(eng));
			int CopyNum = *StockItr;
			Stock_list.remove(*StockItr);
			Stock_list.push_front(CopyNum);
			CountNum--;
		}
		break;
	}
	AllCardNumOutPut_debug();
}
void BaseCard::CardNumToImage(int ThatCardNumber) {
	//�Ă΂ꂽ��A���̈����̃J�[�h��m_img�Ɏw��
	if (ThatCardNumber < 13) {
		m_img = heart[ThatCardNumber];
	}
	else if (ThatCardNumber < 26) {
		m_img = club[ThatCardNumber - 13];
	}
	else if (ThatCardNumber < 39) {
		m_img = diamond[ThatCardNumber - 26];
	}
	else{
		m_img = spade[ThatCardNumber - 39];
	}
}
void BaseCard::LoadTheListAndDraw() {
	auto Itr = Reserve_list0.begin();
	int LineNum = 0;//�s�i���o�[
	int RowNum = 0;//��i���o�[
	int ListCount = 0;//���X�g��N�Ԗ�
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
		if (MovingLane != eNum_ReserveOpen0 || !CardMoving) {
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list0.size()*Space)+OpenSpace* (LineNum- Reserve_list0.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen1 || !CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list1.size() * Space) + OpenSpace * (LineNum - Reserve_list1.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen2 || !CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list2.size() * Space) + OpenSpace * (LineNum - Reserve_list2.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen3 || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list3.size() * Space) + OpenSpace * (LineNum - Reserve_list3.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen4 || !CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list4.size() * Space) + OpenSpace * (LineNum - Reserve_list4.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen5 || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list5.size() * Space) + OpenSpace * (LineNum - Reserve_list5.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_ReserveOpen6 || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920, SCREEN_HEIGHT * (350 + (Reserve_list6.size() * Space) + OpenSpace * (LineNum - Reserve_list6.size())) / 1080);
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
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
		if (MovingLane != eNum_Waste || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * 1500 / 1920, SCREEN_HEIGHT * 0 / 1080);
			m_img.Draw();
		}
	}
	//Foundation_list0
	if (0 < Foundation_list0.size()) {
		Itr = Foundation_list0.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane != eNum_Foundation0 || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * 0 / 1920, SCREEN_HEIGHT * 0 / 1080);
			m_img.Draw();
		}
	}
	//Foundation_list1
	if (0 < Foundation_list1.size()) {
		Itr = Foundation_list1.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane != eNum_Foundation1 || !CardMoving){
			m_img.SetPos(SCREEN_WIDTH * 210 / 1920, SCREEN_HEIGHT * 0 / 1080);
			m_img.Draw();
		}
	}
	//Foundation_list2
	if (0 < Foundation_list2.size()) {
		Itr = Foundation_list2.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane != eNum_Foundation2 || !CardMoving){
			m_img.SetPos(SCREEN_WIDTH * 420 / 1920, SCREEN_HEIGHT * 0 / 1080);
			m_img.Draw();
		}
	}
	//Foundation_list3
	if (0 < Foundation_list3.size()) {
		Itr = Foundation_list3.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane != eNum_Foundation3 || ! CardMoving){
			m_img.SetPos(SCREEN_WIDTH * 630 / 1920, SCREEN_HEIGHT * 0 / 1080);
			m_img.Draw();
		}
	}
}
void BaseCard::InsideOrOutsideTheCard() {
	//��i���o�[
	int RowNum = 0;
	//�s�i���o�[
	int LineNum = Reserve_listOpen0.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	//Reserve0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list0.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list0.size() * Space)+(LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen0;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen1.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 1;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list1.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list1.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen1;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen2.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 2;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list2.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list2.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen2;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen3.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 3;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list3.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list3.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen3;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve4�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen4.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 4;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list4.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list4.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen4;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve5�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen5.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 5;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list5.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list5.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen5;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve6�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen6.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 6;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= MousePos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list6.size() * Space)) / 1080 <= MousePos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list6.size() * Space) + (LineNum * OpenSpace)) / 1080 >= MousePos.y) {
		ListNum = eNum_ReserveOpen6;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Foundation0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 0 / 1920 <= MousePos.x && SCREEN_WIDTH * 200 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_Foundation0;
		MouseOverCard = true;
		return;
	}
	//Foundation1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 210 / 1920 <= MousePos.x && SCREEN_WIDTH * 410 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_Foundation1;
		MouseOverCard = true;
		return;
	}
	//Foundation2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 420 / 1920 <= MousePos.x && SCREEN_WIDTH * 620 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_Foundation2;
		MouseOverCard = true;
		return;
	}
	//Foundation3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 630 / 1920 <= MousePos.x && SCREEN_WIDTH * 830 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_Foundation3;
		MouseOverCard = true;
		return;
	}
	//stock�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 1710 / 1920 <= MousePos.x && SCREEN_WIDTH * 1910 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_stock;
		MouseOverStockList = true;
	}
	else {
		MouseOverStockList = false;
	}
	//waste�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 1500 / 1920 <= MousePos.x && SCREEN_WIDTH * 1700 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		ListNum = eNum_Waste;
		MouseOverCard = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	else {
		MouseOverCard = false;
		MouseOverReserve = false;
		MouseOverReserveAndWasteLists = false;
	}
}
void BaseCard::MovingCardDraw() {
	auto Itr = Reserve_listOpen0.begin();
	int LineNum = 0;//�s�i���o�[
	int RowNum = 0;//��i���o�[
	int ListCount = 0;//���X�g��N�Ԗ�
	int CardLen;//���̗�̒���
	int ListSize;//���̗�̋󔒂̐�
	//Reserve_listOpen0:1�ԍ�
	ListSize=Reserve_listOpen0.size() - 1;
	if (ListSize < 0 ) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	while (ListCount < Reserve_listOpen0.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen0 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH *( CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen1:2���
	RowNum = 1;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen1.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen1.begin();
	while (ListCount < Reserve_listOpen1.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen1 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen2:3���
	RowNum = 2;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen2.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen2.begin();
	while (ListCount < Reserve_listOpen2.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen2 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen3:4���
	RowNum = 3;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen3.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen3.begin();
	while (ListCount < Reserve_listOpen3.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen3 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen4:5���
	RowNum = 4;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen4.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen4.begin();
	while (ListCount < Reserve_listOpen4.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen4 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen5:6���
	RowNum = 5;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen5.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen5.begin();
	while (ListCount < Reserve_listOpen5.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen5 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}
	//Reserve_listOpen6:7���
	RowNum = 6;
	LineNum = 0;
	ListCount = 0;
	ListSize = Reserve_listOpen6.size() - 1;
	if (ListSize < 0) {
		ListSize = 0;
	}
	CardLen = ListSize * OpenSpace + 375;
	Itr = Reserve_listOpen6.begin();
	while (ListCount < Reserve_listOpen6.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen6 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * (CardLen / 2 - LineNum * OpenSpace) / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
		Itr++;
	}//Waste_list
	if (0 < Waste_list.size()) {
		Itr = Waste_list.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_Waste && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
	}
	//Foundation_list0
	if (0 < Foundation_list0.size()) {
		Itr = Foundation_list0.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane == eNum_Foundation0 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
	}
	//Foundation_list1
	if (0 < Foundation_list1.size()) {
		Itr = Foundation_list1.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane == eNum_Foundation1 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
	}
	//Foundation_list2
	if (0 < Foundation_list2.size()) {
		Itr = Foundation_list2.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane == eNum_Foundation2 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
	}
	//Foundation_list3
	if (0 < Foundation_list3.size()) {
		Itr = Foundation_list3.end();
		Itr--;
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		if (MovingLane == eNum_Foundation3 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
	}
}
void BaseCard::BothStockAndWaste() {
	if (Stock_list.size() > 0) {
		auto ItrStock = Stock_list.begin();
		AddToMoved_Log(eNum_stock, *ItrStock, eNum_Waste, 0);
		Waste_list.push_back(*ItrStock);
		Stock_list.pop_front();
	}
	else {
		Stock_list.swap(Waste_list);
		AddToMoved_Log(eNum_Waste, 0, eNum_stock, 0);
	}
}
void BaseCard::OpenListCheckAndAdd() {
	if (Reserve_listOpen0.empty()) {
		if (!Reserve_list0.empty()) {
			auto Itr = Reserve_list0.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve0, *Itr, eNum_ReserveOpen0, 0);
			Reserve_listOpen0.push_back(*Itr);
			Reserve_list0.pop_back();
		}
	}
	if (Reserve_listOpen1.empty()) {
		if (!Reserve_list1.empty()) {
			auto Itr = Reserve_list1.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve1, *Itr, eNum_ReserveOpen1, 0);
			Reserve_listOpen1.push_back(*Itr);
			Reserve_list1.pop_back();
		}
	}
	if (Reserve_listOpen2.empty()) {
		if (!Reserve_list2.empty()) {
			auto Itr = Reserve_list2.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve2, *Itr, eNum_ReserveOpen2, 0);
			Reserve_listOpen2.push_back(*Itr);
			Reserve_list2.pop_back();
		}
	}
	if (Reserve_listOpen3.empty()) {
		if (!Reserve_list3.empty()) {
			auto Itr = Reserve_list3.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve3, *Itr, eNum_ReserveOpen3, 0);
			Reserve_listOpen3.push_back(*Itr);
			Reserve_list3.pop_back();
		}
	}
	if (Reserve_listOpen4.empty()) {
		if (!Reserve_list4.empty()) {
			auto Itr = Reserve_list4.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve4, *Itr, eNum_ReserveOpen4, 0);
			Reserve_listOpen4.push_back(*Itr);
			Reserve_list4.pop_back();
		}
	}
	if (Reserve_listOpen5.empty()) {
		if (!Reserve_list5.empty()) {
			auto Itr = Reserve_list5.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve5, *Itr, eNum_ReserveOpen5, 0);
			Reserve_listOpen5.push_back(*Itr);
			Reserve_list5.pop_back();
		}
	}
	if (Reserve_listOpen6.empty()) {
		if (!Reserve_list6.empty()) {
			auto Itr = Reserve_list6.end();
			Itr--;
			AddToMoved_Log(eNum_Reserve6, *Itr, eNum_ReserveOpen6, 0);
			Reserve_listOpen6.push_back(*Itr);
			Reserve_list6.pop_back();
		}
	}
}
void BaseCard::CheckAddToReserveList(){
	//empty�̏ꍇ�A�����܂�
	//empty����Ȃ��ꍇ��
	/*if (EmptyOrNotTheList(MovingLane)|| EmptyOrNotTheList(ListNum)) {
		return;
	}*/
	auto MovingCard_Itr = Reserve_listOpen0.end();
	auto SearchCard_Itr = Reserve_listOpen0.end();
	//ListNum�̔ԍ��̃��X�g�ɒǉ�
	//�����Ă�J�[�h���X�g�́A���肷��J�[�h���w��
	//empty�������ꍇ�̏�����empty�ł͂Ȃ��ꍇ�̏������K�v
	//std::cout << "Itr�w��fin";
	switch (MovingLane) {
	case eNum_Waste:
		MovingCard_Itr = Waste_list.end();
		MovingCard_Itr--;
		break;
	case eNum_ReserveOpen0:
		MovingCard_Itr = Reserve_listOpen0.begin();
		break;
	case eNum_ReserveOpen1:
		MovingCard_Itr = Reserve_listOpen1.begin();
		break;
	case eNum_ReserveOpen2:
		MovingCard_Itr = Reserve_listOpen2.begin();
		break;
	case eNum_ReserveOpen3:
		MovingCard_Itr = Reserve_listOpen3.begin();
		break;
	case eNum_ReserveOpen4:
		MovingCard_Itr = Reserve_listOpen4.begin();
		break;
	case eNum_ReserveOpen5:
		MovingCard_Itr = Reserve_listOpen5.begin();
		break;
	case eNum_ReserveOpen6:
		MovingCard_Itr = Reserve_listOpen6.begin();
		break;
	case eNum_Foundation0:
		MovingCard_Itr = Foundation_list0.end();
		MovingCard_Itr--;
		break;
	case eNum_Foundation1:
		MovingCard_Itr = Foundation_list1.end();
		MovingCard_Itr--;
		break;
	case eNum_Foundation2:
		MovingCard_Itr = Foundation_list2.end();
		MovingCard_Itr--;
		break;
	case eNum_Foundation3:
		MovingCard_Itr = Foundation_list3.end();
		MovingCard_Itr--;
		break;
	}
	//std::cout << "MoveItr�w��fin";
	//�Ŋ��̃J�[�h�̃��X�g�̍Ō���C�e���[�^�w��
	switch (ListNum) {
	case eNum_ReserveOpen0:
		SearchCard_Itr = Reserve_listOpen0.end();
		break;
	case eNum_ReserveOpen1:
		SearchCard_Itr = Reserve_listOpen1.end();
		break;
	case eNum_ReserveOpen2:
		SearchCard_Itr = Reserve_listOpen2.end();
		break;
	case eNum_ReserveOpen3:
		SearchCard_Itr = Reserve_listOpen3.end();
		break;
	case eNum_ReserveOpen4:
		SearchCard_Itr = Reserve_listOpen4.end();
		break;
	case eNum_ReserveOpen5:
		SearchCard_Itr = Reserve_listOpen5.end();
		break;
	case eNum_ReserveOpen6:
		SearchCard_Itr = Reserve_listOpen6.end();
		break;
	}
	//std::cout << "SearchItr�w��fin";
	//���ׂ�J�[�h�̃C�e���[�^
	SearchCard_Itr--;
	//std::cout << "SearchItr--"<<std::endl;
	//std::cout << "SearchPointer=ListNum" << *SearchCard_Itr << " ";
	//std::cout << "MovePointer=MovingLane" << *MovingCard_Itr << std::endl;
	//�d�˂���J�[�h�̏ꍇ
	if (( * SearchCard_Itr + 12 == *MovingCard_Itr || *SearchCard_Itr + 38 == *MovingCard_Itr ||
		*SearchCard_Itr - 14 == *MovingCard_Itr || *SearchCard_Itr - 40 == *MovingCard_Itr) && (*SearchCard_Itr != 0 && *SearchCard_Itr != 13 && *SearchCard_Itr != 26 && *SearchCard_Itr != 39)) {
		AddToMoved_Log(MovingLane,*MovingCard_Itr,ListNum,*SearchCard_Itr);
		//std::cout << "IfItr�Q��fin";
		//�������J�[�h��reserve_open�̃J�[�h�̏ꍇ�A
		switch (MovingLane) {
		case eNum_ReserveOpen0:
		case eNum_ReserveOpen1:
		case eNum_ReserveOpen2:
		case eNum_ReserveOpen3:
		case eNum_ReserveOpen4:
		case eNum_ReserveOpen5:
		case eNum_ReserveOpen6:
			// ���ׂẴJ�[�h���ړ������āA���Ƃ̃��X�g��O��������B
			while (!EmptyOrNotTheList(MovingLane)) {
				AddToListend(ListNum, *MovingCard_Itr);
				if (CheckListSize(MovingLane) >= 2) {
					MovingCard_Itr++;
				}
				//std::cout << "DeleteNow";
				DeleteListFront(MovingLane);
				//std::cout << "Deletefin";
				if (EmptyOrNotTheList(MovingLane)) {
					break;
				}
			}
			break;
		case eNum_Waste:
		case eNum_Foundation0:
		case eNum_Foundation1:
		case eNum_Foundation2:
		case eNum_Foundation3:
			//foundation���X�g���瓮�����ꍇ�B
			//�ړ���̃��X�g�ɒǉ�
			AddToListend(ListNum, *MovingCard_Itr);
			//std::cout << "DeleteendNow";
			//�����Ă�J�[�h�̃��X�g���폜
			RemoveFromListend(MovingLane);
			//std::cout << "DeleteendFin";
			//�P���̏ꍇ�̏������������ĂȂ����߁A�������������Ƃ܂Ƃ��ɓ����Ȃ�
			break;
		}
	}
}
void BaseCard::CheckAddToFoundationList() {
	auto MovingCard_Itr = Reserve_listOpen0.begin();
	auto SearchCard_Itr = Reserve_listOpen0.begin();
	//foundationList�ɒu����Ȃ�u��
	// ���̃J�[�h�̃��[����empty�̏ꍇ=�J�[�h���P�̏ꍇ
	//MovingLane�ɃJ�[�h���Ȃ��ꍇ�A�I��
	if (EmptyOrNotTheList(MovingLane)) {
		return;
	}
	switch (MovingLane) {
	case eNum_Waste:
		MovingCard_Itr = Waste_list.end();
		break;
	case eNum_ReserveOpen0:
		MovingCard_Itr = Reserve_listOpen0.end();
		break;
	case eNum_ReserveOpen1:
		MovingCard_Itr = Reserve_listOpen1.end();
		break;
	case eNum_ReserveOpen2:
		MovingCard_Itr = Reserve_listOpen2.end();
		break;
	case eNum_ReserveOpen3:
		MovingCard_Itr = Reserve_listOpen3.end();
		break;
	case eNum_ReserveOpen4:
		MovingCard_Itr = Reserve_listOpen4.end();
		break;
	case eNum_ReserveOpen5:
		MovingCard_Itr = Reserve_listOpen5.end();
		break;
	case eNum_ReserveOpen6:
		MovingCard_Itr = Reserve_listOpen6.end();
		break;
	case eNum_Foundation0:
		MovingCard_Itr = Foundation_list0.end();
		break;
	case eNum_Foundation1:
		MovingCard_Itr = Foundation_list1.end();
		break;
	case eNum_Foundation2:
		MovingCard_Itr = Foundation_list2.end();
		break;
	case eNum_Foundation3:
		MovingCard_Itr = Foundation_list3.end();
		break;
	}
	MovingCard_Itr--;
	// empty����Ȃ��āA���A�Q~�P�R�̏ꍇ
	//�������J�[�h�̃C�e���[�^�w�肱���܂�
	//�J�[�h��1�̏ꍇ
	if (*MovingCard_Itr == 0 || *MovingCard_Itr == 13 || *MovingCard_Itr == 26 || *MovingCard_Itr == 39) {
		//���X�g�Ƀf�[�^����
		if (*MovingCard_Itr == 0) {
			AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation0, 0);
			Foundation_list0.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 13) {
			AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation1, 0);
			Foundation_list1.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 26) {
			AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation2, 0);
			Foundation_list2.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 39) {
			AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation3, 0);
			Foundation_list3.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		RemoveFromListend(MovingLane);
		return;
	}
	//���̃J�[�h�̖͗l��foundationlist��empty����Ȃ��ꍇ�G
	//�J�[�h��2~13�̏ꍇ
	else {
		if (1 <= *MovingCard_Itr && *MovingCard_Itr <= 12 && !Foundation_list0.empty()) {
			SearchCard_Itr = Foundation_list0.end();
			SearchCard_Itr--;
			//Movinglane�̍Ō�̃J�[�h�̃|�C���^�������ꂩ��foundationList�̃|�C���^�{�P��������ړ�
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation0, *SearchCard_Itr);
				Foundation_list0.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (14 <= *MovingCard_Itr && *MovingCard_Itr <= 25 && !Foundation_list1.empty()) {
			SearchCard_Itr = Foundation_list1.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation1, *SearchCard_Itr);
				Foundation_list1.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (27 <= *MovingCard_Itr && *MovingCard_Itr <= 38 && !Foundation_list2.empty()) {
			SearchCard_Itr = Foundation_list2.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation2, *SearchCard_Itr);
				Foundation_list2.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (40 <= *MovingCard_Itr && *MovingCard_Itr <= 51 && !Foundation_list3.empty()) {
			SearchCard_Itr = Foundation_list3.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				AddToMoved_Log(MovingLane, *MovingCard_Itr, eNum_Foundation3, *SearchCard_Itr);
				Foundation_list3.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
	}
}
void BaseCard::RemoveFromListend(int ListNum) {
	//���X�g����폜
	switch (ListNum) {
	case eNum_Waste:
		Waste_list.pop_back();
		break;
	case eNum_ReserveOpen0:
		Reserve_listOpen0.pop_back();
		break;
	case eNum_ReserveOpen1:
		Reserve_listOpen1.pop_back();
		break;
	case eNum_ReserveOpen2:
		Reserve_listOpen2.pop_back();
		break;
	case eNum_ReserveOpen3:
		Reserve_listOpen3.pop_back();
		break;
	case eNum_ReserveOpen4:
		Reserve_listOpen4.pop_back();
		break;
	case eNum_ReserveOpen5:
		Reserve_listOpen5.pop_back();
		break;
	case eNum_ReserveOpen6:
		Reserve_listOpen6.pop_back();
		break;
	case eNum_Foundation0:
		Foundation_list0.pop_back();
		break;
	case eNum_Foundation1:
		Foundation_list1.pop_back();
		break;
	case eNum_Foundation2:
		Foundation_list2.pop_back();
		break;
	case eNum_Foundation3:
		Foundation_list3.pop_back();
		break;
	}
}
void BaseCard::AddToListend(int ListNum, int AddNum) {
	switch (ListNum) {
	case eNum_ReserveOpen0:
		Reserve_listOpen0.push_back(AddNum);
		break;
	case eNum_ReserveOpen1:
		Reserve_listOpen1.push_back(AddNum);
		break;
	case eNum_ReserveOpen2:
		Reserve_listOpen2.push_back(AddNum);
		break;
	case eNum_ReserveOpen3:
		Reserve_listOpen3.push_back(AddNum);
		break;
	case eNum_ReserveOpen4:
		Reserve_listOpen4.push_back(AddNum);
		break;
	case eNum_ReserveOpen5:
		Reserve_listOpen5.push_back(AddNum);
		break;
	case eNum_ReserveOpen6:
		Reserve_listOpen6.push_back(AddNum);
		break;
	}
}
bool BaseCard::EmptyOrNotTheList(int ListNum) {
	switch (ListNum) {
	case eNum_Reserve0:
		return Reserve_list0.empty();
		break;
	case eNum_Reserve1:
		return Reserve_list1.empty();
		break;
	case eNum_Reserve2:
		return Reserve_list2.empty();
		break;
	case eNum_Reserve3:
		return Reserve_list3.empty();
		break;
	case eNum_Reserve4:
		return Reserve_list4.empty();
		break;
	case eNum_Reserve5:
		return Reserve_list5.empty();
		break;
	case eNum_Reserve6:
		return Reserve_list6.empty();
		break;
	case eNum_ReserveOpen0:
		return Reserve_listOpen0.empty();
		break;
	case eNum_ReserveOpen1:
		return Reserve_listOpen1.empty();
		break;
	case eNum_ReserveOpen2:
		return Reserve_listOpen2.empty();
		break;
	case eNum_ReserveOpen3:
		return Reserve_listOpen3.empty();
		break;
	case eNum_ReserveOpen4:
		return Reserve_listOpen4.empty();
		break;
	case eNum_ReserveOpen5:
		return Reserve_listOpen5.empty();
		break;
	case eNum_ReserveOpen6:
		return Reserve_listOpen6.empty();
		break;
	case eNum_Foundation0:
		return Foundation_list0.empty();
		break;
	case eNum_Foundation1:
		return Foundation_list1.empty();
		break;
	case eNum_Foundation2:
		return Foundation_list2.empty();
		break;
	case eNum_Foundation3:
		return Foundation_list3.empty();
		break;
	case eNum_Waste:
		return Waste_list.empty();
		break;
	default:
		return false;
	}
}
void BaseCard::DeleteListFront(int ListNum) {
	switch (ListNum) {
	case eNum_ReserveOpen0:
		Reserve_listOpen0.pop_front();
		break;
	case eNum_ReserveOpen1:
		Reserve_listOpen1.pop_front();
		break;
	case eNum_ReserveOpen2:
		Reserve_listOpen2.pop_front();
		break;
	case eNum_ReserveOpen3:
		Reserve_listOpen3.pop_front();
		break;
	case eNum_ReserveOpen4:
		Reserve_listOpen4.pop_front();
		break;
	case eNum_ReserveOpen5:
		Reserve_listOpen5.pop_front();
		break;
	case eNum_ReserveOpen6:
		Reserve_listOpen6.pop_front();
		break;
	}
}
int BaseCard::CheckListSize(int ListNum) {
	switch (ListNum) {
	case eNum_ReserveOpen0:
		return Reserve_listOpen0.size();
		break;
	case eNum_ReserveOpen1:
		return Reserve_listOpen1.size();
		break;
	case eNum_ReserveOpen2:
		return Reserve_listOpen2.size();
		break;
	case eNum_ReserveOpen3:
		return Reserve_listOpen3.size();
		break;
	case eNum_ReserveOpen4:
		return Reserve_listOpen4.size();
		break;
	case eNum_ReserveOpen5:
		return Reserve_listOpen5.size();
		break;
	case eNum_ReserveOpen6:
		return Reserve_listOpen6.size();
		break;
	case eNum_Waste:
		return Waste_list.size();
		break;
	case eNum_Foundation0:
		return Foundation_list0.size();
		break;
	case eNum_Foundation1:
		return Foundation_list1.size();
		break;
	case eNum_Foundation2:
		return Foundation_list2.size();
		break;
	case eNum_Foundation3:
		return Foundation_list3.size();
		break;
	}
}
void BaseCard::MoveIfK() {
	//�����A�������Ă�J�[�h�̃��X�g��ReserveOpen��waste�ŁA���̈�ԍŏ���K�Ȃ�
	//�ړ��\
	if (eNum_ReserveOpen0 <= MovingLane && MovingLane <= eNum_ReserveOpen6){}
	else if (MovingLane == eNum_Waste){}
	else {
		return;
	}
	auto Itr= Reserve_listOpen0.begin();
	//�܂��Areserveopen�̏ꍇ�A
	//K���ǂ������m���߂�
	switch (MovingLane) {
	case eNum_ReserveOpen0:
		Itr= Reserve_listOpen0.begin();
		break;
	case eNum_ReserveOpen1:
		Itr = Reserve_listOpen1.begin();
		break;
	case eNum_ReserveOpen2:
		Itr = Reserve_listOpen2.begin();
		break;
	case eNum_ReserveOpen3:
		Itr = Reserve_listOpen3.begin();
		break;
	case eNum_ReserveOpen4:
		Itr = Reserve_listOpen4.begin();
		break;
	case eNum_ReserveOpen5:
		Itr = Reserve_listOpen5.begin();
		break;
	case eNum_ReserveOpen6:
		Itr = Reserve_listOpen6.begin();
		break;
	case eNum_Waste:
		Itr = Waste_list.end();
		Itr--;
		break;
	}
	//K�̏ꍇ
	if (*Itr == 12 || *Itr == 25 || *Itr == 38 || *Itr == 51) {
		AddToMoved_Log(MovingLane, *Itr, ListNum, 0);
		//movingLane����ListNum�ցA�v�f�̒��g�����ׂĈړ�
		switch (MovingLane) {
		case eNum_ReserveOpen0:
		case eNum_ReserveOpen1:
		case eNum_ReserveOpen2:
		case eNum_ReserveOpen3:
		case eNum_ReserveOpen4:
		case eNum_ReserveOpen5:
		case eNum_ReserveOpen6:
			// ���ׂẴJ�[�h���ړ������āA���Ƃ̃��X�g��O��������B
			while (!EmptyOrNotTheList(MovingLane)) {
				AddToListend(ListNum, *Itr);
				if (CheckListSize(MovingLane) >= 2) {
					Itr++;
				}
				DeleteListFront(MovingLane);
				if (EmptyOrNotTheList(MovingLane)) {
					break;
				}
			}
			break;
		case eNum_Waste:
			//foundation���X�g���瓮�����ꍇ�B
			//�ړ���̃��X�g�ɒǉ�
			AddToListend(ListNum, *Itr);
			//�����Ă�J�[�h�̃��X�g���폜
			RemoveFromListend(MovingLane);
			//�P���̏ꍇ�̏������������ĂȂ����߁A�������������Ƃ܂Ƃ��ɓ����Ȃ�
			break;
		}
	}
}
void BaseCard::NormalMode() {
	//���ׂĂ�reserve���X�g�̃J�[�h�������Ȃ�����A
	if (CheckReserveEmpty()) {
		SelectMode = eState_Auto;
		//std::cout << "ModeChange" << std::endl;
	}
	//std::cout << CheckReserveEmpty() ;
	//��������J�[�h�̏�Ƀ}�E�X�����邩�ǂ���
	//����ꍇ,	MouseOverCard=true�ɂ���AListNum���X�V����B
	InsideOrOutsideTheCard();
	//���[�U�[����ɑ΂��鏈��
	UserOperation();
}
void BaseCard::RandomMode() {
	//���ׂĂ�reserve���X�g�̃J�[�h�������Ȃ�����A
	if (CheckReserveEmpty()) {
		SelectMode = eState_Auto;
	}
	//��������J�[�h�̏�Ƀ}�E�X�����邩�ǂ���
	//����ꍇ,	MouseOverCard=true�ɂ���AListNum���X�V����B
	InsideOrOutsideTheCard();
	//���[�U�[����ɑ΂��鏈��
	UserOperation();
	
}
void BaseCard::AutoMode() {
	InsideOrOutsideTheCard();
	//ListNum��moving���[�����P���������߂�
	for (int i = eNum_Waste; i <= eNum_ReserveOpen6; i++) {
		MovingLane = i;
		if (MovingLane == eNum_Waste) {
			BothStockAndWaste();
		}
		if ((eNum_Reserve0 <= i && eNum_Reserve6 >= i)|| EmptyOrNotTheList(MovingLane)) {
			//std::cout << MovingLane << ": continue" << std::endl;
			continue;
		}
		//BothStockAndWaste();
		//for (auto const& i : Waste_list) {
		//	std::cout << "," << i<<std::endl;
		//}
		//std::cout<<"MovingLane" << MovingLane << ":" << CheckListSize(MovingLane) << ":" << EmptyOrNotTheList(MovingLane) << std::endl;
		for (int k = eNum_Foundation0; k <= eNum_Foundation3; k++) {
			ListNum = k;
			//std::cout << "ListNum" << ListNum << ":" << CheckListSize(ListNum) << ":" << EmptyOrNotTheList(ListNum) << std::endl;
			CheckAddToFoundationList();
			OpenListCheckAndAdd();
			/*for (int a = 0; a <MiddleMovingCount ; a++) {
				std::cout << MiddleMovingCheck<< MiddleMovingCount<<" " << a << " " << MiddleMovingList[a] << " " << MiddleMovingLane[a] << std::endl;
			}*/
			if (EmptyOrNotTheList(MovingLane)) {
				break;
			}
		}
		if (EmptyOrNotTheList(MovingLane)) {
			break;
		}
		for (int k = eNum_ReserveOpen0; k <= eNum_ReserveOpen6; k++) {
			ListNum = k;
			//std::cout << "ListNum" << ListNum << ":" << CheckListSize(ListNum) << ":" << EmptyOrNotTheList(ListNum) << std::endl;
			//��̃��X�g���󔒂̏ꍇ
			if (EmptyOrNotTheList(ListNum)) {
				//�������Ă郊�X�g�̈�ԍŏ��̃J�[�h��K�̏ꍇ�A
				//�u����
				//std::cout << "NoCheckfin";
				MoveIfK();
				//std::cout << "NoCheck"<<std::endl;
			}
			//��̃��X�g���󔒂���Ȃ��ꍇ
			else if (!EmptyOrNotTheList(ListNum)) {
				//std::cout << "Check";

				CheckAddToReserveList();
				//std::cout << "Checkfin"<<std::endl;
			}
			//std::cout << "Open";
			OpenListCheckAndAdd();
			//std::cout << "Openfin" << std::endl;
			
			if (EmptyOrNotTheList(MovingLane)) {
				break;
			}
		}
		//	Movinglane��r�����瑼�̃��[���Ɉړ��\�����ׂ�
		Middle_Judgement_CheckAddToReserveList(MovingLane);
		Middle_CheckAddToReserveList();

		//�����ŁA�r�����烌�[���ړ��̏����B�ړ��\�̏ꍇ�̂�
		if (MiddleMovingCheck) {
			Middle_CheckAddToReserveList();
		}
	}
	//�Q�[���N���A�̏ꍇ��loop����ɂȂ��Ă���B
	//����������ă��X�^�[�g�̏����ɕύX
	if (ClearOrNot() == false) {
		ReStartGame(LoopOrNot());
	}
	//�����A������Ƃ�5��ȏ�J��Ԃ��Ă���ꍇ�A�����ĂȂ��ꍇ�A�ŏ������蒼��
	//���������J�[�h�F����������̗񖼂����Ă̏����H
}
bool BaseCard::CheckReserveEmpty() {
	if (EmptyOrNotTheList(eNum_Reserve0) &&
		EmptyOrNotTheList(eNum_Reserve1) &&
		EmptyOrNotTheList(eNum_Reserve2) &&
		EmptyOrNotTheList(eNum_Reserve3) &&
		EmptyOrNotTheList(eNum_Reserve4) &&
		EmptyOrNotTheList(eNum_Reserve5) &&
		EmptyOrNotTheList(eNum_Reserve6)) {
		return true;
	}
	else {
		return false;
	}
}
void BaseCard::AddToMoved_Log(int BeforeList, int Beforeard, int afterList, int afterCard) {
	//�������J�[�h�A���X�g�A(����΁A��������̃J�[�h)�A���X�g
	//���X�g�F�������J�[�h�F���X�g�F��������̃J�[�h
	int addnum = BeforeList * 100000 + Beforeard * 10000 + afterList * 100 + afterCard;
	Moved_Log.push_back(addnum);
	if (Moved_Log.size() >= 500) {
		Moved_Log.pop_front();
	}
}
bool BaseCard::LoopOrNot() {
	if (Moved_Log.size() == 0) {
		return false;
	}
	int Max = Moved_Log.size();
	auto ChoiceItr = Moved_Log.begin();
	auto Sortitr = Moved_Log.begin();
	int ChoiceItrCount = 0;
	int SortItrCount = 0;
	//�P�x��������������ꍇ
	bool finish = false;
	//���󃋁[�v�������Ă�ꍇ�B
	bool CorrectNow = false;
	//�`�F�b�N���̃J�E���g
	int CheckCount = 0;
	//�����̂����������牽�x�������m���߂�
	int LoopCount = 0;
	//���[�v�̃`�F�b�N����|�C���g�̐������w��
	int PointNum;
	do{
		//�܂��A�����̂�T��
		while (ChoiceItrCount < Max && ChoiceItrCount < 200) {
			//�\�[�g�̕��̏���
			for (int SortItrCount = 0; SortItrCount < Max; SortItrCount++) {
				if (*ChoiceItr == *Sortitr) {
					//������������Aitr�ƃJ�E���g�𑝂₵�ă��[�v������
					ChoiceItr++;
					ChoiceItrCount++;
					finish = true;
					break;
				}
				else {
					//���̏ꍇ�Atrue�ɂȂ邩�A�I���܂Ŏ��s��������
					Sortitr++;
					SortItrCount++;
				}
			}
			//�����������������Ă���Ȃ�A���[�v������
			if (finish==true) {
				break;
			}
			ChoiceItr++;
			ChoiceItrCount++;
			//�I�ԕ��̃C�e���[�^��200��������I���
			if (ChoiceItrCount >= 200) {
				return false;
			}
		}
		//finish��false�̏ꍇ�A�S�����[�v���Ă��Ȃ��̂�return;
		if (finish==false) {
			return false;
		}
		//���̐���������1�x�����灁���������������烋�[�v�Ƃ���B
		PointNum = *ChoiceItr;
		do {
			if (*ChoiceItr = *Sortitr) {
				//�����������J��Ԃ��Ă鐔�𐔂���B
				CheckCount++;
				//���������̐��ŁA���[�v�̐��𐔂���
				if (PointNum == *Sortitr) {
					LoopCount++;
				}
				else {
					//���[�v�̎w�����ԈႦ�Ă���ꍇ�́A�񐔂ƃ|�C���g�̏�����
					PointNum == *ChoiceItr;
					LoopCount = 0;
				}
				//�C�e���[�^��i�߂�
				ChoiceItr++;
				Sortitr++;
				//�C�e���[�^�̃J�E���g�𑝂₷
				ChoiceItrCount++;
				SortItrCount++;
				//���[�v�������Ă邩��true
				CorrectNow = true;
			}
			else {
				//���[�v�I��肾����false
				CorrectNow = false;
			}
		} while (ChoiceItrCount < Max && SortItrCount < Max && CorrectNow == true);
		//CorrectNow = false;�̏ꍇ�A�ŏ��ɖ߂�
	} while (CorrectNow==false);
	//�Ō�܂Ń��[�v�������Ă�ꍇ�G
	if (CorrectNow = true) {
		//�����Ă��Ԃ̎w��
		if (LoopCount >= 5 && CheckCount>=200) {
			return true;
		}
	}
	return false;
	//���̊֐��̂��ƁA���X�^�[�g�̃R�[�h������
}
void BaseCard::ReStartGame(bool NewGame) {
	//std::cout <<"TrueOrFalse: " << NewGame << std::endl;
	if (NewGame==false) {
		//std::cout << "return" << std::endl;
		return;
	}
	//std::cout << "Restart" << std::endl;
	//���X�g���I�[���N���A
	Stock_list.clear();
	Waste_list.clear();
	Reserve_list0.clear();
	Reserve_list1.clear();
	Reserve_list2.clear();
	Reserve_list3.clear();
	Reserve_list4.clear();
	Reserve_list5.clear();
	Reserve_list6.clear();
	Reserve_listOpen0.clear();
	Reserve_listOpen1.clear();
	Reserve_listOpen2.clear();
	Reserve_listOpen3.clear();
	Reserve_listOpen4.clear();
	Reserve_listOpen5.clear();
	Reserve_listOpen6.clear(); 
	Foundation_list0.clear();
	Foundation_list1.clear();
	Foundation_list2.clear();
	Foundation_list3.clear(); 
	Moved_Log.clear(); 
	Remaining_list.clear();
	Empty_list4Types.clear();
	//�J�[�h�������ʒu�֔z�u
	Remaining_list = AllCard_list;
	HeartCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };
	ClubCard_list = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };
	DiamondCard_list = { 26,27,28,29,30,31,32,33,34,35,36,37,38 };
	SpadeCard_list = { 39,40,41,42,43,44,45,46,47,48,49,50,51 };
	CardListSet();
}
bool BaseCard::ClearOrNot(){
	//�����A���ׂĂ�foundation���X�g��13���̃J�[�h����������true;
	if (Foundation_list0.size() == 13 && Foundation_list1.size() == 13 &&
		Foundation_list2.size() == 13 && Foundation_list3.size() == 13) {
		return true;
	}
	return false;
}
void BaseCard::UserOperation() {
	//���X�g����
	//���N���b�N�����Ƃ��A��������J�[�h�̏�Ƀ}�E�X���������ꍇ�B
	if (PUSH(CInput::eMouseL) && MouseOverCard) {
		//ListNum���g���āA���̃J�[�h�̍��W��ύX�B
		MovingLane = ListNum;
		CardMoving = true;
		//�}�E�X���Awaste���X�g��reserve���X�g�̂����ɂ���ꍇ
		if (MouseOverReserveAndWasteLists == true) {
			CheckAddToFoundationList();
		}
		if (MouseOverReserve == true) {
			//Middle_Judgement_CheckAddToReserveList();
		}
	}
	//�����A�������J�[�h�̃��X�g���󔒂���Ȃ��ꍇ�A�r���̃J�[�h����ړ��ł���Ȃ�΁A
	// �r������ړ��ł��邩�ǂ����̏���������֐����K�v
	//if(MovingLane)
	// ���̃J�[�h�̏ꏊ�ύX�ƁA�r������ړ��\�Ƃ����t���O��ON�ɂ���
	//�}�E�X�𗣂����Ƃ��A�}�E�X��reserve���X�g�̏�ɂ���ꍇ
	if (PULL(CInput::eMouseL) && MouseOverReserve && CardMoving) {
		//�}�E�X�̉��̃��X�g���󔒂ł��A�������Ă�J�[�h�̃��X�g���󔒂���Ȃ��ꍇ
		if (!EmptyOrNotTheList(MovingLane) && EmptyOrNotTheList(ListNum)) {
			//�������Ă郊�X�g�̈�ԍŏ��̃J�[�h��K�̏ꍇ�A
			//�u����
			MoveIfK();
		}
		//�}�E�X�̉��̃��X�g�Ɠ������Ă郊�X�g�̗������󔒂���Ȃ��ꍇ
		else if (!EmptyOrNotTheList(MovingLane) || !EmptyOrNotTheList(ListNum)) {
			CheckAddToReserveList();
		}
	}
	//�����Aopen�̃��X�g�ɉ����Ȃ���΁A�P���ړ�����B
	OpenListCheckAndAdd();
	if (FREE(CInput::eMouseL)) {
		CardMoving = false;
	}
	//�}�E�X���Astock���X�g�̂Ȃ��ɂ����
	//���L�[���������Ƃ��ɁA�X�g�b�N���X�g����wasteList�Ɉړ�
	if (PUSH(CInput::eLeft) || (MouseOverStockList && PUSH(CInput::eMouseL))) {
		BothStockAndWaste();
	}
}
void BaseCard::AddEmptyList() {
	Empty_list.clear();
	if (Reserve_list0.size() < 1) {
		Empty_list.push_back(eNum_Reserve0);
	}
	if (Reserve_list1.size() < 2) {
		Empty_list.push_back(eNum_Reserve1);
	}
	if (Reserve_list2.size() < 3) {
		Empty_list.push_back(eNum_Reserve2);
	}
	if (Reserve_list3.size() < 4) {
		Empty_list.push_back(eNum_Reserve3);
	}
	if (Reserve_list4.size() < 5) {
		Empty_list.push_back(eNum_Reserve4);
	}
	if (Reserve_list5.size() < 6) {
		Empty_list.push_back(eNum_Reserve5);
	}
	if (Reserve_list6.size() < 7) {
		Empty_list.push_back(eNum_Reserve6);
	}
	if (Stock_list.size() < 24) {
		Empty_list.push_back(eNum_stock);
	}
	std::cout << std::endl << " Empty_debug :";
	for (auto const& i : Empty_list) {
		std::cout << "," << i;
	}
}
void BaseCard::AllCardNumOutPut_debug() {
	/*std::cout << std::endl << " Empty_debug :";
	for (auto const& i : Empty_list) {
		std::cout << "," << i;
	}*/
	std::cout << std::endl << " Stock :";
	for (auto const& i : Stock_list) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Waste :";
	for (auto const& i : Waste_list) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list0 :";
	for (auto const& i : Reserve_list0) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list1 :";
	for (auto const& i : Reserve_list1) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list2 :";
	for (auto const& i : Reserve_list2) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list3 :";
	for (auto const& i : Reserve_list3) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list4 :";
	for (auto const& i : Reserve_list4) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list5 :";
	for (auto const& i : Reserve_list5) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_list6 :";
	for (auto const& i : Reserve_list6) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen0 :";
	for (auto const& i : Reserve_listOpen0) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen1 :";
	for (auto const& i : Reserve_listOpen1) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen2 :";
	for (auto const& i : Reserve_listOpen2) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen3 :";
	for (auto const& i : Reserve_listOpen3) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen4 :";
	for (auto const& i : Reserve_listOpen4) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen5 :";
	for (auto const& i : Reserve_listOpen5) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Reserve_listOpen6 :";
	for (auto const& i : Reserve_listOpen6) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Foundation_list0 :";
	for (auto const& i : Foundation_list0) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Foundation_list1 :";
	for (auto const& i : Foundation_list1) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Foundation_list2 :";
	for (auto const& i : Foundation_list2) {
		std::cout << "," << i;
	}
	std::cout << std::endl << " Foundation_list3 :" ;
	for (auto const& i : Foundation_list3) {
		std::cout << "," << i;
	}
	std::cout << std::endl;
}
void BaseCard::AddEmpty4CardList() {
	Empty_list4Types.clear();
	if (HeartCard_list.size() > 0) {
		Empty_list4Types.push_back(eNum_Heart);
	}
	if (DiamondCard_list.size() > 0) {
		Empty_list4Types.push_back(eNum_Diamond);
	}
	if (ClubCard_list.size() > 0) {
		Empty_list4Types.push_back(eNum_Club);
	}
	if (SpadeCard_list.size() > 0) {
		Empty_list4Types.push_back(eNum_Spade);
	}
}
void BaseCard::DebugMode() {
	//���[�h�؂�ւ�
	if(PUSH(CInput::eButton5)){
		if (DebugMode_State == eState_Normal) {
			DebugMode_State = eState_Auto;
		}
		else if (DebugMode_State == eState_Auto) {
			DebugMode_State = eState_Normal;
		}
	}
	if (PUSH(CInput::eButton10)) {
		ReStartGame(true);
	}
	switch (DebugMode_State) {
	case eState_Normal:
		NormalMode();
		break;
	case eState_Auto:
		AutoMode();
		break;
	}
}
void BaseCard::Middle_Judgement_CheckAddToReserveList(int MovingLane) {
	//false�ŏ�����
	MiddleMovingCheck = false;
	//std::cout << "start" <<std::endl;
	//�������鐔�̃J�E���g
	int MovingCount = 0;
	//MovingLane�𒲂ׂ����̃J�E���g�BN�Ԗ�
	int CheckCount = 0;
	//MovingItr�̃J�E���g
	int MovingItrCount = 0;
	//�������鐔��������
	MiddleMovingCount = 0;
	if (EmptyOrNotTheList(MovingLane) || eNum_ReserveOpen0 > MovingLane || MovingLane > eNum_ReserveOpen6) {
		return;
	}
	//std::cout << "return fin" << std::endl;
	//�r������ړ��ł��邩���ׂ�
	//���ׂ�ꂽ��MiddleMovingCheck=true;
	auto MovingItr = Reserve_listOpen0.begin();
	auto SearchItr = Reserve_listOpen0.begin();
	switch (MovingLane) {
	case eNum_ReserveOpen0:
		MovingItr = Reserve_listOpen0.begin();
		break;
	case eNum_ReserveOpen1:
		MovingItr = Reserve_listOpen1.begin();
		break;
	case eNum_ReserveOpen2:
		MovingItr = Reserve_listOpen2.begin();
		break;
	case eNum_ReserveOpen3:
		MovingItr = Reserve_listOpen3.begin();
		break;
	case eNum_ReserveOpen4:
		MovingItr = Reserve_listOpen4.begin();
		break;
	case eNum_ReserveOpen5:
		MovingItr = Reserve_listOpen5.begin();
		break;
	case eNum_ReserveOpen6:
		MovingItr = Reserve_listOpen6.begin();
		break;
	}
	//std::cout << "MovingLane :" << MovingLane << std::endl;
	//std::cout << "MovingListSize :" << CheckListSize(MovingLane) << std::endl;
	//std::cout << "*MovingItr :" << *MovingItr << std::endl;
	//std::cout << "Itrfin" << std::endl;
	while (CheckListSize(MovingLane) > CheckCount) {
		//std::cout << "loop start" << std::endl;
		//���ׂĂ�reserve�̍Ō�̃J�[�h�𒲂ׂ�
		int ListEndNum;
		int SearchList;
		//���̃^�X�N�F���ꂼ�ꂪ�󔒂���Ȃ����ǂ������ׁA�󔒂��������΂�
		for (int i = eNum_ReserveOpen0; i <= eNum_ReserveOpen6; i++) {
			//�����󔒂��������΂�
			if (EmptyOrNotTheList(i)) {
				continue;
			}
			//std::cout << "ListEndNum�w��start" << std::endl;
			switch (i) {
			case eNum_ReserveOpen0:
				ListEndNum = Reserve_listOpen0.back();
				break;
			case eNum_ReserveOpen1:
				ListEndNum = Reserve_listOpen1.back();
				break;
			case eNum_ReserveOpen2:
				ListEndNum = Reserve_listOpen2.back();
				break;
			case eNum_ReserveOpen3:
				ListEndNum = Reserve_listOpen3.back();
				break;
			case eNum_ReserveOpen4:
				ListEndNum = Reserve_listOpen4.back();
				break;
			case eNum_ReserveOpen5:
				ListEndNum = Reserve_listOpen5.back();
				break;
			case eNum_ReserveOpen6:
				ListEndNum = Reserve_listOpen6.back();
				break;
			}
			//std::cout << "ListEndNum�w��fin" << std::endl;
			//std::cout <<"MovingItr :" << *MovingItr << std::endl;
			//movinglane�̃J�[�h���P�����ړ��\���A�e���X�g�m���߂�
			if ((ListEndNum + 12 == *MovingItr || ListEndNum + 38 == *MovingItr ||
				ListEndNum - 14 == *MovingItr || ListEndNum - 40 == *MovingItr) &&
				(ListEndNum != 0 && ListEndNum != 13 && ListEndNum != 26 && ListEndNum != 39)) {
				MiddleMovingCheck = true;
				MiddleMovingList[MovingCount] = i;
				MiddleMovingLane[MovingCount] = MovingItrCount;
				MovingCount++;
				MiddleMovingCount = MovingCount;
				break;
				//return;
				//std::cout << "����fin" << std::endl;
			}
			//std::cout << "else" << std::endl;
			//std::cout << "for fin" << std::endl;
		}
		//std::cout << "while fin" << std::endl;
		MovingItr++;
		MovingItrCount++;
		CheckCount++; 
		if (MovingItrCount >= CheckListSize(MovingLane)-1) {
			return;
		}
		//std::cout << "MovingItrCount :" << MovingItrCount << std::endl;
		//std::cout << "MovingListSize :" << CheckListSize(MovingLane) << std::endl;
		//std::cout << "*MovingItr :" << *MovingItr << std::endl;
		//std::cout << "Itr++fin" << std::endl;
	}
	//�ړ��\���ǂ�������I��
	//std::cout << "all fin" << std::endl;
	//std::cout << "MiddleMovingCheck :" << MiddleMovingCheck << std::endl;
};
void BaseCard::Middle_CheckAddToReserveList() {
	//�N���b�N�����ꍇ�ɁA���̏����Ɠ��l�Ɏ��s����鏈��
	//�r�����瓮������J�[�h������ꍇ�������s�����
	std::cout << "Middle_CheckAddToReserveList start" << std::endl;
	if (!MiddleMovingCheck || EmptyOrNotTheList(MovingLane)) {
		std::cout << "Middle_CheckAddToReserveList end0" << std::endl;
		return;
	}
	//�}�E�X�̏ꏊ�Ɣ�r���āA��������ꏊ��艺�Ƀ}�E�X������Γ�������Ƃ���
	//���̃��X�g�ɂ́AMiddleMovingCount�̐���������Ƃ��낪����
	//��������Ƃ��̃t���O
	bool MiddleMoving=false;
	int MouseLane = MousePositionIsNthInTheList(MovingLane);
	int count=0;
	int MovingArea;
	auto movingItr = Reserve_listOpen0.begin();
	std::cout << "0" << std::endl;
	while (count < MiddleMovingCount-1) {
		if (MiddleMovingLane[count] <= MouseLane < MiddleMovingLane[count + 1]) {
			//����������Ă����t���O�𗧂Ă�A
			MiddleMoving = true;
			//MovingLane���瓮������
			MovingArea = MiddleMovingLane[count];
			break;
		}
		else {
			MiddleMoving = false;
		}
		count++;
	}
	std::cout << "1" << std::endl;
	if (!MiddleMoving) {
		std::cout << "Middle_CheckAddToReserveList end1" << std::endl;
		return;
	}
	std::cout << "2" << std::endl;
	//��������ꍇ�̈ړ�����
	//MovingArea���牺���ړ��\���X�g�ɓ������Ƃ�������
	//MovingLane�̃��X�g�T�C�Y��ǂݍ���ŁAMovingArea���炠�Ƃ�MiddleMovinglist�Ɉړ�
	//�����āA���̃��X�g�������
	std::cout <<"MovingArea :" << MovingArea << std::endl;
	std::cout << "MovingLane :" << MovingLane << std::endl;
	switch (MovingLane) {
	case eNum_ReserveOpen0:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		//movingItr = Reserve_listOpen0.begin();
		std::cout << "Itr fin" << std::endl;
		std::advance(movingItr, MovingArea);
		std::cout << "adv fin" << std::endl;
		while (CheckListSize(eNum_ReserveOpen0)>MovingArea) {
			AddToListend(MiddleMovingList[count], *movingItr);
			std::cout << "adde fin" << std::endl;
			int num = *movingItr;
			Reserve_listOpen0.remove(num); 
			std::cout << "remove fin" << std::endl;
			movingItr = Reserve_listOpen0.begin();
			std::advance(movingItr, MovingArea);
			std::cout << "adv fin" << std::endl;
		}
		std::cout << "case fin" << std::endl;
		break;
	case eNum_ReserveOpen1:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen1.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen1.remove(num);
		}
		break;
	case eNum_ReserveOpen2:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen2.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen2.remove(num);
		}
		break;
	case eNum_ReserveOpen3:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen3.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen3.remove(num);
		}
		break;
	case eNum_ReserveOpen4:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen4.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen4.remove(num);
		}
		break;
	case eNum_ReserveOpen5:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen5.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen5.remove(num);
		}
		break;
	case eNum_ReserveOpen6:
		//�C�e���[�^���A��������ꏊ�ɔz�u
		while (CheckListSize(eNum_ReserveOpen0) > MovingArea) {
			movingItr = Reserve_listOpen6.begin();
			std::advance(movingItr, MovingArea);
			AddToListend(MiddleMovingList[count], *movingItr);
			int num = *movingItr;
			Reserve_listOpen6.remove(num);
		}
		break;
	}
	std::cout << "Middle_CheckAddToReserveList badend" << std::endl;
}
int BaseCard::MousePositionIsNthInTheList(int ListNum) {
	//Listnum�̃��X�g�́A�ꏊ�𑪒肵�Amousupos�Ɣ�r����N���ڂ����A
	//����reserve�̃T�C�Y��20�����āA��������0���ڂ���A50���Ƃɐ����𑫂��Ă����āA
	//MousePos�Ɣ�r���Ĕ���
	//reserve���X�g�̒���
	int ReserveSpace=0;
	//reserve���X�g�𐔂���
	int ReserveCount=0; 
	//
	std::cout<<"MousePositionIsNthInTheList start"<<std::endl;
	if (eNum_ReserveOpen0 > ListNum || eNum_ReserveOpen6 < ListNum) {
		std::cout << "error end1" << std::endl;
		return 111;
	}
	ReserveSpace = CheckListSize(ListNum - 7) * 20;
	while (ReserveCount < (CheckListSize(ListNum)) - 1) {
		if (SCREEN_WIDTH * (ReserveSpace + ReserveCount * 50) / 1920 <= MousePos.y < SCREEN_WIDTH * (ReserveSpace + (ReserveCount + 1) * 50) / 1920) {
			std::cout << "end1" << std::endl;
			return ReserveCount;
		}
		ReserveCount++;
	}
	if (ReserveCount == CheckListSize(ListNum) - 1) {
		if (SCREEN_WIDTH * (ReserveSpace + ReserveCount * 50) / 1920 <= MousePos.y <= SCREEN_WIDTH * (ReserveSpace + 375 + ReserveCount * 50) / 1920) {
			std::cout << "end2" << std::endl;
			return ReserveCount;
		}
	}
	else {
		std::cout << "error end2" << std::endl;
		return 111;
	}
}
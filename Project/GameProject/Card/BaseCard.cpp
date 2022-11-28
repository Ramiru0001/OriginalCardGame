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
	MousePos = CInput::GetMousePoint();
	//��������J�[�h�̏�Ƀ}�E�X�����邩�ǂ���
	//����ꍇ,	MouseOverCard=true�ɂ���AListNum���X�V����B
	InsideOrOutsideTheCard();
	//���X�g����
	//ReserveOpen���X�g�́A��ԍŌ�̉摜�̂����Ń}�E�X�̍��N���b�N�������ăh���b�O���ė������Ƃ�
	//��ԋ߂��̃J�[�h�̏�ɍڂ����邩�𔻒肵�āA������������߂��A�\�Ȃ炻�̂܂܂ɂ���B
	//�܂��A�������Ƃ��ɂǂꂩ�̃J�[�h�͈͓̔����ǂ������������B
	//�͈͓���������A���X�g����Ԃ�
	//�����Ă�Ƃ��ɁA���̒��ɓ����Ă���A�J�[�h���}�E�X�̒����ɓ�����
	//�����ŁA�J�[�h�̍��W��ϐ��ɓ���Ă����āADraw�̕��ł�����w�肷��B
	if (PUSH(CInput::eMouseL) && MouseOverCard) {
		//ListNum���g���āA���̃J�[�h�̍��W��ύX�B
		MovingLane = ListNum;
		CardMoving = true;
		if (MouseOverReserveAndWasteLists == true) {
			CheckAddToFoundationList();
		}
	}
	//�}�E�X�𗣂����Ƃ�
	//�}�E�X�̉���reserve���X�g�ɂ����邩������
	//�u����ꍇ�͂��̃��X�g�̂P�ԍŌ�ɒǉ�
	//K�̃J�[�h�̏ꍇ�A���̃��X�g���󔒂������炻�̂܂܂�����
	if (PULL(CInput::eMouseL) && MouseOverReserve) {
		//�}�E�X�̉��̃��X�g���󔒂̏ꍇ
		if (EmptyOrNotTheList(ListNum)) {
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
	BothStockAndWaste();
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
	int Space = 20;//��D�̋�
	int OpenSpace = 40;
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
	int LineNum = Reserve_listOpen0.size() + Reserve_list0.size() - 1;
	CVector2D mouse_pos = CInput::GetMousePoint();
	//Reserve0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen0;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen1.size() + Reserve_list1.size() - 1;
	RowNum = 1;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen1;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen2.size() + Reserve_list2.size() - 1;
	RowNum = 2;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen2;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen3.size() + Reserve_list3.size() - 1;
	RowNum = 3;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen3;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve4�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen4.size() + Reserve_list4.size() - 1;
	RowNum = 4;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen4;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve5�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen5.size() + Reserve_list5.size() - 1;
	RowNum = 5;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen5;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve6�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	LineNum = Reserve_listOpen6.size() + Reserve_list6.size() - 1;
	RowNum = 6;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen6;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Foundation0�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 0 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 200 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation0;
		MouseOverCard = true;
		return;
	}
	//Foundation1�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 210 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 410 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation1;
		MouseOverCard = true;
		return;
	}
	//Foundation2�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 420 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 620 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation2;
		MouseOverCard = true;
		return;
	}
	//Foundation3�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 630 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 830 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation3;
		MouseOverCard = true;
		return;
	}
	//stock�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	/*if (SCREEN_WIDTH * 1710 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 1910 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_stock;
		MouseOverCard = true;
		return;
	}*/
	//waste�̃J�[�h�̒��Ƀ}�E�X�����邩�ǂ���
	if (SCREEN_WIDTH * 1500 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 1700 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
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
	int Space = 20;//��D�̋�
	//Reserve_listOpen0:1�ԍ�
	while (ListCount < Reserve_listOpen0.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen0 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen1:2���
	RowNum = 1;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen1.begin();
	while (ListCount < Reserve_listOpen1.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen1 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen2:3���
	RowNum = 2;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen2.begin();
	while (ListCount < Reserve_listOpen2.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen2 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen3:4���
	RowNum = 3;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen3.begin();
	while (ListCount < Reserve_listOpen3.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen3 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen4:5���
	RowNum = 4;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen4.begin();
	while (ListCount < Reserve_listOpen4.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen4 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen5:6���
	RowNum = 5;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen5.begin();
	while (ListCount < Reserve_listOpen5.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen5 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
	}
	//Reserve_listOpen6:7���
	RowNum = 6;
	LineNum = 0;
	ListCount = 0;
	Itr = Reserve_listOpen6.begin();
	while (ListCount < Reserve_listOpen6.size()) {
		CardNumToImage(*Itr);
		m_img.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		if (MovingLane == eNum_ReserveOpen6 && CardMoving) {
			m_img.SetPos(MousePos.x - (SCREEN_WIDTH * 125 / 1920), MousePos.y - (SCREEN_WIDTH * 187 / 1920));
			m_img.Draw();
		}
		LineNum++;
		ListCount++;
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
	//���L�[���������Ƃ��ɁA�X�g�b�N���X�g����wasteList�Ɉړ�
	bool MouseArea = false;
	if (SCREEN_WIDTH * 1710 / 1920 <= MousePos.x && SCREEN_WIDTH * 1910 / 1920 >= MousePos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= MousePos.y && SCREEN_HEIGHT * 300 / 1080 >= MousePos.y) {
		MouseArea = true;
	}
	if (PUSH(CInput::eLeft)|| (MouseArea && PUSH(CInput::eMouseL))) {
		if (Stock_list.size() > 0) {
			auto ItrStock = Stock_list.begin();
			Waste_list.push_back(*ItrStock);
			Stock_list.pop_front();
		}
		else {
			Stock_list.swap(Waste_list);
		}
	}
}
void BaseCard::OpenListCheckAndAdd() {
	if (Reserve_listOpen0.empty()) {
		if (!Reserve_list0.empty()) {
			auto Itr = Reserve_list0.end();
			Itr--;
			Reserve_listOpen0.push_back(*Itr);
			Reserve_list0.pop_back();
		}
	}
	if (Reserve_listOpen1.empty()) {
		if (!Reserve_list1.empty()) {
			auto Itr = Reserve_list1.end();
			Itr--;
			Reserve_listOpen1.push_back(*Itr);
			Reserve_list1.pop_back();
		}
	}
	if (Reserve_listOpen2.empty()) {
		if (!Reserve_list2.empty()) {
			auto Itr = Reserve_list2.end();
			Itr--;
			Reserve_listOpen2.push_back(*Itr);
			Reserve_list2.pop_back();
		}
	}
	if (Reserve_listOpen3.empty()) {
		if (!Reserve_list3.empty()) {
			auto Itr = Reserve_list3.end();
			Itr--;
			Reserve_listOpen3.push_back(*Itr);
			Reserve_list3.pop_back();
		}
	}
	if (Reserve_listOpen4.empty()) {
		if (!Reserve_list4.empty()) {
			auto Itr = Reserve_list4.end();
			Itr--;
			Reserve_listOpen4.push_back(*Itr);
			Reserve_list4.pop_back();
		}
	}
	if (Reserve_listOpen5.empty()) {
		if (!Reserve_list5.empty()) {
			auto Itr = Reserve_list5.end();
			Itr--;
			Reserve_listOpen5.push_back(*Itr);
			Reserve_list5.pop_back();
		}
	}
	if (Reserve_listOpen6.empty()) {
		if (!Reserve_list6.empty()) {
			auto Itr = Reserve_list6.end();
			Itr--;
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
	//���ׂ�J�[�h�̃C�e���[�^
	SearchCard_Itr--;
	//�d�˂���J�[�h�̏ꍇ
	if (*SearchCard_Itr + 12 == *MovingCard_Itr || *SearchCard_Itr + 38 == *MovingCard_Itr || 
		*SearchCard_Itr - 14 == *MovingCard_Itr || *SearchCard_Itr - 40 == *MovingCard_Itr) {
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
				DeleteListFront(MovingLane);
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
			//�����Ă�J�[�h�̃��X�g���폜
			RemoveFromListend(MovingLane);
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
			Foundation_list0.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 13) {
			Foundation_list1.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 26) {
			Foundation_list2.push_front(*MovingCard_Itr);
			CardMoving = false;
		}
		else if (*MovingCard_Itr == 39) {
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
				Foundation_list0.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (14 <= *MovingCard_Itr && *MovingCard_Itr <= 25 && !Foundation_list1.empty()) {
			SearchCard_Itr = Foundation_list1.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				Foundation_list1.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (27 <= *MovingCard_Itr && *MovingCard_Itr <= 38 && !Foundation_list2.empty()) {
			SearchCard_Itr = Foundation_list2.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
				Foundation_list2.push_back(*MovingCard_Itr);
				RemoveFromListend(MovingLane);
				CardMoving = false;
			}
		}
		else if (40 <= *MovingCard_Itr && *MovingCard_Itr <= 51 && !Foundation_list3.empty()) {
			SearchCard_Itr = Foundation_list3.end();
			SearchCard_Itr--;
			if (*SearchCard_Itr + 1 == *MovingCard_Itr) {
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
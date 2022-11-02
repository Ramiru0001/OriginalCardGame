#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
#include <Gllibrary.h>
std::random_device rnd;
std::default_random_engine eng(rnd());
//�J�[�h���������Ƃ��ɌĂ΂��B
BaseCard::BaseCard():Base(eType_Card){
	//�J�[�h��AllCard_list���烉���_���Ńs�b�N���Astock_list��reserve_list�ɐU�蕪����B
	CardListSet();
}
BaseCard::~BaseCard() {
}
void BaseCard::Update() {
}
void BaseCard::ImageSet() {
	//�摜�̃R�s�[�A�؂���A�T�C�Y�ݒ�A���O�ݒ�B
	for (int i = 0; i++; i < 13) {
		//�摜�̃R�s�[
		heart[i] = COPY_RESOURCE("TrumpCard", CImage);
		diamond[i] = COPY_RESOURCE("TrumpCard", CImage);
		club[i] = COPY_RESOURCE("TrumpCard", CImage);
		spade[i] = COPY_RESOURCE("TrumpCard", CImage);
		//�؂���
		heart[i].SetRect(23 + 293.6 * i, 23, 294 + 293.6 * i, 23 + 406);
		diamond[i].SetRect(23 + 293.6 * i, 452, 294 + 293.6 * i, 452 + 406);
		club[i].SetRect(23 + 293.6 * i, 881, 294 + 293.6 * i, 881 + 406);
		spade[i].SetRect(23 + 293.6 * i, 1310, 294 + 293.6 * i, 1310 + 406);
		//�T�C�Y�w��
		heart[i].SetSize(271, 406);
		diamond[i].SetSize(271, 406);
		club[i].SetSize(271, 406);
		spade[i].SetSize(271, 406);
	}
	BehindCard = COPY_RESOURCE("TrumpBehind", CImage);
	BehindCard.SetRect(23, 23, 294, 429);
	BehindCard.SetSize(271, 406);
}
void BaseCard::Draw() {
	/*heart[0].Draw();
	diamond[0].Draw();
	club[0].Draw();
	spade[0].Draw();*/
}
void BaseCard::CardListSet() {
	for (int i = 0; i++; i < 52) {
		AllCard_list.push_front(CardNum[i]);
		Remaining_list.push_front(CardNum[i]);
	}
	while (!(Remaining_list.empty())) {
		std::cout << Remaining_list.size() << std::endl;
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
			Reserve_list0.push_front(NextProcessCardNum);
			break;
		case 51:
			Reserve_list1.push_front(NextProcessCardNum);
			break;
		case 49:
			Reserve_list2.push_front(NextProcessCardNum);
			break;
		case 46:
			Reserve_list3.push_front(NextProcessCardNum);
			break;
		case 42:
			Reserve_list4.push_front(NextProcessCardNum);
			break;
		case 37:
			Reserve_list5.push_front(NextProcessCardNum);
			break;
		case 31:
			Reserve_list6.push_front(NextProcessCardNum);
			break;
		default:
			Stock_list.push_front(NextProcessCardNum);
			break;
		}
	}
}
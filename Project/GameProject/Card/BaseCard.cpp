#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
std::random_device rnd;
std::default_random_engine eng(rnd());
std::uniform_int_distribution<int> CardRan(0, 15);
//�J�[�h���������Ƃ��ɌĂ΂��B
BaseCard::BaseCard():m_kill(false),Base(eType_Card){
	//�J�[�h���w��
	CardNum = CardRan(eng);
}
BaseCard::~BaseCard() {
	Base::Add(new BaseCard());
}
void BaseCard::Update() {
	//���̃J�[�h���I�΂ꂽ�Ƃ��ɃJ�[�h�̌��ʂɉ����āA���̏���������	
	//���ʂ̓J�[�h�̐����Ŕ���
	//�������́A�J�[�h�̃N���X����virtual�ɂ��Ă����āA�Ă�
	//�J�[�h���g��ꂽ�ꍇ�ɃL������B
	//���̌�A�V�����J�[�h���Ă�
}
void BaseCard::ImageSet() {
	//�摜�̃R�s�[�A�؂���A�T�C�Y�ݒ�A���O�ݒ�B
}
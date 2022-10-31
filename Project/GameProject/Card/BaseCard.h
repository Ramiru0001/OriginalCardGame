#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//�J�[�h�̗D��x
enum class ECardNum
{
	eGoddess_0,//���_�J�[�h
	eGoddess_1,//���_�J�[�h
	eGoddess_2,//���_�J�[�h
	eGoddess_3,//���_�J�[�h
	eMagic_0,//�L(���@)�J�[�h
	eMagic_1,//�L(���@)�J�[�h
	eMagic_2,//�L(���@)�J�[�h
	eMagic_3,//�L(���@)�J�[�h
	eNormal_0,//�m�[�}��
	eNormal_1,//�m�[�}��
	eNormal_2,//�m�[�}��
	eNormal_3,//�m�[�}��
	eDeveil_0,//�ƍߎҁA�����J�[�h
	eDeveil_1,//�ƍߎҁA�����J�[�h
	eDeveil_2,//�ƍߎҁA�����J�[�h
	eDeveil_3,//�ƍߎҁA�����J�[�h
};
//�J�[�h���������Ƃ��ɌĂ΂��
class BaseCard :public Base{
public:
	//�J�[�h�̎w��
	int CardNum;
	//�폜�t���O
	bool m_kill;
	//�J�[�h���X�g
	static std::list<BaseCard*> Card_list;
public:
	BaseCard();
	~BaseCard();
	void ImageSet();
	void Update();
	void Draw();
	static void Add(BaseCard* b);
	void BaseCard::CheckKillAll();
};
#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//�J�[�h�̗D��x
enum class ECardNum
{
};
//�J�[�h���������Ƃ��ɌĂ΂��
class BaseCard :public Base{
public:
	//�J�[�h�̐����B
	//0~12���n�[�g
	//13~25���_�C��
	//26~38���N���u
	//39~51���X�y�[�h
	int CardNum[45];
	//���ׂẴJ�[�h�̃��X�g
	std::list<int> AllCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	//�]���Ă�J�[�h�̃��X�g
	std::list<int> Remaining_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	std::list<int> Stock_list;//�J����ĂȂ��R�D
	std::list<int> Waste_list;//�J����č��Ɉړ������R�D
	std::list<int> Reserve_list0;//��D�B1�ԍ�
	std::list<int> Reserve_list1;//��D�B������2�Ԗ�
	std::list<int> Reserve_list2;//��D�B������3�Ԗ�
	std::list<int> Reserve_list3;//��D�B������4�Ԗ�
	std::list<int> Reserve_list4;//��D�B������5�Ԗ�
	std::list<int> Reserve_list5;//��D�B������6�Ԗ�
	std::list<int> Reserve_list6;//��D�B������7�Ԗ�,1�ԉE
	std::list<int> Foundation_list0;//����̑g�D�B1�ԍ�
	std::list<int> Foundation_list1;//����̑g�D�B������2�Ԃ�
	std::list<int> Foundation_list2;//����̑g�D�B������3�Ԗ�
	std::list<int> Foundation_list3;//����̑g�D�B������4�Ԗ�
	CImage heart[14];//��
	CImage diamond[14];//��
	CImage club[14];//��
	CImage spade[14];//��
	CImage BehindCard;//�g�����v�̔w�ʂ̉摜
public:
	BaseCard();
	~BaseCard();
	//�R�s�[�A�؂���A�T�C�Y�w��ACardNum�w��
	void ImageSet();
	void Update();
	void Draw();
	void CardListSet();
};
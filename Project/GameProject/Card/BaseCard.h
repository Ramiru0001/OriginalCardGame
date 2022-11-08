#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//�J�[�h���������Ƃ��ɌĂ΂��
class BaseCard :public Base{
public:
	//���X�g�i���o�[
	enum {
		eNum_stock,
		eNum_Waste,
		eNum_Reserve0,
		eNum_Reserve1,
		eNum_Reserve2,
		eNum_Reserve3,
		eNum_Reserve4,
		eNum_Reserve5,
		eNum_Reserve6,
		eNum_ReserveOpen0,
		eNum_ReserveOpen1,
		eNum_ReserveOpen2,
		eNum_ReserveOpen3,
		eNum_ReserveOpen4,
		eNum_ReserveOpen5,
		eNum_ReserveOpen6,
		eNum_Foundation0,
		eNum_Foundation1,
		eNum_Foundation2,
		eNum_Foundation3,
	};
	//�J�[�h�̐����B
	//0~12���n�[�g
	//13~25���_�C��
	//26~38���N���u
	//39~51���X�y�[�h
	int CardNum[51];

	//���X�g�i���o�[
	//bool InsideOrOutsideTheCard();��������s������X�V�����
	int ListNum;
	//�������Ă���J�[�h�̃��[�����w��
	int MovingLane;
	//��������J�[�h�̏�Ƀ}�E�X�����邩�ǂ���
	bool MouseOverCard;
	//��D�̋�
	int Space = 20;
	//�J�[�h���������Ă��邩�ǂ���
	bool CardMoving;
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
	std::list<int> Reserve_listOpen0;//�J���ꂽ��D�B1�ԍ�
	std::list<int> Reserve_listOpen1;//�J���ꂽ��D�B������2�Ԗ�
	std::list<int> Reserve_listOpen2;//�J���ꂽ��D�B������3�Ԗ�
	std::list<int> Reserve_listOpen3;//�J���ꂽ��D�B������4�Ԗ�
	std::list<int> Reserve_listOpen4;//�J���ꂽ��D�B������5�Ԗ�
	std::list<int> Reserve_listOpen5;//�J���ꂽ��D�B������6�Ԗ�
	std::list<int> Reserve_listOpen6;//�J���ꂽ��D�B������7�Ԗ�,1�ԉE
	std::list<int> Foundation_list0;//����̑g�D�B1�ԍ�
	std::list<int> Foundation_list1;//����̑g�D�B������2�Ԃ�
	std::list<int> Foundation_list2;//����̑g�D�B������3�Ԗ�
	std::list<int> Foundation_list3;//����̑g�D�B������4�Ԗ�
	CImage heart[14];//�n�[�g�̐�
	CImage diamond[14];//�_�C���̐�
	CImage club[14];//�N���[�o�[�̍�
	CImage spade[14];//�X�y�[�h�̍�
	CImage BehindCard;//�g�����v�̔w�ʂ̉摜
	CImage m_img;//�I�𒆂̉摜�BTemp
	CVector2D MousePos;
public:
	BaseCard();
	~BaseCard();
	//�R�s�[�A�؂���A�T�C�Y�w��ACardNum�w��B�����ݒ�
	void ImageSet();
	void Update();
	void Draw();
	//�J�[�h�����X�g�ɃZ�b�g����B�U�蕪����B�����ݒ�
	void CardListSet();
	//�Ă΂ꂽ��A���̈����̃J�[�h��m_img�Ɏw��
	void CardNumToImage(int ThatCardNumber);
	//���X�g��ǂݍ��݁A�摜���w��A�z�u�B
	void LoadTheListAndDraw();
	//�����Ă���J�[�h�̕\��
	void MovingCardDraw();
	//�}�E�X����������J�[�h�̏�ɂ��邩�Ȃ����B
	//����ꍇ,	MouseOverCard=true�ɂ���AListNum���X�V����B
	void InsideOrOutsideTheCard();
	//StockList��WaseteList�̑o�����ړ�
	void BothStockAndWaste();
	// �J�[�h������͈͓��ŁA��ԋ߂��J�[�h�ɒu���邩�ǂ���������
	//�u����ꍇ�͂��̃��X�g�̂P�ԍŌ�ɒǉ�
	//void
};
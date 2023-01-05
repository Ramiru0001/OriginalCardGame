#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//�J�[�h���������Ƃ��ɌĂ΂��
class BaseCard :public Base{
public:
	enum CardDesign{
		eNum_Heart,
		eNum_Diamond,
		eNum_Club,
		eNum_Spade,
	};
	//���݂̃Q�[���ݒ�
	enum GameMode{
		eState_Normal,
		eState_Random,
		eState_Debug,
		eState_Auto,
	};
	//���X�g�i���o�[
	//�J�[�h�̐����B
	//0~12���n�[�g
	//13~25���N���u
	//26~38���_�C��
	//39~51���X�y�[�h
	enum List{
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
	//���݂̏�ʁB���[�U�[�����삷���ʂ̈ڍs�Ɏg����
	enum GameScene{
	eScene_Play,//�v���C��
	eScene_AutoStay,//AUTO�{�^���\����
	eScene_Auto,//����
	eScene_Clear,//�N���A���
	};
	int CardNum[51];
	//���݂̃Q�[����ʁB�v���C���AAUTO�{�^�����\������Ă���A��
	//���[�U�[�����삷���ʂ̈ڍs�Ɏg����
	int GameScene = eScene_Play;
	//���X�g�i���o�[
	//bool InsideOrOutsideTheCard();��������s������X�V�����
	int ListNum;
	//���X�g��N�Ԗ�
	int LaneNum;
	//�������Ă���J�[�h�̃��[�����w��
	int MovingLane;
	//�r�����瓮�����郌�[�����w��
	int MiddleMovingLaneNum;
	//�r�����瓮�������̃��X�g���w��
	int MiddleMovingListNum;
	//��������J�[�h�̏�Ƀ}�E�X�����邩�ǂ���
	bool MouseOverCard;
	//reserve���X�g�̏�Ƀ}�E�X�����邩�ǂ���
	bool MouseOverReserve;
	//resreve���X�g��Waste���X�g�̏�Ƀ}�E�X�����邩�ǂ���
	bool MouseOverReserveAndWasteLists;
	//stock���X�g�̏�Ƀ}�E�X�����邩�ǂ���
	bool MouseOverStockList;
	//�r�����瓮������ꍇ:true
	bool MiddleMovingCheck;
	//�r�����瓮������ꍇ�A���������̃��X�g�������
	int MiddleMovingList[10];
	//�r�����瓮������ꍇ�A�����ɂ��̃��X�g��N�ԖځA������
	int MiddleMovingLane[10];
	//�r�����瓮�����鐔�𐔂��āA���
	int MiddleMovingCount = 0;
	///��D�̋� 20
	int Space = 20;
	//��Dopen�̋� 50
	int OpenSpace = 50;
	//�I�𒆂̃��[�h�F0_normal;1_auto
	int SelectMode = 0;
	//�J�[�h���������Ă��邩�ǂ���
	bool CardMoving;
	//���A�r������J�[�h�������Ă��邩�ۂ�
	bool MiddleCardMoving;
	//debug���[�h��state
	int DebugMode_State;
	//�}�E�X�ƃJ�[�h�̏�[�̋���
	int MouseDistance;
	//�N���A��ʕ\���܂ł̃J�E���g�_�E��
	int ClearCountDown;
	//���ׂẴJ�[�h�̃��X�g
	std::list<int> AllCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51 };
	std::list<int> HeartCard_list = { 0,1,2,3,4,5,6,7,8,9,10,11,12 };//�n�[�g�J�[�h���X�g
	std::list<int> ClubCard_list = { 13,14,15,16,17,18,19,20,21,22,23,24,25 };//�N���u�J�[�h���X�g
	std::list<int> DiamondCard_list = { 26,27,28,29,30,31,32,33,34,35,36,37,38 };//�_�C���J�[�h���X�g
	std::list<int> SpadeCard_list = { 39,40,41,42,43,44,45,46,47,48,49,50,51 };//�X�y�[�h�J�[�h���X�g
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
	std::list<int> Moved_Log;//���O
	std::list<int> Empty_list;//�J�[�h�z�u���A�󔒂̃��X�g������
	std::list<int> Empty_list4Types;//�J�[�h�z�u���A�󔒂̃��X�g������B�S��ނ̖͗l�J�[�h�B
	std::list<int> Temp_list;//temp�B�ړ�������Ƃ��Ɏg���A���̃��X�g
	CImage heart[14];//�n�[�g�̐�
	CImage diamond[14];//�_�C���̐�
	CImage club[14];//�N���[�o�[�̍�
	CImage spade[14];//�X�y�[�h�̍�
	CImage BehindCard;//�g�����v�̔w�ʂ̉摜
	CImage m_img;//�I�𒆂̉摜�BTemp
	CVector2D MousePos;
	CImage AutoButton;
	CImage ScreenDesign;
	CImage BackGround;
	CImage Clear_Excellent;
	CImage Clear_Star;
	CImage Clear_Score;
	CImage Clear_Cloud;
	CFont PushEnter_Text;
public:
	BaseCard(int GameMode);
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
	//�r�����瓮���Ă���J�[�h�̕\��
	void MiddleCardMovingDraw();
	//�}�E�X����������J�[�h�̏�ɂ��邩�Ȃ����B
	//����ꍇ,	MouseOverCard=true�ɂ���AListNum���X�V����B
	void InsideOrOutsideTheCard();
	//StockList��WaseteList�̑o�����ړ�
	void BothStockAndWaste();
	// �J�[�h������͈͓��ŁA��ԋ߂��J�[�h�ɒu���邩�ǂ���������
	//�u����ꍇ�͂��̃��X�g�̂P�ԍŌ�ɒǉ�
	// 
	//open���X�g�ɃJ�[�h���L�邩�ǂ����m���߂�B�����Ȃ�������ǉ�
	void OpenListCheckAndAdd();
	//���N���b�N�𗣂����Ƃ��A�����Ă�J�[�h���ǂ�����reserve���X�g�ɒu���邩�`�F�b�N�B�u�����烊�X�g�ړ�
	void CheckAddToReserveList();
	//���N���b�N�𗣂����Ƃ��A�����Ă�J�[�h���ǂ�����Foundation���X�g�ɒu���邩�`�F�b�N�B�u�����烊�X�g�ړ�
	void CheckAddToFoundationList();
	//ListNum�̃��X�g�̍Ō���폜
	void RemoveFromListend(int ListNum);
	//ListNum�̃��X�g�̍Ō�ɒǉ�
	void AddToListend(int ListNum,int AddNum);
	//������ListNum�̃��X�g��empty���ۂ�
	bool EmptyOrNotTheList(int ListNum);
	//���X�g�̍ŏ����폜
	void DeleteListFront(int ListNum);
	//���X�g�̗v�f����߂�l�Ƃ���
	int CheckListSize(int ListNum);
	//����K�̃J�[�h�Ȃ�A�ړ��\
	void MoveIfK();
	//�ʏ탂�[�h�B�����������珇�ɔz�u���Ă������[�h�B�N���A�ł���\��������
	void NormalMode();
	//�����_�����[�h�B���S�����_���z�u�B�N���A�\���s��
	void RandomMode();
	//Auto���[�h
	void AutoMode();
	//���O��ǉ�����
	void AddToMoved_Log(int BeforeList,int Beforeard,int afterList,int afterCard);
	//���ׂĂ�reserve���X�g���󔒂Ȃ�true;
	bool CheckReserveEmpty();
	//���[�v���Ă���true��Ԃ�
	bool LoopOrNot();
	//���ׂẴ��X�g�����������ăJ�[�h���Ĕz�u
	void ReStartGame(bool);
	//�N���A���ǂ����̔���
	bool ClearOrNot();
	//���[�U�[����ɑ΂��鏈���B
	void UserOperation();
	//�J�[�h�z�u���A�󂫂̂��郊�X�g�𒲂ׂ�
	void AddEmptyList();
	//�S��ނ̃J�[�h���X�g�ŋ󂫂̂��郊�X�g�𒲂ׂ�
	void AddEmpty4CardList();
	//�f�o�b�O�p�B�J�[�h���X�g�̏o��
	void AllCardNumOutPut_debug();
	//�f�o�b�O�p�B�I�[�g�Ǝ蓮�ؑ։\�B
	void DebugMode();
	//�r������reserve���X�g�ֈړ��ł��邩�ǂ����̔���i����ƃ��X�g�̐���������̂݁j
	void Middle_Judgement_CheckAddToReserveList(int MovingLane);
	//�r�����瓮�����邩�ǂ����̔���B
	//�\�ȏꍇMiddleMovingCheck = true;
	//���ݍ쐬���E�E�E
	void Middle_CheckAddToReserveList();
	//�}�E�X�̈ʒu�̓��X�g��N�Ԗ�
	int MousePositionIsNthInTheList(int ListNum);
	//�r�����瓮�����邩�ǂ����̔���ƁA�ǂ����瓮�����邩�B��������ꍇtrue
	bool CheckIfItCanBeMovedFromTheMiddle();
};
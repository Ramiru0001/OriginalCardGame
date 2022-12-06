#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
#include <Gllibrary.h>
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
std::random_device rnd;
std::default_random_engine eng(rnd());
//カードを引いたときに呼ばれる。
BaseCard::BaseCard(int GameMode):Base(eType_Card){
	SelectMode = GameMode;
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
	case eState_Auto:
		AutoMode();
		break;
	}
}
void BaseCard::ImageSet() {
	//画像のコピー、切り取り、サイズ設定、名前設定。
	for (int i = 0; i<13; i++) {
		//画像のコピー
		heart[i] = COPY_RESOURCE("TrumpCard", CImage);
		diamond[i] = COPY_RESOURCE("TrumpCard", CImage);
		club[i] = COPY_RESOURCE("TrumpCard", CImage);
		spade[i] = COPY_RESOURCE("TrumpCard", CImage);
		//切り取り
		spade[i].SetRect(23 + 293.6 * i, 23, 294 + 293.6 * i, 23 + 406);
		heart[i].SetRect(23 + 293.6 * i, 452, 294 + 293.6 * i, 452 + 406);
		diamond[i].SetRect(23 + 293.6 * i, 881, 294 + 293.6 * i, 881 + 406);
		club[i].SetRect(23 + 293.6 * i, 1310, 294 + 293.6 * i, 1310 + 406);
		//サイズ指定
		heart[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		diamond[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		club[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
		spade[i].SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
	}//カードの後ろの画像のセット
	BehindCard = COPY_RESOURCE("TrumpBehind", CImage);
	BehindCard.SetRect(23, 23, 294, 429);
	BehindCard.SetSize(SCREEN_WIDTH * 250 / 1920, SCREEN_HEIGHT * 375 / 1080);
}
void BaseCard::Draw() {
	//リストを読み込んで、そのリストの数字の画像を表示させる
	//MouseOverCardがtrueならマウスのところにカードを指定
	LoadTheListAndDraw();
	MovingCardDraw();
}
void BaseCard::CardListSet() {
	switch (SelectMode) {
		case eState_Random:
		case eState_Auto:
			//std::cout << Remaining_list.size() << std::endl;
			while (!Remaining_list.empty()) {
				//std::cout << Remaining_list.size() << std::endl;
				//残っているカードの数
				int RemainingCard_num = Remaining_list.size();
				//残っているカードの数の中で、乱数を生成する関数を作成。
				std::uniform_int_distribution<int> CardRan(0, RemainingCard_num - 1);
				//Itrは、リストのN番目を指す。最初の要素を入れる
				auto Itr = Remaining_list.begin();
				//CardRan(eng)番目の要素を取得。Itrのポインタがその数字
				std::advance(Itr, CardRan(eng));
				//次に処理するカードの数字
				int NextProcessCardNum = *Itr;
				//Remaining_listから、使用した値を削除
				Remaining_list.remove(NextProcessCardNum);
				//カードの数字を各リストに入れる
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
			while (!Remaining_list.empty()) {
				//std::cout << Remaining_list.size() << std::endl;
				//残ってるカードリストの中で乱数
				std::uniform_int_distribution<int> CardRan(0, Empty_list.size() - 1);
				//Itrは、リストのN番目を指す。最初の要素を入れる
				auto RemainingItr = Remaining_list.begin();
				auto EmptyItr = Empty_list.begin();
				//入れるリストの数字を入手
				std::advance(EmptyItr, CardRan(eng));
				//次に追加するリストの数字を入手
				int AddListNum = *RemainingItr;
				//Remaining_listの最初の数字を削除
				Remaining_list.pop_front();
				//カードの数字を各リストに入れる
				switch (AddListNum) {
				case eNum_Reserve0:
					Reserve_list0.push_front(*EmptyItr);
					break;
				case eNum_Reserve1:
					Reserve_list1.push_front(*EmptyItr);
					break;
				case eNum_Reserve2:
					Reserve_list2.push_front(*EmptyItr);
					break;
				case eNum_Reserve3:
					Reserve_list3.push_front(*EmptyItr);
					break;
				case eNum_Reserve4:
					Reserve_list4.push_front(*EmptyItr);
					break;
				case eNum_Reserve5:
					Reserve_list5.push_front(*EmptyItr);
					break;
				case eNum_Reserve6:
					Reserve_list6.push_front(*EmptyItr);
					break;
				case eNum_Waste:
					Waste_list.push_front(*EmptyItr);

				}
			}
			break;
	}
	//std::cout << Remaining_list.size() << std::endl;
	/*std::cout << "Stock :";
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
	std::cout<<std::endl;*/
	//std::cout << std::endl << " Foundation_list :" ;
	/*for (auto const& i : Foundation_list) {
		std::cout << "," << i;
	}*/
}
void BaseCard::CardNumToImage(int ThatCardNumber) {
	//呼ばれたら、その引数のカードをm_imgに指定
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
	int LineNum = 0;//行ナンバー
	int RowNum = 0;//列ナンバー
	int ListCount = 0;//リストのN番目
	//Reserve_listOpen0:1番左
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
	//Reserve_listOpen1:2列目
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
	//Reserve_listOpen2:3列目
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
	//Reserve_listOpen3:4列目
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
	//Reserve_listOpen4:5列目
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
	//Reserve_listOpen5:6列目
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
	//Reserve_listOpen6:7列目
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
	//Stock_list:1枚でもあったら背景画像を表示
	if (0 < Stock_list.size()) {
		m_img = BehindCard;
		m_img.SetSize(SCREEN_WIDTH * 200 / 1920, SCREEN_HEIGHT * 300 / 1080);
		m_img.SetPos(SCREEN_WIDTH * 1710 / 1920, SCREEN_HEIGHT * 0 / 1080);
		m_img.Draw();
	}
	//Waste_list:1枚でもあったら最後の画像を表示
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
	//列ナンバー
	int RowNum = 0;
	//行ナンバー
	int LineNum = Reserve_listOpen0.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	CVector2D mouse_pos = CInput::GetMousePoint();
	//Reserve0のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list0.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list0.size() * Space)+(LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen0;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve1のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen1.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 1;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list1.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list1.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen1;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve2のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen2.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 2;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list2.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list2.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen2;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve3のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen3.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 3;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list3.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list3.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen3;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve4のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen4.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 4;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list4.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list4.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen4;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve5のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen5.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 5;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list5.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list5.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen5;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve6のカードの中にマウスがあるかどうか
	LineNum = Reserve_listOpen6.size() - 1;
	if (LineNum < 0) {
		LineNum = 0;
	}
	RowNum = 6;
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (Reserve_list6.size() * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (Reserve_list6.size() * Space) + (LineNum * OpenSpace)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen6;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Foundation0のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * 0 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 200 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation0;
		MouseOverCard = true;
		return;
	}
	//Foundation1のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * 210 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 410 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation1;
		MouseOverCard = true;
		return;
	}
	//Foundation2のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * 420 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 620 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation2;
		MouseOverCard = true;
		return;
	}
	//Foundation3のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * 630 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 830 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_Foundation3;
		MouseOverCard = true;
		return;
	}
	//stockのカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * 1710 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 1910 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_stock;
		MouseOverStockList = true;
	}
	else {
		MouseOverStockList = false;
	}
	//wasteのカードの中にマウスがあるかどうか
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
	int LineNum = 0;//行ナンバー
	int RowNum = 0;//列ナンバー
	int ListCount = 0;//リストのN番目
	int CardLen;//その列の長さ
	int ListSize;//その列の空白の数
	//Reserve_listOpen0:1番左
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
	//Reserve_listOpen1:2列目
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
	//Reserve_listOpen2:3列目
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
	//Reserve_listOpen3:4列目
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
	//Reserve_listOpen4:5列目
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
	//Reserve_listOpen5:6列目
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
	//Reserve_listOpen6:7列目
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
	//emptyの場合、おしまい
	//emptyじゃない場合↓
	/*if (EmptyOrNotTheList(MovingLane)|| EmptyOrNotTheList(ListNum)) {
		return;
	}*/
	auto MovingCard_Itr = Reserve_listOpen0.end();
	auto SearchCard_Itr = Reserve_listOpen0.end();
	//ListNumの番号のリストに追加
	//動いてるカードリストの、判定するカードを指定
	//emptyだった場合の処理とemptyではない場合の処理が必要
	//std::cout << "Itr指定fin";
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
	//std::cout << "MoveItr指定fin";
	//最寄りのカードのリストの最後をイテレータ指定
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
	//std::cout << "SearchItr指定fin";
	//調べるカードのイテレータ
	SearchCard_Itr--;
	//std::cout << "SearchItr--"<<std::endl;
	//std::cout << "SearchPointer=ListNum" << *SearchCard_Itr << " ";
	//std::cout << "MovePointer=MovingLane" << *MovingCard_Itr << std::endl;
	//重ねられるカードの場合
	if (( * SearchCard_Itr + 12 == *MovingCard_Itr || *SearchCard_Itr + 38 == *MovingCard_Itr ||
		*SearchCard_Itr - 14 == *MovingCard_Itr || *SearchCard_Itr - 40 == *MovingCard_Itr) && (*SearchCard_Itr != 0 && *SearchCard_Itr != 13 && *SearchCard_Itr != 26 && *SearchCard_Itr != 39)) {
		AddToMoved_Log(MovingLane,*MovingCard_Itr,ListNum,*SearchCard_Itr);
		//std::cout << "IfItr参照fin";
		//動かすカードがreserve_openのカードの場合、
		switch (MovingLane) {
		case eNum_ReserveOpen0:
		case eNum_ReserveOpen1:
		case eNum_ReserveOpen2:
		case eNum_ReserveOpen3:
		case eNum_ReserveOpen4:
		case eNum_ReserveOpen5:
		case eNum_ReserveOpen6:
			// すべてのカードを移動させて、もとのリストを前消しする。
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
			//foundationリストから動かす場合。
			//移動先のリストに追加
			AddToListend(ListNum, *MovingCard_Itr);
			//std::cout << "DeleteendNow";
			//動いてるカードのリストを削除
			RemoveFromListend(MovingLane);
			//std::cout << "DeleteendFin";
			//１枚の場合の処理しか書いてないため、複数枚動かすとまともに動かない
			break;
		}
	}
}
void BaseCard::CheckAddToFoundationList() {
	auto MovingCard_Itr = Reserve_listOpen0.begin();
	auto SearchCard_Itr = Reserve_listOpen0.begin();
	//foundationListに置けるなら置く
	// そのカードのレーンがemptyの場合=カードが１の場合
	//MovingLaneにカードがない場合、終了
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
	// emptyじゃなくて、かつ、２~１３の場合
	//動いたカードのイテレータ指定ここまで
	//カードが1の場合
	if (*MovingCard_Itr == 0 || *MovingCard_Itr == 13 || *MovingCard_Itr == 26 || *MovingCard_Itr == 39) {
		//リストにデータ入力
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
	//そのカードの模様のfoundationlistがemptyじゃない場合；
	//カードが2~13の場合
	else {
		if (1 <= *MovingCard_Itr && *MovingCard_Itr <= 12 && !Foundation_list0.empty()) {
			SearchCard_Itr = Foundation_list0.end();
			SearchCard_Itr--;
			//Movinglaneの最後のカードのポインタがいずれかのfoundationListのポインタ＋１だったら移動
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
	//リストから削除
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
	//もし、動かしてるカードのリストがReserveOpenかwasteで、その一番最初がKなら
	//移動可能
	if (eNum_ReserveOpen0 <= MovingLane && MovingLane <= eNum_ReserveOpen6){}
	else if (MovingLane == eNum_Waste){}
	else {
		return;
	}
	auto Itr= Reserve_listOpen0.begin();
	//まず、reserveopenの場合、
	//Kかどうかを確かめる
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
	//Kの場合
	if (*Itr == 12 || *Itr == 25 || *Itr == 38 || *Itr == 51) {
		AddToMoved_Log(MovingLane, *Itr, ListNum, 0);
		//movingLaneからListNumへ、要素の中身をすべて移動
		switch (MovingLane) {
		case eNum_ReserveOpen0:
		case eNum_ReserveOpen1:
		case eNum_ReserveOpen2:
		case eNum_ReserveOpen3:
		case eNum_ReserveOpen4:
		case eNum_ReserveOpen5:
		case eNum_ReserveOpen6:
			// すべてのカードを移動させて、もとのリストを前消しする。
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
			//foundationリストから動かす場合。
			//移動先のリストに追加
			AddToListend(ListNum, *Itr);
			//動いてるカードのリストを削除
			RemoveFromListend(MovingLane);
			//１枚の場合の処理しか書いてないため、複数枚動かすとまともに動かない
			break;
		}
	}
}
void BaseCard::NormalMode() {
	//すべてのreserveリストのカードが無くなったら、
	if (CheckReserveEmpty()) {
		SelectMode = eState_Auto;
	}
	//動かせるカードの上にマウスがあるかどうか
	//ある場合,	MouseOverCard=trueにする、ListNumを更新する。
	InsideOrOutsideTheCard();
	//ユーザー操作に対する処理
	UserOperation();
}
void BaseCard::RandomMode() {
	//すべてのreserveリストのカードが無くなったら、
	if (CheckReserveEmpty()) {
		SelectMode = eState_Auto;
	}
	//動かせるカードの上にマウスがあるかどうか
	//ある場合,	MouseOverCard=trueにする、ListNumを更新する。
	InsideOrOutsideTheCard();
	//ユーザー操作に対する処理
	UserOperation();
	
}
void BaseCard::AutoMode() {
	InsideOrOutsideTheCard();
	//ListNumとmovingレーンを１つずつたしかめる
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
			//先のリストが空白の場合
			if (EmptyOrNotTheList(ListNum)) {
				//動かしてるリストの一番最初のカードがKの場合、
				//置ける
				//std::cout << "NoCheckfin";
				MoveIfK();
				//std::cout << "NoCheck"<<std::endl;
			}
			//先のリストが空白じゃない場合
			else if (!EmptyOrNotTheList(ListNum)) {
				//std::cout << "Check";

				CheckAddToReserveList();
				//std::cout << "Checkfin"<<std::endl;
			}
			//std::cout << "Open";
			OpenListCheckAndAdd();
			//std::cout << "Openfin" << std::endl;
			/*std::cout << std::endl << "Stock :";
			for (auto const& i : Stock_list) {
				std::cout << "," << i;
			}
			std::cout << std::endl << "Waste :";
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
			std::cout << std::endl << " Foundation_list3 :" << std::endl;
			for (auto const& i : Foundation_list3) {
				std::cout << "," << i;
			}*/
			if (EmptyOrNotTheList(MovingLane)) {
				break;
			}
		}
	}
	//ゲームクリアの場合もloop判定になっている。
	//それを除いてリスタートの処理に変更
	if (ClearOrNot() == false) {
		ReStartGame(LoopOrNot());
	}
	//もし、同じ作業を5回以上繰り返している場合、動いてない場合、最初からやり直す
	//動かしたカード：動かした先の列名を見ての処理？
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
	//動かすカード、リスト、(あれば、動かす先のカード)、リスト
	//リスト：動かすカード：リスト：動かす先のカード
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
	//１度同じ動きがある場合
	bool finish = false;
	//現状ループが続いてる場合。
	bool CorrectNow = false;
	//チェック中のカウント
	int CheckCount = 0;
	//同じのが見つかったら何度続くか確かめる
	int LoopCount = 0;
	//ループのチェックするポイントの数字を指定
	int PointNum;
	do{
		//まず、同じのを探す
		while (ChoiceItrCount < Max && ChoiceItrCount < 200) {
			//ソートの方の条件
			for (int SortItrCount = 0; SortItrCount < Max; SortItrCount++) {
				if (*ChoiceItr == *Sortitr) {
					//同じだったら、itrとカウントを増やしてループ抜ける
					ChoiceItr++;
					ChoiceItrCount++;
					finish = true;
					break;
				}
				else {
					//この場合、trueになるか、終わるまで実行し続ける
					Sortitr++;
					SortItrCount++;
				}
			}
			//同じ動きが見つかっているなら、ループ抜ける
			if (finish==true) {
				break;
			}
			ChoiceItr++;
			ChoiceItrCount++;
			//選ぶ方のイテレータが200超えたら終わる
			if (ChoiceItrCount >= 200) {
				return false;
			}
		}
		//finishがfalseの場合、全くループしていないのでreturn;
		if (finish==false) {
			return false;
		}
		//この数字がもう1度来たら＝同じ動きをしたらループとする。
		PointNum = *ChoiceItr;
		do {
			if (*ChoiceItr = *Sortitr) {
				//同じ数字を繰り返してる数を数える。
				CheckCount++;
				//同じ数字の数で、ループの数を数える
				if (PointNum == *Sortitr) {
					LoopCount++;
				}
				else {
					//ループの指定先を間違えている場合は、回数とポイントの初期化
					PointNum == *ChoiceItr;
					LoopCount = 0;
				}
				//イテレータを進める
				ChoiceItr++;
				Sortitr++;
				//イテレータのカウントを増やす
				ChoiceItrCount++;
				SortItrCount++;
				//ループが続いてるからtrue
				CorrectNow = true;
			}
			else {
				//ループ終わりだからfalse
				CorrectNow = false;
			}
		} while (ChoiceItrCount < Max && SortItrCount < Max && CorrectNow == true);
		//CorrectNow = false;の場合、最初に戻る
	} while (CorrectNow==false);
	//最後までループが続いてる場合；
	if (CorrectNow = true) {
		//続いてる区間の指定
		if (LoopCount >= 5 && CheckCount>=200) {
			return true;
		}
	}
	return false;
	//この関数のあと、リスタートのコードを書く
}
void BaseCard::ReStartGame(bool NewGame) {
	//std::cout <<"TrueOrFalse: " << NewGame << std::endl;
	if (NewGame==false) {
		//std::cout << "return" << std::endl;
		return;
	}
	//std::cout << "Restart" << std::endl;
	//リストをオールクリア
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
	//カードを初期位置へ配置
	Remaining_list = AllCard_list;
	CardListSet();
}
bool BaseCard::ClearOrNot(){
	//もし、すべてのfoundationリストに13枚のカードがあったらtrue;
	if (Foundation_list0.size() == 13 && Foundation_list1.size() == 13 &&
		Foundation_list2.size() == 13 && Foundation_list3.size() == 13) {
		return true;
	}
	return false;
}
void BaseCard::UserOperation() {
	//リスト操作
	//左クリックしたとき、動かせるカードの上にマウスがあった場合。
	if (PUSH(CInput::eMouseL) && MouseOverCard) {
		//ListNumを使って、そのカードの座標を変更。
		MovingLane = ListNum;
		CardMoving = true;
		//マウスが、wasteリストかreserveリストのうえにある場合
		if (MouseOverReserveAndWasteLists == true) {
			CheckAddToFoundationList();
		}
	}
	//マウスを離したとき、マウスがreserveリストの上にある場合
	if (PULL(CInput::eMouseL) && MouseOverReserve) {
		//マウスの下のリストが空白でかつ、動かしてるカードのリストが空白じゃない場合
		if (!EmptyOrNotTheList(MovingLane) && EmptyOrNotTheList(ListNum)) {
			//動かしてるリストの一番最初のカードがKの場合、
			//置ける
			MoveIfK();
		}
		//マウスの下のリストと動かしてるリストの両方が空白じゃない場合
		else if (!EmptyOrNotTheList(MovingLane) || !EmptyOrNotTheList(ListNum)) {
			CheckAddToReserveList();
		}
	}
	//もし、openのリストに何もなければ、１枚移動する。
	OpenListCheckAndAdd();
	if (FREE(CInput::eMouseL)) {
		CardMoving = false;
	}
	//マウスが、stockリストのなかにあれば
	//左キーを押したときに、ストックリストからwasteListに移動
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
}
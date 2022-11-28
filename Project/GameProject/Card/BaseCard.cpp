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
BaseCard::BaseCard():Base(eType_Card){
	ImageSet();
	CardListSet();
}
BaseCard::~BaseCard() {
}
void BaseCard::Update() {
	MousePos = CInput::GetMousePoint();
	//動かせるカードの上にマウスがあるかどうか
	//ある場合,	MouseOverCard=trueにする、ListNumを更新する。
	InsideOrOutsideTheCard();
	//リスト操作
	//ReserveOpenリストの、一番最後の画像のうえでマウスの左クリックを押してドラッグして離したとき
	//一番近くのカードの上に載せられるかを判定して、無理だったら戻し、可能ならそのままにする。
	//まず、押したときにどれかのカードの範囲内かどうかをさがす。
	//範囲内だったら、リスト名を返す
	//押してるときに、その中に入ってたら、カードをマウスの中央に動かす
	//ここで、カードの座標を変数に入れておいて、Drawの方でそれを指定する。
	if (PUSH(CInput::eMouseL) && MouseOverCard) {
		//ListNumを使って、そのカードの座標を変更。
		MovingLane = ListNum;
		CardMoving = true;
		if (MouseOverReserveAndWasteLists == true) {
			CheckAddToFoundationList();
		}
	}
	//マウスを離したとき
	//マウスの下のreserveリストにおけるか試して
	//置ける場合はそのリストの１番最後に追加
	//Kのカードの場合、そのリストが空白だったらそのままおける
	if (PULL(CInput::eMouseL) && MouseOverReserve) {
		//マウスの下のリストが空白の場合
		if (EmptyOrNotTheList(ListNum)) {
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
	BothStockAndWaste();
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
	int Space = 20;//場札の空白
	int OpenSpace = 40;
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
	int LineNum = Reserve_listOpen0.size() + Reserve_list0.size() - 1;
	CVector2D mouse_pos = CInput::GetMousePoint();
	//Reserve0のカードの中にマウスがあるかどうか
	if (SCREEN_WIDTH * (25 + (250 + 20) * RowNum) / 1920 <= mouse_pos.x && SCREEN_WIDTH * (25 + 250 + (250 + 20) * RowNum) / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * (350 + (LineNum * Space)) / 1080 <= mouse_pos.y && SCREEN_HEIGHT * (375 + 350 + (LineNum * Space)) / 1080 >= mouse_pos.y) {
		ListNum = eNum_ReserveOpen0;
		MouseOverCard = true;
		MouseOverReserve = true;
		MouseOverReserveAndWasteLists = true;
		return;
	}
	//Reserve1のカードの中にマウスがあるかどうか
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
	//Reserve2のカードの中にマウスがあるかどうか
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
	//Reserve3のカードの中にマウスがあるかどうか
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
	//Reserve4のカードの中にマウスがあるかどうか
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
	//Reserve5のカードの中にマウスがあるかどうか
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
	//Reserve6のカードの中にマウスがあるかどうか
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
	/*if (SCREEN_WIDTH * 1710 / 1920 <= mouse_pos.x && SCREEN_WIDTH * 1910 / 1920 >= mouse_pos.x &&
		SCREEN_HEIGHT * 0 / 1080 <= mouse_pos.y && SCREEN_HEIGHT * 300 / 1080 >= mouse_pos.y) {
		ListNum = eNum_stock;
		MouseOverCard = true;
		return;
	}*/
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
	int Space = 20;//場札の空白
	//Reserve_listOpen0:1番左
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
	//Reserve_listOpen1:2列目
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
	//Reserve_listOpen2:3列目
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
	//Reserve_listOpen3:4列目
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
	//Reserve_listOpen4:5列目
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
	//Reserve_listOpen5:6列目
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
	//Reserve_listOpen6:7列目
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
	//左キーを押したときに、ストックリストからwasteListに移動
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
	//調べるカードのイテレータ
	SearchCard_Itr--;
	//重ねられるカードの場合
	if (*SearchCard_Itr + 12 == *MovingCard_Itr || *SearchCard_Itr + 38 == *MovingCard_Itr || 
		*SearchCard_Itr - 14 == *MovingCard_Itr || *SearchCard_Itr - 40 == *MovingCard_Itr) {
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
			//foundationリストから動かす場合。
			//移動先のリストに追加
			AddToListend(ListNum, *MovingCard_Itr);
			//動いてるカードのリストを削除
			RemoveFromListend(MovingLane);
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
	//そのカードの模様のfoundationlistがemptyじゃない場合；
	//カードが2~13の場合
	else {
		if (1 <= *MovingCard_Itr && *MovingCard_Itr <= 12 && !Foundation_list0.empty()) {
			SearchCard_Itr = Foundation_list0.end();
			SearchCard_Itr--;
			//Movinglaneの最後のカードのポインタがいずれかのfoundationListのポインタ＋１だったら移動
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
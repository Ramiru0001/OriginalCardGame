#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
#include <Gllibrary.h>
std::random_device rnd;
std::default_random_engine eng(rnd());
//カードを引いたときに呼ばれる。
BaseCard::BaseCard():Base(eType_Card){
	//カードをAllCard_listからランダムでピックし、stock_listとreserve_listに振り分ける。
	CardListSet();
}
BaseCard::~BaseCard() {
}
void BaseCard::Update() {
}
void BaseCard::ImageSet() {
	//画像のコピー、切り取り、サイズ設定、名前設定。
	for (int i = 0; i++; i < 13) {
		//画像のコピー
		heart[i] = COPY_RESOURCE("TrumpCard", CImage);
		diamond[i] = COPY_RESOURCE("TrumpCard", CImage);
		club[i] = COPY_RESOURCE("TrumpCard", CImage);
		spade[i] = COPY_RESOURCE("TrumpCard", CImage);
		//切り取り
		heart[i].SetRect(23 + 293.6 * i, 23, 294 + 293.6 * i, 23 + 406);
		diamond[i].SetRect(23 + 293.6 * i, 452, 294 + 293.6 * i, 452 + 406);
		club[i].SetRect(23 + 293.6 * i, 881, 294 + 293.6 * i, 881 + 406);
		spade[i].SetRect(23 + 293.6 * i, 1310, 294 + 293.6 * i, 1310 + 406);
		//サイズ指定
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
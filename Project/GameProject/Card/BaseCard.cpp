#include "BaseCard.h"
#include "../Base/Base.h"
#include <iostream>
#include <random>
std::random_device rnd;
std::default_random_engine eng(rnd());
std::uniform_int_distribution<int> CardRan(0, 15);
//カードを引いたときに呼ばれる。
BaseCard::BaseCard():m_kill(false),Base(eType_Card){
	//カードを指定
	CardNum = CardRan(eng);
}
BaseCard::~BaseCard() {
	Base::Add(new BaseCard());
}
void BaseCard::Update() {
	//このカードが選ばれたときにカードの効果に応じて、その処理をする	
	//効果はカードの数字で判定
	//もしくは、カードのクラス側でvirtualにしておいて、呼ぶ
	//カードが使われた場合にキルする。
	//その後、新しいカードを呼ぶ
}
void BaseCard::ImageSet() {
	//画像のコピー、切り取り、サイズ設定、名前設定。
}
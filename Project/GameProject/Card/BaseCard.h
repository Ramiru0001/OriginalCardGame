#pragma once
#include "../Base/Base.h"
#include <Gllibrary.h>
//カードの優先度
enum class ECardNum
{
	eGoddess_0,//女神カード
	eGoddess_1,//女神カード
	eGoddess_2,//女神カード
	eGoddess_3,//女神カード
	eMagic_0,//猫(魔法)カード
	eMagic_1,//猫(魔法)カード
	eMagic_2,//猫(魔法)カード
	eMagic_3,//猫(魔法)カード
	eNormal_0,//ノーマル
	eNormal_1,//ノーマル
	eNormal_2,//ノーマル
	eNormal_3,//ノーマル
	eDeveil_0,//犯罪者、悪魔カード
	eDeveil_1,//犯罪者、悪魔カード
	eDeveil_2,//犯罪者、悪魔カード
	eDeveil_3,//犯罪者、悪魔カード
};
//カードを引いたときに呼ばれる
class BaseCard :public Base{
public:
	//カードの指定
	int CardNum;
	//削除フラグ
	bool m_kill;
	//カードリスト
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